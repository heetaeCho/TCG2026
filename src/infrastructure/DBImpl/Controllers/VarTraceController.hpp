#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class VarTraceController : public IDBController{
        public:
        VarTraceController() {}
        int add_to_db(sqlite3* db, trace_model::AbsModel& model) override;
        int get_var_id(sqlite3* db, trace_model::AbsModel& model);
    };
}