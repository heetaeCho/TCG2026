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
class TiffEntryBaseTest_297 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(TiffEntryBaseTest_297, DefaultIdx_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_297, TiffTypeReturnsConstructedType_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_297, TiffTypeUndefined_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

TEST_F(TiffEntryBaseTest_297, TiffTypeLong_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_297, DefaultOffsetIsZero_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_297, SetOffsetChangesOffset_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_297, SetOffsetLargeValue_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFFu);
}

TEST_F(TiffEntryBaseTest_297, DefaultPDataIsNull_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, DefaultPValueIsNull_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, SetDataWithSharedBuf_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, SetDataWithRawPointer_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    std::memset(storage->data(), 0xCD, 10);
    entry.setData(storage->data(), storage->size(), storage);
    EXPECT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData()[0], 0xCD);
}

TEST_F(TiffEntryBaseTest_297, SetValueSetsValue_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, SetValueOverwritesPrevious_297) {
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

TEST_F(TiffEntryBaseTest_297, UpdateValueSetsValue_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, UpdateValueDataAccessible_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1234");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, TagReturnsConstructedTag_297) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    EXPECT_EQ(entry.tag(), 0x0110);
}

TEST_F(TiffEntryBaseTest_297, SetValueNullptr_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    // Set a value first
    auto value = Value::create(asciiString);
    value->read("test");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    
    // Set nullptr
    entry.setValue(nullptr);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_297, SetDataEmptyBuf_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // With empty buffer, pData behavior depends on implementation
    // but should not crash
}

TEST_F(TiffEntryBaseTest_297, SetOffsetZero_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    EXPECT_EQ(entry.offset(), 100u);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_297, CountAfterSetValue_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1 2 3");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 3u);
}

TEST_F(TiffEntryBaseTest_297, MultipleSetDataCalls_297) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf1 = std::make_shared<DataBuf>(5);
    std::memset(buf1->data(), 0x11, 5);
    entry.setData(buf1);
    
    auto buf2 = std::make_shared<DataBuf>(10);
    std::memset(buf2->data(), 0x22, 10);
    entry.setData(buf2);
    
    EXPECT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData()[0], 0x22);
}

TEST_F(TiffEntryBaseTest_297, DifferentTiffTypes_297) {
    TiffEntry entryByte(0x01, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(entryByte.tiffType(), ttByte);
    
    TiffEntry entryRational(0x02, IfdId::ifd0Id, ttRational);
    EXPECT_EQ(entryRational.tiffType(), ttRational);
    
    TiffEntry entrySRational(0x03, IfdId::ifd0Id, ttSRational);
    EXPECT_EQ(entrySRational.tiffType(), ttSRational);
}
