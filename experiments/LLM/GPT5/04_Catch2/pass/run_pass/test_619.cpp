// File: columns_iterator_operator_deref_tests_619.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"
#include <string>

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

// Small helper that reads the first "row" that the Columns iterator produces.
// This uses only the public iterator API (& does not assume anything else).
static std::string FirstRow(const Columns& cols) {
    Columns::iterator it(cols);
    return *it;
}

// ---------- Tests ----------

TEST(ColumnsIteratorTest_619, ConcatenatesTwoColumnsWithPadding_619) {
    // Column1 text shorter than width -> spaces between columns should equal (width1 - len1)
    Column c1("A");    c1.width(3);   // len=1, width=3 -> 2 spaces after "A"
    Column c2("BB");   c2.width(4);   // len=2, width=4

    Columns cols = c1 + c2;

    EXPECT_EQ(FirstRow(cols), "A" + std::string(2, ' ') + "BB"); // "A␠␠BB"
}

TEST(ColumnsIteratorTest_619, SkipsLeadingEndedColumnAddsItsWidthAsIndent_619) {
    // First column has no visible rows -> the next column's text should be preceded
    // by full width of the ended column (no left-trim by operator*).
    Column empty("");  empty.width(5);
    Column c2("X");    c2.width(2);

    Columns cols = empty + c2;

    EXPECT_EQ(FirstRow(cols), std::string(5, ' ') + "X");
}

TEST(ColumnsIteratorTest_619, NoTrailingSpacesWhenLastColumnShorterThanWidth_619) {
    // Last column is shorter than its width. operator* should NOT append trailing spaces
    // after the last printed column (padding is only inserted before subsequent columns).
    Column c1("AAA");  c1.width(3);   // len == width -> no inter-column spaces from c1
    Column c2("BB");   c2.width(5);   // len < width, but there is no following column

    Columns cols = c1 + c2;

    EXPECT_EQ(FirstRow(cols), "AAABB"); // No trailing spaces after "BB"
}

TEST(ColumnsIteratorTest_619, NoTrailingSpacesWhenSecondColumnHasNoRows_619) {
    // First column prints text, second column is ended from the start.
    // The combined row should contain only the first column text (no trailing spaces).
    Column c1("A");    c1.width(3);   // len=1, width=3 -> would create padding for next col
    Column empty("");  empty.width(4); // ended column

    Columns cols = c1 + empty;

    EXPECT_EQ(FirstRow(cols), "A"); // No trailing spaces added
}

TEST(ColumnsIteratorTest_619, AllColumnsEndedYieldsEmptyRowString_619) {
    // If all columns are ended from the beginning, dereferencing should yield an empty string.
    Column e1(""); e1.width(3);
    Column e2(""); e2.width(2);

    Columns cols = e1 + e2;

    EXPECT_EQ(FirstRow(cols), "");
}
