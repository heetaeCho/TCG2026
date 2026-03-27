// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/iptc_key_tag_test_646.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

using Exiv2::IptcKey;

TEST(IptcKeyTest_646, TagFromStringCtorIsZero_646) {
  IptcKey key(std::string("Iptc.Application2.ObjectName"));
  EXPECT_EQ(key.tag(), 0u);
}

TEST(IptcKeyTest_646, TagFromEmptyStringCtorIsZero_646) {
  IptcKey key(std::string());
  EXPECT_EQ(key.tag(), 0u);
}

TEST(IptcKeyTest_646, TagFromTagRecordCtorReturnsProvidedTag_646) {
  const uint16_t tag = 42;
  const uint16_t record = 2;
  IptcKey key(tag, record);
  EXPECT_EQ(key.tag(), tag);
}

TEST(IptcKeyTest_646, TagBoundaryZero_646) {
  const uint16_t tag = 0;
  const uint16_t record = 0;
  IptcKey key(tag, record);
  EXPECT_EQ(key.tag(), tag);
}

TEST(IptcKeyTest_646, TagBoundaryMaxUint16_646) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();  // 65535
  const uint16_t record = 0;
  IptcKey key(tag, record);
  EXPECT_EQ(key.tag(), tag);
}

TEST(IptcKeyTest_646, TagIsStableAcrossMultipleCalls_646) {
  const uint16_t tag = 1234;
  const uint16_t record = 2;
  IptcKey key(tag, record);

  EXPECT_EQ(key.tag(), tag);
  EXPECT_EQ(key.tag(), tag);
  EXPECT_EQ(key.tag(), tag);
}

TEST(IptcKeyTest_646, TagReadThroughConstReference_646) {
  IptcKey key(static_cast<uint16_t>(7), static_cast<uint16_t>(2));
  const IptcKey& cref = key;
  EXPECT_EQ(cref.tag(), 7u);
}

}  // namespace