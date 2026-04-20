#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_40 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTest_40, IsBoolean_ReturnsTrueForBooleanType_40) {
    Value booleanValue(true);
    EXPECT_TRUE(booleanValue.isBoolean());
}

TEST_F(ValueTest_40, IsBoolean_ReturnsFalseForNonBooleanTypes_40) {
    Value stringValue("test");
    Value intValue(123);
    Value doubleValue(123.45);
    JsonBox::Object object;
    Value objectValue(object);
    JsonBox::Array array;
    Value arrayValue(array);
    Value nullValue;
    EXPECT_FALSE(stringValue.isBoolean());
    EXPECT_FALSE(intValue.isBoolean());
    EXPECT_FALSE(doubleValue.isBoolean());
    EXPECT_FALSE(objectValue.isBoolean());
    EXPECT_FALSE(arrayValue.isBoolean());
    EXPECT_FALSE(nullValue.isBoolean());
}

TEST_F(ValueTest_40, IsBoolean_BoundaryConditionWithFalse_40) {
    Value booleanValue(false);
    EXPECT_TRUE(booleanValue.isBoolean());
}