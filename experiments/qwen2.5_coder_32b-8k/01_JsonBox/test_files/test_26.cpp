#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueComparisonTest_26 : public ::testing::Test {

protected:

    Value intVal1;

    Value intVal2;

    Value doubleVal1;

    Value doubleVal2;

    Value stringVal1;

    Value stringVal2;

    Value boolTrue;

    Value boolFalse;



    void SetUp() override {

        intVal1.setInteger(5);

        intVal2.setInteger(10);

        doubleVal1.setDouble(3.14);

        doubleVal2.setDouble(6.28);

        stringVal1.setString("apple");

        stringVal2.setString("banana");

        boolTrue.setBoolean(true);

        boolFalse.setBoolean(false);

    }

};



TEST_F(ValueComparisonTest_26, IntegerLessThanEqual_26) {

    EXPECT_TRUE(intVal1 <= intVal2);

    EXPECT_TRUE(intVal1 <= intVal1);

    EXPECT_FALSE(intVal2 <= intVal1);

}



TEST_F(ValueComparisonTest_26, DoubleLessThanEqual_26) {

    EXPECT_TRUE(doubleVal1 <= doubleVal2);

    EXPECT_TRUE(doubleVal1 <= doubleVal1);

    EXPECT_FALSE(doubleVal2 <= doubleVal1);

}



TEST_F(ValueComparisonTest_26, StringLessThanEqual_26) {

    EXPECT_TRUE(stringVal1 <= stringVal2);

    EXPECT_TRUE(stringVal1 <= stringVal1);

    EXPECT_FALSE(stringVal2 <= stringVal1);

}



TEST_F(ValueComparisonTest_26, BooleanLessThanEqual_26) {

    EXPECT_TRUE(boolFalse <= boolTrue);

    EXPECT_TRUE(boolFalse <= boolFalse);

    EXPECT_TRUE(boolTrue <= boolTrue);

    EXPECT_FALSE(boolTrue <= boolFalse);

}



TEST_F(ValueComparisonTest_26, MixedTypeComparison_26) {

    EXPECT_FALSE(intVal1 <= doubleVal1); // Assuming integer and double comparisons are not allowed or always false

    EXPECT_FALSE(stringVal1 <= intVal1); // Assuming string and integer comparisons are not allowed or always false

}



TEST_F(ValueComparisonTest_26, SelfComparison_26) {

    Value selfCompare;

    selfCompare.setInteger(42);

    EXPECT_TRUE(selfCompare <= selfCompare);

}
