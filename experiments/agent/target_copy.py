import os, sys, shutil, math, random
import argparse
import pandas as pd

LLMs = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]

class Main:
    def __init__(self):
        pass

    def get_build_fail_files(self, ROOT, llm, project):
        build_fail_path = os.path.join(ROOT, llm, project, "fail", "build_fail")
        if not os.path.exists(build_fail_path):
            return set()
        return set(os.listdir(build_fail_path))

    def get_error_type(self, ROOT, proj, filename):
        # test_58.cpp → test_58.log
        log_name = filename.replace(".cpp", ".log")
        metric_path = os.path.join(ROOT, "claude", "structural_metric.csv")
        print(metric_path)
        if not os.path.exists(metric_path):
            return ["Unknown"]
        df = pd.read_csv(metric_path)
        df = df[(df["log"] == log_name) & (df["project"] == proj) & (df["error_type"] != "PASS")]
        if df.empty:
            return ["Unknown"]
        return df["error_type"].tolist()

    def stratified_sample(self, files, ROOT, proj, max_count=100):
        if len(files) <= max_count:
            return list(files)

        # 파일별 에러 타입 분류 (첫 번째 에러 타입만 사용)
        type_map = {}
        for f in files:
            types = self.get_error_type(ROOT, proj, f)
            t = types[0] if types else "Unknown"
            type_map.setdefault(t, []).append(f)

        total = len(files)
        type_counts = {t: len(fs) for t, fs in type_map.items()}

        # 최소 1개 보장 + floor
        alloc = {t: max(1, math.floor(count / total * max_count)) for t, count in type_counts.items()}

        # 합계 조정
        total_alloc = sum(alloc.values())
        remainder = max_count - total_alloc

        if remainder > 0:
            # 소수점 큰 순서대로 채우기
            sorted_by_decimal = sorted(type_counts.keys(),
                key=lambda t: (type_counts[t] / total * max_count) - alloc[t],
                reverse=True)
            for t in sorted_by_decimal[:remainder]:
                alloc[t] += 1
        elif remainder < 0:
            # 비율 큰 순서대로 빼기 (1개 아래로 안 내려감)
            sorted_by_ratio = sorted(type_counts.keys(), key=lambda t: type_counts[t], reverse=True)
            for t in sorted_by_ratio:
                if remainder == 0:
                    break
                if alloc[t] > 1:
                    alloc[t] -= 1
                    remainder += 1

        # 각 타입에서 랜덤 샘플
        selected = []
        for t, n in alloc.items():
            selected.extend(random.sample(type_map[t], min(n, len(type_map[t]))))

        return selected

    def find_and_copy(self, ROOT, target_llm, dest, project_filter=None):
        first_llm_path = os.path.join(ROOT, LLMs[0])
        project_dirs = sorted([d for d in os.listdir(first_llm_path)
                                if os.path.isdir(os.path.join(first_llm_path, d))])

        os.makedirs(dest, exist_ok=True)

        print("=== 프로젝트별 공통 build_fail ===")
        for proj in project_dirs:
            if project_filter and project_filter not in proj:
                continue
            
            llm_files = [self.get_build_fail_files(ROOT, llm, proj) for llm in LLMs]
            common_files = set.intersection(*llm_files)
            print(f"  {proj}: {len(common_files)}", end="")

            selected = self.stratified_sample(common_files, ROOT, proj)
            print(f" → 샘플링: {len(selected)}")

            for filename in selected:
                src_file = os.path.join(ROOT, target_llm, proj, "fail", "build_fail", filename)
                if os.path.exists(src_file):
                    shutil.copy2(src_file, os.path.join(dest, filename))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--LLM")
    parser.add_argument("--project_folder_name")
    parser.add_argument("--project", default=None)
    parser.add_argument("--retry", type=int, default=0)
    parser.add_argument("--seed", type=int, default=42)
    args = parser.parse_args()

    random.seed(args.seed)

    base = "claude-proj" if args.LLM == "claude" else "codex-proj"
    ROOT = os.path.join(base, "TCG2026", "experiments", "LLM")

    main = Main()
    dest = os.path.join(base, args.project_folder_name, "test_files")
    main.find_and_copy(ROOT, args.LLM, dest, project_filter=args.project)

    sys.exit(0)