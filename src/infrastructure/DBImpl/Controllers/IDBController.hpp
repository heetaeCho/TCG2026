#pragma once

#include <sqlite3.h>
#include "domain/code_analyzer/model/AbsModel.hpp"
#include "domain/dependency_tracer/model/AbsModel.hpp"

namespace entity_model = NewTCG::domain::code_analyzer;
namespace trace_model = NewTCG::domain::dependency_tracer;

namespace NewTCG::infrastructure::DBImpl {
class IDBController {
    protected:
    int get_file_id(sqlite3* db, trace_model::AbsModel& model);
    int get_caller_function_id(sqlite3* db, trace_model::AbsModel& model);
    public:
    virtual ~IDBController() = default;
    virtual int add_to_db(sqlite3* db, entity_model::AbsModel& model) { return 0; };
    virtual int add_to_db(sqlite3* db, trace_model::AbsModel& model) { return 0; };
};
}
