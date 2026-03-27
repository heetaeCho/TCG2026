#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_50 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ValueTest_50, TryGetDouble_DoubleType_ReturnsDoubleValue_50) {

    Value value(42.5);

    EXPECT_EQ(value.tryGetDouble(0.0), 42.5);

}



TEST_F(ValueTest_50, TryGetDouble_IntegerType_CastsToDouble_50) {

    Value value(42);

    EXPECT_EQ(value.tryGetDouble(0.0), 42.0);

}



TEST_F(ValueTest_50, TryGetDouble_DefaultValueForNonNumericTypes_ReturnsDefaultValue_50) {

    Value stringValue("not a number");

    EXPECT_EQ(stringValue.tryGetDouble(99.99), 99.99);



    Value objectValue(Object{{"key", Value{}}});

    EXPECT_EQ(objectValue.tryGetDouble(99.99), 99.99);



    Value arrayValue(Array{Value{}});

    EXPECT_EQ(arrayValue.tryGetDouble(99.99), 99.99);



    Value booleanValue(true);

    EXPECT_EQ(booleanValue.tryGetDouble(99.99), 99.99);



    Value nullValue;

    EXPECT_EQ(nullValue.tryGetDouble(99.99), 99.99);

}



TEST_F(ValueTest_50, TryGetDouble_BoundaryCondition_NegativeDouble_50) {

    Value value(-1234567890.12345);

    EXPECT_EQ(value.tryGetDouble(0.0), -1234567890.12345);

}



TEST_F(ValueTest_50, TryGetDouble_BoundaryCondition_Zero_50) {

    Value value(0.0);

    EXPECT_EQ(value.tryGetDouble(99.99), 0.0);

}
