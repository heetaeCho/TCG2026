#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class FunctionCallTraceController : public IDBController{
        public:
        FunctionCallTraceController() {}
        int add_to_db(sqlite3* db, trace_model::AbsModel& model) override;
        int get_callee_id(sqlite3* db, trace_model::AbsModel& model);
    };
}