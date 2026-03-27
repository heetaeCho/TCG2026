#include "FrontendAction.hpp"
#include "ASTConsumer.hpp"

#include <iostream>

namespace NewTCG::domain::code_analyzer {
    FrontendAction::FrontendAction(){}

    std::unique_ptr<clang::ASTConsumer> FrontendAction::CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef InFile) {
        return std::make_unique<ASTConsumer>(compiler);
    }

    void FrontendAction::EndSourceFileAction() {}
}