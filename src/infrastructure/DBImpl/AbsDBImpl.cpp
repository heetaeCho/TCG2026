#include "infrastructure/DBImpl/AbsDBImpl.hpp"

namespace NewTCG::infrastructure::DBImpl {
    bool AbsDBImpl::open_db() {
        std::string temp = config.database_path + "/" + config.project_name + "_info.db";
        // std::cout << "here is  temp: " << temp << std::endl;
        const char* db_name = temp.c_str();
        int rc = sqlite3_open(db_name, &db);
        if (rc != SQLITE_OK) {
            // std::cout << "Failed to open database" << std::endl;
            return false;
        } else {
            // std::cout << "open database" << std::endl;
            return true;
        }
    }

    bool AbsDBImpl::create_tables() {
        for (std::string table : tables) {
            char* errorMessage = nullptr;
            int rc = sqlite3_exec(db, queries[table], nullptr, nullptr, &errorMessage);
            if (rc != SQLITE_OK) {
                sqlite3_free(errorMessage);
            }
        }
        return true;
    }

    int AbsDBImpl::add_to_db(const std::string& type, entity_model::AbsModel& model) {
        auto controller = controllerFactory.create(type);
        if (!controller) {
            std::cerr << "[ERROR] No controller for type: " << type << "\n";
            return -1;
        }
        return controller->add_to_db(db, model); // 실제 실행
    }

    int AbsDBImpl::add_to_db(const std::string& type, trace_model::AbsModel& model) {
        auto controller = controllerFactory.create(type);
        if (!controller) {
            std::cerr << "[ERROR] No controller for type: " << type << "\n";
            return -1;
        }
        return controller->add_to_db(db, model); // 실제 실행
    }
}