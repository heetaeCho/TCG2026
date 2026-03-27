#pragma once 

#include "AbsHandler.hpp"
#include "UsingModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class UsingHandler : public AbsHandler {
        public:
        UsingModel model;
        UsingHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::UsingDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("Using", model);
        }
    };
}