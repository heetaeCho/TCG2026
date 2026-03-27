import os
import re
import subprocess

class Builder:
    def __init__(self, cwd, project_id, project):
        self.cwd = cwd
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.project_base = "TestProjects"
        self.real_project_base = os.path.join(self.cwd, self.project_base)
        self.real_project_path = os.path.join(self.cwd, self.real_project_base, self.project)
        self.project_build_options = {
            "poppler": ["-DENABLE_GPGME=OFF", "-DENABLE_QT6=OFF"],
            "re2": ["-DCMAKE_POLICY_VERSION_MINIMUM=3.5"],
            }

class ProjectBuilder(Builder):
    def __init__(self, cwd, project_id, project):
        super().__init__(cwd, int(project_id), project)
        self.cmake_lists = os.path.join(self.real_project_path, "CMakeLists.txt")

    def build(self, update=False):
        print(f"-"*50)
        print(f"Project {self.project} build start")
        command = [
            "-DCMAKE_C_COMPILER=/usr/lib/llvm-20/bin/clang",
            "-DCMAKE_CXX_COMPILER=/usr/lib/llvm-20/bin/clang++",
            "-DCMAKE_C_FLAGS=-fprofile-instr-generate -fcoverage-mapping",
            "-DCMAKE_CXX_FLAGS=-fprofile-instr-generate -fcoverage-mapping",
            "-DCMAKE_EXE_LINKER_FLAGS=-fprofile-instr-generate",
            "-DCMAKE_SHARED_LINKER_FLAGS=-fprofile-instr-generate"
        ]
        if self.project in self.project_build_options.keys():
            command.extend(self.project_build_options[self.project])
        cmake = "cmake" if self.project == "leveldb" else "/opt/cmake-4.2.0/bin/cmake" 

        subprocess.run([cmake, "-S", self.real_project_path, "-B", os.path.join(self.real_project_path,"build"),
                    *command], cwd=self.real_project_path)
        if not update:
            subprocess.run([cmake, "--build", os.path.join(self.real_project_path,"build")], cwd=self.real_project_path)
            # subprocess.run([cmake, "--graphviz", os.path.join(self.real_project_path,"deps.dot")], cwd=self.real_project_path)
                           
        print(f"Project {self.project} build complete")
        print(f"-"*50)

    def init_cmake_lists(self):
        with open(self.cmake_lists, 'r', encoding='utf-8') as f:
            lines = f.readlines()

        with open(self.cmake_lists, 'w', encoding='utf-8') as f:
            f.writelines(lines[:-1])

    def modify_cmake_lists(self):
        path = self.project_id + '_' + self.project
        with open(self.cmake_lists, 'a', encoding='utf-8') as cmake_list:
            cmake_list.write(f"add_subdirectory(../../experiments/{path}/build generated_build)")
            
if __name__ == "__main__":
    project_list = ["JsonBox", "re2", "leveldb", "Catch2", "glomap",
                    "ninja", "tinyxml2", "yaml-cpp", "exiv2", "poppler"]
    cwd = os.getcwd()
    for ix, project in enumerate(project_list):
        project_id = ix + 1
        pb = ProjectBuilder(cwd, project_id, project)
        pb.build()
