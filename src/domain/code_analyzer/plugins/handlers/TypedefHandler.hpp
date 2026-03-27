#pragma once 

#include "utils/StringUtils.hpp"
#include "AbsHandler.hpp"
#include "TypedefModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class TypedefHandler : public AbsHandler {
        public:
        TypedefModel model;
        TypedefHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::TypedefDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("Typedef", model);
        }
    };
}