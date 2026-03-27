#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class CXXRecordModel : public AbsModel {
        public:
        inline static int anonimous_id = 0;
        ~CXXRecordModel() = default;
        std::string record_type;
        std::string name;
        std::string qualified_name;
        std::string inheritances;
        std::string _template;
        std::string access;

        std::string parent_type;
        std::string parent_name;
        int parent_cxxrecord_id;

        std::vector<std::string> get_data() {
            std::vector<std::string> data;
            data.push_back(record_type);
            data.push_back(name);
            data.push_back(qualified_name);
            data.push_back(inheritances);
            data.push_back(_template);
            data.push_back(access);
            data.push_back(parent_type);
            data.push_back(parent_name);
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