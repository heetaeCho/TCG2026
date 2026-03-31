#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class TiffSizeEntryTest_243 : public ::testing::Test {
protected:
    // Helper to create TiffSizeEntry objects for testing
};

// Test that dtTag() returns the dtTag value passed in constructor
TEST_F(TiffSizeEntryTest_243, DtTagReturnsConstructorValue_243) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;
    
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(entry.dtTag(), dtTag);
}

// Test that dtGroup() returns the dtGroup value passed in constructor
TEST_F(TiffSizeEntryTest_243, DtGroupReturnsConstructorValue_243) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0201;
    IfdId dtGroup = IfdId::ifd1Id;
    
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test with zero dtTag value
TEST_F(TiffSizeEntryTest_243, DtTagZeroValue_243) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0000;
    IfdId dtGroup = IfdId::ifd0Id;
    
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(entry.dtTag(), 0x0000);
}

// Test with maximum dtTag value
TEST_F(TiffSizeEntryTest_243, DtTagMaxValue_243) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0xFFFF;
    IfdId dtGroup = IfdId::ifd0Id;
    
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(entry.dtTag(), 0xFFFF);
}

// Test that tag and group from base class are independent of dtTag and dtGroup
TEST_F(TiffSizeEntryTest_243, DtTagIndependentOfBaseTag_243) {
    uint16_t tag = 0x1234;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x5678;
    IfdId dtGroup = IfdId::ifd1Id;
    
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    
    EXPECT_EQ(entry.dtTag(), 0x5678);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
    // Verify base class tag is different from dtTag
    EXPECT_EQ(entry.tag(), 0x1234);
}

// Test multiple instances have independent values
TEST_F(TiffSizeEntryTest_243, MultipleInstancesIndependent_243) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd1Id);
    TiffSizeEntry entry2(0x0300, IfdId::ifd1Id, 0x0401, IfdId::ifd0Id);
    
    EXPECT_EQ(entry1.dtTag(), 0x0201);
    EXPECT_EQ(entry2.dtTag(), 0x0401);
    EXPECT_NE(entry1.dtTag(), entry2.dtTag());
}

// Test dtGroup with different IfdId values
TEST_F(TiffSizeEntryTest_243, DtGroupDifferentIfdIds_243) {
    TiffSizeEntry entry1(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd0Id);
    TiffSizeEntry entry2(0x0100, IfdId::ifd0Id, 0x0201, IfdId::ifd1Id);
    
    EXPECT_EQ(entry1.dtGroup(), IfdId::ifd0Id);
    EXPECT_EQ(entry2.dtGroup(), IfdId::ifd1Id);
}

// Test consistency - calling dtTag() multiple times returns same value
TEST_F(TiffSizeEntryTest_243, DtTagConsistentOnMultipleCalls_243) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0999, IfdId::ifd1Id);
    
    EXPECT_EQ(entry.dtTag(), 0x0999);
    EXPECT_EQ(entry.dtTag(), 0x0999);
    EXPECT_EQ(entry.dtTag(), 0x0999);
}

// Test consistency - calling dtGroup() multiple times returns same value
TEST_F(TiffSizeEntryTest_243, DtGroupConsistentOnMultipleCalls_243) {
    TiffSizeEntry entry(0x0100, IfdId::ifd0Id, 0x0999, IfdId::ifd1Id);
    
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
}
