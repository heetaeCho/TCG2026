#pragma once 

#include "AbsHandler.hpp"
#include "EnumModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class EnumHandler : public AbsHandler {
        public:
        EnumModel model;
        EnumHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::EnumDecl* decl);
        void determineParentContext(clang::EnumDecl* decl);
        std::string getVariables(clang::EnumDecl* decl);

        void add_to_db() {
            db->add_to_db("Enum", model);
        }

    };
}