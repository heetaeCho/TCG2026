// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptc_sortbykey_698.cpp
//
// Unit tests for Exiv2::IptcData::sortByKey()
// TEST_ID: 698

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/iptc.hpp"
#include "exiv2/value.hpp"

namespace {

class IptcDataTest_698 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeStringValue(const std::string& s) {
    // Exiv2::Value::create(...) returns a heap object; IptcData::add(const Value*)
    // is expected to clone/copy the passed value (observable via successful add
    // without requiring ownership transfer).
    std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::string));
    if (v) v->read(s);
    return v;
  }

  static std::vector<std::string> CollectKeys(Exiv2::IptcData& data) {
    std::vector<std::string> keys;
    for (auto it = data.begin(); it != data.end(); ++it) {
      keys.push_back(it->key());
    }
    return keys;
  }

  static bool IsNonDecreasing(const std::vector<std::string>& keys) {
    return std::is_sorted(keys.begin(), keys.end());
  }
};

}  // namespace

TEST_F(IptcDataTest_698, SortByKey_EmptyNoChange_698) {
  Exiv2::IptcData data;
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data.size(), 0u);

  // Should be safe on empty containers.
  EXPECT_NO_THROW(data.sortByKey());

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.size(), 0u);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(IptcDataTest_698, SortByKey_SingleElementNoChange_698) {
  Exiv2::IptcData data;

  const Exiv2::IptcKey key("Iptc.Application2.Caption");
  auto v = MakeStringValue("caption");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(0, data.add(key, v.get()));

  ASSERT_EQ(data.size(), 1u);

  const auto before = CollectKeys(data);
  ASSERT_EQ(before.size(), 1u);

  EXPECT_NO_THROW(data.sortByKey());

  const auto after = CollectKeys(data);
  ASSERT_EQ(after.size(), 1u);
  EXPECT_EQ(after[0], before[0]);
}

TEST_F(IptcDataTest_698, SortByKey_MultipleElementsOrdersByKey_698) {
  Exiv2::IptcData data;

  // Insert out-of-order keys.
  {
    auto v = MakeStringValue("v1");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Application2.Headline"), v.get()));
  }
  {
    auto v = MakeStringValue("v2");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Envelope.CharacterSet"), v.get()));
  }
  {
    auto v = MakeStringValue("v3");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Application2.Caption"), v.get()));
  }

  ASSERT_EQ(data.size(), 3u);

  const auto beforeKeys = CollectKeys(data);
  ASSERT_EQ(beforeKeys.size(), 3u);

  EXPECT_NO_THROW(data.sortByKey());

  const auto afterKeys = CollectKeys(data);
  ASSERT_EQ(afterKeys.size(), 3u);

  // Observable behavior: after sortByKey(), iteration order should be non-decreasing by key().
  EXPECT_TRUE(IsNonDecreasing(afterKeys));

  // Boundary/robustness: sorting should not add/drop items (multiset of keys preserved).
  auto sortedBefore = beforeKeys;
  auto sortedAfter = afterKeys;
  std::sort(sortedBefore.begin(), sortedBefore.end());
  std::sort(sortedAfter.begin(), sortedAfter.end());
  EXPECT_EQ(sortedAfter, sortedBefore);
}

TEST_F(IptcDataTest_698, SortByKey_DuplicateKeysPreservedAndAdjacentInSortedOrder_698) {
  Exiv2::IptcData data;

  // Add duplicates + another key.
  {
    auto v = MakeStringValue("a1");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Application2.Caption"), v.get()));
  }
  {
    auto v = MakeStringValue("a2");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Application2.Caption"), v.get()));
  }
  {
    auto v = MakeStringValue("b");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(0, data.add(Exiv2::IptcKey("Iptc.Application2.Headline"), v.get()));
  }

  ASSERT_EQ(data.size(), 3u);

  const auto beforeKeys = CollectKeys(data);
  ASSERT_EQ(beforeKeys.size(), 3u);

  EXPECT_NO_THROW(data.sortByKey());

  const auto afterKeys = CollectKeys(data);
  ASSERT_EQ(afterKeys.size(), 3u);

  EXPECT_TRUE(IsNonDecreasing(afterKeys));

  // Duplicates should remain (key multiset preserved).
  auto sortedBefore = beforeKeys;
  auto sortedAfter = afterKeys;
  std::sort(sortedBefore.begin(), sortedBefore.end());
  std::sort(sortedAfter.begin(), sortedAfter.end());
  EXPECT_EQ(sortedAfter, sortedBefore);

  // In a sorted-by-key sequence, equal keys must appear contiguously (adjacent).
  const std::string dup = "Iptc.Application2.Caption";
  std::vector<size_t> positions;
  for (size_t i = 0; i < afterKeys.size(); ++i) {
    if (afterKeys[i] == dup) positions.push_back(i);
  }
  ASSERT_EQ(positions.size(), 2u);
  EXPECT_EQ(positions[1], positions[0] + 1u);
}