#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include "domain/configurator/model/ConfigModel.hpp"
#include "Visitor.hpp"

#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"

namespace configurator = NewTCG::domain::configurator;
namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;

namespace NewTCG::domain::code_analyzer {
    class ASTConsumer : public clang::ASTConsumer {
        private:
            configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
            std::unique_ptr<adapter::IDBAdapter> db = std::make_unique<infra_db::AbsDBImpl>();

            clang::CompilerInstance& compiler;
            clang::SourceManager &sourceManager;
            Visitor visitor;

        public:
            explicit ASTConsumer(clang::CompilerInstance& compiler);
            virtual bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;
    };
}