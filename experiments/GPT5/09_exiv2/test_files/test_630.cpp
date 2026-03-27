// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatasets_630.cpp
//
// Unit tests for Exiv2::IptcDataSets (datasets.cpp / datasets.hpp)
//
// Constraints respected:
// - Treat implementation as a black box
// - Test only via public interface and observable behavior
// - No private state access, no internal logic reimplementation

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

bool LooksLikeHexDatasetName(const std::string& s) {
  // datasets.cpp uses stringFormat("0x{:04x}", number) => e.g. "0x1234"
  return s.size() == 6 && s.rfind("0x", 0) == 0;
}

}  // namespace

namespace Exiv2 {

class IptcDataSetsTest_630 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_630, UnknownNumberFormatsAsHex_630) {
  // Choose a number extremely unlikely to exist as a real dataset number.
  const uint16_t number = 0x1234;

  // Use common recordIds (0/1/2) to avoid any risk of out-of-range record indexing.
  EXPECT_EQ(IptcDataSets::dataSetName(number, 0), "0x1234");
  EXPECT_EQ(IptcDataSets::dataSetName(number, 1), "0x1234");
  EXPECT_EQ(IptcDataSets::dataSetName(number, 2), "0x1234");
}

TEST_F(IptcDataSetsTest_630, UnknownNumberBoundaryZeroFormatsAsHex_630) {
  // Boundary-ish input: 0x0000 should still format to 4 hex digits if unknown.
  const uint16_t number = 0x0000;

  const std::string name = IptcDataSets::dataSetName(number, 2);
  // If 0x0000 ever becomes a valid dataset, this assertion would fail; that would be a
  // meaningful behavior change (no longer "unknown"), so we keep it strict.
  EXPECT_EQ(name, "0x0000");
}

TEST_F(IptcDataSetsTest_630, KnownDatasetRoundTripsThroughNameAndLookup_630) {
  // We attempt to obtain a known dataset from the published record lists.
  // This avoids hardcoding specific dataset numbers/names.
  const uint16_t recordId = 2;  // IPTC Application2 is commonly record 2

  // Guard: if this build/config does not recognize recordId 2, skip instead of guessing.
  const std::string recName = IptcDataSets::recordName(recordId);
  if (LooksLikeHexDatasetName(recName)) {
    GTEST_SKIP() << "recordId 2 does not appear to be recognized in this build (recordName="
                 << recName << ")";
  }

  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  // Take the first entry. We do not assume any specific field values beyond the struct layout.
  const uint16_t number = list[0].number_;

  const std::string dsName = IptcDataSets::dataSetName(number, recordId);

  // If the returned name looks like "0x....", the implementation did not find that number
  // for this recordId; in that case, skip rather than inferring sentinel/termination rules.
  if (LooksLikeHexDatasetName(dsName)) {
    GTEST_SKIP() << "First application2 dataset number did not resolve to a named dataset "
                    "(number=0x"
                 << std::hex << number << std::dec << ", name=" << dsName << ")";
  }

  // Observable round-trip: name -> number must return the same dataset number.
  EXPECT_EQ(IptcDataSets::dataSet(dsName, recordId), number);
}

TEST_F(IptcDataSetsTest_630, KnownDatasetMetadataAccessorsAreCallable_630) {
  const uint16_t recordId = 2;

  const std::string recName = IptcDataSets::recordName(recordId);
  if (LooksLikeHexDatasetName(recName)) {
    GTEST_SKIP() << "recordId 2 does not appear to be recognized in this build (recordName="
                 << recName << ")";
  }

  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const uint16_t number = list[0].number_;
  const std::string dsName = IptcDataSets::dataSetName(number, recordId);
  if (LooksLikeHexDatasetName(dsName)) {
    GTEST_SKIP() << "Dataset number did not resolve to a named dataset; skipping metadata checks.";
  }

  // Title is typically present; require non-null and non-empty for a known dataset.
  const char* title = IptcDataSets::dataSetTitle(number, recordId);
  ASSERT_NE(title, nullptr);
  EXPECT_NE(std::string(title).size(), 0u);

  // Desc / Photoshop name may or may not exist depending on dataset; just verify callable and
  // (if provided) non-empty.
  const char* desc = IptcDataSets::dataSetDesc(number, recordId);
  if (desc != nullptr) {
    EXPECT_NE(std::string(desc).size(), 0u);
  }

  const char* ps = IptcDataSets::dataSetPsName(number, recordId);
  if (ps != nullptr) {
    EXPECT_NE(std::string(ps).size(), 0u);
  }
}

TEST_F(IptcDataSetsTest_630, RepeatableAndTypeQueriesAreStableForSameInputs_630) {
  const uint16_t recordId = 2;

  const std::string recName = IptcDataSets::recordName(recordId);
  if (LooksLikeHexDatasetName(recName)) {
    GTEST_SKIP() << "recordId 2 does not appear to be recognized in this build (recordName="
                 << recName << ")";
  }

  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const uint16_t number = list[0].number_;
  const std::string dsName = IptcDataSets::dataSetName(number, recordId);
  if (LooksLikeHexDatasetName(dsName)) {
    GTEST_SKIP() << "Dataset number did not resolve to a named dataset; skipping stability checks.";
  }

  const bool rep1 = IptcDataSets::dataSetRepeatable(number, recordId);
  const bool rep2 = IptcDataSets::dataSetRepeatable(number, recordId);
  EXPECT_EQ(rep1, rep2);

  const TypeId t1 = IptcDataSets::dataSetType(number, recordId);
  const TypeId t2 = IptcDataSets::dataSetType(number, recordId);
  EXPECT_EQ(t1, t2);
}

}  // namespace Exiv2