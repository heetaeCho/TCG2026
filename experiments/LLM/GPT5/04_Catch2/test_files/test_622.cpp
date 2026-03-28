// File: tests/textflow_columns_ostream_622_tests.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the public TextFlow headers as they are in your project
// Adjust the include path as needed for your repository layout.
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Columns;
using Catch::TextFlow::Column;

class TextFlowColumnsOstreamTest_622 : public ::testing::Test {
protected:
    // Helper: stream Columns to std::string via operator<<
    static std::string ToString(const Columns& cols) {
        std::ostringstream oss;
        oss << cols;
        return oss.str();
    }
};

// [Normal] Empty Columns should print nothing (no newline)
TEST_F(TextFlowColumnsOstreamTest_622, EmptyColumns_ProducesEmptyString_622) {
    Columns cols; // default constructed, no content
    EXPECT_EQ(ToString(cols), "");
}

// [Normal] Single-column, single-line content prints that line with no trailing newline
TEST_F(TextFlowColumnsOstreamTest_622, SingleColumnSingleLine_NoTrailingNewline_622) {
    Columns cols;
    cols += Column("hello");
    EXPECT_EQ(ToString(cols), "hello");
}

// [Boundary] Single-column with explicit newlines: lines are joined with '\n', no extra newline at end
TEST_F(TextFlowColumnsOstreamTest_622, SingleColumnMultipleExplicitLines_JoinedByNewlines_622) {
    Columns cols;
    cols += Column("line1\nline2\nline3");
    EXPECT_EQ(ToString(cols), "line1\nline2\nline3");
}

// [Boundary/Normal] Multiple columns side-by-side should still serialize all produced lines,
// separated by single '\n' between lines, and no leading/trailing newline.
// We do not assert internal spacing/padding between columns—only the line breaks behavior.
TEST_F(TextFlowColumnsOstreamTest_622, MultipleColumns_LinesSeparatedBySingleNewlines_622) {
    Columns cols;
    // Use short, simple contents so we can make a minimal assertion about line breaks only.
    cols += Column("A");
    cols += Column("B");

    const std::string out = ToString(cols);

    // The operator<< guarantees only that consecutive *lines* from the iterator
    // are separated by '\n'. We assert there is no leading or trailing newline,
    // and if there are multiple lines, they are joined by single '\n's.
    // Since we treat TextFlow as a black box, we do not assert the exact line text,
    // only the absence of leading/trailing newlines and no duplicate separators.

    // No leading newline
    ASSERT_FALSE(!out.empty() && out.front() == '\n');
    // No trailing newline
    ASSERT_FALSE(!out.empty() && out.back() == '\n');

    // If there are multiple lines, ensure they are separated by single '\n'.
    // Split and rejoin to check idempotence on line separators.
    size_t count_newlines = std::count(out.begin(), out.end(), '\n');
    if (count_newlines > 0) {
        // Ensure no occurrence of "\n\n" (double separator)
        ASSERT_EQ(out.find("\n\n"), std::string::npos);
    }
}
