#include "VarTraceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int VarTraceController::add_to_db(sqlite3* db, trace_model::AbsModel& model) {
        int file_id = get_file_id(db, model);
        int caller_function_id = get_caller_function_id(db, model);
        int var_id = get_var_id(db, model);

        std::map<std::string, std::string> data = model.get_data();
        std::string is_caller_constructor = data["is_caller_constructor"] == "0" ? "function" : "constructor";

        sqlite3_stmt* stmt;
        if (caller_function_id != -1 && var_id != -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO VarTrace (caller_id, caller_type, var_id, file_id) VALUES (?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, caller_function_id);
                sqlite3_bind_text(stmt, 2, is_caller_constructor.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 3, var_id);
                sqlite3_bind_int(stmt, 4, file_id);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            } else {
                std::cerr << "❌ Failed to step ADD: " << sqlite3_errmsg(db) << "\n";
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }

    int VarTraceController::get_var_id(sqlite3* db, trace_model::AbsModel& model) {
        int var_id = -1;

        std::map<std::string, std::string> data = model.get_data();
        std::string var_name = data["var_name"];
        std::string var_type = data["var_type"];
        // std::string var_value = data["var_value"];

        sqlite3_stmt* stmt;
        // const char* selectSQL = "SELECT variable_id FROM Variable Where name = ? AND type = ? AND value = ?;";
        const char* selectSQL = "SELECT variable_id FROM Variable Where name = ? AND type = ?;";

        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, var_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, var_type.c_str(), -1, SQLITE_STATIC);
            // sqlite3_bind_text(stmt, 3, var_value.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                var_id = sqlite3_column_int(stmt, 0);
            }
        } else {
            std::cerr << "❌ Failed to step ADD: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_finalize(stmt);
        return var_id;
    }
}