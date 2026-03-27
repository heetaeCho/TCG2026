#include "RecordTraceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int RecordTraceController::add_to_db(sqlite3* db, trace_model::AbsModel& model) {
        int file_id = get_file_id(db, model);
        int caller_function_id = get_caller_function_id(db, model);
        int record_id = get_record_id(db, model);

        std::map<std::string, std::string> data = model.get_data();
        std::string is_caller_constructor = data["is_caller_constructor"] == "0" ? "function" : "constructor";

        sqlite3_stmt* stmt;
        if (caller_function_id != -1 && record_id != -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO RecordTrace (caller_id, caller_type, record_id, file_id) VALUES (?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, caller_function_id);
                sqlite3_bind_text(stmt, 2, is_caller_constructor.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 3, record_id);
                sqlite3_bind_int(stmt, 4, file_id);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }

    int RecordTraceController::get_record_id(sqlite3* db, trace_model::AbsModel& model) {
        int record_id = -1;

        std::map<std::string, std::string> data = model.get_data();
        std::string record_qualified_name = data["record_qualified_name"];
        std::string record_type = data["record_type"];

        sqlite3_stmt* stmt;
        const char* selectSQL = "SELECT record_id FROM Record Where qualified_name = ? AND type = ?;";

        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, record_qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, record_type.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                record_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
        return record_id;
    }
}