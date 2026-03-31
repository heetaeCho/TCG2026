#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffDataEntryBaseTest_242 : public ::testing::Test {
protected:
};

// Test that szGroup() returns the group ID passed to the constructor
TEST_F(TiffDataEntryBaseTest_242, SzGroupReturnsConstructorValue_242) {
    // Use known IfdId values
    uint16_t tag = 0x0111;       // StripOffsets tag
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;     // StripByteCounts tag
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szGroup(), szGroup);
}

// Test that szTag() returns the szTag passed to the constructor
TEST_F(TiffDataEntryBaseTest_242, SzTagReturnsConstructorValue_242) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szTag(), szTag);
}

// Test with different IfdId values for szGroup
TEST_F(TiffDataEntryBaseTest_242, SzGroupWithDifferentIfdId_242) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd1Id;
    uint16_t szTag = 0x0202;
    IfdId szGroup = IfdId::ifd1Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szGroup(), IfdId::ifd1Id);
}

// Test with different szTag values
TEST_F(TiffDataEntryBaseTest_242, SzTagWithDifferentValues_242) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd1Id;
    uint16_t szTag = 0x0202;
    IfdId szGroup = IfdId::ifd1Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szTag(), 0x0202);
}

// Test that group and tag from base class are accessible
TEST_F(TiffDataEntryBaseTest_242, BaseClassTagAndGroup_242) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.tag(), tag);
    EXPECT_EQ(entry.group(), group);
}

// Test with zero tag values (boundary)
TEST_F(TiffDataEntryBaseTest_242, ZeroTagValues_242) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0000;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szTag(), 0x0000);
    EXPECT_EQ(entry.szGroup(), IfdId::ifd0Id);
}

// Test with max uint16 tag value (boundary)
TEST_F(TiffDataEntryBaseTest_242, MaxTagValue_242) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0xFFFF;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.szTag(), 0xFFFF);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

// Test setStrips with nullptr values
TEST_F(TiffDataEntryBaseTest_242, SetStripsWithNullptr_242) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0117;
    IfdId szGroup = IfdId::ifd0Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    // Should handle nullptr gracefully
    EXPECT_NO_THROW(entry.setStrips(nullptr, nullptr, 0, 0));
}

// Test that szGroup and szTag are independent of base tag/group
TEST_F(TiffDataEntryBaseTest_242, SzFieldsIndependentOfBaseFields_242) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    uint16_t szTag = 0x0202;
    IfdId szGroup = IfdId::ifd1Id;

    TiffDataEntry entry(tag, group, szTag, szGroup);
    EXPECT_EQ(entry.tag(), tag);
    EXPECT_EQ(entry.group(), group);
    EXPECT_EQ(entry.szTag(), szTag);
    EXPECT_EQ(entry.szGroup(), szGroup);
    EXPECT_NE(entry.tag(), entry.szTag());
    EXPECT_NE(entry.group(), entry.szGroup());
}
