#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSizeEntryTest_244 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructor properly sets dtGroup
TEST_F(TiffSizeEntryTest_244, ConstructorSetsDtGroup_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0200, IfdId::ifd1Id);
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
}

// Test that constructor properly sets dtTag
TEST_F(TiffSizeEntryTest_244, ConstructorSetsDtTag_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0200, IfdId::ifd1Id);
    EXPECT_EQ(entry.dtTag(), 0x0200);
}

// Test that inherited tag() returns the correct tag
TEST_F(TiffSizeEntryTest_244, ConstructorSetsTag_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0200, IfdId::ifd1Id);
    EXPECT_EQ(entry.tag(), 0x0100);
}

// Test that inherited group() returns the correct group
TEST_F(TiffSizeEntryTest_244, ConstructorSetsGroup_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0200, IfdId::ifd1Id);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

// Test with zero values for tag and dtTag
TEST_F(TiffSizeEntryTest_244, ZeroTagValues_244) {
    TiffSizeEntry entry(0x0000, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0000);
    EXPECT_EQ(entry.dtTag(), 0x0000);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd0Id);
}

// Test with maximum uint16_t values
TEST_F(TiffSizeEntryTest_244, MaxTagValues_244) {
    TiffSizeEntry entry(0xFFFF, IfdId::ifd0Id, 0xFFFF, IfdId::ifd1Id);
    EXPECT_EQ(entry.tag(), 0xFFFF);
    EXPECT_EQ(entry.dtTag(), 0xFFFF);
}

// Test that dtGroup and group can be different
TEST_F(TiffSizeEntryTest_244, DifferentGroupAndDtGroup_244) {
    TiffSizeEntry entry(0x0001, IfdId::ifd0Id, 0x0002, IfdId::exifId);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry.dtGroup(), IfdId::exifId);
    EXPECT_NE(entry.group(), entry.dtGroup());
}

// Test that dtTag and tag can be different
TEST_F(TiffSizeEntryTest_244, DifferentTagAndDtTag_244) {
    TiffSizeEntry entry(0x0001, IfdId::ifd0Id, 0x0002, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0001);
    EXPECT_EQ(entry.dtTag(), 0x0002);
    EXPECT_NE(entry.tag(), entry.dtTag());
}

// Test same group for both group and dtGroup
TEST_F(TiffSizeEntryTest_244, SameGroupAndDtGroup_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0200, IfdId::ifd0Id);
    EXPECT_EQ(entry.group(), entry.dtGroup());
}

// Test same tag for both tag and dtTag
TEST_F(TiffSizeEntryTest_244, SameTagAndDtTag_244) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0100, IfdId::ifd1Id);
    EXPECT_EQ(entry.tag(), entry.dtTag());
}
