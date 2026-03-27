#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class RecordTraceController : public IDBController{
        public:
        RecordTraceController() {}
        int add_to_db(sqlite3* db, trace_model::AbsModel& model) override;
        int get_record_id(sqlite3* db, trace_model::AbsModel& model);
    };
}