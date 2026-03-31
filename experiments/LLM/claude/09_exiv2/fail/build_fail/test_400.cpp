#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/tags.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffImageEntry inherits from TiffDataEntryBase which inherits from TiffEntryBase
// which inherits from TiffComponent, we need to construct it properly.
// The key function under test is doSizeData() which checks if group() > IfdId::mnId.

// We need a concrete TiffImageEntry to test. Based on the interface, TiffImageEntry
// inherits from TiffDataEntryBase. We'll construct instances with different groups
// to test the doSizeData() behavior through the public sizeData() interface.

class TiffImageEntryTest_400 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that sizeData() returns 0 when group is less than or equal to mnId
// IfdId::mnId = 20, so groups <= 20 should result in sizeData() returning 0
// (since no strips are set, sizeImage() should also be 0, but the condition won't be entered)
TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroWhenGroupLessThanMnId_400) {
    // Use ifd0Id which is 1, well below mnId (20)
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroWhenGroupEqualToMnId_400) {
    // mnId = 20, group() == mnId should NOT satisfy group() > mnId
    TiffImageEntry entry(0x0111, IfdId::mnId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroWhenGroupGreaterThanMnIdButNoStrips_400) {
    // canonId = 21 which is > mnId (20), so the condition is true
    // But with no strips set, sizeImage() should return 0
    TiffImageEntry entry(0x0111, IfdId::canonId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroForExifId_400) {
    // exifId = 5, which is < mnId (20)
    TiffImageEntry entry(0x0111, IfdId::exifId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroForGpsId_400) {
    // gpsId = 6, which is < mnId (20)
    TiffImageEntry entry(0x0111, IfdId::gpsId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataReturnsZeroForIfdIdNotSet_400) {
    // ifdIdNotSet = 0
    TiffImageEntry entry(0x0111, IfdId::ifdIdNotSet);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataForHighGroupIdWithoutStrips_400) {
    // lastId = 140, well above mnId
    // Without strips, sizeImage should be 0, so sizeData returns 0
    TiffImageEntry entry(0x0111, IfdId::lastId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

TEST_F(TiffImageEntryTest_400, SizeDataForPanaRawId_400) {
    // panaRawId = 19, which is < mnId (20)
    TiffImageEntry entry(0x0111, IfdId::panaRawId);
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

// Test the boundary: group just above mnId
TEST_F(TiffImageEntryTest_400, SizeDataForCanonIdJustAboveMnId_400) {
    // canonId = 21, which is > mnId (20) — boundary case
    TiffImageEntry entry(0x0111, IfdId::canonId);
    size_t result = entry.sizeData();
    // No strips set, so even though condition is true, sizeImage() returns 0
    EXPECT_EQ(result, 0u);
}

// Test sizeImage returns 0 for a freshly constructed entry
TEST_F(TiffImageEntryTest_400, SizeImageReturnsZeroForNewEntry_400) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t result = entry.sizeImage();
    EXPECT_EQ(result, 0u);
}

// Test that tag() returns the tag set during construction
TEST_F(TiffImageEntryTest_400, TagReturnsCorrectValue_400) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0111);
}

// Test that group() returns the group set during construction
TEST_F(TiffImageEntryTest_400, GroupReturnsCorrectValue_400) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

// Test with different tag values
TEST_F(TiffImageEntryTest_400, DifferentTagValues_400) {
    TiffImageEntry entry1(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(entry1.tag(), 0x0000);

    TiffImageEntry entry2(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
}

// Test size() for a freshly constructed entry
TEST_F(TiffImageEntryTest_400, SizeReturnsValueForNewEntry_400) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    // A fresh entry with no data should have some defined size behavior
    size_t result = entry.size();
    // We just verify it doesn't crash; the actual value depends on implementation
    EXPECT_GE(result, 0u);
}

// Test count() for a freshly constructed entry
TEST_F(TiffImageEntryTest_400, CountReturnsValueForNewEntry_400) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t result = entry.count();
    EXPECT_GE(result, 0u);
}

// Test that multiple entries with different groups behave correctly
TEST_F(TiffImageEntryTest_400, MultipleEntriesWithDifferentGroups_400) {
    TiffImageEntry entryLow(0x0111, IfdId::ifd0Id);    // group < mnId
    TiffImageEntry entryMn(0x0111, IfdId::mnId);         // group == mnId
    TiffImageEntry entryHigh(0x0111, IfdId::canonId);     // group > mnId

    EXPECT_EQ(entryLow.sizeData(), 0u);
    EXPECT_EQ(entryMn.sizeData(), 0u);
    EXPECT_EQ(entryHigh.sizeData(), 0u);  // No strips, so 0 even though group > mnId
}

// Test with subImage IDs (all < mnId)
TEST_F(TiffImageEntryTest_400, SizeDataForSubImageIds_400) {
    TiffImageEntry entry1(0x0111, IfdId::subImage1Id);  // 9
    TiffImageEntry entry2(0x0111, IfdId::subImage9Id);  // 17
    
    EXPECT_EQ(entry1.sizeData(), 0u);
    EXPECT_EQ(entry2.sizeData(), 0u);
}

// Test with Sony and other manufacturer IDs (all > mnId)
TEST_F(TiffImageEntryTest_400, SizeDataForManufacturerIds_400) {
    TiffImageEntry entrySony(0x0111, IfdId::sony1Id);     // 122
    TiffImageEntry entryNikon(0x0111, IfdId::nikon3Id);    // 64
    TiffImageEntry entrySigma(0x0111, IfdId::sigmaId);     // 121
    
    // All > mnId, but no strips set, so sizeData should be 0
    EXPECT_EQ(entrySony.sizeData(), 0u);
    EXPECT_EQ(entryNikon.sizeData(), 0u);
    EXPECT_EQ(entrySigma.sizeData(), 0u);
}
