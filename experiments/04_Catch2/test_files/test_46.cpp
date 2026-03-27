#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnTest_46 : public ::testing::Test {

protected:

    Column column;

};



TEST_F(ColumnTest_46, IteratorConstructor_DefaultInitialization_46) {

    // Test the default constructor of const_iterator

    Column::const_iterator it(column);

    EXPECT_TRUE(it != column.cend());

}



TEST_F(ColumnTest_46, IteratorEquality_SameInstance_46) {

    // Test equality operator when iterators are the same instance

    Column::const_iterator it1(column);

    Column::const_iterator it2 = it1;

    EXPECT_TRUE(it1 == it2);

}



TEST_F(ColumnTest_46, IteratorInequality_DifferentInstances_46) {

    // Test inequality operator with different instances

    Column::const_iterator it1(column);

    Column::const_iterator it2(column);

    EXPECT_FALSE(it1 != it2);

}



// Since we don't have any observable behavior for the increment operators or dereference,

// we can only test that they compile and do not cause runtime errors.

TEST_F(ColumnTest_46, IteratorIncrementPrefix_ValidUsage_46) {

    // Test prefix increment operator

    Column::const_iterator it(column);

    ++it;

}



TEST_F(ColumnTest_46, IteratorIncrementPostfix_ValidUsage_46) {

    // Test postfix increment operator

    Column::const_iterator it(column);

    it++;

}
