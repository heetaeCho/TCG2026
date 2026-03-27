#pragma once 

#include "AbsHandler.hpp"
#include "LinkageSpecModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class LinkageSpecHandler : public AbsHandler {
        public:
        LinkageSpecModel model;
        LinkageSpecHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::LinkageSpecDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);

            add_to_db();
        }

        void add_to_db() {
            std::vector<std::string> data = model.get_data();
            // for (std::string name : data) {
            //     std::cout << name << std::endl;
            // }
            // std::cout << " ----------------- " << std::endl;
        }
    };
}