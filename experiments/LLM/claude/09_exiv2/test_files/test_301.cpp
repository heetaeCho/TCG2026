#include <gtest/gtest.h>
#include <memory>

#include "exiv2/value.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete subclass of TiffEntryBase since it inherits from TiffComponent
// which may have pure virtual methods. We'll use TiffEntry which is a concrete derived class.
// If TiffEntry is not available, we create a minimal concrete subclass.

// TiffEntry is typically defined in tiffcomposite_int.hpp as a concrete class derived from TiffEntryBase.

class TiffEntryBaseTest_301 : public ::testing::Test {
protected:
    // Helper to create a TiffEntry (concrete subclass of TiffEntryBase)
    // Using tag=0x0100, group=ifd0Id, tiffType=unsignedShort (3)
    std::unique_ptr<TiffEntry> createEntry(uint16_t tag = 0x0100, IfdId group = IfdId::ifd0Id) {
        return std::make_unique<TiffEntry>(tag, group);
    }
};

// Test that setValue with a valid Value sets pValue, tiffType, and count correctly
TEST_F(TiffEntryBaseTest_301, SetValueWithValidValue_301) {
    auto entry = createEntry();
    
    // Create a UShortValue
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("1024");
    
    size_t expectedCount = value->count();
    
    entry->setValue(std::move(value));
    
    EXPECT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->count(), expectedCount);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::unsignedShort);
}

// Test that setValue with nullptr does not change state
TEST_F(TiffEntryBaseTest_301, SetValueWithNullptr_301) {
    auto entry = createEntry();
    
    // Initially pValue should be null
    EXPECT_EQ(entry->pValue(), nullptr);
    
    Value::UniquePtr nullValue;
    entry->setValue(std::move(nullValue));
    
    // pValue should still be null
    EXPECT_EQ(entry->pValue(), nullptr);
}

// Test that setValue replaces a previously set value
TEST_F(TiffEntryBaseTest_301, SetValueReplacesExistingValue_301) {
    auto entry = createEntry();
    
    // Set first value
    auto value1 = Value::create(TypeId::unsignedShort);
    value1->read("42");
    entry->setValue(std::move(value1));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 42);
    
    // Set second value
    auto value2 = Value::create(TypeId::unsignedLong);
    value2->read("12345");
    entry->setValue(std::move(value2));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 12345);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::unsignedLong);
}

// Test that setValue sets the correct tiffType for different value types
TEST_F(TiffEntryBaseTest_301, SetValueSetsCorrectTiffTypeForUnsignedByte_301) {
    auto entry = createEntry();
    
    auto value = Value::create(TypeId::unsignedByte);
    value->read("128");
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::unsignedByte);
    // tiffType() should correspond to the value's type
    EXPECT_EQ(entry->tiffType(), toTiffType(TypeId::unsignedByte));
}

// Test setValue with asciiString type
TEST_F(TiffEntryBaseTest_301, SetValueWithAsciiString_301) {
    auto entry = createEntry();
    
    auto value = Value::create(TypeId::asciiString);
    value->read("Hello World");
    
    size_t expectedCount = value->count();
    
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::asciiString);
    EXPECT_EQ(entry->tiffType(), toTiffType(TypeId::asciiString));
}

// Test setValue with signedRational type
TEST_F(TiffEntryBaseTest_301, SetValueWithSignedRational_301) {
    auto entry = createEntry();
    
    auto value = Value::create(TypeId::signedRational);
    value->read("1/2");
    
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::signedRational);
    EXPECT_EQ(entry->tiffType(), toTiffType(TypeId::signedRational));
    EXPECT_EQ(entry->pValue()->count(), 1u);
}

// Test setValue with unsignedLong type and multiple values
TEST_F(TiffEntryBaseTest_301, SetValueWithMultipleValues_301) {
    auto entry = createEntry();
    
    auto value = Value::create(TypeId::unsignedLong);
    value->read("1 2 3 4 5");
    
    size_t expectedCount = value->count();
    
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->count(), expectedCount);
    EXPECT_EQ(entry->pValue()->toInt64(0), 1);
    EXPECT_EQ(entry->pValue()->toInt64(4), 5);
}

// Test initial state of TiffEntryBase (via TiffEntry)
TEST_F(TiffEntryBaseTest_301, InitialState_301) {
    auto entry = createEntry(0x0110, IfdId::ifd0Id);
    
    EXPECT_EQ(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pData(), nullptr);
    EXPECT_EQ(entry->offset(), 0u);
    EXPECT_EQ(entry->tag(), 0x0110);
}

// Test that tiffType changes after setValue
TEST_F(TiffEntryBaseTest_301, TiffTypeChangesAfterSetValue_301) {
    auto entry = createEntry();
    
    TiffType initialType = entry->tiffType();
    
    auto value = Value::create(TypeId::unsignedLong);
    value->read("100");
    entry->setValue(std::move(value));
    
    TiffType newType = entry->tiffType();
    EXPECT_EQ(newType, toTiffType(TypeId::unsignedLong));
}

// Test setOffset and offset
TEST_F(TiffEntryBaseTest_301, SetOffsetAndGetOffset_301) {
    auto entry = createEntry();
    
    entry->setOffset(1024);
    EXPECT_EQ(entry->offset(), 1024u);
    
    entry->setOffset(0);
    EXPECT_EQ(entry->offset(), 0u);
    
    entry->setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry->offset(), 0xFFFFFFFF);
}

// Test setData with shared_ptr<DataBuf>
TEST_F(TiffEntryBaseTest_301, SetDataWithSharedDataBuf_301) {
    auto entry = createEntry();
    
    auto buf = std::make_shared<DataBuf>(10);
    entry->setData(buf);
    
    EXPECT_NE(entry->pData(), nullptr);
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_301, SetDataWithRawPointer_301) {
    auto entry = createEntry();
    
    auto storage = std::make_shared<DataBuf>(10);
    byte* rawPtr = storage->data();
    entry->setData(rawPtr, 10, storage);
    
    EXPECT_EQ(entry->pData(), rawPtr);
}

// Test setValue after setting nullptr doesn't crash, then set valid value
TEST_F(TiffEntryBaseTest_301, SetValueNullThenValid_301) {
    auto entry = createEntry();
    
    // Set null
    entry->setValue(nullptr);
    EXPECT_EQ(entry->pValue(), nullptr);
    
    // Now set valid
    auto value = Value::create(TypeId::unsignedShort);
    value->read("500");
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->toInt64(0), 500);
}

// Test setValue with undefined type
TEST_F(TiffEntryBaseTest_301, SetValueWithUndefinedType_301) {
    auto entry = createEntry();
    
    auto value = Value::create(TypeId::undefined);
    ASSERT_NE(value, nullptr);
    
    // Read some bytes as a string representation
    value->read("0 1 2 3");
    
    entry->setValue(std::move(value));
    
    ASSERT_NE(entry->pValue(), nullptr);
    EXPECT_EQ(entry->pValue()->typeId(), TypeId::undefined);
    EXPECT_EQ(entry->tiffType(), toTiffType(TypeId::undefined));
}

// Test idx returns expected value for fresh entry
TEST_F(TiffEntryBaseTest_301, IdxInitialValue_301) {
    auto entry = createEntry();
    // idx should be 0 initially
    EXPECT_EQ(entry->idx(), 0);
}
