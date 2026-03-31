#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

#include <memory>
#include <vector>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to suppress warnings during tests
class SuppressWarnings {
public:
    SuppressWarnings() {
        oldLevel_ = LogMsg::level();
        LogMsg::setLevel(LogMsg::mute);
    }
    ~SuppressWarnings() {
        LogMsg::setLevel(oldLevel_);
    }
private:
    LogMsg::Level oldLevel_;
};

class TiffDataEntryTest_302 : public ::testing::Test {
protected:
    void SetUp() override {
        // Mute warnings for cleaner test output
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test: setStrips with null pSize should return early (no crash)
TEST_F(TiffDataEntryTest_302, SetStrips_NullPSize_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Set up a value for the entry
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    byte data[100] = {};
    // pSize is nullptr - should return without crashing
    EXPECT_NO_THROW(entry.setStrips(nullptr, data, sizeof(data), 0));

    // Verify that no data area was set (sizeDataArea should remain 0)
    // We check indirectly: pValue's dataArea should be empty
    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with null pValue (no value set) should return early
TEST_F(TiffDataEntryTest_302, SetStrips_NullPValue_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Don't set any value on entry
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 0));
}

// Test: setStrips with empty pValue (count == 0) should return early
TEST_F(TiffDataEntryTest_302, SetStrips_EmptyPValue_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Create an empty value with count 0
    auto offsetValue = Value::create(unsignedLong);
    // Don't read anything, so count is 0
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 0));

    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with mismatched counts between pValue and pSize
TEST_F(TiffDataEntryTest_302, SetStrips_MismatchedCounts_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Offset value with 2 components
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0 10");
    entry.setValue(std::move(offsetValue));

    // Size value with 1 component (mismatch)
    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 0));

    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with data area exceeding buffer size
TEST_F(TiffDataEntryTest_302, SetStrips_DataAreaExceedsBuffer_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("200");  // Size exceeds sizeData

    byte data[100] = {};
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 0));

    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with offset exceeding buffer
TEST_F(TiffDataEntryTest_302, SetStrips_OffsetExceedsBuffer_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("90");  // offset = 90
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("20");  // size = 20, offset + size = 110 > 100

    byte data[100] = {};
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 0));

    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with baseOffset causing overflow
TEST_F(TiffDataEntryTest_302, SetStrips_BaseOffsetCausesOverflow_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("10");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100] = {};
    // baseOffset = 90, offset = 10, size = 10 => 90 + 10 + 10 = 110 > 100
    EXPECT_NO_THROW(entry.setStrips(sizeValue.get(), data, sizeof(data), 90));

    if (entry.pValue()) {
        EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
    }
}

// Test: setStrips with valid contiguous single strip
TEST_F(TiffDataEntryTest_302, SetStrips_ValidSingleStrip_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("10");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("20");

    byte data[100];
    std::memset(data, 0xAB, sizeof(data));

    // offset=10, size=20, baseOffset=0, sizeData=100
    // last offset + last size = 10 + 20 = 30 == size + offset = 20 + 10 = 30 ✓
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 20u);
}

// Test: setStrips with valid contiguous multiple strips
TEST_F(TiffDataEntryTest_302, SetStrips_ValidMultipleContiguousStrips_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Two strips: offsets at 10 and 20, sizes 10 and 10
    // Total size = 20, first offset = 10
    // Last offset + last size = 20 + 10 = 30 == size + offset = 20 + 10 = 30 ✓
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("10 20");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10 10");

    byte data[100];
    std::memset(data, 0xCD, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 20u);
}

// Test: setStrips with non-contiguous strips should return early
TEST_F(TiffDataEntryTest_302, SetStrips_NonContiguousStrips_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Two strips: offsets at 10 and 30 (gap between 20 and 30), sizes 10 and 10
    // Total size = 20, first offset = 10
    // Last offset + last size = 30 + 10 = 40 != size + offset = 20 + 10 = 30
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("10 30");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10 10");

    byte data[100];
    std::memset(data, 0, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
}

// Test: setStrips with baseOffset > 0 and valid data
TEST_F(TiffDataEntryTest_302, SetStrips_ValidWithBaseOffset_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("5");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100];
    std::memset(data, 0xEF, sizeof(data));

    // baseOffset=5, offset=5, size=10 => 5+5+10 = 20 <= 100 ✓
    // contiguity: last_offset + last_size = 5 + 10 = 15 == size + offset = 10 + 5 = 15 ✓
    entry.setStrips(sizeValue.get(), data, sizeof(data), 5);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 10u);
}

// Test: setStrips with zero size strips
TEST_F(TiffDataEntryTest_302, SetStrips_ZeroSizeStrip_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("0");

    byte data[100];
    std::memset(data, 0, sizeof(data));

    // size=0, offset=0, baseOffset=0 => 0 > 100? No. 0 > 100-0? No. 0 > 100-0-0? No.
    // contiguity: 0 + 0 = 0 == 0 + 0 = 0 ✓
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
}

// Test: setStrips at exact boundary of buffer
TEST_F(TiffDataEntryTest_302, SetStrips_ExactBoundary_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("100");

    byte data[100];
    std::memset(data, 0xFF, sizeof(data));

    // size=100, offset=0, baseOffset=0 => 100 > 100? No. 0 > 100-100=0? No. 0 > 0-0=0? No.
    // contiguity: 0 + 100 = 100 == 100 + 0 = 100 ✓
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 100u);
}

// Test: setStrips exceeding buffer by 1 byte
TEST_F(TiffDataEntryTest_302, SetStrips_ExceedsByOneByte_ReturnsEarly_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("101");  // 101 > 100

    byte data[100];
    std::memset(data, 0, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 0u);
}

// Test: setStrips with three contiguous strips
TEST_F(TiffDataEntryTest_302, SetStrips_ThreeContiguousStrips_SetsDataArea_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    // Three strips: offsets at 0, 10, 25; sizes 10, 15, 5
    // Total size = 30, first offset = 0
    // Last offset + last size = 25 + 5 = 30 == 30 + 0 = 30 ✓
    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("0 10 25");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10 15 5");

    byte data[100];
    std::memset(data, 0xAA, sizeof(data));

    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 30u);
}

// Test: Data area content is correctly pointed (verify through dataArea())
TEST_F(TiffDataEntryTest_302, SetStrips_VerifyDataAreaContent_302) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117);

    auto offsetValue = Value::create(unsignedLong);
    offsetValue->read("5");
    entry.setValue(std::move(offsetValue));

    auto sizeValue = Value::create(unsignedLong);
    sizeValue->read("10");

    byte data[100];
    for (int i = 0; i < 100; ++i) {
        data[i] = static_cast<byte>(i);
    }

    // baseOffset=0, offset=5, size=10
    entry.setStrips(sizeValue.get(), data, sizeof(data), 0);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->sizeDataArea(), 10u);

    DataBuf buf = entry.pValue()->dataArea();
    ASSERT_EQ(buf.size(), 10u);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(buf.data()[i], static_cast<byte>(5 + i));
    }
}
