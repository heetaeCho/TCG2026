#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "exif.hpp"
#include "types.hpp"
#include "value.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase that we can instantiate
class TiffEntryBaseTest_359 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(TiffEntryBaseTest_359, ConstructorSetsTag_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0100);
}

TEST_F(TiffEntryBaseTest_359, ConstructorSetsGroup_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

TEST_F(TiffEntryBaseTest_359, ConstructorSetsTiffType_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

TEST_F(TiffEntryBaseTest_359, ConstructorWithShortType_359) {
    TiffEntry entry(0x0101, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_359, ConstructorWithLongType_359) {
    TiffEntry entry(0x0102, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_359, InitialPDataIsNull_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, InitialPValueIsNull_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, InitialOffsetIsZero_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_359, InitialIdxIsZero_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_359, SetOffsetChangesOffset_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_359, SetOffsetToZero_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_359, SetOffsetToLargeValue_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFF);
}

TEST_F(TiffEntryBaseTest_359, SetDataWithSharedBuf_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, SetDataWithPointerAndStorage_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    std::memset(storage->data(), 0xCD, 10);
    entry.setData(storage->data(), 10, storage);
    EXPECT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData()[0], 0xCD);
}

TEST_F(TiffEntryBaseTest_359, SetDataPointerPreservesContent_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    byte data[] = {1, 2, 3, 4, 5};
    std::memcpy(storage->data(), data, 5);
    entry.setData(storage->data(), 5, storage);
    EXPECT_EQ(entry.pData()[0], 1);
    EXPECT_EQ(entry.pData()[4], 5);
}

TEST_F(TiffEntryBaseTest_359, SetValueSetsValue_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, SetValueUpdatesData_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Test");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, UpdateValueWithByteOrder_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, UpdateValueBigEndian_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, SetValueWithNullUniquePtr_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    std::unique_ptr<Value> nullValue;
    entry.setValue(std::move(nullValue));
    // After setting null, pValue should be null
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, SetValueTwiceOverwritesPrevious_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value1 = Value::create(asciiString);
    value1->read("First");
    entry.setValue(std::move(value1));

    auto value2 = Value::create(asciiString);
    value2->read("Second");
    entry.setValue(std::move(value2));

    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "Second");
}

TEST_F(TiffEntryBaseTest_359, SetDataWithEmptyBuf_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // With empty buffer, pData might be null or point to empty
}

TEST_F(TiffEntryBaseTest_359, TagZero_359) {
    TiffEntry entry(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0000);
}

TEST_F(TiffEntryBaseTest_359, MaxTag_359) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

TEST_F(TiffEntryBaseTest_359, SetDataWithSharedBufContentAccessible_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(4);
    buf->data()[0] = 0x01;
    buf->data()[1] = 0x02;
    buf->data()[2] = 0x03;
    buf->data()[3] = 0x04;
    entry.setData(buf);
    EXPECT_EQ(entry.pData()[0], 0x01);
    EXPECT_EQ(entry.pData()[1], 0x02);
    EXPECT_EQ(entry.pData()[2], 0x03);
    EXPECT_EQ(entry.pData()[3], 0x04);
}

TEST_F(TiffEntryBaseTest_359, SetValueLongType_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    auto value = Value::create(unsignedLong);
    value->read("12345678");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 12345678);
}

TEST_F(TiffEntryBaseTest_359, UpdateValuePreservesValueContent_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("500");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 500);
}

TEST_F(TiffEntryBaseTest_359, MultipleSetOffsetCalls_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(10);
    EXPECT_EQ(entry.offset(), 10u);
    entry.setOffset(20);
    EXPECT_EQ(entry.offset(), 20u);
    entry.setOffset(30);
    EXPECT_EQ(entry.offset(), 30u);
}

TEST_F(TiffEntryBaseTest_359, DifferentTiffTypes_359) {
    TiffEntry entryByte(0x01, IfdId::ifd0Id, ttUnsignedByte);
    EXPECT_EQ(entryByte.tiffType(), ttUnsignedByte);

    TiffEntry entryRational(0x02, IfdId::ifd0Id, ttUnsignedRational);
    EXPECT_EQ(entryRational.tiffType(), ttUnsignedRational);

    TiffEntry entrySigned(0x03, IfdId::ifd0Id, ttSignedLong);
    EXPECT_EQ(entrySigned.tiffType(), ttSignedLong);
}

TEST_F(TiffEntryBaseTest_359, SetValueRationalType_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedRational);
    auto value = Value::create(unsignedRational);
    value->read("1/2");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_359, SetDataZeroSizePointer_359) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    entry.setData(storage->data(), 0, storage);
    // Size is zero - test that it doesn't crash
}
