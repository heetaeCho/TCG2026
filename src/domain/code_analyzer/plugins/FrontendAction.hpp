#pragma once

#include <clang/Frontend/FrontendAction.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include "domain/configurator/model/ConfigModel.hpp"
#include "Visitor.hpp"

namespace NewTCG::domain::code_analyzer {
    class FrontendAction : public clang::ASTFrontendAction {
        public:
            FrontendAction();
            virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer\
            (clang::CompilerInstance& compiler, llvm::StringRef InFile) override;
            void EndSourceFileAction() override;
    };
}
