#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>
#include <unistd.h>    // fork, exec
#include <sys/wait.h>  // wait
#include "utils/StringUtils.hpp"

namespace NewTCG {
    std::vector<std::string> find_all_code_files(const std::string project_path) {
        std::vector<std::string> files;
        for (const auto &entry : std::filesystem::recursive_directory_iterator(project_path)) {
            std::string fileName = entry.path().string();
            if (fileName.find("test") != std::string::npos || fileName.find("tests") != std::string::npos || fileName.find("build/") != std::string::npos \
                    || fileName.find("third_party") != std::string::npos || fileName.find("third-party") != std::string::npos || fileName.find("thirdparty") != std::string::npos \
                    || fileName.find("issues") != std::string::npos || fileName.find("fuzz") != std::string::npos || fileName.find("app") != std::string::npos \
                    || fileName.find("samples") != std::string::npos || fileName.find("contrib") != std::string::npos || fileName.find("unitTests") != std::string::npos \
                    || fileName.find("xmlsdk") != std::string::npos || fileName.find("scripts") != std::string::npos || fileName.find("qt6") != std::string::npos) {
                    continue;
                }
            if (utils::ends_with(fileName, ".cpp") || utils::ends_with(fileName, ".C") \
                || utils::ends_with(fileName, ".cxx") || utils::ends_with(fileName, ".cc") \
                || utils::ends_with(fileName, ".hpp") || utils::ends_with(fileName, ".h"))
                files.push_back(fileName);
        }
        return files;
    }

    int run_exe(const std::string file_path) {
        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "fork failed" << std::endl;
            return -1;
        }
        else if (pid == 0) { // child process
            std::vector<char*> exec_args;
            exec_args.push_back((char*)"./build/NewTraceDBModule.exe");
            exec_args.push_back(const_cast<char*>(file_path.c_str()));
            exec_args.push_back(nullptr);

            execvp(exec_args[0], exec_args.data());
            // exec 실패 시
            std::cerr << "exec 실행 실패!" << std::endl;
            exit(1);  // 자식 프로세스는 종료
        }
        else { // parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                // std::cout << "자식 정상 종료, 코드: " << WEXITSTATUS(status) << std::endl;
                return WEXITSTATUS(status);
            }
            else if (WIFSIGNALED(status)) {
                // std::cout << "자식이 시그널로 종료됨, 시그널: " << WTERMSIG(status) << std::endl;
                return -2;
            }
        }
        return 0;
    }
}

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

    std::vector<std::string> code_files = NewTCG::find_all_code_files(project_path);
    for (int i=0; i < code_files.size(); ++i ) {
        std::cout << i+1 << "/" << code_files.size() << std::endl;
        std::string file_path = code_files[i];
        
        // if (NewTCG::utils::ends_with(file_path, "/Escaper.cpp")) {

            std::cout << file_path << std::endl;
            int result = NewTCG::run_exe(file_path);
            if (result != 0) {
                std::cerr << file_path << ": execution failed. " << std::endl;
            }

        // } else {continue;}
    }
    return 0;
}
