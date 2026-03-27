#pragma once 

#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"

#include <clang/Basic/SourceManager.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include "domain/configurator/model/ConfigModel.hpp"

namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;
namespace configurator = NewTCG::domain::configurator;

namespace NewTCG::domain::dependency_tracer {
    class IFinder{
        protected:
        adapter::IDBAdapter* db;

        public:
        configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
        IFinder(adapter::IDBAdapter* db) : db(db) {}
        virtual ~IFinder() = default;
        virtual void find(clang::FunctionDecl* decl) = 0;
    };
}