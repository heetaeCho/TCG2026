#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test normal construction and extendedTag() accessor
TEST(TiffPathItemTest_226, ExtendedTagReturnsCorrectValue_226) {
    TiffPathItem item(0x1234, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0x1234u);
}

// Test with zero extended tag
TEST(TiffPathItemTest_226, ExtendedTagZero_226) {
    TiffPathItem item(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0x0000u);
}

// Test with max uint32_t extended tag
TEST(TiffPathItemTest_226, ExtendedTagMaxValue_226) {
    TiffPathItem item(0xFFFFFFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0xFFFFFFFFu);
}

// Test tag() returns the lower 16 bits of the extended tag
TEST(TiffPathItemTest_226, TagReturnsLower16Bits_226) {
    TiffPathItem item(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0100u);
}

// Test tag() with extended tag that has upper bits set
TEST(TiffPathItemTest_226, TagWithExtendedBitsSet_226) {
    TiffPathItem item(0x00010100, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0100u);
}

// Test tag() with zero
TEST(TiffPathItemTest_226, TagZero_226) {
    TiffPathItem item(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0x0000u);
}

// Test tag() when lower 16 bits are max
TEST(TiffPathItemTest_226, TagMaxLower16_226) {
    TiffPathItem item(0x0000FFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), 0xFFFFu);
}

// Test group() returns the correct IfdId
TEST(TiffPathItemTest_226, GroupReturnsCorrectValue_226) {
    TiffPathItem item(0x1234, IfdId::ifd0Id);
    EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

// Test group() with a different IfdId
TEST(TiffPathItemTest_226, GroupReturnsDifferentIfdId_226) {
    TiffPathItem item(0x5678, IfdId::exifId);
    EXPECT_EQ(item.group(), IfdId::exifId);
}

// Test that different TiffPathItem objects are independent
TEST(TiffPathItemTest_226, MultipleItemsIndependent_226) {
    TiffPathItem item1(0x0001, IfdId::ifd0Id);
    TiffPathItem item2(0x0002, IfdId::exifId);
    
    EXPECT_NE(item1.extendedTag(), item2.extendedTag());
    EXPECT_NE(item1.group(), item2.group());
    
    EXPECT_EQ(item1.extendedTag(), 0x0001u);
    EXPECT_EQ(item2.extendedTag(), 0x0002u);
    EXPECT_EQ(item1.group(), IfdId::ifd0Id);
    EXPECT_EQ(item2.group(), IfdId::exifId);
}

// Test constexpr construction
TEST(TiffPathItemTest_226, ConstexprConstruction_226) {
    constexpr TiffPathItem item(0xABCD, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0xABCDu);
    EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

// Test with large extended tag value and verify both tag and extendedTag
TEST(TiffPathItemTest_226, LargeExtendedTagConsistency_226) {
    TiffPathItem item(0xDEADBEEF, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), 0xDEADBEEFu);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(0xBEEF));
}
