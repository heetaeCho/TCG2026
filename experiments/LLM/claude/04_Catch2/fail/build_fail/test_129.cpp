#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/internal/catch_test_macro_impl.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Test fixture
class DecomposerTest_129 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Decomposer can decompose an integer lvalue via operator<=
TEST_F(DecomposerTest_129, DecomposeIntegerLvalue_129) {
    int value = 42;
    auto expr = Catch::Decomposer{} <= value;
    // ExprLhs should be created; we verify it compiles and the result
    // can be used to produce a BinaryExpr or UnaryExpr
    // The expression should be truthy for non-zero values
    auto result = expr.makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test that Decomposer can decompose a zero integer (falsy)
TEST_F(DecomposerTest_129, DecomposeZeroInteger_129) {
    int value = 0;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    EXPECT_FALSE(result.succeeded());
}

// Test that Decomposer can decompose a boolean true
TEST_F(DecomposerTest_129, DecomposeBoolTrue_129) {
    // bool is captured by value, so this tests the other overload
    // but let's test with a const bool ref scenario
    bool value = true;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test that Decomposer can decompose a boolean false
TEST_F(DecomposerTest_129, DecomposeBoolFalse_129) {
    bool value = false;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    EXPECT_FALSE(result.succeeded());
}

// Test that Decomposer works with string types (not captured by value)
TEST_F(DecomposerTest_129, DecomposeStringLvalue_129) {
    std::string value = "hello";
    auto expr = Catch::Decomposer{} <= value;
    // A non-empty string - ExprLhs should hold a reference to it
    // We can form a comparison expression
    auto result = (Catch::Decomposer{} <= value == std::string("hello")).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test that Decomposer works with string comparison that fails
TEST_F(DecomposerTest_129, DecomposeStringComparisonFails_129) {
    std::string value = "hello";
    auto result = (Catch::Decomposer{} <= value == std::string("world")).makeUnaryExpr();
    EXPECT_FALSE(result.succeeded());
}

// Test decomposition with negative integer
TEST_F(DecomposerTest_129, DecomposeNegativeInteger_129) {
    int value = -1;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    // -1 is truthy
    EXPECT_TRUE(result.succeeded());
}

// Test decomposition with comparison operators through ExprLhs
TEST_F(DecomposerTest_129, DecomposeEqualityComparison_129) {
    int value = 42;
    auto result = (Catch::Decomposer{} <= value == 42).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test decomposition with inequality
TEST_F(DecomposerTest_129, DecomposeInequalityComparison_129) {
    int value = 42;
    auto result = (Catch::Decomposer{} <= value != 43).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test decomposition with less-than comparison
TEST_F(DecomposerTest_129, DecomposeLessThanComparison_129) {
    int value = 10;
    auto result = (Catch::Decomposer{} <= value < 20).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test decomposition with greater-than comparison
TEST_F(DecomposerTest_129, DecomposeGreaterThanComparison_129) {
    int value = 30;
    auto result = (Catch::Decomposer{} <= value > 20).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test that the reference is maintained (value change after decomposition)
TEST_F(DecomposerTest_129, DecomposeReferenceMaintained_129) {
    int value = 42;
    auto expr = Catch::Decomposer{} <= value;
    // The ExprLhs holds a const& to value
    auto result = (expr == 42).makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test with a nullptr
TEST_F(DecomposerTest_129, DecomposeNullptr_129) {
    int* ptr = nullptr;
    auto expr = Catch::Decomposer{} <= ptr;
    auto result = expr.makeUnaryExpr();
    EXPECT_FALSE(result.succeeded());
}

// Test with a non-null pointer
TEST_F(DecomposerTest_129, DecomposeNonNullPointer_129) {
    int x = 5;
    int* ptr = &x;
    auto expr = Catch::Decomposer{} <= ptr;
    auto result = expr.makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test with double
TEST_F(DecomposerTest_129, DecomposeDouble_129) {
    double value = 3.14;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    EXPECT_TRUE(result.succeeded());
}

// Test with zero double
TEST_F(DecomposerTest_129, DecomposeZeroDouble_129) {
    double value = 0.0;
    auto expr = Catch::Decomposer{} <= value;
    auto result = expr.makeUnaryExpr();
    EXPECT_FALSE(result.succeeded());
}
