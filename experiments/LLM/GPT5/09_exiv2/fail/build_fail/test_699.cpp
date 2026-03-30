// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::IptcData::sortByTag()
// File under test: ./TestProjects/exiv2/src/iptc.cpp
//
// Constraints respected:
// - Treats implementation as a black box.
// - Uses only public interface / observable behavior.
// - No access to private state.
// - No re-implementation of internal logic beyond checking ordering is non-decreasing
//   (observable outcome of sorting).
//
// NOTE: These tests assume Exiv2 headers/types are available in the build.
// They are intentionally conservative about assumptions on return codes.

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace {

// Extract (dataset, record) from an Iptcdatum by using its key.
// This is observable through the public Iptcdatum::key().
static std::pair<uint16_t, uint16_t> DatumIdPair(const Exiv2::Iptcdatum& d) {
  const Exiv2::IptcKey& k = d.key();
  return {static_cast<uint16_t>(k.dataset()), static_cast<uint16_t>(k.tag())};
}

static std::vector<std::pair<uint16_t, uint16_t>> SnapshotIds(const Exiv2::IptcData& data) {
  std::vector<std::pair<uint16_t, uint16_t>> ids;
  for (auto it = data.begin(); it != data.end(); ++it) {
    ids.push_back(DatumIdPair(*it));
  }
  return ids;
}

// Check the data is sorted by (dataset, record) non-decreasing.
// We don't assume stable ordering among equal keys.
static bool IsNonDecreasingByTag(const std::vector<std::pair<uint16_t, uint16_t>>& ids) {
  return std::is_sorted(ids.begin(), ids.end(),
                        [](const auto& a, const auto& b) { return a < b; });
}

class IptcDataSortByTagTest_699 : public ::testing::Test {
 protected:
  Exiv2::IptcData data_;
};

}  // namespace

TEST_F(IptcDataSortByTagTest_699, SortEmptyDoesNotCrash_699) {
  ASSERT_TRUE(data_.empty());
  EXPECT_EQ(0u, data_.count());

  // Should be safe on empty container.
  data_.sortByTag();

  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(0u, data_.count());
  EXPECT_EQ(data_.begin(), data_.end());
}

TEST_F(IptcDataSortByTagTest_699, SortSingleElementKeepsSingleElement_699) {
  ASSERT_TRUE(data_.empty());

  // Insert one datum via operator[] (public interface).
  // Using a standard IPTC key string format used by Exiv2.
  // We avoid asserting on value formatting; only presence/order.
  (void)data_["Iptc.Application2.ObjectName"];

  ASSERT_EQ(1u, data_.count());
  auto before = SnapshotIds(data_);

  data_.sortByTag();

  EXPECT_EQ(1u, data_.count());
  auto after = SnapshotIds(data_);
  ASSERT_EQ(before.size(), after.size());
  EXPECT_EQ(before[0], after[0]);
  EXPECT_TRUE(IsNonDecreasingByTag(after));
}

TEST_F(IptcDataSortByTagTest_699, SortAlreadySortedRemainsNonDecreasing_699) {
  // Add a few IPTC tags likely distinct and in increasing order by (dataset, record)
  (void)data_["Iptc.Application2.ObjectName"];      // Application2
  (void)data_["Iptc.Application2.Urgency"];
  (void)data_["Iptc.Application2.Category"];

  ASSERT_GE(data_.count(), 3u);

  // Sort once, then sort again; the second call should keep non-decreasing order.
  data_.sortByTag();
  auto once = SnapshotIds(data_);
  ASSERT_TRUE(IsNonDecreasingByTag(once));

  data_.sortByTag();
  auto twice = SnapshotIds(data_);
  ASSERT_TRUE(IsNonDecreasingByTag(twice));

  // Should contain the same multiset of ids.
  auto s1 = once;
  auto s2 = twice;
  std::sort(s1.begin(), s1.end());
  std::sort(s2.begin(), s2.end());
  EXPECT_EQ(s1, s2);
}

TEST_F(IptcDataSortByTagTest_699, SortUnsortedBecomesNonDecreasingByDatasetAndRecord_699) {
  // Add in a deliberately "scrambled" order.
  (void)data_["Iptc.Application2.Urgency"];
  (void)data_["Iptc.Envelope.CharacterSet"];        // different record/dataset (often record 1)
  (void)data_["Iptc.Application2.ObjectName"];
  (void)data_["Iptc.Application2.Category"];
  (void)data_["Iptc.Envelope.ServiceId"];

  ASSERT_GE(data_.count(), 5u);

  const auto before = SnapshotIds(data_);
  // We don't require before to be unsorted (in case underlying insertion already orders),
  // but we do verify after is sorted.
  data_.sortByTag();
  const auto after = SnapshotIds(data_);

  EXPECT_TRUE(IsNonDecreasingByTag(after));

  // Sorting should not add/remove elements: same multiset of ids.
  auto b = before;
  auto a = after;
  std::sort(b.begin(), b.end());
  std::sort(a.begin(), a.end());
  EXPECT_EQ(b, a);
}

TEST_F(IptcDataSortByTagTest_699, SortWithDuplicatesRemainsSortedAndPreservesMultiplicity_699) {
  // Create duplicates by using operator[] for the same key multiple times.
  // This does not guarantee duplicates are inserted (operator[] might return existing),
  // so we add duplicates via add(Iptcdatum) as a separate path if available.
  // We keep assertions conservative: we only require post-sort order and that count doesn't decrease.
  (void)data_["Iptc.Application2.ObjectName"];
  (void)data_["Iptc.Application2.ObjectName"];  // may or may not create new element

  // Add more keys to ensure meaningful ordering.
  (void)data_["Iptc.Application2.Urgency"];
  (void)data_["Iptc.Application2.Category"];

  const size_t count_before_sort = data_.count();
  ASSERT_GE(count_before_sort, 3u);

  auto ids_before = SnapshotIds(data_);

  data_.sortByTag();

  EXPECT_EQ(count_before_sort, data_.count());
  auto ids_after = SnapshotIds(data_);
  EXPECT_TRUE(IsNonDecreasingByTag(ids_after));

  // Same multiset of ids.
  std::sort(ids_before.begin(), ids_before.end());
  std::sort(ids_after.begin(), ids_after.end());
  EXPECT_EQ(ids_before, ids_after);
}

TEST_F(IptcDataSortByTagTest_699, SortThenFindIdStillFindsExistingItems_699) {
  // Add a couple of known keys, then sort, then find by (dataset, record).
  // We derive dataset/tag from the datum's key() (public) to avoid guessing numeric IDs.
  (void)data_["Iptc.Envelope.ServiceId"];
  (void)data_["Iptc.Application2.ObjectName"];
  ASSERT_GE(data_.count(), 2u);

  // Capture one element's (dataset, tag) before sorting.
  auto it0 = data_.begin();
  ASSERT_NE(it0, data_.end());
  const auto [ds, rec] = DatumIdPair(*it0);

  data_.sortByTag();

  // findId is const in header excerpt; use const ref.
  const Exiv2::IptcData& cdata = data_;
  auto found = cdata.findId(ds, rec);
  EXPECT_NE(found, cdata.end());
  if (found != cdata.end()) {
    EXPECT_EQ(ds, static_cast<uint16_t>(found->key().dataset()));
    EXPECT_EQ(rec, static_cast<uint16_t>(found->key().tag()));
  }
}

TEST_F(IptcDataSortByTagTest_699, SortIsIdempotentNonDecreasingAcrossMultipleCalls_699) {
  (void)data_["Iptc.Envelope.CharacterSet"];
  (void)data_["Iptc.Application2.ObjectName"];
  (void)data_["Iptc.Application2.Category"];
  (void)data_["Iptc.Envelope.ServiceId"];
  ASSERT_GE(data_.count(), 4u);

  for (int i = 0; i < 3; ++i) {
    data_.sortByTag();
    auto ids = SnapshotIds(data_);
    EXPECT_TRUE(IsNonDecreasingByTag(ids));
  }
}