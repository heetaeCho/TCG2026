#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class FileModel : public AbsModel {
        public:
        ~FileModel() = default;
        std::string name;

        std::vector<std::string> get_data() override {
            std::vector<std::string> data;
            data.push_back(name);
            return data;
        }

        void set_current_file_id(int file_id) { AbsModel::set_current_file_id(file_id); }
        int get_current_file_id() { return AbsModel::get_current_file_id(); }
    };
}