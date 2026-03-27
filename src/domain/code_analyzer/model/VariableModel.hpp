#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class VariableModel : public AbsModel {
        public:
        ~VariableModel() = default;
        std::string name;
        std::string type;
        std::string value;
        std::string is_const = "false";
        std::string is_static = "false";

        std::vector<std::string> get_data() {
            std::vector<std::string> data;
            data.push_back(name);
            data.push_back(type);
            data.push_back(value);
            data.push_back(is_const);
            data.push_back(is_static);
            return data;
        }

        void set_current_file_id(int file_id) { AbsModel::set_current_file_id(file_id); }
        int get_current_file_id() { return AbsModel::get_current_file_id(); }

        void set_current_namespace_id(int namespace_id) { AbsModel::set_current_namespace_id(namespace_id); }
        int get_current_namespace_id() { return AbsModel::get_current_namespace_id(); }

        void set_current_cxxrecord_id(int cxxrecord_id) { AbsModel::set_current_cxxrecord_id(cxxrecord_id); }
        int get_current_cxxrecord_id() { return AbsModel::get_current_cxxrecord_id(); }
    };
}