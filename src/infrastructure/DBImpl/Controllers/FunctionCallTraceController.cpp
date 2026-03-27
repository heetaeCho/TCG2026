#include "FunctionCallTraceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int FunctionCallTraceController::add_to_db(sqlite3* db, trace_model::AbsModel& model) {
        std::map<std::string, std::string> data = model.get_data();
        int file_id = get_file_id(db, model);
        int caller_function_id = get_caller_function_id(db, model);
        int callee_function_id = get_callee_id(db, model);

        std::string is_caller_constructor = data["is_caller_constructor"] == "0" ? "function" : "constructor";
        std::string is_callee_constructor = data["is_callee_constructor"] == "0" ? "function" : "constructor";

        sqlite3_stmt* stmt;
        if (caller_function_id != -1 && callee_function_id != -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO FunctionCallTrace (caller_id, caller_type, callee_id, callee_type, file_id) VALUES (?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, caller_function_id);
                sqlite3_bind_text(stmt, 2, is_caller_constructor.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 3, callee_function_id);
                sqlite3_bind_text(stmt, 4, is_callee_constructor.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 5, file_id);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }

    int FunctionCallTraceController::get_callee_id(sqlite3* db, trace_model::AbsModel& model) {
        int function_def_id = -1;
        std::map<std::string, std::string> data = model.get_data();
        std::string is_caller_constructor = data["is_callee_constructor"] == "0" ? "false" : "true";
        std::string caller_qualified_name = data["callee_qualified_name"];
        std::string caller_parameters = data["callee_parameters"];

        sqlite3_stmt* stmt;
        const char* selectSQL;
        if (is_caller_constructor == "false") {
            selectSQL = "SELECT function_def_id FROM FunctionDefinition WHERE qualified_name = ? AND parameters = ?;";
        } else {
            selectSQL = "SELECT constructor_def_id FROM ConstructorDefinition WHERE qualified_name = ? AND parameters = ?;";
        }

        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, caller_qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, caller_parameters.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                function_def_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
        return function_def_id;
    }
}