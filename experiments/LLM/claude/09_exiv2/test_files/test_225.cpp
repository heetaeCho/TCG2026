#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test that tag() returns the lower 16 bits of extendedTag for a zero value
TEST(TiffPathItemTest_225, TagReturnsZeroForZeroExtendedTag_225) {
    TiffPathItem item(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0000);
}

// Test that tag() returns the lower 16 bits of a small extendedTag value
TEST(TiffPathItemTest_225, TagReturnsCorrectValueForSmallExtendedTag_225) {
    TiffPathItem item(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0001);
}

// Test that tag() correctly truncates a 32-bit value to 16 bits
TEST(TiffPathItemTest_225, TagTruncatesHighBitsOfExtendedTag_225) {
    TiffPathItem item(0x00010002, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0002);
}

// Test tag() with maximum 16-bit value in extendedTag
TEST(TiffPathItemTest_225, TagReturnsMaxUint16WhenExtendedTagHasMaxLow16_225) {
    TiffPathItem item(0x0000FFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0xFFFF);
}

// Test tag() with maximum 32-bit extendedTag value
TEST(TiffPathItemTest_225, TagReturnsFFFFForMaxExtendedTag_225) {
    TiffPathItem item(0xFFFFFFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0xFFFF);
}

// Test tag() when upper bits are set but lower 16 bits are zero
TEST(TiffPathItemTest_225, TagReturnsZeroWhenOnlyUpperBitsSet_225) {
    TiffPathItem item(0xFFFF0000, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0000);
}

// Test extendedTag() returns the full 32-bit value
TEST(TiffPathItemTest_225, ExtendedTagReturnsFullValue_225) {
    TiffPathItem item(0x00010002, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0x00010002);
}

// Test extendedTag() with zero
TEST(TiffPathItemTest_225, ExtendedTagReturnsZero_225) {
    TiffPathItem item(0, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0u);
}

// Test extendedTag() with max value
TEST(TiffPathItemTest_225, ExtendedTagReturnsMaxValue_225) {
    TiffPathItem item(0xFFFFFFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0xFFFFFFFF);
}

// Test group() returns the correct group
TEST(TiffPathItemTest_225, GroupReturnsCorrectValue_225) {
    TiffPathItem item(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

// Test group() with a different IfdId
TEST(TiffPathItemTest_225, GroupReturnsExifId_225) {
    TiffPathItem item(0x0001, IfdId::exifId);
    EXPECT_EQ(item.group(), IfdId::exifId);
}

// Test that tag() and extendedTag() are consistent for values that fit in 16 bits
TEST(TiffPathItemTest_225, TagAndExtendedTagConsistentForSmallValues_225) {
    TiffPathItem item(0x00000100, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(item.extendedTag()));
}

// Test tag() with a typical EXIF tag value like 0x010F (Make)
TEST(TiffPathItemTest_225, TagReturnsTypicalExifTagValue_225) {
    TiffPathItem item(0x010F, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x010F);
}

// Boundary: extendedTag exactly at 16-bit boundary
TEST(TiffPathItemTest_225, TagAtExact16BitBoundary_225) {
    TiffPathItem item(0x00010000, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0000);
}

// Test with extendedTag value 0x00008000 (bit 15 set)
TEST(TiffPathItemTest_225, TagWithBit15Set_225) {
    TiffPathItem item(0x00008000, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x8000);
}
