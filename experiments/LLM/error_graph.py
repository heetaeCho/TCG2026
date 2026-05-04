import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ===== 1. 파일 로드 =====
# 순서: Claude, GPT, Qwen
claude = pd.read_csv("claude/error.csv")
gpt = pd.read_csv("GPT5/error.csv")
qwen = pd.read_csv("qwen2.5_coder_32b-8k/error.csv")

# ===== 2. 첫 번째 컬럼 제거 =====
claude = claude.iloc[:, 1:]
gpt = gpt.iloc[:, 1:]
qwen = qwen.iloc[:, 1:]

claude.columns = ["category", "count", "ratio"]
gpt.columns = ["category", "count", "ratio"]
qwen.columns = ["category", "count", "ratio"]

claude["model"] = "Claude"
gpt["model"] = "GPT5"
qwen["model"] = "Qwen"

# =========================
# 3. Top-level mapping
# =========================
def map_top_category(cat):
    c = cat.lower()
    if "lex" in c:
        return "Lexical"
    elif "parse" in c or "syntac" in c:
        return "Syntactic"
    elif "link" in c:
        return "Linker"
    else:
        return "Semantic"

# =========================
# Figure 1: Top-level
# =========================

df = pd.concat([claude, gpt, qwen], ignore_index=True)
df["count"] = pd.to_numeric(df["count"], errors="coerce")
df["top_category"] = df["category"].apply(map_top_category)

df_fig1 = df.copy()

pivot_fig1 = df_fig1.pivot_table(
    index="model",
    columns="top_category",
    values="count",
    aggfunc="sum"
).fillna(0)

# 비율 변환
pivot_fig1 = pivot_fig1.div(pivot_fig1.sum(axis=1), axis=0)

colors_fig1 = [
    "#4C72B0",  # Lexical (파랑)
    "#55A868",  # Syntactic (초록)
    "#C44E52",  # Linker (빨강)
    "#8172B2"   # Semantic (보라)
]

# Plot
pivot_fig1.plot(kind="bar", stacked=True, color=colors_fig1)

plt.title("Top-level Error Distribution")
plt.ylabel("Proportion")
plt.xlabel("Model")

plt.legend(bbox_to_anchor=(1.05, 1), loc="upper left")
plt.tight_layout()
#plt.show()
plt.savefig("figure1_top_level.png", dpi=300, bbox_inches="tight")
plt.close()

# =========================
# Figure 2: "Semantic" row 제거
# =========================

# 1️⃣ Semantic row 제거
df_fig2 = df[df["category"] != "Semantic"].copy()

# 2️⃣ 전체 기준 Top-N 선택
total = df_fig2.groupby("category")["count"].sum().sort_values(ascending=False)

cum_ratio = total.cumsum() / total.sum()

top_categories = cum_ratio[cum_ratio <= 0.8].index.tolist()

# 경계 하나 더 포함
if len(top_categories) < len(total):
    top_categories.append(cum_ratio.index[len(top_categories)])

# 3️⃣ Others 처리
df_fig2["category_grouped"] = df_fig2["category"].apply(
    lambda x: x if x in top_categories else "Others"
)

# 4️⃣ Pivot
pivot_fig2 = df_fig2.pivot_table(
    index="model",
    columns="category_grouped",
    values="count",
    aggfunc="sum"
).fillna(0)

# 5️⃣ 비율 변환
pivot_fig2 = pivot_fig2.div(pivot_fig2.sum(axis=1), axis=0)

# 6️⃣ 컬럼 순서 정렬 (빈도 기준)
ordered_cols = total.index.tolist()
ordered_cols = [c for c in ordered_cols if c in pivot_fig2.columns]

if "Others" in pivot_fig2.columns:
    ordered_cols.append("Others")

pivot_fig2 = pivot_fig2[ordered_cols]

categories = pivot_fig2.columns.tolist()

# 색 생성 (colormap 활용)
cmap = plt.cm.tab20  # 논문용 무난
colors = cmap(np.linspace(0, 1, len(categories)))

# Others는 회색으로 덮기
colors = list(colors)
for i, cat in enumerate(categories):
    if cat == "Others":
        colors[i] = "#BBBBBB"

# 7️⃣ Plot
pivot_fig2.plot(
    kind="bar",
    stacked=True,
    color=colors,
    edgecolor="black",
    linewidth=0.3
)

plt.legend(
    bbox_to_anchor=(1.05, 1),
    loc="upper left",
    fontsize=8
)

# 전체 기준 순서
ordered_cols = total.sort_values(ascending=False).index.tolist()

# pivot에 존재하는 것만 필터
ordered_cols = [c for c in ordered_cols if c in pivot_fig2.columns]

# Others는 항상 맨 위
if "Others" in pivot_fig2.columns:
    ordered_cols.append("Others")

# 순서 적용
pivot_fig2 = pivot_fig2[ordered_cols]


plt.title("Error Distribution (Top Categories, Semantic Removed)")
plt.ylabel("Proportion")
plt.xlabel("Model")

plt.legend(bbox_to_anchor=(1.05, 1), loc="upper left")
plt.tight_layout()
# plt.show()

plt.savefig("figure2_semantic_breakdown.png", dpi=300, bbox_inches="tight")
plt.close()
