#include "EnumController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int EnumController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();
        int cxxrecord_id = model.get_current_cxxrecord_id();

        std::vector<std::string> data = model.get_data();
        std::string type = data[0];
        std::string name = data[1];
        std::string qualified_name = data[2];
        std::string variables = data[3];
        std::string parent_type = data[4];
        std::string parent_name = data[5];
        std::string access = data[6];

        sqlite3_stmt* stmt;
        int enum_id = -1;
        const char* selectSQL = "SELECT enum_id FROM Enum Where name = ? AND type = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                enum_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (enum_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO Enum (name, type, qualified_name, variables, access, file_id, namespace_id, cxxrecord_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, qualified_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, variables.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, access.c_str(), -1, SQLITE_STATIC);
                
                sqlite3_bind_int(stmt, 6, file_id);
                sqlite3_bind_int(stmt, 7, namespace_id);
                sqlite3_bind_int(stmt, 8, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}