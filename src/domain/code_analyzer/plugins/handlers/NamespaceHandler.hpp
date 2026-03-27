#pragma once

#include "AbsHandler.hpp"
#include "NamespaceModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class NamespaceHandler : public AbsHandler {
        public:
        NamespaceModel model;
        NamespaceHandler() = delete;
        NamespaceHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::NamespaceDecl* decl);
        void resolve_current_id();
        void add_to_db();
    };
}