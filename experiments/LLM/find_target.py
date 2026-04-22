import os
import pandas as pd
import numpy as np

# 모든 프로젝트에서 생성된 수가 다르니까 당연히 %로 비교해야하는 거겠고.
# 비율의 합은.... 아니니까 평균으로 해야하는거고.

ROOT = os.path.dirname(os.path.abspath(__file__))  # 실제 경로로 바꿔
LLMs = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]
TARGET_CSV = "type19_rate_error.csv"  # or "type19_count_error.csv"
# TARGET_CSV = "type19_count_error.csv"


def read_csv_as_series(path, value_col):
    """CSV를 읽어 Semantic 제외, Category를 index로 한 Series 반환"""
    df = pd.read_csv(path)
    df = df[df["Category"] != "Semantic"].copy()
    df = df.set_index("Category")

    series = df[value_col].astype(str).str.replace("%", "", regex=False).astype(float)
    return series


def get_mean_vector(llm_dirs):
    """3개 LLM의 error.csv에서 %Error 컬럼 평균 벡터 계산"""
    frames = []
    for llm in llm_dirs:
        path = os.path.join(ROOT, llm, "error.csv")
        s = read_csv_as_series(path, value_col="%Error")
        # s = read_csv_as_series(path, value_col="#Error")
        frames.append(s)

    mean_series = pd.concat(frames, axis=1).mean(axis=1)
    return mean_series
    # sum_series = pd.concat(frames, axis=1).sum(axis=1)
    # return sum_series


def find_closest_project(llm, mean_vec):
    """한 LLM 폴더 안 10개 프로젝트 중 평균과 가장 가까운 것 탐색"""
    llm_path = os.path.join(ROOT, llm)

    project_dirs = sorted([
        d for d in os.listdir(llm_path)
        if os.path.isdir(os.path.join(llm_path, d))
    ])

    # TARGET_CSV에 따라 읽을 컬럼 결정
    value_col = "%Error" if "rate" in TARGET_CSV else "#Error"

    distances = {}
    for project in project_dirs:
        target_path = os.path.join(llm_path, project, TARGET_CSV)
        if not os.path.exists(target_path):
            print(f"  [SKIP] {project}: {TARGET_CSV} 없음")
            continue

        vec = read_csv_as_series(target_path, value_col=value_col)

        shared_idx = mean_vec.index.intersection(vec.index)
        # 유클리드 디스트
        dist = ((vec[shared_idx] - mean_vec[shared_idx]) ** 2).sum() ** 0.5
        distances[project] = dist

    closest = min(distances, key=distances.get)
    return closest, distances

def find_most_uniform_project(llm_dirs):
    """30개 프로젝트 중 17개 카테고리 비율이 가장 균등한 것 탐색"""
    all_distances = {}  # { "GPT5/project1": dist, ... }

    for llm in llm_dirs:
        llm_path = os.path.join(ROOT, llm)
        project_dirs = sorted([
            d for d in os.listdir(llm_path)
            if os.path.isdir(os.path.join(llm_path, d))
        ])

        for project in project_dirs:
            target_path = os.path.join(llm_path, project, TARGET_CSV)
            if not os.path.exists(target_path):
                continue

            vec = read_csv_as_series(target_path, value_col="%Error")
            uniform_vec = pd.Series([100 / len(vec)] * len(vec), index=vec.index)
            shared_idx = uniform_vec.index.intersection(vec.index)
            dist = ((vec[shared_idx] - uniform_vec[shared_idx]) ** 2).sum() ** 0.5
            all_distances[f"{llm}/{project}"] = dist

    return all_distances

def get_build_fail_count(llm, project):
    build_fail_path = os.path.join(ROOT, llm, project, "fail", "build_fail")
    if not os.path.exists(build_fail_path):
        return -1  # 폴더 없으면 -1
    return len(os.listdir(build_fail_path))

def get_build_fail_files(llm, project):
    build_fail_path = os.path.join(ROOT, llm, project, "fail", "build_fail")
    if not os.path.exists(build_fail_path):
        return set()
    return set(os.listdir(build_fail_path))


def save_results(llm_dirs, mean_vec, closest_distances, uniform_distances, common_fails):
    """
    closest_distances: { llm: (closest, {proj: dist}) }
    uniform_distances: { "llm/proj": dist }
    common_fails: { proj: count }
    """
    project_dirs = sorted(common_fails.keys())

    # CSV 1: 평균과의 거리
    rows = []
    for llm, (closest, distances) in closest_distances.items():
        for proj, dist in distances.items():
            fail_count = get_build_fail_count(llm, proj)
            rows.append({
                "LLM": llm,
                "Project": proj,
                "build_fail": fail_count,
                "dist_from_mean": round(dist, 4),
                "closest": proj == closest
            })
    pd.DataFrame(rows).to_csv("result_mean_dist.csv", index=False)

    # CSV 2: 균등과의 거리
    rows = []
    for llm in llm_dirs:
        llm_distances = {k.split("/")[1]: v for k, v in uniform_distances.items() if k.startswith(llm)}
        closest = min(llm_distances, key=llm_distances.get)
        for proj, dist in llm_distances.items():
            fail_count = get_build_fail_count(llm, proj)
            rows.append({
                "LLM": llm,
                "Project": proj,
                "build_fail": fail_count,
                "dist_from_uniform": round(dist, 4),
                "closest": proj == closest
            })
    pd.DataFrame(rows).to_csv("result_uniform_dist.csv", index=False)

    # CSV 3: 프로젝트별 공통 build_fail
    rows = [{"Project": proj, "common_build_fail": count} for proj, count in common_fails.items()]
    pd.DataFrame(rows).to_csv("result_common_fails.csv", index=False)

    print("저장 완료: result_mean_dist.csv / result_uniform_dist.csv / result_common_fails.csv")


# ── 메인 ──────────────────────────────────────────────

mean_vec = get_mean_vector(LLMs)
'''
평균과 가장 가까운 프로젝트 찾기 (find_closest_project)


3개 LLM의 error.csv %Error를 평균낸 벡터를 기준으로
각 LLM의 10개 프로젝트 중 그 평균 분포와 유클리드 거리가 가장 작은 프로젝트 탐색
즉 "전체 평균을 가장 잘 대표하는 프로젝트"
'''
print("=== 3개 LLM 평균 벡터 ===")
print(mean_vec.round(4))
print()

closest_distances = {}
for llm in LLMs:
    print(f"=== {llm} ===")
    closest, distances = find_closest_project(llm, mean_vec)
    closest_distances[llm] = (closest, distances)  # 저장용으로 보관
    for proj, dist in sorted(distances.items(), key=lambda x: x[1]):
        marker = " ◀ 최근접" if proj == closest else ""
        fail_count = get_build_fail_count(llm, proj)
        print(f"  {proj} ({fail_count}): {dist:.4f}{marker}")

print("=" * 50)


'''
균등 분포와 가장 가까운 프로젝트 찾기 (find_most_uniform_project)

17개 카테고리가 모두 동일한 비율(100/17 ≈ 5.88%)인 이상적 균등 벡터를 기준으로
30개 프로젝트 중 그 균등 분포와 유클리드 거리가 가장 작은 프로젝트 탐색
즉 "에러가 특정 카테고리에 편중되지 않고 고르게 퍼진 프로젝트"
'''
uniform_distances = find_most_uniform_project(LLMs)
print("=== 균등 분포와의 거리 ===")
for llm in LLMs:
    print(f"\n  {llm}")
    llm_distances = {k.split("/")[1]: v for k, v in uniform_distances.items() if k.startswith(llm)}
    closest = min(llm_distances, key=llm_distances.get)
    for proj, dist in sorted(llm_distances.items(), key=lambda x: x[1]):
        marker = " ◀ 최근접" if proj == closest else ""
        fail_count = get_build_fail_count(llm, proj)
        print(f"    {proj} ({fail_count}): {dist:.4f}{marker}")

first_llm_path = os.path.join(ROOT, LLMs[0])
project_dirs = sorted([d for d in os.listdir(first_llm_path) if os.path.isdir(os.path.join(first_llm_path, d))])
common_fails = {}
print("=== 프로젝트별 공통 build_fail ===")
for proj in project_dirs:
    llm_files = [get_build_fail_files(llm, proj) for llm in LLMs]
    common_fails[proj] = len(set.intersection(*llm_files))
    print(f"  {proj}: {common_fails[proj]}")

# ── 저장 ──
save_results(LLMs, mean_vec, closest_distances, uniform_distances, common_fails)


import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
COLORS = {"GPT5": "#4C72B0", "claude": "#DD8452", "qwen2.5_coder_32b-8k": "#55A868"}


def plot_mean_dist(closest_distances):
    """1. 평균과의 거리 막대 그래프"""
    fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=False)
    fig.suptitle("Distance from Mean Vector (per LLM)", fontsize=14, fontweight="bold")

    for ax, (llm, (closest, distances)) in zip(axes, closest_distances.items()):
        projs = sorted(distances, key=distances.get)
        dists = [distances[p] for p in projs]
        colors = ["#E74C3C" if p == closest else COLORS[llm] for p in projs]

        bars = ax.barh(projs, dists, color=colors)
        ax.set_title(llm, fontsize=11)
        ax.set_xlabel("Euclidean Distance")
        ax.invert_yaxis()
        for bar, val in zip(bars, dists):
            ax.text(val + 0.3, bar.get_y() + bar.get_height() / 2,
                    f"{val:.2f}", va="center", fontsize=8)

    plt.tight_layout()
    plt.savefig("plot_mean_dist.png", dpi=150)
    plt.close()


def plot_uniform_dist(uniform_distances, llm_dirs):
    """2. 균등과의 거리 막대 그래프"""
    fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=False)
    fig.suptitle("Distance from Uniform Distribution (per LLM)", fontsize=14, fontweight="bold")

    for ax, llm in zip(axes, llm_dirs):
        llm_distances = {k.split("/")[1]: v for k, v in uniform_distances.items() if k.startswith(llm)}
        closest = min(llm_distances, key=llm_distances.get)
        projs = sorted(llm_distances, key=llm_distances.get)
        dists = [llm_distances[p] for p in projs]
        colors = ["#E74C3C" if p == closest else COLORS[llm] for p in projs]

        bars = ax.barh(projs, dists, color=colors)
        ax.set_title(llm, fontsize=11)
        ax.set_xlabel("Euclidean Distance")
        ax.invert_yaxis()
        for bar, val in zip(bars, dists):
            ax.text(val + 0.3, bar.get_y() + bar.get_height() / 2,
                    f"{val:.2f}", va="center", fontsize=8)

    plt.tight_layout()
    plt.savefig("plot_uniform_dist.png", dpi=150)
    plt.close()


def plot_stacked_bar(closest_distances, mean_vec):
    """3. 누적 바차트 - LLM별 최근접 프로젝트 vs 평균"""
    categories = list(mean_vec.index)
    cmap = plt.get_cmap("tab20")
    cat_colors = {cat: cmap(i / len(categories)) for i, cat in enumerate(categories)}

    fig, axes = plt.subplots(1, 3, figsize=(18, 6))
    fig.suptitle("Closest Project vs Mean Vector (Stacked Bar)", fontsize=14, fontweight="bold")

    for ax, (llm, (closest, distances)) in zip(axes, closest_distances.items()):
        proj_path = os.path.join(ROOT, llm, closest, TARGET_CSV)
        proj_vec = read_csv_as_series(proj_path, value_col="%Error")

        labels = ["Mean", closest]
        data = {
            "Mean": [mean_vec.get(c, 0) for c in categories],
            closest: [proj_vec.get(c, 0) for c in categories],
        }

        bottoms = [0, 0]
        for cat in categories:
            vals = [data[lb][categories.index(cat)] for lb in labels]
            ax.bar(labels, vals, bottom=bottoms, color=cat_colors[cat], label=cat, width=0.5)
            bottoms = [bottoms[i] + vals[i] for i in range(2)]

        ax.set_title(llm, fontsize=10)
        ax.set_ylabel("%Error")
        ax.set_ylim(0, 110)

    # 범례는 마지막 ax 오른쪽에
    handles = [mpatches.Patch(color=cat_colors[c], label=c) for c in categories]
    fig.legend(handles=handles, loc="center right", fontsize=7,
               bbox_to_anchor=(1.15, 0.5), title="Category")

    plt.tight_layout()
    plt.savefig("plot_stacked_bar.png", dpi=150, bbox_inches="tight")
    plt.close()



def plot_common_fails(common_fails, closest_distances):
    """4. 공통 build_fail 가로 막대 (로그 스케일)"""
    projs = list(common_fails.keys())
    counts = [common_fails[p] for p in projs]

    fig, ax = plt.subplots(figsize=(10, 6))
    bars = ax.barh(projs, counts, color="#7F7F7F")
    ax.set_xscale("log")
    ax.set_xlabel("Common build_fail count (log scale)")
    ax.set_title("Common build_fail across all LLMs", fontsize=13, fontweight="bold")
    ax.invert_yaxis()
    for bar, val in zip(bars, counts):
        ax.text(val * 1.05, bar.get_y() + bar.get_height() / 2,
                str(val), va="center", fontsize=9)

    plt.tight_layout()
    plt.savefig("plot_common_fails.png", dpi=150)
    plt.close()


def plot_scatter(closest_distances, uniform_distances, common_fails):
    """5. 산점도 - 레이블을 LLM명으로"""
    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    fig.suptitle("Scatter Analysis", fontsize=14, fontweight="bold")
    ax1, ax2 = axes

    for llm, (closest, distances) in closest_distances.items():
        llm_uniform = {k.split("/")[1]: v for k, v in uniform_distances.items() if k.startswith(llm)}
        color = COLORS[llm]

        for proj, dist in distances.items():
            fail = common_fails.get(proj, 0)
            uni = llm_uniform.get(proj, 0)
            proj_label = proj.split("_", 1)[1] if "_" in proj else proj  # "JsonBox", "re2" 등

            ax1.scatter(dist, fail, color=color, s=60, alpha=0.8)
            ax1.annotate(proj_label, (dist, fail), fontsize=7,
                         textcoords="offset points", xytext=(4, 2))

            ax2.scatter(dist, uni, color=color, s=60, alpha=0.8)
            ax2.annotate(proj_label, (dist, uni), fontsize=7,
                         textcoords="offset points", xytext=(4, 2))

    ax1.set_xlabel("Distance from Mean")
    ax1.set_ylabel("Common build_fail count (log)")
    ax1.set_yscale("log")
    ax1.set_title("Mean Distance vs Common Fails")

    ax2.set_xlabel("Distance from Mean")
    ax2.set_ylabel("Distance from Uniform")
    ax2.set_title("Mean Distance vs Uniform Distance")

    patches = [mpatches.Patch(color=COLORS[llm], label=llm) for llm in COLORS]
    fig.legend(handles=patches, loc="upper left", fontsize=9)

    plt.tight_layout()
    plt.savefig("plot_scatter.png", dpi=150)
    plt.close()


# ── 호출 ──
plot_mean_dist(closest_distances)
plot_uniform_dist(uniform_distances, LLMs)
plot_stacked_bar(closest_distances, mean_vec)
plot_common_fails(common_fails, closest_distances)
# plot_scatter(closest_distances, uniform_distances, common_fails)
print("시각화 완료: plot_mean_dist / plot_uniform_dist / plot_radar / plot_common_fails / plot_scatter")