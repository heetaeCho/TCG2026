#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsIteratorTest : public ::testing::Test {

protected:

    Columns columns;

};



TEST_F(ColumnsIteratorTest, DereferenceOperatorReturnsCorrectRow_619) {

    Column column1("Column1");

    Column column2("Col2");

    columns = column1 + column2;



    Columns::iterator it(columns);

    EXPECT_EQ(*it, "Column1 Col2");

}



TEST_F(ColumnsIteratorTest, DereferenceOperatorWithDifferentWidths_619) {

    Column column1("Short");

    Column column2("A somewhat longer text");

    column1.width(5);

    column2.width(20);

    columns = column1 + column2;



    Columns::iterator it(columns);

    EXPECT_EQ(*it, "Short A somewhat longer text");

}



TEST_F(ColumnsIteratorTest, DereferenceOperatorWithPadding_619) {

    Column column1("Col");

    Column column2("Text");

    column1.width(10);

    columns = column1 + column2;



    Columns::iterator it(columns);

    EXPECT_EQ(*it, "Col       Text");

}



TEST_F(ColumnsIteratorTest, IteratorIncrementWorks_619) {

    Column column1("Line1\nLine2");

    Column column2("A\nB");

    columns = column1 + column2;



    Columns::iterator it(columns);

    ++it;

    EXPECT_EQ(*it, "Line2 B");

}



TEST_F(ColumnsIteratorTest, IteratorEndCondition_619) {

    Column column1("SingleLine");

    Column column2("OneLine");

    columns = column1 + column2;



    Columns::iterator it(columns);

    ++it;

    EXPECT_TRUE(it == Columns::iterator(columns, Columns::iterator::EndTag{}));

}



TEST_F(ColumnsIteratorTest, MultipleColumnsWithDifferentWidths_619) {

    Column column1("Short");

    Column column2("MediumLength");

    Column column3("VeryLongTextIndeed");

    column1.width(5);

    column2.width(12);

    columns = column1 + column2 + column3;



    Columns::iterator it(columns);

    EXPECT_EQ(*it, "Short MediumLength VeryLongTextIndeed");

}



TEST_F(ColumnsIteratorTest, SingleColumn_619) {

    Column column1("SingleColumn");

    columns = column1;



    Columns::iterator it(columns);

    EXPECT_EQ(*it, "SingleColumn");

}



TEST_F(ColumnsIteratorTest, EmptyColumns_619) {

    columns = Columns();



    Columns::iterator it(columns);

    EXPECT_TRUE(it == Columns::iterator(columns, Columns::iterator::EndTag{}));

}
