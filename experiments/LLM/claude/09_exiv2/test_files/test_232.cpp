#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test that tag() returns the lower 16 bits of extendedTag_
TEST(TiffMappingInfoTest_232, TagReturnsLower16Bits_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0x1234;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x1234));
}

TEST(TiffMappingInfoTest_232, TagReturnsZeroWhenExtendedTagIsZero_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0));
}

TEST(TiffMappingInfoTest_232, TagTruncatesHighBits_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0x10001;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x0001));
}

TEST(TiffMappingInfoTest_232, TagMaxUint16Value_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0xFFFF;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0xFFFF));
}

TEST(TiffMappingInfoTest_232, TagWithLargeExtendedTag_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0xABCD1234;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x1234));
}

TEST(TiffMappingInfoTest_232, TagWith32BitMaxValue_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0xFFFFFFFF;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0xFFFF));
}

TEST(TiffMappingInfoTest_232, TagWithOnlyHighBitsSet_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0xFFFF0000;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x0000));
}

TEST(TiffMappingInfoTest_232, TagWithSingleBitSet_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0x0001;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x0001));
}

TEST(TiffMappingInfoTest_232, TagWithBit15Set_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0x8000;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x8000));
}

TEST(TiffMappingInfoTest_232, TagWithBit16Set_232) {
    TiffMappingInfo info{};
    info.extendedTag_ = 0x10000;
    EXPECT_EQ(info.tag(), static_cast<uint16_t>(0x0000));
}
