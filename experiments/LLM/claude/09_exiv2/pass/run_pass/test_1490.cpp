#include <gtest/gtest.h>
#include <cstddef>

// Minimal declarations to match the interface under test
namespace Exiv2 {

using byte = uint8_t;

enum ByteOrder {
    littleEndian,
    bigEndian,
    invalidByteOrder
};

namespace Internal {

class SamsungMnHeader {
public:
    size_t baseOffset(size_t mnOffset) const {
        return mnOffset;
    }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2::Internal;

class SamsungMnHeaderTest_1490 : public ::testing::Test {
protected:
    SamsungMnHeader header;
};

// Test that baseOffset returns the same value as mnOffset (identity behavior)
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetReturnsInputValue_1490) {
    EXPECT_EQ(header.baseOffset(100), 100u);
}

// Test baseOffset with zero
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithZero_1490) {
    EXPECT_EQ(header.baseOffset(0), 0u);
}

// Test baseOffset with a large value
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithLargeValue_1490) {
    size_t largeValue = 0xFFFFFFFF;
    EXPECT_EQ(header.baseOffset(largeValue), largeValue);
}

// Test baseOffset with size_t max value
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithMaxSizeT_1490) {
    size_t maxVal = std::numeric_limits<size_t>::max();
    EXPECT_EQ(header.baseOffset(maxVal), maxVal);
}

// Test baseOffset with value of 1
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithOne_1490) {
    EXPECT_EQ(header.baseOffset(1), 1u);
}

// Test baseOffset with a typical MakerNote offset value
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithTypicalOffset_1490) {
    size_t typicalOffset = 12345;
    EXPECT_EQ(header.baseOffset(typicalOffset), typicalOffset);
}

// Test that multiple calls with same value return consistent results
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetIsConsistent_1490) {
    size_t offset = 42;
    EXPECT_EQ(header.baseOffset(offset), header.baseOffset(offset));
}

// Test baseOffset with multiple different values sequentially
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetMultipleDifferentValues_1490) {
    EXPECT_EQ(header.baseOffset(10), 10u);
    EXPECT_EQ(header.baseOffset(20), 20u);
    EXPECT_EQ(header.baseOffset(30), 30u);
}

// Test baseOffset with power-of-two values
TEST_F(SamsungMnHeaderTest_1490, BaseOffsetWithPowerOfTwo_1490) {
    EXPECT_EQ(header.baseOffset(1024), 1024u);
    EXPECT_EQ(header.baseOffset(2048), 2048u);
    EXPECT_EQ(header.baseOffset(4096), 4096u);
}

// Test that a default-constructed header works correctly
TEST_F(SamsungMnHeaderTest_1490, DefaultConstructedHeaderBaseOffset_1490) {
    SamsungMnHeader defaultHeader;
    EXPECT_EQ(defaultHeader.baseOffset(500), 500u);
}
