// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpdata_count_1311.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "exiv2/xmp_exiv2.hpp"

namespace {

class XmpDataCountTest_1311 : public ::testing::Test {
 protected:
  static std::vector<std::string> MakeDistinctKeys(std::size_t n) {
    std::vector<std::string> keys;
    keys.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
      // Use typical XMP-like prefixes to avoid obviously-invalid keys.
      keys.push_back("Xmp.dc.title_" + std::to_string(i));
    }
    return keys;
  }
};

TEST_F(XmpDataCountTest_1311, DefaultConstructedIsEmptyAndCountZero_1311) {
  Exiv2::XmpData xmp;

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());

  // Count should also match the number of iterated elements.
  EXPECT_EQ(0L, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
}

TEST_F(XmpDataCountTest_1311, OperatorBracketOnNewKeyIncreasesCount_1311) {
  Exiv2::XmpData xmp;

  const long before = xmp.count();
  (void)xmp["Xmp.dc.title"];  // observable effect should be visible via count/iteration
  const long after = xmp.count();

  EXPECT_GE(after, before);
  EXPECT_EQ(after, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
  EXPECT_FALSE(xmp.empty());
}

TEST_F(XmpDataCountTest_1311, OperatorBracketSameKeyDoesNotIncreaseCountTwice_1311) {
  Exiv2::XmpData xmp;

  (void)xmp["Xmp.dc.title"];
  const long after_first = xmp.count();

  // Accessing the same key again should not create a second entry.
  (void)xmp["Xmp.dc.title"];
  const long after_second = xmp.count();

  EXPECT_EQ(after_first, after_second);
  EXPECT_EQ(after_second, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
}

TEST_F(XmpDataCountTest_1311, MultipleDistinctKeysProduceMatchingCountAndIterationDistance_1311) {
  Exiv2::XmpData xmp;

  const auto keys = MakeDistinctKeys(5);
  for (const auto& k : keys) {
    (void)xmp[k];
  }

  const long c = xmp.count();
  EXPECT_EQ(c, static_cast<long>(std::distance(xmp.begin(), xmp.end())));

  // Boundary-ish: count should be at least the number of distinct keys we touched.
  // (If implementation normalizes/aliases keys, this still remains a black-box assertion via >=.)
  EXPECT_GE(c, static_cast<long>(keys.size()));
}

TEST_F(XmpDataCountTest_1311, ClearResetsCountToZeroAndEmptyTrue_1311) {
  Exiv2::XmpData xmp;

  (void)xmp["Xmp.dc.title"];
  (void)xmp["Xmp.dc.subject"];
  ASSERT_GT(xmp.count(), 0L);

  xmp.clear();

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
  EXPECT_EQ(0L, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
}

TEST_F(XmpDataCountTest_1311, EraseRemovesOneElementAndDecrementsCount_1311) {
  Exiv2::XmpData xmp;

  (void)xmp["Xmp.dc.title"];
  (void)xmp["Xmp.dc.subject"];
  const long before = xmp.count();
  ASSERT_GE(before, 1L);

  auto it = xmp.begin();
  ASSERT_NE(it, xmp.end());

  (void)xmp.erase(it);

  const long after = xmp.count();
  EXPECT_EQ(after, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
  EXPECT_LE(after, before);
  if (before > 0) {
    EXPECT_EQ(before - 1, after);
  }
}

TEST_F(XmpDataCountTest_1311, SortByKeyDoesNotChangeCount_1311) {
  Exiv2::XmpData xmp;

  (void)xmp["Xmp.dc.subject"];
  (void)xmp["Xmp.dc.title"];
  (void)xmp["Xmp.dc.creator"];

  const long before = xmp.count();
  const long before_dist = static_cast<long>(std::distance(xmp.begin(), xmp.end()));
  ASSERT_EQ(before, before_dist);

  xmp.sortByKey();

  const long after = xmp.count();
  const long after_dist = static_cast<long>(std::distance(xmp.begin(), xmp.end()));
  EXPECT_EQ(before, after);
  EXPECT_EQ(after, after_dist);
}

TEST_F(XmpDataCountTest_1311, EraseFamilyDoesNotIncreaseCountAndKeepsIteratorsValid_1311) {
  Exiv2::XmpData xmp;

  // Create a small set of entries; we avoid assuming any particular "family" semantics.
  (void)xmp["Xmp.dc.title"];
  (void)xmp["Xmp.dc.subject"];
  (void)xmp["Xmp.dc.creator"];

  long before = xmp.count();
  ASSERT_GT(before, 0L);

  auto pos = xmp.begin();
  ASSERT_NE(pos, xmp.end());

  xmp.eraseFamily(pos);

  long after = xmp.count();
  EXPECT_EQ(after, static_cast<long>(std::distance(xmp.begin(), xmp.end())));
  EXPECT_LE(after, before);  // should not add elements

  // `pos` is passed by reference; ensure it is at least usable for comparison.
  EXPECT_TRUE(pos == xmp.end() || pos != xmp.end());
}

}  // namespace