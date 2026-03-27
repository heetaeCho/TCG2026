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
from function_analyzer import StructureMetric, LogisticAnalyzer

class Main:
    def __init__(self):
        self.project_list = ["JsonBox", "re2", "leveldb", "Catch2", "glomap",
                             "ninja", "tinyxml2", "yaml-cpp", "exiv2", "poppler"]

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
            pb = ProjectBuilder(cwd, project_id, project)
            pb.build()

            tb = TestBuilder(cwd, project_id, project)
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

        prepare_csv(csv)
        cwd = os.getcwd()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            statistic = Statistic(cwd, project_id, project)
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

        prepare_csv(csv)
        cwd = os.getcwd()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            cov_checker = CoverageChecker(cwd, project_id, project)
            cov_checker.check()
            line_coverage = cov_checker.get_line_coverage()
            branch_coverage = cov_checker.get_branch_coverage()
            # print("PROJTECT: ", project)
            # print(f"Line Coverage: {line_coverage}")
            # print(f"Branch Coverage: {branch_coverage}")
            with open(csv, 'a', encoding='utf-8') as f:
                text = f'{project_id},{project},{line_coverage},{branch_coverage}\n'
                f.write(text)
        post_csv(csv)

    def analyze_error(self, csv, specific=0, skip=0):
        cwd = os.getcwd()
        frequency = []
        unique = set()
        for ix, project in enumerate(self.project_list):
            project_id = ix + 1
            if specific != 0:
                if project_id != specific:
                    continue
            if skip != 0:
                if project_id <= skip:
                    continue
            
            print("PROJECT: ", project)
            error_analyzer = ErrorAnalyzer(cwd, project_id, project)
            # if print_old then print error already assigned as error type;
            # if print_new then print new error not yet assigned as log; 
            f, u = error_analyzer.analyze(print_old=True, print_new=True) 
            frequency.extend(f)
            unique.update(u)

        print(len(frequency))
        print(len(unique))
        for line in unique:
            print(line)

        # sm = StructureMetric(project_id, project)
        # sm.calculate()
        
        # # 모든 프로젝트의 정보가 모여야 가능하니까.
        # la = LogisticAnalyzer()
        # la.analyze()



if __name__ == "__main__":
    print("Experiments Main")
    main = Main()
    # main.run_build()
    # main.get_statistics('./experiments/statistic.csv')
    main.coverage_check('./experiments/coverage.csv')
    # main.analyze_error('./experiments/error.csv')

    # specific is project id
    # main.run_build(specific=0, skip=4)
    # 일단 ninja 실패 specific = 6
    # main.run_build(specific=6)
    # main.coverage_check('./experiments/coverage.csv', specific=6)

    # main.run_build(specific=2)
    # main.coverage_check(specific=2)
    # main.run_build(specific=4)
    # main.coverage_check(specific=4)
