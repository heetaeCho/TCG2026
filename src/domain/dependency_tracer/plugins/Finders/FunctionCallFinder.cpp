#include "FunctionCallFinder.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    FunctionCallFinder::FunctionCallFinder(const AbsModel& base, adapter::IDBAdapter* db) : IFinder(db) {
        model = FunctionCallModel(base);
    }

    void FunctionCallFinder::find(clang::FunctionDecl* decl) {
        TraverseStmt(decl->getBody());
    }

    bool FunctionCallFinder::VisitVarDecl(VarDecl *VD) {
        if (Expr *InitExpr = VD->getInit()) {
            if (auto *Call = dyn_cast<CallExpr>(InitExpr)) {
                return VisitCallExpr(Call); // ✅ 변수 초기화 함수 호출도 포함
            }
        }
        return true;
    }

    bool FunctionCallFinder::VisitCallExpr(CallExpr *CE) {
        if (FunctionDecl *FD = CE->getDirectCallee()) {
            SourceLocation DeclLoc = FD->getLocation();
            if (DeclLoc.isMacroID()) return true; // 매크로에서 생성된 함수 제외

            if (DeclLoc.isValid()) {
                clang::SourceManager &SM = FD->getASTContext().getSourceManager();
                std::string declFile = SM.getFilename(DeclLoc).str();
                if (declFile.find(config.project_name) == std::string::npos) {
                    return true; // 프로젝트 외부 함수 제외
                }

                std::string functionName = FD->getNameAsString();
                std::string defFile = "";

                // ✅ 일반 함수의 정의 찾기
                if (FunctionDecl *Definition = FD->getDefinition()) {
                    SourceLocation DefLoc = Definition->getLocation();
                    defFile = SM.getFilename(DefLoc).str();
                }

                // ✅ 템플릿 함수의 정의 찾기
                if (FD->isTemplateInstantiation()) {
                    if (FunctionDecl *TemplatePattern = FD->getTemplateInstantiationPattern()) {
                        SourceLocation TemplateLoc = TemplatePattern->getLocation();
                        defFile = SM.getFilename(TemplateLoc).str();
                    }
                }

                std::string parameters = "";
                for (unsigned int i = 0; i < FD->getNumParams(); ++i) {
                    ParmVarDecl *param = FD->getParamDecl(i);
                    if (i > 0) parameters += ", ";
                    std::string _param_type = param->getType().getAsString();
                    std::string _param_var = param->getNameAsString();
                    if (_param_type == "_Bool") {
                        _param_type = "bool";
                    }
                    parameters += _param_type + " " + _param_var; // 타입 가져오기
                }

                model.callee_qualified_name = FD->getQualifiedNameAsString();
                model.callee_parameters = parameters;
                add_to_db();
                // std::cout << "📌 FunctionCall: " << functionName
                //         << " parameters: " << parameters
                //         << ", 파일: " << defFile << ")\n";

                // if (!functionName.empty()) {
                //     FunctionCallInfo _functionCallInfo;
                //     _functionCallInfo.decl_file_name = declFile;
                //     _functionCallInfo.def_file_name = defFile;
                //     _functionCallInfo.function_name = functionName;
                //     _functionCallInfo.parameters = parameters;
                //     functionCallInfo->insert(_functionCallInfo);
                // }
            }
        }
        return true;
    }
    bool FunctionCallFinder::VisitCXXConstructExpr(CXXConstructExpr *CE) {
        if (CXXConstructorDecl *FD = CE->getConstructor()) {
            SourceLocation DeclLoc = CE->getLocation();
            if (DeclLoc.isMacroID()) return true; // 매크로에서 생성된 함수 제외

            if (DeclLoc.isValid()) {
                clang::SourceManager &SM = FD->getASTContext().getSourceManager();
                std::string declFile = SM.getFilename(DeclLoc).str();
                if (declFile.find(config.project_name) == std::string::npos) {
                    return true; // 프로젝트 외부 함수 제외
                }

                std::string functionName = FD->getNameAsString();
                std::string defFile = "";

                // ✅ 일반 함수의 정의 찾기
                if (FunctionDecl *Definition = FD->getDefinition()) {
                    SourceLocation DefLoc = Definition->getLocation();
                    defFile = SM.getFilename(DefLoc).str();
                }

                // ✅ 템플릿 함수의 정의 찾기
                if (FD->isTemplateInstantiation()) {
                    if (FunctionDecl *TemplatePattern = FD->getTemplateInstantiationPattern()) {
                        SourceLocation TemplateLoc = TemplatePattern->getLocation();
                        defFile = SM.getFilename(TemplateLoc).str();
                    }
                }

                std::string parameters = "";
                for (unsigned int i = 0; i < FD->getNumParams(); ++i) {
                    ParmVarDecl *param = FD->getParamDecl(i);
                    if (i > 0) parameters += ", ";
                    std::string _param_type = param->getType().getAsString();
                    std::string _param_var = param->getNameAsString();
                    if (_param_type == "_Bool") {
                        _param_type = "bool";
                    }
                    parameters += _param_type + " " + _param_var; // 타입 가져오기
                }

                model.callee_qualified_name = FD->getQualifiedNameAsString();
                model.callee_parameters = parameters;
                model.is_callee_constructor = true;
                add_to_db();

                // std::cout << "📌 FunctionCall: " << functionName
                //         << " parameters: " << parameters
                //         << ", 파일: " << defFile << ")\n";

                // if (!functionName.empty()) {
                //     FunctionCallInfo _functionCallInfo;
                //     _functionCallInfo.decl_file_name = declFile;
                //     _functionCallInfo.def_file_name = defFile;
                //     _functionCallInfo.function_name = functionName;
                //     _functionCallInfo.parameters = parameters;
                //     _functionCallInfo.isCallerConstructor = true;
                //     functionCallInfo->insert(_functionCallInfo);
                // }
            }
        }
        return true;
    }
}