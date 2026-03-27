cmake_minimum_required(VERSION 3.20)
project(TCG)

# C++17 표준 사용 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# temp - for debug
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
# add_link_options(-fprofile-instr-generate)

# Clang 컴파일러 설정
# if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
# set(CMAKE_C_COMPILER /usr/local/Cellar/llvm/19.1.4/bin/clang)
# set(CMAKE_CXX_COMPILER /usr/local/Cellar/llvm/19.1.4/bin/clang++)
# else()
set(CMAKE_C_COMPILER /usr/lib/llvm-18/bin/clang)
set(CMAKE_CXX_COMPILER /usr/lib/llvm-18/bin/clang++)
# endif()

# LLVM과 Clang 찾기
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# 실행 파일 설정 및 라이브러리 링크
include_directories(include src ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS} ${CLANG_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(src)

add_executable(JsonConfig.exe src/application/main_json_config.cpp)
# add_executable(CreateDB.exe src/application/main_create_db.cpp)
# add_executable(TraceDB.exe src/application/main_trace_db.cpp)

add_executable(NewCreateDB.exe src/application/main_new_create_db.cpp)
add_executable(NewCreateDBModule.exe src/domain/code_analyzer/plugins/CodeAnalyzer_main.cpp)

add_executable(NewTraceDB.exe src/application/main_new_trace_db.cpp)
add_executable(NewTraceDBModule.exe src/domain/dependency_tracer/plugins/DependencyTracer_main.cpp)


target_link_libraries(JsonConfig.exe 
	PUBLIC
	ApplicationLib
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)

# target_link_libraries(CreateDB.exe 
# 	PUBLIC
# 	ApplicationLib
# 	DomainConfiguratorLib
# 	DomainCodeAnalyzerLib
# 	DomainDependencyTracerLib
# )

# target_link_libraries(TraceDB.exe 
# 	PUBLIC
# 	ApplicationLib
# 	DomainConfiguratorLib
# 	DomainCodeAnalyzerLib
# 	DomainDependencyTracerLib
# )

target_link_libraries(NewCreateDB.exe 
	PUBLIC
	ApplicationLib
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)

target_link_libraries(NewCreateDBModule.exe 
	PUBLIC
	ApplicationLib
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)

target_link_libraries(NewTraceDB.exe 
	PUBLIC
	ApplicationLib
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)

target_link_libraries(NewTraceDBModule.exe 
	PUBLIC
	ApplicationLib
	DomainConfiguratorLib
	DomainCodeAnalyzerLib
	DomainDependencyTracerLib
)
