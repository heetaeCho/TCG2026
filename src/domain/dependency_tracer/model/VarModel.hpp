#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::dependency_tracer {
    class VarModel : public AbsModel {
        public:
        VarModel() {}
        VarModel(const AbsModel& base) {
            this->file_name = base.file_name;
            this->caller_qualified_name = base.caller_qualified_name;
            this->caller_parameters = base.caller_parameters;
            this->is_caller_constructor = base.is_caller_constructor;
        }

        public:
        std::string var_name;
        std::string var_type;

        std::map<std::string, std::string> get_data() override {
            std::map<std::string, std::string> data = AbsModel::get_data();
            data.insert(std::make_pair("var_name", var_name));
            data.insert(std::make_pair("var_type", var_type));
            return data;
        }
    };
}