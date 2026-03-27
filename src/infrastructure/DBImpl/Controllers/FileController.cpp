#include "FileController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    int FileController::add_to_db(sqlite3* db, entity_model::AbsModel& model) {

        std::vector<std::string> data = model.get_data();
        std::string file_name = data[0];

        sqlite3_stmt* stmt;
        int file_id = -1;

        // 1️⃣ `File_name`으로 검색
        const char* selectSQL = "SELECT file_id FROM File WHERE name = ?;";
        if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, file_name.c_str(), -1, SQLITE_STATIC);
            
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                file_id = sqlite3_column_int(stmt, 0); // File_id 가져오기
                // std::cout << "파일이 이미 존재함: " << file_name << " (File_id: " << fileId << ")\n";
            }
        }
        sqlite3_finalize(stmt);

        if (file_id == -1) {
            // 2️⃣ `FileInfo`에 파일 추가
            const char* insertSQL = "INSERT INTO File (name) VALUES (?);";
            if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, file_name.c_str(), -1, SQLITE_STATIC);
                
                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    file_id = sqlite3_last_insert_rowid(db); // 새로 추가된 파일의 ID 가져오기
                    // std::cout << "새 파일 추가됨: " << file_name << " (File_id: " << fileId << ")\n";
                }
            }
            sqlite3_finalize(stmt);
        }

        return file_id;
    }
}