#include "catch2/internal/catch_result_type.hpp"
#include <gtest/gtest.h>

namespace {

class ResultDispositionTest_62 : public ::testing::Test {
protected:
};

// Test combining two different flags
TEST_F(ResultDispositionTest_62, OrOperatorCombinesTwoFlags_62) {
    auto result = Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest;
    EXPECT_EQ(static_cast<int>(result),
              static_cast<int>(Catch::ResultDisposition::Normal) | static_cast<int>(Catch::ResultDisposition::FalseTest));
}

// Test that Normal (0) OR'd with any flag returns that flag
TEST_F(ResultDispositionTest_62, OrWithNormalReturnsOtherFlag_62) {
    auto result = Catch::ResultDisposition::Normal | Catch::ResultDisposition::ContinueOnFailure;
    EXPECT_EQ(static_cast<int>(result), static_cast<int>(Catch::ResultDisposition::ContinueOnFailure));
}

// Test OR of a flag with itself is idempotent
TEST_F(ResultDispositionTest_62, OrWithSelfIsIdempotent_62) {
    auto result = Catch::ResultDisposition::FalseTest | Catch::ResultDisposition::FalseTest;
    EXPECT_EQ(static_cast<int>(result), static_cast<int>(Catch::ResultDisposition::FalseTest));
}

// Test combining ContinueOnFailure and FalseTest
TEST_F(ResultDispositionTest_62, OrContinueOnFailureAndFalseTest_62) {
    auto result = Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest;
    int expected = static_cast<int>(Catch::ResultDisposition::ContinueOnFailure) |
                   static_cast<int>(Catch::ResultDisposition::FalseTest);
    EXPECT_EQ(static_cast<int>(result), expected);
}

// Test that Normal OR Normal yields Normal
TEST_F(ResultDispositionTest_62, OrNormalWithNormalYieldsNormal_62) {
    auto result = Catch::ResultDisposition::Normal | Catch::ResultDisposition::Normal;
    EXPECT_EQ(static_cast<int>(result), static_cast<int>(Catch::ResultDisposition::Normal));
}

// Test that the result type is ResultDisposition::Flags
TEST_F(ResultDispositionTest_62, ReturnTypeIsFlags_62) {
    auto result = Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest;
    bool isSameType = std::is_same<decltype(result), Catch::ResultDisposition::Flags>::value;
    EXPECT_TRUE(isSameType);
}

// Test combining SuppressFail with other flags
TEST_F(ResultDispositionTest_62, OrSuppressFailWithContinueOnFailure_62) {
    auto result = Catch::ResultDisposition::SuppressFail | Catch::ResultDisposition::ContinueOnFailure;
    int expected = static_cast<int>(Catch::ResultDisposition::SuppressFail) |
                   static_cast<int>(Catch::ResultDisposition::ContinueOnFailure);
    EXPECT_EQ(static_cast<int>(result), expected);
}

// Test constexpr evaluation
TEST_F(ResultDispositionTest_62, OperatorIsConstexpr_62) {
    constexpr auto result = Catch::ResultDisposition::FalseTest | Catch::ResultDisposition::SuppressFail;
    constexpr int expected = static_cast<int>(Catch::ResultDisposition::FalseTest) |
                             static_cast<int>(Catch::ResultDisposition::SuppressFail);
    EXPECT_EQ(static_cast<int>(result), expected);
}

// Test chaining multiple OR operations
TEST_F(ResultDispositionTest_62, ChainingMultipleOrOperations_62) {
    auto result = Catch::ResultDisposition::ContinueOnFailure |
                  Catch::ResultDisposition::FalseTest |
                  Catch::ResultDisposition::SuppressFail;
    int expected = static_cast<int>(Catch::ResultDisposition::ContinueOnFailure) |
                   static_cast<int>(Catch::ResultDisposition::FalseTest) |
                   static_cast<int>(Catch::ResultDisposition::SuppressFail);
    EXPECT_EQ(static_cast<int>(result), expected);
}

// Test commutativity of OR operator
TEST_F(ResultDispositionTest_62, OrOperatorIsCommutative_62) {
    auto result1 = Catch::ResultDisposition::FalseTest | Catch::ResultDisposition::SuppressFail;
    auto result2 = Catch::ResultDisposition::SuppressFail | Catch::ResultDisposition::FalseTest;
    EXPECT_EQ(static_cast<int>(result1), static_cast<int>(result2));
}

} // namespace
