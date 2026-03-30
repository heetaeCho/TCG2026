// File: test_operator_or_127.cpp
#include <gtest/gtest.h>

// The header under test (black box)
#include "catch2/internal/catch_decomposer.hpp"

// Test fixture (kept minimal as we don't rely on any private state)
class OperatorOrTest_127 : public ::testing::Test {
protected:
    // Helper with observable side effect to verify short-circuiting behavior
    struct SideEffect {
        int* counter;
        explicit SideEffect(int& c) : counter(&c) {}
        bool call() {
            ++(*counter);
            return true;
        }
    };
};

// [Normal operation] Built-in logical-or works for plain bools and returns expected result.
TEST_F(OperatorOrTest_127, BoolOrReturnsExpected_127) {
    const bool a = false;
    const bool b = true;
    EXPECT_TRUE(a || b);
    EXPECT_FALSE(a || false);
    EXPECT_TRUE(true || b);
}

// [Boundary/observable behavior] Short-circuiting: RHS must not evaluate when LHS is true.
TEST_F(OperatorOrTest_127, ShortCircuitsWhenLeftIsTrue_127) {
    int calls = 0;
    SideEffect s(calls);

    // LHS true -> RHS must not be evaluated
    bool result = true || s.call();
    EXPECT_TRUE(result);
    EXPECT_EQ(calls, 0) << "RHS should not be evaluated due to short-circuiting";
}

// [Boundary/observable behavior] RHS is evaluated when LHS is false.
TEST_F(OperatorOrTest_127, EvaluatesRightWhenLeftIsFalse_127) {
    int calls = 0;
    SideEffect s(calls);

    bool result = false || s.call();
    EXPECT_TRUE(result);
    EXPECT_EQ(calls, 1) << "RHS should be evaluated when LHS is false";
}

/*
  ──────────────────────────────────────────────────────────────────────────────
  Optional negative-compile check (disabled by default):

  The provided interface declares a friend template operator|| that triggers a
  static_assert with the message:

      "operator|| is not supported inside assertions, wrap the expression
       inside parentheses, or decompose it"

  Any attempt to directly form an expression that binds to that operator should
  be a *compile-time* error. Because negative compilation cannot be expressed as
  a runtime test, we keep it behind a macro so normal test builds stay green.

  To enable locally (expecting compilation to fail), build with:
      -DENABLE_NEGATIVE_COMPILE_TESTS_OPERATOR_OR_127

  Notes:
  - We do not re-implement or simulate internal types/logic.
  - If the full Catch2 decomposition types (e.g., Catch::ExprLhs, Catch::BinaryExpr)
    are visible via the included header in your environment, forming the expression
    below should instantiate the forbidden operator and fail to compile.
*/
#ifdef ENABLE_NEGATIVE_COMPILE_TESTS_OPERATOR_OR_127
// Intentionally NOT inside a TEST_... because it should fail at compile time.
namespace {
    using CatchExpr = Catch::ExprLhs<int>;  // Uses the real type from the header if available.

    // This line should trigger the static_assert in the provided operator||.
    static auto kForceForbiddenOr_127 =
        std::declval<CatchExpr&&>() || 1; // expect compile-time failure
}
#endif
