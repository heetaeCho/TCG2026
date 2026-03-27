#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class EnumController : public IDBController{
        public:
        EnumController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}