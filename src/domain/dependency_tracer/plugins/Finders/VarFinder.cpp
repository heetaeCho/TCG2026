#include "VarFinder.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    VarFinder::VarFinder(const AbsModel& base, adapter::IDBAdapter* db) : IFinder(db) {
        model = VarModel(base);
    }

    void VarFinder::find(clang::FunctionDecl* decl) {
        // TraverseDecl(decl);
        TraverseStmt(decl->getBody());
    }

    bool VarFinder::VisitVarDecl(clang::VarDecl* decl) {
        // model.var_name = decl->getNameAsString();
        // model.var_type = decl->getType().getAsString();
        // if (model.var_type == "_Bool") {
        //     model.var_type = "bool";
        // }
        // if(const auto* init = decl->getInit()) {
        //     model.var_value = stmtToString(init);
        // }
        // add_to_db();
        return true;
    }

    bool VarFinder::VisitDeclRefExpr(DeclRefExpr *DRE) {
        if (auto *VD = dyn_cast<VarDecl>(DRE->getDecl())) {
            // 전역 변수 또는 정적 변수만 대상으로 할 수 있음 (필요시 조건 추가)
            if (!VD->hasGlobalStorage() && !VD->isStaticLocal()) return true;
    
            const DeclContext *DC = VD->getDeclContext();
            clang::SourceManager &SM = VD->getASTContext().getSourceManager();
            SourceLocation Loc = VD->getLocation();
            if (!Loc.isValid() || Loc.isMacroID()) return true; // 매크로에서 생성된 변수 제외
    
            std::string fileName = SM.getFilename(Loc).str();
            if (fileName.find(config.project_name) == std::string::npos) {
                return true; // 외부 파일 제외
            }
    
            model.var_name = VD->getNameAsString();
            model.var_type = VD->getType().getAsString();
            if (model.var_type == "_Bool") {
                model.var_type = "bool";
            }
            add_to_db();
        }
        return true;
    }
}