import os, sys
import subprocess
import argparse

class Executor:
    def __init__(self, llm, project_folder_name, project):
        self.llm = llm
        self.project_folder_name = project_folder_name
        self.project = project
        claude_path = "claude-proj"
        codex_path = "codex-proj"
        if os.path.exists(claude_path):
            self.base = claude_path
        elif os.path.exists(codex_path):
            self.base = codex_path
        else:
            raise

        self.cwd = os.path.dirname(os.path.abspath(__file__))
        self.project_base_path = os.path.join(self.base, self.project_folder_name)
        self.repair_path = os.path.join(self.project_base_path, "repair")
        self.build_path = os.path.join(self.repair_path, "build")
        print(self.build_path)

    def execute(self, test_file):
        test_name = test_file.split(".")[0]
        exe_path = os.path.join(self.build_path, test_name)
        result = None
        try:
            try:
                result = subprocess.run(f"./{test_name}", timeout=10, cwd=exe_path, capture_output=True)
            except:
                result = subprocess.run([exe_path], timeout=10, capture_output=True)
        except subprocess.TimeoutExpired as e:
            print(f"[RUN FAIL] : {test_name}")
            if os.path.exists(os.path.join(self.build_path, "default.profraw")):
                os.remove(os.path.join(self.build_path, "default.profraw"))
            return False, None

        if result.returncode >= 0:
            print(f"[RUN PASS] : {test_name}")
        else:
            print(f"[RUN FAIL] : {test_name}")
            if os.path.exists(os.path.join(self.build_path, "default.profraw")):
                os.remove(os.path.join(self.build_path, "default.profraw"))

        return result.returncode >= 0, result

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--LLM")
    parser.add_argument("--project_folder_name")
    parser.add_argument("--project")
    parser.add_argument("--test_file")
    args = parser.parse_args()

    base = "claude-proj" if args.LLM == "claude" else "codex-proj"
    test_name = os.path.splitext(args.test_file)[0]
    log_dir = f"./{base}/{args.project_folder_name}/results/logs"
    os.makedirs(log_dir, exist_ok=True)

    executor = Executor(args.LLM, args.project_folder_name, args.project)
    is_pass, result = executor.execute(args.test_file)

    # gtest 출력을 로그 파일에 저장 (bash에서 grep -q "FAILED" 로 판단)
    with open(f"{log_dir}/{test_name}_result.txt", "w") as f:
        if result is not None:
            f.write(result.stdout.decode() if result.stdout else "")
            f.write(result.stderr.decode() if result.stderr else "")

    sys.exit(0)  # exit code는 항상 0, bash는 로그파일로 판단