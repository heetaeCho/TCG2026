// File: catch_decomposer_and_operator_and_tests.cpp

#include <gtest/gtest.h>

// NOTE ABOUT SCOPE OF TESTING:
// The provided interface is a friend-template overload of operator&& inside Catch2's
// decomposer that intentionally triggers a compile-time error when used in assertions.
// Per the constraints, we must treat the implementation as a black box and test only
// observable behavior through the interface. Since the observable behavior here is a
// *compile-time* prohibition (static_assert), actually invoking it would prevent
// the test binary from compiling. Therefore:
//   - We test normal operation of boolean && outside of Catch assertions.
//   - We demonstrate the safe parenthesized form that Catch suggests, also outside of Catch.
//   - We add a SKIPPED test documenting why the negative test cannot be compiled/run.

// ----------------------
// Test suite
// ----------------------

class CatchDecomposerAndOperatorTest_126 : public ::testing::Test {};

// [Normal operation] Basic truth table for boolean &&
TEST_F(CatchDecomposerAndOperatorTest_126, BoolAnd_BasicTruthTable_126) {
    // true && true -> true
    EXPECT_TRUE(true && true);

    // true && false -> false
    EXPECT_FALSE(true && false);

    // false && true -> false
    EXPECT_FALSE(false && true);

    // false && false -> false
    EXPECT_FALSE(false && false);
}

// [Boundary-ish] Parenthesized expression behaves as a single boolean value.
// This mirrors the guidance "wrap the expression inside parentheses" (done here
// in plain C++ context; *not* invoking Catch's decomposer).
TEST_F(CatchDecomposerAndOperatorTest_126, ParenthesizedAndExpression_EvaluatesAsSingleBool_126) {
    auto acceptsBool = [](bool v){ return v ? 1 : 0; };

    bool a = true;
    bool b = false;

    // Parenthesizing makes it a single boolean expression value.
    EXPECT_EQ(acceptsBool( (a && true) ), 1);
    EXPECT_EQ(acceptsBool( (a && b) ), 0);

    // Also verify nested parentheses do not alter semantics.
    EXPECT_EQ(acceptsBool( ((a && true)) ), 1);
    EXPECT_EQ(acceptsBool( ((a && b)) ), 0);
}

// [Documentation / Negative] The Catch decomposer's operator&& is intentionally
// not supported and triggers a compile-time error if used. That behavior cannot
// be verified in a *runtime* unit test because attempting to compile such a test
// would fail the build. We mark this test as skipped while clearly stating the contract.
TEST_F(CatchDecomposerAndOperatorTest_126, OperatorAnd_InsideCatchAssertions_IsCompileTimeError_126) {
    GTEST_SKIP() << "By design, Catch's decomposer overload of operator&& triggers a compile-time "
                    "error when used in assertions (via static_assert). Invoking it here would "
                    "prevent the test binary from compiling. This test documents that contract.";
}
