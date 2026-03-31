#include <gtest/gtest.h>

// Include the necessary headers
namespace Catch {

namespace ResultDisposition {
    enum Flags {
        Normal = 1,
        ContinueOnFailure = 2,
        FalseTest = 4,
        SuppressFail = 8
    };
}

constexpr bool shouldSuppressFailure(int flags) {
    return (flags & ResultDisposition::SuppressFail) != 0;
}

} // namespace Catch

// Test fixture
class ShouldSuppressFailureTest_64 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenSuppressFailFlagIsSet_64) {
    EXPECT_TRUE(Catch::shouldSuppressFailure(Catch::ResultDisposition::SuppressFail));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenNormalFlagIsSet_64) {
    EXPECT_FALSE(Catch::shouldSuppressFailure(Catch::ResultDisposition::Normal));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenContinueOnFailureFlagIsSet_64) {
    EXPECT_FALSE(Catch::shouldSuppressFailure(Catch::ResultDisposition::ContinueOnFailure));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenFalseTestFlagIsSet_64) {
    EXPECT_FALSE(Catch::shouldSuppressFailure(Catch::ResultDisposition::FalseTest));
}

// Combined flags tests

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenSuppressFailCombinedWithNormal_64) {
    int flags = Catch::ResultDisposition::Normal | Catch::ResultDisposition::SuppressFail;
    EXPECT_TRUE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenSuppressFailCombinedWithContinueOnFailure_64) {
    int flags = Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail;
    EXPECT_TRUE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenSuppressFailCombinedWithFalseTest_64) {
    int flags = Catch::ResultDisposition::FalseTest | Catch::ResultDisposition::SuppressFail;
    EXPECT_TRUE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenAllFlagsCombined_64) {
    int flags = Catch::ResultDisposition::Normal |
                Catch::ResultDisposition::ContinueOnFailure |
                Catch::ResultDisposition::FalseTest |
                Catch::ResultDisposition::SuppressFail;
    EXPECT_TRUE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenAllFlagsExceptSuppressFailCombined_64) {
    int flags = Catch::ResultDisposition::Normal |
                Catch::ResultDisposition::ContinueOnFailure |
                Catch::ResultDisposition::FalseTest;
    EXPECT_FALSE(Catch::shouldSuppressFailure(flags));
}

// Boundary / edge cases

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenFlagsIsZero_64) {
    EXPECT_FALSE(Catch::shouldSuppressFailure(0));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenFlagsHasSuppressFailBitSetAmongArbitraryBits_64) {
    // Set SuppressFail (8 = 0b1000) along with some higher bits
    int flags = 0xFF; // All lower 8 bits set, includes bit 3 (SuppressFail)
    EXPECT_TRUE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseWhenFlagsHaveNonOverlappingBits_64) {
    // Bits that don't overlap with SuppressFail (8 = 0b1000)
    int flags = 0x70; // 0b01110000 - no overlap with bit 3
    EXPECT_FALSE(Catch::shouldSuppressFailure(flags));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueWhenOnlySuppressFailBitValue8_64) {
    EXPECT_TRUE(Catch::shouldSuppressFailure(8));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseForNegativeValueWithoutSuppressFailBit_64) {
    // Negative values in two's complement typically have MSB set
    // -1 in two's complement has all bits set, which includes SuppressFail
    // So -1 should return true
    EXPECT_TRUE(Catch::shouldSuppressFailure(-1));
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsFalseForValuesThatDontIncludeBit3_64) {
    // Values 1, 2, 4 don't include bit 3
    EXPECT_FALSE(Catch::shouldSuppressFailure(1));
    EXPECT_FALSE(Catch::shouldSuppressFailure(2));
    EXPECT_FALSE(Catch::shouldSuppressFailure(4));
    EXPECT_FALSE(Catch::shouldSuppressFailure(3)); // 0b011
    EXPECT_FALSE(Catch::shouldSuppressFailure(5)); // 0b101
    EXPECT_FALSE(Catch::shouldSuppressFailure(6)); // 0b110
    EXPECT_FALSE(Catch::shouldSuppressFailure(7)); // 0b111
}

TEST_F(ShouldSuppressFailureTest_64, ReturnsTrueForValuesIncludingBit3_64) {
    EXPECT_TRUE(Catch::shouldSuppressFailure(8));   // 0b1000
    EXPECT_TRUE(Catch::shouldSuppressFailure(9));   // 0b1001
    EXPECT_TRUE(Catch::shouldSuppressFailure(10));  // 0b1010
    EXPECT_TRUE(Catch::shouldSuppressFailure(11));  // 0b1011
    EXPECT_TRUE(Catch::shouldSuppressFailure(12));  // 0b1100
    EXPECT_TRUE(Catch::shouldSuppressFailure(13));  // 0b1101
    EXPECT_TRUE(Catch::shouldSuppressFailure(14));  // 0b1110
    EXPECT_TRUE(Catch::shouldSuppressFailure(15));  // 0b1111
}

// Constexpr test - verify it can be used at compile time
TEST_F(ShouldSuppressFailureTest_64, IsConstexprEvaluable_64) {
    constexpr bool result1 = Catch::shouldSuppressFailure(Catch::ResultDisposition::SuppressFail);
    constexpr bool result2 = Catch::shouldSuppressFailure(Catch::ResultDisposition::Normal);
    constexpr bool result3 = Catch::shouldSuppressFailure(0);
    
    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
    EXPECT_FALSE(result3);
}
