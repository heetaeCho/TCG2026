#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_47 : public ::testing::Test {

protected:

    Value intValue;

    Value doubleValue;

    Value nullValue;



    void SetUp() override {

        intValue = Value(42);

        doubleValue = Value(3.14);

        nullValue = Value();

    }

};



TEST_F(ValueTest_47, TryGetInteger_IntegerType_47) {

    EXPECT_EQ(intValue.tryGetInteger(0), 42);

}



TEST_F(ValueTest_47, TryGetInteger_DoubleType_47) {

    EXPECT_EQ(doubleValue.tryGetInteger(0), static_cast<int>(3.14));

}



TEST_F(ValueTest_47, TryGetInteger_NullType_DefaultValue_47) {

    EXPECT_EQ(nullValue.tryGetInteger(99), 99);

}



TEST_F(ValueTest_47, TryGetInteger_BoundaryConditionMinInt_47) {

    Value minValue = Value(std::numeric_limits<int>::min());

    EXPECT_EQ(minValue.tryGetInteger(0), std::numeric_limits<int>::min());

}



TEST_F(ValueTest_47, TryGetInteger_BoundaryConditionMaxInt_47) {

    Value maxValue = Value(std::numeric_limits<int>::max());

    EXPECT_EQ(maxValue.tryGetInteger(0), std::numeric_limits<int>::max());

}
