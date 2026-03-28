#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSizeEntryTest_289 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffSizeEntry can be constructed with valid parameters
TEST_F(TiffSizeEntryTest_289, ConstructWithValidParameters_289) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd0Id;

    ASSERT_NO_THROW(TiffSizeEntry entry(tag, group, dtTag, dtGroup));
}

// Test dtTag() returns the correct dtTag value
TEST_F(TiffSizeEntryTest_289, DtTagReturnsCorrectValue_289) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    EXPECT_EQ(entry.dtTag(), dtTag);
}

// Test dtGroup() returns the correct dtGroup value
TEST_F(TiffSizeEntryTest_289, DtGroupReturnsCorrectValue_289) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test that different dtTag values are stored correctly
TEST_F(TiffSizeEntryTest_289, DifferentDtTagValues_289) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    TiffSizeEntry entry2(0x0100, IfdId::ifd0Id, 0xFFFF, IfdId::ifd0Id);

    EXPECT_EQ(entry1.dtTag(), 0x0000);
    EXPECT_EQ(entry2.dtTag(), 0xFFFF);
}

// Test that different dtGroup values are stored correctly
TEST_F(TiffSizeEntryTest_289, DifferentDtGroupValues_289) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd0Id);
    TiffSizeEntry entry2(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd1Id);

    EXPECT_EQ(entry1.dtGroup(), IfdId::ifd0Id);
    EXPECT_EQ(entry2.dtGroup(), IfdId::ifd1Id);
}

// Test boundary value for tag - zero
TEST_F(TiffSizeEntryTest_289, BoundaryZeroTag_289) {
    TiffSizeEntry entry(0x0000, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    EXPECT_EQ(entry.dtTag(), 0x0000);
}

// Test boundary value for tag - max uint16
TEST_F(TiffSizeEntryTest_289, BoundaryMaxTag_289) {
    TiffSizeEntry entry(0xFFFF, IfdId::ifd0Id, 0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(entry.dtTag(), 0xFFFF);
}

// Test that the inherited tag() from TiffEntryBase works correctly
TEST_F(TiffSizeEntryTest_289, InheritedTagAccessor_289) {
    uint16_t tag = 0x0102;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    EXPECT_EQ(entry.tag(), tag);
}

// Test that the inherited group() from TiffEntryBase works correctly
TEST_F(TiffSizeEntryTest_289, InheritedGroupAccessor_289) {
    uint16_t tag = 0x0102;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    EXPECT_EQ(entry.group(), group);
}

// Test that two independently constructed entries with same params have same accessors
TEST_F(TiffSizeEntryTest_289, ConsistentConstruction_289) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd1Id);
    TiffSizeEntry entry2(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd1Id);

    EXPECT_EQ(entry1.dtTag(), entry2.dtTag());
    EXPECT_EQ(entry1.dtGroup(), entry2.dtGroup());
    EXPECT_EQ(entry1.tag(), entry2.tag());
    EXPECT_EQ(entry1.group(), entry2.group());
}
