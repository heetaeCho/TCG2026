// File: test_binaryexpr_chained_greater_122.cpp
#include <gtest/gtest.h>

// Include the real header from your tree
#include "catch2/internal/catch_decomposer.hpp"

// ----------------------------------------------------------------------------
// This test suite verifies the *interface-level observable behavior* of
// Catch::BinaryExpr::operator>(T):
//  - Attempting to chain comparisons must be a compile-time error (static_assert).
//
// Notes:
//  * We do NOT re-implement or simulate BinaryExpr internals.
//  * The negative test is an intentional compile-time failure and is
//    enabled only if ENABLE_NEGATIVE_TESTS_122 is defined in the build.
// ----------------------------------------------------------------------------

// 1) Documented “negative compilation” test.
//    When ENABLE_NEGATIVE_TESTS_122 is defined, the code inside the block
//    attempts to use `operator>` and must fail to compile due to the
//    static_assert in the provided interface.
//    This adheres to the black-box behavior: using the operator is ill-formed.

#ifndef ENABLE_NEGATIVE_TESTS_122

TEST(Catch2BinaryExprTest_122, ChainedGreater_IsACompileTimeError_Documented_122) {
    // We cannot *execute* a compile-time failure inside a running test.
    // Instead, we document and enforce it via an opt-in build configuration.
    GTEST_SKIP() << "Define ENABLE_NEGATIVE_TESTS_122 to run the negative compile-time check "
                    "(code is expected not to compile by design).";
}

#else

// If you enable this block (by defining ENABLE_NEGATIVE_TESTS_122), your build
// should fail to compile here, proving the observable contract holds.
//
// We intentionally put the ill-formed expression in a function that would be
// instantiated when this TU is compiled. There is no attempt to catch or
// bypass the static_assert; the failure is the expected result.

namespace {
// Helper that tries to use the forbidden chained comparison path.
template <typename E>
void AttemptChainedGreater(const E& e) {
    // This line must trigger the static_assert inside the provided operator>.
    // No evaluation occurs; the *act of forming the expression* with operator>
//  is enough to cause the compile-time error per the interface.
    (void)(e > 42);
}
} // namespace

// The following test will never run; the compilation is expected to fail
// earlier due to the static_assert in the operator implementation.
TEST(Catch2BinaryExprTest_122, ChainedGreater_TriggersStaticAssert_122) {
    // Constructing BinaryExpr as an object. We rely on the real header’s
    // availability; no internal details are assumed here.
    Catch::BinaryExpr expr{};
    AttemptChainedGreater(expr);

    // If somehow this compiled (it shouldn't), fail hard at runtime.
    FAIL() << "Compilation should have failed due to static_assert in operator>.";
}

#endif // ENABLE_NEGATIVE_TESTS_122

// 2) Smoke test: the suite itself is wired correctly.
//    (No assumptions about internals; just ensures the test file integrates.)
TEST(Catch2BinaryExprTest_122, SuiteCompilesAndLinks_122) {
    SUCCEED();
}
