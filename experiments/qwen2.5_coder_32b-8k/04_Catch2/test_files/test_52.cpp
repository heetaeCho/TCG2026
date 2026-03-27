#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnTest_52 : public ::testing::Test {

protected:

    void SetUp() override {

        column = std::make_unique<Column>("Sample text");

    }



    std::unique_ptr<Column> column;

};



TEST_F(ColumnTest_52, DefaultWidthIsSetCorrectly_52) {

    EXPECT_EQ(column->width(), 79u);

}



TEST_F(ColumnTest_52, SetWidthUpdatesWidth_52) {

    column->width(100);

    EXPECT_EQ(column->width(), 100u);

}



TEST_F(ColumnTest_52, DefaultIndentIsZero_52) {

    EXPECT_EQ(column->indent(), 0u);

}



TEST_F(ColumnTest_52, SetIndentUpdatesIndent_52) {

    column->indent(5);

    EXPECT_EQ(column->indent(), 5u);

}



TEST_F(ColumnTest_52, DefaultInitialIndentIsNpos_52) {

    EXPECT_EQ(column->initialIndent(), std::string::npos);

}



TEST_F(ColumnTest_52, SetInitialIndentUpdatesInitialIndent_52) {

    column->initialIndent(10);

    EXPECT_EQ(column->initialIndent(), 10u);

}



TEST_F(ColumnTest_52, EndIteratorIsNotEqualToBeginIterator_52) {

    auto beginIt = column->begin();

    auto endIt = column->end();

    EXPECT_NE(beginIt, endIt);

}



TEST_F(ColumnTest_52, EndIteratorIsConsistent_52) {

    auto endIt1 = column->end();

    auto endIt2 = column->end();

    EXPECT_EQ(endIt1, endIt2);

}
