#pragma once

#include "AbsHandler.hpp"
#include "FileModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class FileHandler : public AbsHandler {
        public:
        FileModel model;
        FileHandler() = delete;
        FileHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void add_to_db(std::string file_name) {
            model.name = file_name;
            int file_id = db->add_to_db("File", model);
            model.set_current_file_id(file_id);
        }
    };
}