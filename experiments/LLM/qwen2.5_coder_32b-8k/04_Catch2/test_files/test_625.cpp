#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsTest_625 : public ::testing::Test {

protected:

    Column column1;

    Column column2;

    Columns columns;



    ColumnsTest_625() 

        : column1("Column1"), column2("Column2") {}

};



TEST_F(ColumnsTest_625, AddSingleColumn_625) {

    columns += column1;

    EXPECT_EQ(columns.begin()->m_string.m_str, "Column1");

}



TEST_F(ColumnsTest_625, AddMultipleColumns_625) {

    columns += column1;

    columns += column2;

    auto it = columns.begin();

    EXPECT_EQ(it->m_string.m_str, "Column1");

    ++it;

    EXPECT_EQ(it->m_string.m_str, "Column2");

}



TEST_F(ColumnsTest_625, AddEmptyColumn_625) {

    Column emptyColumn("");

    columns += emptyColumn;

    EXPECT_EQ(columns.begin()->m_string.m_str, "");

}



TEST_F(ColumnsTest_625, ConcatenateColumnsUsingOperatorPlus_625) {

    Columns newColumns = columns + column1 + column2;

    auto it = newColumns.begin();

    EXPECT_EQ(it->m_string.m_str, "Column1");

    ++it;

    EXPECT_EQ(it->m_string.m_str, "Column2");

}



TEST_F(ColumnsTest_625, ConcatenateMoveSemantics_625) {

    Columns newColumns = std::move(columns) + Column("MovedColumn");

    auto it = newColumns.begin();

    EXPECT_EQ(it->m_string.m_str, "MovedColumn");

}
