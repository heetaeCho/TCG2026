#include <gtest/gtest.h>

#include <catch2/internal/catch_textflow.hpp>



using namespace Catch::TextFlow;



class ColumnsTest : public ::testing::Test {

protected:

    Columns columns;

};



TEST_F(ColumnsTest_56, BeginAndEndAreConsistent_56) {

    auto beginIt = columns.begin();

    auto endIt = columns.end();

    EXPECT_EQ(beginIt, endIt);

}



TEST_F(ColumnsTest_56, OperatorPlusWithConstColumn_ReturnsNewColumnsObject_56) {

    Column column;

    Columns result = columns + column;

    EXPECT_NE(&result, &columns);

}



TEST_F(ColumnsTest_56, OperatorPlusWithRvalueColumn_ReturnsNewColumnsObject_56) {

    Column column;

    Columns result = std::move(columns) + std::move(column);

    EXPECT_NE(&result, &columns);

}



TEST_F(ColumnsTest_56, OperatorPlusEqualWithConstColumn_ModifiesOriginalColumnsObject_56) {

    Column column;

    auto originalAddress = &columns;

    columns += column;

    EXPECT_EQ(&columns, originalAddress);

}



TEST_F(ColumnsTest_56, OperatorPlusEqualWithRvalueColumn_ModifiesOriginalColumnsObject_56) {

    Column column;

    auto originalAddress = &columns;

    columns += std::move(column);

    EXPECT_EQ(&columns, originalAddress);

}
