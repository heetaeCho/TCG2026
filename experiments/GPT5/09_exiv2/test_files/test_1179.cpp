// =================================================================================================
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for: ./TestProjects/exiv2/src/tiffimage_int.cpp (static isTiffImageTagLookup)
//
// Constraints honored:
// - Treat implementation as black box (no re-implementation of logic beyond observable behavior)
// - Use only public/visible interface in this TU (we include the .cpp to access the internal static)
// - No private state access
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// Dependency for IfdId
#include "exiv2/tags.hpp"

// NOTE:
// The function under test has internal linkage (static) inside tiffimage_int.cpp.
// Including the .cpp makes it visible in THIS translation unit, enabling black-box tests.
#include "tiffimage_int.cpp"

namespace {

using Exiv2::IfdId;

class TiffImageTagLookupTest_1179 : public ::testing::Test {};

TEST_F(TiffImageTagLookupTest_1179, ReturnsFalseForNonIfd0GroupEvenForKnownTag_1179) {
  const uint16_t knownTag = 0x0100;  // Exif.Image.ImageWidth (listed in switch)

  const std::vector<IfdId> nonIfd0Groups = {
      IfdId::ifdIdNotSet, IfdId::ifd1Id, IfdId::ifd2Id, IfdId::ifd3Id, IfdId::exifId,
      IfdId::gpsId,       IfdId::iopId,  IfdId::mpfId,  IfdId::mnId,   IfdId::ignoreId,
  };

  for (const auto group : nonIfd0Groups) {
    SCOPED_TRACE(static_cast<int>(group));
    EXPECT_FALSE(Exiv2::Internal::isTiffImageTagLookup(knownTag, group));
  }
}

TEST_F(TiffImageTagLookupTest_1179, ReturnsTrueForAllKnownTagsInIfd0_1179) {
  const std::vector<uint16_t> knownTags = {
      0x00fe, 0x00ff, 0x0100, 0x0101, 0x0102, 0x0103, 0x0106, 0x010a, 0x0111, 0x0115, 0x0116,
      0x0117, 0x011a, 0x011b, 0x011c, 0x0122, 0x0123, 0x0124, 0x0125, 0x0128, 0x0129, 0x012d,
      0x013d, 0x013e, 0x013f, 0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x014c, 0x014d,
      0x014e, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x0159,
      0x015a, 0x015b, 0x0200, 0x0201, 0x0202, 0x0203, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209,
      0x0211, 0x0212, 0x0213, 0x0214, 0x828d, 0x828e, 0x8824, 0x8828, 0x9102, 0x9217,
  };

  for (const auto tag : knownTags) {
    SCOPED_TRACE(::testing::Message() << "tag=0x" << std::hex << tag);
    EXPECT_TRUE(Exiv2::Internal::isTiffImageTagLookup(tag, IfdId::ifd0Id));
  }
}

TEST_F(TiffImageTagLookupTest_1179, ReturnsFalseForUnknownTagsInIfd0_1179) {
  // A mix of clearly-not-listed tags and some "nearby" values.
  const std::vector<uint16_t> unknownTags = {
      0x0000,  // unlikely / not listed
      0x00fd,  // adjacent below first known (0x00fe)
      0x0104,  // in the 0x0100 range but not listed
      0x0112,  // adjacent above 0x0111
      0x0210,  // adjacent below 0x0211
      0x0215,  // adjacent above 0x0214
      0x828c,  // adjacent below 0x828d
      0x828f,  // adjacent above 0x828e
      0x9101,  // adjacent below 0x9102
      0x9103,  // adjacent above 0x9102
      0xffff,  // max uint16
  };

  for (const auto tag : unknownTags) {
    SCOPED_TRACE(::testing::Message() << "tag=0x" << std::hex << tag);
    EXPECT_FALSE(Exiv2::Internal::isTiffImageTagLookup(tag, IfdId::ifd0Id));
  }
}

TEST_F(TiffImageTagLookupTest_1179, BoundaryKnownTagsAndAdjacents_1179) {
  // Boundary at the low end: 0x00fe is known, 0x00fd is unknown.
  EXPECT_TRUE(Exiv2::Internal::isTiffImageTagLookup(static_cast<uint16_t>(0x00fe), IfdId::ifd0Id));
  EXPECT_FALSE(Exiv2::Internal::isTiffImageTagLookup(static_cast<uint16_t>(0x00fd), IfdId::ifd0Id));

  // Boundary at the high end: 0x9217 is known, its neighbors are not listed.
  EXPECT_TRUE(Exiv2::Internal::isTiffImageTagLookup(static_cast<uint16_t>(0x9217), IfdId::ifd0Id));
  EXPECT_FALSE(Exiv2::Internal::isTiffImageTagLookup(static_cast<uint16_t>(0x9216), IfdId::ifd0Id));
  EXPECT_FALSE(Exiv2::Internal::isTiffImageTagLookup(static_cast<uint16_t>(0x9218), IfdId::ifd0Id));
}

}  // namespace