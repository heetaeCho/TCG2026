#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_31 : public ::testing::Test {
protected:
    Value value;
};

TEST_F(ValueTest_31, InitialTypeIsNull_31) {
    EXPECT_EQ(value.getType(), JsonBox::Value::NULL_VALUE);
}

TEST_F(ValueTest_31, OperatorArrayAccessConvertsToEmptyArray_31) {
    value[static_cast<Array::size_type>(0)];
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(value.getArray().size(), 1u);
}

TEST_F(ValueTest_31, OperatorArrayAccessResizesArray_31) {
    value[static_cast<Array::size_type>(5)];
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(value.getArray().size(), 6u);
}

TEST_F(ValueTest_31, OperatorArrayAccessReturnsReferenceToElement_31) {
    Value& element = value[static_cast<Array::size_type>(0)];
    element.setInteger(42);
    EXPECT_EQ(value.getArray()[static_cast<Array::size_type>(0)].getInteger(), 42);
}

TEST_F(ValueTest_31, OperatorArrayAccessDoesNotShrinkArray_31) {
    value[static_cast<Array::size_type>(5)];
    value[static_cast<Array::size_type>(3)];
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(value.getArray().size(), 6u);
}