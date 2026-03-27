set(SOURCES
	plugins/DependencyTracer.cpp
	plugins/FrontendAction.cpp
	plugins/ASTConsumer.cpp
	plugins/Visitor.cpp
	plugins/Finders/FinderDispatcher.cpp
	plugins/Finders/FunctionCallFinder.cpp
	plugins/Finders/VarFinder.cpp
	plugins/Finders/EnumFinder.cpp
	plugins/Finders/CXXRecordFinder_new.cpp
	plugins/Finders/RecordFinder.cpp
)
set(HEADERS
	interface/IDependencyTracer.hpp
	plugins/AbsDependencyTracer.hpp
	plugins/DependencyTracer.hpp
	plugins/Finders/IFinder.hpp
)

add_library(DomainDependencyTracerLib ${SOURCES} ${HEADERS})
target_include_directories(DomainDependencyTracerLib 
	# 아래 헤더파일들을 이 Lib만 사용가능 : PRIVATE
	# 아래 헤더파일들을 이 Lib을 사용하는 Lib도 사용가능 : PUBLIC
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/model
	${CMAKE_CURRENT_SOURCE_DIR}/interface
	${CMAKE_CURRENT_SOURCE_DIR}/plugins
	${CMAKE_CURRENT_SOURCE_DIR}/plugins/Finders
)