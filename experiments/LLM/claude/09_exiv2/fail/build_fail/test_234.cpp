#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase that we can instantiate
// We use it to test TiffEntryBase's public interface

class TiffEntryBaseTest_234 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that tiffType returns the type passed at construction
TEST_F(TiffEntryBaseTest_234, TiffTypeReturnsConstructedType_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(ttUnsignedShort, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_234, TiffTypeUndefined_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(ttUndefined, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_234, TiffTypeLong_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedLong);
    EXPECT_EQ(ttUnsignedLong, entry.tiffType());
}

// Test that pData returns nullptr initially
TEST_F(TiffEntryBaseTest_234, PDataInitiallyNull_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(nullptr, entry.pData());
}

// Test that pValue returns nullptr initially
TEST_F(TiffEntryBaseTest_234, PValueInitiallyNull_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test that offset returns 0 initially
TEST_F(TiffEntryBaseTest_234, OffsetInitiallyZero_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(0u, entry.offset());
}

// Test setOffset
TEST_F(TiffEntryBaseTest_234, SetOffsetChangesOffset_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(42);
    EXPECT_EQ(42u, entry.offset());
}

TEST_F(TiffEntryBaseTest_234, SetOffsetZero_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(0u, entry.offset());
}

TEST_F(TiffEntryBaseTest_234, SetOffsetLargeValue_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFFu, entry.offset());
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_234, SetDataWithSharedBuf_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(nullptr, entry.pData());
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_234, SetDataWithRawPointer_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    std::memset(data, 0x42, 5);
    entry.setData(data, 5, storage);
    EXPECT_EQ(data, entry.pData());
}

// Test setValue
TEST_F(TiffEntryBaseTest_234, SetValueStoresValue_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.setValue(std::move(value));
    EXPECT_NE(nullptr, entry.pValue());
}

TEST_F(TiffEntryBaseTest_234, SetValueNullptr_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setValue(nullptr);
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test idx returns 0 initially
TEST_F(TiffEntryBaseTest_234, IdxInitiallyZero_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(0, entry.idx());
}

// Test tag and group from TiffComponent base
TEST_F(TiffEntryBaseTest_234, TagReturnsConstructedTag_234) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAsciiString);
    EXPECT_EQ(0x0110, entry.tag());
}

TEST_F(TiffEntryBaseTest_234, GroupReturnsConstructedGroup_234) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAsciiString);
    EXPECT_EQ(IfdId::ifd0Id, entry.group());
}

// Test updateValue
TEST_F(TiffEntryBaseTest_234, UpdateValueSetsValue_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("256");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(nullptr, entry.pValue());
}

TEST_F(TiffEntryBaseTest_234, UpdateValueBigEndian_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedLong);
    auto value = Value::create(unsignedLong);
    value->read("12345678");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(nullptr, entry.pValue());
    EXPECT_NE(nullptr, entry.pData());
}

// Test that after setValue, pData reflects the value data
TEST_F(TiffEntryBaseTest_234, SetValueUpdatesData_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAsciiString);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    const Value* v = entry.pValue();
    ASSERT_NE(nullptr, v);
    EXPECT_EQ("Hello", v->toString());
}

// Test multiple setOffset calls
TEST_F(TiffEntryBaseTest_234, MultipleSetOffsetCalls_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(10);
    EXPECT_EQ(10u, entry.offset());
    entry.setOffset(20);
    EXPECT_EQ(20u, entry.offset());
    entry.setOffset(30);
    EXPECT_EQ(30u, entry.offset());
}

// Test setData with empty buffer
TEST_F(TiffEntryBaseTest_234, SetDataEmptyBuffer_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // With empty buffer, pData may be null or point to empty data
    // Just verify no crash
}

// Test different TiffTypes
TEST_F(TiffEntryBaseTest_234, TiffTypeSignedByte_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttSignedByte);
    EXPECT_EQ(ttSignedByte, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_234, TiffTypeSignedLong_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttSignedLong);
    EXPECT_EQ(ttSignedLong, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_234, TiffTypeFloat_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttTiffFloat);
    EXPECT_EQ(ttTiffFloat, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_234, TiffTypeDouble_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttTiffDouble);
    EXPECT_EQ(ttTiffDouble, entry.tiffType());
}

// Test replacing value with setValue
TEST_F(TiffEntryBaseTest_234, SetValueReplacesExistingValue_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAsciiString);
    
    auto value1 = Value::create(asciiString);
    value1->read("First");
    entry.setValue(std::move(value1));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("First", entry.pValue()->toString());
    
    auto value2 = Value::create(asciiString);
    value2->read("Second");
    entry.setValue(std::move(value2));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("Second", entry.pValue()->toString());
}

// Test setData overwrites previous data
TEST_F(TiffEntryBaseTest_234, SetDataOverwritesPreviousData_234) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    
    auto buf1 = std::make_shared<DataBuf>(5);
    std::memset(buf1->data(), 0x11, 5);
    entry.setData(buf1);
    const byte* p1 = entry.pData();
    
    auto buf2 = std::make_shared<DataBuf>(10);
    std::memset(buf2->data(), 0x22, 10);
    entry.setData(buf2);
    const byte* p2 = entry.pData();
    
    // Data pointer should reflect the new buffer
    EXPECT_NE(nullptr, p2);
}

// Boundary: tag value 0
TEST_F(TiffEntryBaseTest_234, ZeroTag_234) {
    TiffEntry entry(0x0000, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(0x0000, entry.tag());
}

// Boundary: max tag value
TEST_F(TiffEntryBaseTest_234, MaxTag_234) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(0xFFFF, entry.tag());
}
