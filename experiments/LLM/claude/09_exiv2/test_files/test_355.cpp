#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSizeEntryTest_355 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that the constructor properly stores dtTag
TEST_F(TiffSizeEntryTest_355, ConstructorStoresDtTag_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), dtTag);
}

// Test that the constructor properly stores dtGroup
TEST_F(TiffSizeEntryTest_355, ConstructorStoresDtGroup_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test that tag is properly inherited from TiffEntryBase
TEST_F(TiffSizeEntryTest_355, ConstructorStoresTag_355) {
    uint16_t tag = 0x0202;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.tag(), tag);
}

// Test with zero values for dtTag
TEST_F(TiffSizeEntryTest_355, ZeroDtTag_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0000;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), 0x0000);
}

// Test with maximum uint16 value for dtTag
TEST_F(TiffSizeEntryTest_355, MaxDtTag_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0xFFFF;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), 0xFFFF);
}

// Test with different group values
TEST_F(TiffSizeEntryTest_355, DifferentGroups_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::exifId;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::gpsId;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), dtTag);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test that two entries with different parameters are independent
TEST_F(TiffSizeEntryTest_355, TwoEntriesAreIndependent_355) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    TiffSizeEntry entry2(0x0200, IfdId::ifd1Id, 0x0222, IfdId::ifd1Id);

    EXPECT_EQ(entry1.dtTag(), 0x0111);
    EXPECT_EQ(entry1.dtGroup(), IfdId::ifd0Id);
    EXPECT_EQ(entry2.dtTag(), 0x0222);
    EXPECT_EQ(entry2.dtGroup(), IfdId::ifd1Id);
}

// Test tag and dtTag can be the same
TEST_F(TiffSizeEntryTest_355, TagAndDtTagSame_355) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0100;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.tag(), tag);
    EXPECT_EQ(entry.dtTag(), dtTag);
    EXPECT_EQ(entry.tag(), entry.dtTag());
}
