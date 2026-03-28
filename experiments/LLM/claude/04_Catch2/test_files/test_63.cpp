#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_result_type.hpp"

// Test that isFalseTest returns true when FalseTest flag is set alone
TEST(IsFalseTestTest_63, ReturnsTrueWhenFalseTestFlagIsSet_63) {
    EXPECT_TRUE(Catch::isFalseTest(Catch::ResultDisposition::FalseTest));
}

// Test that isFalseTest returns false when Normal flag is set
TEST(IsFalseTestTest_63, ReturnsFalseWhenNormalFlagIsSet_63) {
    EXPECT_FALSE(Catch::isFalseTest(Catch::ResultDisposition::Normal));
}

// Test that isFalseTest returns false when ContinueOnFailure flag is set
TEST(IsFalseTestTest_63, ReturnsFalseWhenContinueOnFailureFlagIsSet_63) {
    EXPECT_FALSE(Catch::isFalseTest(Catch::ResultDisposition::ContinueOnFailure));
}

// Test that isFalseTest returns false when SuppressFail flag is set
TEST(IsFalseTestTest_63, ReturnsFalseWhenSuppressFailFlagIsSet_63) {
    EXPECT_FALSE(Catch::isFalseTest(Catch::ResultDisposition::SuppressFail));
}

// Test that isFalseTest returns false when flags is zero
TEST(IsFalseTestTest_63, ReturnsFalseWhenFlagsIsZero_63) {
    EXPECT_FALSE(Catch::isFalseTest(0));
}

// Test that isFalseTest returns true when FalseTest is combined with Normal
TEST(IsFalseTestTest_63, ReturnsTrueWhenFalseTestCombinedWithNormal_63) {
    int flags = Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

// Test that isFalseTest returns true when FalseTest is combined with ContinueOnFailure
TEST(IsFalseTestTest_63, ReturnsTrueWhenFalseTestCombinedWithContinueOnFailure_63) {
    int flags = Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

// Test that isFalseTest returns true when FalseTest is combined with SuppressFail
TEST(IsFalseTestTest_63, ReturnsTrueWhenFalseTestCombinedWithSuppressFail_63) {
    int flags = Catch::ResultDisposition::SuppressFail | Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

// Test that isFalseTest returns true when all flags are combined
TEST(IsFalseTestTest_63, ReturnsTrueWhenAllFlagsCombined_63) {
    int flags = Catch::ResultDisposition::Normal |
                Catch::ResultDisposition::ContinueOnFailure |
                Catch::ResultDisposition::FalseTest |
                Catch::ResultDisposition::SuppressFail;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

// Test that isFalseTest returns false when flags combine Normal, ContinueOnFailure, and SuppressFail but not FalseTest
TEST(IsFalseTestTest_63, ReturnsFalseWhenAllFlagsExceptFalseTestCombined_63) {
    int flags = Catch::ResultDisposition::Normal |
                Catch::ResultDisposition::ContinueOnFailure |
                Catch::ResultDisposition::SuppressFail;
    EXPECT_FALSE(Catch::isFalseTest(flags));
}

// Test with the exact numeric value of FalseTest (4)
TEST(IsFalseTestTest_63, ReturnsTrueWhenRawValue4Passed_63) {
    EXPECT_TRUE(Catch::isFalseTest(4));
}

// Test with a value that doesn't have bit 2 set (value 3 = 0b011)
TEST(IsFalseTestTest_63, ReturnsFalseWhenValue3Passed_63) {
    EXPECT_FALSE(Catch::isFalseTest(3));
}

// Test with value 5 (0b101) which has FalseTest bit set
TEST(IsFalseTestTest_63, ReturnsTrueWhenValue5Passed_63) {
    EXPECT_TRUE(Catch::isFalseTest(5));
}

// Test with value 7 (0b111) which has FalseTest bit set
TEST(IsFalseTestTest_63, ReturnsTrueWhenValue7Passed_63) {
    EXPECT_TRUE(Catch::isFalseTest(7));
}

// Test with value 8 which does not have FalseTest bit set
TEST(IsFalseTestTest_63, ReturnsFalseWhenValue8Passed_63) {
    EXPECT_FALSE(Catch::isFalseTest(8));
}

// Test constexpr usage at compile time
TEST(IsFalseTestTest_63, IsConstexprEvaluable_63) {
    constexpr bool result = Catch::isFalseTest(Catch::ResultDisposition::FalseTest);
    EXPECT_TRUE(result);

    constexpr bool result2 = Catch::isFalseTest(Catch::ResultDisposition::Normal);
    EXPECT_FALSE(result2);
}
