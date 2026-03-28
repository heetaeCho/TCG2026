#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase that we can instantiate
// We need to find a concrete class. TiffEntry should work.
#include "tiffimage_int.hpp"

// Helper: create a TiffEntry (concrete subclass of TiffEntryBase)
// TiffEntry(uint16_t tag, IfdId group) is typically available

class TiffEntryBaseTest_237 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TiffEntry which is a concrete derived class of TiffEntryBase
        // Using tag 0x0100 (ImageWidth) and ifdIdNotSet or ifd0Id
        entry_ = std::make_unique<TiffEntry>(0x0100, IfdId::ifd0Id);
    }

    void TearDown() override {
        entry_.reset();
    }

    std::unique_ptr<TiffEntry> entry_;
};

// Test that pValue() returns nullptr when no value has been set
TEST_F(TiffEntryBaseTest_237, PValueReturnsNullWhenNoValueSet_237) {
    EXPECT_EQ(entry_->pValue(), nullptr);
}

// Test that pData() returns nullptr when no data has been set
TEST_F(TiffEntryBaseTest_237, PDataReturnsNullWhenNoDataSet_237) {
    EXPECT_EQ(entry_->pData(), nullptr);
}

// Test tiffType() returns the type set during construction
TEST_F(TiffEntryBaseTest_237, TiffTypeReturnsConstructedType_237) {
    // TiffEntry typically sets tiffType to unsignedShort or similar based on tag
    // We just verify it returns a valid type (not crashing)
    TiffType type = entry_->tiffType();
    // The default tiffType for TiffEntry is typically ttUndefined (0)
    // Just ensure it doesn't crash and returns something
    (void)type;
    SUCCEED();
}

// Test offset() returns 0 when no offset has been set
TEST_F(TiffEntryBaseTest_237, OffsetReturnsZeroInitially_237) {
    EXPECT_EQ(entry_->offset(), 0u);
}

// Test setOffset and offset
TEST_F(TiffEntryBaseTest_237, SetOffsetUpdatesOffset_237) {
    entry_->setOffset(42);
    EXPECT_EQ(entry_->offset(), 42u);
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_237, SetOffsetToZero_237) {
    entry_->setOffset(100);
    EXPECT_EQ(entry_->offset(), 100u);
    entry_->setOffset(0);
    EXPECT_EQ(entry_->offset(), 0u);
}

// Test setOffset with large value
TEST_F(TiffEntryBaseTest_237, SetOffsetLargeValue_237) {
    size_t largeOffset = 0xFFFFFFFF;
    entry_->setOffset(largeOffset);
    EXPECT_EQ(entry_->offset(), largeOffset);
}

// Test setValue and pValue
TEST_F(TiffEntryBaseTest_237, SetValueMakesPValueNonNull_237) {
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry_->setValue(std::move(value));
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toLong(), 42);
}

// Test setValue with string value
TEST_F(TiffEntryBaseTest_237, SetValueWithStringValue_237) {
    auto value = Value::create(asciiString);
    value->read("Hello World");
    entry_->setValue(std::move(value));
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toString(), "Hello World");
}

// Test setValue replaces previous value
TEST_F(TiffEntryBaseTest_237, SetValueReplacesPreviousValue_237) {
    auto value1 = Value::create(unsignedShort);
    value1->read("10");
    entry_->setValue(std::move(value1));
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toLong(), 10);

    auto value2 = Value::create(unsignedShort);
    value2->read("20");
    entry_->setValue(std::move(value2));
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toLong(), 20);
}

// Test setValue with nullptr (unique_ptr)
TEST_F(TiffEntryBaseTest_237, SetValueWithNullptr_237) {
    // First set a value
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry_->setValue(std::move(value));
    ASSERT_NE(entry_->pValue(), nullptr);

    // Now set nullptr
    std::unique_ptr<Value> nullVal;
    entry_->setValue(std::move(nullVal));
    EXPECT_EQ(entry_->pValue(), nullptr);
}

// Test idx() returns default value
TEST_F(TiffEntryBaseTest_237, IdxReturnsDefaultZero_237) {
    EXPECT_EQ(entry_->idx(), 0);
}

// Test setData with shared buffer
TEST_F(TiffEntryBaseTest_237, SetDataWithSharedBuffer_237) {
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry_->setData(buf);
    ASSERT_NE(entry_->pData(), nullptr);
    EXPECT_EQ(entry_->pData()[0], 0xAB);
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_237, SetDataWithRawPointer_237) {
    auto storage = std::make_shared<DataBuf>(5);
    byte* data = storage->data();
    data[0] = 0x01;
    data[1] = 0x02;
    data[2] = 0x03;
    data[3] = 0x04;
    data[4] = 0x05;
    entry_->setData(data, 5, storage);
    ASSERT_NE(entry_->pData(), nullptr);
    EXPECT_EQ(entry_->pData()[0], 0x01);
    EXPECT_EQ(entry_->pData()[4], 0x05);
}

// Test updateValue with a value and byte order
TEST_F(TiffEntryBaseTest_237, UpdateValueSetsValue_237) {
    auto value = Value::create(unsignedShort);
    value->read("100");
    entry_->updateValue(std::move(value), littleEndian);
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toLong(), 100);
}

// Test updateValue with big endian
TEST_F(TiffEntryBaseTest_237, UpdateValueBigEndian_237) {
    auto value = Value::create(unsignedLong);
    value->read("12345678");
    entry_->updateValue(std::move(value), bigEndian);
    ASSERT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toLong(), 12345678);
}

// Test that tag() returns what was passed in constructor (inherited from TiffComponent)
TEST_F(TiffEntryBaseTest_237, TagReturnsConstructedTag_237) {
    EXPECT_EQ(entry_->tag(), 0x0100);
}

// Test with different tag and group
TEST(TiffEntryBaseStandalone_237, DifferentTagAndGroup_237) {
    TiffEntry entry(0x0110, IfdId::ifd1Id);
    EXPECT_EQ(entry.tag(), 0x0110);
    EXPECT_EQ(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pData(), nullptr);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test multiple setData calls
TEST_F(TiffEntryBaseTest_237, MultipleSetDataCalls_237) {
    auto buf1 = std::make_shared<DataBuf>(4);
    std::memset(buf1->data(), 0x11, 4);
    entry_->setData(buf1);
    EXPECT_EQ(entry_->pData()[0], 0x11);

    auto buf2 = std::make_shared<DataBuf>(8);
    std::memset(buf2->data(), 0x22, 8);
    entry_->setData(buf2);
    EXPECT_EQ(entry_->pData()[0], 0x22);
}

// Test setData with empty buffer
TEST_F(TiffEntryBaseTest_237, SetDataWithEmptyBuffer_237) {
    auto buf = std::make_shared<DataBuf>();
    entry_->setData(buf);
    // After setting empty buffer, pData may be nullptr or point to empty
    // Just ensure no crash
    SUCCEED();
}

// Test setValue with various value types
TEST_F(TiffEntryBaseTest_237, SetValueWithRationalType_237) {
    auto value = Value::create(unsignedRational);
    value->read("1/2");
    entry_->setValue(std::move(value));
    ASSERT_NE(entry_->pValue(), nullptr);
    Rational r = entry_->pValue()->toRational();
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test setValue with long value
TEST_F(TiffEntryBaseTest_237, SetValueWithUnsignedLong_237) {
    auto value = Value::create(unsignedLong);
    value->read("4294967295");
    entry_->setValue(std::move(value));
    ASSERT_NE(entry_->pValue(), nullptr);
}

// Test that offset can be set after data is set
TEST_F(TiffEntryBaseTest_237, SetOffsetAfterSetData_237) {
    auto buf = std::make_shared<DataBuf>(10);
    entry_->setData(buf);
    entry_->setOffset(500);
    EXPECT_EQ(entry_->offset(), 500u);
    ASSERT_NE(entry_->pData(), nullptr);
}
