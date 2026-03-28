#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase
class TiffEntryBaseTest_240 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with basic parameters
TEST_F(TiffEntryBaseTest_240, ConstructWithTagAndGroup_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0100);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test that initial pData is null
TEST_F(TiffEntryBaseTest_240, InitialPDataIsNull_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test that initial pValue is null
TEST_F(TiffEntryBaseTest_240, InitialPValueIsNull_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test initial offset is zero
TEST_F(TiffEntryBaseTest_240, InitialOffsetIsZero_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test setOffset
TEST_F(TiffEntryBaseTest_240, SetOffsetChangesOffset_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_240, SetOffsetToZero_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test setOffset with large value
TEST_F(TiffEntryBaseTest_240, SetOffsetLargeValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    size_t largeOffset = 0xFFFFFFFF;
    entry.setOffset(largeOffset);
    EXPECT_EQ(entry.offset(), largeOffset);
}

// Test tiffType returns the type set during construction
TEST_F(TiffEntryBaseTest_240, TiffTypeReturnsConstructedType_240) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(entry1.tiffType(), ttByte);

    TiffEntry entry2(0x0100, IfdId::ifd0Id, ttAscii);
    EXPECT_EQ(entry2.tiffType(), ttAscii);

    TiffEntry entry3(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry3.tiffType(), ttShort);

    TiffEntry entry4(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry4.tiffType(), ttLong);
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_240, SetDataWithSharedDataBuf_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test setData with raw pointer and storage
TEST_F(TiffEntryBaseTest_240, SetDataWithRawPointerAndStorage_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    std::memset(data, 0xCD, 5);
    entry.setData(data, 5, storage);
    EXPECT_EQ(entry.pData(), data);
}

// Test storage returns shared pointer
TEST_F(TiffEntryBaseTest_240, StorageAfterSetData_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(8);
    entry.setData(buf);
    EXPECT_EQ(entry.storage(), buf);
}

// Test storage is initially null
TEST_F(TiffEntryBaseTest_240, StorageInitiallyNull_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.storage(), nullptr);
}

// Test setValue sets a value
TEST_F(TiffEntryBaseTest_240, SetValueSetsValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test setValue with AsciiValue
TEST_F(TiffEntryBaseTest_240, SetValueAsciiString_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Test string");
    entry.setValue(std::move(value));
    const Value* pv = entry.pValue();
    ASSERT_NE(pv, nullptr);
    EXPECT_EQ(pv->toString(), "Test string");
}

// Test setValue with UShortValue
TEST_F(TiffEntryBaseTest_240, SetValueUShort_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.setValue(std::move(value));
    const Value* pv = entry.pValue();
    ASSERT_NE(pv, nullptr);
    EXPECT_EQ(pv->toInt64(), 42);
}

// Test setValue with nullptr-like unique_ptr
TEST_F(TiffEntryBaseTest_240, SetValueWithNullUniquePtr_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    std::unique_ptr<Value> nullValue;
    entry.setValue(std::move(nullValue));
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test updateValue
TEST_F(TiffEntryBaseTest_240, UpdateValueSetsDataAndValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.updateValue(std::move(value), littleEndian);
    const Value* pv = entry.pValue();
    ASSERT_NE(pv, nullptr);
    EXPECT_EQ(pv->toInt64(), 1024);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test updateValue with bigEndian
TEST_F(TiffEntryBaseTest_240, UpdateValueBigEndian_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    auto value = Value::create(unsignedLong);
    value->read("65536");
    entry.updateValue(std::move(value), bigEndian);
    const Value* pv = entry.pValue();
    ASSERT_NE(pv, nullptr);
    EXPECT_EQ(pv->toInt64(), 65536);
}

// Test idx initial value
TEST_F(TiffEntryBaseTest_240, IdxInitialValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

// Test different tag values
TEST_F(TiffEntryBaseTest_240, DifferentTagValues_240) {
    TiffEntry entry1(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry1.tag(), 0x0000);

    TiffEntry entry2(0xFFFF, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
}

// Test setData then storage reflects the same buffer
TEST_F(TiffEntryBaseTest_240, SetDataRawPointerStorageConsistency_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto storage = std::make_shared<DataBuf>(4);
    byte testData[] = {0x01, 0x02, 0x03, 0x04};
    std::memcpy(storage->data(), testData, 4);
    entry.setData(storage->data(), 4, storage);
    
    EXPECT_EQ(entry.pData(), storage->data());
    EXPECT_EQ(entry.storage(), storage);
}

// Test setting data then updating value
TEST_F(TiffEntryBaseTest_240, SetDataThenUpdateValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto buf = std::make_shared<DataBuf>(2);
    buf->data()[0] = 0x00;
    buf->data()[1] = 0x01;
    entry.setData(buf);
    
    auto value = Value::create(unsignedShort);
    value->read("256");
    entry.updateValue(std::move(value), littleEndian);
    
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(), 256);
}

// Test multiple setValue calls replace the previous value
TEST_F(TiffEntryBaseTest_240, SetValueReplacesExistingValue_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    
    auto value1 = Value::create(asciiString);
    value1->read("First");
    entry.setValue(std::move(value1));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "First");
    
    auto value2 = Value::create(asciiString);
    value2->read("Second");
    entry.setValue(std::move(value2));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "Second");
}

// Test setData with empty buffer
TEST_F(TiffEntryBaseTest_240, SetDataWithEmptyBuffer_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // Empty buffer - pData may be null since DataBuf has no data
    // Just ensure no crash
}

// Test updateValue with multiple types
TEST_F(TiffEntryBaseTest_240, UpdateValueWithRational_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttRational);
    auto value = Value::create(unsignedRational);
    value->read("1/2");
    entry.updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry.pValue(), nullptr);
    Rational r = entry.pValue()->toRational();
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test construction with different groups
TEST_F(TiffEntryBaseTest_240, ConstructWithDifferentGroups_240) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry1.group(), IfdId::ifd0Id);

    TiffEntry entry2(0x0100, IfdId::ifd1Id, ttUndefined);
    EXPECT_EQ(entry2.group(), IfdId::ifd1Id);

    TiffEntry entry3(0x0100, IfdId::exifId, ttUndefined);
    EXPECT_EQ(entry3.group(), IfdId::exifId);
}

// Test setOffset multiple times
TEST_F(TiffEntryBaseTest_240, SetOffsetMultipleTimes_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(10);
    EXPECT_EQ(entry.offset(), 10u);
    entry.setOffset(20);
    EXPECT_EQ(entry.offset(), 20u);
    entry.setOffset(30);
    EXPECT_EQ(entry.offset(), 30u);
}

// Test storage keeps shared ownership
TEST_F(TiffEntryBaseTest_240, StorageKeepsSharedOwnership_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    std::shared_ptr<DataBuf> buf;
    {
        auto originalBuf = std::make_shared<DataBuf>(16);
        std::memset(originalBuf->data(), 0xFF, 16);
        entry.setData(originalBuf);
        buf = originalBuf;
    }
    // After originalBuf goes out of scope, entry still holds reference
    EXPECT_EQ(entry.storage(), buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test updateValue stores data accessible via pData
TEST_F(TiffEntryBaseTest_240, UpdateValueMakesDataAccessible_240) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto value = Value::create(unsignedByte);
    value->read("255");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pData(), nullptr);
    // The data should contain the byte representation
    EXPECT_EQ(entry.pData()[0], 255);
}
