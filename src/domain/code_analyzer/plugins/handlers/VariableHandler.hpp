#pragma once 

#include "AbsHandler.hpp"
#include "VariableModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class VariableHandler : public AbsHandler {
        public:
        VariableModel model;
        VariableHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::VarDecl* decl);

        void add_to_db() {
            db->add_to_db("Variable", model);
        }
    };
}