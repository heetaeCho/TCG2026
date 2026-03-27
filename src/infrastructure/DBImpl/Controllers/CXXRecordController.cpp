#include "CXXRecordController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int CXXRecordController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {
        int file_id = model.get_current_file_id();
        int namespace_id = model.get_current_namespace_id();

        std::vector<std::string> data = model.get_data();
        std::string record_type = data[0];
        std::string name = data[1];
        std::string qualified_name = data[2];
        std::string inheritances = data[3];
        std::string _template = data[4];
        std::string access = data[5];

        std::string parent_type = data[6];
        std::string parent_name = data[7];

        sqlite3_stmt* stmt;
        int cxxrecord_id = -1;
        int parent_id =-1 ;

        if (!parent_name.empty()) {
            const char* selectSQL = "SELECT cxxrecord_id FROM CXXRecord WHERE name = ? AND file_id = ?;";
            if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, parent_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, file_id);

                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    parent_id = sqlite3_column_int(stmt, 0);
                }
            }
            sqlite3_finalize(stmt);
        }

        const char* selectSQL = "SELECT cxxrecord_id FROM CXXRecord Where name = ? AND file_id = ? AND namespace_id = ? AND parent_id = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, file_id);
            sqlite3_bind_int(stmt, 3, namespace_id);
            sqlite3_bind_int(stmt, 4, parent_id);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                cxxrecord_id = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);

        if (cxxrecord_id == -1) {
            const char* insertSQL = "INSERT OR IGNORE INTO CXXRecord (name, qualified_name, record_type, inheritances, template, access, file_id, namespace_id, parent_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, qualified_name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, record_type.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, inheritances.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, _template.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 6, access.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 7, file_id);
                sqlite3_bind_int(stmt, 8, namespace_id);
                sqlite3_bind_int(stmt, 9, parent_id);

                sqlite3_step(stmt);  // INSERT 실행
            }
            sqlite3_finalize(stmt);

            // INSERT 성공 여부와 무관하게 항상 SELECT 재조회
            const char* selectSQL2 = "SELECT cxxrecord_id FROM CXXRecord WHERE name = ? AND file_id = ? AND namespace_id = ? AND parent_id = ?;";
            if (sqlite3_prepare_v2(db, selectSQL2, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, file_id);
                sqlite3_bind_int(stmt, 3, namespace_id);
                sqlite3_bind_int(stmt, 4, parent_id);
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    cxxrecord_id = sqlite3_column_int(stmt, 0);
                }
            }
            sqlite3_finalize(stmt);
        }
        model.set_current_cxxrecord_id(cxxrecord_id);
        return parent_id;
    }
}