#include "NamespaceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int NamespaceController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        std::vector<std::string> data = model.get_data();

        int file_id = model.get_current_file_id();
        std::string name = data[0];
        std::string parent_name = data[1];

        sqlite3_stmt* stmt;
        int namespace_id = -1;
        int parent_id =-1 ;

        if (!parent_name.empty()) {
            const char* selectSQL = "SELECT namespace_id FROM Namespace WHERE name = ? AND file_id = ?;";
            if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, parent_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, file_id);

                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    parent_id = sqlite3_column_int(stmt, 0);
                }
            }
            sqlite3_finalize(stmt);
        }

        const char* selectSQL = "SELECT namespace_id FROM Namespace Where name = ? AND file_id = ? AND parent_id = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, file_id);
            sqlite3_bind_int(stmt, 3, parent_id);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                namespace_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (namespace_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO Namespace (name, file_id, parent_id) VALUES (?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, file_id);
                sqlite3_bind_int(stmt, 3, parent_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    namespace_id = sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        model.set_current_namespace_id(namespace_id);
        return parent_id;
    }
}