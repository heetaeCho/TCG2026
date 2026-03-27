#pragma once

#include "domain/code_analyzer/model/AbsModel.hpp"
#include "domain/dependency_tracer/model/AbsModel.hpp"

namespace entity_model = NewTCG::domain::code_analyzer;
namespace trace_model = NewTCG::domain::dependency_tracer;

namespace NewTCG::adapter {
    class IDBAdapter {
        public:
        virtual ~IDBAdapter() = default;
        virtual int add_to_db(const std::string& type, entity_model::AbsModel& model) = 0;
        virtual int add_to_db(const std::string& type, trace_model::AbsModel& model) = 0;
    };
}