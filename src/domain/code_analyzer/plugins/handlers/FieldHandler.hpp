#pragma once 

#include "utils/StringUtils.hpp"
#include "AbsHandler.hpp"
#include "FieldModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class FieldHandler : public AbsHandler {
        public:
        FieldModel model;
        FieldHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::FieldDecl* decl);
        void handle(clang::CXXRecordDecl* decl);

        void add_to_db() {
            db->add_to_db("Field", model);
        }
    };
}