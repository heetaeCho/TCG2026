#include <gtest/gtest.h>
#include <stdexcept>

// Include necessary headers from exiv2
#include "exiv2/tags.hpp"
#include "exiv2/error.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TagNumberTest_1376 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a known tag name in a known IFD returns the correct tag number
TEST_F(TagNumberTest_1376, KnownTagReturnsCorrectNumber_1376) {
    // "ImageWidth" is a well-known Exif IFD0 tag with tag number 0x0100 = 256
    uint16_t result = tagNumber("ImageWidth", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0100);
}

// Test that another known tag name returns the correct tag number
TEST_F(TagNumberTest_1376, ImageLengthTagReturnsCorrectNumber_1376) {
    uint16_t result = tagNumber("ImageLength", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0101);
}

// Test that a valid hex string (4 hex digits with 0x prefix) is parsed correctly
TEST_F(TagNumberTest_1376, ValidHexStringReturnsCorrectNumber_1376) {
    uint16_t result = tagNumber("0x0100", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0100);
}

// Test another valid hex string
TEST_F(TagNumberTest_1376, ValidHexStringFFFF_1376) {
    uint16_t result = tagNumber("0xffff", IfdId::ifd0Id);
    EXPECT_EQ(result, 0xffff);
}

// Test hex string with uppercase hex digits
TEST_F(TagNumberTest_1376, ValidHexStringUpperCase_1376) {
    uint16_t result = tagNumber("0xABCD", IfdId::ifd0Id);
    EXPECT_EQ(result, 0xABCD);
}

// Test hex string 0x0000
TEST_F(TagNumberTest_1376, ValidHexStringZero_1376) {
    uint16_t result = tagNumber("0x0000", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0000);
}

// Test that an invalid (non-hex, non-known) tag name throws an error
TEST_F(TagNumberTest_1376, InvalidTagNameThrowsError_1376) {
    EXPECT_THROW(tagNumber("CompletelyInvalidTagName", IfdId::ifd0Id), Error);
}

// Test that a string that looks like hex but is too short throws
TEST_F(TagNumberTest_1376, ShortHexStringThrowsError_1376) {
    EXPECT_THROW(tagNumber("0x01", IfdId::ifd0Id), Error);
}

// Test that a string starting with 0x but with invalid hex chars throws
TEST_F(TagNumberTest_1376, InvalidHexCharsThrowsError_1376) {
    EXPECT_THROW(tagNumber("0xGGGG", IfdId::ifd0Id), Error);
}

// Test that an empty string throws an error
TEST_F(TagNumberTest_1376, EmptyStringThrowsError_1376) {
    EXPECT_THROW(tagNumber("", IfdId::ifd0Id), Error);
}

// Test known Exif IFD tag - ExposureTime in exifId
TEST_F(TagNumberTest_1376, ExifExposureTimeTag_1376) {
    uint16_t result = tagNumber("ExposureTime", IfdId::exifId);
    EXPECT_EQ(result, 0x829a);
}

// Test known Exif IFD tag - FNumber
TEST_F(TagNumberTest_1376, ExifFNumberTag_1376) {
    uint16_t result = tagNumber("FNumber", IfdId::exifId);
    EXPECT_EQ(result, 0x829d);
}

// Test known GPS tag
TEST_F(TagNumberTest_1376, GpsLatitudeTag_1376) {
    uint16_t result = tagNumber("GPSLatitude", IfdId::gpsId);
    EXPECT_EQ(result, 0x0002);
}

// Test hex fallback with valid hex for an IFD that has no matching tag name
TEST_F(TagNumberTest_1376, HexFallbackOnUnknownIfd_1376) {
    uint16_t result = tagNumber("0x1234", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x1234);
}

// Test that a tag name with wrong IFD falls back to hex parsing if possible
TEST_F(TagNumberTest_1376, KnownTagWrongIfdThrows_1376) {
    // "ExposureTime" is an exifId tag, not an ifd0Id tag
    // If tagInfo doesn't find it, it should try hex parse, which will fail
    EXPECT_THROW(tagNumber("ExposureTime", IfdId::ifd0Id), Error);
}

// Test BitsPerSample tag in ifd0
TEST_F(TagNumberTest_1376, BitsPerSampleTag_1376) {
    uint16_t result = tagNumber("BitsPerSample", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0102);
}

// Test Compression tag
TEST_F(TagNumberTest_1376, CompressionTag_1376) {
    uint16_t result = tagNumber("Compression", IfdId::ifd0Id);
    EXPECT_EQ(result, 0x0103);
}

// Test that the error thrown for invalid tag has the right error code
TEST_F(TagNumberTest_1376, InvalidTagErrorCode_1376) {
    try {
        tagNumber("NotAValidTag", IfdId::ifd0Id);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerInvalidTag);
    }
}

// Test hex string with mixed case
TEST_F(TagNumberTest_1376, HexMixedCase_1376) {
    uint16_t result = tagNumber("0xAbCd", IfdId::ifd0Id);
    EXPECT_EQ(result, 0xABCD);
}

// Test that "0x" alone (without 4 hex digits) throws
TEST_F(TagNumberTest_1376, OnlyPrefixThrows_1376) {
    EXPECT_THROW(tagNumber("0x", IfdId::ifd0Id), Error);
}

// Test hex string with too many digits throws
TEST_F(TagNumberTest_1376, TooManyHexDigitsThrows_1376) {
    EXPECT_THROW(tagNumber("0x12345", IfdId::ifd0Id), Error);
}
