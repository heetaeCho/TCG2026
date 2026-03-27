#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_108 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects or common variables if needed.

    }

};



TEST_F(ObjectTest_108, GetInt64_NormalOperation_108) {

    long long expectedValue = 123456789012;

    Object obj(expectedValue);

    EXPECT_EQ(obj.getInt64(), expectedValue);

}



TEST_F(ObjectTest_108, GetInt64_BoundaryConditionZero_108) {

    long long expectedValue = 0;

    Object obj(expectedValue);

    EXPECT_EQ(obj.getInt64(), expectedValue);

}



TEST_F(ObjectTest_108, GetInt64_BoundaryConditionMax_108) {

    long long expectedValue = LLONG_MAX;

    Object obj(expectedValue);

    EXPECT_EQ(obj.getInt64(), expectedValue);

}



TEST_F(ObjectTest_108, GetInt64_BoundaryConditionMin_108) {

    long long expectedValue = LLONG_MIN;

    Object obj(expectedValue);

    EXPECT_EQ(obj.getInt64(), expectedValue);

}



TEST_F(ObjectTest_108, GetInt64_TypeMismatch_108) {

    int intValue = 123;

    Object obj(intValue); // Assuming this creates an object of type objInt

    EXPECT_FALSE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), 0); // Expecting default or error value if type mismatch is handled internally

}



TEST_F(ObjectTest_108, GetInt64_TypeMismatchForReal_108) {

    double realValue = 123.45;

    Object obj(realValue); // Assuming this creates an object of type objReal

    EXPECT_FALSE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), 0); // Expecting default or error value if type mismatch is handled internally

}
