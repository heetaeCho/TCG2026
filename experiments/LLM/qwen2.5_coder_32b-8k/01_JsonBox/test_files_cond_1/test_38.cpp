#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_38 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup if necessary
    }
    void TearDown() override {
        // Cleanup if necessary
    }
};

TEST_F(ValueTest_38, IsObject_ReturnsTrueForObjectType_38) {
    Value value(JsonBox::Value::Type::OBJECT);
    EXPECT_TRUE(value.isObject());
}

TEST_F(ValueTest_38, IsObject_ReturnsFalseForNonObjectType_38) {
    Value stringValue("test");
    EXPECT_FALSE(stringValue.isObject());
    Value intValue(42);
    EXPECT_FALSE(intValue.isObject());
    Value doubleValue(3.14);
    EXPECT_FALSE(doubleValue.isObject());
    Value booleanValue(true);
    EXPECT_FALSE(booleanValue.isObject());
    Value nullValue;
    EXPECT_FALSE(nullValue.isObject());
}

TEST_F(ValueTest_38, IsObject_BoundaryConditionWithEmptyObject_38) {
    JsonBox::Object emptyObject;
    Value value(emptyObject);
    EXPECT_TRUE(value.isObject());
}

TEST_F(ValueTest_38, IsObject_ExceptionalCase_NoExceptionExpected_38) {
    // Since the constructor and isObject method do not throw exceptions for valid inputs,
    // we just verify that no exception is thrown for a normal case.
    JsonBox::Object obj;
    Value value(obj);
    EXPECT_NO_THROW(value.isObject());
}