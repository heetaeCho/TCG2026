import os, shutil, math, random
import pandas as pd

LLMs = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]

class TargetCopy:
    def get_build_fail_files(self, ROOT, llm, proj):
        build_fail_path = os.path.join(ROOT, llm, proj, "fail", "build_fail")
        if not os.path.exists(build_fail_path):
            return set()
        return set(os.listdir(build_fail_path))

    def get_error_type(self, ROOT, proj, filename):
        log_name = filename.replace(".cpp", ".log")
        metric_path = os.path.join(ROOT, "claude", "structural_metric.csv")
        if not os.path.exists(metric_path):
            return ["Unknown"]
        df = pd.read_csv(metric_path)
        proj_name = proj.split('_', 1)[-1]
        df = df[(df["log"] == log_name) & (df["project"] == proj_name) & (df["error_type"] != "PASS")]
        if df.empty:
            return ["Unknown"]
        return df["error_type"].tolist()

    def stratified_sample(self, files, ROOT, proj, max_count=100):
        if len(files) <= max_count:
            return list(files)

        type_map = {}
        for f in files:
            types = self.get_error_type(ROOT, proj, f)
            t = types[0] if types else "Unknown"
            type_map.setdefault(t, []).append(f)

        total = len(files)
        type_counts = {t: len(fs) for t, fs in type_map.items()}
        alloc = {t: max(1, math.floor(count / total * max_count)) for t, count in type_counts.items()}

        total_alloc = sum(alloc.values())
        remainder = max_count - total_alloc

        if remainder > 0:
            sorted_by_decimal = sorted(type_counts.keys(),
                key=lambda t: (type_counts[t] / total * max_count) - alloc[t],
                reverse=True)
            for t in sorted_by_decimal[:remainder]:
                alloc[t] += 1
        elif remainder < 0:
            sorted_by_ratio = sorted(type_counts.keys(), key=lambda t: type_counts[t], reverse=True)
            for t in sorted_by_ratio:
                if remainder == 0:
                    break
                if alloc[t] > 1:
                    alloc[t] -= 1
                    remainder += 1

        selected = []
        for t, n in alloc.items():
            selected.extend(random.sample(type_map[t], min(n, len(type_map[t]))))
        return selected

    def run(self, target_llm):
        ROOT = os.path.join(".", "experiments", "LLM")
        first_llm_path = os.path.join(ROOT, LLMs[0])
        project_dirs = sorted([d for d in os.listdir(first_llm_path)
                                if os.path.isdir(os.path.join(first_llm_path, d))])

        print("=== 프로젝트별 공통 build_fail 복사 ===")
        for proj in project_dirs:
            proj_name = proj.split('_', 1)[-1]
            llm_files = [self.get_build_fail_files(ROOT, llm, proj) for llm in LLMs]
            common_files = set.intersection(*llm_files)
            print(f"  {proj}: {len(common_files)}", end="")

            selected = self.stratified_sample(common_files, ROOT, proj)
            print(f" → 샘플링: {len(selected)}")

            dest = os.path.join(".", "experiments", "repair", "generated_test", proj_name, "test_files")
            os.makedirs(dest, exist_ok=True)

            for filename in selected:
                src_file = os.path.join(ROOT, target_llm, proj, "fail", "build_fail", filename)
                if os.path.exists(src_file):
                    shutil.copy2(src_file, os.path.join(dest, filename))


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--LLM", default="claude")
    parser.add_argument("--seed", type=int, default=42)
    args = parser.parse_args()

    random.seed(args.seed)
    tc = TargetCopy()
    tc.run(args.LLM)