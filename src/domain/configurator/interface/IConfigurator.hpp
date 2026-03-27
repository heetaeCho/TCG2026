#pragma once

#include "ConfigModel.hpp"
#include "application/IPipelineStep.hpp"

namespace NewTCG::domain::configurator {
    class IConfigurator : public NewTCG::application::IPipelineStep {
    protected:
    ConfigModel& config = ConfigModel::get_instance();
    
    virtual void project_configuration() = 0;
    virtual std::vector<std::string> find_include_dirs() = 0;
    virtual std::vector<std::string> make_args() = 0;

    public:
    virtual bool execute() override = 0;
    virtual ~IConfigurator() = default;
    };
}