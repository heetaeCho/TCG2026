#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class TextFlowTest_628 : public ::testing::Test {

protected:

    Column column1;

    Column column2;

    Columns columns;



    void SetUp() override {

        column1 = Column("Column1");

        column2 = Column("Column2");

        columns = Columns();

    }

};



TEST_F(TextFlowTest_628, PutIncreasesCount_628) {

    size_t initialSize = columns.begin()->size();

    columns += std::move(column1);

    EXPECT_EQ(columns.begin()->size(), initialSize + 1);

}



TEST_F(TextFlowTest_628, AddColumnsUsingOperatorPlus_628) {

    Columns result = std::move(columns) + std::move(column1) + std::move(column2);

    EXPECT_EQ(result.begin()->size(), 2);

}



TEST_F(TextFlowTest_628, SetAndGetWidth_628) {

    column1.width(40);

    EXPECT_EQ(column1.width(), 40);

}



TEST_F(TextFlowTest_628, SetAndGetIndent_628) {

    column1.indent(5);

    EXPECT_EQ(column1.indent(), 5);

}



TEST_F(TextFlowTest_628, SetAndGetInitialIndent_628) {

    column1.initialIndent(10);

    EXPECT_EQ(column1.initialIndent(), 10);

}



TEST_F(TextFlowTest_628, BoundaryConditionWidthZero_628) {

    column1.width(0);

    EXPECT_EQ(column1.width(), 0);

}



TEST_F(TextFlowTest_628, BoundaryConditionIndentZero_628) {

    column1.indent(0);

    EXPECT_EQ(column1.indent(), 0);

}



TEST_F(TextFlowTest_628, BoundaryConditionInitialIndentNpos_628) {

    column1.initialIndent(std::string::npos);

    EXPECT_EQ(column1.initialIndent(), std::string::npos);

}
