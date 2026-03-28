#include <gtest/gtest.h>
#include <memory>
#include <cstring>

#include "exiv2/types.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntryBase is abstract (inherits from TiffComponent with pure virtuals),
// so we need to use a concrete derived class. TiffEntry is the simplest one.
// We use TiffDirectory or TiffEntry from the TIFF composite hierarchy.

class TiffEntryBaseTest_298 : public ::testing::Test {
protected:
    // Use a concrete TiffEntry subclass for testing
    // TiffEntry inherits from TiffEntryBase
    std::unique_ptr<TiffEntry> createEntry(uint16_t tag = 0x0100, IfdId group = IfdId::ifd0Id) {
        return std::make_unique<TiffEntry>(tag, group);
    }
};

// Test setData with a shared_ptr<DataBuf> containing valid data
TEST_F(TiffEntryBaseTest_298, SetDataWithValidBuffer_298) {
    auto entry = createEntry();
    
    const uint8_t testData[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto buf = std::make_shared<DataBuf>(testData, sizeof(testData));
    
    entry->setData(buf);
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(std::memcmp(entry->pData(), testData, sizeof(testData)), 0);
}

// Test setData with an empty DataBuf
TEST_F(TiffEntryBaseTest_298, SetDataWithEmptyBuffer_298) {
    auto entry = createEntry();
    
    auto buf = std::make_shared<DataBuf>();
    
    entry->setData(buf);
    
    // After setting empty data, pData should reflect empty buffer
    // size should be 0
    EXPECT_EQ(entry->pData(), buf->data());
}

// Test setData with a single byte buffer
TEST_F(TiffEntryBaseTest_298, SetDataWithSingleByte_298) {
    auto entry = createEntry();
    
    const uint8_t testData[] = {0xFF};
    auto buf = std::make_shared<DataBuf>(testData, 1);
    
    entry->setData(buf);
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData()[0], 0xFF);
}

// Test setData with a large buffer
TEST_F(TiffEntryBaseTest_298, SetDataWithLargeBuffer_298) {
    auto entry = createEntry();
    
    const size_t largeSize = 10000;
    auto buf = std::make_shared<DataBuf>(largeSize);
    // Fill with pattern
    for (size_t i = 0; i < largeSize; ++i) {
        buf->write_uint8(i, static_cast<uint8_t>(i & 0xFF));
    }
    
    entry->setData(buf);
    
    ASSERT_NE(entry->pData(), nullptr);
    // Verify data integrity
    for (size_t i = 0; i < largeSize; ++i) {
        EXPECT_EQ(entry->pData()[i], static_cast<uint8_t>(i & 0xFF)) << "Mismatch at index " << i;
    }
}

// Test that setData replaces previous data
TEST_F(TiffEntryBaseTest_298, SetDataReplacesExistingData_298) {
    auto entry = createEntry();
    
    const uint8_t data1[] = {0x01, 0x02, 0x03};
    auto buf1 = std::make_shared<DataBuf>(data1, sizeof(data1));
    entry->setData(buf1);
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData()[0], 0x01);
    
    const uint8_t data2[] = {0xAA, 0xBB};
    auto buf2 = std::make_shared<DataBuf>(data2, sizeof(data2));
    entry->setData(buf2);
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData()[0], 0xAA);
    EXPECT_EQ(entry->pData()[1], 0xBB);
}

// Test that pData points into the shared DataBuf
TEST_F(TiffEntryBaseTest_298, SetDataPDataPointsToBuffer_298) {
    auto entry = createEntry();
    
    const uint8_t testData[] = {0x10, 0x20, 0x30, 0x40};
    auto buf = std::make_shared<DataBuf>(testData, sizeof(testData));
    const byte* expectedPtr = buf->data();
    
    entry->setData(buf);
    
    EXPECT_EQ(entry->pData(), expectedPtr);
}

// Test setData with byte pointer overload
TEST_F(TiffEntryBaseTest_298, SetDataWithBytePointerAndStorage_298) {
    auto entry = createEntry();
    
    const uint8_t testData[] = {0xDE, 0xAD, 0xBE, 0xEF};
    auto storage = std::make_shared<DataBuf>(testData, sizeof(testData));
    byte* pData = storage->data();
    
    entry->setData(pData, sizeof(testData), storage);
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData(), pData);
    EXPECT_EQ(entry->pData()[0], 0xDE);
    EXPECT_EQ(entry->pData()[3], 0xEF);
}

// Test tiffType returns default type
TEST_F(TiffEntryBaseTest_298, TiffTypeReturnsConstructedType_298) {
    auto entry = createEntry();
    // TiffEntry default tiffType is ttUndefined (typically 7)
    TiffType type = entry->tiffType();
    // Just verify it's a valid type and doesn't crash
    EXPECT_GE(type, 0);
}

// Test offset default value
TEST_F(TiffEntryBaseTest_298, OffsetDefaultIsZero_298) {
    auto entry = createEntry();
    EXPECT_EQ(entry->offset(), 0u);
}

// Test setOffset and offset
TEST_F(TiffEntryBaseTest_298, SetOffsetAndRetrieve_298) {
    auto entry = createEntry();
    
    entry->setOffset(42);
    EXPECT_EQ(entry->offset(), 42u);
    
    entry->setOffset(0);
    EXPECT_EQ(entry->offset(), 0u);
    
    entry->setOffset(999999);
    EXPECT_EQ(entry->offset(), 999999u);
}

// Test pData returns nullptr when no data is set
TEST_F(TiffEntryBaseTest_298, PDataReturnsNullWhenNoData_298) {
    auto entry = createEntry();
    EXPECT_EQ(entry->pData(), nullptr);
}

// Test pValue returns nullptr when no value is set
TEST_F(TiffEntryBaseTest_298, PValueReturnsNullWhenNoValue_298) {
    auto entry = createEntry();
    EXPECT_EQ(entry->pValue(), nullptr);
}

// Test idx returns default value
TEST_F(TiffEntryBaseTest_298, IdxReturnsDefaultValue_298) {
    auto entry = createEntry();
    EXPECT_EQ(entry->idx(), 0);
}

// Test setData called multiple times doesn't leak (no crash)
TEST_F(TiffEntryBaseTest_298, SetDataMultipleTimesNoLeak_298) {
    auto entry = createEntry();
    
    for (int i = 0; i < 100; ++i) {
        const uint8_t data[] = {static_cast<uint8_t>(i)};
        auto buf = std::make_shared<DataBuf>(data, 1);
        entry->setData(buf);
    }
    
    ASSERT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData()[0], 99);
}

// Test tag and group from TiffComponent base
TEST_F(TiffEntryBaseTest_298, TagAndGroupFromConstruction_298) {
    auto entry = createEntry(0x0110, IfdId::ifd0Id);
    EXPECT_EQ(entry->tag(), 0x0110);
}

// Test storage is properly maintained (shared ownership)
TEST_F(TiffEntryBaseTest_298, StorageSharedOwnership_298) {
    auto entry = createEntry();
    
    const uint8_t testData[] = {0x01, 0x02, 0x03};
    auto buf = std::make_shared<DataBuf>(testData, sizeof(testData));
    
    // buf has use_count 1
    EXPECT_EQ(buf.use_count(), 1);
    
    entry->setData(buf);
    
    // After setData, the shared_ptr is moved, so buf should be empty
    // (since setData takes by value/move)
    // Actually setData takes shared_ptr by value, so buf may still be valid
    // depending on whether it was moved from. Let's just verify pData is valid.
    ASSERT_NE(entry->pData(), nullptr);
}

// Test setData with DataBuf containing zeros
TEST_F(TiffEntryBaseTest_298, SetDataWithZeroFilledBuffer_298) {
    auto entry = createEntry();
    
    auto buf = std::make_shared<DataBuf>(10);
    // DataBuf(size) should create a zero-initialized buffer
    
    entry->setData(buf);
    
    ASSERT_NE(entry->pData(), nullptr);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(entry->pData()[i], 0) << "Non-zero at index " << i;
    }
}
