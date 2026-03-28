#include <gtest/gtest.h>
#include <string>

// Include necessary headers from exiv2
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TagInfoTest_1368 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an empty tag name returns nullptr
TEST_F(TagInfoTest_1368, EmptyTagNameReturnsNullptr_1368) {
    const TagInfo* result = tagInfo("", IfdId::ifd0Id);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid tag name in IFD0 returns non-null
TEST_F(TagInfoTest_1368, ValidIfd0TagReturnsNonNull_1368) {
    // "ImageWidth" is a well-known standard TIFF tag in IFD0
    const TagInfo* result = tagInfo("ImageWidth", IfdId::ifd0Id);
    EXPECT_NE(result, nullptr);
}

// Test that a valid tag returns correct tag name
TEST_F(TagInfoTest_1368, ValidTagHasCorrectName_1368) {
    const TagInfo* result = tagInfo("ImageWidth", IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->name_, "ImageWidth");
}

// Test that a nonexistent tag name returns nullptr
TEST_F(TagInfoTest_1368, NonexistentTagNameReturnsNullptr_1368) {
    const TagInfo* result = tagInfo("CompletelyBogusTagName12345", IfdId::ifd0Id);
    EXPECT_EQ(result, nullptr);
}

// Test that an invalid IFD ID returns nullptr
TEST_F(TagInfoTest_1368, InvalidIfdIdReturnsNullptr_1368) {
    const TagInfo* result = tagInfo("ImageWidth", IfdId::lastId);
    EXPECT_EQ(result, nullptr);
}

// Test another well-known IFD0 tag
TEST_F(TagInfoTest_1368, ImageLengthTagFound_1368) {
    const TagInfo* result = tagInfo("ImageLength", IfdId::ifd0Id);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "ImageLength");
    }
}

// Test a well-known Exif tag
TEST_F(TagInfoTest_1368, ExifIfdTagFound_1368) {
    const TagInfo* result = tagInfo("ExposureTime", IfdId::exifId);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "ExposureTime");
    }
}

// Test GPS IFD tag
TEST_F(TagInfoTest_1368, GpsIfdTagFound_1368) {
    const TagInfo* result = tagInfo("GPSLatitude", IfdId::gpsId);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "GPSLatitude");
    }
}

// Test that a tag valid in one IFD is not found in another IFD
TEST_F(TagInfoTest_1368, TagNotFoundInWrongIfd_1368) {
    // "ExposureTime" is an Exif tag, not a GPS tag
    const TagInfo* result = tagInfo("ExposureTime", IfdId::gpsId);
    EXPECT_EQ(result, nullptr);
}

// Test case sensitivity - tag names should be case sensitive
TEST_F(TagInfoTest_1368, TagNameIsCaseSensitive_1368) {
    const TagInfo* result = tagInfo("imagewidth", IfdId::ifd0Id);
    EXPECT_EQ(result, nullptr);
}

// Test with a single character tag name that doesn't exist
TEST_F(TagInfoTest_1368, SingleCharNonexistentTagReturnsNullptr_1368) {
    const TagInfo* result = tagInfo("X", IfdId::ifd0Id);
    EXPECT_EQ(result, nullptr);
}

// Test well-known tag: Make
TEST_F(TagInfoTest_1368, MakeTagFound_1368) {
    const TagInfo* result = tagInfo("Make", IfdId::ifd0Id);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "Make");
    }
}

// Test well-known tag: Model
TEST_F(TagInfoTest_1368, ModelTagFound_1368) {
    const TagInfo* result = tagInfo("Model", IfdId::ifd0Id);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "Model");
    }
}

// Test well-known Exif tag: ISOSpeedRatings / PhotographicSensitivity
TEST_F(TagInfoTest_1368, FNumberTagFound_1368) {
    const TagInfo* result = tagInfo("FNumber", IfdId::exifId);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "FNumber");
    }
}

// Test IFD1 (thumbnail IFD) - should share tags with IFD0
TEST_F(TagInfoTest_1368, Ifd1TagFound_1368) {
    const TagInfo* result = tagInfo("ImageWidth", IfdId::ifd1Id);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "ImageWidth");
    }
}

// Test with tag name containing spaces (should not match standard tags)
TEST_F(TagInfoTest_1368, TagNameWithSpacesReturnsNullptr_1368) {
    const TagInfo* result = tagInfo("Image Width", IfdId::ifd0Id);
    EXPECT_EQ(result, nullptr);
}

// Test Interop IFD
TEST_F(TagInfoTest_1368, InteropIfdTagFound_1368) {
    const TagInfo* result = tagInfo("InteroperabilityIndex", IfdId::iopId);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_STREQ(result->name_, "InteroperabilityIndex");
    }
}
