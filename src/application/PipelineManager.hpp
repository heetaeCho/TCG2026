#pragma once

#include "IPipelineStep.hpp"
#include <vector>
#include <string>
#include <memory>

namespace NewTCG {
	namespace application {
		class PipelineManager {
			private:
			std::vector<std::unique_ptr<IPipelineStep>> steps;
			void add_step(std::unique_ptr<IPipelineStep> step) {
				// 어렵다.
				// unique_ptr은 복사할 수 없고 "소유권 이전 (move)"만 가능함.
				steps.push_back(std::move(step));
			}
			public:
			void setup(const std::string& project_path, const std::string& configuration_type, const std::string& setup_type);
			void run();
			void init();
		};
	}
}
