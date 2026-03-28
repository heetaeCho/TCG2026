#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase
class TiffEntryBaseTest_348 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with valid parameters
TEST_F(TiffEntryBaseTest_348, ConstructWithValidParams_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.tag(), 0x0100);
    EXPECT_EQ(entry.tiffType(), ttUnsignedShort);
}

// Test default state after construction
TEST_F(TiffEntryBaseTest_348, DefaultStateAfterConstruction_348) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAsciiString);
    EXPECT_EQ(entry.tiffType(), ttAsciiString);
    EXPECT_EQ(entry.offset(), 0u);
    EXPECT_EQ(entry.pData(), nullptr);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test idx returns default value
TEST_F(TiffEntryBaseTest_348, IdxReturnsDefault_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.idx(), 0);
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_348, SetDataWithSharedBuf_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_348, SetDataWithRawPointer_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto storage = std::make_shared<DataBuf>(10);
    std::memset(storage->data(), 0xCD, 10);
    entry.setData(storage->data(), 10, storage);
    EXPECT_EQ(entry.pData(), storage->data());
}

// Test setValue with a Value
TEST_F(TiffEntryBaseTest_348, SetValueSetsValue_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test setValue replaces previous value
TEST_F(TiffEntryBaseTest_348, SetValueReplacesExisting_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value1 = Value::create(unsignedShort);
    value1->read("42");
    entry.setValue(std::move(value1));

    auto value2 = Value::create(unsignedShort);
    value2->read("99");
    entry.setValue(std::move(value2));

    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(), 99);
}

// Test updateValue with a Value and byte order
TEST_F(TiffEntryBaseTest_348, UpdateValueSetsValue_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("123");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test setOffset
TEST_F(TiffEntryBaseTest_348, SetOffsetUpdatesOffset_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_348, SetOffsetZero_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test setOffset with large value
TEST_F(TiffEntryBaseTest_348, SetOffsetLargeValue_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFF);
}

// Test construction with different tiff types
TEST_F(TiffEntryBaseTest_348, ConstructWithDifferentTiffTypes_348) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    EXPECT_EQ(entry1.tiffType(), ttUnsignedByte);

    TiffEntry entry2(0x0100, IfdId::ifd0Id, ttUnsignedLong);
    EXPECT_EQ(entry2.tiffType(), ttUnsignedLong);

    TiffEntry entry3(0x0100, IfdId::ifd0Id, ttUnsignedRational);
    EXPECT_EQ(entry3.tiffType(), ttUnsignedRational);
}

// Test pValue returns nullptr when no value set
TEST_F(TiffEntryBaseTest_348, PValueNullWhenNoValueSet_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test setting data to nullptr-like empty buffer
TEST_F(TiffEntryBaseTest_348, SetDataEmptyBuffer_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // With empty buffer, pData should reflect the buffer state
}

// Test updateValue with different byte orders
TEST_F(TiffEntryBaseTest_348, UpdateValueBigEndian_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("256");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_348, UpdateValueLittleEndian_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("256");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test tag value preserved
TEST_F(TiffEntryBaseTest_348, TagValuePreserved_348) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

// Test tag zero
TEST_F(TiffEntryBaseTest_348, TagZero_348) {
    TiffEntry entry(0x0000, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.tag(), 0x0000);
}

// Test setValue with nullptr (null unique_ptr)
TEST_F(TiffEntryBaseTest_348, SetValueWithNullptr_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    std::unique_ptr<Value> nullValue;
    entry.setValue(std::move(nullValue));
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test multiple setData calls
TEST_F(TiffEntryBaseTest_348, MultipleSetDataCalls_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);

    auto buf1 = std::make_shared<DataBuf>(5);
    std::memset(buf1->data(), 0x11, 5);
    entry.setData(buf1);
    const byte* data1 = entry.pData();

    auto buf2 = std::make_shared<DataBuf>(10);
    std::memset(buf2->data(), 0x22, 10);
    entry.setData(buf2);
    const byte* data2 = entry.pData();

    EXPECT_NE(data1, data2);
}

// Test updateValue updates pData content
TEST_F(TiffEntryBaseTest_348, UpdateValueContentVerification_348) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("12345");
    entry.updateValue(std::move(value), littleEndian);

    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toInt64(), 12345);
}
