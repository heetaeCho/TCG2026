#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnTest_48 : public ::testing::Test {

protected:

    Column column;

};



TEST_F(ColumnTest_48, IndentSetsNewIndentValue_48) {

    size_t newIndent = 5;

    Column& result = column.indent(newIndent);

    EXPECT_EQ(&result, &column); // Verify method chaining

}



TEST_F(ColumnTest_48, WidthSetsNewWidthValue_48) {

    size_t newWidth = 120;

    Column& result = column.width(newWidth);

    EXPECT_EQ(&result, &column); // Verify method chaining

}



TEST_F(ColumnTest_48, InitialIndentSetsNewInitialIndentValue_48) {

    size_t newInitialIndent = 3;

    Column& result = column.initialIndent(newInitialIndent);

    EXPECT_EQ(&result, &column); // Verify method chaining

}



TEST_F(ColumnTest_48, WidthReturnsSetWidth_48) {

    size_t expectedWidth = 100;

    column.width(expectedWidth);

    EXPECT_EQ(column.width(), expectedWidth);

}



TEST_F(ColumnTest_48, IndentSetsZeroIndent_48) {

    Column& result = column.indent(0);

    EXPECT_EQ(&result, &column); // Verify method chaining

}



TEST_F(ColumnTest_48, WidthSetsMinimumWidth_48) {

    size_t minExpectedWidth = 1;

    column.width(minExpectedWidth);

    EXPECT_EQ(column.width(), minExpectedWidth);

}



TEST_F(ColumnTest_48, InitialIndentSetsLargeValue_48) {

    size_t largeInitialIndent = std::string::npos;

    Column& result = column.initialIndent(largeInitialIndent);

    EXPECT_EQ(&result, &column); // Verify method chaining

}
