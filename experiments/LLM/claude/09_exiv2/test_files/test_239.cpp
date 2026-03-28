#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase that we can instantiate
class TiffEntryBaseTest_239 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TiffEntry which derives from TiffEntryBase
        // Using tag 0x0100, ifdIdNotSet group, and ttUndefined type
    }
};

// Helper: TiffEntry is a concrete derived class of TiffEntryBase
// We use it to test TiffEntryBase functionality

TEST_F(TiffEntryBaseTest_239, ConstructorSetsTag_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0100);
}

TEST_F(TiffEntryBaseTest_239, ConstructorSetsTiffType_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

TEST_F(TiffEntryBaseTest_239, ConstructorWithDifferentTiffType_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_239, ConstructorWithLongType_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_239, DefaultIdxIsZero_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_239, SetIdxChangesIdx_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(5);
    EXPECT_EQ(entry.idx(), 5);
}

TEST_F(TiffEntryBaseTest_239, SetIdxNegativeValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(-1);
    EXPECT_EQ(entry.idx(), -1);
}

TEST_F(TiffEntryBaseTest_239, SetIdxZero_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(42);
    EXPECT_EQ(entry.idx(), 42);
    entry.setIdx(0);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_239, SetIdxMultipleTimes_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(1);
    EXPECT_EQ(entry.idx(), 1);
    entry.setIdx(100);
    EXPECT_EQ(entry.idx(), 100);
    entry.setIdx(-50);
    EXPECT_EQ(entry.idx(), -50);
}

TEST_F(TiffEntryBaseTest_239, DefaultPDataIsNull_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, DefaultPValueIsNull_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, DefaultOffsetIsZero_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_239, SetOffsetChangesOffset_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(1024);
    EXPECT_EQ(entry.offset(), 1024u);
}

TEST_F(TiffEntryBaseTest_239, SetOffsetToZero_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(500);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_239, SetOffsetLargeValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFFu);
}

TEST_F(TiffEntryBaseTest_239, SetDataWithSharedBuffer_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, SetDataWithRawPointer_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    byte* data = storage->data();
    entry.setData(data, 10, storage);
    EXPECT_EQ(entry.pData(), data);
}

TEST_F(TiffEntryBaseTest_239, SetValueSetsValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, SetValueWithUndefinedType_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto value = Value::create(undefined);
    const byte testData[] = {0x01, 0x02, 0x03};
    value->read(testData, 3, littleEndian);
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, UpdateValueSetsValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, UpdateValueBigEndian_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("100");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, TagPreservedAfterOperations_239) {
    TiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    entry.setIdx(3);
    entry.setOffset(200);
    EXPECT_EQ(entry.tag(), 0x0110);
}

TEST_F(TiffEntryBaseTest_239, TiffTypePreservedAfterSetIdx_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    entry.setIdx(10);
    EXPECT_EQ(entry.tiffType(), ttByte);
}

TEST_F(TiffEntryBaseTest_239, SetIdxLargePositiveValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(2147483647); // INT_MAX
    EXPECT_EQ(entry.idx(), 2147483647);
}

TEST_F(TiffEntryBaseTest_239, SetIdxMinNegativeValue_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setIdx(-2147483647);
    EXPECT_EQ(entry.idx(), -2147483647);
}

TEST_F(TiffEntryBaseTest_239, SetDataEmptyBuffer_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // After setting empty data, pData might be null or point to empty buffer
    // We just verify no crash occurs
    SUCCEED();
}

TEST_F(TiffEntryBaseTest_239, SetValueNullptr_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    std::unique_ptr<Value> nullVal;
    entry.setValue(std::move(nullVal));
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, MultipleSetDataCalls_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf1 = std::make_shared<DataBuf>(5);
    auto buf2 = std::make_shared<DataBuf>(10);
    entry.setData(buf1);
    entry.setData(buf2);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_239, SetValueReplacesExisting_239) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    
    auto value1 = Value::create(asciiString);
    value1->read("First");
    entry.setValue(std::move(value1));
    EXPECT_NE(entry.pValue(), nullptr);
    
    auto value2 = Value::create(asciiString);
    value2->read("Second");
    entry.setValue(std::move(value2));
    EXPECT_NE(entry.pValue(), nullptr);
}
