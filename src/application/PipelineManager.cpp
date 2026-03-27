#include "PipelineManager.hpp"
#include "domain/configurator/factory/ConfigFactory.hpp"
#include "domain/code_analyzer/plugins/CodeAnalyzer.hpp"
#include "domain/dependency_tracer/plugins/DependencyTracer.hpp"
#include <memory>

namespace domain = NewTCG::domain;

namespace NewTCG {
	namespace application {
		void PipelineManager::setup(const std::string& project_path, const std::string& configuration_type, const std::string& setup_type) {
			domain::configurator::ConfigFactory factory;
			if (std::unique_ptr<IPipelineStep> step = factory.create(project_path, configuration_type)) {
				// unique_ptr은 복사가 불가능. 함수 호출시 무조건 복사를 시도함. 
				// add_step 내부의 std::move는 해당 함수의 step을 move하는 것. 지금의 step이랑은 별개의 것임. 
				add_step(std::move(step));
			}

			if (setup_type == "create_db") {
				if (std::unique_ptr<IPipelineStep> step = std::make_unique<domain::code_analyzer::CodeAnalyzer>()) {
					add_step(std::move(step));
				}
			}

			if (setup_type == "trace_db") {
				if (std::unique_ptr<IPipelineStep> step = std::make_unique<domain::dependency_tracer::DependencyTracer>()) {
					add_step(std::move(step));
				}	
			}
		}

		void PipelineManager::run() {
			for (const auto& step : steps) {
				step->execute();
			}
		}

		void PipelineManager::init() {
			steps.clear();
		}
	}
}