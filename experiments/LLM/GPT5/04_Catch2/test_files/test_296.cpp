// File: tests/assertion_result_get_expression_296_tests.cpp

#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

// Helper to build AssertionResult instances without assuming any internal logic.
static Catch::AssertionResult MakeResult_296(const std::string& expr,
                                             Catch::ResultDisposition::Flags flags) {
    Catch::AssertionInfo info;
    info.macroName = Catch::StringRef("REQUIRE");
    info.capturedExpression = Catch::StringRef(expr);
    info.resultDisposition = flags;

    // We do not rely on internals of AssertionResultData; we just pass a default instance.
    return Catch::AssertionResult(info, Catch::AssertionResultData{});
}

// Normal operation: when resultDisposition does NOT indicate a false-test,
// getExpression() should return the captured expression verbatim.
TEST(AssertionResultGetExpression_296, ReturnsRawExpressionWhenNormal_296) {
    auto ar = MakeResult_296("a == b", Catch::ResultDisposition::Normal);
    EXPECT_EQ(ar.getExpression(), "a == b");
}

// Boundary: empty captured expression with normal disposition should yield an empty string.
TEST(AssertionResultGetExpression_296, EmptyExpressionWhenNormal_296) {
    auto ar = MakeResult_296("", Catch::ResultDisposition::Normal);
    EXPECT_EQ(ar.getExpression(), "");
}

// Behavior with FalseTest flag: the expression should be wrapped as `!(<expr>)`.
TEST(AssertionResultGetExpression_296, WrapsWithNotAndParensWhenFalseTest_296) {
    auto ar = MakeResult_296("x > 0", Catch::ResultDisposition::FalseTest);
    EXPECT_EQ(ar.getExpression(), "!(x > 0)");
}

// Boundary with FalseTest: empty captured expression should still be wrapped as `!()`.
TEST(AssertionResultGetExpression_296, EmptyExpressionWithFalseTest_296) {
    auto ar = MakeResult_296("", Catch::ResultDisposition::FalseTest);
    EXPECT_EQ(ar.getExpression(), "!()");
}

// Robustness: special characters and whitespace are preserved exactly (except for the wrapping when FalseTest).
TEST(AssertionResultGetExpression_296, PreservesWhitespaceAndSymbols_296) {
    const std::string complex = "foo(  a[ i ]  ,  bar->baz()  ) && (s == \"q\"){#?}";
    auto ar = MakeResult_296(complex, Catch::ResultDisposition::FalseTest);
    EXPECT_EQ(ar.getExpression(), "!(" + complex + ")");
}

// Idempotence across calls: getExpression() should not change internal state affecting subsequent calls.
TEST(AssertionResultGetExpression_296, MultipleCallsReturnSameResult_296) {
    auto ar = MakeResult_296("x != y", Catch::ResultDisposition::Normal);
    const auto first = ar.getExpression();
    const auto second = ar.getExpression();
    EXPECT_EQ(first, "x != y");
    EXPECT_EQ(second, "x != y");
}

// Macro name should not affect the returned expression (observable via public interface).
TEST(AssertionResultGetExpression_296, MacroNameDoesNotAffectExpression_296) {
    // Build with some macro name first
    Catch::AssertionInfo infoA;
    infoA.macroName = Catch::StringRef("CHECK");
    infoA.capturedExpression = Catch::StringRef("value()");
    infoA.resultDisposition = Catch::ResultDisposition::Normal;
    Catch::AssertionResult arA(infoA, Catch::AssertionResultData{});

    // Build another with a different macro name
    Catch::AssertionInfo infoB = infoA;
    infoB.macroName = Catch::StringRef("REQUIRE");
    Catch::AssertionResult arB(infoB, Catch::AssertionResultData{});

    EXPECT_EQ(arA.getExpression(), "value()");
    EXPECT_EQ(arB.getExpression(), "value()");
    // And they are equal to each other
    EXPECT_EQ(arA.getExpression(), arB.getExpression());
}
