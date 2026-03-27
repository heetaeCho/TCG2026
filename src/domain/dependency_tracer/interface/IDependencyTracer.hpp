#pragma once

#pragma once

#include "application/IPipelineStep.hpp"
#include "domain/configurator/model/ConfigModel.hpp"
#include <vector>

namespace configurator = NewTCG::domain::configurator;

namespace NewTCG::domain::dependency_tracer {
    class IDependencyTracer : public NewTCG::application::IPipelineStep {
    protected:
    configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
    virtual std::vector<std::string> find_all_code_files() = 0;
    virtual std::string read_file(const std::string& file_path) = 0;

    public:
    virtual ~IDependencyTracer() = default;
    virtual bool execute() = 0;
    };
}