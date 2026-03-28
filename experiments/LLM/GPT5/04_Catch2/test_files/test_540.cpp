// FormatReconstructedExpression_tests_540.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Use the provided StringRef interface
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

// Forward declaration of the function under test (no re-implementation)
namespace Catch {
    void formatReconstructedExpression(
        std::ostream& os,
        std::string const& lhs,
        StringRef op,
        std::string const& rhs
    );
}

using Catch::StringRef;

// --- Tests ---

// Normal operation: short lhs+rhs without newlines -> single-line: "lhs op rhs"
TEST(FormatReconstructedExpressionTest_540, SingleLine_WhenShortAndNoNewlines_540) {
    std::ostringstream os;
    std::string lhs = "a + b";          // len 5
    std::string rhs = "c - d";          // len 5  -> total 10 < 40
    Catch::formatReconstructedExpression(os, lhs, StringRef("=="), rhs);
    EXPECT_EQ(os.str(), "a + b == c - d");
}

// Boundary condition: total length exactly 39 -> still single-line
TEST(FormatReconstructedExpressionTest_540, SingleLine_WhenSumIs39_540) {
    std::ostringstream os;
    // 19 + 20 = 39
    std::string lhs(19, 'x');
    std::string rhs(20, 'y');
    Catch::formatReconstructedExpression(os, lhs, StringRef("!="), rhs);
    EXPECT_EQ(os.str(), std::string(19, 'x') + " != " + std::string(20, 'y'));
}

// Boundary condition: total length exactly 40 -> multiline
TEST(FormatReconstructedExpressionTest_540, MultiLine_WhenSumIs40_540) {
    std::ostringstream os;
    // 20 + 20 = 40
    std::string lhs(20, 'L');
    std::string rhs(20, 'R');
    Catch::formatReconstructedExpression(os, lhs, StringRef("<="), rhs);
    EXPECT_EQ(os.str(), std::string(20, 'L') + "\n<=\n" + std::string(20, 'R'));
}

// Newline in lhs forces multiline regardless of length
TEST(FormatReconstructedExpressionTest_540, MultiLine_WhenLhsContainsNewline_540) {
    std::ostringstream os;
    std::string lhs = "line1\nline2";   // contains '\n', length small
    std::string rhs = "ok";
    Catch::formatReconstructedExpression(os, lhs, StringRef("=="), rhs);
    EXPECT_EQ(os.str(), "line1\nline2\n==\nok");
}

// Newline in rhs forces multiline regardless of length
TEST(FormatReconstructedExpressionTest_540, MultiLine_WhenRhsContainsNewline_540) {
    std::ostringstream os;
    std::string lhs = "ok";
    std::string rhs = "r1\nr2";
    Catch::formatReconstructedExpression(os, lhs, StringRef("!="), rhs);
    EXPECT_EQ(os.str(), "ok\n!=\nr1\nr2");
}

// Edge case: empty lhs and rhs (no newlines, total 0) -> single-line with spaces around op
TEST(FormatReconstructedExpressionTest_540, SingleLine_WhenBothSidesEmpty_540) {
    std::ostringstream os;
    std::string lhs; // ""
    std::string rhs; // ""
    Catch::formatReconstructedExpression(os, lhs, StringRef("=="), rhs);
    EXPECT_EQ(os.str(), " == ");
}
