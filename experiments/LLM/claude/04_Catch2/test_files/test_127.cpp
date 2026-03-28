#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/internal/catch_test_macro_impl.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// TEST_ID is 127

// Test that the Decomposer can decompose simple expressions
TEST(CatchDecomposerTest_127, DecomposerCreatesExprLhs_127) {
    Catch::Decomposer decomposer;
    // Decomposer's operator<= creates an ExprLhs from a value
    auto expr = decomposer <= 42;
    // The expression should be truthy for non-zero values
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithFalseValue_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 0;
    EXPECT_FALSE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithTrueBoolean_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= true;
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithFalseBoolean_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= false;
    EXPECT_FALSE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, ExprLhsEqualityComparison_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 5 == 5;
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, ExprLhsInequalityComparison_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 5 == 6;
    EXPECT_FALSE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithNullptr_127) {
    Catch::Decomposer decomposer;
    int* p = nullptr;
    auto expr = decomposer <= p;
    EXPECT_FALSE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithNonNullPtr_127) {
    Catch::Decomposer decomposer;
    int val = 42;
    int* p = &val;
    auto expr = decomposer <= p;
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithNegativeValue_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= -1;
    // Non-zero should be truthy
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithStringLiteral_127) {
    Catch::Decomposer decomposer;
    // A non-null string literal pointer should be truthy
    auto expr = decomposer <= "hello";
    EXPECT_TRUE(static_cast<bool>(expr));
}

// Verify that operator|| static_assert exists - this is a compile-time check
// We verify the type trait that always_false is indeed false for any type
TEST(CatchDecomposerTest_127, AlwaysFalseIsFalse_127) {
    EXPECT_FALSE(Catch::Detail::always_false<int>::value);
    EXPECT_FALSE(Catch::Detail::always_false<double>::value);
    EXPECT_FALSE(Catch::Detail::always_false<std::string>::value);
    EXPECT_FALSE(Catch::Detail::always_false<void>::value);
}

TEST(CatchDecomposerTest_127, DecomposerWithDoubleValue_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 3.14;
    EXPECT_TRUE(static_cast<bool>(expr));
}

TEST(CatchDecomposerTest_127, DecomposerWithZeroDouble_127) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 0.0;
    EXPECT_FALSE(static_cast<bool>(expr));
}
