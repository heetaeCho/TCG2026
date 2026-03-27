#include "IDBController.hpp"

#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    int IDBController::get_file_id(sqlite3* db, trace_model::AbsModel& model) {
        int file_id = -1;
        std::map<std::string, std::string> data = model.get_data();
        std::string file_name = data["file_name"];

        // std::cout << "in get_file_id(): " << file_name << std::endl;

        sqlite3_stmt* stmt;
        const char* selectSQL = "SELECT file_id FROM File WHERE name = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, file_name.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                file_id = sqlite3_column_int(stmt, 0);
            }
        } 
        sqlite3_finalize(stmt);
        return file_id;
    }

    int IDBController::get_caller_function_id(sqlite3* db, trace_model::AbsModel& model) {
        int function_def_id = -1;
        std::map<std::string, std::string> data = model.get_data();
        std::string is_caller_constructor = data["is_caller_constructor"] == "0" ? "false" : "true";
        std::string caller_qualified_name = data["caller_qualified_name"];
        std::string caller_parameters = data["caller_parameters"];

        sqlite3_stmt* stmt;
        const char* selectSQL;
        if (is_caller_constructor == "false") {
            selectSQL = "SELECT function_def_id FROM FunctionDefinition WHERE qualified_name = ? AND parameters = ?;";
        } else {
            selectSQL = "SELECT constructor_def_id FROM ConstructorDefinition WHERE qualified_name = ? AND parameters = ?;";
        }

        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, caller_qualified_name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, caller_parameters.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                function_def_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
        return function_def_id;
    }
}