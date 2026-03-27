#pragma once 

#include "AbsHandler.hpp"
#include "FriendModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class FriendHandler : public AbsHandler {
        public:
        FriendModel model;
        FriendHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::FriendDecl* decl);

        void add_to_db() {
            db->add_to_db("Friend", model);
        }
    };
}