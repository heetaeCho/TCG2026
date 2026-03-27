#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsTest : public ::testing::Test {

protected:

    Column column1{"FirstColumn"};

    Column column2{"SecondColumn"};

    Columns columns;

};



TEST_F(ColumnsTest, AddSingleColumn_1094) {

    columns += column1;

    EXPECT_EQ(columns.begin()->operator*(), "FirstColumn");

}



TEST_F(ColumnsTest, AddMultipleColumns_1094) {

    columns += column1;

    columns += column2;

    auto it = columns.begin();

    EXPECT_EQ(*it++, "FirstColumn");

    EXPECT_EQ(*it, "SecondColumn");

}



TEST_F(ColumnsTest, IteratorEquality_1094) {

    Columns::iterator it1(columns);

    Columns::iterator it2(columns);

    EXPECT_TRUE(it1 == it2);



    ++it1;

    EXPECT_FALSE(it1 == it2);

}



TEST_F(ColumnsTest, IteratorInequality_1094) {

    Columns::iterator it1(columns);

    Columns::iterator it2(columns);

    EXPECT_FALSE(it1 != it2);



    ++it1;

    EXPECT_TRUE(it1 != it2);

}



TEST_F(ColumnsTest, IncrementIteratorPre_1094) {

    columns += column1;

    Columns::iterator it(columns);

    auto& incrementedIt = ++it;



    // Since there's only one column, incrementing should reach the end.

    EXPECT_EQ(incrementedIt, Columns::iterator(columns, EndTag{}));

}



TEST_F(ColumnsTest, IncrementIteratorPost_1094) {

    columns += column1;

    Columns::iterator it(columns);

    auto incrementedIt = it++;



    // Post-increment returns the old iterator value.

    EXPECT_EQ(*incrementedIt, "FirstColumn");



    // The original iterator should now be at the end.

    EXPECT_EQ(it, Columns::iterator(columns, EndTag{}));

}



TEST_F(ColumnsTest, DereferenceIterator_1094) {

    columns += column1;

    Columns::iterator it(columns);

    EXPECT_EQ(*it, "FirstColumn");

}
