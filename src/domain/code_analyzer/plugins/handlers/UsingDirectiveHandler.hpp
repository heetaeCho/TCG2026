#pragma once 

#include "AbsHandler.hpp"
#include "UsingDirectiveModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class UsingDirectiveHandler : public AbsHandler {
        public:
        UsingDirectiveModel model;
        UsingDirectiveHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::UsingDirectiveDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("UsingDirective", model);
        }
    };
}