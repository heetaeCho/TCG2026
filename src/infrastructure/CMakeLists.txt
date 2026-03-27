set(SOURCES
	DBImpl/AbsDBImpl.cpp
	DBImpl/DBFactory.cpp
	DBImpl/TopLevelQueries.cpp

	DBImpl/Controllers/IDBController.cpp
	
	DBImpl/Controllers/FileController.cpp
	DBImpl/Controllers/NamespaceController.cpp
	DBImpl/Controllers/CXXRecordController.cpp
	DBImpl/Controllers/EnumController.cpp
	DBImpl/Controllers/RecordController.cpp
	DBImpl/Controllers/FieldController.cpp
	DBImpl/Controllers/VariableController.cpp
	DBImpl/Controllers/ConstructorDeclarationController.cpp
	DBImpl/Controllers/ConstructorDefinitionController.cpp
	DBImpl/Controllers/FunctionDeclarationController.cpp
	DBImpl/Controllers/FunctionDefinitionController.cpp
	DBImpl/Controllers/TypedefController.cpp
	DBImpl/Controllers/NamespaceAliasController.cpp
	DBImpl/Controllers/TypeAliasController.cpp
	DBImpl/Controllers/FriendController.cpp
	DBImpl/Controllers/UsingDirectiveController.cpp
	DBImpl/Controllers/UsingController.cpp
	DBImpl/Controllers/MacroController.cpp

	DBImpl/Controllers/FunctionCallTraceController.cpp
	DBImpl/Controllers/VarTraceController.cpp
	DBImpl/Controllers/EnumTraceController.cpp
	DBImpl/Controllers/RecordTraceController.cpp
	DBImpl/Controllers/CXXRecordTraceController.cpp

	DBImpl/Controllers/HeaderTraceController.cpp
)
set(HEADERS
	DBImpl/AbsDBImpl.hpp
    DBImpl/DBFactory.hpp
    DBImpl/TopLevelQueries.hpp
	DBImpl/Controllers/IDBController.hpp
)

find_package(SQLite3 REQUIRED)

add_library(InfrastructureLib ${SOURCES} ${HEADERS})
target_include_directories(InfrastructureLib 
	# 아래 헤더파일들을 이 Lib만 사용가능 : PRIVATE
	# 아래 헤더파일들을 이 Lib을 사용하는 Lib도 사용가능 : PUBLIC
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/DBImpl
	${CMAKE_CURRENT_SOURCE_DIR}/DBImpl/Controllers
)


target_link_libraries(InfrastructureLib
	PRIVATE
	SQLite::SQLite3
)