#pragma once 

#include "AbsHandler.hpp"
#include "TypeAliasModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class TypeAliasHandler : public AbsHandler {
        public:
        TypeAliasModel model;
        TypeAliasHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::TypeAliasDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("TypeAlias", model);
        }
    };
}