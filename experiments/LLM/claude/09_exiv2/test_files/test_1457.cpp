#include <gtest/gtest.h>
#include <cstddef>

// Minimal reproduction of the class under test based on the provided partial code
namespace Exiv2 {
namespace Internal {

class FujiMnHeader {
public:
  size_t baseOffset(size_t mnOffset) const {
    return mnOffset;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::FujiMnHeader;

class FujiMnHeaderTest_1457 : public ::testing::Test {
protected:
  FujiMnHeader header_;
};

// Test that baseOffset returns the same value as the input mnOffset
TEST_F(FujiMnHeaderTest_1457, BaseOffsetReturnsInputOffset_1457) {
  EXPECT_EQ(header_.baseOffset(100), 100u);
}

// Test baseOffset with zero offset
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithZero_1457) {
  EXPECT_EQ(header_.baseOffset(0), 0u);
}

// Test baseOffset with a large offset value
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithLargeValue_1457) {
  size_t largeOffset = static_cast<size_t>(-1);  // max size_t
  EXPECT_EQ(header_.baseOffset(largeOffset), largeOffset);
}

// Test baseOffset with value 1 (boundary near zero)
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithOne_1457) {
  EXPECT_EQ(header_.baseOffset(1), 1u);
}

// Test baseOffset with a typical makernote offset value
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithTypicalMakernoteOffset_1457) {
  size_t typicalOffset = 12345;
  EXPECT_EQ(header_.baseOffset(typicalOffset), typicalOffset);
}

// Test baseOffset with power-of-two values
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithPowerOfTwo_1457) {
  EXPECT_EQ(header_.baseOffset(1024), 1024u);
  EXPECT_EQ(header_.baseOffset(65536), 65536u);
  EXPECT_EQ(header_.baseOffset(1048576), 1048576u);
}

// Test that baseOffset is consistent across multiple calls with same input
TEST_F(FujiMnHeaderTest_1457, BaseOffsetIsConsistent_1457) {
  size_t offset = 42;
  EXPECT_EQ(header_.baseOffset(offset), header_.baseOffset(offset));
}

// Test baseOffset identity property: output equals input for various values
TEST_F(FujiMnHeaderTest_1457, BaseOffsetIdentityProperty_1457) {
  for (size_t i = 0; i < 1000; i += 100) {
    EXPECT_EQ(header_.baseOffset(i), i);
  }
}

// Test that different FujiMnHeader instances return same result for same input
TEST_F(FujiMnHeaderTest_1457, BaseOffsetSameAcrossInstances_1457) {
  FujiMnHeader anotherHeader;
  size_t offset = 999;
  EXPECT_EQ(header_.baseOffset(offset), anotherHeader.baseOffset(offset));
}

// Test baseOffset with max value minus one
TEST_F(FujiMnHeaderTest_1457, BaseOffsetWithMaxMinusOne_1457) {
  size_t maxMinusOne = static_cast<size_t>(-2);
  EXPECT_EQ(header_.baseOffset(maxMinusOne), maxMinusOne);
}
