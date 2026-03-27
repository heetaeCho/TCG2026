// tests/column_const_iterator_operator_deref_614.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnIteratorTest_614 : public ::testing::Test {};

// [614] Empty input: dereferencing begin() should yield an empty string.
TEST_F(ColumnIteratorTest_614, EmptyString_DerefReturnsEmpty_614) {
    Column col{std::string{}};

    auto it = col.begin();
    // If the implementation yields no lines for empty input, begin==end.
    // If it yields a single empty line, begin!=end and operator* returns "".
    if (it != col.end()) {
        std::string first = *it;
        EXPECT_TRUE(first.empty());
        ++it;
    }
    EXPECT_EQ(it, col.end());
}

// [614] Short string (well under any width): first line equals original text,
// and a single increment reaches end().
TEST_F(ColumnIteratorTest_614, ShortString_NoWrap_614) {
    const std::string input = "hello world";
    Column col{input};

    auto it = col.begin();
    ASSERT_NE(it, col.end()) << "Expected at least one line for non-empty input";

    const std::string first = *it;
    // Observable behavior: for a short string, the first produced line
    // should contain the text (no assumptions about trailing spaces/formatting).
    // We check that the produced line contains the input as a substring.
    // This avoids depending on internal padding/indent decisions.
    EXPECT_NE(first.find(input), std::string::npos);

    ++it;
    EXPECT_EQ(it, col.end()) << "Short input should finish after one produced line";
}

// [614] Exactly console width (boundary): first line length should be <= width,
// and a single increment should reach end().
TEST_F(ColumnIteratorTest_614, ExactlyWidth_NoWrapSingleLine_614) {
    // The header indicates CATCH_CONFIG_CONSOLE_WIDTH 80; we avoid assuming
    // internal padding and merely ensure the first produced line is non-empty
    // and not longer than a typical console width boundary.
    const size_t width = 80;
    const std::string input(width, 'x');
    Column col{input};

    auto it = col.begin();
    ASSERT_NE(it, col.end());

    const std::string first = *it;
    EXPECT_FALSE(first.empty());
    // The produced line should not exceed a typical console width boundary.
    EXPECT_LE(first.size(), width);

    ++it;
    EXPECT_EQ(it, col.end());
}

// [614] Long string (wrap/continuation behavior is opaque): iterating should
// eventually reach end(), and produce multiple lines. The first line should
// be non-empty and reasonably bounded in length.
TEST_F(ColumnIteratorTest_614, LongString_IteratesMultipleLines_614) {
    const size_t width = 80; // From header; used only for len <= boundary check.
    // Construct a long input to exercise multiple dereferences/advances.
    const std::string input(200, 'a');
    Column col{input};

    auto it = col.begin();
    ASSERT_NE(it, col.end()) << "Expected at least one produced line";

    const std::string first = *it;
    EXPECT_FALSE(first.empty());
    EXPECT_LE(first.size(), width);

    // Walk the iterator until end(), counting lines.
    size_t lineCount = 0;
    for (; it != col.end(); ++it) {
        const std::string line = *it;
        EXPECT_FALSE(line.empty()) << "Each produced line should be dereferenceable";
        ++lineCount;

        // Safety bound to avoid infinite loops due to a broken iterator.
        ASSERT_LT(lineCount, 100u) << "Iterator should make progress toward end()";
    }

    // For sufficiently long input, we expect more than one produced line.
    EXPECT_GE(lineCount, 2u);
}
