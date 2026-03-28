// File: binaryexpr_operator_lt_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_decomposer.hpp"

// Basic smoke fixture (not strictly needed but keeps naming consistent)
class BinaryExprTest_123 : public ::testing::Test {};

// 1) Sanity: the public type is complete and usable as a regular C++ type,
//    without instantiating operator<.
TEST_F(BinaryExprTest_123, TypeIsCompleteAndHasPositiveSize_123) {
    // Verifies we can form objects/pointers/references to the type without touching operator<
    EXPECT_GT(sizeof(Catch::BinaryExpr), 0u);
    Catch::BinaryExpr* ptr = nullptr; // pointer to demonstrate usability
    (void)ptr;
}

// 2) Interface-level traits: the type should be copy/move constructible by default
//    (no private/protected constructors are exposed in the interface snippet).
TEST_F(BinaryExprTest_123, TypeIsCopyAndMoveConstructible_123) {
    static_assert(std::is_copy_constructible<Catch::BinaryExpr>::value,
                  "BinaryExpr should be copy constructible by interface assumptions");
    static_assert(std::is_move_constructible<Catch::BinaryExpr>::value,
                  "BinaryExpr should be move constructible by interface assumptions");

    EXPECT_TRUE(std::is_copy_constructible<Catch::BinaryExpr>::value);
    EXPECT_TRUE(std::is_move_constructible<Catch::BinaryExpr>::value);
}

// 3) Documented negative test (skipped): attempting to use operator< on BinaryExpr
//    is a compile-time error by design (static_assert in the template body).
//    We cannot run a test that actually triggers a compile error, so we:
//      - Provide the exact code that would fail, commented out.
//      - Mark the test as skipped, explaining the rationale.
//    Maintainers can temporarily uncomment the block locally to verify the failure message.
TEST_F(BinaryExprTest_123, ChainedComparisonIsCompileTimeError_Documented_123) {
    GTEST_SKIP() << "This is a documentation/negative test. "
                    "Instantiating BinaryExpr::operator< triggers a compile-time static_assert "
                    "to prohibit chained comparisons. See the commented code below.";

#if 0
    // WARNING: UNCOMMENTING THIS BLOCK WILL MAKE THE TEST FILE FAIL TO COMPILE,
    // which is the intended behavior enforced by the interface.

    Catch::BinaryExpr expr;        // Construct an expression object
    int rhs = 42;

    // The following line *instantiates* the templated operator<, causing the static_assert to fire:
    // "chained comparisons are not supported inside assertions, wrap the expression inside parentheses, or decompose it"
    auto illegal = (expr < rhs);   // expected: compile-time error by design

    (void)illegal;
#endif
}
