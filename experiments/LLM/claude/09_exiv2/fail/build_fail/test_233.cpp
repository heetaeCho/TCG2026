#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase
// We use it to test TiffEntryBase's public interface

class TiffEntryBaseTest_233 : public ::testing::Test {
protected:
    // Using TiffEntry as a concrete instantiation of TiffEntryBase
    // TiffEntry(uint16_t tag, IfdId group) constructs with ttUndefined typically
    std::unique_ptr<TiffEntry> entry_;

    void SetUp() override {
        entry_ = std::make_unique<TiffEntry>(0x0100, IfdId::ifd0Id);
    }
};

// Test that setOffset and offset work correctly for a normal value
TEST_F(TiffEntryBaseTest_233, SetOffsetNormalValue_233) {
    entry_->setOffset(42);
    EXPECT_EQ(entry_->offset(), 42u);
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_233, SetOffsetZero_233) {
    entry_->setOffset(0);
    EXPECT_EQ(entry_->offset(), 0u);
}

// Test setOffset with a large value
TEST_F(TiffEntryBaseTest_233, SetOffsetLargeValue_233) {
    size_t largeVal = static_cast<size_t>(-1);  // max size_t
    entry_->setOffset(largeVal);
    EXPECT_EQ(entry_->offset(), largeVal);
}

// Test that offset defaults to 0 initially
TEST_F(TiffEntryBaseTest_233, OffsetDefaultIsZero_233) {
    EXPECT_EQ(entry_->offset(), 0u);
}

// Test setOffset overwrites previous value
TEST_F(TiffEntryBaseTest_233, SetOffsetOverwritesPrevious_233) {
    entry_->setOffset(100);
    EXPECT_EQ(entry_->offset(), 100u);
    entry_->setOffset(200);
    EXPECT_EQ(entry_->offset(), 200u);
}

// Test tiffType returns expected type
TEST_F(TiffEntryBaseTest_233, TiffTypeReturnsCorrectType_233) {
    // TiffEntry constructor typically sets tiffType to ttUndefined
    TiffType t = entry_->tiffType();
    EXPECT_EQ(t, ttUndefined);
}

// Test pData is initially null
TEST_F(TiffEntryBaseTest_233, PDataInitiallyNull_233) {
    EXPECT_EQ(entry_->pData(), nullptr);
}

// Test pValue is initially null
TEST_F(TiffEntryBaseTest_233, PValueInitiallyNull_233) {
    EXPECT_EQ(entry_->pValue(), nullptr);
}

// Test idx returns initial value
TEST_F(TiffEntryBaseTest_233, IdxInitialValue_233) {
    EXPECT_EQ(entry_->idx(), 0);
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_233, SetDataWithSharedDataBuf_233) {
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry_->setData(buf);
    EXPECT_NE(entry_->pData(), nullptr);
}

// Test setData with raw pointer and storage
TEST_F(TiffEntryBaseTest_233, SetDataWithRawPointerAndStorage_233) {
    auto storage = std::make_shared<DataBuf>(8);
    std::memset(storage->data(), 0xCD, 8);
    entry_->setData(storage->data(), 8, storage);
    EXPECT_NE(entry_->pData(), nullptr);
    EXPECT_EQ(entry_->pData()[0], 0xCD);
}

// Test setValue with a Value
TEST_F(TiffEntryBaseTest_233, SetValueStoresValue_233) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    entry_->setValue(std::move(val));
    EXPECT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toInt64(), 42);
}

// Test setValue replaces existing value
TEST_F(TiffEntryBaseTest_233, SetValueReplacesExisting_233) {
    auto val1 = Value::create(unsignedShort);
    val1->read("10");
    entry_->setValue(std::move(val1));
    EXPECT_EQ(entry_->pValue()->toInt64(), 10);

    auto val2 = Value::create(unsignedShort);
    val2->read("20");
    entry_->setValue(std::move(val2));
    EXPECT_EQ(entry_->pValue()->toInt64(), 20);
}

// Test setValue with nullptr
TEST_F(TiffEntryBaseTest_233, SetValueWithNullptr_233) {
    entry_->setValue(nullptr);
    EXPECT_EQ(entry_->pValue(), nullptr);
}

// Test updateValue with a Value and byte order
TEST_F(TiffEntryBaseTest_233, UpdateValueSetsValue_233) {
    auto val = Value::create(unsignedLong);
    val->read("12345");
    entry_->updateValue(std::move(val), littleEndian);
    EXPECT_NE(entry_->pValue(), nullptr);
    EXPECT_NE(entry_->pData(), nullptr);
}

// Test tag returns correct tag
TEST_F(TiffEntryBaseTest_233, TagReturnsCorrectTag_233) {
    EXPECT_EQ(entry_->tag(), 0x0100);
}

// Test construction with different tag and group
TEST_F(TiffEntryBaseTest_233, ConstructWithDifferentTagGroup_233) {
    TiffEntry entry2(0x0110, IfdId::exifId);
    EXPECT_EQ(entry2.tag(), 0x0110);
}

// Test setData with empty buffer
TEST_F(TiffEntryBaseTest_233, SetDataWithEmptyBuffer_233) {
    auto buf = std::make_shared<DataBuf>();
    entry_->setData(buf);
    // With empty buffer, pData may be null or point to empty data
    // Just verify it doesn't crash
}

// Test multiple setOffset calls
TEST_F(TiffEntryBaseTest_233, MultipleSetOffsetCalls_233) {
    for (size_t i = 0; i < 100; ++i) {
        entry_->setOffset(i * 1000);
        EXPECT_EQ(entry_->offset(), i * 1000);
    }
}

// Test setData with raw pointer, zero size
TEST_F(TiffEntryBaseTest_233, SetDataZeroSize_233) {
    auto storage = std::make_shared<DataBuf>(4);
    entry_->setData(storage->data(), 0, storage);
    // Should not crash; pData should still be set to the pointer
    EXPECT_EQ(entry_->pData(), storage->data());
}

// Test updateValue with big endian
TEST_F(TiffEntryBaseTest_233, UpdateValueBigEndian_233) {
    auto val = Value::create(unsignedShort);
    val->read("256");
    entry_->updateValue(std::move(val), bigEndian);
    EXPECT_NE(entry_->pValue(), nullptr);
    EXPECT_EQ(entry_->pValue()->toInt64(), 256);
}
