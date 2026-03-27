#pragma once

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include "domain/configurator/model/ConfigModel.hpp"

#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"

namespace configurator = NewTCG::domain::configurator;
namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;

namespace NewTCG::domain::dependency_tracer {
    class Visitor : public clang::RecursiveASTVisitor<Visitor> {
        private:
        configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
        std::unique_ptr<adapter::IDBAdapter> db = std::make_unique<infra_db::AbsDBImpl>();

        clang::SourceManager &sourceManager;

        public:
        Visitor(clang::CompilerInstance& compiler);

        public:
        bool VisitFunctionDecl(clang::FunctionDecl* decl);
    };
}