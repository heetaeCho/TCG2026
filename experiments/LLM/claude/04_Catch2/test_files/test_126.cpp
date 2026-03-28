#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/internal/catch_test_macro_impl.hpp>
#include <gtest/gtest.h>
#include <type_traits>

// TEST_ID is 126

// Since the operator&& in ExprLhs is specifically designed to trigger a
// static_assert (compile-time error), we cannot test its invocation at runtime.
// We test the decomposer's valid behavior and verify the type traits that
// make the static_assert work.

class CatchDecomposerTest_126 : public ::testing::Test {
protected:
    Catch::Decomposer decomposer;
};

// Test that the Decomposer can create an ExprLhs from an integer
TEST_F(CatchDecomposerTest_126, DecomposerCreatesExprLhsFromInt_126) {
    auto expr = decomposer <= 42;
    // The expression should be truthy for non-zero values
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that the Decomposer handles zero (falsy) value
TEST_F(CatchDecomposerTest_126, DecomposerHandlesZeroValue_126) {
    auto expr = decomposer <= 0;
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test that the Decomposer handles boolean true
TEST_F(CatchDecomposerTest_126, DecomposerHandlesBoolTrue_126) {
    auto expr = decomposer <= true;
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that the Decomposer handles boolean false
TEST_F(CatchDecomposerTest_126, DecomposerHandlesBoolFalse_126) {
    auto expr = decomposer <= false;
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test that ExprLhs supports equality comparison
TEST_F(CatchDecomposerTest_126, ExprLhsSupportsEqualityComparison_126) {
    auto expr = decomposer <= 5 == 5;
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that ExprLhs supports inequality comparison
TEST_F(CatchDecomposerTest_126, ExprLhsSupportsInequalityComparison_126) {
    auto expr = decomposer <= 5 != 3;
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that ExprLhs supports less-than comparison
TEST_F(CatchDecomposerTest_126, ExprLhsSupportsLessThanComparison_126) {
    auto expr = decomposer <= 3 < 5;
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test that always_false trait is indeed false for various types
// This is the trait used in the static_assert for operator&&
TEST_F(CatchDecomposerTest_126, AlwaysFalseIsFalseForInt_126) {
    EXPECT_FALSE(Catch::Detail::always_false<int>::value);
}

TEST_F(CatchDecomposerTest_126, AlwaysFalseIsFalseForDouble_126) {
    EXPECT_FALSE(Catch::Detail::always_false<double>::value);
}

TEST_F(CatchDecomposerTest_126, AlwaysFalseIsFalseForString_126) {
    EXPECT_FALSE(Catch::Detail::always_false<std::string>::value);
}

// Test decomposer with negative values
TEST_F(CatchDecomposerTest_126, DecomposerHandlesNegativeValue_126) {
    auto expr = decomposer <= -1;
    // Non-zero, so truthy (implementation dependent on how ExprLhs converts)
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Test decomposer with pointer (nullptr)
TEST_F(CatchDecomposerTest_126, DecomposerHandlesNullptr_126) {
    int* p = nullptr;
    auto expr = decomposer <= p;
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test decomposer with non-null pointer
TEST_F(CatchDecomposerTest_126, DecomposerHandlesNonNullPointer_126) {
    int val = 42;
    int* p = &val;
    auto expr = decomposer <= p;
    EXPECT_TRUE(static_cast<bool>(expr));
}
