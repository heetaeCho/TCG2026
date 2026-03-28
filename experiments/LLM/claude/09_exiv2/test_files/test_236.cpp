#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

// Include necessary headers from the exiv2 project
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete subclass of TiffEntryBase since it may be abstract
// TiffEntry is typically a concrete subclass
// If TiffEntry is available, we use it; otherwise we create a minimal concrete class

// TiffEntry should be defined in the same header or related headers
// Based on the exiv2 codebase, TiffEntry extends TiffEntryBase

class TiffEntryBaseTest_236 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Default construction - pData should be null initially
TEST_F(TiffEntryBaseTest_236, DefaultConstructionPDataIsNull_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(nullptr, entry.pData());
}

// Test: Default construction - tiffType returns the type passed in constructor
TEST_F(TiffEntryBaseTest_236, ConstructionTiffTypeReturnsCorrectType_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(ttShort, entry.tiffType());
}

// Test: Default construction - offset should be 0 initially
TEST_F(TiffEntryBaseTest_236, DefaultConstructionOffsetIsZero_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.offset());
}

// Test: Default construction - pValue should be null initially
TEST_F(TiffEntryBaseTest_236, DefaultConstructionPValueIsNull_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test: Default construction - idx should return 0
TEST_F(TiffEntryBaseTest_236, DefaultConstructionIdxIsZero_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0, entry.idx());
}

// Test: setOffset changes the offset value
TEST_F(TiffEntryBaseTest_236, SetOffsetChangesOffset_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(42u, entry.offset());
}

// Test: setOffset with zero
TEST_F(TiffEntryBaseTest_236, SetOffsetToZero_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(0u, entry.offset());
}

// Test: setOffset with large value
TEST_F(TiffEntryBaseTest_236, SetOffsetLargeValue_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    size_t largeOffset = 0xFFFFFFFF;
    entry.setOffset(largeOffset);
    EXPECT_EQ(largeOffset, entry.offset());
}

// Test: setData with shared_ptr<DataBuf> sets pData correctly
TEST_F(TiffEntryBaseTest_236, SetDataWithSharedDataBuf_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    ASSERT_NE(nullptr, entry.pData());
    EXPECT_EQ(0xAB, entry.pData()[0]);
}

// Test: setData with raw pointer, size, and storage
TEST_F(TiffEntryBaseTest_236, SetDataWithRawPointerAndStorage_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    data[0] = 0x01;
    data[1] = 0x02;
    data[2] = 0x03;
    data[3] = 0x04;
    data[4] = 0x05;
    entry.setData(data, 5, storage);
    ASSERT_NE(nullptr, entry.pData());
    EXPECT_EQ(0x01, entry.pData()[0]);
    EXPECT_EQ(0x05, entry.pData()[4]);
}

// Test: setValue sets the value and makes it accessible via pValue
TEST_F(TiffEntryBaseTest_236, SetValueMakesValueAccessible_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = std::make_unique<AsciiValue>();
    value->read("Hello");
    entry.setValue(std::move(value));
    ASSERT_NE(nullptr, entry.pValue());
}

// Test: setValue with AsciiValue - check value content
TEST_F(TiffEntryBaseTest_236, SetValueAsciiContent_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = std::make_unique<AsciiValue>();
    value->read("TestString");
    entry.setValue(std::move(value));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("TestString", entry.pValue()->toString());
}

// Test: setValue replaces previous value
TEST_F(TiffEntryBaseTest_236, SetValueReplacesPreviousValue_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value1 = std::make_unique<AsciiValue>();
    value1->read("First");
    entry.setValue(std::move(value1));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("First", entry.pValue()->toString());

    auto value2 = std::make_unique<AsciiValue>();
    value2->read("Second");
    entry.setValue(std::move(value2));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("Second", entry.pValue()->toString());
}

// Test: updateValue with UShortValue and little-endian byte order
TEST_F(TiffEntryBaseTest_236, UpdateValueUShortLittleEndian_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = std::make_unique<ValueType<uint16_t>>();
    value->value_.push_back(256);
    entry.updateValue(std::move(value), littleEndian);
    ASSERT_NE(nullptr, entry.pValue());
}

// Test: updateValue updates pData as well
TEST_F(TiffEntryBaseTest_236, UpdateValueUpdatesPData_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = std::make_unique<ValueType<uint16_t>>();
    value->value_.push_back(0x1234);
    entry.updateValue(std::move(value), littleEndian);
    ASSERT_NE(nullptr, entry.pData());
}

// Test: Construction with different TiffTypes
TEST_F(TiffEntryBaseTest_236, ConstructionWithTiffTypeLong_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(ttLong, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_236, ConstructionWithTiffTypeByte_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(ttByte, entry.tiffType());
}

TEST_F(TiffEntryBaseTest_236, ConstructionWithTiffTypeRational_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttRational);
    EXPECT_EQ(ttRational, entry.tiffType());
}

// Test: Tag is correctly stored
TEST_F(TiffEntryBaseTest_236, TagIsCorrectlyStored_236) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    EXPECT_EQ(0x0110, entry.tag());
}

// Test: Group is correctly stored
TEST_F(TiffEntryBaseTest_236, GroupIsCorrectlyStored_236) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    EXPECT_EQ(IfdId::ifd0Id, entry.group());
}

// Test: setData with empty DataBuf
TEST_F(TiffEntryBaseTest_236, SetDataWithEmptyDataBuf_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // With an empty buffer, pData might be null or point to empty data
    // The behavior depends on implementation, but it shouldn't crash
}

// Test: setData with size 0
TEST_F(TiffEntryBaseTest_236, SetDataWithSizeZero_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    entry.setData(storage->data(), 0, storage);
    // Should not crash; pData should still point to valid memory
    ASSERT_NE(nullptr, entry.pData());
}

// Test: Multiple setOffset calls
TEST_F(TiffEntryBaseTest_236, MultipleSetOffsetCalls_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    for (size_t i = 0; i < 100; ++i) {
        entry.setOffset(i * 10);
        EXPECT_EQ(i * 10, entry.offset());
    }
}

// Test: setValue with nullptr (move from empty unique_ptr)
TEST_F(TiffEntryBaseTest_236, SetValueWithNullptr_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    std::unique_ptr<Value> nullValue;
    entry.setValue(std::move(nullValue));
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test: Different tag values
TEST_F(TiffEntryBaseTest_236, DifferentTagValues_236) {
    TiffEntry entry1(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0x0000, entry1.tag());

    TiffEntry entry2(0xFFFF, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0xFFFF, entry2.tag());
}

// Test: setValue with long value then check pValue is valid
TEST_F(TiffEntryBaseTest_236, SetLongValue_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    auto value = std::make_unique<ValueType<uint32_t>>();
    value->value_.push_back(12345678);
    entry.setValue(std::move(value));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ(1, entry.pValue()->count());
}

// Test: updateValue with big-endian byte order
TEST_F(TiffEntryBaseTest_236, UpdateValueBigEndian_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = std::make_unique<ValueType<uint16_t>>();
    value->value_.push_back(0x0102);
    entry.updateValue(std::move(value), bigEndian);
    ASSERT_NE(nullptr, entry.pValue());
    ASSERT_NE(nullptr, entry.pData());
}

// Test: setData followed by pData returns correct data
TEST_F(TiffEntryBaseTest_236, SetDataFollowedByPDataReturnsCorrectData_236) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto buf = std::make_shared<DataBuf>(4);
    buf->data()[0] = 0xDE;
    buf->data()[1] = 0xAD;
    buf->data()[2] = 0xBE;
    buf->data()[3] = 0xEF;
    entry.setData(buf);
    ASSERT_NE(nullptr, entry.pData());
    EXPECT_EQ(0xDE, entry.pData()[0]);
    EXPECT_EQ(0xAD, entry.pData()[1]);
    EXPECT_EQ(0xBE, entry.pData()[2]);
    EXPECT_EQ(0xEF, entry.pData()[3]);
}
