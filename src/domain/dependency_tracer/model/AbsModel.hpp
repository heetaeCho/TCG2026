#pragma once

#include <string>
#include <map>

namespace NewTCG::domain::dependency_tracer {
    class AbsModel {
        public:
        std::string file_name;
        bool is_caller_constructor = false;
        std::string caller_qualified_name;
        std::string caller_parameters; 

        virtual ~AbsModel() = default;
        virtual std::map<std::string, std::string> get_data() {
            std::map<std::string, std::string> data = {
                {"file_name", file_name},
                {"is_caller_constructor", std::to_string(is_caller_constructor)},
                {"caller_qualified_name", caller_qualified_name},
                {"caller_parameters", caller_parameters},
            };
            return data;
        }
    };
}