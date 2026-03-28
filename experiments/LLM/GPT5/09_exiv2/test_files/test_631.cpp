// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::IptcDataSets::dataSetTitle
//
// File under test: ./TestProjects/exiv2/src/datasets.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

#include <exiv2/datasets.hpp>

namespace {

// IPTC IIM record ids (stable / standardized)
constexpr uint16_t kEnvelopeRecordId = 1;
constexpr uint16_t kApplication2RecordId = 2;

// Defensive iteration over DataSet lists (they are typically C-arrays with a sentinel).
// We stop if title_ is null OR number_ is 0, or after a hard cap to avoid runaway loops.
template <typename Fn>
void ForEachDataSetCapped(const Exiv2::DataSet* list, Fn&& fn, size_t hard_cap = 256) {
  ASSERT_NE(list, nullptr);
  for (size_t i = 0; i < hard_cap; ++i) {
    const Exiv2::DataSet& ds = list[i];
    if (ds.title_ == nullptr || ds.number_ == 0) break;
    fn(ds, i);
  }
}

}  // namespace

class IptcDataSetsTest_631 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_631, ReturnsUnknownForClearlyInvalidRecordId_631) {
  // Boundary/exceptional: recordId out of expected IPTC range.
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 1, /*recordId*/ 0));
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 1, /*recordId*/ 9999));
}

TEST_F(IptcDataSetsTest_631, ReturnsUnknownForUnlikelyDataSetNumbers_631) {
  // Boundary numbers that are very unlikely to be valid dataset numbers in standard records.
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 0, kEnvelopeRecordId));
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 65535, kEnvelopeRecordId));
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 0, kApplication2RecordId));
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(/*number*/ 65535, kApplication2RecordId));
}

TEST_F(IptcDataSetsTest_631, EnvelopeRecordListTitlesMatchDataSetTitle_631) {
  // Normal operation: for datasets listed in the envelope record list,
  // dataSetTitle(number, envelopeRecordId) should match the list's title.
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
  ForEachDataSetCapped(list, [](const Exiv2::DataSet& ds, size_t /*i*/) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(ds.number_, kEnvelopeRecordId);
    ASSERT_NE(title, nullptr);
    ASSERT_NE(ds.title_, nullptr);
    EXPECT_STREQ(ds.title_, title);
  });
}

TEST_F(IptcDataSetsTest_631, Application2RecordListTitlesMatchDataSetTitle_631) {
  // Normal operation: for datasets listed in the Application2 record list,
  // dataSetTitle(number, application2RecordId) should match the list's title.
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ForEachDataSetCapped(list, [](const Exiv2::DataSet& ds, size_t /*i*/) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(ds.number_, kApplication2RecordId);
    ASSERT_NE(title, nullptr);
    ASSERT_NE(ds.title_, nullptr);
    EXPECT_STREQ(ds.title_, title);
  });
}

TEST_F(IptcDataSetsTest_631, UnknownDataSetNumberInRecordReturnsUnknown_631) {
  // Boundary: pick a dataset number that is not present in the known list (best-effort).
  // We select a number outside common IPTC dataset number ranges and verify "Unknown dataset".
  // (We avoid assuming any internal indexing / storage.)
  constexpr uint16_t kVeryUnlikelyNumber = 65000;

  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(kVeryUnlikelyNumber, kEnvelopeRecordId));
  EXPECT_STREQ("Unknown dataset", Exiv2::IptcDataSets::dataSetTitle(kVeryUnlikelyNumber, kApplication2RecordId));
}