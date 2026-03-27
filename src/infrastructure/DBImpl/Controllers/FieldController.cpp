#include "FieldController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int FieldController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();
        int cxxrecord_id = model.get_current_cxxrecord_id();

        std::vector<std::string> data = model.get_data();
        std::string name = data[0];
        std::string type = data[1];
        std::string value = data[2];
        bool is_const = data[3] == "false" ? false : true;
        bool is_static = data[4] == "false" ? false : true;
        std::string access = data[5];

        sqlite3_stmt* stmt;
        int field_id = -1;
        const char* selectSQL = "SELECT field_id FROM Field Where name = ? AND type = ? AND value = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, value.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                field_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (field_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO Field (name, type, value, is_const, is_static, access, file_id, namespace_id, cxxrecord_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, value.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 4, is_const);
                sqlite3_bind_int(stmt, 5, is_static);
                sqlite3_bind_text(stmt, 6, access.c_str(), -1, SQLITE_STATIC);
                
                sqlite3_bind_int(stmt, 7, file_id);
                sqlite3_bind_int(stmt, 8, namespace_id);
                sqlite3_bind_int(stmt, 9, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}