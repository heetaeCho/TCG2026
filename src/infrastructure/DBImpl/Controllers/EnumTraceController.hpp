#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class EnumTraceController : public IDBController{
        public:
        EnumTraceController() {}
        int add_to_db(sqlite3* db, trace_model::AbsModel& model) override;
        int get_enum_id(sqlite3* db, trace_model::AbsModel& model);
    };
}