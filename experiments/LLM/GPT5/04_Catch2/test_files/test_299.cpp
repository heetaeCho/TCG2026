// File: tests/assertion_result_get_expanded_expression_299.cpp
#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"

using namespace Catch;

namespace {

// A tiny helper to build a minimal, valid AssertionResult through the public API.
static AssertionResult makeResultForTest() {
    // We treat the implementation as a black box and only use public interfaces.
    // Construct minimal dependencies using their public constructors.
    // The exact values are irrelevant for getExpandedExpression behavior.
    LazyExpression lazy{}; // assume default constructible in the provided interface
    AssertionResultData data(ResultWas::Ok, lazy);

    AssertionInfo info{}; // assume default constructible in the provided interface

    return AssertionResult(info, std::move(data));
}

} // namespace

// [299] When reconstructed expression is non-empty, it should be returned as-is.
TEST(AssertionResult_GetExpandedExpression_299, ReturnsReconstructedWhenNonEmpty_299) {
    auto ar = makeResultForTest();

    // Arrange: set a non-empty reconstructed expression via public member
    const std::string kExpanded = "a == b  (expanded)";
    ar.m_resultData.reconstructedExpression = kExpanded;

    // Act
    const std::string got = ar.getExpandedExpression();

    // Assert
    EXPECT_EQ(got, kExpanded);
}

// [299] When reconstructed expression is empty, it should fall back to getExpression().
TEST(AssertionResult_GetExpandedExpression_299, FallsBackToGetExpressionWhenEmpty_299) {
    auto ar = makeResultForTest();

    // Arrange: capture current "plain" expression through the public API
    const std::string baselineExpression = ar.getExpression();

    // Ensure reconstructed expression is empty so the fallback path is exercised
    ar.m_resultData.reconstructedExpression.clear();

    // Act
    const std::string got = ar.getExpandedExpression();

    // Assert: must match the plain expression returned by the object
    EXPECT_EQ(got, baselineExpression);
}

// [299] Whitespace-only reconstructed expression is NOT empty (std::string::empty() == false),
// so it should be returned verbatim and not fall back.
TEST(AssertionResult_GetExpandedExpression_299, WhitespaceOnlyIsConsideredNonEmpty_299) {
    auto ar = makeResultForTest();

    const std::string kSpaces = "   \t";
    ar.m_resultData.reconstructedExpression = kSpaces;

    const std::string got = ar.getExpandedExpression();

    EXPECT_EQ(got, kSpaces);
}

// [299] Multi-line reconstructed expression should be returned intact (no trimming or changes).
TEST(AssertionResult_GetExpandedExpression_299, MultilineReconstructedIsPreserved_299) {
    auto ar = makeResultForTest();

    const std::string kMultiline =
        "x == y\n"
        "x=3, y=4\n"
        "[extra context]";
    ar.m_resultData.reconstructedExpression = kMultiline;

    const std::string got = ar.getExpandedExpression();

    EXPECT_EQ(got, kMultiline);
}
