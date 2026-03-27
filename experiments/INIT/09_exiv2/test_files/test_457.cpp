#include <gtest/gtest.h>

namespace Exiv2 {
namespace Internal {

// The function being tested is `flashModeUsesManualScale`
static constexpr bool flashModeUsesManualScale(const int64_t mode) {
    return (mode == 6 || mode == 7);
}

} // namespace Internal
} // namespace Exiv2

// Unit Tests for flashModeUsesManualScale

// Test normal operation for known valid modes
TEST_F(FlashModeTest_457, ReturnsTrueForMode6_457) {
    // Test mode 6 which is expected to return true
    EXPECT_TRUE(Exiv2::Internal::flashModeUsesManualScale(6));
}

TEST_F(FlashModeTest_457, ReturnsTrueForMode7_457) {
    // Test mode 7 which is expected to return true
    EXPECT_TRUE(Exiv2::Internal::flashModeUsesManualScale(7));
}

// Test normal operation for known invalid modes
TEST_F(FlashModeTest_457, ReturnsFalseForMode5_457) {
    // Test mode 5 which is not expected to return true
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(5));
}

TEST_F(FlashModeTest_457, ReturnsFalseForMode8_457) {
    // Test mode 8 which is not expected to return true
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(8));
}

// Test boundary conditions
TEST_F(FlashModeTest_457, ReturnsFalseForMinValidMode_457) {
    // Test a boundary case where mode is the minimum possible valid value (which is 0 in this case)
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(0));
}

TEST_F(FlashModeTest_457, ReturnsFalseForMaxValidMode_457) {
    // Test a boundary case where mode is the maximum possible valid value (a very large number)
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(1000000));
}

// Exceptional cases (although the function should not throw exceptions in normal usage)
TEST_F(FlashModeTest_457, ReturnsFalseForNegativeMode_457) {
    // Test a negative mode which is not expected to return true
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(-1));
}

TEST_F(FlashModeTest_457, ReturnsFalseForLargeNegativeMode_457) {
    // Test a very large negative mode
    EXPECT_FALSE(Exiv2::Internal::flashModeUsesManualScale(-1000000));
}