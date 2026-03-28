#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete subclass since TiffEntryBase may be abstract
// TiffEntry is typically a concrete subclass available in the codebase
// If not, we create a minimal concrete class for testing

namespace {

// TiffEntry should be a concrete derived class of TiffEntryBase
// Based on the exiv2 codebase, TiffEntry is defined in tiffcomposite_int.hpp

class TiffEntryBaseTest_299 : public ::testing::Test {
protected:
    void SetUp() override {
        // Using tag 0x0100 (ImageWidth) and IfdId ifd0Id as example
        // TiffType ttUnsignedShort = 3
    }
};

} // anonymous namespace

// Test: setData with valid pointer and size stores data correctly
TEST_F(TiffEntryBaseTest_299, SetDataWithValidPointer_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto buf = std::make_shared<DataBuf>(10);
    byte* rawPtr = buf->data();
    
    // Fill buffer with known values
    for (size_t i = 0; i < 10; ++i) {
        rawPtr[i] = static_cast<byte>(i);
    }
    
    entry.setData(rawPtr, 10, buf);
    
    EXPECT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData(), rawPtr);
}

// Test: setData with nullptr sets size to 0
TEST_F(TiffEntryBaseTest_299, SetDataWithNullptrSetsZeroSize_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto storage = std::make_shared<DataBuf>(10);
    
    entry.setData(nullptr, 100, storage);
    
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test: setData with shared_ptr<DataBuf> overload
TEST_F(TiffEntryBaseTest_299, SetDataWithSharedDataBuf_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto buf = std::make_shared<DataBuf>(20);
    
    // Fill with data
    for (size_t i = 0; i < 20; ++i) {
        buf->data()[i] = static_cast<byte>(i + 1);
    }
    
    entry.setData(buf);
    
    EXPECT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData(), buf->data());
}

// Test: setData with empty DataBuf
TEST_F(TiffEntryBaseTest_299, SetDataWithEmptyDataBuf_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto buf = std::make_shared<DataBuf>();
    
    entry.setData(buf);
    
    // Empty DataBuf has null data pointer
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test: tiffType returns the type set in constructor
TEST_F(TiffEntryBaseTest_299, TiffTypeReturnsConstructorValue_299) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry1.tiffType(), ttUnsignedShort);
    
    TiffEntry entry2(0x0101, IfdId::ifd0Id, ttUnsignedLong);
    EXPECT_EQ(entry2.tiffType(), ttUnsignedLong);
    
    TiffEntry entry3(0x0102, IfdId::ifd0Id, ttAsciiString);
    EXPECT_EQ(entry3.tiffType(), ttAsciiString);
}

// Test: offset initial value and setOffset
TEST_F(TiffEntryBaseTest_299, OffsetDefaultIsZero_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_299, SetOffsetUpdatesOffset_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_299, SetOffsetLargeValue_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFF);
}

// Test: pData initially null
TEST_F(TiffEntryBaseTest_299, PDataInitiallyNull_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test: pValue initially null
TEST_F(TiffEntryBaseTest_299, PValueInitiallyNull_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test: idx initial value
TEST_F(TiffEntryBaseTest_299, IdxInitialValue_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.idx(), 0);
}

// Test: setValue sets a value accessible via pValue
TEST_F(TiffEntryBaseTest_299, SetValueMakesValueAccessible_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    
    Value* rawPtr = value.get();
    entry.setValue(std::move(value));
    
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test: setValue with different value type
TEST_F(TiffEntryBaseTest_299, SetValueWithAsciiString_299) {
    TiffEntry entry(0x010E, IfdId::ifd0Id, ttAsciiString);
    auto value = Value::create(asciiString);
    value->read("Hello World");
    
    entry.setValue(std::move(value));
    
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "Hello World");
}

// Test: setData with zero size and valid pointer
TEST_F(TiffEntryBaseTest_299, SetDataWithZeroSize_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto buf = std::make_shared<DataBuf>(10);
    byte* rawPtr = buf->data();
    
    entry.setData(rawPtr, 0, buf);
    
    // With zero size, pData should still be set to the pointer
    EXPECT_EQ(entry.pData(), rawPtr);
}

// Test: setData replaces previous data
TEST_F(TiffEntryBaseTest_299, SetDataReplacesOldData_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    
    auto buf1 = std::make_shared<DataBuf>(10);
    entry.setData(buf1->data(), 10, buf1);
    EXPECT_EQ(entry.pData(), buf1->data());
    
    auto buf2 = std::make_shared<DataBuf>(20);
    entry.setData(buf2->data(), 20, buf2);
    EXPECT_EQ(entry.pData(), buf2->data());
}

// Test: setOffset can be called multiple times
TEST_F(TiffEntryBaseTest_299, SetOffsetMultipleTimes_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    
    entry.setOffset(10);
    EXPECT_EQ(entry.offset(), 10u);
    
    entry.setOffset(200);
    EXPECT_EQ(entry.offset(), 200u);
    
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test: tag returns correct value from constructor
TEST_F(TiffEntryBaseTest_299, TagReturnsCorrectValue_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    EXPECT_EQ(entry.tag(), 0x0100);
}

// Test: Construction with different groups
TEST_F(TiffEntryBaseTest_299, ConstructionWithDifferentGroups_299) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    TiffEntry entry2(0x0100, IfdId::ifd1Id, ttUnsignedShort);
    
    EXPECT_EQ(entry1.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry2.group(), IfdId::ifd1Id);
}

// Test: setValue replaces previous value
TEST_F(TiffEntryBaseTest_299, SetValueReplacesPreviousValue_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    
    auto value1 = Value::create(unsignedShort);
    value1->read("10");
    entry.setValue(std::move(value1));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "10");
    
    auto value2 = Value::create(unsignedShort);
    value2->read("20");
    entry.setValue(std::move(value2));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "20");
}

// Test: setData with nullptr and zero size
TEST_F(TiffEntryBaseTest_299, SetDataWithNullptrAndZeroSize_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto storage = std::make_shared<DataBuf>();
    
    entry.setData(nullptr, 0, storage);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test: updateValue with a valid value and byte order
TEST_F(TiffEntryBaseTest_299, UpdateValueSetsValue_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    
    // First set some data
    auto buf = std::make_shared<DataBuf>(4);
    buf->data()[0] = 0x01;
    buf->data()[1] = 0x00;
    entry.setData(buf->data(), 2, buf);
    
    auto value = Value::create(unsignedShort);
    value->read("100");
    entry.updateValue(std::move(value), littleEndian);
    
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test: setData with nullptr and non-null storage
TEST_F(TiffEntryBaseTest_299, SetDataNullPtrWithStorage_299) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    auto storage = std::make_shared<DataBuf>(50);
    
    entry.setData(nullptr, 50, storage);
    
    // When pData is null, size should be set to 0
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test: storage is properly managed (shared ownership)
TEST_F(TiffEntryBaseTest_299, StorageSharedOwnership_299) {
    auto buf = std::make_shared<DataBuf>(10);
    byte* rawPtr = buf->data();
    
    {
        TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
        entry.setData(rawPtr, 10, buf);
        EXPECT_EQ(buf.use_count(), 2); // shared between buf and entry
    }
    
    // After entry is destroyed, buf should still be valid
    EXPECT_EQ(buf.use_count(), 1);
    EXPECT_EQ(buf->data(), rawPtr);
}
