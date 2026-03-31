#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::getBoolWithDefaultValue
class ObjectGetBoolWithDefaultValueTest_111 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When Object is a bool with value true, getBoolWithDefaultValue returns true regardless of default
TEST_F(ObjectGetBoolWithDefaultValueTest_111, BoolTrueReturnsTrue_111) {
    Object obj(true);
    ASSERT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// Test: When Object is a bool with value false, getBoolWithDefaultValue returns false regardless of default
TEST_F(ObjectGetBoolWithDefaultValueTest_111, BoolFalseReturnsFalse_111) {
    Object obj(false);
    ASSERT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is not a bool (objNone), returns default value true
TEST_F(ObjectGetBoolWithDefaultValueTest_111, NoneTypeReturnsDefaultTrue_111) {
    Object obj;
    ASSERT_TRUE(obj.isNone());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// Test: When Object is not a bool (objNone), returns default value false
TEST_F(ObjectGetBoolWithDefaultValueTest_111, NoneTypeReturnsDefaultFalse_111) {
    Object obj;
    ASSERT_TRUE(obj.isNone());
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is objNull, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, NullTypeReturnsDefault_111) {
    Object obj = Object::null();
    ASSERT_TRUE(obj.isNull());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is an int, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, IntTypeReturnsDefault_111) {
    Object obj(42);
    ASSERT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is a real, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, RealTypeReturnsDefault_111) {
    Object obj(3.14);
    ASSERT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is an int64, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, Int64TypeReturnsDefault_111) {
    Object obj(static_cast<long long>(123456789LL));
    ASSERT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is a string, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, StringTypeReturnsDefault_111) {
    Object obj(std::string("hello"));
    ASSERT_TRUE(obj.isString());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is a name, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, NameTypeReturnsDefault_111) {
    Object obj(objName, "someName");
    ASSERT_TRUE(obj.isName());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is a cmd, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, CmdTypeReturnsDefault_111) {
    Object obj(objCmd, "someCmd");
    ASSERT_TRUE(obj.isCmd());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is error, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, ErrorTypeReturnsDefault_111) {
    Object obj = Object::error();
    ASSERT_TRUE(obj.isError());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: When Object is EOF, returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, EOFTypeReturnsDefault_111) {
    Object obj = Object::eof();
    ASSERT_TRUE(obj.isEOF());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: Bool true object with default true still returns true
TEST_F(ObjectGetBoolWithDefaultValueTest_111, BoolTrueWithDefaultTrue_111) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// Test: Bool false object with default false still returns false
TEST_F(ObjectGetBoolWithDefaultValueTest_111, BoolFalseWithDefaultFalse_111) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test: Moved-from bool object after move, the moved-to object retains bool value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, MovedObjectRetainsBoolValue_111) {
    Object original(true);
    Object moved(std::move(original));
    ASSERT_TRUE(moved.isBool());
    EXPECT_TRUE(moved.getBoolWithDefaultValue(false));
}

// Test: Object set to null via setToNull returns default value
TEST_F(ObjectGetBoolWithDefaultValueTest_111, SetToNullReturnsDefault_111) {
    Object obj(true);
    ASSERT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
    obj.setToNull();
    ASSERT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}
