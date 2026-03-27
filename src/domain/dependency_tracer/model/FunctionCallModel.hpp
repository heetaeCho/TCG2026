#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::dependency_tracer {
    class FunctionCallModel : public AbsModel {
        public:
        FunctionCallModel() {}
        FunctionCallModel(const AbsModel& base) {
            this->file_name = base.file_name;
            this->caller_qualified_name = base.caller_qualified_name;
            this->caller_parameters = base.caller_parameters;
            this->is_caller_constructor = base.is_caller_constructor;
        }

        public:
        bool is_callee_constructor = false;
        std::string callee_qualified_name;
        std::string callee_parameters; 

        std::map<std::string, std::string> get_data() override {
            std::map<std::string, std::string> data = AbsModel::get_data();
            data.insert(std::make_pair("is_callee_constructor", std::to_string(is_caller_constructor)));
            data.insert(std::make_pair("callee_qualified_name", callee_qualified_name));
            data.insert(std::make_pair("callee_parameters", callee_parameters));
            return data;
        }
    };
}