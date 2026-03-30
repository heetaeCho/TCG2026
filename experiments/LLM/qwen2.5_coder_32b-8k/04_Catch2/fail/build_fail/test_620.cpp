#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsIteratorTest_620 : public ::testing::Test {

protected:

    Columns columns;

    Columns::iterator it;



    void SetUp() override {

        // Initialize with two columns for testing

        Column col1("Column1 text");

        Column col2("Another column text");

        columns = col1 + col2;

        it = columns.begin();

    }

};



TEST_F(ColumnsIteratorTest_620, InitialDereferenceReturnsFirstRow_620) {

    EXPECT_EQ(*it, "Column1 text\nAnother column text");

}



TEST_F(ColumnsIteratorTest_620, IncrementAdvancesToNextRow_620) {

    ++it;

    EXPECT_EQ(*it, "");

}



TEST_F(ColumnsIteratorTest_620, EndIteratorEquality_620) {

    auto endIt = columns.end();

    while (it != endIt) {

        ++it;

    }

    EXPECT_TRUE(it == endIt);

}



TEST_F(ColumnsIteratorTest_620, InequalityOperatorWorks_620) {

    auto endIt = columns.end();

    EXPECT_TRUE(it != endIt);

    while (it != endIt) {

        ++it;

    }

    EXPECT_FALSE(it != endIt);

}



TEST_F(ColumnsIteratorTest_620, IteratorDoesNotAdvanceWhenNoMoreRows_620) {

    auto endIt = columns.end();

    while (it != endIt) {

        ++it;

    }

    EXPECT_EQ(*it, "");

    ++it;

    EXPECT_EQ(*it, "");

}



TEST_F(ColumnsIteratorTest_620, SingleColumnHandling_620) {

    Column singleCol("Single column text");

    Columns singleColumns = singleCol + Column("");

    auto singleIt = singleColumns.begin();

    EXPECT_EQ(*singleIt, "Single column text\n");

    ++singleIt;

    EXPECT_EQ(*singleIt, "");

}



TEST_F(ColumnsIteratorTest_620, MultipleColumnsHandling_620) {

    Column col1("First");

    Column col2("Second");

    Column col3("Third");

    Columns multiColumns = col1 + col2 + col3;

    auto multiIt = multiColumns.begin();

    EXPECT_EQ(*multiIt, "First\nSecond\nThird");

    ++multiIt;

    EXPECT_EQ(*multiIt, "");

}
