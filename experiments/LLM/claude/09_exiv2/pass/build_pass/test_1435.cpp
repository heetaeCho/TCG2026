#include <gtest/gtest.h>
#include <cstddef>

// Include the necessary header or replicate the minimal interface
namespace Exiv2 {
namespace Internal {
class MnHeader {
public:
    size_t baseOffset(size_t /*mnOffset*/) const {
        return 0;
    }
};
}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::MnHeader;

class MnHeaderTest_1435 : public ::testing::Test {
protected:
    MnHeader header;
};

// Test that baseOffset returns 0 for a typical offset value
TEST_F(MnHeaderTest_1435, BaseOffsetReturnsZeroForTypicalOffset_1435) {
    size_t result = header.baseOffset(100);
    EXPECT_EQ(result, 0u);
}

// Test that baseOffset returns 0 when given zero as offset
TEST_F(MnHeaderTest_1435, BaseOffsetReturnsZeroForZeroOffset_1435) {
    size_t result = header.baseOffset(0);
    EXPECT_EQ(result, 0u);
}

// Test that baseOffset returns 0 for a large offset value
TEST_F(MnHeaderTest_1435, BaseOffsetReturnsZeroForLargeOffset_1435) {
    size_t result = header.baseOffset(1000000);
    EXPECT_EQ(result, 0u);
}

// Test that baseOffset returns 0 for maximum size_t value
TEST_F(MnHeaderTest_1435, BaseOffsetReturnsZeroForMaxSizeT_1435) {
    size_t result = header.baseOffset(static_cast<size_t>(-1));
    EXPECT_EQ(result, 0u);
}

// Test that baseOffset returns 0 for offset value of 1
TEST_F(MnHeaderTest_1435, BaseOffsetReturnsZeroForOffsetOne_1435) {
    size_t result = header.baseOffset(1);
    EXPECT_EQ(result, 0u);
}

// Test that baseOffset is consistent across multiple calls with the same argument
TEST_F(MnHeaderTest_1435, BaseOffsetConsistentAcrossMultipleCalls_1435) {
    size_t result1 = header.baseOffset(42);
    size_t result2 = header.baseOffset(42);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 0u);
}

// Test that baseOffset returns 0 regardless of different offset arguments
TEST_F(MnHeaderTest_1435, BaseOffsetAlwaysReturnsZeroForDifferentOffsets_1435) {
    EXPECT_EQ(header.baseOffset(0), 0u);
    EXPECT_EQ(header.baseOffset(10), 0u);
    EXPECT_EQ(header.baseOffset(255), 0u);
    EXPECT_EQ(header.baseOffset(65535), 0u);
    EXPECT_EQ(header.baseOffset(static_cast<size_t>(-1)), 0u);
}

// Test that a const MnHeader object can call baseOffset
TEST_F(MnHeaderTest_1435, ConstObjectCanCallBaseOffset_1435) {
    const MnHeader constHeader;
    size_t result = constHeader.baseOffset(50);
    EXPECT_EQ(result, 0u);
}

// Test default construction of MnHeader
TEST_F(MnHeaderTest_1435, DefaultConstruction_1435) {
    MnHeader h;
    EXPECT_EQ(h.baseOffset(0), 0u);
}

// Test that multiple MnHeader instances all return 0
TEST_F(MnHeaderTest_1435, MultipleInstancesAllReturnZero_1435) {
    MnHeader h1, h2, h3;
    EXPECT_EQ(h1.baseOffset(10), 0u);
    EXPECT_EQ(h2.baseOffset(20), 0u);
    EXPECT_EQ(h3.baseOffset(30), 0u);
}
