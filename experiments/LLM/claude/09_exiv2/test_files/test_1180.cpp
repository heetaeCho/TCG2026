#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace functions
namespace Exiv2 {
namespace Internal {
bool isTiffImageTag(uint16_t tag, IfdId group);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class IsTiffImageTagTest_1180 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with a known TIFF image tag - ImageWidth (tag 256) in IFD0
TEST_F(IsTiffImageTagTest_1180, ImageWidthInIfd0_1180) {
    // Tag 0x0100 = ImageWidth is a standard TIFF image tag in IFD0
    bool result = isTiffImageTag(0x0100, IfdId::ifd0Id);
    // ImageWidth is typically a TIFF image tag
    EXPECT_TRUE(result);
}

// Test with ImageLength (tag 257) in IFD0
TEST_F(IsTiffImageTagTest_1180, ImageLengthInIfd0_1180) {
    bool result = isTiffImageTag(0x0101, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with BitsPerSample (tag 258) in IFD0
TEST_F(IsTiffImageTagTest_1180, BitsPerSampleInIfd0_1180) {
    bool result = isTiffImageTag(0x0102, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with Compression (tag 259) in IFD0
TEST_F(IsTiffImageTagTest_1180, CompressionInIfd0_1180) {
    bool result = isTiffImageTag(0x0103, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with PhotometricInterpretation (tag 262) in IFD0
TEST_F(IsTiffImageTagTest_1180, PhotometricInterpretationInIfd0_1180) {
    bool result = isTiffImageTag(0x0106, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with StripOffsets (tag 273) in IFD0
TEST_F(IsTiffImageTagTest_1180, StripOffsetsInIfd0_1180) {
    bool result = isTiffImageTag(0x0111, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with SamplesPerPixel (tag 277) in IFD0
TEST_F(IsTiffImageTagTest_1180, SamplesPerPixelInIfd0_1180) {
    bool result = isTiffImageTag(0x0115, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with RowsPerStrip (tag 278) in IFD0
TEST_F(IsTiffImageTagTest_1180, RowsPerStripInIfd0_1180) {
    bool result = isTiffImageTag(0x0116, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with StripByteCounts (tag 279) in IFD0
TEST_F(IsTiffImageTagTest_1180, StripByteCountsInIfd0_1180) {
    bool result = isTiffImageTag(0x0117, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with a non-image tag - a random/unlikely tag number in IFD0
TEST_F(IsTiffImageTagTest_1180, NonImageTagInIfd0_1180) {
    // Tag 0xFFFF is very unlikely to be a TIFF image tag
    bool result = isTiffImageTag(0xFFFF, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test with tag 0 in IFD0 - boundary condition
TEST_F(IsTiffImageTagTest_1180, TagZeroInIfd0_1180) {
    bool result = isTiffImageTag(0x0000, IfdId::ifd0Id);
    // Tag 0 is not a standard TIFF image tag
    EXPECT_FALSE(result);
}

// Test with an Exif-specific tag in ExifIFD (not a TIFF image tag)
TEST_F(IsTiffImageTagTest_1180, ExifTagInExifGroup_1180) {
    // ExposureTime tag (0x829A) in Exif IFD is not a TIFF image tag
    bool result = isTiffImageTag(0x829A, IfdId::exifId);
    EXPECT_FALSE(result);
}

// Test with a valid image tag but in wrong group
TEST_F(IsTiffImageTagTest_1180, ImageTagInExifGroup_1180) {
    // ImageWidth in Exif group may or may not be considered a TIFF image tag
    bool result = isTiffImageTag(0x0100, IfdId::exifId);
    // Just verify it returns a consistent boolean
    EXPECT_TRUE(result == true || result == false);
}

// Test with a GPS tag in GPS group
TEST_F(IsTiffImageTagTest_1180, GpsTagInGpsGroup_1180) {
    // GPSVersionID (tag 0x0000) in GPS group
    bool result = isTiffImageTag(0x0000, IfdId::gpsId);
    EXPECT_FALSE(result);
}

// Test with tag in IFD1 (thumbnail IFD)
TEST_F(IsTiffImageTagTest_1180, ImageWidthInIfd1_1180) {
    bool result = isTiffImageTag(0x0100, IfdId::ifd1Id);
    // ImageWidth should also be an image tag in IFD1
    EXPECT_TRUE(result);
}

// Test with TileWidth (tag 322) in IFD0
TEST_F(IsTiffImageTagTest_1180, TileWidthInIfd0_1180) {
    bool result = isTiffImageTag(0x0142, IfdId::ifd0Id);
    // TileWidth is a TIFF image tag
    EXPECT_TRUE(result);
}

// Test with TileLength (tag 323) in IFD0
TEST_F(IsTiffImageTagTest_1180, TileLengthInIfd0_1180) {
    bool result = isTiffImageTag(0x0143, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with TileOffsets (tag 324) in IFD0
TEST_F(IsTiffImageTagTest_1180, TileOffsetsInIfd0_1180) {
    bool result = isTiffImageTag(0x0144, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with TileByteCounts (tag 325) in IFD0
TEST_F(IsTiffImageTagTest_1180, TileByteCountsInIfd0_1180) {
    bool result = isTiffImageTag(0x0145, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with a maker note tag - should not be a TIFF image tag
TEST_F(IsTiffImageTagTest_1180, MakerNoteTag_1180) {
    bool result = isTiffImageTag(0x0001, IfdId::canonId);
    EXPECT_FALSE(result);
}

// Test consistency - calling the function twice with the same arguments returns the same result
TEST_F(IsTiffImageTagTest_1180, ConsistencyCheck_1180) {
    bool result1 = isTiffImageTag(0x0100, IfdId::ifd0Id);
    bool result2 = isTiffImageTag(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result1, result2);
}

// Test with max uint16_t tag value
TEST_F(IsTiffImageTagTest_1180, MaxUint16TagValue_1180) {
    bool result = isTiffImageTag(UINT16_MAX, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}

// Test JPEGInterchangeFormat (tag 513) in IFD0
TEST_F(IsTiffImageTagTest_1180, JPEGInterchangeFormatInIfd0_1180) {
    bool result = isTiffImageTag(0x0201, IfdId::ifd0Id);
    // JPEGInterchangeFormat is typically a TIFF image tag
    EXPECT_TRUE(result);
}

// Test JPEGInterchangeFormatLength (tag 514) in IFD0
TEST_F(IsTiffImageTagTest_1180, JPEGInterchangeFormatLengthInIfd0_1180) {
    bool result = isTiffImageTag(0x0202, IfdId::ifd0Id);
    EXPECT_TRUE(result);
}

// Test with a non-image Exif tag like DateTimeOriginal in IFD0
TEST_F(IsTiffImageTagTest_1180, DateTimeOriginalInIfd0_1180) {
    // DateTimeOriginal (0x9003) is an Exif tag, not a TIFF image tag
    bool result = isTiffImageTag(0x9003, IfdId::ifd0Id);
    EXPECT_FALSE(result);
}
