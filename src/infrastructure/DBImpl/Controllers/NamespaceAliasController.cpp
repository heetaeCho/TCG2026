#include "NamespaceAliasController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int NamespaceAliasController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();
        int cxxrecord_id = model.get_current_cxxrecord_id();

        std::vector<std::string> data = model.get_data();
        std::string content = data[0];
        
        sqlite3_stmt* stmt;
        int namespace_alias_id = -1;
        const char* selectSQL = "SELECT namespace_alias_id FROM NamespaceAlias Where content = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, content.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                namespace_alias_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (namespace_alias_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO NamespaceAlias (content, file_id, namespace_id, cxxrecord_id) VALUES (?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, content.c_str(), -1, SQLITE_STATIC);

                sqlite3_bind_int(stmt, 2, file_id);
                sqlite3_bind_int(stmt, 3, namespace_id);
                sqlite3_bind_int(stmt, 4, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}