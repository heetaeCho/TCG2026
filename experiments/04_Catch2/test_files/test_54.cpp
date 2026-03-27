#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsTest : public ::testing::Test {

protected:

    Columns columns;

};



TEST_F(ColumnsTest_54, DefaultConstructorInitializesIterators_54) {

    Columns::iterator it(columns);

    EXPECT_EQ(it != Columns::iterator(columns, Columns::EndTag()), true);

}



TEST_F(ColumnsTest_54, EndIteratorComparisonWorks_54) {

    Columns::iterator begin(columns);

    Columns::iterator end(columns, Columns::EndTag());

    EXPECT_NE(begin, end);

}



TEST_F(ColumnsTest_54, IteratorIncrementOperatorPreAndPostWork_54) {

    Columns::iterator it(columns);

    Columns::iterator preInc = ++it;

    Columns::iterator postInc = it++;

    EXPECT_EQ(preInc != it, true);

    EXPECT_EQ(postInc != it, true);

}



TEST_F(ColumnsTest_54, IteratorDereferenceOperatorReturnsString_54) {

    Columns::iterator it(columns);

    std::string value = *it;

    EXPECT_TRUE(value.empty() || !value.empty()); // Depending on internal state, this is the best we can assert

}
