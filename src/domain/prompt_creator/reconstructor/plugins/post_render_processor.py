class PostRenderProcessor:
    def __init__(self):
        self.base = \
"""
--- PROMPT START ---

You are given a partial implementation of a C++ class.
This class is already implemented and used in the actual codebase.
Your task is to write unit tests in a single file without main function for the given interface, using Google Test (and Google Mock if needed), while strictly following the constraints below.

[Constraints]
1. **Do NOT re-implement or infer the internal logic** of any function.  
   You must treat the implementation as a black box.
2. **Write tests only based on the provided interface** — that is, based on:
   - Function signatures
   - Observable behavior (e.g., return values, effects visible through public functions or callback invocations)
3. **You may use Google Mock**:
   - Only when mocking external collaborators (e.g., passed-in handlers, callbacks, or dependencies)
   - Not to simulate internal behavior of the class under test
4. **Do NOT access or rely on private/internal state**, such as internal buffers, counters, or helper function behavior.
5. Include test cases for:
   - Normal operation
   - Boundary conditions
   - Exceptional or error cases (if observable through the interface)
   - Verification of external interactions (e.g., mock handler calls and their parameters)
6. Each test case should clearly indicate what behavior is being tested, and should follow consistent naming conventions.

[Requirements]
1. add TEST_ID for every Test name
   e.g.) TEST_F(WriteBatchTest_85, PutIncreasesCount_85), where The TEST_ID is 85

[Partial Code]
{function_under_test}
---
[Known or Inferred Dependencies (Optional)]
{information_about_the_function}
--- PROMPT END ---
"""

    def run(self, target_map):
        main_list = ['headers', 'target_function']
        key_order_list = ['cxxrecord', 'enum', 'record', 'variable']
        # key_order_list = ['cxxrecord', 'enum', 'record', \
        #                   'constructor_callee_of_target', 'constructor_caller_of_target', \
        #                   'function_callee_of_target', 'function_caller_of_target']

        function_under_test = target_map[main_list[1]]#.replace('\n', ' ')

        self.variable_cnt = 0
        information_about_the_function = ""
        for key in key_order_list:
            if key in target_map.keys():
                for info in target_map[key]:
                     if key == 'variable':
                        self.variable_pp(info)
                     else:
                        information_about_the_function += info+'\n'

        if self.variable_cnt > 0:
            information_about_the_function += self.variable_merge()
        prompt = self.base.format(function_under_test=function_under_test, information_about_the_function=information_about_the_function)
        return prompt
    
    def variable_merge(self):
        temp_prompt = "File name : {}\nGlobal Variables :\n```cpp\n{}```"
        variable_parts = []
        for key in self.variable_info.keys():
            vars = self.variable_info[key]
            variable_parts.append(temp_prompt.format(key, '\n'.join(vars)))
        line = '\n'.join(variable_parts)
        return line

    def variable_pp(self, info):
        if self.variable_cnt == 0:
            self.variable_info = {}

        def parse(info):
            info = info.split('\n')
            file_name = info[0].split(':')[-1].strip()
            variable = info[2].split('`')[0].strip()
            if file_name in self.variable_info.keys():
                self.variable_info[file_name].append(variable)
            else:
                self.variable_info[file_name] =[variable]
        parse(info)
        self.variable_cnt += 1 
