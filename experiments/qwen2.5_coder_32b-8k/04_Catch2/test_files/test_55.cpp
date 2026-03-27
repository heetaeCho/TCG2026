#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/internal/catch_textflow.hpp"

#include <vector>

#include <iostream>



using namespace Catch::TextFlow;



TEST_F(ColumnsTest_55, DefaultConstructorInitializesEmptyColumns_55) {

    Columns cols;

    EXPECT_EQ(cols.begin(), cols.end());

}



TEST_F(ColumnsTest_55, OperatorPlusCombinesColumns_55) {

    Columns cols1, cols2;

    Column col1, col2;

    cols1 += col1;

    cols2 += col2;



    Columns combined = cols1 + cols2;

    EXPECT_NE(combined.begin(), combined.end());

}



TEST_F(ColumnsTest_55, OperatorPlusMoveCombinesColumns_55) {

    Columns cols1, cols2;

    Column col1, col2;

    cols1 += std::move(col1);

    cols2 += std::move(col2);



    Columns combined = std::move(cols1) + std::move(cols2);

    EXPECT_NE(combined.begin(), combined.end());

}



TEST_F(ColumnsTest_55, OperatorPlusEqualsCombinesColumns_55) {

    Columns cols;

    Column col1, col2;



    cols += col1;

    cols += col2;



    EXPECT_NE(cols.begin(), cols.end());

}



TEST_F(ColumnsTest_55, OperatorPlusEqualsMoveCombinesColumns_55) {

    Columns cols;

    Column col1, col2;



    cols += std::move(col1);

    cols += std::move(col2);



    EXPECT_NE(cols.begin(), cols.end());

}



TEST_F(ColumnsTest_55, OutputStreamOperatorWorks_55) {

    Columns cols;

    Column col;

    cols += col;



    std::ostringstream oss;

    oss << cols;

    EXPECT_FALSE(oss.str().empty());

}
