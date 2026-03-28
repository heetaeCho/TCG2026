// File: test_columns_plus_equal_625.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <iterator>

// Include the headers under test
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

class ColumnsPlusEqualTest_625 : public ::testing::Test {};

// Helper: count elements using public iterators
static std::size_t countCols(const Columns& cols) {
    return static_cast<std::size_t>(std::distance(cols.begin(), cols.end()));
}

// Helper: stream a single Column to string using the public operator<<
static std::string renderColumn(const Column& c) {
    std::ostringstream os;
    os << c;
    return os.str();
}

TEST_F(ColumnsPlusEqualTest_625, AddsSingleColumn_625) {
    Columns cols;
    Column c1{"hello"};

    cols += c1;

    EXPECT_EQ(countCols(cols), 1u);

    // Verify that the (only) column, when streamed, contains our text.
    // We do not assert exact formatting to avoid relying on internals.
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    const std::string out = renderColumn(*it);
    EXPECT_NE(out.find("hello"), std::string::npos);
}

TEST_F(ColumnsPlusEqualTest_625, ChainingReturnsLhsReference_625) {
    Columns cols;
    Column c1{"A"};
    Column c2{"B"};

    // Verify that operator+= returns lhs by reference (enables chaining).
    Columns* returned = &( (cols += c1) += c2 );
    EXPECT_EQ(returned, &cols);

    // Verify two elements were appended in order.
    EXPECT_EQ(countCols(cols), 2u);

    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    EXPECT_NE(renderColumn(*it).find("A"), std::string::npos);

    ++it;
    ASSERT_NE(it, cols.end());
    EXPECT_NE(renderColumn(*it).find("B"), std::string::npos);
}

TEST_F(ColumnsPlusEqualTest_625, AppendingEmptyColumnStillIncreasesCount_625) {
    Columns cols;
    Column empty{""};

    cols += empty;

    EXPECT_EQ(countCols(cols), 1u);

    // The rendered output could be empty or contain formatting;
    // we only assert that the element exists and is streamable.
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    (void)renderColumn(*it); // Should be safe to stream without throwing.
}

TEST_F(ColumnsPlusEqualTest_625, MultipleAppendsPreserveAllEntries_625) {
    Columns cols;
    Column c1{"first"};
    Column c2{"second"};
    Column c3{"third"};

    cols += c1;
    cols += c2;
    cols += c3;

    EXPECT_EQ(countCols(cols), 3u);

    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    EXPECT_NE(renderColumn(*it).find("first"), std::string::npos);

    ++it; ASSERT_NE(it, cols.end());
    EXPECT_NE(renderColumn(*it).find("second"), std::string::npos);

    ++it; ASSERT_NE(it, cols.end());
    EXPECT_NE(renderColumn(*it).find("third"), std::string::npos);
}

TEST_F(ColumnsPlusEqualTest_625, HandlesVeryLongTextWithoutAssumingFormatting_625) {
    Columns cols;
    std::string longText(500, 'x'); // 500 'x' characters
    Column longCol{longText};

    cols += longCol;

    EXPECT_EQ(countCols(cols), 1u);

    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    const std::string out = renderColumn(*it);

    // We only verify that some recognizable portion is present.
    EXPECT_NE(out.find(std::string(10, 'x')), std::string::npos);
}
