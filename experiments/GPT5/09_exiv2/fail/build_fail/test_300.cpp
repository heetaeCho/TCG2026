#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "value.hpp"

namespace Exiv2 {
namespace Internal {

// Test case for TiffEntryBase constructor and basic initialization
TEST_F(TiffEntryBaseTest_300, Constructor_InitializesCorrectly_300) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);

    EXPECT_EQ(entry.tiffType(), tiffType);
    EXPECT_EQ(entry.offset(), 0);
    EXPECT_EQ(entry.idx(), 0);
}

// Test case for updating value
TEST_F(TiffEntryBaseTest_301, UpdateValue_ChangesSizeCorrectly_301) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);

    auto value = std::make_unique<Value>(TypeId::kInt16);
    ByteOrder byteOrder = ByteOrder::BigEndian;

    entry.updateValue(std::move(value), byteOrder);

    // Assuming updateValue should change internal state
    EXPECT_EQ(entry.pValue()->size(), 2);  // Example for 16-bit type
}

// Test case for setting data with pointer
TEST_F(TiffEntryBaseTest_302, SetData_ValidPointer_302) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);
    size_t dataSize = 10;
    byte* pData = new byte[dataSize];
    auto storage = std::make_shared<DataBuf>();

    entry.setData(pData, dataSize, storage);

    EXPECT_EQ(entry.offset(), dataSize);
    EXPECT_EQ(entry.pData(), pData);
}

// Test case for setting data with shared buffer
TEST_F(TiffEntryBaseTest_303, SetData_SharedBuffer_303) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);
    auto storage = std::make_shared<DataBuf>();

    entry.setData(storage);

    EXPECT_EQ(entry.storage(), storage);
}

// Test for exceptional case: null value passed to updateValue
TEST_F(TiffEntryBaseTest_304, UpdateValue_NullValue_304) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);

    entry.updateValue(nullptr, ByteOrder::BigEndian);

    // Since value is null, internal state shouldn't be altered
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test case for checking the clone functionality of Value
TEST_F(TiffEntryBaseTest_305, ValueClone_CreatesValidClone_305) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_SHORT;

    TiffEntryBase entry(tag, group, tiffType);
    auto value = std::make_unique<Value>(TypeId::kInt16);
    ByteOrder byteOrder = ByteOrder::BigEndian;

    entry.updateValue(std::move(value), byteOrder);
    auto clonedValue = entry.pValue()->clone();

    EXPECT_NE(clonedValue, nullptr);
    EXPECT_EQ(clonedValue->size(), entry.pValue()->size());
}

// Boundary test case: Testing extreme size for data
TEST_F(TiffEntryBaseTest_306, SetData_LargeBuffer_306) {
    uint16_t tag = 1;
    IfdId group = IfdId::TIFF;
    TiffType tiffType = TiffType::TIFF_LONG;

    TiffEntryBase entry(tag, group, tiffType);
    size_t dataSize = 1000000;
    byte* pData = new byte[dataSize];
    auto storage = std::make_shared<DataBuf>();

    entry.setData(pData, dataSize, storage);

    EXPECT_EQ(entry.offset(), dataSize);
    EXPECT_EQ(entry.pData(), pData);
}

}  // namespace Internal
}  // namespace Exiv2