import os
import re
import subprocess

class Builder:
    def __init__(self, cwd, project_id, project, llm):
        self.cwd = cwd
        self.llm = llm
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
    def __init__(self, cwd, project_id, project, llm):
        super().__init__(cwd, int(project_id), project, llm)
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
            cmake_list.write(f"add_subdirectory(../../experiments/LLM/{self.llm}/{path}/build generated_build)")

class TestBuilder(Builder):
    cmake_template = \
    """
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_C_COMPILER /usr/lib/llvm-20/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/lib/llvm-20/bin/clang++)
    """

    def __init__(self, cwd, project_id, project, llm):
        super().__init__(cwd, int(project_id), project, llm)
        self.project_path = os.path.join("experiments", f"LLM/{self.llm}", self.project_id + '_' + self.project)
        self.TEST_FILES_PATH = os.path.join(self.project_path, "test_files")
        self.BUILD_DIR = os.path.join(self.project_path, "build")
        self.LOG_DIR = os.path.join(self.project_path, "log")
        self.BUILD_LOG_DIR = os.path.join(self.LOG_DIR, "build_log")
        self.RUN_LOG_DIR = os.path.join(self.LOG_DIR, "run_log")
        self.PASS_DIR = os.path.join(self.project_path, "pass")
        self.BUILD_PASS_DIR = os.path.join(self.PASS_DIR, "build_pass")
        self.RUN_PASS_DIR = os.path.join(self.PASS_DIR, "run_pass")
        self.FAIL_DIR = os.path.join(self.project_path, "fail")
        self.BUILD_FAIL_DIR = os.path.join(self.FAIL_DIR, "build_fail")
        self.RUN_FAIL_DIR = os.path.join(self.FAIL_DIR, "run_fail")
        self.DIRS = [self.BUILD_DIR, self.LOG_DIR, self.BUILD_LOG_DIR, self.RUN_LOG_DIR, 
                self.PASS_DIR, self.BUILD_PASS_DIR, self.RUN_PASS_DIR, 
                self.FAIL_DIR, self.BUILD_FAIL_DIR, self.RUN_FAIL_DIR]

    def build(self):
        # print(os.getcwd())
        ## Project별 test 파일 위치 및 빌드/실행 준비
        for d in self.DIRS:
            os.makedirs(d, exist_ok=True)

        self.project_includes = {
            "JsonBox": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'include'),
                os.path.join(self.real_project_path, 'include/JsonBox')
            ],
            "re2": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 're2'),
                os.path.join(self.real_project_path, 'util'),
            ],
            "leveldb": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build/include'),
                os.path.join(self.real_project_path, 'include'),
                os.path.join(self.real_project_path, 'include/leveldb'),
                os.path.join(self.real_project_path, 'db'),
                os.path.join(self.real_project_path, 'helpers'),
                os.path.join(self.real_project_path, 'helpers/memenv'),
                os.path.join(self.real_project_path, 'port'),
                os.path.join(self.real_project_path, 'table'),
                os.path.join(self.real_project_path, 'util'),
            ],
            "Catch2": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'build/generated-includes/catch2'),
                os.path.join(self.real_project_path, 'src'),
                os.path.join(self.real_project_path, 'src/catch2'),
                os.path.join(self.real_project_path, 'src/catch2/reporters'),
                os.path.join(self.real_project_path, 'src/catch2/matchers'),
                os.path.join(self.real_project_path, 'src/catch2/generators'),
                os.path.join(self.real_project_path, 'src/catch2/interfaces'),
                os.path.join(self.real_project_path, 'src/catch2/internal'),
                os.path.join(self.real_project_path, 'src/catch2/benchmark'),
            ],
            "glomap": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'glomap'),
                os.path.join(self.real_project_path, 'glomap/controllers'),
                os.path.join(self.real_project_path, 'glomap/estimators'),
                os.path.join(self.real_project_path, 'glomap/exe'),
                os.path.join(self.real_project_path, 'glomap/io'),
                os.path.join(self.real_project_path, 'glomap/math'),
                os.path.join(self.real_project_path, 'glomap/processors'),
                os.path.join(self.real_project_path, 'glomap/scene'),
            ],
            "ninja": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'src'),
            ],
            "tinyxml2": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
            ],
            "yaml-cpp": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'include'),
                os.path.join(self.real_project_path, 'include/yaml-cpp'),
                os.path.join(self.real_project_path, 'include/yaml-cpp/contrib'),
                os.path.join(self.real_project_path, 'include/yaml-cpp/node'),
                os.path.join(self.real_project_path, 'include/yaml-cpp/node/detail'),
                os.path.join(self.real_project_path, 'src'),
                os.path.join(self.real_project_path, 'src/contrib'),
            ],
            "exiv2": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'app'),
                os.path.join(self.real_project_path, 'include'),
                os.path.join(self.real_project_path, 'include/exiv2'),
                os.path.join(self.real_project_path, 'src'),
            ],
            "poppler": [
                self.cwd,
                self.real_project_base,
                self.real_project_path,
                os.path.join(self.real_project_path, 'build'),
                os.path.join(self.real_project_path, 'cpp'),
                os.path.join(self.real_project_path, 'fofi'),
                os.path.join(self.real_project_path, 'glib'),
                os.path.join(self.real_project_path, 'goo'),
                os.path.join(self.real_project_path, 'poppler'),
                os.path.join(self.real_project_path, 'qt5'),
                os.path.join(self.real_project_path, 'qt5/src'),
                os.path.join(self.real_project_path, 'qt6'),
                os.path.join(self.real_project_path, 'qt6/src'),
                os.path.join(self.real_project_path, 'splash'),
                os.path.join(self.real_project_path, 'utils'),
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

        # self._parse_graphviz()
        if self.project != "poppler":
            libs = list(self._parse_cmakelist())
            self.project_depenendy[self.project].extend(libs)
            self.project_depenendy[self.project] = list(set(self.project_depenendy[self.project]))
        ## 테스트 빌드
        test_files = os.listdir(self.TEST_FILES_PATH)
        cmake_lists = self.__make_cmake_lists(test_files)
        with open(os.path.join(self.BUILD_DIR, "CMakeLists.txt"), 'w') as f:
            f.write(cmake_lists)
        self.__rebuild(test_files)
    
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

    def _parse_graphviz(self):
        libs = set()
        with open(os.path.join(self.real_project_path,"deps.dot"), 'r', encoding='utf-8') as f:
            for line in f.readlines():
                if '->' in line and "//" in line:
                    # print(line)
                    line = line.split("//")[-1].strip()
                    left, right = line.split('->')
                    left = left.strip()
                    right = right.strip()
                    if not left.startswith('-'):
                        libs.add(left.strip())
                    if not right.startswith('-'):
                        libs.add(right.strip())
            libs = list(libs)
            self.project_depenendy[self.project].extend(libs)
            self.project_depenendy[self.project] = list(set(self.project_depenendy[self.project]))

    def __make_cmake_lists(self, test_files):
        cmake_list = self.cmake_template
        for test_file in test_files:
            test_name = os.path.splitext(test_file)[0]
            test_build_dir = os.path.join(self.BUILD_DIR, test_name)
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
                test_file = "../test_files/"+test_file,
                includes = ' '.join(self.project_includes[self.project]),
                libraries = 'gmock gtest gtest_main ' + ' '.join(self.project_depenendy[self.project])
            )
            cmake_list = cmake_list + content
        return cmake_list
        
    def __rebuild(self, test_files):
        import shutil
        try:
            pb = ProjectBuilder(self.cwd, int(self.project_id), self.project, self.llm)
            pb.modify_cmake_lists()
            pb.build(update=True)
            for test_file in test_files:
                test_name = os.path.splitext(test_file)[0]
                build_log_path = os.path.join(self.BUILD_LOG_DIR, f"{test_name}.log")
                with open(build_log_path, 'w', encoding='utf-8') as log:
                    try:
                        subprocess.run(["/opt/cmake-4.2.0/bin/cmake", "--build", os.path.join(self.real_project_path,"build"), "--target", test_name],
                                       cwd=self.real_project_path, check=True, stdout=log, stderr=log)
                        shutil.copy(os.path.join(self.TEST_FILES_PATH, test_name+".cpp"), os.path.join(self.BUILD_PASS_DIR, test_name+".cpp"))
                        print(f"[BUILD PASS] : {test_name}")
                    except subprocess.CalledProcessError:
                        shutil.copy(os.path.join(self.TEST_FILES_PATH, test_name+".cpp"), os.path.join(self.BUILD_FAIL_DIR, test_name+".cpp"))
                        print(f"[BUILD FAIL] : {test_name}")
        except:
            pass
        finally:
            pb.init_cmake_lists()

    def execute(self):
        import shutil
        build_successed = [file.split(".cpp")[0] for file in os.listdir(self.BUILD_PASS_DIR)]
        for build_success in build_successed:
            test_name = build_success
            run_log_pass = os.path.join(self.RUN_LOG_DIR, f"{test_name}.log")
            test_build_dir = os.path.join(self.BUILD_DIR, test_name)
            with open(run_log_pass, 'w', encoding='utf-8') as log:
                exe_path = os.path.join(test_build_dir, test_name)
                try:
                    result = subprocess.run(f"./{test_name}", timeout=10, cwd=test_build_dir)
                    result = subprocess.run([exe_path], timeout=10, stdout=log, stderr=log)
                except subprocess.TimeoutExpired as e:
                    shutil.copy(os.path.join(self.TEST_FILES_PATH, test_name+".cpp"), os.path.join(self.RUN_FAIL_DIR, test_name+".cpp"))
                    print(f"[RUN FAIL] : {test_name}")
                    if os.path.exists(os.path.join(test_build_dir, "default.profraw")):
                        os.remove(os.path.join(test_build_dir, "default.profraw"))
                    
                if result.returncode >= 0:
                    shutil.copy(os.path.join(self.TEST_FILES_PATH, test_name+".cpp"), os.path.join(self.RUN_PASS_DIR, test_name+".cpp"))
                    print(f"[RUN PASS] : {test_name}")
                else:
                    shutil.copy(os.path.join(self.TEST_FILES_PATH, test_name+".cpp"), os.path.join(self.RUN_FAIL_DIR, test_name+".cpp"))
                    print(f"[RUN FAIL] : {test_name}")
                    if os.path.exists(os.path.join(test_build_dir, "default.profraw")):
                        os.remove(os.path.join(test_build_dir, "default.profraw"))
