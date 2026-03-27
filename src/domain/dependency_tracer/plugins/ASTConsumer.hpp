#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include "domain/configurator/model/ConfigModel.hpp"
#include "Visitor.hpp"

namespace configurator = NewTCG::domain::configurator;

namespace NewTCG::domain::dependency_tracer {
    class ASTConsumer : public clang::ASTConsumer {
        private:
            configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
            

            clang::CompilerInstance& compiler;
            clang::SourceManager &sourceManager;
            Visitor visitor;

        public:
            explicit ASTConsumer(clang::CompilerInstance& compiler);
            virtual bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;
    };
}