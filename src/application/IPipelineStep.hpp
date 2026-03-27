#pragma once

#include <string>

namespace NewTCG {
	namespace application {
		class IPipelineStep {
			public:
			std::string name;
			virtual bool execute() = 0;
			virtual ~IPipelineStep() = default;
		};
	}
}
