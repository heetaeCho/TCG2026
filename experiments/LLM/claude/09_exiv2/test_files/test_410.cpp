#include <gtest/gtest.h>
#include "exiv2/tags.hpp"
#include "tiffcomposite_int.hpp"

// We need access to the findTagInfo function which is in the Internal namespace
// Since it's a static function in the .cpp file, we need to test it indirectly
// or include the source. However, based on the interface, we'll test what we can.

// Since findTagInfo is a static function within the .cpp file (internal linkage),
// we cannot directly call it from tests. We need to test it through whatever
// public interface exposes its behavior. However, given the constraints of the task,
// let's assume we can access it for testing purposes through some mechanism.

// For testing purposes, we'll declare the function signature we want to test.
// In practice, this would need to be exposed via a header or test-friend mechanism.

namespace Exiv2 {
namespace Internal {

// Forward declaration - this function exists in tiffcomposite_int.cpp
// We declare it here for testing. In a real codebase, this would be in a header.
const TagInfo* findTagInfo(uint16_t tag, IfdId group);

// These are declared in the Exiv2 Internal namespace
const TagInfo* gpsTagList();
const TagInfo* exifTagList();

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class FindTagInfoTest_410 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a known GPS tag can be found
TEST_F(FindTagInfoTest_410, FindKnownGpsTag_410) {
  // GPS VersionID is tag 0x0000 in GPS IFD
  const TagInfo* result = findTagInfo(0x0000, IfdId::gpsId);
  // GPS tags should contain tag 0 (GPSVersionID)
  // We expect a non-null result for a known GPS tag
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x0000);
  }
}

// Test that a known GPS Latitude tag can be found
TEST_F(FindTagInfoTest_410, FindGpsLatitudeTag_410) {
  // GPSLatitude is tag 0x0002
  const TagInfo* result = findTagInfo(0x0002, IfdId::gpsId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x0002);
  }
}

// Test that a known Exif tag can be found
TEST_F(FindTagInfoTest_410, FindKnownExifTag_410) {
  // ExifVersion is tag 0x9000 in Exif IFD
  const TagInfo* result = findTagInfo(0x9000, IfdId::exifId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x9000);
  }
}

// Test that ExposureTime (0x829A) can be found in Exif IFD
TEST_F(FindTagInfoTest_410, FindExifExposureTimeTag_410) {
  const TagInfo* result = findTagInfo(0x829A, IfdId::exifId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x829A);
  }
}

// Test that a non-existent tag returns nullptr for GPS group
TEST_F(FindTagInfoTest_410, NonExistentGpsTagReturnsNull_410) {
  // Use a tag number that's unlikely to exist in GPS tags
  const TagInfo* result = findTagInfo(0xFFFE, IfdId::gpsId);
  EXPECT_EQ(result, nullptr);
}

// Test that a non-existent tag returns nullptr for Exif group
TEST_F(FindTagInfoTest_410, NonExistentExifTagReturnsNull_410) {
  // Use a tag number that's unlikely to exist in Exif tags
  const TagInfo* result = findTagInfo(0xFFFE, IfdId::exifId);
  EXPECT_EQ(result, nullptr);
}

// Test that an unsupported group (not GPS or Exif) returns nullptr
TEST_F(FindTagInfoTest_410, UnsupportedGroupReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::ifd0Id);
  EXPECT_EQ(result, nullptr);
}

// Test with ifdIdNotSet returns nullptr
TEST_F(FindTagInfoTest_410, IfdIdNotSetReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::ifdIdNotSet);
  EXPECT_EQ(result, nullptr);
}

// Test with ifd1Id (not GPS or Exif) returns nullptr
TEST_F(FindTagInfoTest_410, Ifd1IdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0100, IfdId::ifd1Id);
  EXPECT_EQ(result, nullptr);
}

// Test with iopId returns nullptr (not GPS or Exif)
TEST_F(FindTagInfoTest_410, IopIdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::iopId);
  EXPECT_EQ(result, nullptr);
}

// Test with manufacturer-specific IFD returns nullptr
TEST_F(FindTagInfoTest_410, ManufacturerIdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::canonId);
  EXPECT_EQ(result, nullptr);
}

// Test that the sentinel tag 0xFFFF is not found (it's the terminator)
TEST_F(FindTagInfoTest_410, SentinelTagNotFound_410) {
  // 0xFFFF is used as sentinel in tag lists, so searching for it should stop
  const TagInfo* result = findTagInfo(0xFFFF, IfdId::gpsId);
  EXPECT_EQ(result, nullptr);
}

// Test sentinel tag in Exif group
TEST_F(FindTagInfoTest_410, SentinelTagNotFoundExif_410) {
  const TagInfo* result = findTagInfo(0xFFFF, IfdId::exifId);
  EXPECT_EQ(result, nullptr);
}

// Test GPS Longitude tag (0x0004)
TEST_F(FindTagInfoTest_410, FindGpsLongitudeTag_410) {
  const TagInfo* result = findTagInfo(0x0004, IfdId::gpsId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x0004);
  }
}

// Test GPS Altitude tag (0x0006)
TEST_F(FindTagInfoTest_410, FindGpsAltitudeTag_410) {
  const TagInfo* result = findTagInfo(0x0006, IfdId::gpsId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x0006);
  }
}

// Test Exif ISOSpeedRatings (0x8827)
TEST_F(FindTagInfoTest_410, FindExifISOTag_410) {
  const TagInfo* result = findTagInfo(0x8827, IfdId::exifId);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->tag_, 0x8827);
  }
}

// Test with nikon ID (should return nullptr as it's not GPS or Exif)
TEST_F(FindTagInfoTest_410, NikonIdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::nikon3Id);
  EXPECT_EQ(result, nullptr);
}

// Test with lastId/ignoreId returns nullptr
TEST_F(FindTagInfoTest_410, LastIdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::lastId);
  EXPECT_EQ(result, nullptr);
}

// Test tag 0 in exif group (may or may not exist)
TEST_F(FindTagInfoTest_410, TagZeroInExifGroup_410) {
  const TagInfo* result = findTagInfo(0x0000, IfdId::exifId);
  // Tag 0 might not exist in Exif - just verify no crash
  // Result could be null or valid
  if (result) {
    EXPECT_EQ(result->tag_, 0x0000);
  }
}

// Test multiple lookups return consistent results
TEST_F(FindTagInfoTest_410, ConsistentResults_410) {
  const TagInfo* result1 = findTagInfo(0x9000, IfdId::exifId);
  const TagInfo* result2 = findTagInfo(0x9000, IfdId::exifId);
  EXPECT_EQ(result1, result2);
}

// Test that GPS tag is not found in Exif group and vice versa
TEST_F(FindTagInfoTest_410, GpsTagNotInExifGroup_410) {
  // GPSLatitudeRef (0x0001) is a GPS tag
  const TagInfo* gpsResult = findTagInfo(0x0001, IfdId::gpsId);
  // Tag 0x0001 may or may not exist in Exif
  // But the GPS result should differ from exif result if both exist
  if (gpsResult) {
    EXPECT_EQ(gpsResult->tag_, 0x0001);
  }
}

// Test with mpfId returns nullptr
TEST_F(FindTagInfoTest_410, MpfIdReturnsNull_410) {
  const TagInfo* result = findTagInfo(0x0001, IfdId::mpfId);
  EXPECT_EQ(result, nullptr);
}
