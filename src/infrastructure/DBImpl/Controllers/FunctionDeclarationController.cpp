#include "FunctionDeclarationController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int FunctionDeclarationController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
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

        std::string return_type = data[6];
        bool is_static = data[7] == "true" ? true : false;
        bool is_virtual = data[8] == "true" ? true : false;
        bool is_override = data[9] == "true" ? true : false;
        bool is_final = data[10] == "true" ? true : false;
        bool is_friend = data[11] == "true" ? true : false;
        bool is_const = data[12] == "true" ? true : false;

        std::string parent_type = data[13];
        std::string parent_name = data[14];

        sqlite3_stmt* stmt;
        int function_decl_id = -1;
        const char* selectSQL = "SELECT function_decl_id FROM FunctionDeclaration Where qualified_name = ? AND parameters = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, parameters.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                function_decl_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (function_decl_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO FunctionDeclaration \
            (name, qualified_name, access, template, parameters, return_type, is_static, is_virtual, is_override, is_final, is_friend, is_const, file_id, namespace_id, cxxrecord_id) \
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, qualified_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, access.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, _template.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, parameters.c_str(), -1, SQLITE_STATIC);

                sqlite3_bind_text(stmt, 6, return_type.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 7, is_static);
                sqlite3_bind_int(stmt, 8, is_virtual);
                sqlite3_bind_int(stmt, 9, is_override);
                sqlite3_bind_int(stmt, 10, is_final);
                sqlite3_bind_int(stmt, 11, is_friend);
                sqlite3_bind_int(stmt, 12, is_const);
                
                sqlite3_bind_int(stmt, 13, file_id);
                sqlite3_bind_int(stmt, 14, namespace_id);
                sqlite3_bind_int(stmt, 15, cxxrecord_id);
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    sqlite3_last_insert_rowid(db);
                }
            }
            sqlite3_finalize(stmt);
        }
        return 0;
    }
}