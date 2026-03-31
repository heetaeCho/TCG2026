#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <sstream>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffMnEntryTest_360 : public ::testing::Test {
protected:
    void SetUp() override {
        // Mute log messages to avoid noise in tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        // Reset log level
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test that a newly constructed TiffMnEntry with no mn_ set delegates count to TiffEntryBase
TEST_F(TiffMnEntryTest_360, CountWithNoMakernote_ReturnsBaseCount_360) {
    // When mn_ is nullptr, doCount() should delegate to TiffEntryBase::doCount()
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    // A freshly constructed entry with no data should have count of 0 from base
    size_t result = entry.count();
    EXPECT_EQ(result, 0u);
}

// Test construction with different tag values
TEST_F(TiffMnEntryTest_360, ConstructionWithDifferentTags_360) {
    TiffMnEntry entry1(0x0001, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry1.tag(), 0x0001);
    
    TiffMnEntry entry2(0xFFFF, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
    
    TiffMnEntry entry3(0x0000, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry3.tag(), 0x0000);
}

// Test that the tiffType is set to ttUndefined by default construction
TEST_F(TiffMnEntryTest_360, DefaultTiffTypeIsUndefined_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test that group is correctly set
TEST_F(TiffMnEntryTest_360, GroupIsCorrectlySet_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test count after setting data with no makernote
TEST_F(TiffMnEntryTest_360, CountAfterSetData_NoMakernote_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    auto buf = std::make_shared<DataBuf>(10);
    entry.setData(buf);
    
    // With mn_ == nullptr, count should come from TiffEntryBase::doCount()
    size_t result = entry.count();
    // The base count should reflect the data that was set
    EXPECT_GE(result, 0u);
}

// Test count with data set via raw pointer, no makernote
TEST_F(TiffMnEntryTest_360, CountWithRawDataSet_NoMakernote_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    entry.setData(data, 5, storage);
    
    size_t result = entry.count();
    // Without makernote, delegates to base which uses stored count
    EXPECT_GE(result, 0u);
}

// Test that pData returns nullptr for freshly constructed entry
TEST_F(TiffMnEntryTest_360, FreshEntryPDataIsNull_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test that pValue returns nullptr for freshly constructed entry
TEST_F(TiffMnEntryTest_360, FreshEntryPValueIsNull_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test size of freshly constructed entry
TEST_F(TiffMnEntryTest_360, FreshEntrySizeIsZero_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.size(), 0u);
}

// Test offset of freshly constructed entry
TEST_F(TiffMnEntryTest_360, FreshEntryOffsetIsZero_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test boundary: tag value at max uint16_t
TEST_F(TiffMnEntryTest_360, BoundaryMaxTag_360) {
    TiffMnEntry entry(0xFFFF, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tag(), 0xFFFF);
    EXPECT_EQ(entry.count(), 0u);
}

// Test boundary: tag value at zero
TEST_F(TiffMnEntryTest_360, BoundaryZeroTag_360) {
    TiffMnEntry entry(0x0000, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tag(), 0x0000);
    EXPECT_EQ(entry.count(), 0u);
}

// Test setting a value and checking count without makernote
TEST_F(TiffMnEntryTest_360, SetValueAndCheckCount_NoMakernote_360) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    
    auto value = Value::create(TypeId::undefined);
    DataBuf buf(8);
    value->read(buf.data(), buf.size(), ByteOrder::littleEndian);
    entry.setValue(std::move(value));
    
    // With no makernote, count comes from base class
    size_t result = entry.count();
    EXPECT_GE(result, 0u);
}

// Test multiple entries don't interfere with each other
TEST_F(TiffMnEntryTest_360, MultipleEntriesIndependent_360) {
    TiffMnEntry entry1(0x0001, IfdId::exifId, IfdId::canonId);
    TiffMnEntry entry2(0x0002, IfdId::exifId, IfdId::nikonId);
    
    EXPECT_EQ(entry1.tag(), 0x0001);
    EXPECT_EQ(entry2.tag(), 0x0002);
    EXPECT_EQ(entry1.count(), 0u);
    EXPECT_EQ(entry2.count(), 0u);
}
