// =================================================================================================
// UNIT TESTS for Exiv2::IptcDataSets::dataSet(const std::string&, uint16_t)
// File: test_iptc_datasets_dataset_635.cpp
// TEST_ID: 635
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>

namespace {

class IptcDataSetsTest_635 : public ::testing::Test {
 protected:
  static constexpr uint16_t kApplication2RecordId = 2;  // Common IPTC record id; used only for calling public APIs safely.

  // Best-effort: fetch a valid dataset number from the public record list without hardcoding names.
  // If the list appears empty / unusable, return std::nullopt (simulated by bool + out param).
  static bool TryGetAnyApplication2DataSetNumber(uint16_t& outNumber) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    if (list == nullptr) return false;

    // We do NOT assume the sentinel format; we only try a bounded scan and accept the first
    // entry that looks usable (number != 0).
    for (int i = 0; i < 1024; ++i) {
      const auto& ds = list[i];
      if (ds.number_ != 0) {
        outNumber = ds.number_;
        return true;
      }
    }
    return false;
  }
};

TEST_F(IptcDataSetsTest_635, ParsesHexLowerBound_635) {
  const uint16_t v = Exiv2::IptcDataSets::dataSet("0x0000", kApplication2RecordId);
  EXPECT_EQ(v, static_cast<uint16_t>(0));
}

TEST_F(IptcDataSetsTest_635, ParsesHexUpperBound_635) {
  const uint16_t v = Exiv2::IptcDataSets::dataSet("0xFFFF", kApplication2RecordId);
  EXPECT_EQ(v, std::numeric_limits<uint16_t>::max());
}

TEST_F(IptcDataSetsTest_635, ParsesHexMixedCase_635) {
  const uint16_t v1 = Exiv2::IptcDataSets::dataSet("0x00ff", kApplication2RecordId);
  const uint16_t v2 = Exiv2::IptcDataSets::dataSet("0x00FF", kApplication2RecordId);
  EXPECT_EQ(v1, static_cast<uint16_t>(0x00FF));
  EXPECT_EQ(v2, static_cast<uint16_t>(0x00FF));
}

TEST_F(IptcDataSetsTest_635, RejectsInvalidHexFormat_635) {
  // Wrong length (expects exactly 4 hex digits after "0x")
  EXPECT_THROW((void)Exiv2::IptcDataSets::dataSet("0xFFF", kApplication2RecordId), Exiv2::Error);
  EXPECT_THROW((void)Exiv2::IptcDataSets::dataSet("0x00000", kApplication2RecordId), Exiv2::Error);

  // Missing prefix
  EXPECT_THROW((void)Exiv2::IptcDataSets::dataSet("0001", kApplication2RecordId), Exiv2::Error);

  // Invalid hex characters
  EXPECT_THROW((void)Exiv2::IptcDataSets::dataSet("0xGGGG", kApplication2RecordId), Exiv2::Error);
}

TEST_F(IptcDataSetsTest_635, RejectsUnknownNonHexName_635) {
  // Name that is neither a known dataset name nor a valid "0xNNNN" form should throw.
  EXPECT_THROW((void)Exiv2::IptcDataSets::dataSet("ThisIsNotARealDataSetName", kApplication2RecordId), Exiv2::Error);
}

TEST_F(IptcDataSetsTest_635, ResolvesKnownDataSetNameFromPublicList_635) {
  uint16_t anyNumber = 0;
  if (!TryGetAnyApplication2DataSetNumber(anyNumber)) {
    GTEST_SKIP() << "Could not obtain a usable dataset number from application2RecordList().";
  }

  // Obtain a canonical dataset name via the public API, then resolve it back to the number.
  const std::string name = Exiv2::IptcDataSets::dataSetName(anyNumber, kApplication2RecordId);

  // If for some reason the returned name is empty, skip rather than guessing.
  if (name.empty()) {
    GTEST_SKIP() << "dataSetName() returned empty; cannot validate name-to-number resolution safely.";
  }

  const uint16_t resolved = Exiv2::IptcDataSets::dataSet(name, kApplication2RecordId);
  EXPECT_EQ(resolved, anyNumber);
}

}  // namespace