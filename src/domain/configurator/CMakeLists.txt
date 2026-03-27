set(SOURCES
	plugins/ModelConfigurator.cpp
	plugins/JsonConfigurator.cpp
)
set(HEADERS
	factory/ConfigFactory.hpp
	interface/IConfigurator.hpp
	model/ConfigModel.hpp
	plugins/AbsConfigurator.hpp
	plugins/ModelConfigurator.hpp
)

add_library(DomainConfiguratorLib ${SOURCES} ${HEADERS})
target_include_directories(DomainConfiguratorLib 
	# 아래 헤더파일들을 이 Lib만 사용가능 : PRIVATE
	# 아래 헤더파일들을 이 Lib을 사용하는 Lib도 사용가능 : PUBLIC
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/factory
	${CMAKE_CURRENT_SOURCE_DIR}/interface
	${CMAKE_CURRENT_SOURCE_DIR}/model
	${CMAKE_CURRENT_SOURCE_DIR}/plugins
)

target_link_libraries(DomainConfiguratorLib
	PRIVATE
	ApplicationLib
)
# add_library(DomainConfiguratorLib INTERFACE)
# target_include_directories(DomainConfiguratorLib
# 	INTERFACE
# 	${CMAKE_CURRENT_SOURCE_DIR}/factory
# 	${CMAKE_CURRENT_SOURCE_DIR}/interface
# 	${CMAKE_CURRENT_SOURCE_DIR}/model
# 	${CMAKE_CURRENT_SOURCE_DIR}/plugins
# )

