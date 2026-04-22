from builder import ProjectBuilder, TestBuilder
from error_analyzer import ErrorAnalyzer
import error_category_description
from repair import repair_prompt
import copy
import ollama
import os
import json

class MAIN:
    def __init__(self):
        # self.llms = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]
        self.llms = ["claude"]
        self.project_list = ["JsonBox", "re2", "leveldb", "Catch2", "glomap",
                             "ninja", "tinyxml2", "yaml-cpp", "exiv2", "poppler"]
        self.condition_1_flag = True
        self.condition_2_flag = False
        self.condition_3_flag = False
        self.complete_flag = False

    def init_path(self, llm, project_id, project):
        self.llm = llm
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.project_path = os.path.join("./experiments", f"LLM/{self.llm}", self.project_id + '_' + self.project)
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

    def run(self):
        print("run")
        cwd = os.getcwd()
        for llm in self.llms:
            for ix, project in enumerate(self.project_list):
                print(project)
                if ix != 0: continue
                self.repair_path = os.path.join("./experiments", "repair", "generated_test")
                self.repair_project_dir = os.path.join(self.repair_path, project)
                os.makedirs(self.repair_project_dir, exist_ok=True)

                project_id = ix + 1
                self.init_path(llm, project_id, project)
                ea = ErrorAnalyzer(cwd, project_id, project, llm)
                failed_log_list = ea._get_build_failed_list()
                
                for _ in range(3):
                    for ix, failed_log in enumerate(failed_log_list):
                        print(f"{ix+1}/{len(failed_log_list)}")
                        error_lines = self.get_error_lines(ea, failed_log)
                        if error_lines is None:
                            continue

                        init_prompt = self.get_init_prompt(failed_log)
                        init_test = self.get_init_test(failed_log)
                        init_test = "\n".join([line for line in init_test.split('\n') if line != ''])

                        error_lines = list(set(error_lines))
                        categorized_errors = self.get_categorized_error(ea, error_lines)

                        if self.condition_1_flag:
                            print("condition_1")
                            self.condition_1(ea, failed_log, init_prompt, error_lines, init_test)
                        elif self.condition_2_flag:
                            print("condition_2")
                            self.condition_2(ea, failed_log, init_prompt, error_lines, init_test, categorized_errors)
                        elif self.condition_3_flag:
                            print("condition_3")
                            self.condition_3(ea, failed_log, init_prompt, error_lines, init_test, categorized_errors)
                    if self.condition_1_flag:
                        self.condition_1_flag = False
                        self.condition_2_flag = True
                    elif self.condition_2_flag:
                        self.condition_2_flag = False
                        self.condition_3_flag = True
                    elif self.condition_3_flag:
                        self.condition_3_flag = False
                        self.condition_1_flag = True

    def __update_init_prompt_path(self):
        base = os.path.join("./experiments", "repair", "init_prompts")
        folders = [f for f in os.listdir(base) if os.path.isdir(os.path.join(base, f))]

        for folder in folders:
            if self.project.lower() in folder.lower():
                self.init_prompt_path = os.path.join(base, folder, 'prompts')
                break

    def _find_init_prompt(self, ix):
        prompt_name = f"prompt_{ix}.txt"
        prompt_path = os.path.join(self.init_prompt_path, prompt_name)
        prompt = open(prompt_path, 'r', encoding='utf-8').read()
        return prompt

    def get_init_prompt(self, failed_log):
        self.__update_init_prompt_path()
        ix = failed_log.split('_')[-1].replace(".log", '')
        init_prompt = self._find_init_prompt(ix)
        return init_prompt

    def get_init_test(self, failed_log):
        ix = failed_log.split('_')[-1].replace(".log", '')
        test_name = f"test_{ix}.cpp"
        test_path = os.path.join(self.BUILD_FAIL_DIR, test_name)
        test = open(test_path, 'r', encoding='utf-8').read()
        return test

    def get_error_lines(self, ea, failed_log, log_path=None):
        return ea.find_error_lines([failed_log], log_path).get(failed_log)

    def get_categorized_error(self, ea, error_lines):
        categorized_errors = []
        if error_lines:
            for line in error_lines:
                pattern, _ = ea.match_line_to_pattern(line)
                category, subtype = ea.match_pattern_to_category(pattern)
                try:
                    if category != "Semantic":
                        description, guide = error_category_description.CATEGORIE_DESCRIPTIONS.get(category).values()
                    else:
                        description, guide = error_category_description.CATEGORIE_DESCRIPTIONS.get(category).get(subtype).values()
                    categorized_errors.append((category, subtype, description, guide))
                except:
                    with open(os.path.join(self.project_path, "may_new_error_line.log"), 'a', encoding='utf-8') as f:
                        f.write(line)
                        f.write('\n')
        return categorized_errors

    def generate_test(self, prompt):
        client = ollama.Client()
        response = client.chat(
            model='qwen2.5-coder:32b',
            messages=[
                {'role': 'user', 'content': f"{prompt}"}
            ]
        )
        return response.message.content

    def get_code(self, test):
        read_flag = False
        lines = test.split('\n')
        new_lines = []
        for ix, line in enumerate(lines):
            if ix < len(lines)//2 and not read_flag and '```' in line:
                read_flag = True
                continue
            elif ix > len(lines)//2 and read_flag and '```' in line:
                read_flag = False
                continue
            elif read_flag:
                new_lines.append(line)
            else:
                continue
        return '\n'.join(new_lines)
    
    def _get_after_first(self, ea, i, test_name, condition_dir, error_messages):        
        # round = startswith 1
        prev_round_path = os.path.join(condition_dir, str(i))
        failed_log_path = os.path.join(prev_round_path, "log", "build_log")
        # failed_log = a qFileName
        error_lines = self.get_error_lines(ea, test_name.replace('.cpp', '.log'), failed_log_path)
        test_path = os.path.join(prev_round_path, "test_files", test_name)
        test_code = open(test_path, 'r', encoding='utf-8').read()
        # error_messages = startswith 0
        attempt = ''
        for key in range(i):
            msg = error_messages.get(key)
            msg = '\n'.join(msg)
            attempt += f"Attempt#{key+1}: [{msg}]\n"

        categorized_errors = self.get_categorized_error(ea, error_lines)
        categories = {}
        for error in categorized_errors:
            category, subtype, description, guide = error
            if subtype is not None:
                categories['-'.join([category, subtype])] = (description, guide)
            else:
                categories[category] = (description, guide)
        
        return error_lines, test_code, attempt, categories

    def is_done(self, condition_dir, test_name):
        path = os.path.join(condition_dir, 'check_list.txt')
        if not os.path.exists(path):
            return False
        with open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            for ix, line in enumerate(lines):
                if f"{test_name}: 5: False" in line:
                    return True
                else:
                    for round in range(1, 6):
                        if f"{test_name}: {round}: True" in line:
                            return True
            return False

    def condition_1(self, ea, test_name, init_prompt, error_lines, init_test):
        cwd = os.getcwd()
        error_messages = {}
        attempt = ''
        test_name = test_name.replace('.log', '.cpp')
        condition_dir = os.path.join(self.repair_project_dir, 'cond_1')
        os.makedirs(condition_dir, exist_ok=True)
        print(test_name)
        if self.is_done(condition_dir, test_name):
            return
        for i in range(5):
            round = str(i+1)
            print(f"ROUND #{round}")
            if i != 0:
                error_lines, init_test, attempt, _ = self._get_after_first(ea, i, test_name, condition_dir, error_messages)

            round_dir = os.path.join(condition_dir, round)
            test_path_dir = os.path.join(round_dir, "test_files")
            prompts_dir = os.path.join(round_dir, "prompts")
            os.makedirs(test_path_dir, exist_ok=True)
            os.makedirs(prompts_dir, exist_ok=True)

            error_messages[i] = error_lines
            prompt = copy.deepcopy(repair_prompt.CONDITION_1)
            prompt = prompt.format(
                init_prompt=init_prompt,
                errors='\n'.join(error_lines),
                attempt=attempt,
                test_code=init_test
            )
            prompt += f"\nThis is for repair the test file and this round is {i+1}"
            prompt += "\nOnly the test cases should be produced. If you output anything other than test code, the answer is incorrect."
            with open(os.path.join(prompts_dir, test_name.replace(".cpp", ".log").replace("test", "prompt")), 'w', encoding='utf-8') as f:
                f.write(prompt)
            #1: MAKE TEST
            test = self.get_code(self.generate_test(prompt))
            test_path = os.path.join(round_dir, 'test_files', test_name)
            with open(test_path, 'w', encoding='utf-8') as f:
                f.write(test)

            # 2: TRY BUILD
            tb = TestBuilder(cwd, self.project_id, self.project, self.llm, repair=True, round=round, round_dir=round_dir)
            passed = tb.build(test_name)
            with open(os.path.join(condition_dir, 'check_list.txt'), 'a', encoding='utf-8') as f:
                f.write(f"{test_name}: {round}: {str(passed)}\n")
            if passed:
                break

    def condition_2(self, ea, test_name, init_prompt, error_lines, init_test, categorized_errors):
        cwd = os.getcwd()
        error_messages = {}
        attempt = ''
        test_name = test_name.replace('.log', '.cpp')
        condition_dir = os.path.join(self.repair_project_dir, 'cond_2')
        os.makedirs(condition_dir, exist_ok=True)
        categories = {}
        for error in categorized_errors:
            category, subtype, description, guide = error
            if subtype is not None:
                categories['-'.join([category, subtype])] = (description, guide)
            else:
                categories[category] = (description, guide)
        
        if self.is_done(condition_dir, test_name):
            return
        for i in range(5):
            round = str(i+1)
            print(f"ROUND #{round}")
            if i != 0:
                error_lines, init_test, attempt, categories = self._get_after_first(ea, i, test_name, condition_dir, error_messages)

            round_dir = os.path.join(condition_dir, round)
            test_path_dir = os.path.join(round_dir, "test_files")
            prompts_dir = os.path.join(round_dir, "prompts")
            os.makedirs(test_path_dir, exist_ok=True)
            os.makedirs(prompts_dir, exist_ok=True)

            category_description = []
            if categories:
                errors_categories = '\n'.join(list(categories.keys()))
                for key in categories.keys():
                    description, _ = categories.get(key)
                    if description not in category_description:
                        category_description.append(description)

            error_messages[i] = error_lines
            prompt = copy.deepcopy(repair_prompt.CONDITION_2)
            prompt = prompt.format(
                init_prompt=init_prompt,
                errors='\n'.join(error_lines),
                errors_categories=errors_categories,
                category_descriptions='\n'.join(category_description),
                attempt=attempt,
                test_code=init_test
            )
            prompt += f"\nThis is for repair the test file and this round is {i+1}"
            prompt += "\nOnly the test cases should be produced. If you output anything other than test code, the answer is incorrect."
            with open(os.path.join(prompts_dir, test_name.replace(".cpp", ".log").replace("test", "prompt")), 'w', encoding='utf-8') as f:
                f.write(prompt)
            ## 1: MAKE TEST
            test = self.get_code(self.generate_test(prompt))
            test_path = os.path.join(round_dir, 'test_files', test_name)
            with open(test_path, 'w', encoding='utf-8') as f:
                f.write(test)

            ## 2: TRY BUILD
            tb = TestBuilder(cwd, self.project_id, self.project, self.llm, repair=True, round=round, round_dir=round_dir)
            passed = tb.build(test_name)
            with open(os.path.join(condition_dir, 'check_list.txt'), 'a', encoding='utf-8') as f:
                f.write(f"{test_name}: {round}: {str(passed)}\n")
            if passed:
                break

    def condition_3(self, ea, test_name, init_prompt, error_lines, init_test, categorized_errors):
        cwd = os.getcwd()
        error_messages = {}
        attempt = ''
        test_name = test_name.replace('.log', '.cpp')
        condition_dir = os.path.join(self.repair_project_dir, 'cond_3')
        os.makedirs(condition_dir, exist_ok=True)
        categories = {}
        for error in categorized_errors:
            category, subtype, description, guide = error
            if subtype is not None:
                categories['-'.join([category, subtype])] = (description, guide)
            else:
                categories[category] = (description, guide)

        if self.is_done(condition_dir, test_name):
            return
        for i in range(5):
            round = str(i+1)
            print(f"ROUND #{round}")
            if i != 0:
                error_lines, init_test, attempt, categories = self._get_after_first(ea, i, test_name, condition_dir, error_messages)

            round_dir = os.path.join(condition_dir, round)
            test_path_dir = os.path.join(round_dir, "test_files")
            prompts_dir = os.path.join(round_dir, "prompts")
            os.makedirs(test_path_dir, exist_ok=True)
            os.makedirs(prompts_dir, exist_ok=True)

            category_description = []
            solution_guide = []
            if categories:
                errors_categories = '\n'.join(list(categories.keys()))
                for key in categories.keys():
                    description, guide = categories.get(key)
                    if description not in category_description:
                        category_description.append(description)
                    if guide not in solution_guide:
                        solution_guide.append(guide)

            error_messages[i] = error_lines
            prompt = copy.deepcopy(repair_prompt.CONDITION_3)
            prompt = prompt.format(
                init_prompt=init_prompt,
                errors='\n'.join(error_lines),
                errors_categories=errors_categories,
                category_descriptions='\n'.join(category_description),
                solutions='\n'.join(solution_guide),
                attempt=attempt,
                test_code=init_test
            )
            prompt += f"\nThis is for repair the test file and this round is {i+1}"
            prompt += "\nOnly the test cases should be produced. If you output anything other than test code, the answer is incorrect."
            with open(os.path.join(prompts_dir, test_name.replace(".cpp", ".log").replace("test", "prompt")), 'w', encoding='utf-8') as f:
                f.write(prompt)
            ## 1: MAKE TEST
            test = self.get_code(self.generate_test(prompt))
            test_path = os.path.join(round_dir, 'test_files', test_name)
            with open(test_path, 'w', encoding='utf-8') as f:
                f.write(test)

            ## 2: TRY BUILD
            tb = TestBuilder(cwd, self.project_id, self.project, self.llm, repair=True, round=round, round_dir=round_dir)
            passed = tb.build(test_name)
            with open(os.path.join(condition_dir, 'check_list.txt'), 'a', encoding='utf-8') as f:
                f.write(f"{test_name}: {round}: {str(passed)}\n")
            if passed:
                break
