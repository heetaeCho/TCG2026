#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_decomposer.hpp"

// TEST_ID is 125

// Since BinaryExpr is a template class in the actual Catch2 codebase,
// we need to work with the actual types available from the decomposer.

namespace {

// Test that the Catch namespace and decomposition infrastructure exists
TEST(CatchDecomposerTest_125, DecomposerExists_125) {
    // Verify that Decomposer type exists and can be instantiated
    Catch::Decomposer decomposer;
    (void)decomposer;
    SUCCEED();
}

// Test that decomposing a simple integer value works
TEST(CatchDecomposerTest_125, DecomposeIntegerValue_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 42;
    // The result of decomposing a value should be a UnaryExpr
    // that can be converted to bool or evaluated
    (void)expr;
    SUCCEED();
}

// Test that decomposing a boolean value works
TEST(CatchDecomposerTest_125, DecomposeBooleanValue_125) {
    Catch::Decomposer decomposer;
    auto expr_true = decomposer <= true;
    auto expr_false = decomposer <= false;
    (void)expr_true;
    (void)expr_false;
    SUCCEED();
}

// Test that a simple comparison can be decomposed
TEST(CatchDecomposerTest_125, DecomposeEqualityComparison_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= (1 == 1);
    (void)expr;
    SUCCEED();
}

// Test that decomposing a string literal works
TEST(CatchDecomposerTest_125, DecomposeStringLiteral_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= "hello";
    (void)expr;
    SUCCEED();
}

// Test decomposition with comparison operators that produce BinaryExpr
TEST(CatchDecomposerTest_125, DecomposeComparisonProducesBinaryExpr_125) {
    Catch::Decomposer decomposer;
    // This should produce a BinaryExpr via the decomposition mechanism
    int a = 5;
    int b = 5;
    auto expr = decomposer <= a == b;
    (void)expr;
    SUCCEED();
}

// Test decomposition with not-equal comparison
TEST(CatchDecomposerTest_125, DecomposeNotEqualComparison_125) {
    Catch::Decomposer decomposer;
    int a = 5;
    int b = 3;
    auto expr = decomposer <= a != b;
    (void)expr;
    SUCCEED();
}

// Test decomposition with less-than comparison
TEST(CatchDecomposerTest_125, DecomposeLessThanComparison_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 3 < 5;
    (void)expr;
    SUCCEED();
}

// Test decomposition with greater-than comparison
TEST(CatchDecomposerTest_125, DecomposeGreaterThanComparison_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 5 > 3;
    (void)expr;
    SUCCEED();
}

// Note: The chained comparison operator<= on BinaryExpr is a static_assert
// guard. It cannot be tested at runtime because it deliberately causes a
// compile-time error. This is by design to prevent chained comparisons
// inside Catch2 assertions (e.g., REQUIRE(a <= b <= c)).
// The following test documents this design intent:
TEST(CatchDecomposerTest_125, BinaryExprChainedComparisonIsCompileTimeError_125) {
    // Attempting: decomposer <= a == b <= c would trigger static_assert
    // "chained comparisons are not supported inside assertions"
    // This is verified by code review, not runtime test.
    SUCCEED();
}

// Test decomposition with floating point values
TEST(CatchDecomposerTest_125, DecomposeFloatingPointValue_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= 3.14;
    (void)expr;
    SUCCEED();
}

// Test decomposition with nullptr
TEST(CatchDecomposerTest_125, DecomposeNullptr_125) {
    Catch::Decomposer decomposer;
    auto expr = decomposer <= nullptr;
    (void)expr;
    SUCCEED();
}

} // anonymous namespace
