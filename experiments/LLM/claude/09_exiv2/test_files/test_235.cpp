#include <gtest/gtest.h>
#include <memory>

// Include necessary headers from the exiv2 project
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

// We need a concrete class derived from TiffEntryBase since it has pure virtual methods
// from TiffComponent. We'll use TiffEntry which is a concrete subclass.
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffEntryBaseTest_235 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TiffEntry (concrete subclass of TiffEntryBase)
        // Using a common tag and group
        entry_ = std::make_unique<TiffEntry>(0x0100, IfdId::ifd0Id, ttUndefined);
    }

    void TearDown() override {
        entry_.reset();
    }

    std::unique_ptr<TiffEntry> entry_;
};

// Test default offset is zero after construction
TEST_F(TiffEntryBaseTest_235, DefaultOffsetIsZero_235) {
    EXPECT_EQ(0u, entry_->offset());
}

// Test setOffset and offset getter
TEST_F(TiffEntryBaseTest_235, SetOffsetAndGetOffset_235) {
    entry_->setOffset(42);
    EXPECT_EQ(42u, entry_->offset());
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_235, SetOffsetToZero_235) {
    entry_->setOffset(100);
    EXPECT_EQ(100u, entry_->offset());
    entry_->setOffset(0);
    EXPECT_EQ(0u, entry_->offset());
}

// Test setOffset with large value
TEST_F(TiffEntryBaseTest_235, SetOffsetLargeValue_235) {
    size_t largeOffset = static_cast<size_t>(-1); // max size_t
    entry_->setOffset(largeOffset);
    EXPECT_EQ(largeOffset, entry_->offset());
}

// Test tiffType returns the type set in constructor
TEST_F(TiffEntryBaseTest_235, TiffTypeReturnsConstructorType_235) {
    EXPECT_EQ(ttUndefined, entry_->tiffType());
}

// Test tiffType with different type
TEST_F(TiffEntryBaseTest_235, TiffTypeShort_235) {
    TiffEntry shortEntry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(ttShort, shortEntry.tiffType());
}

// Test tiffType with ttLong
TEST_F(TiffEntryBaseTest_235, TiffTypeLong_235) {
    TiffEntry longEntry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(ttLong, longEntry.tiffType());
}

// Test pData is null initially
TEST_F(TiffEntryBaseTest_235, PDataIsNullInitially_235) {
    EXPECT_EQ(nullptr, entry_->pData());
}

// Test pValue is null initially
TEST_F(TiffEntryBaseTest_235, PValueIsNullInitially_235) {
    EXPECT_EQ(nullptr, entry_->pValue());
}

// Test idx returns 0 by default
TEST_F(TiffEntryBaseTest_235, IdxDefaultIsZero_235) {
    EXPECT_EQ(0, entry_->idx());
}

// Test tag returns the tag set in constructor
TEST_F(TiffEntryBaseTest_235, TagReturnsConstructorTag_235) {
    EXPECT_EQ(0x0100, entry_->tag());
}

// Test group returns the group set in constructor
TEST_F(TiffEntryBaseTest_235, GroupReturnsConstructorGroup_235) {
    EXPECT_EQ(IfdId::ifd0Id, entry_->group());
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_235, SetDataWithSharedDataBuf_235) {
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry_->setData(buf);
    EXPECT_NE(nullptr, entry_->pData());
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_235, SetDataWithRawPointer_235) {
    auto storage = std::make_shared<DataBuf>(20);
    std::memset(storage->data(), 0xCD, 20);
    entry_->setData(storage->data(), 20, storage);
    EXPECT_NE(nullptr, entry_->pData());
    EXPECT_EQ(0xCD, entry_->pData()[0]);
}

// Test setValue with a Value
TEST_F(TiffEntryBaseTest_235, SetValueSetsValue_235) {
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry_->setValue(std::move(value));
    EXPECT_NE(nullptr, entry_->pValue());
    EXPECT_EQ(42, entry_->pValue()->toInt64());
}

// Test setValue replaces existing value
TEST_F(TiffEntryBaseTest_235, SetValueReplacesExistingValue_235) {
    auto value1 = Value::create(unsignedShort);
    value1->read("10");
    entry_->setValue(std::move(value1));
    EXPECT_EQ(10, entry_->pValue()->toInt64());

    auto value2 = Value::create(unsignedShort);
    value2->read("20");
    entry_->setValue(std::move(value2));
    EXPECT_EQ(20, entry_->pValue()->toInt64());
}

// Test setValue with nullptr
TEST_F(TiffEntryBaseTest_235, SetValueWithNullptr_235) {
    auto value = Value::create(unsignedShort);
    value->read("10");
    entry_->setValue(std::move(value));
    EXPECT_NE(nullptr, entry_->pValue());

    entry_->setValue(nullptr);
    EXPECT_EQ(nullptr, entry_->pValue());
}

// Test updateValue
TEST_F(TiffEntryBaseTest_235, UpdateValueSetsValue_235) {
    auto value = Value::create(unsignedShort);
    value->read("100");
    entry_->updateValue(std::move(value), bigEndian);
    EXPECT_NE(nullptr, entry_->pValue());
    EXPECT_EQ(100, entry_->pValue()->toInt64());
}

// Test updateValue with littleEndian
TEST_F(TiffEntryBaseTest_235, UpdateValueLittleEndian_235) {
    auto value = Value::create(unsignedLong);
    value->read("256");
    entry_->updateValue(std::move(value), littleEndian);
    EXPECT_NE(nullptr, entry_->pValue());
    EXPECT_EQ(256, entry_->pValue()->toInt64());
}

// Test multiple offset changes
TEST_F(TiffEntryBaseTest_235, MultipleOffsetChanges_235) {
    for (size_t i = 0; i < 100; i++) {
        entry_->setOffset(i * 10);
        EXPECT_EQ(i * 10, entry_->offset());
    }
}

// Test creating entries with different tags
TEST_F(TiffEntryBaseTest_235, DifferentTagEntries_235) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttShort);
    TiffEntry entry2(0x0101, IfdId::ifd0Id, ttLong);
    TiffEntry entry3(0x0102, IfdId::ifd1Id, ttUndefined);

    EXPECT_EQ(0x0100, entry1.tag());
    EXPECT_EQ(0x0101, entry2.tag());
    EXPECT_EQ(0x0102, entry3.tag());

    EXPECT_EQ(ttShort, entry1.tiffType());
    EXPECT_EQ(ttLong, entry2.tiffType());
    EXPECT_EQ(ttUndefined, entry3.tiffType());
}

// Test setting data then reading it back
TEST_F(TiffEntryBaseTest_235, SetDataAndVerifyContent_235) {
    auto storage = std::make_shared<DataBuf>(4);
    storage->data()[0] = 0x01;
    storage->data()[1] = 0x02;
    storage->data()[2] = 0x03;
    storage->data()[3] = 0x04;
    entry_->setData(storage->data(), 4, storage);

    ASSERT_NE(nullptr, entry_->pData());
    EXPECT_EQ(0x01, entry_->pData()[0]);
    EXPECT_EQ(0x02, entry_->pData()[1]);
    EXPECT_EQ(0x03, entry_->pData()[2]);
    EXPECT_EQ(0x04, entry_->pData()[3]);
}

// Test setData with empty buffer
TEST_F(TiffEntryBaseTest_235, SetDataEmptyBuffer_235) {
    auto buf = std::make_shared<DataBuf>();
    entry_->setData(buf);
    // pData might be null for empty buffer
    // We just verify no crash
}

// Test boundary: offset at SIZE_MAX / 2
TEST_F(TiffEntryBaseTest_235, OffsetBoundaryHalfMax_235) {
    size_t halfMax = std::numeric_limits<size_t>::max() / 2;
    entry_->setOffset(halfMax);
    EXPECT_EQ(halfMax, entry_->offset());
}

// Test that setValue with string value works
TEST_F(TiffEntryBaseTest_235, SetValueWithStringType_235) {
    auto value = Value::create(asciiString);
    value->read("Hello, World!");
    entry_->setValue(std::move(value));
    EXPECT_NE(nullptr, entry_->pValue());
    EXPECT_EQ("Hello, World!", entry_->pValue()->toString());
}
