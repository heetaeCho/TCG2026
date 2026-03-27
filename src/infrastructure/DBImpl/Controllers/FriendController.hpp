#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class FriendController : public IDBController{
        public:
        FriendController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}