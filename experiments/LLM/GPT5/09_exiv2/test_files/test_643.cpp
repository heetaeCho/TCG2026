// File: test_iptckey_tagname_643.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

using Exiv2::IptcDataSets;
using Exiv2::IptcKey;

class IptcKeyTagNameTest_643 : public ::testing::Test {};

TEST_F(IptcKeyTagNameTest_643, TagNameMatchesIptcDataSetsDataSetName_643) {
  const uint16_t tag = 5;
  const uint16_t record = 2;

  IptcKey key(tag, record);

  const std::string expected = IptcDataSets::dataSetName(tag, record);
  EXPECT_EQ(key.tagName(), expected);
}

TEST_F(IptcKeyTagNameTest_643, TagNameIsStableAcrossMultipleCalls_643) {
  const uint16_t tag = 120;
  const uint16_t record = 2;

  IptcKey key(tag, record);

  const std::string first = key.tagName();
  const std::string second = key.tagName();
  EXPECT_EQ(first, second);

  // Also cross-check against the dependency function.
  EXPECT_EQ(first, IptcDataSets::dataSetName(tag, record));
}

TEST_F(IptcKeyTagNameTest_643, TagNameMatchesDataSetNameAtZeroBoundary_643) {
  const uint16_t tag = 0;
  const uint16_t record = 0;

  IptcKey key(tag, record);

  EXPECT_EQ(key.tagName(), IptcDataSets::dataSetName(tag, record));
}

TEST_F(IptcKeyTagNameTest_643, TagNameMatchesDataSetNameAtMaxUInt16Boundary_643) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  const uint16_t record = std::numeric_limits<uint16_t>::max();

  IptcKey key(tag, record);

  EXPECT_EQ(key.tagName(), IptcDataSets::dataSetName(tag, record));
}

TEST_F(IptcKeyTagNameTest_643, TagNameFromStringKeyMatchesDataSetNameUsingParsedTagAndRecord_643) {
  // Use a typical IPTC key string format used by Exiv2.
  // We don't assume what tag/record it maps to; we only assert internal consistency
  // via the public interface.
  IptcKey key(std::string("Iptc.Application2.ObjectName"));

  const uint16_t parsedTag = key.tag();
  const uint16_t parsedRecord = key.record();

  EXPECT_EQ(key.tagName(), IptcDataSets::dataSetName(parsedTag, parsedRecord));
}

}  // namespace