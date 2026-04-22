import os, sys
import subprocess
import argparse

class Builder:
    def __init__(self, llm, project_folder_name, project):
        self.llm = llm
        self.project_folder_name = project_folder_name
        self.project = project
        claude_path = "claude-proj"
        codex_path = "codex-proj"
        if self.llm == "claude" and os.path.exists(claude_path):
            self.base = claude_path
        elif self.llm == "codex" and os.path.exists(codex_path):
            self.base = codex_path
        else:
            raise

        self.cwd = os.path.dirname(os.path.abspath(__file__))
        self.project_base_path = os.path.join(self.base, self.project_folder_name)
        self.real_project_path = os.path.join(self.project_base_path, self.project)

        self.include_base = os.path.join(self.cwd, self.real_project_path)

        self.repair_path = os.path.join(self.project_base_path, "repair")
        os.makedirs(self.repair_path, exist_ok=True)
        self.test_path = os.path.join(self.project_base_path, "test_files")
        self.build_path = os.path.join(self.repair_path, "build")

        self.config()

    def config(self):
        self.project_build_options = {
            "poppler": ["-DENABLE_GPGME=OFF", "-DENABLE_QT6=OFF"],
            "re2": ["-DCMAKE_POLICY_VERSION_MINIMUM=3.5"],
            "glomap": ["-DOpenMP_C_FLAGS=-fopenmp", 
                        "-DOpenMP_CXX_FLAGS=-fopenmp", 
                        "-DOpenMP_C_LIB_NAMES=omp",
                        "-DOpenMP_CXX_LIB_NAMES=omp",
                        "-DOpenMP_omp_LIBRARY=/usr/lib/llvm-20/lib/libomp.so"]
            }

class ProjectBuilder(Builder):
    def __init__(self, llm, project_folder_name, project):
        super().__init__(llm, project_folder_name, project)
        self.cmake_lists = os.path.join(self.real_project_path, "CMakeLists.txt")
    
    def build(self, rebuild = False):
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
                    *command], cwd=self.cwd)
        if not rebuild:
            subprocess.run([cmake, "--build", os.path.join(self.real_project_path,"build")], cwd=self.cwd)

    def init_cmake_lists(self):
        with open(self.cmake_lists, 'r', encoding='utf-8') as f:
            lines = f.readlines()

        with open(self.cmake_lists, 'w', encoding='utf-8') as f:
            f.writelines(lines[:-1])

    def modify_cmake_lists(self):
        with open(self.cmake_lists, 'a', encoding='utf-8') as cmake_list:
            cmake_list.write(f"add_subdirectory({os.path.join(self.cwd, self.build_path)} generated_build)")


class TestBuilder(Builder):
    cmake_template = \
    """
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_C_COMPILER /usr/lib/llvm-20/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/lib/llvm-20/bin/clang++)
    """

    cmake_template_poppler = \
    """
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_C_COMPILER /usr/lib/llvm-20/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/lib/llvm-20/bin/clang++)
    """

    def __init__(self, llm, project_folder_name, project):
        super().__init__(llm, project_folder_name, project)
        self.project_includes = {
            "JsonBox": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'include'),
                os.path.join(self.include_base, 'include/JsonBox')
            ],
            "re2": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 're2'),
                os.path.join(self.include_base, 'util'),
            ],
            "leveldb": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build/include'),
                os.path.join(self.include_base, 'include'),
                os.path.join(self.include_base, 'include/leveldb'),
                os.path.join(self.include_base, 'db'),
                os.path.join(self.include_base, 'helpers'),
                os.path.join(self.include_base, 'helpers/memenv'),
                os.path.join(self.include_base, 'port'),
                os.path.join(self.include_base, 'table'),
                os.path.join(self.include_base, 'util'),
            ],
            "Catch2": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'build/generated-includes/catch2'),
                os.path.join(self.include_base, 'src'),
                os.path.join(self.include_base, 'src/catch2'),
                os.path.join(self.include_base, 'src/catch2/reporters'),
                os.path.join(self.include_base, 'src/catch2/matchers'),
                os.path.join(self.include_base, 'src/catch2/generators'),
                os.path.join(self.include_base, 'src/catch2/interfaces'),
                os.path.join(self.include_base, 'src/catch2/internal'),
                os.path.join(self.include_base, 'src/catch2/benchmark'),
            ],
            "glomap": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'glomap'),
                os.path.join(self.include_base, 'glomap/controllers'),
                os.path.join(self.include_base, 'glomap/estimators'),
                os.path.join(self.include_base, 'glomap/exe'),
                os.path.join(self.include_base, 'glomap/io'),
                os.path.join(self.include_base, 'glomap/math'),
                os.path.join(self.include_base, 'glomap/processors'),
                os.path.join(self.include_base, 'glomap/scene'),
            ],
            "ninja": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'src'),
            ],
            "tinyxml2": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
            ],
            "yaml-cpp": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'include'),
                os.path.join(self.include_base, 'include/yaml-cpp'),
                os.path.join(self.include_base, 'include/yaml-cpp/contrib'),
                os.path.join(self.include_base, 'include/yaml-cpp/node'),
                os.path.join(self.include_base, 'include/yaml-cpp/node/detail'),
                os.path.join(self.include_base, 'src'),
                os.path.join(self.include_base, 'src/contrib'),
            ],
            "exiv2": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'app'),
                os.path.join(self.include_base, 'include'),
                os.path.join(self.include_base, 'include/exiv2'),
                os.path.join(self.include_base, 'src'),
            ],
            "poppler": [
                os.path.join(self.include_base, self.project_base_path),
                self.include_base,
                os.path.join(self.include_base, 'build'),
                os.path.join(self.include_base, 'cpp'),
                os.path.join(self.include_base, 'fofi'),
                os.path.join(self.include_base, 'glib'),
                os.path.join(self.include_base, 'goo'),
                os.path.join(self.include_base, 'poppler'),
                os.path.join(self.include_base, 'qt5'),
                os.path.join(self.include_base, 'qt5/src'),
                os.path.join(self.include_base, 'qt6'),
                os.path.join(self.include_base, 'qt6/src'),
                os.path.join(self.include_base, 'splash'),
                os.path.join(self.include_base, 'utils'),
            ],
        }
        self.project_depenendy = {
            "JsonBox": ['JsonBox'],
            "re2": ['re2'],
            "leveldb": ['leveldb'],
            "Catch2": ['Catch2'],
            "glomap": ['glomap'],
            "ninja": ['libninja-re2c', 'libninja'],
            "tinyxml2": ['tinyxml2::tinyxml2'],
            "yaml-cpp": ['yaml-cpp::yaml-cpp'],
            "exiv2": ['Exiv2::exiv2lib', 'exiv2lib', 'exiv2lib_int', 'exiv2-xmp', 'expat'],
            "poppler": ['poppler', '${poppler_LIBS}']
        }

    def rebuild(self, test_file):
        if self.project != "poppler":
            libs = list(self._parse_cmakelist())
            self.project_depenendy[self.project].extend(libs)
            self.project_depenendy[self.project] = list(set(self.project_depenendy[self.project]))
        test_files = [test_file]
        cmake_lists = self.__make_cmake_lists(test_files)
        with open(os.path.join(self.build_path, "CMakeLists.txt"), 'w') as f:
            f.write(cmake_lists)
        return self.__rebuild(test_files)

    def __rebuild(self, test_files):
        is_pass = False
        result = None
        try:
            pb = ProjectBuilder(self.llm, self.project_folder_name, self.project)
            pb.modify_cmake_lists()
            pb.build(rebuild=True)
            for test_file in test_files:
                test_name = os.path.splitext(test_file)[0]
                try:
                    result = subprocess.run(["/opt/cmake-4.2.0/bin/cmake", "--build", \
                        os.path.join(self.real_project_path,"build"), "--target", test_name], capture_output=True, cwd=self.cwd, check=True)
                    print(f"[BUILD PASS] : {test_name}")
                    is_pass = True
                except subprocess.CalledProcessError as e:
                    print(f"[BUILD FAIL] : {test_name}")
                    is_pass = False
                    result = e
        except:
            pass
        finally:
            pb.init_cmake_lists()
            return is_pass, result

    def __make_cmake_lists(self, test_files):
        cmake_list = self.cmake_template if self.project != "poppler" else self.cmake_template_poppler
        for test_file in test_files:
            test_name = os.path.splitext(test_file)[0]
            test_build_dir = os.path.join(self.build_path, test_name)
            os.makedirs(test_build_dir, exist_ok=True)

            tlp_per_file = \
            """
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${{CMAKE_CURRENT_SOURCE_DIR}}/{test_name} CACHE PATH "" FORCE)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${{CMAKE_CURRENT_SOURCE_DIR}}/{test_name} CACHE PATH "" FORCE)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${{CMAKE_CURRENT_SOURCE_DIR}}/{test_name} CACHE PATH "" FORCE)
            
            add_executable({test_name} {test_file})
            target_include_directories({test_name} PRIVATE {includes})
            target_link_libraries({test_name} PRIVATE {libraries})

            target_compile_options({test_name} PRIVATE -fprofile-instr-generate -fcoverage-mapping -fcoverage-mcdc -O0 -g)
            target_link_options({test_name} PRIVATE -fprofile-instr-generate -fcoverage-mapping -fcoverage-mcdc )
            set_target_properties({test_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${{CMAKE_CURRENT_SOURCE_DIR}}/{test_name}
            )
            """
            content = tlp_per_file.format(
                test_name = test_name,
                test_file = os.path.join(self.cwd, self.test_path, test_file),
                includes = ' '.join(self.project_includes[self.project]),
                libraries = 'gmock gtest gtest_main ' + ' '.join(self.project_depenendy[self.project])
            )
            cmake_list = cmake_list + content
        return cmake_list
    

    def _parse_cmakelist(self):
        def collect_options():
            options = {}
            for root, dirs, files in os.walk(self.real_project_path):
                for file in files:
                    if file == "CMakeLists.txt":
                        with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                            for line in f.readlines():
                                line = line.strip()
                                if line.startswith("option("):
                                    tokens = line.split()
                                    name = tokens[0].replace("option(", '')
                                    value = tokens[-1].replace(')', '')
                                    if value in ("ON", "OFF"):
                                        options[name] = value
            return options
        
        def collect_libraries(options):
            SKIP_TOKENS = [
                "PUBLIC", "PRIVATE", "INTERFACE", "gtest", "gmock", "gtest_main", "gmock_main", "LINK_PRIVATE",
            ]
            SKIP_DIRS = {"test", "tests", "benchmark", "benchmarks", "example", "examples", "build", "third-party", "third_party", "thirdparty", "issues", "fuzz", "fuzzing", "app", "contrib", "sample", "samples", "unitTests", "xmlsdk", "scripts"}
            libs = set()
            for root, dirs, files in os.walk(self.real_project_path):
                dirs[:] = [d for d in dirs if d not in SKIP_DIRS]
                for file in files:
                    if file == "CMakeLists.txt":
                        with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                            lines = f.readlines()
                        
                        variables = {}
                        for line in lines:
                            line = line.strip()
                            if line.startswith('set('):
                                tokens = line.split()
                                name = tokens[0].replace('set(', '')
                                value = tokens[-1].replace(')', '')
                                variables[name] = value

                        in_if = False
                        if_condition = True
                        for line in lines:
                            line = line.strip()
                            if line.startswith('if('):
                                condition = line.replace('if(', '').replace(')', '')
                                if_condition = options.get(condition, "OFF") == 'ON'
                                in_if = True
                            elif line.startswith('endif()'):
                                in_if = False
                                if_condition = True
                            elif line.startswith('target_link_libraries('):
                                if in_if and not if_condition:
                                    continue
                                tokens = line.split()
                                for t in tokens[1:]:
                                    t = t.replace(')', '')
                                    if t in SKIP_TOKENS:
                                        continue
                                    elif t.startswith("GTest::") or t.startswith('-') or t.startswith('Qt6::'):
                                        continue
                                    elif 'benchmark' in t or 'test' in t or '"' in t or '(' in t:
                                        continue
                                    if t.startswith("${"):
                                        t = variables.get(t[2:-1], t)
                                        if 'benchmark' in t or 'test' in t or '"' in t or '(' in t:
                                            continue
                                    libs.add(t)
            return libs
        
        options = collect_options()
        libs = collect_libraries(options)
        return libs

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--LLM")
    parser.add_argument("--project_folder_name")
    parser.add_argument("--project")
    parser.add_argument("--test_file")
    parser.add_argument("--retry", type=int, default=0)
    args = parser.parse_args()

    base = "claude-proj" if args.LLM == "claude" else "codex-proj"
    test_name = os.path.splitext(args.test_file)[0]
    log_dir = f"./{base}/{args.project_folder_name}/results/logs"
    os.makedirs(log_dir, exist_ok=True)

    pb = ProjectBuilder(args.LLM, args.project_folder_name, args.project)
    pb.build()
    tb = TestBuilder(args.LLM, args.project_folder_name, args.project)
    is_pass, result = tb.rebuild(args.test_file)

    if not is_pass:
        with open(f"{log_dir}/{test_name}_compile_retry#{args.retry}.txt", "w") as f:
            f.write(result.stdout.decode() if result.stdout else "")
            f.write(result.stderr.decode() if result.stderr else "")
        sys.exit(1)

    sys.exit(0)