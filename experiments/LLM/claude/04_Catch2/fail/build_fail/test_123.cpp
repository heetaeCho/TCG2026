#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

namespace {

// Test fixture
class BinaryExprTest_123 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the Catch namespace and decomposer components exist
TEST_F(BinaryExprTest_123, DecomposerExists_123) {
    // Verify that Decomposer type exists and can be instantiated
    Catch::Decomposer decomposer;
    (void)decomposer;
    SUCCEED();
}

// Test that decomposition of simple less-than comparison works
TEST_F(BinaryExprTest_123, SimpleLessThanDecomposition_123) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 3 < 5;
    // The expression `3 < 5` is evaluated first (as bool true), 
    // then decomposer <= true creates a UnaryExpr
    // This should compile and work fine since it's not a chained comparison
    SUCCEED();
}

// Test decomposition with equality
TEST_F(BinaryExprTest_123, SimpleEqualityDecomposition_123) {
    Catch::Decomposer decomposer;
    int a = 5;
    auto expr = decomposer <= a == 5;
    (void)expr;
    SUCCEED();
}

// Test decomposition with integer values
TEST_F(BinaryExprTest_123, IntegerValueDecomposition_123) {
    Catch::Decomposer decomposer;
    int value = 42;
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Test decomposition with boolean values
TEST_F(BinaryExprTest_123, BooleanValueDecomposition_123) {
    Catch::Decomposer decomposer;
    bool value = true;
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Test decomposition with string values
TEST_F(BinaryExprTest_123, StringValueDecomposition_123) {
    Catch::Decomposer decomposer;
    std::string value = "hello";
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Test decomposition with nullptr
TEST_F(BinaryExprTest_123, NullptrDecomposition_123) {
    Catch::Decomposer decomposer;
    int* ptr = nullptr;
    auto expr = decomposer <= ptr;
    (void)expr;
    SUCCEED();
}

// Test decomposition with negative values
TEST_F(BinaryExprTest_123, NegativeValueDecomposition_123) {
    Catch::Decomposer decomposer;
    int value = -1;
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Test decomposition with zero boundary
TEST_F(BinaryExprTest_123, ZeroValueDecomposition_123) {
    Catch::Decomposer decomposer;
    int value = 0;
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Test decomposition with floating point
TEST_F(BinaryExprTest_123, FloatingPointDecomposition_123) {
    Catch::Decomposer decomposer;
    double value = 3.14;
    auto expr = decomposer <= value;
    (void)expr;
    SUCCEED();
}

// Note: Chained comparison test (e.g., `decomposer <= a < b < c`) 
// cannot be tested at runtime because it triggers a static_assert 
// at compile time, which is the intended behavior of BinaryExpr::operator<

} // namespace
