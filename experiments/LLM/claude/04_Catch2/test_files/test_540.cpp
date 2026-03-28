#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the necessary headers
#include "catch2/internal/catch_stringref.hpp"

// Declare the function under test
namespace Catch {
    void formatReconstructedExpression(std::ostream& os, std::string const& lhs, StringRef op, std::string const& rhs);
}

class FormatReconstructedExpressionTest_540 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Short lhs and rhs without newlines should be on a single line
TEST_F(FormatReconstructedExpressionTest_540, ShortExpressionsOnSingleLine_540) {
    std::string lhs = "1";
    std::string rhs = "2";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    EXPECT_EQ(os.str(), "1 == 2");
}

// Test: Combined length exactly 39 (under 40) should be on single line
TEST_F(FormatReconstructedExpressionTest_540, CombinedLengthJustUnder40SingleLine_540) {
    std::string lhs(19, 'a');  // 19 chars
    std::string rhs(20, 'b');  // 20 chars, total = 39 < 40
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + " == " + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Combined length exactly 40 should be on multiple lines
TEST_F(FormatReconstructedExpressionTest_540, CombinedLengthExactly40MultiLine_540) {
    std::string lhs(20, 'a');  // 20 chars
    std::string rhs(20, 'b');  // 20 chars, total = 40 >= 40
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Combined length greater than 40 should be on multiple lines
TEST_F(FormatReconstructedExpressionTest_540, CombinedLengthOver40MultiLine_540) {
    std::string lhs(30, 'x');
    std::string rhs(30, 'y');
    Catch::StringRef op("!=");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n!=\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Newline in lhs forces multi-line even if short
TEST_F(FormatReconstructedExpressionTest_540, NewlineInLhsForcesMultiLine_540) {
    std::string lhs = "a\nb";
    std::string rhs = "c";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Newline in rhs forces multi-line even if short
TEST_F(FormatReconstructedExpressionTest_540, NewlineInRhsForcesMultiLine_540) {
    std::string lhs = "a";
    std::string rhs = "c\nd";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Newlines in both lhs and rhs forces multi-line
TEST_F(FormatReconstructedExpressionTest_540, NewlineInBothForcesMultiLine_540) {
    std::string lhs = "a\nb";
    std::string rhs = "c\nd";
    Catch::StringRef op(">=");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n>=\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Empty lhs and rhs (both empty, combined size 0 < 40)
TEST_F(FormatReconstructedExpressionTest_540, EmptyLhsAndRhsSingleLine_540) {
    std::string lhs;
    std::string rhs;
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    EXPECT_EQ(os.str(), " == ");
}

// Test: Empty lhs with non-empty rhs
TEST_F(FormatReconstructedExpressionTest_540, EmptyLhsNonEmptyRhs_540) {
    std::string lhs;
    std::string rhs = "42";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    EXPECT_EQ(os.str(), " == 42");
}

// Test: Non-empty lhs with empty rhs
TEST_F(FormatReconstructedExpressionTest_540, NonEmptyLhsEmptyRhs_540) {
    std::string lhs = "42";
    std::string rhs;
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    EXPECT_EQ(os.str(), "42 ==");
}

// Test: Different operators
TEST_F(FormatReconstructedExpressionTest_540, DifferentOperators_540) {
    std::string lhs = "5";
    std::string rhs = "3";

    {
        std::ostringstream oss;
        Catch::formatReconstructedExpression(oss, lhs, Catch::StringRef("<"), rhs);
        EXPECT_EQ(oss.str(), "5 < 3");
    }
    {
        std::ostringstream oss;
        Catch::formatReconstructedExpression(oss, lhs, Catch::StringRef("<="), rhs);
        EXPECT_EQ(oss.str(), "5 <= 3");
    }
    {
        std::ostringstream oss;
        Catch::formatReconstructedExpression(oss, lhs, Catch::StringRef(">"), rhs);
        EXPECT_EQ(oss.str(), "5 > 3");
    }
    {
        std::ostringstream oss;
        Catch::formatReconstructedExpression(oss, lhs, Catch::StringRef(">="), rhs);
        EXPECT_EQ(oss.str(), "5 >= 3");
    }
    {
        std::ostringstream oss;
        Catch::formatReconstructedExpression(oss, lhs, Catch::StringRef("!="), rhs);
        EXPECT_EQ(oss.str(), "5 != 3");
    }
}

// Test: Boundary - combined length exactly 39 (maximum for single line)
TEST_F(FormatReconstructedExpressionTest_540, BoundaryCombinedLength39_540) {
    std::string lhs(39, 'z');  // 39 chars
    std::string rhs;           // 0 chars, total = 39 < 40
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + " == ";
    EXPECT_EQ(os.str(), expected);
}

// Test: Long expressions with newlines - both conditions trigger multi-line
TEST_F(FormatReconstructedExpressionTest_540, LongWithNewlines_540) {
    std::string lhs(50, 'a');
    lhs[25] = '\n';
    std::string rhs(50, 'b');
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Lhs has newline at the very start
TEST_F(FormatReconstructedExpressionTest_540, NewlineAtStartOfLhs_540) {
    std::string lhs = "\nabc";
    std::string rhs = "def";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Rhs has newline at the very end
TEST_F(FormatReconstructedExpressionTest_540, NewlineAtEndOfRhs_540) {
    std::string lhs = "abc";
    std::string rhs = "def\n";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}

// Test: Strings with special characters but no newline, short enough
TEST_F(FormatReconstructedExpressionTest_540, SpecialCharsNoNewline_540) {
    std::string lhs = "\"hello\"";
    std::string rhs = "\"world\"";
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    EXPECT_EQ(os.str(), "\"hello\" == \"world\"");
}

// Test: lhs size is 0, rhs size is 40 -> total = 40, should be multi-line
TEST_F(FormatReconstructedExpressionTest_540, EmptyLhsRhs40CharsMultiLine_540) {
    std::string lhs;
    std::string rhs(40, 'r');
    Catch::StringRef op("==");

    Catch::formatReconstructedExpression(os, lhs, op, rhs);

    std::string expected = lhs + "\n==\n" + rhs;
    EXPECT_EQ(os.str(), expected);
}
