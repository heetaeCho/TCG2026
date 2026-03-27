#pragma once

#include "AbsModel.hpp"

namespace NewTCG::domain::dependency_tracer {
    class CXXRecordModel : public AbsModel {
        public:
        CXXRecordModel() {}
        CXXRecordModel(const AbsModel& base) {
            this->file_name = base.file_name;
            this->caller_qualified_name = base.caller_qualified_name;
            this->caller_parameters = base.caller_parameters;
            this->is_caller_constructor = base.is_caller_constructor;
        }

        public:
        std::string cxxrecord_qualified_name;
        std::string cxxrecord_type;

        std::map<std::string, std::string> get_data() override {
            std::map<std::string, std::string> data = AbsModel::get_data();
            data.insert(std::make_pair("cxxrecord_qualified_name", cxxrecord_qualified_name));
            data.insert(std::make_pair("cxxrecord_type", cxxrecord_type));
            return data;
        }
    };
}