#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_52 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ValueTest_52, TryGetFloat_DefaultValueForNonNumericType_52) {

    Value value;

    float result = value.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, 42.0f);

}



TEST_F(ValueTest_52, TryGetFloat_IntegerType_52) {

    Value intValue(10);

    float result = intValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, 10.0f);

}



TEST_F(ValueTest_52, TryGetFloat_DoubleType_52) {

    Value doubleValue(3.14);

    float result = doubleValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, 3.14f);

}



TEST_F(ValueTest_52, TryGetFloat_BoundaryConditionIntegerMax_52) {

    Value intValue(std::numeric_limits<int>::max());

    float result = intValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, static_cast<float>(std::numeric_limits<int>::max()));

}



TEST_F(ValueTest_52, TryGetFloat_BoundaryConditionIntegerMin_52) {

    Value intValue(std::numeric_limits<int>::min());

    float result = intValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, static_cast<float>(std::numeric_limits<int>::min()));

}



TEST_F(ValueTest_52, TryGetFloat_BoundaryConditionDoubleMax_52) {

    Value doubleValue(std::numeric_limits<double>::max());

    float result = doubleValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, static_cast<float>(std::numeric_limits<double>::max()));

}



TEST_F(ValueTest_52, TryGetFloat_BoundaryConditionDoubleMin_52) {

    Value doubleValue(std::numeric_limits<double>::min());

    float result = doubleValue.tryGetFloat(42.0f);

    EXPECT_FLOAT_EQ(result, static_cast<float>(std::numeric_limits<double>::min()));

}
