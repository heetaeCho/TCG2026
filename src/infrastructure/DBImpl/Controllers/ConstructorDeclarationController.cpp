#include "ConstructorDeclarationController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int ConstructorDeclarationController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();
        int cxxrecord_id = model.get_current_cxxrecord_id();

        std::vector<std::string> data = model.get_data();
        std::string __type = data[0];
        std::string name = data[1];
        std::string qualified_name = data[2];
        std::string access = data[3];
        std::string _template = data[4];
        std::string parameters = data[5];
        bool is_const = data[6] == "true" ? true : false;
        bool is_explicit = data[7]  == "true" ? true : false;
        bool is_delete = data[8] == "true" ? true : false;
        std::string parent_type = data[9];
        std::string parent_name = data[10];

        sqlite3_stmt* stmt;
        int constructor_decl_id = -1;
        const char* selectSQL = "SELECT constructor_decl_id FROM ConstructorDeclaration Where qualified_name = ? AND parameters = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, parameters.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                constructor_decl_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (constructor_decl_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO ConstructorDeclaration \
            (name, qualified_name, access, template, parameters, is_const, is_explicit, is_delete, file_id, namespace_id, cxxrecord_id) \
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, qualified_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, access.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, _template.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, parameters.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 6, is_const);
                sqlite3_bind_int(stmt, 7, is_explicit);
                sqlite3_bind_int(stmt, 8, is_delete);
                
                sqlite3_bind_int(stmt, 9, file_id);
                sqlite3_bind_int(stmt, 10, namespace_id);
                sqlite3_bind_int(stmt, 11, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}