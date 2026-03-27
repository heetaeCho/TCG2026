#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueComparisonTest_28 : public ::testing::Test {

protected:

    Value intVal1;

    Value intVal2;

    Value doubleVal1;

    Value doubleVal2;

    Value stringVal1;

    Value stringVal2;

    Value boolVal1;

    Value boolVal2;

    Value nullVal1;

    Value nullVal2;



    void SetUp() override {

        intVal1 = 5;

        intVal2 = 10;

        doubleVal1 = 3.14;

        doubleVal2 = 6.28;

        stringVal1 = "hello";

        stringVal2 = "world";

        boolVal1 = true;

        boolVal2 = false;

        nullVal1;

        nullVal2;

    }

};



TEST_F(ValueComparisonTest_28, IntegersEqual_28) {

    EXPECT_TRUE(intVal1 >= intVal1);

}



TEST_F(ValueComparisonTest_28, IntegersNotEqual_28) {

    EXPECT_FALSE(intVal1 >= intVal2);

}



TEST_F(ValueComparisonTest_28, IntegersGreaterOrEqual_28) {

    EXPECT_TRUE(intVal2 >= intVal1);

}



TEST_F(ValueComparisonTest_28, DoublesEqual_28) {

    Value doubleVal3 = 3.14;

    EXPECT_TRUE(doubleVal1 >= doubleVal3);

}



TEST_F(ValueComparisonTest_28, DoublesNotEqual_28) {

    EXPECT_FALSE(doubleVal1 >= doubleVal2);

}



TEST_F(ValueComparisonTest_28, DoublesGreaterOrEqual_28) {

    EXPECT_TRUE(doubleVal2 >= doubleVal1);

}



TEST_F(ValueComparisonTest_28, StringsEqual_28) {

    Value stringVal3 = "hello";

    EXPECT_TRUE(stringVal1 >= stringVal3);

}



TEST_F(ValueComparisonTest_28, StringsNotEqual_28) {

    EXPECT_FALSE(stringVal1 >= stringVal2);

}



TEST_F(ValueComparisonTest_28, StringsGreaterOrEqual_28) {

    EXPECT_TRUE(stringVal2 >= stringVal1);

}



TEST_F(ValueComparisonTest_28, BooleansEqual_28) {

    Value boolVal3 = true;

    EXPECT_TRUE(boolVal1 >= boolVal3);

}



TEST_F(ValueComparisonTest_28, BooleansNotEqual_28) {

    EXPECT_FALSE(boolVal1 >= boolVal2);

}



TEST_F(ValueComparisonTest_28, BooleansGreaterOrEqual_28) {

    EXPECT_TRUE(boolVal2 >= boolVal1);

}



TEST_F(ValueComparisonTest_28, NullsEqual_28) {

    EXPECT_TRUE(nullVal1 >= nullVal2);

}
