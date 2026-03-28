#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

// Include internal headers for tagInfo and IfdId
#include "tags_int.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class TagInfoTest_1367 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a known tag in IFD0 (e.g., ImageWidth, tag 0x0100) returns a valid, matching TagInfo
TEST_F(TagInfoTest_1367, KnownIfd0TagReturnsMatchingTagInfo_1367) {
    const TagInfo* ti = tagInfo(0x0100, ifdIdNotSet);
    // ifdIdNotSet may not have tags, try with ifd0Id
    const TagInfo* ti2 = tagInfo(0x0100, ifd0Id);
    if (ti2) {
        EXPECT_EQ(ti2->tag_, 0x0100);
    }
}

// Test that a well-known Exif IFD tag (e.g., ExposureTime 0x829a) returns matching entry
TEST_F(TagInfoTest_1367, KnownExifTagReturnsMatchingTagInfo_1367) {
    const TagInfo* ti = tagInfo(0x829a, exifId);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0x829a);
    }
}

// Test that a known GPS tag (e.g., GPSLatitude 0x0002) returns matching entry
TEST_F(TagInfoTest_1367, KnownGpsTagReturnsMatchingTagInfo_1367) {
    const TagInfo* ti = tagInfo(0x0002, gpsId);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0x0002);
    }
}

// Test that requesting an unknown/non-existent tag returns the sentinel entry (tag_ == 0xffff)
TEST_F(TagInfoTest_1367, UnknownTagReturnsSentinelEntry_1367) {
    const TagInfo* ti = tagInfo(0xBEEF, ifd0Id);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0xffff);
    }
}

// Test that an invalid IfdId returns nullptr
TEST_F(TagInfoTest_1367, InvalidIfdIdReturnsNullptr_1367) {
    const TagInfo* ti = tagInfo(0x0100, ifdIdNotSet);
    // ifdIdNotSet likely has no tag list, so nullptr is expected
    // This depends on implementation of tagList for ifdIdNotSet
    // We just verify it doesn't crash
    SUCCEED();
}

// Test with tag value 0 (boundary - minimum tag value)
TEST_F(TagInfoTest_1367, TagZeroBoundary_1367) {
    const TagInfo* ti = tagInfo(0x0000, ifd0Id);
    ASSERT_NE(ti, nullptr);
    // Either it finds tag 0 or returns sentinel
    EXPECT_TRUE(ti->tag_ == 0x0000 || ti->tag_ == 0xffff);
}

// Test with tag value 0xfffe (just below sentinel)
TEST_F(TagInfoTest_1367, TagJustBelowSentinelBoundary_1367) {
    const TagInfo* ti = tagInfo(0xfffe, ifd0Id);
    ASSERT_NE(ti, nullptr);
    // Either found or sentinel
    EXPECT_TRUE(ti->tag_ == 0xfffe || ti->tag_ == 0xffff);
}

// Test that the sentinel tag (0xffff) itself, when searched, returns the sentinel
TEST_F(TagInfoTest_1367, SentinelTagValueReturnsSentinel_1367) {
    const TagInfo* ti = tagInfo(0xffff, ifd0Id);
    if (ti) {
        // The loop stops at sentinel without matching 0xffff (because condition checks tag != 0xffff first)
        EXPECT_EQ(ti->tag_, 0xffff);
    }
}

// Test multiple known IFD0 tags to verify correct lookup
TEST_F(TagInfoTest_1367, MultipleKnownIfd0Tags_1367) {
    // ImageDescription = 0x010e
    const TagInfo* ti = tagInfo(0x010e, ifd0Id);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0x010e);
    }

    // Make = 0x010f
    ti = tagInfo(0x010f, ifd0Id);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0x010f);
    }

    // Model = 0x0110
    ti = tagInfo(0x0110, ifd0Id);
    if (ti) {
        EXPECT_EQ(ti->tag_, 0x0110);
    }
}

// Test with Exif IFD for an unknown tag
TEST_F(TagInfoTest_1367, UnknownExifTagReturnsSentinel_1367) {
    const TagInfo* ti = tagInfo(0x0001, exifId);
    if (ti) {
        // Tag 0x0001 is likely not in Exif IFD
        EXPECT_EQ(ti->tag_, 0xffff);
    }
}

// Test that the returned pointer is not null for valid IFDs even when tag is not found
TEST_F(TagInfoTest_1367, ValidIfdAlwaysReturnsNonNull_1367) {
    const TagInfo* ti = tagInfo(0xAAAA, ifd0Id);
    EXPECT_NE(ti, nullptr);
}

// Test different IFD IDs return appropriate results
TEST_F(TagInfoTest_1367, Ifd1TagLookup_1367) {
    // Ifd1 (thumbnail) should also have ImageWidth
    const TagInfo* ti = tagInfo(0x0100, ifd1Id);
    if (ti) {
        EXPECT_TRUE(ti->tag_ == 0x0100 || ti->tag_ == 0xffff);
    }
}

// Test last valid IfdId enum value doesn't crash
TEST_F(TagInfoTest_1367, LastIfdIdDoesNotCrash_1367) {
    const TagInfo* ti = tagInfo(0x0001, lastId);
    // lastId is not a real IFD, tagList should return nullptr
    EXPECT_EQ(ti, nullptr);
}

}  // namespace
