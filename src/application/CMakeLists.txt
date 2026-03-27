set(SOURCES
	PipelineManager.cpp
)

set(HEADERS 
	IPipelineStep.hpp
	PipelineManager.hpp
)

add_library(ApplicationLib ${SOURCES} ${HEADERS})
target_include_directories(ApplicationLib 
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ApplicationLib
	PRIVATE
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)