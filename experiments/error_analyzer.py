import os
import re

class ErrorAnalyzer:
    count = 0
    def __init__(self, cwd, project_id, project):
        self.cwd = cwd
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.real_project_base = "TestProjects"
        self.real_project_path = os.path.join(self.cwd, self.real_project_base, self.project)
        self.project_build_options = {
            "poppler": ["-DENABLE_GPGME=OFF", "-DENABLE_QT6=OFF"],
            "re2": ["-DCMAKE_POLICY_VERSION_MINIMUM=3.5"],
            }
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

    def analyze(self, print_old=False, print_new=True):
        frequency = []
        unique = set()
        build_failed_list = self._get_build_failed_list()
        for build_failed in build_failed_list:
            build_failed = os.path.join(self.BUILD_LOG_DIR, build_failed)
            with open(build_failed, 'r', encoding='utf-8') as log:
                for line in log.readlines():
                    if self._is_error_line(line):
                        if self.TEST_FILES_PATH in line :
                            error_log = line.split("error:")[-1].strip()
                            frequency.append(error_log)
                            unique.add(error_log)
                            # print("error: ", )
                            self.count += 1
                        # else:
                        #     print(line)
        print(self.count)
        print(len(frequency))
        print(len(unique))
        return frequency, unique

    def _get_build_failed_list(self):
        failed = os.listdir(self.BUILD_FAIL_DIR)
        return [item.replace('.cpp', '.log') for item in failed]
    
    def _is_error_line(self, line):
        COMPILER_ERROR_LINE = re.compile(
            r"^\s*(?:[^:\n]+:\d+:\d+:\s*)?(?:fatal\s+)?error:\s"
        )
        LINKER_ERROR_LINE = re.compile(
            r"^\s*(?:/usr/bin/ld|ld|ld\.lld|/usr/bin/ld\.lld|collect2)(?::|\s).*?\berror:\s",
            re.IGNORECASE
        )
        if ("note" in line) or ("warning" in line) or ("clang++:" in line):
            return False
        return bool(COMPILER_ERROR_LINE.search(line) or LINKER_ERROR_LINE.search(line))
