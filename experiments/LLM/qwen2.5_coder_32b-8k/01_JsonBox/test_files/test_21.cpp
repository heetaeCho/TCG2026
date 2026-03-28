#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_21 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_21, AssignArray_NormalOperation_21) {

    Array array = {Value(1), Value("test"), Value(true)};

    value = array;

    EXPECT_TRUE(value.isArray());

    EXPECT_EQ(array, value.getArray());

}



TEST_F(ValueTest_21, AssignEmptyArray_21) {

    Array emptyArray;

    value = emptyArray;

    EXPECT_TRUE(value.isArray());

    EXPECT_TRUE(value.getArray().empty());

}



TEST_F(ValueTest_21, AssignArray_BoundaryCondition_21) {

    Array largeArray(1000, Value(42));

    value = largeArray;

    EXPECT_TRUE(value.isArray());

    EXPECT_EQ(largeArray.size(), value.getArray().size());

    for (const auto& item : value.getArray()) {

        EXPECT_TRUE(item.isInteger());

        EXPECT_EQ(42, item.getInteger());

    }

}



TEST_F(ValueTest_21, AssignAfterOtherAssignments_21) {

    value = 42;

    Array array = {Value("hello"), Value(false)};

    value = array;

    EXPECT_TRUE(value.isArray());

    EXPECT_EQ(array, value.getArray());

}
