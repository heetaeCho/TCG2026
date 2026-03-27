#include "PipelineManager.hpp"
#include <iostream>

/*
지금처럼 다 구현하고,
main.cpp를 상황에 맞게 여러게 만들어서
executable로 만들면 된대.
*/

namespace application = NewTCG::application;

int main(int argc, char** argv) {
	// std::cout << "argc" << argc << std::endl;
	// std::cout << "argv[0]" << argv[0] << std::endl;
    // std::string project_path = argv[1];
    // std::string project_path = "./TestProjects/leveldb";
    // std::string project_path = "./TestProjects/JsonBox";
    std::string project_path = "./TestProjects/JsonBox";
    if (argc > 1) {
        std::string project_name = argv[1];
        project_path = "./TestProjects/" + project_name;
    }
	application::PipelineManager manager;
	manager.setup(project_path, "json", "");
	manager.run();
}
