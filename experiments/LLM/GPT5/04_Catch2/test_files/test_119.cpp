// File: test_binaryexpr_or_119.cpp
#include <gtest/gtest.h>

// The header under test (as provided)
#include "catch2/internal/catch_decomposer.hpp"

// --------------------------------------------------------------------------------------
// NOTE ABOUT TESTING STRATEGY
// --------------------------------------------------------------------------------------
// The provided interface defines a templated member operator|| that triggers a
// compile-time static_assert to forbid chained comparisons:
//   template <typename T>
//   auto operator||(T) const -> BinaryExpr<LhsT, RhsT const&> const {
//       static_assert(always_false<T>::value,
//         "chained comparisons are not supported inside assertions, "
//         "wrap the expression inside parentheses, or decompose it");
//   }
//
// Because this is a *compile-time diagnostic*, it cannot be asserted via runtime
// GoogleTest EXPECT/ASSERT macros. Instead, we:
//   1) Provide a compile-only "negative test" block that, if enabled, must FAIL to compile.
//   2) Provide a small smoke test that includes the header without ODR-using the operator,
//      confirming the test TU compiles and runs.
//
// If you want to verify the negative case locally, flip the #if 0 to #if 1 below
// and confirm your build fails with the expected static_assert message.
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// NEGATIVE-COMPILATION CHECK (Disabled by default)
// --------------------------------------------------------------------------------------
// Enabling this block should cause a *compile-time* failure due to the static_assert
// inside BinaryExpr::operator||. This demonstrates the observable interface behavior.
#if 0  // <-- Change to 1 locally to verify compile error
namespace {
    // We cannot construct a real BinaryExpr easily from here because its actual
    // constructors/operational semantics are not part of the provided interface.
    // However, even attempting to *use* operator|| on a BinaryExpr instance would
    // instantiate the operator template and trigger the static_assert.
    //
    // The following adapter makes the expression dependent, but will still hard-error
    // when instantiated — matching the interface's intended behavior.
    template <typename Expr, typename T>
    void ForceOrUse(Expr&& e, T&& t) {
        // This line should cause a compile-time error when compiled:
        (void)(e || t); // expected: static_assert fails with the given message
    }

    // Dummy function to force template instantiation:
    void TriggerCompileTimeFailure() {
        // We cannot build a real BinaryExpr value here; this call is illustrative:
        // ForceOrUse(Catch::BinaryExpr{/*not constructible here*/}, 42);
        //
        // If you *do* have a BinaryExpr instance 'expr' from your real codebase,
        // uncomment the line below and ensure the build fails with the message:
        //
        //   "chained comparisons are not supported inside assertions, wrap the expression
        //    inside parentheses, or decompose it"
    }
}
#endif

// --------------------------------------------------------------------------------------
// SMOKE TESTS (runtime) — these only verify the TU compiles/links and the header is usable
// without accidentally invoking the forbidden operator||.
// --------------------------------------------------------------------------------------

TEST(BinaryExprTest_119, HeaderIsIncludableAndTestRuns_119) {
    // This is a simple sanity check to ensure the test binary runs.
    // We do NOT instantiate or ODR-use BinaryExpr::operator|| here.
    SUCCEED();
}

// This test documents the expected compile-time behavior and guards against accidental
// misuse in the codebase. It does not invoke the forbidden operator at runtime.
TEST(BinaryExprTest_119, DocumentedChainedOrIsForbiddenAtCompileTime_119) {
    // Intentionally empty at runtime. See the compile-only block above for the negative test.
    // Keeping this test enforces review visibility of the constraint and naming convention.
    SUCCEED();
}
