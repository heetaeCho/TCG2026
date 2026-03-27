#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



// Test fixture for Column tests

class ColumnTest_627 : public ::testing::Test {

protected:

    Column column;

};



// Test fixture for Columns tests

class ColumnsTest_627 : public ::testing::Test {

protected:

    Columns columns;

    Column column1{"Hello"};

    Column column2{"World"};

};



// Column Tests



TEST_F(ColumnTest_627, DefaultConstructorWidth_627) {

    EXPECT_EQ(column.width(), 79);

}



TEST_F(ColumnTest_627, DefaultConstructorIndent_627) {

    EXPECT_EQ(column.indent(), 0);

}



TEST_F(ColumnTest_627, WidthSetterAndGetters_627) {

    column.width(50);

    EXPECT_EQ(column.width(), 50);

}



TEST_F(ColumnTest_627, IndentSetterAndGetters_627) {

    column.indent(10);

    EXPECT_EQ(column.indent(), 10);

}



TEST_F(ColumnTest_627, InitialIndentSetterAndGetters_627) {

    column.initialIndent(5);

    EXPECT_EQ(column.width(), 79); // Width should not change

    // Note: We cannot directly check initialIndent as it's not exposed in the public interface.

}



// Columns Tests



TEST_F(ColumnsTest_627, PlusOperatorWithColumnConstRef_627) {

    Columns combined = columns + column1;

    EXPECT_EQ(std::distance(combined.begin(), combined.end()), 1);

}



TEST_F(ColumnsTest_627, PlusOperatorWithColumnRvalueRef_627) {

    Columns combined = columns + Column{"Hello"};

    EXPECT_EQ(std::distance(combined.begin(), combined.end()), 1);

}



TEST_F(ColumnsTest_627, PlusEqualOperatorWithColumnConstRef_627) {

    columns += column1;

    EXPECT_EQ(std::distance(columns.begin(), columns.end()), 1);

}



TEST_F(ColumnsTest_627, PlusEqualOperatorWithColumnRvalueRef_627) {

    columns += Column{"Hello"};

    EXPECT_EQ(std::distance(columns.begin(), columns.end()), 1);

}



TEST_F(ColumnsTest_627, MultipleColumnsAddition_627) {

    Columns combined = column1 + column2;

    EXPECT_EQ(std::distance(combined.begin(), combined.end()), 2);

}



TEST_F(ColumnsTest_627, AdditionBoundaryConditionEmptyColumn_627) {

    Column emptyColumn{""};

    Columns combined = columns + emptyColumn;

    EXPECT_EQ(std::distance(combined.begin(), combined.end()), 1);

}



// Exceptional/Error Cases (if any observable through the interface)

// In this case, there are no observable exceptional cases based on provided interface.
