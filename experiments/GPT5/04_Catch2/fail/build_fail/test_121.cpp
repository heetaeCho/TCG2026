// File: test_binaryexpr_operator_ne_121.cpp

#include <gtest/gtest.h>

// Include the header that defines Catch::BinaryExpr
// (Path from prompt)
#include "catch2/internal/catch_decomposer.hpp"

// The fixture is light; we only need the type presence.
class BinaryExprTest_121 : public ::testing::Test {};

// ----------------------------------------------------------------------------
// [Normal/Boundary: Type presence / basic declarations]
// We verify that the type is available and can be referenced in declarations
// without instantiating any forbidden operators.
// ----------------------------------------------------------------------------
TEST_F(BinaryExprTest_121, CanDeclarePointer_121) {
    // Declaring a pointer/reference to an (even incomplete) type is valid and
    // does not instantiate any operators. This ensures the header provides the
    // symbol Catch::BinaryExpr and that we can compile against it.
    const Catch::BinaryExpr* ptr = nullptr;
    (void)ptr; // silence unused warning
}

// ----------------------------------------------------------------------------
// [Exceptional/Error case: Compile-time failure on chained comparison]
// The operator!= is intentionally defined to trigger a static_assert that
// chained comparisons are not supported.
//
// This cannot be an active (passing) test because it must FAIL TO COMPILE.
// We therefore provide an opt-in block that can be enabled locally if you
// want to verify the compile-time error and diagnostic message.
//
// To run the negative test, change `#if 0` to `#if 1` and build. Compilation
// should fail with a message similar to:
//   "chained comparisons are not supported inside assertions, wrap the
//    expression inside parentheses, or decompose it"
// ----------------------------------------------------------------------------
#if 0  // <-- switch to 1 to intentionally trigger a compile-time failure
TEST_F(BinaryExprTest_121, ChainedComparisonNotSupported_121) {
    // NOTE: We construct a const BinaryExpr "object" through a minimal
    // placeholder. In the real codebase, BinaryExpr is a proper type;
    // simply attempting to use operator!= must trip the static_assert.
    const Catch::BinaryExpr expr{};
    // This line is expected to cause a compile-time error due to the
    // static_assert in operator!=.
    // We deliberately keep the RHS simple; any T should trigger the same path.
    (void)(expr != 42); // EXPECTED: compile-time static_assert failure
}
#endif
