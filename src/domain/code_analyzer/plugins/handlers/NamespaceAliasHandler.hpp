#pragma once 

#include "AbsHandler.hpp"
#include "NamespaceAliasModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class NamespaceAliasHandler : public AbsHandler {
        public:
        NamespaceAliasModel model;
        NamespaceAliasHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::NamespaceAliasDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("NamespaceAlias", model);
        }
    };
}