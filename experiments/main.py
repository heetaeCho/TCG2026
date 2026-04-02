# 뭘 해야하지?
# 빌드, 실행, 커버리지 측정, 빌드 실패 이유 분석, 함수 구조 지표 측정, 로지스틱 분석
# 빌드-실행 은 하나
# 커버리지 측정은 실행 이후
# 빌드 실패 이유 분석은 빌드 결과 이후
# 함수 구조 지표 측정은 빌드 결과 이후
# 로지스틱 분석은 모든 프로젝트의 함수 구조 지표 측정 이후

# 고로 빌드-실행이 먼저.
# 커버리지가 그 다음.
# 빌드 실패 이유 분석을 한 다음.
# 구조 지표를 분석하고
# 모든 프로젝트의 지표가 모이면 로지스틱 분석이 마지막

# 기존 MyError는 일단 복제 필요 - 언제부터 사용하지? 
import os
from builder import ProjectBuilder, TestBuilder
from statistic import Statistic
from coverage import CoverageChecker
from error_analyzer import ErrorAnalyzer
import error_category
from function_analyzer import StructureMetric, Integrator, LogisticAnalyzer
import copy 
import pandas as pd

class Main:
    def __init__(self, llm):
        self.llm = llm
        self.project_list = ["JsonBox", "re2", "leveldb", "Catch2", "glomap",
                             "ninja", "tinyxml2", "yaml-cpp", "exiv2", "poppler"]
        # self.project_list.reverse()

    def run_build(self, specific=0, skip=0):
        cwd = os.getcwd()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            pb = ProjectBuilder(cwd, project_id, project, self.llm)
            pb.build()

            tb = TestBuilder(cwd, project_id, project, self.llm)
            tb.build()
            tb.execute()

    def get_statistics(self, csv, specific=0, skip=0):
        def prepare_csv(csv):
            with open(csv, 'w', encoding='utf-8') as f:
                text = 'index,PROJECT,#Code Files,LOC,#function under test,#generated test cases,#build success,build success rate,#run success,run success rate\n'
                f.write(text)

        def post_csv(csv):
            total_num_function_under_test,\
            total_num_generated_test_cases,\
            total_num_build_success,\
            avg_build_success_rate,\
            total_num_run_success,\
            avg_run_success_rate,\
            total_loc,\
            total_code_files = statistic.get_total()

            with open(csv, 'a', encoding='utf-8')as f:
                text = f',TOTAL,{total_code_files},{total_loc},{total_num_function_under_test},{total_num_generated_test_cases},{total_num_build_success},{avg_build_success_rate},{total_num_run_success},{avg_run_success_rate}'
                f.write(text)

        cwd = os.getcwd()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            statistic = Statistic(cwd, project_id, project, self.llm)
            num_function_under_test = statistic.get_num_function_under_tests()
            num_generated_test_cases = statistic.get_num_generated_test_cases()
            num_build_success = statistic.get_num_build_success()
            build_success_rate = statistic.get_build_success_rate()
            num_run_success = statistic.get_num_run_success()
            run_success_rate = statistic.get_run_success_rate()
            loc = statistic.get_loc()
            num_code_files = statistic.get_num_code_files()
            # print("-"*50)
            # print(f"PROJECT: {project}")
            # print(f"#Code Files: {num_code_files}")
            # print(f"LOC: {loc}")
            # print(f"#function under test: {num_function_under_test}")
            # print(f"#generated test cases: {num_generated_test_cases}")
            # print(f"#build success: {num_build_success}")
            # print(f"build success rate: {build_success_rate}")
            # print(f"#run success: {num_run_success}")
            # print(f"run success_rate: {run_success_rate}")
            with open(csv, 'a', encoding='utf-8') as f:
                text = f'{project_id},{project},{num_code_files},{loc},{num_function_under_test},{num_generated_test_cases},{num_build_success},{build_success_rate},{num_run_success},{run_success_rate}\n'
                f.write(text)
        prepare_csv(csv)
        post_csv(csv)


    def coverage_check(self, csv, specific=0, skip=0):
        def prepare_csv(csv):
            with open(csv, 'w', encoding='utf-8') as f:
                text = 'index,PROJECT,Line Coverage,Branch Coverage\n'
                f.write(text)

        def post_csv(csv):
            avg_line_coverage, avg_branch_coverage = cov_checker.get_total()
            with open(csv, 'a', encoding='utf-8') as f:
                text = f',Total,{avg_line_coverage}%,{avg_branch_coverage}%\n'
                f.write(text)

        cwd = os.getcwd()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            cov_checker = CoverageChecker(cwd, project_id, project, self.llm)
            cov_checker.check()
            line_coverage = cov_checker.get_line_coverage()
            branch_coverage = cov_checker.get_branch_coverage()
            # print("PROJTECT: ", project)
            # print(f"Line Coverage: {line_coverage}")
            # print(f"Branch Coverage: {branch_coverage}")
            with open(csv, 'a', encoding='utf-8') as f:
                text = f'{project_id},{project},{line_coverage},{branch_coverage}\n'
                f.write(text)
        prepare_csv(csv)
        post_csv(csv)

    def analyze_error(self, csv, specific=0, skip=0):
        def prepare_csv(csv):
            with open(csv, 'w', encoding='utf-8') as f:
                text = 'index,Category,#Error,%Error\n'
                f.write(text)

        def post_csv(csv, type4_count, type19_count, type4_rate, type19_rate):
            with open(csv, 'a', encoding='utf-8') as f:
                for category, value in type4_count.items():
                    rate = type4_rate[category]
                    text = f',{category},{value},{rate}%\n'
                    f.write(text)

                for category, value in type19_count["Semantic"].items():
                    # print(value)
                    rate = type19_rate["Semantic"][category]
                    text = f',{category},{value},{rate}%\n'
                    f.write(text)

        def type_4(_error_count):
            count = {"Lexical": 0,
                     "Syntactic": 0,
                     "Linker": 0,
                     "Semantic": 0}
            for category in _error_count:
                if category != "Semantic":
                    count[category] = _error_count[category]
                else:
                    for subtype in project_error_count[category]:
                        count[category] += _error_count[category][subtype]
            return count

        def type_4_rate(total, _error_count):
            rate = {"Lexical": 0,
                     "Syntactic": 0,
                     "Linker": 0,
                     "Semantic": 0}
            for category in _error_count.keys():
                rate[category] = (_error_count[category] / total) * 100
            return rate

        def type_19_rate(total, _error_count):
            rate = copy.deepcopy(error_category.COUNT_CATEGORIES)
            for category in _error_count.keys():
                if category != "Semantic":
                    rate[category] = (_error_count[category] / total) * 100
                else:
                    for subtype in _error_count[category]:
                        rate[category][subtype] = (_error_count[category][subtype] / total) * 100
            return rate

        cwd = os.getcwd()
        error_count = copy.deepcopy(error_category.COUNT_CATEGORIES)
        # frequency = []
        # unique = set()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            
            print("PROJECT: ", project)
            error_analyzer = ErrorAnalyzer(cwd, project_id, project, self.llm)
            project_error_count = error_analyzer.analyze()
            for category in project_error_count:
                if category != "Semantic":
                    error_count[category] += project_error_count[category]
                else:
                    for subtype in project_error_count[category]:
                        error_count[category][subtype] += project_error_count[category][subtype]

        type4_count = type_4(error_count)
        type19_count = copy.deepcopy(error_count)
        total = sum(type4_count.values())
        # print(total)
        # print(type4_count)
        # print(error_count)
        
        type4_rate = type_4_rate(total, type4_count)
        type19_rate = type_19_rate(total, error_count)
        # print(type4_rate)
        # print(type19_rate)
        prepare_csv(csv)
        post_csv(csv, type4_count, type19_count, type4_rate, type19_rate)
        '''
            f, u = error_analyzer._pre_analyze() 
            frequency.extend(f)
            unique.update(u)

        print(len(frequency))
        print(len(unique))
        for line in unique:
            print(line)
        '''

    def analyze_structural_metric(self, csv, specific=0, skip=0):
        cwd = os.getcwd()
        all_dfs = []
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            sm = StructureMetric(cwd, project_id, project, self.llm)
            results = sm.calculate()
            df = pd.DataFrame(results)
            df['project'] = project
            all_dfs.append(df)
        final_df = pd.concat(all_dfs, ignore_index=True)
        final_df.to_csv(csv, index=False)
    
    def integrate_metric(self):
        cwd = os.getcwd()
        # 1: 통합본
        # 2: LLM별
        # -1: 평균/성공/실패 수치
        # -2: 에러별 수치
        # 1) 3개 df, 1개 통합 df
        integrator = Integrator(cwd)
        integrator.analyze()

        integrated_csv_apf = f'./experiments/LLM/integrated_apf.csv'
        gpt_csv_apf = f'./experiments/LLM/GPT5/gpt_apf.csv'
        claude_csv_apf = f'./experiments/LLM/claude/claude_apf.csv'
        qwen_csv_apf = f'./experiments/LLM/qwen2.5_coder_32b-8k/qwen_apf.csv'

        integrated_csv_pe = f'./experiments/LLM/integrated_pe.csv'
        gpt_csv_pe = f'./experiments/LLM/GPT5/gpt_pe.csv'
        claude_csv_pe = f'./experiments/LLM/claude/claude_pe.csv'
        qwen_csv_pe = f'./experiments/LLM/qwen2.5_coder_32b-8k/qwen_pe.csv'

        integrated_apf = integrator.get_integrated_apf()
        integrated_apf.to_csv(integrated_csv_apf)

        integrated_pe = integrator.get_integrated_pe()
        integrated_pe.to_csv(integrated_csv_pe)

        gpt_apf = integrator.get_gpt_apf()
        gpt_apf.to_csv(gpt_csv_apf)
        gpt_pe = integrator.get_gpt_pe()
        gpt_pe.to_csv(gpt_csv_pe)

        claude_apf = integrator.get_claude_apf()
        claude_apf.to_csv(claude_csv_apf)
        claude_pe = integrator.get_claude_pe()
        claude_pe.to_csv(claude_csv_pe)

        qwen_apf = integrator.get_qwen_apf()
        qwen_apf.to_csv(qwen_csv_apf)
        qwen_pe = integrator.get_qwen_pe()
        qwen_pe.to_csv(qwen_csv_pe)


    def analyze_logistic(self):
        cwd = os.getcwd()
        la = LogisticAnalyzer(cwd)
        la.analyze()

        binary = la.get_bin()
        bin_csv = f'./experiments/LLM/binary_logistic.csv'
        binary.to_csv(bin_csv, float_format="%.6e")

        multi = la.get_mn()
        mn_csv = f'./experiments/LLM/multiclass_logistic.csv'
        multi.to_csv(mn_csv, float_format="%.6e")

if __name__ == "__main__":
    print("Experiments Main")
    # llms = ["qwen2.5_coder_32b-8k"]
    # llms = ["claude"]
    llms = ["claude", "qwen2.5_coder_32b-8k"]
    for llm in llms:
        main = Main(llm)
        main.run_build(specific=6)

    llms = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]
    for llm in llms:
        print("LLM: ", llm)
        main = Main(llm)
        # main.run_build(specific=6)
        # main.get_statistics(f'./experiments/LLM/{llm}/statistic.csv')
        # main.coverage_check(f'./experiments/LLM/{llm}/coverage.csv')
        main.analyze_error(f'./experiments/LLM/{llm}/error.csv')
        main.analyze_structural_metric(f'./experiments/LLM/{llm}/structural_metric.csv')

    main = Main(None)
    main.integrate_metric()
    main.analyze_logistic()

        # specific is project id
        # main.run_build(specific=0, skip=4)
        # 일단 ninja 실패 specific = 6
        # main.run_build(specific=6)
        # main.coverage_check('./experiments/coverage.csv', specific=6)

        # main.run_build(specific=2)
        # main.coverage_check(specific=2)
        # main.run_build(specific=4)
        # main.coverage_check(specific=4)