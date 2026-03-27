#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::dependency_tracer {
    class EnumModel : public AbsModel {
        public:
        EnumModel() {}
        EnumModel(const AbsModel& base) {
            this->file_name = base.file_name;
            this->caller_qualified_name = base.caller_qualified_name;
            this->caller_parameters = base.caller_parameters;
            this->is_caller_constructor = base.is_caller_constructor;
        }

        public:
        std::string enum_qualified_name;
        std::string enum_type;

        std::map<std::string, std::string> get_data() override {
            std::map<std::string, std::string> data = AbsModel::get_data();
            data.insert(std::make_pair("enum_qualified_name", enum_qualified_name));
            data.insert(std::make_pair("enum_type", enum_type));
            return data;
        }
    };
}