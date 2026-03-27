// CairoOutputDev_StructParentsMcidHash_1737_test.cc
#include <climits>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "./TestProjects/poppler/poppler/CairoOutputDev.h"

namespace {

using Hash = CairoOutputDev::StructParentsMcidHash;
using Key = std::pair<int, int>;

struct PairEq {
  bool operator()(const Key &a, const Key &b) const { return a.first == b.first && a.second == b.second; }
};

TEST(CairoOutputDevStructParentsMcidHashTest_1737, DeterministicForSameInput_1737) {
  const Hash h{};
  const Key k{123, 456};

  const std::size_t v1 = h(k);
  const std::size_t v2 = h(k);
  const std::size_t v3 = h(k);

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST(CairoOutputDevStructParentsMcidHashTest_1737, WorksAsHasherInUnorderedSet_1737) {
  std::unordered_set<Key, Hash, PairEq> s;

  const Key a{0, 0};
  const Key b{1, 0};
  const Key c{0, 1};
  const Key d{42, 99};

  EXPECT_TRUE(s.insert(a).second);
  EXPECT_TRUE(s.insert(b).second);
  EXPECT_TRUE(s.insert(c).second);
  EXPECT_TRUE(s.insert(d).second);

  EXPECT_EQ(s.size(), 4u);

  EXPECT_NE(s.find(a), s.end());
  EXPECT_NE(s.find(b), s.end());
  EXPECT_NE(s.find(c), s.end());
  EXPECT_NE(s.find(d), s.end());
}

TEST(CairoOutputDevStructParentsMcidHashTest_1737, HandlesBoundaryIntValues_1737) {
  const Hash h{};

  const std::vector<Key> keys = {
      {0, 0},
      {INT_MAX, 0},
      {0, INT_MAX},
      {INT_MIN, 0},
      {0, INT_MIN},
      {INT_MAX, INT_MIN},
      {-1, -1},
  };

  // Black-box expectation: callable and stable per key.
  for (const auto &k : keys) {
    const std::size_t v1 = h(k);
    const std::size_t v2 = h(k);
    EXPECT_EQ(v1, v2);
  }

  // Also ensure these keys can be stored and found.
  std::unordered_set<Key, Hash, PairEq> s(keys.begin(), keys.end());
  EXPECT_EQ(s.size(), keys.size());
  for (const auto &k : keys) {
    EXPECT_NE(s.find(k), s.end());
  }
}

TEST(CairoOutputDevStructParentsMcidHashTest_1737, CollisionDoesNotBreakLookupIfItOccurs_1737) {
  const Hash h{};

  // Try to *find* a collision in a small domain without assuming anything about the hash.
  // If we find one, verify unordered containers still behave correctly (distinct keys remain distinct).
  std::unordered_map<std::size_t, Key> seen;
  Key k1{0, 0}, k2{0, 0};
  bool found_collision = false;

  for (int a = 0; a < 512 && !found_collision; ++a) {
    for (int b = 0; b < 512 && !found_collision; ++b) {
      const Key k{a, b};
      const std::size_t hv = h(k);
      auto it = seen.find(hv);
      if (it != seen.end() && !(PairEq{}(it->second, k))) {
        k1 = it->second;
        k2 = k;
        found_collision = true;
      } else {
        seen.emplace(hv, k);
      }
    }
  }

  if (!found_collision) {
    SUCCEED() << "No collision found in the sampled domain; skipping collision-specific assertions.";
    return;
  }

  std::unordered_set<Key, Hash, PairEq> s;
  EXPECT_TRUE(s.insert(k1).second);
  EXPECT_TRUE(s.insert(k2).second);
  EXPECT_EQ(s.size(), 2u);

  EXPECT_NE(s.find(k1), s.end());
  EXPECT_NE(s.find(k2), s.end());
}

}  // namespace