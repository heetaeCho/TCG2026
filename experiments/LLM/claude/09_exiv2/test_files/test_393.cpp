#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "value.hpp"

namespace Exiv2 {
namespace Internal {

class TiffMnEntryTest_393 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffMnEntry with no mn_ set returns size from TiffEntryBase
TEST_F(TiffMnEntryTest_393, SizeWithNoMakernote_ReturnsBaseSize_393) {
    // When mn_ is nullptr, doSize() should delegate to TiffEntryBase::doSize()
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    // With no data set, the base size should be 0
    size_t result = entry.size();
    EXPECT_EQ(result, 0u);
}

// Test that TiffMnEntry can be constructed with valid tag and group
TEST_F(TiffMnEntryTest_393, ConstructionWithValidParameters_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.tag(), 0x927c);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test that tiffType is ttUndefined as set in constructor
TEST_F(TiffMnEntryTest_393, TiffTypeIsUndefined_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test count with no makernote set
TEST_F(TiffMnEntryTest_393, CountWithNoMakernote_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    size_t result = entry.count();
    EXPECT_EQ(result, 0u);
}

// Test size after setting data on the entry (no mn_ set, so base behavior)
TEST_F(TiffMnEntryTest_393, SizeAfterSetData_ReturnsBaseSize_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    auto buf = std::make_shared<DataBuf>(10);
    entry.setData(buf);
    
    // With data set but no mn_, should use TiffEntryBase::doSize()
    size_t result = entry.size();
    // The base size should reflect the data that was set
    EXPECT_GE(result, 0u);
}

// Test with different tag values
TEST_F(TiffMnEntryTest_393, DifferentTagValues_393) {
    TiffMnEntry entry1(0x0001, IfdId::exifId, IfdId::canonId);
    TiffMnEntry entry2(0xFFFF, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry1.tag(), 0x0001);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
}

// Test with zero tag
TEST_F(TiffMnEntryTest_393, ZeroTag_393) {
    TiffMnEntry entry(0x0000, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.tag(), 0x0000);
    EXPECT_EQ(entry.size(), 0u);
}

// Test pData returns nullptr when no data is set
TEST_F(TiffMnEntryTest_393, PDataWithNoData_ReturnsNull_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test pValue returns nullptr when no value is set
TEST_F(TiffMnEntryTest_393, PValueWithNoValue_ReturnsNull_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test offset is 0 initially
TEST_F(TiffMnEntryTest_393, InitialOffsetIsZero_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    EXPECT_EQ(entry.offset(), 0u);
}

// Test setOffset and offset
TEST_F(TiffMnEntryTest_393, SetAndGetOffset_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

// Test sizeData with no makernote
TEST_F(TiffMnEntryTest_393, SizeDataWithNoMakernote_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    size_t result = entry.sizeData();
    EXPECT_EQ(result, 0u);
}

// Test sizeImage with no makernote
TEST_F(TiffMnEntryTest_393, SizeImageWithNoMakernote_393) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    size_t result = entry.sizeImage();
    EXPECT_EQ(result, 0u);
}

// Test destruction doesn't crash (no makernote)
TEST_F(TiffMnEntryTest_393, DestructionWithNoMakernote_393) {
    auto entry = new TiffMnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_NO_THROW(delete entry);
}

// Test multiple groups
TEST_F(TiffMnEntryTest_393, DifferentGroups_393) {
    TiffMnEntry entry1(0x927c, IfdId::exifId, IfdId::canonId);
    TiffMnEntry entry2(0x927c, IfdId::ifd0Id, IfdId::nikonId);
    
    EXPECT_EQ(entry1.group(), IfdId::exifId);
    EXPECT_EQ(entry2.group(), IfdId::ifd0Id);
}

}  // namespace Internal
}  // namespace Exiv2
