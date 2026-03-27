#pragma once 

#include "AbsHandler.hpp"
#include "RecordModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class RecordHandler : public AbsHandler {
        public:
        RecordModel model;
        RecordHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::RecordDecl* decl);
        void determineParentContext(clang::RecordDecl* decl);
        std::string getVariables(clang::RecordDecl* decl);

        void add_to_db() {
            db->add_to_db("Record", model);
        }
    };
}