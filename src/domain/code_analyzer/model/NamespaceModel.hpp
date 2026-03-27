#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class NamespaceModel : public AbsModel {
        public:
        inline static int anonimous_id = 0;
        ~NamespaceModel() = default;
        std::string name;
        std::string parent_name;
        int parent_namespace_id = -1;

        std::vector<std::string> get_data() {
            std::vector<std::string> data;
            data.push_back(name);
            data.push_back(parent_name);
            return data;
        }

        void set_current_file_id(int file_id) { AbsModel::set_current_file_id(file_id); }
        int get_current_file_id() { return AbsModel::get_current_file_id(); }

        void set_current_namespace_id(int namespace_id) { AbsModel::set_current_namespace_id(namespace_id); }
        int get_current_namespace_id() { return AbsModel::get_current_namespace_id(); }
    };
}