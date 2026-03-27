#include "ConstructorDefinitionController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int ConstructorDefinitionController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();

        std::vector<std::string> data = model.get_data();
        std::string __type = data[0];
        std::string name = data[1];
        std::string qualified_name = data[2];
        std::string access = data[3];
        std::string _template = data[4];
        std::string parameters = data[5];
        std::string body = data[6];
        std::string definition = data[7];

        std::string parent_type = data[8];
        std::string parent_name = data[9];

        std::string cxx_record_qname = data[10];

        sqlite3_stmt* stmt;
        int cxxrecord_id = -1;
        const char* selectCXXRecordSQL = "SELECT cxxrecord_id FROM CXXRecord Where qualified_name = ?;";
        if (sqlite3_prepare_v2(db, selectCXXRecordSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, cxx_record_qname.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                cxxrecord_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        int constructor_def_id = -1;
        const char* selectSQL = "SELECT constructor_def_id FROM ConstructorDefinition Where qualified_name = ? AND parameters = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, parameters.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                constructor_def_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (constructor_def_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO ConstructorDefinition \
            (name, qualified_name, access, template, parameters, body, definition, file_id, namespace_id, cxxrecord_id) \
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, qualified_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, access.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, _template.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, parameters.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 6, body.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 7, definition.c_str(), -1, SQLITE_STATIC);
                
                sqlite3_bind_int(stmt, 8, file_id);
                sqlite3_bind_int(stmt, 9, namespace_id);
                sqlite3_bind_int(stmt, 10, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}