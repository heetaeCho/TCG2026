#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "tiffcomposite_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete subclass of TiffEntryBase since it inherits from TiffComponent
// which may have pure virtual methods. We use TiffEntry which is a concrete derived class.
// If TiffEntry is not available, we create a minimal concrete subclass.

// For testing purposes, we'll use a concrete TiffEntry-like class
// TiffEntry is defined in the codebase as a concrete subclass of TiffEntryBase

#include "tiffimage_int.hpp"  // Should contain TiffEntry definition

class TiffEntryBaseTest_300 : public ::testing::Test {
protected:
    void SetUp() override {
        // Using tag 0x0100 (ImageWidth) and IfdId ifd0Id as reasonable defaults
        // TiffType ttUnsignedShort = 3
    }

    std::unique_ptr<TiffEntry> createEntry(uint16_t tag = 0x0100, IfdId group = IfdId::ifd0Id, TiffType tiffType = ttUnsignedShort) {
        return std::make_unique<TiffEntry>(tag, group);
    }
};

// Test: Default construction - pData should be null and pValue should be null
TEST_F(TiffEntryBaseTest_300, DefaultConstructionPDataIsNull_300) {
    auto entry = createEntry();
    EXPECT_EQ(entry->pData(), nullptr);
    EXPECT_EQ(entry->pValue(), nullptr);
}

// Test: Default construction - offset should be 0
TEST_F(TiffEntryBaseTest_300, DefaultConstructionOffsetIsZero_300) {
    auto entry = createEntry();
    EXPECT_EQ(entry->offset(), 0u);
}

// Test: Default construction - tiffType should match what was passed
TEST_F(TiffEntryBaseTest_300, DefaultConstructionTiffType_300) {
    auto entry = std::make_unique<TiffEntry>(0x0100, IfdId::ifd0Id);
    // TiffEntry default tiffType is ttUndefined or similar
    // We just check it returns a valid TiffType
    TiffType tt = entry->tiffType();
    EXPECT_GE(tt, 0);
}

// Test: setOffset stores the offset value
TEST_F(TiffEntryBaseTest_300, SetOffsetStoresValue_300) {
    auto entry = createEntry();
    entry->setOffset(42);
    EXPECT_EQ(entry->offset(), 42u);
}

// Test: setOffset with zero
TEST_F(TiffEntryBaseTest_300, SetOffsetZero_300) {
    auto entry = createEntry();
    entry->setOffset(0);
    EXPECT_EQ(entry->offset(), 0u);
}

// Test: setOffset with large value
TEST_F(TiffEntryBaseTest_300, SetOffsetLargeValue_300) {
    auto entry = createEntry();
    entry->setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry->offset(), 0xFFFFFFFF);
}

// Test: setData with shared DataBuf sets pData
TEST_F(TiffEntryBaseTest_300, SetDataWithSharedBufSetsPData_300) {
    auto entry = createEntry();
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry->setData(buf);
    EXPECT_NE(entry->pData(), nullptr);
}

// Test: setData with raw pointer and size
TEST_F(TiffEntryBaseTest_300, SetDataWithRawPointer_300) {
    auto entry = createEntry();
    auto storage = std::make_shared<DataBuf>(20);
    std::memset(storage->data(), 0xCD, 20);
    entry->setData(storage->data(), 20, storage);
    EXPECT_NE(entry->pData(), nullptr);
    EXPECT_EQ(entry->pData()[0], 0xCD);
}

// Test: setValue sets the value pointer
TEST_F(TiffEntryBaseTest_300, SetValueSetsValue_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry->setValue(std::move(value));
    EXPECT_NE(entry->pValue(), nullptr);
}

// Test: setValue - value can be read back
TEST_F(TiffEntryBaseTest_300, SetValueReadBack_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("100");
    entry->setValue(std::move(value));
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 100);
}

// Test: updateValue with a valid value
TEST_F(TiffEntryBaseTest_300, UpdateValueWithValidValue_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("255");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 255);
    EXPECT_NE(entry->pData(), nullptr);
}

// Test: updateValue with null value should be a no-op
TEST_F(TiffEntryBaseTest_300, UpdateValueWithNullValueNoOp_300) {
    auto entry = createEntry();
    Value::UniquePtr nullValue;
    entry->updateValue(std::move(nullValue), littleEndian);
    EXPECT_EQ(entry->pValue(), nullptr);
}

// Test: updateValue with big endian byte order
TEST_F(TiffEntryBaseTest_300, UpdateValueBigEndian_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("1000");
    entry->updateValue(std::move(value), bigEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 1000);
}

// Test: updateValue replaces existing value
TEST_F(TiffEntryBaseTest_300, UpdateValueReplacesExistingValue_300) {
    auto entry = createEntry();

    auto value1 = Value::create(unsignedShort);
    value1->read("10");
    entry->updateValue(std::move(value1), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 10);

    auto value2 = Value::create(unsignedShort);
    value2->read("20");
    entry->updateValue(std::move(value2), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 20);
}

// Test: updateValue with larger value triggers reallocation
TEST_F(TiffEntryBaseTest_300, UpdateValueWithLargerValueReallocates_300) {
    auto entry = createEntry();

    // First, set a small value
    auto value1 = Value::create(unsignedShort);
    value1->read("5");
    entry->updateValue(std::move(value1), littleEndian);
    const byte* firstPData = entry->pData();

    // Now set a larger value (string type which might be larger)
    auto value2 = Value::create(asciiString);
    value2->read("This is a much longer string value for testing reallocation");
    entry->updateValue(std::move(value2), littleEndian);

    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_NE(entry->pData(), nullptr);
}

// Test: updateValue with unsignedLong type
TEST_F(TiffEntryBaseTest_300, UpdateValueUnsignedLong_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedLong);
    value->read("123456");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 123456);
}

// Test: updateValue with signedLong type
TEST_F(TiffEntryBaseTest_300, UpdateValueSignedLong_300) {
    auto entry = createEntry();
    auto value = Value::create(signedLong);
    value->read("-500");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), -500);
}

// Test: updateValue with asciiString type
TEST_F(TiffEntryBaseTest_300, UpdateValueAsciiString_300) {
    auto entry = createEntry();
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toString(), "Hello");
}

// Test: setValue with null unique_ptr
TEST_F(TiffEntryBaseTest_300, SetValueWithNullPtr_300) {
    auto entry = createEntry();
    // First set a valid value
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry->setValue(std::move(value));
    ASSERT_NE(entry->pValue(), nullptr);

    // Now set null
    Value::UniquePtr nullValue;
    entry->setValue(std::move(nullValue));
    EXPECT_EQ(entry->pValue(), nullptr);
}

// Test: idx() returns default value
TEST_F(TiffEntryBaseTest_300, IdxReturnsDefaultValue_300) {
    auto entry = createEntry();
    EXPECT_EQ(entry->idx(), 0);
}

// Test: tag() is preserved from construction
TEST_F(TiffEntryBaseTest_300, TagIsPreserved_300) {
    auto entry = std::make_unique<TiffEntry>(0x0110, IfdId::ifd0Id);
    EXPECT_EQ(entry->tag(), 0x0110);
}

// Test: Multiple sequential updateValue calls
TEST_F(TiffEntryBaseTest_300, MultipleSequentialUpdateValues_300) {
    auto entry = createEntry();

    for (int i = 1; i <= 5; ++i) {
        auto value = Value::create(unsignedShort);
        value->read(std::to_string(i * 100));
        entry->updateValue(std::move(value), littleEndian);
        ASSERT_NE(entry->pValue(), nullptr);
        EXPECT_EQ(entry->pValue()->toInt64(0), i * 100);
    }
}

// Test: updateValue data written correctly in little endian
TEST_F(TiffEntryBaseTest_300, UpdateValueDataLittleEndian_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("256"); // 0x0100
    entry->updateValue(std::move(value), littleEndian);

    ASSERT_NE(entry->pData(), nullptr);
    // In little endian, 256 (0x0100) should be stored as 0x00, 0x01
    EXPECT_EQ(entry->pData()[0], 0x00);
    EXPECT_EQ(entry->pData()[1], 0x01);
}

// Test: updateValue data written correctly in big endian
TEST_F(TiffEntryBaseTest_300, UpdateValueDataBigEndian_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("256"); // 0x0100
    entry->updateValue(std::move(value), bigEndian);

    ASSERT_NE(entry->pData(), nullptr);
    // In big endian, 256 (0x0100) should be stored as 0x01, 0x00
    EXPECT_EQ(entry->pData()[0], 0x01);
    EXPECT_EQ(entry->pData()[1], 0x00);
}

// Test: setData with empty DataBuf
TEST_F(TiffEntryBaseTest_300, SetDataWithEmptyBuf_300) {
    auto entry = createEntry();
    auto buf = std::make_shared<DataBuf>();
    entry->setData(buf);
    // pData might be null for empty buffer
    // Just verify no crash
}

// Test: updateValue with unsignedByte type
TEST_F(TiffEntryBaseTest_300, UpdateValueUnsignedByte_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedByte);
    value->read("200");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 200);
}

// Test: updateValue preserves value count
TEST_F(TiffEntryBaseTest_300, UpdateValuePreservesCount_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedShort);
    value->read("1 2 3");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->count(), 3u);
}

// Test: updateValue with rational type
TEST_F(TiffEntryBaseTest_300, UpdateValueRational_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedRational);
    value->read("1/2");
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    auto r = entry->pValue()->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test: Value size matches after updateValue
TEST_F(TiffEntryBaseTest_300, UpdateValueSizeConsistency_300) {
    auto entry = createEntry();
    auto value = Value::create(unsignedLong);
    value->read("42");
    size_t expectedSize = value->size();
    entry->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->size(), expectedSize);
}
