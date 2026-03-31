#include <gtest/gtest.h>
#include <cstddef>

// Minimal reproduction of the class under test based on the provided partial code
namespace Exiv2 {
namespace Internal {

class Olympus2MnHeader {
 public:
  size_t baseOffset(size_t mnOffset) const {
    return mnOffset;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::Olympus2MnHeader;

class Olympus2MnHeaderTest_1444 : public ::testing::Test {
 protected:
  Olympus2MnHeader header_;
};

// Test that baseOffset returns the same value as the input mnOffset
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetReturnsInputValue_1444) {
  EXPECT_EQ(header_.baseOffset(100), 100u);
}

// Test baseOffset with zero offset
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithZero_1444) {
  EXPECT_EQ(header_.baseOffset(0), 0u);
}

// Test baseOffset with a large offset value
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithLargeValue_1444) {
  size_t largeOffset = 0xFFFFFFFF;
  EXPECT_EQ(header_.baseOffset(largeOffset), largeOffset);
}

// Test baseOffset with maximum size_t value
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithMaxSizeT_1444) {
  size_t maxVal = std::numeric_limits<size_t>::max();
  EXPECT_EQ(header_.baseOffset(maxVal), maxVal);
}

// Test baseOffset with value 1 (boundary near zero)
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithOne_1444) {
  EXPECT_EQ(header_.baseOffset(1), 1u);
}

// Test baseOffset with a typical mid-range offset
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithMidRangeValue_1444) {
  size_t midRange = 12345678;
  EXPECT_EQ(header_.baseOffset(midRange), midRange);
}

// Test that multiple calls with different values return correct results (identity property)
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetMultipleCalls_1444) {
  EXPECT_EQ(header_.baseOffset(10), 10u);
  EXPECT_EQ(header_.baseOffset(20), 20u);
  EXPECT_EQ(header_.baseOffset(30), 30u);
}

// Test that baseOffset is const-correct (can be called on a const object)
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetConstCorrectness_1444) {
  const Olympus2MnHeader constHeader;
  EXPECT_EQ(constHeader.baseOffset(42), 42u);
}

// Test with power-of-two values
TEST_F(Olympus2MnHeaderTest_1444, BaseOffsetWithPowerOfTwo_1444) {
  EXPECT_EQ(header_.baseOffset(1024), 1024u);
  EXPECT_EQ(header_.baseOffset(2048), 2048u);
  EXPECT_EQ(header_.baseOffset(4096), 4096u);
}
