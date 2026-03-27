#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



TEST_F(ColumnIteratorTest_615, IncrementOperatorAdvancesToNextLine_615) {

    Column column("Line 1\nLine 2\nLine 3");

    auto it = column.begin();

    ++it; // Move to the start of "Line 2"

    EXPECT_EQ(*it, "Line 2");

}



TEST_F(ColumnIteratorTest_615, IncrementOperatorSkipsLeadingWhitespace_615) {

    Column column("Line 1\n   Line 2\nLine 3");

    auto it = column.begin();

    ++it; // Move to the start of "Line 2"

    EXPECT_EQ(*it, "Line 2");

}



TEST_F(ColumnIteratorTest_615, IncrementOperatorHandlesEndOfLines_615) {

    Column column("Line 1\nLine 2\n");

    auto it = column.begin();

    ++it; // Move to the start of "Line 2"

    EXPECT_EQ(*it, "Line 2");

    ++it; // Move to the end

    EXPECT_EQ(it != column.end(), false);

}



TEST_F(ColumnIteratorTest_615, IncrementOperatorHandlesSingleLine_615) {

    Column column("SingleLine");

    auto it = column.begin();

    ++it; // Move to the end

    EXPECT_EQ(it != column.end(), false);

}



TEST_F(ColumnIteratorTest_615, IteratorEqualityComparison_615) {

    Column column("Line 1\nLine 2\nLine 3");

    auto it1 = column.begin();

    auto it2 = column.begin();

    ++it2; // Move to the start of "Line 2"

    EXPECT_EQ(it1 == it2, false);

    EXPECT_EQ(it1 != it2, true);

}



TEST_F(ColumnIteratorTest_615, IteratorEqualityComparisonAtEnd_615) {

    Column column("Line 1\nLine 2");

    auto it1 = column.begin();

    ++it1;

    ++it1; // Move to the end

    auto it2 = column.end(); // Directly at the end

    EXPECT_EQ(it1 == it2, true);

    EXPECT_EQ(it1 != it2, false);

}



TEST_F(ColumnIteratorTest_615, IteratorPostIncrementBehavior_615) {

    Column column("Line 1\nLine 2");

    auto it = column.begin();

    auto oldIt = it++;

    EXPECT_EQ(*oldIt, "Line 1");

    EXPECT_EQ(*it, "Line 2");

}



TEST_F(ColumnIteratorTest_615, IteratorHandlesEmptyString_615) {

    Column column("");

    auto it = column.begin();

    EXPECT_EQ(it != column.end(), false);

}
