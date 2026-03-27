#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsTest_624 : public ::testing::Test {

protected:

    Column col1;

    Column col2;

    Columns cols;



    ColumnsTest_624() 

        : col1("Column 1"),

          col2("Column 2") {}

};



TEST_F(ColumnsTest_624, ConstructorInitializesEmptyColumns_624) {

    EXPECT_EQ(cols.begin(), cols.end());

}



TEST_F(ColumnsTest_624, AddSingleColumnUsingOperatorPlus_624) {

    Columns result = cols + col1;

    EXPECT_EQ(result.size(), 1);

}



TEST_F(ColumnsTest_624, AddMultipleColumnsUsingOperatorPlus_624) {

    Columns result = (cols + col1) + col2;

    EXPECT_EQ(result.size(), 2);

}



TEST_F(ColumnsTest_624, AddSingleColumnUsingMoveOperatorPlus_624) {

    Columns result = cols + std::move(Column("Moved Column"));

    EXPECT_EQ(result.size(), 1);

}



TEST_F(ColumnsTest_624, AddMultipleColumnsUsingMoveOperatorPlus_624) {

    Columns result = (cols + std::move(Column("Moved Column 1"))) + std::move(Column("Moved Column 2"));

    EXPECT_EQ(result.size(), 2);

}



TEST_F(ColumnsTest_624, AddSingleColumnUsingOperatorPlusEqual_624) {

    cols += col1;

    EXPECT_EQ(cols.size(), 1);

}



TEST_F(ColumnsTest_624, AddMultipleColumnsUsingOperatorPlusEqual_624) {

    cols += col1;

    cols += col2;

    EXPECT_EQ(cols.size(), 2);

}



TEST_F(ColumnsTest_624, AddSingleColumnUsingMoveOperatorPlusEqual_624) {

    cols += std::move(Column("Moved Column"));

    EXPECT_EQ(cols.size(), 1);

}



TEST_F(ColumnsTest_624, AddMultipleColumnsUsingMoveOperatorPlusEqual_624) {

    cols += std::move(Column("Moved Column 1"));

    cols += std::move(Column("Moved Column 2"));

    EXPECT_EQ(cols.size(), 2);

}
