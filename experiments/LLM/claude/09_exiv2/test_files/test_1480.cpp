#include <gtest/gtest.h>
#include <cstddef>

// Minimal reproduction of the class under test based on the provided partial code
namespace Exiv2 {
namespace Internal {

class PentaxDngMnHeader {
 public:
  size_t baseOffset(size_t mnOffset) const {
    return mnOffset;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::PentaxDngMnHeader;

class PentaxDngMnHeaderTest_1480 : public ::testing::Test {
 protected:
  PentaxDngMnHeader header_;
};

// Test that baseOffset returns the same value as the input mnOffset
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetReturnsInputValue_1480) {
  EXPECT_EQ(header_.baseOffset(100), 100u);
}

// Test baseOffset with zero
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithZero_1480) {
  EXPECT_EQ(header_.baseOffset(0), 0u);
}

// Test baseOffset with a large value
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithLargeValue_1480) {
  size_t largeValue = static_cast<size_t>(-1);  // max size_t
  EXPECT_EQ(header_.baseOffset(largeValue), largeValue);
}

// Test baseOffset with value 1
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithOne_1480) {
  EXPECT_EQ(header_.baseOffset(1), 1u);
}

// Test baseOffset with a typical offset value
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithTypicalOffset_1480) {
  EXPECT_EQ(header_.baseOffset(4096), 4096u);
}

// Test baseOffset with another typical value
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithMediumValue_1480) {
  EXPECT_EQ(header_.baseOffset(65535), 65535u);
}

// Test that baseOffset is consistent across multiple calls with the same argument
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetIsConsistent_1480) {
  size_t offset = 12345;
  EXPECT_EQ(header_.baseOffset(offset), header_.baseOffset(offset));
}

// Test baseOffset identity: output equals input for various values
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetIdentityProperty_1480) {
  for (size_t i = 0; i < 1000; i += 100) {
    EXPECT_EQ(header_.baseOffset(i), i);
  }
}

// Test that different PentaxDngMnHeader instances return the same result
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetSameAcrossInstances_1480) {
  PentaxDngMnHeader other;
  size_t offset = 999;
  EXPECT_EQ(header_.baseOffset(offset), other.baseOffset(offset));
}

// Test baseOffset with power-of-two boundary values
TEST_F(PentaxDngMnHeaderTest_1480, BaseOffsetWithPowerOfTwoBoundaries_1480) {
  EXPECT_EQ(header_.baseOffset(1u << 0), 1u << 0);
  EXPECT_EQ(header_.baseOffset(1u << 8), 1u << 8);
  EXPECT_EQ(header_.baseOffset(1u << 16), 1u << 16);
  EXPECT_EQ(header_.baseOffset(1u << 24), 1u << 24);
}
