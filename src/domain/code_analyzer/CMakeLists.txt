set_source_files_properties(plugins/CodeAnalyzer.cpp PROPERTIES COMPILE_FLAGS "-fno-rtti")
set_source_files_properties(plugins/FrontendAction.cpp PROPERTIES COMPILE_FLAGS "-fno-rtti")
set_source_files_properties(plugins/ASTConsumer.cpp PROPERTIES COMPILE_FLAGS "-fno-rtti")

set(SOURCES
	plugins/CodeAnalyzer.cpp
	plugins/FrontendAction.cpp
	plugins/ASTConsumer.cpp
	plugins/Visitor.cpp
	plugins/handlers/NamespaceHandler.cpp
	plugins/handlers/CXXRecordHandler.cpp
	plugins/handlers/EnumHandler.cpp
	plugins/handlers/RecordHandler.cpp
	plugins/handlers/FieldHandler.cpp
	plugins/handlers/FriendHandler.cpp
	plugins/handlers/FunctionHandler.cpp
	plugins/handlers/VariableHandler.cpp
)

set(HEADERS
	interface/ICodeAnalyzer.hpp
	plugins/AbsCodeAnalyzer.hpp
	plugins/CodeAnalyzer.hpp
	plugins/FrontendAction.hpp
	plugins/ASTConsumer.hpp
	plugins/Visitor.hpp
	model/BasicModel.hpp
	model/AbsModel.hpp
)

add_library(DomainCodeAnalyzerLib ${SOURCES} ${HEADERS})
target_include_directories(DomainCodeAnalyzerLib 
	# 아래 헤더파일들을 이 Lib만 사용가능 : PRIVATE
	# 아래 헤더파일들을 이 Lib을 사용하는 Lib도 사용가능 : PUBLIC
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/interface
	${CMAKE_CURRENT_SOURCE_DIR}/model
	${CMAKE_CURRENT_SOURCE_DIR}/plugins
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/handlers
)

target_link_libraries(DomainCodeAnalyzerLib
	PRIVATE
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
	InfrastructureLib
)
