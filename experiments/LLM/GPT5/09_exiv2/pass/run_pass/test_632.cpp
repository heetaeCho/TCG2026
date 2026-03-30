// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::IptcDataSets::dataSetDesc
//
// File: ./TestProjects/exiv2/src/datasets.cpp (interface via exiv2/datasets.hpp)

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include <exiv2/datasets.hpp>

namespace {

class IptcDataSetsTest_632 : public ::testing::Test {
 protected:
  static bool ContainsUnknown(const char* s) {
    if (!s) return false;
    const std::string str(s);
    // Keep this tolerant: different builds may vary the exact phrasing.
    return str.find("Unknown") != std::string::npos || str.find("unknown") != std::string::npos;
  }

  static const Exiv2::DataSet* FirstNonSentinel(const Exiv2::DataSet* list) {
    if (!list) return nullptr;
    // We don't know the sentinel convention; keep it defensive and bounded.
    for (int i = 0; i < 512; ++i) {
      const auto n = list[i].number_;
      // Heuristic: dataset number 0 often used as terminator; 65535 is "unknown".
      if (n != 0 && n != 65535) return &list[i];
    }
    return nullptr;
  }
};

TEST_F(IptcDataSetsTest_632, UnknownDatasetForEnvelopeRecordMentionsUnknown_632) {
  // Use the standard IPTC Envelope record id (commonly 1).
  const uint16_t recordId = 1;
  const uint16_t unknownNumber = 65535;

  const char* desc = Exiv2::IptcDataSets::dataSetDesc(unknownNumber, recordId);

  ASSERT_NE(desc, nullptr);
  EXPECT_GT(std::strlen(desc), 0u);
  EXPECT_TRUE(ContainsUnknown(desc));
}

TEST_F(IptcDataSetsTest_632, UnknownDatasetForApplication2RecordMentionsUnknown_632) {
  // Use the standard IPTC Application 2 record id (commonly 2).
  const uint16_t recordId = 2;
  const uint16_t unknownNumber = 65535;

  const char* desc = Exiv2::IptcDataSets::dataSetDesc(unknownNumber, recordId);

  ASSERT_NE(desc, nullptr);
  EXPECT_GT(std::strlen(desc), 0u);
  EXPECT_TRUE(ContainsUnknown(desc));
}

TEST_F(IptcDataSetsTest_632, KnownEnvelopeDatasetDescriptionIsNonEmpty_632) {
  const uint16_t recordId = 1;

  const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);

  const Exiv2::DataSet* ds = FirstNonSentinel(list);
  ASSERT_NE(ds, nullptr) << "Could not find a plausible dataset entry in envelopeRecordList()";

  const char* desc = Exiv2::IptcDataSets::dataSetDesc(ds->number_, recordId);

  ASSERT_NE(desc, nullptr);
  EXPECT_GT(std::strlen(desc), 0u);
  // For a known dataset (pulled from the list), it should generally not look "unknown".
  EXPECT_FALSE(ContainsUnknown(desc));
}

TEST_F(IptcDataSetsTest_632, KnownApplication2DatasetDescriptionIsNonEmpty_632) {
  const uint16_t recordId = 2;

  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const Exiv2::DataSet* ds = FirstNonSentinel(list);
  ASSERT_NE(ds, nullptr) << "Could not find a plausible dataset entry in application2RecordList()";

  const char* desc = Exiv2::IptcDataSets::dataSetDesc(ds->number_, recordId);

  ASSERT_NE(desc, nullptr);
  EXPECT_GT(std::strlen(desc), 0u);
  EXPECT_FALSE(ContainsUnknown(desc));
}

TEST_F(IptcDataSetsTest_632, BoundaryNumberZeroReturnsNonNullForEnvelope_632) {
  const uint16_t recordId = 1;
  const uint16_t number = 0;

  const char* desc = Exiv2::IptcDataSets::dataSetDesc(number, recordId);

  // Boundary condition: should not crash; if unknown, should still produce a stable description.
  ASSERT_NE(desc, nullptr);
  EXPECT_GT(std::strlen(desc), 0u);
}

}  // namespace