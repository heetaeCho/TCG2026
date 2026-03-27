#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnTest : public ::testing::Test {

protected:

    Column col1;

    Column col2;



    ColumnTest() 

        : col1("Hello"), col2("World") {}

};



TEST_F(ColumnTest_623, WidthInitializationDefault_623) {

    EXPECT_EQ(col1.width(), 79);

}



TEST_F(ColumnTest_623, IndentInitializationDefault_623) {

    EXPECT_EQ(col1.indent(), 0);

}



TEST_F(ColumnTest_623, InitialIndentInitializationDefault_623) {

    EXPECT_EQ(col1.initialIndent(), std::string::npos);

}



TEST_F(ColumnTest_623, WidthSetAndGet_623) {

    col1.width(50);

    EXPECT_EQ(col1.width(), 50);

}



TEST_F(ColumnTest_623, IndentSetAndGet_623) {

    col1.indent(10);

    EXPECT_EQ(col1.indent(), 10);

}



TEST_F(ColumnTest_623, InitialIndentSetAndGet_623) {

    col1.initialIndent(5);

    EXPECT_EQ(col1.initialIndent(), 5);

}



class ColumnsTest : public ::testing::Test {

protected:

    Column col1;

    Column col2;

    Columns cols;



    ColumnsTest() 

        : col1("Hello"), col2("World") {}

};



TEST_F(ColumnsTest_623, AddColumnUsingOperatorPlus_623) {

    Columns result = col1 + col2;

    EXPECT_EQ(result.begin()->m_string.get(), "Hello");

    EXPECT_EQ((++result.begin())->m_string.get(), "World");

}



TEST_F(ColumnsTest_623, AddColumnUsingOperatorPlusEquals_623) {

    cols += col1;

    cols += col2;

    EXPECT_EQ(cols.begin()->m_string.get(), "Hello");

    EXPECT_EQ((++cols.begin())->m_string.get(), "World");

}



TEST_F(ColumnsTest_623, BoundaryConditionEmptyColumn_623) {

    Column emptyCol("");

    Columns result = col1 + emptyCol;

    EXPECT_EQ(result.begin()->m_string.get(), "Hello");

    EXPECT_EQ((++result.begin())->m_string.get(), "");

}



TEST_F(ColumnsTest_623, BoundaryConditionSingleColumn_623) {

    Columns singleCol = col1;

    EXPECT_EQ(singleCol.begin()->m_string.get(), "Hello");

}
