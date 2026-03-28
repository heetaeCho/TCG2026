#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/error.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffImageEntryTest_303 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Helper to create a TiffImageEntry with a value set
// TiffImageEntry constructor: TiffImageEntry(uint16_t tag, IfdId group)
// It inherits from TiffDataEntryBase which has szTag and szGroup

TEST_F(TiffImageEntryTest_303, SetStrips_NullPSize_ReturnsEarly_303) {
    // When pSize is null, setStrips should return early without crash
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set a value on the entry so pValue() is not null
    auto value = Value::create(unsignedLong);
    value->read("0");
    entry.setValue(std::move(value));

    byte data[100] = {};
    // pSize is nullptr - should return early
    entry.setStrips(nullptr, data, sizeof(data), 0);

    // No crash means success; sizeImage should be 0 since no strips were added
    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_NullPValue_ReturnsEarly_303) {
    // When pValue() is null (no value set), setStrips should return early
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_CountMismatch_ReturnsEarly_303) {
    // When pValue()->count() != pSize->count(), should return early
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set entry value with 2 components
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0 10");
    entry.setValue(std::move(offsetValue));

    // Size value with 3 components - mismatch
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("5 5 5");

    byte data[100] = {};
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_SingleValidStrip_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set offset value: one strip at offset 0
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    // Size value: strip size 10
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100];
    std::memset(data, 0xAB, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 10u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_MultipleValidStrips_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Two strips at offsets 0 and 20
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0 20");
    entry.setValue(std::move(offsetValue));

    // Sizes: 10 and 15
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10 15");

    byte data[100];
    std::memset(data, 0xCD, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 25u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_StripOutOfBounds_Ignored_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Offset at 90, which with size 20 would exceed sizeData of 100
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("90");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("20");

    byte data[100] = {};

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    // Strip is out of bounds, should be ignored
    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_ZeroSizeStrip_Ignored_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    // Size is 0
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("0");

    byte data[100] = {};

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    // Zero-size strip should not be added
    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_WithBaseOffset_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100];
    std::memset(data, 0xEF, sizeof(data));

    // baseOffset = 50, offset = 0, size = 10 => pData + 50, valid
    entry.setStrips(sizeValue.get(), data, sizeof(data), 50);

    EXPECT_EQ(entry.sizeImage(), 10u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_BaseOffsetCausesOverflow_Ignored_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};

    // baseOffset = 95, offset = 0, size = 10 => 95 + 0 + 10 > 100
    entry.setStrips(sizeValue.get(), data, sizeof(data), 95);

    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_MixedValidAndInvalidStrips_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Three strips: one valid, one out of bounds, one zero-size
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0 90 50");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10 20 0");

    byte data[100] = {};

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    // Only first strip (size 10) should be added
    EXPECT_EQ(entry.sizeImage(), 10u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_ExactBoundary_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Strip exactly at the boundary: offset 90, size 10, sizeData 100
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("90");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 10u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_SizeExceedsSizeData_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    // size > sizeData
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("200");

    byte data[100] = {};

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 0u);
}

TEST_F(TiffImageEntryTest_303, SetStrips_EntireSizeData_SingleStrip_303) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("100");

    byte data[100];
    std::memset(data, 0x42, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    EXPECT_EQ(entry.sizeImage(), 100u);
}
