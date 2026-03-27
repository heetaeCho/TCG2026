#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class HeaderTraceController : public IDBController{
        public:
        HeaderTraceController() {}
        int add_to_db(sqlite3* db, trace_model::AbsModel& model) override;
    };
}