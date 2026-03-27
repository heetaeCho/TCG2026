import os
import subprocess
import glob

class CoverageChecker:
    line_coverage = []
    branch_coverage = []
    def __init__(self, cwd, project_id, project):
        self.cwd = cwd
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.real_project_base = "TestProjects"
        self.real_project_path = os.path.join(self.cwd, self.real_project_base, self.project)

        self.project_bin_map = {
            "JsonBox": ["libJsonBox.a"],
            "re2": ["libre2.a"],
            "leveldb": ["libleveldb.a"],
            "Catch2": ["src/libCatch2.a"],
            "glomap": ["glomap/libglomap.a"],
            "ninja": ["ninja"],
            "tinyxml2": ["libtinyxml2.a"],
            "yaml-cpp": ["libyaml-cpp.a"],
            "exiv2": ["bin/exiv2"],
            "poppler": ["libpoppler.so", "glib/libpoppler-glib.so",
                        'utils/pdftohtml', 'utils/pdfimages', 'utils/pdfseparate', 
                        'utils/pdfinfo', 'utils/pdftoppm', 'utils/pdfsig', 
                        'utils/pdfattach', 'utils/pdffonts', 'utils/pdfunite', 
                        'utils/pdftotext', 'utils/pdftocairo', 'utils/pdftops', 'utils/pdfdetach']
        }
        self.project_path = os.path.join("experiments", self.project_id + '_' + self.project)
        self.coverage_dir = os.path.join(self.project_path, "coverage")
        os.makedirs(self.coverage_dir, exist_ok=True)
    
    def check(self):
        # print('-'*50)
        # print(self.project)
        self.__merge(self.coverage_dir)
        self.__report(self.coverage_dir)
        # print('-'*50)

    def __merge(self, coverage_dir):
        project_build_path = os.path.join(self.project_path, "build")
        prof_files = []
        for test_dir in os.listdir(project_build_path):
            test_path = os.path.join(project_build_path, test_dir)
            
            if os.path.isfile(test_path):
                continue

            for in_dir in os.listdir(test_path):
                in_dir_file = os.path.join(test_path, in_dir)

                if os.path.isfile(in_dir_file) and in_dir == "default.profraw":
                    prof_files.append(in_dir_file)

        profdata = os.path.join(coverage_dir, "merged.profdata")
        command = ["/usr/lib/llvm-18/bin/llvm-profdata", "merge", "-sparse", *map(str, prof_files), "-o", str(profdata)]
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode == 0:
            print(f"✅ Merge 완료")
        else:
            print("❌ 오류 발생:")
            print(result.stderr)
        

    def __report(self, coverage_dir):
        profdata = os.path.join(coverage_dir, "merged.profdata")
        bins = self.project_bin_map[self.project]
        bin_base = os.path.join(self.real_project_path, "build")

        bin_path = [os.path.join(bin_base, bin) for bin in bins]

        command = ["/usr/lib/llvm-18/bin/llvm-cov", "report", f"-instr-profile=./{profdata}", '-ignore-filename-regex=tests?/.*\.cpp$|.*third_party/.*|.*benchmarks?/.*|.*test\.cc']

        for b in bin_path:
            command.extend(['-object', str(b)])


        outfile = os.path.join(coverage_dir, "./coverage-summary.txt")
        with open(outfile, 'w', encoding='utf-8') as f:
            result = subprocess.run(command, text=True, stdout=f)
            if result.returncode == 0:
                print(f"✅ report 완료")
            else:
                # 1. build 폴더 안의 모든 .o 파일 찾기 (re2 소스들)
                obj_files = glob.glob(f"{bin_base}/**/*.o", recursive=True)
                filtered_files = [f for f in obj_files if "/experiments/" not in f]
                filtered_files = [f for f in filtered_files if "/generated_build/" not in f]
                command = ["/usr/lib/llvm-18/bin/llvm-cov", "report", f"-instr-profile=./{profdata}", '-ignore-filename-regex=tests?/.*\.cpp$|.*third_party/.*|.*benchmarks?/.*|.*test\.cc?']
                for obj in filtered_files:
                    command.extend(['-object', str(obj)])

                result = subprocess.run(command, text=True, stdout=f)
                if result.returncode == 0:
                    print(f"✅ report 완료")
                else:
                    print("❌ 오류 발생:")
                    print(result.stderr)
    
    def get_line_coverage(self):
        line_coverage_index = -4
        branch_coverage_index = -1
        outfile = os.path.join(self.coverage_dir, "coverage-summary.txt")
        lines = open(outfile, 'r', encoding='utf-8').readlines()
        try:
            total_coverage_line = lines[-1].split()
            line_coverage = total_coverage_line[line_coverage_index]
            branch_coverage = total_coverage_line[branch_coverage_index]
            self.line_coverage.append(line_coverage)
            self.branch_coverage.append(branch_coverage)
        except IndexError:
            line_coverage = '0.0%'
            branch_coverage = '0.0%'
            self.line_coverage.append(line_coverage)
            self.branch_coverage.append(branch_coverage)
        return line_coverage
    
    def get_branch_coverage(self):
        return self.branch_coverage[int(self.project_id)-1]
    
    def get_total(self):
        temp_line_coverage = []
        temp_branch_coverage = []
        for line_coverage, branch_coverage in zip(self.line_coverage, self.branch_coverage):
            temp_line_coverage.append(float(line_coverage.split("%")[0]))
            temp_branch_coverage.append(float(branch_coverage.split("%")[0]))
        
        avg_line_coverage = sum(temp_line_coverage) / len(temp_line_coverage)
        avg_branch_coverage = sum(temp_branch_coverage) / len(temp_branch_coverage)
        return avg_line_coverage, avg_branch_coverage