#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_23 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ValueTest_23, EqualOperatorForSameStringValues_23) {

    Value v1("test");

    Value v2("test");

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentStringValues_23) {

    Value v1("test");

    Value v2("different");

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForSameIntegerValues_23) {

    Value v1(42);

    Value v2(42);

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentIntegerValues_23) {

    Value v1(42);

    Value v2(99);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForSameDoubleValues_23) {

    Value v1(3.14);

    Value v2(3.14);

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentDoubleValues_23) {

    Value v1(3.14);

    Value v2(2.71);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForSameBooleanValues_23) {

    Value v1(true);

    Value v2(true);

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentBooleanValues_23) {

    Value v1(true);

    Value v2(false);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForSameObjectValues_23) {

    Object obj1 = {{"key", Value("value")}};

    Object obj2 = {{"key", Value("value")}};

    Value v1(obj1);

    Value v2(obj2);

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentObjectValues_23) {

    Object obj1 = {{"key", Value("value")}};

    Object obj2 = {{"key", Value("different")}};

    Value v1(obj1);

    Value v2(obj2);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForSameArrayValues_23) {

    Array arr1 = {Value(1), Value(2)};

    Array arr2 = {Value(1), Value(2)};

    Value v1(arr1);

    Value v2(arr2);

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentArrayValues_23) {

    Array arr1 = {Value(1), Value(2)};

    Array arr2 = {Value(2), Value(1)};

    Value v1(arr1);

    Value v2(arr2);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForDifferentTypes_23) {

    Value v1("test");

    Value v2(42);

    EXPECT_FALSE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForNullValues_23) {

    Value v1;

    Value v2;

    EXPECT_TRUE(v1 == v2);

}



TEST_F(ValueTest_23, EqualOperatorForMixedTypeValues_23) {

    Value v1(42);

    Value v2("42");

    EXPECT_FALSE(v1 == v2);

}
