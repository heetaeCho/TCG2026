#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class CXXRecordController : public IDBController{
        public:
        CXXRecordController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}