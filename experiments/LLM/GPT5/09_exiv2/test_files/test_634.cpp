// File: test_IptcDataSets_repeatable_634.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

using Exiv2::DataSet;
using Exiv2::IptcDataSets;

constexpr uint16_t kRecordEnvelope = 1;
constexpr uint16_t kRecordApplication2 = 2;

const DataSet* pickRecordList(uint16_t recordId) {
  switch (recordId) {
    case kRecordEnvelope:
      return IptcDataSets::envelopeRecordList();
    case kRecordApplication2:
      return IptcDataSets::application2RecordList();
    default:
      return nullptr;
  }
}

// Heuristic list iteration: Exiv2 tables are typically terminated with a sentinel.
// We stay safe by using BOTH a max-iteration cap and a sentinel check.
bool isLikelySentinel(const DataSet& ds) {
  // "Unknown dataset" (65535) is used as a global sentinel in Exiv2 IPTC tables.
  // We keep the condition permissive (number_==65535) to avoid hard dependency on strings.
  return ds.number_ == 65535;
}

}  // namespace

class IptcDataSetsTest_634 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_634, UnknownDataSetReturnsRepeatableTrue_634) {
  // For an unknown dataset (idx == -1), implementation returns unknownDataSet.repeatable_.
  // In Exiv2 this is observable as "Unknown dataset" and repeatable == true.
  const uint16_t badNumber = 65000;  // unlikely to be a valid IPTC dataset number
  const uint16_t recordId = kRecordApplication2;

  bool repeatable = false;
  ASSERT_NO_THROW(repeatable = IptcDataSets::dataSetRepeatable(badNumber, recordId));
  EXPECT_TRUE(repeatable);

  // If title is exposed, it should resolve to "Unknown dataset" for unknown entries.
  const char* title = nullptr;
  ASSERT_NO_THROW(title = IptcDataSets::dataSetTitle(badNumber, recordId));
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_634, MatchesRepeatableFlagForKnownEnvelopeEntries_634) {
  const uint16_t recordId = kRecordEnvelope;
  const DataSet* list = pickRecordList(recordId);
  ASSERT_NE(list, nullptr);

  // Verify: for known entries, dataSetRepeatable(number, recordId) matches the table's repeatable_.
  // This uses only public API + returned public DataSet fields (observable surface).
  bool sawAny = false;

  for (size_t i = 0; i < 2048; ++i) {
    const DataSet& ds = list[i];
    if (isLikelySentinel(ds)) break;

    sawAny = true;

    bool repeatable = false;
    ASSERT_NO_THROW(repeatable = IptcDataSets::dataSetRepeatable(ds.number_, recordId))
        << "Index i=" << i << " dataset number=" << ds.number_;
    EXPECT_EQ(repeatable, ds.repeatable_) << "Index i=" << i << " dataset number=" << ds.number_;
  }

  EXPECT_TRUE(sawAny);
}

TEST_F(IptcDataSetsTest_634, MatchesRepeatableFlagForKnownApplication2Entries_634) {
  const uint16_t recordId = kRecordApplication2;
  const DataSet* list = pickRecordList(recordId);
  ASSERT_NE(list, nullptr);

  bool sawAny = false;

  for (size_t i = 0; i < 4096; ++i) {
    const DataSet& ds = list[i];
    if (isLikelySentinel(ds)) break;

    sawAny = true;

    bool repeatable = false;
    ASSERT_NO_THROW(repeatable = IptcDataSets::dataSetRepeatable(ds.number_, recordId))
        << "Index i=" << i << " dataset number=" << ds.number_;
    EXPECT_EQ(repeatable, ds.repeatable_) << "Index i=" << i << " dataset number=" << ds.number_;
  }

  EXPECT_TRUE(sawAny);
}

TEST_F(IptcDataSetsTest_634, BoundaryDatasetNumberDoesNotCrashAndReturnsBool_634) {
  const uint16_t recordId = kRecordApplication2;

  // Boundary-ish values for dataset number.
  const uint16_t numbers[] = {0u, 1u, 255u, 32767u, 65534u, std::numeric_limits<uint16_t>::max()};

  for (uint16_t n : numbers) {
    bool repeatable = false;
    ASSERT_NO_THROW(repeatable = IptcDataSets::dataSetRepeatable(n, recordId))
        << "dataset number=" << n;
    // Must return a boolean; no stronger assertion without assuming the mapping.
    (void)repeatable;
  }
}

TEST_F(IptcDataSetsTest_634, BoundaryRecordIdDoesNotCrashForUnknownDataset_634) {
  // Even if recordId is out-of-range, the API should not crash for an unknown dataset
  // (error case observable through "no-throw" / safe boolean return).
  const uint16_t badNumber = 65000;

  const uint16_t recordIds[] = {
      0u,
      kRecordEnvelope,
      kRecordApplication2,
      3u,
      100u,
      std::numeric_limits<uint16_t>::max(),
  };

  for (uint16_t recordId : recordIds) {
    bool repeatable = false;
    EXPECT_NO_THROW(repeatable = IptcDataSets::dataSetRepeatable(badNumber, recordId))
        << "recordId=" << recordId;
    // For unknown dataset number, result should be the "unknown dataset" repeatable (true).
    // If implementation treats invalid recordId differently, this test will surface it.
    EXPECT_TRUE(repeatable) << "recordId=" << recordId;
  }
}