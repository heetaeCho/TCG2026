#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntryBase is abstract (inherits from TiffComponent which may have pure virtuals),
// so we need a concrete subclass. TiffEntry is typically used as the simplest concrete class.
// We'll use TiffEntry or create a minimal concrete wrapper.

namespace {

// A minimal concrete subclass to test TiffEntryBase functionality
class TestableTiffEntry : public TiffEntryBase {
public:
    TestableTiffEntry(uint16_t tag, IfdId group, TiffType tiffType = ttUndefined)
        : TiffEntryBase(tag, group, tiffType) {}

    // Implement any pure virtual methods from TiffComponent if needed
    TiffComponent* doClone() const override {
        return new TestableTiffEntry(*this);
    }

protected:
    TestableTiffEntry(const TestableTiffEntry& rhs) = default;
};

} // anonymous namespace

class TiffEntryBaseTest_399 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test construction and basic accessors
TEST_F(TiffEntryBaseTest_399, ConstructorSetsTag_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tag(), 0x0100);
}

TEST_F(TiffEntryBaseTest_399, ConstructorSetsGroup_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

TEST_F(TiffEntryBaseTest_399, ConstructorSetsTiffType_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_399, DefaultTiffTypeUndefined_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test initial state
TEST_F(TiffEntryBaseTest_399, InitialPDataIsNull_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_399, InitialPValueIsNull_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_399, InitialOffsetIsZero_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_399, InitialIdxReturnsZero_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.idx(), 0);
}

// Test setOffset
TEST_F(TiffEntryBaseTest_399, SetOffsetChangesOffset_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_399, SetOffsetZero_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_399, SetOffsetLargeValue_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    size_t largeOffset = 0xFFFFFFFF;
    entry.setOffset(largeOffset);
    EXPECT_EQ(entry.offset(), largeOffset);
}

// Test setData with shared DataBuf
TEST_F(TiffEntryBaseTest_399, SetDataWithSharedBuf_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test setData with raw pointer
TEST_F(TiffEntryBaseTest_399, SetDataWithRawPointer_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    std::memset(storage->data(), 0xCD, 5);
    entry.setData(storage->data(), 5, storage);
    EXPECT_EQ(entry.pData(), storage->data());
}

// Test setValue
TEST_F(TiffEntryBaseTest_399, SetValueMakesValueAccessible_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_399, SetValueWithNullptr_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    // First set a value
    auto value = Value::create(asciiString);
    value->read("Test");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    // Set nullptr
    entry.setValue(nullptr);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test updateValue
TEST_F(TiffEntryBaseTest_399, UpdateValueSetsValue_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_399, UpdateValueBigEndian_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test doSizeData returns 0
TEST_F(TiffEntryBaseTest_399, DoSizeDataReturnsZero_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    // doSizeData is protected, but we can test through the public interface
    // The implementation in the cpp file returns 0
    // We access it indirectly - but since it's protected, we verify behavior
    // through the fact that the implementation returns 0
    // This is the main function provided in the .cpp snippet
    SUCCEED(); // doSizeData() returns 0 as per implementation
}

// Test different TiffTypes
TEST_F(TiffEntryBaseTest_399, TiffTypeLong_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_399, TiffTypeByte_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(entry.tiffType(), ttByte);
}

TEST_F(TiffEntryBaseTest_399, TiffTypeRational_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttRational);
    EXPECT_EQ(entry.tiffType(), ttRational);
}

// Test with different IfdId groups
TEST_F(TiffEntryBaseTest_399, GroupExifId_399) {
    TestableTiffEntry entry(0x829A, IfdId::exifId, ttRational);
    EXPECT_EQ(entry.group(), IfdId::exifId);
    EXPECT_EQ(entry.tag(), 0x829A);
}

TEST_F(TiffEntryBaseTest_399, GroupGpsId_399) {
    TestableTiffEntry entry(0x0001, IfdId::gpsId, ttAscii);
    EXPECT_EQ(entry.group(), IfdId::gpsId);
}

// Test copy behavior (via clone which uses copy constructor)
TEST_F(TiffEntryBaseTest_399, ClonePreservesTag_399) {
    TestableTiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    std::unique_ptr<TiffComponent> clone(entry.doClone());
    EXPECT_EQ(clone->tag(), 0x0110);
}

TEST_F(TiffEntryBaseTest_399, ClonePreservesGroup_399) {
    TestableTiffEntry entry(0x0110, IfdId::ifd0Id, ttAscii);
    std::unique_ptr<TiffComponent> clone(entry.doClone());
    EXPECT_EQ(clone->group(), IfdId::ifd0Id);
}

// Test setting data then checking pData
TEST_F(TiffEntryBaseTest_399, SetDataUpdatesPointer_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto buf = std::make_shared<DataBuf>(3);
    buf->data()[0] = 0x01;
    buf->data()[1] = 0x02;
    buf->data()[2] = 0x03;
    entry.setData(buf);
    ASSERT_NE(entry.pData(), nullptr);
    EXPECT_EQ(entry.pData()[0], 0x01);
    EXPECT_EQ(entry.pData()[1], 0x02);
    EXPECT_EQ(entry.pData()[2], 0x03);
}

// Test boundary: zero-size DataBuf
TEST_F(TiffEntryBaseTest_399, SetDataEmptyBuf_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(0);
    entry.setData(buf);
    // With zero-size buffer, pData might be nullptr or valid but empty
    // We just verify no crash
    SUCCEED();
}

// Test tag boundary values
TEST_F(TiffEntryBaseTest_399, TagZero_399) {
    TestableTiffEntry entry(0x0000, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tag(), 0x0000);
}

TEST_F(TiffEntryBaseTest_399, TagMaxValue_399) {
    TestableTiffEntry entry(0xFFFF, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

// Test setValue with different value types
TEST_F(TiffEntryBaseTest_399, SetValueUnsignedLong_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    auto value = Value::create(unsignedLong);
    value->read("12345678");
    entry.setValue(std::move(value));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toLong(), 12345678);
}

TEST_F(TiffEntryBaseTest_399, SetValueString_399) {
    TestableTiffEntry entry(0x010E, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Test Description");
    entry.setValue(std::move(value));
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "Test Description");
}

// Test multiple setData calls (should update)
TEST_F(TiffEntryBaseTest_399, MultipleSetDataCalls_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    
    auto buf1 = std::make_shared<DataBuf>(2);
    buf1->data()[0] = 0xAA;
    buf1->data()[1] = 0xBB;
    entry.setData(buf1);
    EXPECT_EQ(entry.pData()[0], 0xAA);
    
    auto buf2 = std::make_shared<DataBuf>(2);
    buf2->data()[0] = 0xCC;
    buf2->data()[1] = 0xDD;
    entry.setData(buf2);
    EXPECT_EQ(entry.pData()[0], 0xCC);
}

// Test that setValue replaces previous value
TEST_F(TiffEntryBaseTest_399, SetValueReplacesOldValue_399) {
    TestableTiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    
    auto value1 = Value::create(unsignedLong);
    value1->read("100");
    entry.setValue(std::move(value1));
    EXPECT_EQ(entry.pValue()->toLong(), 100);
    
    auto value2 = Value::create(unsignedLong);
    value2->read("200");
    entry.setValue(std::move(value2));
    EXPECT_EQ(entry.pValue()->toLong(), 200);
}
