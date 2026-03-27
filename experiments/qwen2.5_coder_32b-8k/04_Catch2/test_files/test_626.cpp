#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



TEST_F(ColumnsTest_626, AddRvalueColumnIncreasesSize_626) {

    Columns columns;

    Column column("test");

    size_t initial_size = columns.m_columns.size();

    columns += std::move(column);

    EXPECT_EQ(columns.m_columns.size(), initial_size + 1);

}



TEST_F(ColumnsTest_626, AddLvalueColumnIncreasesSize_626) {

    Columns columns;

    Column column("test");

    size_t initial_size = columns.m_columns.size();

    columns += column;

    EXPECT_EQ(columns.m_columns.size(), initial_size + 1);

}



TEST_F(ColumnsTest_626, AddMultipleColumnsIncreasesSizeCorrectly_626) {

    Columns columns;

    Column column1("test1");

    Column column2("test2");

    Column column3("test3");



    size_t initial_size = columns.m_columns.size();

    columns += std::move(column1);

    columns += column2;

    columns += std::move(column3);



    EXPECT_EQ(columns.m_columns.size(), initial_size + 3);

}



TEST_F(ColumnsTest_626, AddEmptyColumnIncreasesSizeByOne_626) {

    Columns columns;

    Column empty_column("");

    size_t initial_size = columns.m_columns.size();

    columns += std::move(empty_column);

    EXPECT_EQ(columns.m_columns.size(), initial_size + 1);

}



TEST_F(ColumnsTest_626, AddColumnWithDefaultWidthDoesNotThrow_626) {

    Columns columns;

    Column column("test");

    EXPECT_NO_THROW(columns += std::move(column));

}



TEST_F(ColumnsTest_626, AddColumnWithCustomWidthDoesNotThrow_626) {

    Columns columns;

    Column column("test").width(40);

    EXPECT_NO_THROW(columns += std::move(column));

}
