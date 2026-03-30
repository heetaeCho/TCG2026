// File: test_binaryexpr_ge_124.cpp
#include <gtest/gtest.h>

// Include the provided header exactly as given
#include "Catch2/src/catch2/internal/catch_decomposer.hpp"

// We do not access or assume any private/internal state.
// We only verify observable interface constraints per the task.

namespace {

using ::testing::Test;

// Basic smoke test to ensure the header is includable and the type is usable
// without invoking the disallowed comparison operator.
//
// NOTE: We do not construct any internal state beyond what the public
// interface allows (default construction). We do NOT call operator>=
// because the interface intentionally forbids it via a compile-time error.
TEST(BinaryExpr_124, HeaderCompilesAndTypeIsInstantiable_124) {
    // Treat as black box: default-construct and ensure test compiles/links.
    // (If default construction is not allowed by the real implementation,
    // this line can be removed; the key point is we do not exercise >=.)
    Catch::BinaryExpr expr{};
    (void)expr; // silence unused warning
    SUCCEED();  // Reaching here means normal use (sans >=) compiles.
}

// -------------------------
// Negative compilation test
// -------------------------
//
// This block is DISABLED by default. If you define ENABLE_NEGATIVE_COMPILE_124
// in a dedicated "negative compilation" build, it will try to use the forbidden
// operator and should fail at compile time with the interface's static_assert
// message:
//
//   "chained comparisons are not supported inside assertions, wrap the
//    expression inside parentheses, or decompose it"
//
// This respects the constraints: we do not re-implement logic, we only
// demonstrate that invoking the public operator is rejected at compile time.
#ifdef ENABLE_NEGATIVE_COMPILE_124
TEST(BinaryExpr_124, ChainedComparisonIsRejectedAtCompileTime_124) {
    Catch::BinaryExpr expr{};
    // The next line should trigger the interface's static_assert and fail
    // compilation when this block is enabled.
    (void)(expr >= 42);
    // If your build reaches here with this macro enabled, the interface's
    // compile-time guard did not trigger as expected.
    FAIL() << "operator>= did not trigger compile-time rejection as expected";
}
#endif  // ENABLE_NEGATIVE_COMPILE_124

} // namespace
