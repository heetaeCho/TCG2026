// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Internal Exiv2 header for Exiv2::Internal::Cr2Header, IfdId, PrimaryGroups
#include "cr2header_int.hpp"

namespace {

using Exiv2::Internal::Cr2Header;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::PrimaryGroups;

class Cr2HeaderTest_1546 : public ::testing::Test {
 protected:
  Cr2Header hdr_;
  PrimaryGroups primaryGroups_{};
};

TEST_F(Cr2HeaderTest_1546, Ifd2IdAlwaysReturnsTrueForBoundaryTags_1546) {
  const uint16_t kMinTag = 0;
  const uint16_t kOneTag = 1;
  const uint16_t kMaxTag = std::numeric_limits<uint16_t>::max();

  EXPECT_TRUE(hdr_.isImageTag(kMinTag, IfdId::ifd2Id, primaryGroups_));
  EXPECT_TRUE(hdr_.isImageTag(kOneTag, IfdId::ifd2Id, primaryGroups_));
  EXPECT_TRUE(hdr_.isImageTag(kMaxTag, IfdId::ifd2Id, primaryGroups_));
}

TEST_F(Cr2HeaderTest_1546, Ifd3IdAlwaysReturnsTrueForBoundaryTags_1546) {
  const uint16_t kMinTag = 0;
  const uint16_t kMidTag = 0x1234;
  const uint16_t kMaxTag = std::numeric_limits<uint16_t>::max();

  EXPECT_TRUE(hdr_.isImageTag(kMinTag, IfdId::ifd3Id, primaryGroups_));
  EXPECT_TRUE(hdr_.isImageTag(kMidTag, IfdId::ifd3Id, primaryGroups_));
  EXPECT_TRUE(hdr_.isImageTag(kMaxTag, IfdId::ifd3Id, primaryGroups_));
}

TEST_F(Cr2HeaderTest_1546, Ifd2IdResultDoesNotDependOnTagValue_1546) {
  const uint16_t kTagA = 0;
  const uint16_t kTagB = std::numeric_limits<uint16_t>::max();

  const bool a = hdr_.isImageTag(kTagA, IfdId::ifd2Id, primaryGroups_);
  const bool b = hdr_.isImageTag(kTagB, IfdId::ifd2Id, primaryGroups_);

  EXPECT_TRUE(a);
  EXPECT_TRUE(b);
}

TEST_F(Cr2HeaderTest_1546, Ifd3IdResultDoesNotDependOnTagValue_1546) {
  const uint16_t kTagA = 42;
  const uint16_t kTagB = 0xBEEF;

  const bool a = hdr_.isImageTag(kTagA, IfdId::ifd3Id, primaryGroups_);
  const bool b = hdr_.isImageTag(kTagB, IfdId::ifd3Id, primaryGroups_);

  EXPECT_TRUE(a);
  EXPECT_TRUE(b);
}

TEST_F(Cr2HeaderTest_1546, NonIfd2Ifd3IsDeterministicForSameInputs_1546) {
  // For groups other than ifd2Id/ifd3Id, behavior is delegated internally.
  // We only assert the observable property that repeated calls with identical
  // inputs produce the same output (const method, same args).
  const uint16_t tag = 0x0100;
  const IfdId group = IfdId::ifd0Id;

  const bool first = hdr_.isImageTag(tag, group, primaryGroups_);
  const bool second = hdr_.isImageTag(tag, group, primaryGroups_);

  EXPECT_EQ(first, second);
}

TEST_F(Cr2HeaderTest_1546, NonIfd2Ifd3AcceptsBoundaryTagValues_1546) {
  // Boundary tags should be accepted and return a boolean without throwing.
  const IfdId group = IfdId::ifd0Id;

  EXPECT_NO_THROW((void)hdr_.isImageTag(static_cast<uint16_t>(0), group, primaryGroups_));
  EXPECT_NO_THROW((void)hdr_.isImageTag(std::numeric_limits<uint16_t>::max(), group, primaryGroups_));

  // Also ensure the return type is usable as a bool.
  const bool v1 = hdr_.isImageTag(static_cast<uint16_t>(0), group, primaryGroups_);
  const bool v2 = hdr_.isImageTag(std::numeric_limits<uint16_t>::max(), group, primaryGroups_);
  (void)v1;
  (void)v2;
}

}  // namespace