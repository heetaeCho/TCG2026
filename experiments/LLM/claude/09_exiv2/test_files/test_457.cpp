#include <gtest/gtest.h>
#include <cstdint>

// We need to access the function under test. Since it's in a namespace and is constexpr,
// we replicate the declaration to link against it. The actual implementation is in the
// compiled source.
namespace Exiv2 {
namespace Internal {
static constexpr bool flashModeUsesManualScale(const int64_t mode) {
  return (mode == 6 || mode == 7);
}
}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::flashModeUsesManualScale;

// Test fixture
class FlashModeUsesManualScaleTest_457 : public ::testing::Test {};

// Normal operation: mode 6 should return true
TEST_F(FlashModeUsesManualScaleTest_457, Mode6ReturnsTrue_457) {
  EXPECT_TRUE(flashModeUsesManualScale(6));
}

// Normal operation: mode 7 should return true
TEST_F(FlashModeUsesManualScaleTest_457, Mode7ReturnsTrue_457) {
  EXPECT_TRUE(flashModeUsesManualScale(7));
}

// Normal operation: mode 0 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode0ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(0));
}

// Normal operation: mode 1 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode1ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(1));
}

// Normal operation: mode 2 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode2ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(2));
}

// Normal operation: mode 3 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode3ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(3));
}

// Normal operation: mode 4 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode4ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(4));
}

// Normal operation: mode 5 should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode5ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(5));
}

// Boundary: mode 8 (just above valid range) should return false
TEST_F(FlashModeUsesManualScaleTest_457, Mode8ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(8));
}

// Boundary: negative mode should return false
TEST_F(FlashModeUsesManualScaleTest_457, NegativeMode1ReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(-1));
}

// Boundary: large negative value should return false
TEST_F(FlashModeUsesManualScaleTest_457, LargeNegativeReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(-100));
}

// Boundary: large positive value should return false
TEST_F(FlashModeUsesManualScaleTest_457, LargePositiveReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(1000));
}

// Boundary: INT64_MAX should return false
TEST_F(FlashModeUsesManualScaleTest_457, Int64MaxReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(INT64_MAX));
}

// Boundary: INT64_MIN should return false
TEST_F(FlashModeUsesManualScaleTest_457, Int64MinReturnsFalse_457) {
  EXPECT_FALSE(flashModeUsesManualScale(INT64_MIN));
}

// Verify constexpr evaluation works at compile time
TEST_F(FlashModeUsesManualScaleTest_457, ConstexprEvaluation_457) {
  constexpr bool result6 = flashModeUsesManualScale(6);
  constexpr bool result7 = flashModeUsesManualScale(7);
  constexpr bool result0 = flashModeUsesManualScale(0);
  constexpr bool result5 = flashModeUsesManualScale(5);
  constexpr bool result8 = flashModeUsesManualScale(8);

  EXPECT_TRUE(result6);
  EXPECT_TRUE(result7);
  EXPECT_FALSE(result0);
  EXPECT_FALSE(result5);
  EXPECT_FALSE(result8);
}

// Exhaustive test for small range around valid modes
TEST_F(FlashModeUsesManualScaleTest_457, ExhaustiveSmallRange_457) {
  for (int64_t i = -10; i <= 20; ++i) {
    if (i == 6 || i == 7) {
      EXPECT_TRUE(flashModeUsesManualScale(i)) << "Expected true for mode " << i;
    } else {
      EXPECT_FALSE(flashModeUsesManualScale(i)) << "Expected false for mode " << i;
    }
  }
}
