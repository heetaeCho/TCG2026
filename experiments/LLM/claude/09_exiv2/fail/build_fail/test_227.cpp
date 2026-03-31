#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test normal construction and group() accessor
TEST(TiffPathItemTest_227, GroupReturnsCorrectValue_227) {
    TiffPathItem item(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

TEST(TiffPathItemTest_227, GroupReturnsExifIfd_227) {
    TiffPathItem item(0x0002, IfdId::exifId);
    EXPECT_EQ(item.group(), IfdId::exifId);
}

TEST(TiffPathItemTest_227, TagReturnsCorrectValue_227) {
    TiffPathItem item(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(0x0100));
}

TEST(TiffPathItemTest_227, ExtendedTagReturnsCorrectValue_227) {
    TiffPathItem item(0x00010002, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(0x00010002));
}

TEST(TiffPathItemTest_227, TagTruncatesExtendedTag_227) {
    // tag() returns uint16_t, so it should be the lower 16 bits of extendedTag
    uint32_t extendedTag = 0x0001ABCD;
    TiffPathItem item(extendedTag, IfdId::ifd0Id);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(extendedTag & 0xFFFF));
}

TEST(TiffPathItemTest_227, ZeroExtendedTagAndGroup_227) {
    TiffPathItem item(0x0000, IfdId::ifdIdNotSet);
    EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(0));
    EXPECT_EQ(item.group(), IfdId::ifdIdNotSet);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(0));
}

TEST(TiffPathItemTest_227, MaxExtendedTag_227) {
    TiffPathItem item(0xFFFFFFFF, IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(0xFFFFFFFF));
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(0xFFFF));
}

TEST(TiffPathItemTest_227, DifferentGroupValues_227) {
    TiffPathItem item1(0x0001, IfdId::ifd0Id);
    TiffPathItem item2(0x0001, IfdId::ifd1Id);
    EXPECT_NE(item1.group(), item2.group());
}

TEST(TiffPathItemTest_227, SameExtendedTagDifferentGroup_227) {
    TiffPathItem item1(0x0100, IfdId::ifd0Id);
    TiffPathItem item2(0x0100, IfdId::exifId);
    EXPECT_EQ(item1.extendedTag(), item2.extendedTag());
    EXPECT_EQ(item1.tag(), item2.tag());
    EXPECT_NE(item1.group(), item2.group());
}

TEST(TiffPathItemTest_227, GpsGroup_227) {
    TiffPathItem item(0x0001, IfdId::gpsId);
    EXPECT_EQ(item.group(), IfdId::gpsId);
}

TEST(TiffPathItemTest_227, ConstexprConstruction_227) {
    constexpr TiffPathItem item(0x0042, IfdId::ifd0Id);
    EXPECT_EQ(item.group(), IfdId::ifd0Id);
    EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(0x0042));
}
