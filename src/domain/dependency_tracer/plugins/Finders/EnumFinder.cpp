#include "EnumFinder.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    EnumFinder::EnumFinder(const AbsModel& base, adapter::IDBAdapter* db) : IFinder(db) {
        model = EnumModel(base);
    }

    void EnumFinder::find(clang::FunctionDecl* decl) {
        TraverseStmt(decl->getBody());
    }

    bool EnumFinder::VisitDeclRefExpr(DeclRefExpr *DRE) {
        if (auto *ECD = dyn_cast<EnumConstantDecl>(DRE->getDecl())) {
            if (EnumDecl *EnumType = dyn_cast<EnumDecl>(ECD->getDeclContext())) {
                clang::SourceManager &SM = EnumType->getASTContext().getSourceManager();
                SourceLocation Loc = EnumType->getLocation();
                if (!Loc.isValid() || Loc.isMacroID()) return true; // 매크로에서 생성된 Enum 제외

                std::string fileName = SM.getFilename(Loc).str();
                if (fileName.find(config.project_name) == std::string::npos) {
                    return true;
                }

                model.enum_qualified_name = EnumType->getQualifiedNameAsString();
                model.enum_type = EnumType->isScoped() ? "enum class" : "enum";
                add_to_db();
                // std::cout << "📌 Enum 사용: " << ECD->getNameAsString()
                //         << " (속한 Enum: " << EnumType->getNameAsString()
                //         << ", 파일: " << fileName << ")\n";
            }
        }
        return true;
    }
}