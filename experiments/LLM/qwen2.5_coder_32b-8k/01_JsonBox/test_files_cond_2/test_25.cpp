#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueComparisonTest_25 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if necessary

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



TEST_F(ValueComparisonTest_25, CompareDifferentTypes_25) {

    Value intValue(42);

    Value stringValue("hello");

    EXPECT_FALSE(intValue < stringValue);

    EXPECT_TRUE(stringValue < intValue);

}



TEST_F(ValueComparisonTest_25, CompareSameStringValues_25) {

    Value str1("hello");

    Value str2("hello");

    EXPECT_FALSE(str1 < str2);

}



TEST_F(ValueComparisonTest_25, CompareDifferentStringValues_25) {

    Value str1("apple");

    Value str2("banana");

    EXPECT_TRUE(str1 < str2);

    EXPECT_FALSE(str2 < str1);

}



TEST_F(ValueComparisonTest_25, CompareSameIntegerValues_25) {

    Value int1(42);

    Value int2(42);

    EXPECT_FALSE(int1 < int2);

}



TEST_F(ValueComparisonTest_25, CompareDifferentIntegerValues_25) {

    Value int1(42);

    Value int2(84);

    EXPECT_TRUE(int1 < int2);

    EXPECT_FALSE(int2 < int1);

}



TEST_F(ValueComparisonTest_25, CompareSameDoubleValues_25) {

    Value double1(3.14);

    Value double2(3.14);

    EXPECT_FALSE(double1 < double2);

}



TEST_F(ValueComparisonTest_25, CompareDifferentDoubleValues_25) {

    Value double1(3.14);

    Value double2(6.28);

    EXPECT_TRUE(double1 < double2);

    EXPECT_FALSE(double2 < double1);

}



TEST_F(ValueComparisonTest_25, CompareSameBooleanValues_25) {

    Value bool1(true);

    Value bool2(true);

    EXPECT_FALSE(bool1 < bool2);

}



TEST_F(ValueComparisonTest_25, CompareDifferentBooleanValues_25) {

    Value bool1(false);

    Value bool2(true);

    EXPECT_TRUE(bool1 < bool2);

    EXPECT_FALSE(bool2 < bool1);

}



TEST_F(ValueComparisonTest_25, CompareNullValues_25) {

    Value null1;

    Value null2;

    EXPECT_FALSE(null1 < null2);

}



TEST_F(ValueComparisonTest_25, CompareObjectValues_25) {

    Object obj1 = {{"key", Value("value")}};

    Object obj2 = {{"key", Value("another_value")}};

    Value object1(obj1);

    Value object2(obj2);

    EXPECT_TRUE(object1 < object2);

    EXPECT_FALSE(object2 < object1);

}



TEST_F(ValueComparisonTest_25, CompareArrayValues_25) {

    Array arr1 = {Value(1), Value(2)};

    Array arr2 = {Value(3), Value(4)};

    Value array1(arr1);

    Value array2(arr2);

    EXPECT_TRUE(array1 < array2);

    EXPECT_FALSE(array2 < array1);

}
