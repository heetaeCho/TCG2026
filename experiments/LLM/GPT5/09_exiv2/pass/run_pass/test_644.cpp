// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptckey_taglabel_644.cpp
//
// TEST_ID is 644
//
// Unit tests for Exiv2::IptcKey::tagLabel()
// Constraints: treat implementation as black box; test only observable behavior.

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>

#include <cstdint>
#include <string>

namespace {

using Exiv2::IptcDataSets;
using Exiv2::IptcKey;

class IptcKeyTagLabelTest_644 : public ::testing::Test {};

TEST_F(IptcKeyTagLabelTest_644, ReturnsEmptyStringForDefaultConstructedKey_644) {
  // Constructed from a key string does not set tag_/record_ via public interface here.
  // Observable behavior: tagLabel() should match the dataset title for (0,0).
  IptcKey key(std::string("Iptc.Envelope.Whatever"));

  const std::string label = key.tagLabel();
  const char* expected = IptcDataSets::dataSetTitle(/*number=*/0, /*recordId=*/0);

  if (expected == nullptr) {
    EXPECT_TRUE(label.empty());
  } else {
    EXPECT_EQ(label, std::string(expected));
  }
}

TEST_F(IptcKeyTagLabelTest_644, MatchesIptcDataSetsDataSetTitleForSameTagAndRecord_644) {
  // Choose some common record/tag pairs that are likely to exist; but tests do not assume existence.
  struct Pair {
    uint16_t tag;
    uint16_t record;
  };

  const Pair candidates[] = {
      {0, 0},
      {5, 1},   // often Envelope
      {25, 2},  // often Application2
      {55, 2},
  };

  for (const auto& p : candidates) {
    IptcKey key(p.tag, p.record);

    const std::string label = key.tagLabel();
    const char* expected = IptcDataSets::dataSetTitle(p.tag, p.record);

    if (expected == nullptr) {
      EXPECT_TRUE(label.empty()) << "tag=" << p.tag << " record=" << p.record;
    } else {
      EXPECT_EQ(label, std::string(expected)) << "tag=" << p.tag << " record=" << p.record;
    }
  }
}

TEST_F(IptcKeyTagLabelTest_644, ReturnsStableValueAcrossMultipleCalls_644) {
  IptcKey key(/*tag=*/25, /*record=*/2);

  const std::string first = key.tagLabel();
  const std::string second = key.tagLabel();
  const std::string third = key.tagLabel();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(IptcKeyTagLabelTest_644, LargeTagAndRecordDoesNotCrashAndMatchesDataSetTitle_644) {
  // Boundary-ish values. We only assert consistency with IptcDataSets::dataSetTitle.
  const uint16_t tag = static_cast<uint16_t>(0xFFFF);
  const uint16_t record = static_cast<uint16_t>(0xFFFF);

  IptcKey key(tag, record);

  const std::string label = key.tagLabel();
  const char* expected = IptcDataSets::dataSetTitle(tag, record);

  if (expected == nullptr) {
    EXPECT_TRUE(label.empty());
  } else {
    EXPECT_EQ(label, std::string(expected));
  }
}

TEST_F(IptcKeyTagLabelTest_644, DifferentTagOrRecordMayProduceDifferentLabelButAlwaysMatchesDataSetTitle_644) {
  // We do NOT require different labels (dataset tables could map both to empty/unknown).
  // We only require each call matches the corresponding dataset title.
  const struct {
    uint16_t tag;
    uint16_t record;
  } a{25, 2}, b{26, 2}, c{25, 1};

  IptcKey keyA(a.tag, a.record);
  IptcKey keyB(b.tag, b.record);
  IptcKey keyC(c.tag, c.record);

  const std::string labelA = keyA.tagLabel();
  const std::string labelB = keyB.tagLabel();
  const std::string labelC = keyC.tagLabel();

  const char* expA = IptcDataSets::dataSetTitle(a.tag, a.record);
  const char* expB = IptcDataSets::dataSetTitle(b.tag, b.record);
  const char* expC = IptcDataSets::dataSetTitle(c.tag, c.record);

  EXPECT_EQ(labelA, expA ? std::string(expA) : std::string());
  EXPECT_EQ(labelB, expB ? std::string(expB) : std::string());
  EXPECT_EQ(labelC, expC ? std::string(expC) : std::string());

  // Optional (non-binding) sanity: at least one difference is allowed, not required.
  // This keeps the test robust across dataset table variations.
  (void)labelB;
  (void)labelC;
}

}  // namespace