// File: tests/assertion_result_hasExpression_294_tests.cpp

#include <gtest/gtest.h>

#include "Catch2/src/catch2/catch_assertion_result.hpp"
#include "Catch2/src/catch2/catch_assertion_info.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::AssertionResult;
using Catch::AssertionInfo;
using Catch::StringRef;

// These tests treat AssertionResult as a black box and only verify the
// observable behavior of hasExpression() based on the public field
// `m_info.capturedExpression` (which is part of the public interface).

// Normal operation: default-constructed capturedExpression is empty => hasExpression() == false
TEST(AssertionResultTest_294, HasExpression_ReturnsFalse_WhenCapturedExpressionIsEmptyByDefault_294) {
    AssertionResult ar;  // uses the class as given
    EXPECT_FALSE(ar.hasExpression());
}

// Normal operation: non-empty expression via C-string => hasExpression() == true
TEST(AssertionResultTest_294, HasExpression_ReturnsTrue_WhenCapturedExpressionIsNonEmptyCString_294) {
    AssertionResult ar;
    ar.m_info.capturedExpression = StringRef("x + y > 0");
    const auto& ar_const = ar; // verify const-correct usage too
    EXPECT_TRUE(ar_const.hasExpression());
}

// Boundary: explicitly set to empty string literal => hasExpression() == false
TEST(AssertionResultTest_294, HasExpression_ReturnsFalse_WhenCapturedExpressionIsEmptyCString_294) {
    AssertionResult ar;
    ar.m_info.capturedExpression = StringRef("");
    EXPECT_FALSE(ar.hasExpression());
}

// Boundary: length-based constructor with size 0 (non-null pointer) => hasExpression() == false
TEST(AssertionResultTest_294, HasExpression_ReturnsFalse_WhenCapturedExpressionHasZeroLength_294) {
    AssertionResult ar;
    ar.m_info.capturedExpression = StringRef("ignored", 0); // explicitly zero-sized view
    EXPECT_FALSE(ar.hasExpression());
}

// Edge but valid via interface: whitespace-only expression is still non-empty => hasExpression() == true
TEST(AssertionResultTest_294, HasExpression_ReturnsTrue_WhenCapturedExpressionIsWhitespaceOnly_294) {
    AssertionResult ar;
    ar.m_info.capturedExpression = StringRef("   "); // non-empty, even if whitespace
    EXPECT_TRUE(ar.hasExpression());
}

// Normal operation: using std::string source (non-empty) => hasExpression() == true
TEST(AssertionResultTest_294, HasExpression_ReturnsTrue_WhenCapturedExpressionFromStdString_294) {
    AssertionResult ar;
    std::string expr = std::string("a && b");
    ar.m_info.capturedExpression = StringRef(expr);
    EXPECT_TRUE(ar.hasExpression());
}
