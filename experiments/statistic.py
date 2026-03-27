import os
import subprocess

class Statistic:
    total_num_function_under_test = []
    total_num_generated_test_cases = []
    total_num_build_success = []
    total_build_success_rate = []
    total_num_run_success = []
    total_run_success_rate = []
    total_loc = []
    total_code_files = []
    def __init__(self, cwd, project_id, project):
        self.cwd = cwd
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.real_project_base = "TestProjects"
        self.real_project_path = os.path.join(self.cwd, self.real_project_base, self.project)
        self.project_path = os.path.join("experiments", self.project_id + '_' + self.project)
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

    def get_num_function_under_tests(self):
        num_function_under_tests = len(os.listdir(self.TEST_FILES_PATH))
        self.total_num_function_under_test.append(num_function_under_tests)
        return num_function_under_tests

    def get_num_generated_test_cases(self):
        def check_tc(file):
            with open(file, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                while '\n' in lines:
                    lines.remove('\n')
                count = 0
                for line in lines:
                    if line.startswith("TEST_F(") or line.startswith("TEST("):
                    # if line.startswith("TEST("):
                        count += 1
                return count
        
        total = 0
        for test_file in os.listdir(self.TEST_FILES_PATH):
            test_file_path = os.path.join(self.TEST_FILES_PATH, test_file)
            total = total + check_tc(test_file_path)
        self.total_num_generated_test_cases.append(total)
        return total

    def get_num_build_success(self):
        num_build_success = len(os.listdir(self.BUILD_PASS_DIR))
        self.total_num_build_success.append(num_build_success)
        return num_build_success

    def get_build_success_rate(self):
        total = len(os.listdir(self.BUILD_PASS_DIR)) + len(os.listdir(self.BUILD_FAIL_DIR))
        try:
            build_success_rate = len(os.listdir(self.BUILD_PASS_DIR)) / total
            self.total_build_success_rate.append(build_success_rate)
            return build_success_rate
        except ZeroDivisionError:
            self.total_build_success_rate.append(0.0)
            return 0.0

    def get_num_run_success(self):
        num_run_success = len(os.listdir(self.RUN_PASS_DIR))
        self.total_num_run_success.append(num_run_success)
        return num_run_success

    def get_run_success_rate(self):
        total = len(os.listdir(self.RUN_PASS_DIR)) + len(os.listdir(self.RUN_FAIL_DIR))
        try:
            run_success_rate = len(os.listdir(self.RUN_PASS_DIR)) / total
            self.total_run_success_rate.append(run_success_rate)
            return run_success_rate
        except ZeroDivisionError:
            self.total_run_success_rate.append(0.0)
            return 0.0
    
    def get_loc(self):
        command = ["cloc", ".", "--include-lang", "C,C++,C/C++ Header", "--exclude-dir", "test,tests,benchmark,benchmarks,example,examples,build,third-party,third_party,thirdparty,issues,fuzz,app,contrib,sample,samples,unitTests,xmlsdk,scripts"]
        result = subprocess.run(command, cwd=self.real_project_path, capture_output=True, text=True)
        print_flag = False
        text = ''
        for char in result.stdout:
            if char == "S":
                print_flag = True
            elif char == '-':
                print_flag = False
            if print_flag:
                text = text + char
        # print(text.split())
        # print(result.stdout)
        num_code_files = int(text.split()[1])
        loc = int(text.split()[-1])
        self.total_loc.append(loc)
        self.total_code_files.append(num_code_files)
        return loc
    
    def get_num_code_files(self):
        return self.total_code_files[int(self.project_id)-1]

    def get_total(self):
        return sum(self.total_num_function_under_test), \
        sum(self.total_num_generated_test_cases), \
        sum(self.total_num_build_success), \
        sum(self.total_build_success_rate) / len(self.total_build_success_rate), \
        sum(self.total_num_run_success), \
        sum(self.total_run_success_rate) / len(self.total_run_success_rate),\
        sum(self.total_loc),\
        sum(self.total_code_files)