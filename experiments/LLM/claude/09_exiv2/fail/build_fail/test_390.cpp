#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffEntry is a concrete subclass of TiffEntryBase
class TiffEntryBaseTest_390 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(TiffEntryBaseTest_390, Constructor_DefaultState_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.tag(), 0x0100);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

TEST_F(TiffEntryBaseTest_390, TiffType_ReturnsCorrectType_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tiffType(), ttShort);
}

TEST_F(TiffEntryBaseTest_390, TiffType_Long_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(entry.tiffType(), ttLong);
}

TEST_F(TiffEntryBaseTest_390, TiffType_Byte_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(entry.tiffType(), ttByte);
}

TEST_F(TiffEntryBaseTest_390, PData_InitiallyNull_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, PValue_InitiallyNull_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, Offset_InitiallyZero_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_390, SetOffset_SetsValue_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

TEST_F(TiffEntryBaseTest_390, SetOffset_LargeValue_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(entry.offset(), 0xFFFFFFFF);
}

TEST_F(TiffEntryBaseTest_390, SetData_WithSharedBuffer_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, SetData_WithRawPointer_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(10);
    byte* data = storage->data();
    entry.setData(data, 10, storage);
    EXPECT_EQ(entry.pData(), data);
}

TEST_F(TiffEntryBaseTest_390, SetValue_SetsValueCorrectly_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, SetValue_NullValue_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setValue(nullptr);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, DoSize_InitiallyZero_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.size(), 0u);
}

TEST_F(TiffEntryBaseTest_390, SetData_SharedBuf_SizeReflectsBuffer_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto buf = std::make_shared<DataBuf>(20);
    entry.setData(buf);
    // After setting data, size should reflect the buffer size
    EXPECT_EQ(entry.size(), 20u);
}

TEST_F(TiffEntryBaseTest_390, SetData_RawPointer_SizeReflects_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto storage = std::make_shared<DataBuf>(15);
    entry.setData(storage->data(), 15, storage);
    EXPECT_EQ(entry.size(), 15u);
}

TEST_F(TiffEntryBaseTest_390, Idx_InitiallyZero_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(entry.idx(), 0);
}

TEST_F(TiffEntryBaseTest_390, Tag_MatchesConstructor_390) {
    TiffEntry entry(0x0112, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(entry.tag(), 0x0112);
}

TEST_F(TiffEntryBaseTest_390, Group_MatchesConstructor_390) {
    TiffEntry entry(0x0100, IfdId::exifId, ttLong);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

TEST_F(TiffEntryBaseTest_390, SetData_ZeroSizeBuffer_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    EXPECT_EQ(entry.size(), 0u);
}

TEST_F(TiffEntryBaseTest_390, UpdateValue_SetsValueAndData_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, UpdateValue_BigEndian_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1024");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, SetOffset_ThenVerify_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    EXPECT_EQ(entry.offset(), 100u);
    entry.setOffset(200);
    EXPECT_EQ(entry.offset(), 200u);
}

TEST_F(TiffEntryBaseTest_390, SetOffset_Zero_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0);
    EXPECT_EQ(entry.offset(), 0u);
}

TEST_F(TiffEntryBaseTest_390, MultipleSetData_OverwritesPrevious_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto buf1 = std::make_shared<DataBuf>(10);
    entry.setData(buf1);
    EXPECT_EQ(entry.size(), 10u);

    auto buf2 = std::make_shared<DataBuf>(20);
    entry.setData(buf2);
    EXPECT_EQ(entry.size(), 20u);
}

TEST_F(TiffEntryBaseTest_390, SetValue_ThenReplace_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto val1 = Value::create(asciiString);
    val1->read("First");
    entry.setValue(std::move(val1));
    EXPECT_NE(entry.pValue(), nullptr);

    auto val2 = Value::create(asciiString);
    val2->read("Second");
    entry.setValue(std::move(val2));
    EXPECT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_390, Count_AfterSetData_390) {
    TiffEntry entry(0x0100, IfdId::ifd0Id, ttByte);
    auto buf = std::make_shared<DataBuf>(5);
    entry.setData(buf);
    EXPECT_EQ(entry.count(), 5u);
}
