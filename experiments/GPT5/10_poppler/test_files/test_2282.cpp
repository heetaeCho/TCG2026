// CairoOutputDev_StructParentsMcidHash_test_2282.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "poppler/CairoOutputDev.h"

namespace {

using Hash = CairoOutputDev::StructParentsMcidHash;

TEST(CairoOutputDevStructParentsMcidHashTest_2282, ReturnsSizeT_2282) {
  Hash h;
  const std::pair<int, int> p{0, 0};
  static_assert(std::is_same_v<decltype(h(p)), size_t>,
                "operator() must return size_t");
  (void)h(p);
}

TEST(CairoOutputDevStructParentsMcidHashTest_2282, DeterministicForSameInput_2282) {
  Hash h;
  const std::pair<int, int> p{123, 456};
  const size_t a = h(p);
  const size_t b = h(p);
  const size_t c = h(p);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(CairoOutputDevStructParentsMcidHashTest_2282, MatchesExpectedTypicalValues_2282) {
  Hash h;

  // Choose non-negative values where shifts and bitwise ops are well-defined.
  const std::pair<int, int> p{1, 2};
  const size_t got = h(p);

  // Expected result for these safe inputs.
  const size_t expected =
      static_cast<size_t>((static_cast<uint32_t>(p.first) << 16) |
                          static_cast<uint32_t>(p.second));

  EXPECT_EQ(got, expected);
}

TEST(CairoOutputDevStructParentsMcidHashTest_2282, MatchesExpectedBoundaryValues_2282) {
  Hash h;

  // Boundaries that remain safe on typical 32-bit int representations.
  const std::pair<int, int> p1{0, 0};
  const std::pair<int, int> p2{0x7FFF, 0xFFFF};  // 0x7FFF0000 | 0x0000FFFF

  const size_t got1 = h(p1);
  const size_t exp1 =
      static_cast<size_t>((static_cast<uint32_t>(p1.first) << 16) |
                          static_cast<uint32_t>(p1.second));
  EXPECT_EQ(got1, exp1);

  const size_t got2 = h(p2);
  const size_t exp2 =
      static_cast<size_t>((static_cast<uint32_t>(p2.first) << 16) |
                          static_cast<uint32_t>(p2.second));
  EXPECT_EQ(got2, exp2);
}

TEST(CairoOutputDevStructParentsMcidHashTest_2282, UsableInUnorderedMapForLookup_2282) {
  // Verifies external usability: can be used as a hash functor in unordered_map.
  std::unordered_map<std::pair<int, int>, int, Hash> m;

  const std::pair<int, int> k1{10, 20};
  const std::pair<int, int> k2{30, 40};

  m.emplace(k1, 111);
  m.emplace(k2, 222);

  auto it1 = m.find(k1);
  ASSERT_NE(it1, m.end());
  EXPECT_EQ(it1->second, 111);

  auto it2 = m.find(k2);
  ASSERT_NE(it2, m.end());
  EXPECT_EQ(it2->second, 222);

  const std::pair<int, int> missing{99, 100};
  EXPECT_EQ(m.find(missing), m.end());
}

}  // namespace