#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "exif.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase
class TiffEntryBaseTest_238 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(TiffEntryBaseTest_238, ConstructorSetsTag_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0100);
}

TEST_F(TiffEntryBaseTest_238, ConstructorSetsGroup_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

TEST_F(TiffEntryBaseTest_238, ConstructorSetsTiffType_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

TEST_F(TiffEntryBaseTest_238, ConstructorWithShortType_238) {
    TiffEntry entry(0x0101, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_238, ConstructorWithLongType_238) {
    TiffEntry entry(0x0102, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_238, InitialPDataIsNull_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_238, InitialPValueIsNull_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_238, InitialOffsetIsZero_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_238, InitialIdxIsZero_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_238, SetOffsetWorks_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_238, SetOffsetZero_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_238, SetOffsetLargeValue_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFF);
}

TEST_F(TiffEntryBaseTest_238, SetDataWithSharedBuf_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_238, SetDataWithRawPointer_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    std::memset(data, 0x01, 5);
    entry.setData(data, 5, storage);
    EXPECT_EQ(entry.pData(), data);
}

TEST_F(TiffEntryBaseTest_238, SetValueSetsValue_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_238, SetValueStringContent_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("TestString");
    entry.setValue(std::move(value));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "TestString");
}

TEST_F(TiffEntryBaseTest_238, SetValueOverwritesPrevious_238) {
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

TEST_F(TiffEntryBaseTest_238, UpdateValueWithByteOrder_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 42);
}

TEST_F(TiffEntryBaseTest_238, UpdateValueBigEndian_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.updateValue(std::move(value), bigEndian);
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 1024);
}

TEST_F(TiffEntryBaseTest_238, SetDataEmptyBuf_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // Should handle empty buffer gracefully
}

TEST_F(TiffEntryBaseTest_238, MultipleSetOffsetCalls_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(10);
    EXPECT_EQ(entry.offset(), 10u);
    entry.setOffset(20);
    EXPECT_EQ(entry.offset(), 20u);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_238, TagZero_238) {
    TiffEntry entry(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0000);
}

TEST_F(TiffEntryBaseTest_238, TagMaxValue_238) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

TEST_F(TiffEntryBaseTest_238, SetValueWithLongType_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    auto value = Value::create(unsignedLong);
    value->read("999999");
    entry.setValue(std::move(value));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 999999);
}

TEST_F(TiffEntryBaseTest_238, SetDataWithStoragePreservesPointer_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(20);
    byte* rawPtr = storage->data();
    std::memset(rawPtr, 0xFF, 20);
    entry.setData(rawPtr, 20, storage);
    EXPECT_EQ(entry.pData(), rawPtr);
    // Verify data content is accessible
    EXPECT_EQ(entry.pData()[0], 0xFF);
    EXPECT_EQ(entry.pData()[19], 0xFF);
}

TEST_F(TiffEntryBaseTest_238, SetValueNullptr_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    // Setting a value first, then setting nullptr
    auto value = Value::create(asciiString);
    value->read("test");
    entry.setValue(std::move(value));
    ASSERT_NE(entry.pValue(), nullptr);

    entry.setValue(nullptr);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_238, TiffTypeRational_238) {
    TiffEntry entry(0x011A, IfdId::ifd0Id, ttRational);
    EXPECT_EQ(entry.tiffType(), ttRational);
}

TEST_F(TiffEntryBaseTest_238, TiffTypeSRational_238) {
    TiffEntry entry(0x011A, IfdId::ifd0Id, ttSRational);
    EXPECT_EQ(entry.tiffType(), ttSRational);
}

TEST_F(TiffEntryBaseTest_238, SetDataSharedBufContentAccessible_238) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(4);
    buf->data()[0] = 0x01;
    buf->data()[1] = 0x02;
    buf->data()[2] = 0x03;
    buf->data()[3] = 0x04;
    entry.setData(buf);
    ASSERT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData()[0], 0x01);
    EXPECT_EQ(entry.pData()[1], 0x02);
    EXPECT_EQ(entry.pData()[2], 0x03);
    EXPECT_EQ(entry.pData()[3], 0x04);
}
