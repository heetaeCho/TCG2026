#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnTest_51 : public ::testing::Test {

protected:

    std::string testString = "Sample text for testing";

    Column column;

    

    ColumnTest_51() : column(testString) {}

};



TEST_F(ColumnTest_51, DefaultWidthIs79_51) {

    EXPECT_EQ(column.width(), 79);

}



TEST_F(ColumnTest_51, SetWidth_51) {

    column.width(100);

    EXPECT_EQ(column.width(), 100);

}



TEST_F(ColumnTest_51, DefaultIndentIsZero_51) {

    EXPECT_EQ(column.indent(), 0);

}



TEST_F(ColumnTest_51, SetIndent_51) {

    column.indent(5);

    EXPECT_EQ(column.indent(), 5);

}



TEST_F(ColumnTest_51, DefaultInitialIndentIsNpos_51) {

    EXPECT_EQ(column.initialIndent(), std::string::npos);

}



TEST_F(ColumnTest_51, SetInitialIndent_51) {

    column.initialIndent(10);

    EXPECT_EQ(column.initialIndent(), 10);

}



TEST_F(ColumnTest_51, BeginEndIterator_51) {

    auto it = column.begin();

    auto endIt = column.end();

    EXPECT_NE(it, endIt);

}



TEST_F(ColumnTest_51, OperatorPlusConstColumns_51) {

    Column anotherColumn("Another text");

    Columns columns = column + anotherColumn;

    EXPECT_EQ(columns.size(), 2);

}



TEST_F(ColumnTest_51, OperatorPlusRvalueColumns_51) {

    Columns columns = std::move(column) + Column("Moved text");

    EXPECT_EQ(columns.size(), 2);

}
