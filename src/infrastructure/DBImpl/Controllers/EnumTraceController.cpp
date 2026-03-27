#include "EnumTraceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int EnumTraceController::add_to_db(sqlite3* db, trace_model::AbsModel& model) {
        int file_id = get_file_id(db, model);
        int caller_function_id = get_caller_function_id(db, model);
        int enum_id = get_enum_id(db, model);

        std::map<std::string, std::string> data = model.get_data();
        std::string is_caller_constructor = data["is_caller_constructor"] == "0" ? "function" : "constructor";

        sqlite3_stmt* stmt;
        if (caller_function_id != -1 && enum_id != -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO EnumTrace (caller_id, caller_type, enum_id, file_id) VALUES (?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, caller_function_id);
                sqlite3_bind_text(stmt, 2, is_caller_constructor.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 3, enum_id);
                sqlite3_bind_int(stmt, 4, file_id);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }

    int EnumTraceController::get_enum_id(sqlite3* db, trace_model::AbsModel& model) {
        int enum_id = -1;

        std::map<std::string, std::string> data = model.get_data();
        std::string enum_qualified_name = data["enum_qualified_name"];
        std::string enum_type = data["enum_type"];

        sqlite3_stmt* stmt;
        const char* selectSQL = "SELECT enum_id FROM Enum Where qualified_name = ? AND type = ?;";

        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, enum_qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, enum_type.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                enum_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
        return enum_id;
    }
}