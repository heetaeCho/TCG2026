#include "FinderDispatcher.hpp"
#include "FunctionCallFinder.hpp"
#include "EnumFinder.hpp"
// #include "CXXRecordFinder.hpp"
#include "CXXRecordFinder_new.hpp"
#include "RecordFinder.hpp"
#include "VarFinder.hpp"


#include "domain/dependency_tracer/model/AbsModel.hpp"

namespace NewTCG::domain::dependency_tracer {
    void FinderDispatcher::setup(clang::FunctionDecl* decl) {
        clang::SourceLocation Loc = decl->getLocation();
        clang::SourceManager& sourceManager = decl->getASTContext().getSourceManager();

        AbsModel common;
        common.file_name = sourceManager.getFilename(Loc).str();
        common.caller_qualified_name = decl->getQualifiedNameAsString();
        common.caller_parameters = "";
        
        for (unsigned int i = 0; i < decl->getNumParams(); ++i) {
            ParmVarDecl *param = decl->getParamDecl(i);
            if (i > 0) common.caller_parameters += ", ";
            std::string _param_type = param->getType().getAsString();
            std::string _param_var = param->getNameAsString();
            if (_param_type == "_Bool") {
                _param_type = "bool";
            }
            common.caller_parameters += _param_type + " " + _param_var; // 타입 가져오기
        }
        if (auto* ctorDecl = llvm::dyn_cast<clang::CXXConstructorDecl>(decl)) {
            common.is_caller_constructor = true;
        }

        finders.push_back(std::make_unique<FunctionCallFinder>(common, db));
        finders.push_back(std::make_unique<EnumFinder>(common, db));
        // finders.push_back(std::make_unique<CXXRecordFinder>());
        finders.push_back(std::make_unique<CXXRecordFinderNew>(common, db));
        finders.push_back(std::make_unique<RecordFinder>(common, db));
        finders.push_back(std::make_unique<VarFinder>(common, db));
    }

    void FinderDispatcher::explore(clang::FunctionDecl* decl) {
        for (auto& finder : finders) {
            finder->find(decl);
        }
    }
}