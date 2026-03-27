#pragma once

#include "AbsModel.hpp"
#include <vector>
#include <sstream>

namespace NewTCG::domain::dependency_tracer {
    class HeaderModel : public AbsModel {
        public:
        HeaderModel() {}
        HeaderModel(const AbsModel& base) {
            this->file_name = base.file_name;
        }

        public:
        std::vector<std::string> headers;

        std::map<std::string, std::string> get_data() override {
            std::map<std::string, std::string> data = AbsModel::get_data();
            std::ostringstream oss;
            for (size_t i = 0; i < headers.size(); ++i) {
                if (i != 0) oss << ", ";  // 구분자
                oss << headers[i];
            }
            data["headers"] = oss.str();
            return data;
        }
    };
}