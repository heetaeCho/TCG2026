#include "FriendHandler.hpp"
#include <iostream>

namespace NewTCG::domain::code_analyzer {
    void FriendHandler::handle(clang::FriendDecl* decl) {
            clang::SourceRange range = decl->getSourceRange();
            clang::SourceLocation startLoc = range.getBegin();
            clang::SourceLocation endLoc = range.getEnd();
            model.line = getOrigineCode(startLoc, endLoc);
            add_to_db();
        }
}