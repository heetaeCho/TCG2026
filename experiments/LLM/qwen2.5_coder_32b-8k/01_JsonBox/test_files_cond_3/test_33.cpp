#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_33 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be done here if needed
    }
    void TearDown() override {
        // Cleanup can be done here if needed
    }
};

TEST_F(ValueTest_33, IsString_ReturnsTrueForStringValue_33) {
    Value value("test_string");
    EXPECT_TRUE(value.isString());
}

TEST_F(ValueTest_33, IsString_ReturnsFalseForNonStringValue_33) {
    Value intValue(123);
    EXPECT_FALSE(intValue.isString());
    Value doubleValue(123.456);
    EXPECT_FALSE(doubleValue.isString());
    Value booleanValue(true);
    EXPECT_FALSE(booleanValue.isString());
    Value nullValue;
    EXPECT_FALSE(nullValue.isString());
    JsonBox::Object object;
    Value objectValue(object);
    EXPECT_FALSE(objectValue.isString());
    JsonBox::Array array;
    Value arrayValue(array);
    EXPECT_FALSE(arrayValue.isString());
}

TEST_F(ValueTest_33, IsString_ReturnsTrueForEmptyStringValue_33) {
    Value emptyStringValue("");
    EXPECT_TRUE(emptyStringValue.isString());
}

TEST_F(ValueTest_33, IsString_BoundaryConditionWithNullPointerCString_33) {
    Value nullCStringValue(static_cast<const char*>(nullptr));
    EXPECT_FALSE(nullCStringValue.isString()); // Assuming nullptr is not a valid string
}