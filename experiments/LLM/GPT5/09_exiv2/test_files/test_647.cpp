// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

class IptcKeyTest_647 : public ::testing::Test {};

TEST_F(IptcKeyTest_647, RecordNameMatchesDataSetsForZeroRecord_647) {
  const uint16_t recordId = 0;
  Exiv2::IptcKey key(/*tag=*/0, /*record=*/recordId);

  EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(key.record()));
  EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(recordId));
}

TEST_F(IptcKeyTest_647, RecordNameMatchesDataSetsForCommonRecordIds_647) {
  // These IDs may or may not be recognized by the library; the test checks
  // consistency between IptcKey and IptcDataSets for the same record id.
  for (uint16_t recordId : {static_cast<uint16_t>(1), static_cast<uint16_t>(2), static_cast<uint16_t>(3)}) {
    Exiv2::IptcKey key(/*tag=*/0, /*record=*/recordId);
    EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(key.record()));
    EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(recordId));
  }
}

TEST_F(IptcKeyTest_647, RecordNameMatchesDataSetsForMaxUint16Record_647) {
  const uint16_t recordId = std::numeric_limits<uint16_t>::max();
  Exiv2::IptcKey key(/*tag=*/0, /*record=*/recordId);

  EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(key.record()));
  EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(recordId));
}

TEST_F(IptcKeyTest_647, RecordNameIsStableAcrossMultipleCalls_647) {
  Exiv2::IptcKey key(/*tag=*/123, /*record=*/2);

  const std::string first = key.recordName();
  const std::string second = key.recordName();
  const std::string third = key.recordName();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(IptcKeyTest_647, RecordNameConsistentForStringConstructedKey_647) {
  // The string format is not assumed; this test only checks that recordName()
  // uses the same record id that record() reports.
  Exiv2::IptcKey key(std::string("Some.Random.IptcKey"));

  EXPECT_EQ(key.recordName(), Exiv2::IptcDataSets::recordName(key.record()));
}

}  // namespace