#pragma once

#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::code_analyzer {
    class FunctionModel : public AbsModel {
        public:
        ~FunctionModel() = default;

        void set_current_file_id(int file_id) { AbsModel::set_current_file_id(file_id); }
        int get_current_file_id() { return AbsModel::get_current_file_id(); }

        void set_current_namespace_id(int namespace_id) { AbsModel::set_current_namespace_id(namespace_id); }
        int get_current_namespace_id() { return AbsModel::get_current_namespace_id(); }

        void set_current_cxxrecord_id(int cxxrecord_id) { AbsModel::set_current_cxxrecord_id(cxxrecord_id); }
        int get_current_cxxrecord_id() { return AbsModel::get_current_cxxrecord_id(); }
    };

    class DefinitionModel : public FunctionModel {
        public:
        std::string __type;
        std::string name;
        std::string qualified_name;
        std::string access;
        std::string _template;
        std::string parameters;
        std::string return_type;
        std::string body;
        std::string definition;

        std::string parent_type;
        std::string parent_name;

        std::string cxx_record_qname;

        std::vector<std::string> get_data() {
            std::vector<std::string> data;
            data.push_back(__type);
            data.push_back(name);
            data.push_back(qualified_name);
            data.push_back(access);
            data.push_back(_template);
            if (__type == "function") {
                data.push_back(return_type);
            }
            data.push_back(parameters);
            data.push_back(body);
            data.push_back(definition);
            data.push_back(parent_type);
            data.push_back(parent_name);
            data.push_back(cxx_record_qname);
            return data;
        }
    };

    class DeclarationModel : public FunctionModel {
        public:
        std::string __type;
        std::string name;
        std::string qualified_name;
        std::string access;
        std::string _template;
        std::string return_type;
        std::string parameters;

        // for function
        std::string is_static = "false";
        std::string is_virtual = "false";
        std::string is_override = "false";
        std::string is_final = "false";
        std::string is_friend = "false";

        // both
        std::string is_const = "false";

        // for constructor
        std::string is_explicit = "false";
        std::string is_delete = "false";

        std::string parent_type;
        std::string parent_name;

        std::vector<std::string> get_data() {
            std::vector<std::string> data;
            data.push_back(__type);
            data.push_back(name);
            data.push_back(qualified_name);
            data.push_back(access);
            data.push_back(_template);
            data.push_back(parameters);

            if (__type == "function"){
                data.push_back(return_type);
                data.push_back(is_static);
                data.push_back(is_virtual);
                data.push_back(is_override);
                data.push_back(is_final);
                data.push_back(is_friend);
                data.push_back(is_const);
            } else {
                data.push_back(is_const);
                data.push_back(is_explicit);
                data.push_back(is_delete);
            }
            data.push_back(parent_type);
            data.push_back(parent_name);
            return data;
        }
    };
}