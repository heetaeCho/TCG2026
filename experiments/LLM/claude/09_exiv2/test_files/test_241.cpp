#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

// We need to include necessary headers for the types used
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffDataEntryBase
class TiffDataEntryBaseTest_241 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that szTag() returns the szTag value passed in the constructor
TEST_F(TiffDataEntryBaseTest_241, SzTagReturnsConstructedValue_241) {
    uint16_t tag = 0x0111;       // StripOffsets
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;     // StripByteCounts
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntryBase entry(tag, group, szTag, szGroup);
    EXPECT_EQ(szTag, entry.szTag());
}

// Test szTag() with zero value
TEST_F(TiffDataEntryBaseTest_241, SzTagReturnsZero_241) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0000;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntryBase entry(tag, group, szTag, szGroup);
    EXPECT_EQ(0, entry.szTag());
}

// Test szTag() with maximum uint16_t value
TEST_F(TiffDataEntryBaseTest_241, SzTagReturnsMaxUint16_241) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0xFFFF;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntryBase entry(tag, group, szTag, szGroup);
    EXPECT_EQ(0xFFFF, entry.szTag());
}

// Test szGroup() returns the szGroup value passed in the constructor
TEST_F(TiffDataEntryBaseTest_241, SzGroupReturnsConstructedValue_241) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;
    IfdId szGroup = IfdId::ifd1Id;

    TiffDataEntryBase entry(tag, group, szTag, szGroup);
    EXPECT_EQ(szGroup, entry.szGroup());
}

// Test that different constructor parameters yield correct szTag values
TEST_F(TiffDataEntryBaseTest_241, DifferentSzTagValues_241) {
    uint16_t tag = 0x0202;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag1 = 0x0100;
    uint16_t szTag2 = 0x0200;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntryBase entry1(tag, group, szTag1, szGroup);
    TiffDataEntryBase entry2(tag, group, szTag2, szGroup);

    EXPECT_EQ(szTag1, entry1.szTag());
    EXPECT_EQ(szTag2, entry2.szTag());
    EXPECT_NE(entry1.szTag(), entry2.szTag());
}

// Test that szTag and szGroup are independent of tag and group
TEST_F(TiffDataEntryBaseTest_241, SzTagIndependentOfTag_241) {
    uint16_t tag1 = 0x0001;
    uint16_t tag2 = 0x0002;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x00FF;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntryBase entry1(tag1, group, szTag, szGroup);
    TiffDataEntryBase entry2(tag2, group, szTag, szGroup);

    EXPECT_EQ(entry1.szTag(), entry2.szTag());
}

// Test construction with various IfdId values for szGroup
TEST_F(TiffDataEntryBaseTest_241, SzGroupWithDifferentIfdIds_241) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;

    TiffDataEntryBase entry1(tag, group, szTag, IfdId::ifd0Id);
    TiffDataEntryBase entry2(tag, group, szTag, IfdId::ifd1Id);

    EXPECT_EQ(IfdId::ifd0Id, entry1.szGroup());
    EXPECT_EQ(IfdId::ifd1Id, entry2.szGroup());
}
