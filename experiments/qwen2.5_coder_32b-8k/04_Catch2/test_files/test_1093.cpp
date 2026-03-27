#include <gtest/gtest.h>

#include <catch2/internal/catch_textflow.hpp>



using namespace Catch::TextFlow;



class ColumnTest_1093 : public ::testing::Test {

protected:

    Column column;

    

    void SetUp() override {

        column = Column("Sample text for testing.");

    }

};



TEST_F(ColumnTest_1093, DefaultWidthIs79_1093) {

    EXPECT_EQ(column.width(), 79);

}



TEST_F(ColumnTest_1093, SetAndGetWidth_1093) {

    column.width(50);

    EXPECT_EQ(column.width(), 50);

}



TEST_F(ColumnTest_1093, DefaultIndentIsZero_1093) {

    EXPECT_EQ(column.indent(), 0);

}



TEST_F(ColumnTest_1093, SetAndGetIndent_1093) {

    column.indent(4);

    EXPECT_EQ(column.indent(), 4);

}



TEST_F(ColumnTest_1093, DefaultInitialIndentIsNPos_1093) {

    EXPECT_EQ(column.initialIndent(), std::string::npos);

}



TEST_F(ColumnTest_1093, SetAndGetInitialIndent_1093) {

    column.initialIndent(5);

    EXPECT_EQ(column.initialIndent(), 5);

}



TEST_F(ColumnTest_1093, IteratorBeginAndEndEqualForEmptyString_1093) {

    Column emptyColumn("");

    EXPECT_EQ(emptyColumn.begin(), emptyColumn.end());

}



TEST_F(ColumnTest_1093, IteratorBeginNotEqualToEndForNonEmptyString_1093) {

    EXPECT_NE(column.begin(), column.end());

}



TEST_F(ColumnTest_1093, IteratorIncrementWorks_1093) {

    auto it = column.begin();

    ++it;

    EXPECT_NE(it, column.begin());

}



TEST_F(ColumnTest_1093, IteratorDecrementWorks_1093) {

    auto it = column.end();

    --it;

    EXPECT_NE(it, column.end());

}



TEST_F(ColumnTest_1093, IteratorEqualityOperatorWorks_1093) {

    auto it1 = column.begin();

    auto it2 = column.begin();

    EXPECT_TRUE(it1 == it2);

    

    ++it1;

    EXPECT_FALSE(it1 == it2);

}



TEST_F(ColumnTest_1093, IteratorInequalityOperatorWorks_1093) {

    auto it1 = column.begin();

    auto it2 = column.begin();

    EXPECT_FALSE(it1 != it2);

    

    ++it1;

    EXPECT_TRUE(it1 != it2);

}



TEST_F(ColumnDereferenceIteratorReturnsString_1093) {

    auto it = column.begin();

    EXPECT_EQ(*it, "Sample text for testing.");

}
