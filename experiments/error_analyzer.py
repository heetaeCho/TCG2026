import os
import re
import error_patterns
import error_category
import error_category_description

class ErrorAnalyzer:
    count = 0
    def __init__(self, cwd, project_id, project, llm):
        self.cwd = cwd
        self.llm = llm
        self.project = project
        self.project_id = f"{project_id:02d}"
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

    def get_map(self):
        log_errors_map = self.find_error_lines(self._get_build_failed_list())
        for log, lines in log_errors_map.items():
            for ix, line in enumerate(lines):
                pattern, description = self.match_line_to_pattern(line) 
                if pattern is None and description is None:
                    continue
                category, subtype = self.match_pattern_to_category(pattern)
                if category is None and subtype is None:
                    print(pattern)
                elif category != "Semantic":
                    log_errors_map[log][ix] = category
                else:
                    log_errors_map[log][ix] = subtype
        return log_errors_map

    def find_error_lines(self, build_failed_list):
        error_lines = {}
        for build_failed in build_failed_list:
            build_failed = os.path.join(self.BUILD_LOG_DIR, build_failed)
            with open(build_failed, 'r', encoding='utf-8') as log:
                name = build_failed.split('/')[-1]
                for line in log.readlines():
                    if self._is_error_line(line):
                        TEST_FILES_PATH = os.path.join(self.project_path, "test_files")
                        TEST_FILES_PATH = TEST_FILES_PATH.replace("\\", "/")
                        if TEST_FILES_PATH in line:
                            error_log = line.split("error:")[-1].strip()
                            
                            # error_lines.append(error_log)
                            if name in error_lines.keys():
                                error_lines[name].append(error_log)
                            else:
                                error_lines[name] = [error_log]
        return error_lines

    def match_line_to_pattern(self, line):
        for key, (pattern, desc) in error_patterns.PATTERNS.items():
            if re.search(pattern, line):
                return key, desc
        return None, None

    def match_pattern_to_category(self, pattern):
        for category in error_category.CATEGORIES.keys():
            if category in ("Lexical", "Syntactic", "Linker"):
                if pattern in error_category.CATEGORIES.get(category):
                    return category, None
            elif category == "Semantic":
                subtypes = error_category.CATEGORIES.get(category)
                for subtype in subtypes.keys():
                    if pattern in subtypes.get(subtype):
                        return category, subtype
        return None, None

    def analyze(self): 
        import copy 
        project_error_count = copy.deepcopy(error_category.COUNT_CATEGORIES)
        error_lines = self.find_error_lines(self._get_build_failed_list())
        for log, lines in error_lines.items():
            # leveldb = "cannot use 'try' with exceptions disabled" which is removed since this's setting problem
            # exiv2 = "Cannot find WXMP_Common.hpp (needed for WXMP_Result)." which  is project message
            # poppler = "cannot use 'try' with exceptions disabled", "cannot use 'throw' with exceptions disabled"
            #           "Goffset is not defined. Please include the Poppler header that defines Goffset (e.g., goo/gtypes.h) before including this test."
            # poppler have None that appeared with the same reason
            for line in lines:
                pattern, description = self.match_line_to_pattern(line) 
                if pattern is None and description is None:
                    continue
                category, subtype = self.match_pattern_to_category(pattern)
                if category is None and subtype is None:
                    print(pattern)
                elif category != "Semantic":
                    project_error_count[category] += 1
                else:
                    project_error_count[category][subtype] += 1
        return project_error_count

    def _pre_analyze(self):
        frequency = []
        unique = set()
        build_failed_list = self._get_build_failed_list()
        for build_failed in build_failed_list:
            build_failed = os.path.join(self.BUILD_LOG_DIR, build_failed)
            with open(build_failed, 'r', encoding='utf-8') as log:
                for line in log.readlines():
                    if self._is_error_line(line):
                        TEST_FILES_PATH = os.path.join("experiments", self.project_id + '_' + self.project, "test_files")
                        TEST_FILES_PATH = TEST_FILES_PATH.replace("\\", "/")
                        if TEST_FILES_PATH in line:
                            error_log = line.split("error:")[-1].strip()
                            frequency.append(error_log)
                            unique.add(error_log)
                            # print("error: ", )
                            self.count += 1
                        else:
                            print(line)
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
        LINKER_ERROR_PATTERN = re.compile(
            r"undefined reference to|"
            r"undefined symbol:|"
            r"multiple definition of|"
            r"cannot find -l",
            re.IGNORECASE
        )
        if ("note" in line) or ("warning" in line) or ("clang++:" in line):
            return False
        return bool(COMPILER_ERROR_LINE.search(line) or LINKER_ERROR_PATTERN.search(line))
    
