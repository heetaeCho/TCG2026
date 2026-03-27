#include "HeaderTraceController.hpp"

#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    int HeaderTraceController::add_to_db(sqlite3* db, trace_model::AbsModel& model) {
        int file_id = get_file_id(db, model);

        std::map<std::string, std::string> data = model.get_data();
        std::string headers = data["headers"];

        // std::cout << "========================================================" << std::endl;
        // std::cout << data["file_name"] << std::endl;
        // std::cout << file_id << std::endl;
        // std::cout << headers << std::endl;
        // std::cout << "========================================================" << std::endl;

        sqlite3_stmt* stmt;
        if (file_id != -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO HeaderTrace (file_id, headers) VALUES (?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, file_id);
                sqlite3_bind_text(stmt, 2, headers.c_str(), -1, SQLITE_STATIC);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}