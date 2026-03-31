#include <gtest/gtest.h>
#include "Object.h"

// Test constructing Object with double (real) value
TEST(ObjectRealTest_2745, ConstructWithPositiveDouble_2745) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST(ObjectRealTest_2745, ConstructWithZeroDouble_2745) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST(ObjectRealTest_2745, ConstructWithNegativeDouble_2745) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST(ObjectRealTest_2745, ConstructWithVeryLargeDouble_2745) {
    Object obj(1.0e308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e308);
}

TEST(ObjectRealTest_2745, ConstructWithVerySmallDouble_2745) {
    Object obj(1.0e-308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e-308);
}

TEST(ObjectRealTest_2745, IsNotOtherTypes_2745) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isHexString());
}

TEST(ObjectRealTest_2745, IsNumReturnsTrue_2745) {
    Object obj(42.0);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectRealTest_2745, GetNumReturnsRealValue_2745) {
    Object obj(99.99);
    EXPECT_DOUBLE_EQ(obj.getNum(), 99.99);
}

TEST(ObjectRealTest_2745, GetNumWithOkParam_2745) {
    Object obj(7.77);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 7.77);
}

TEST(ObjectRealTest_2745, GetNumWithDefaultValue_2745) {
    Object obj(5.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(10.0), 5.5);
}

TEST(ObjectRealTest_2745, GetTypeName_2745) {
    Object obj(1.0);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test move constructor
TEST(ObjectRealTest_2745, MoveConstructor_2745) {
    Object obj1(3.14);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

// Test move assignment
TEST(ObjectRealTest_2745, MoveAssignment_2745) {
    Object obj1(2.72);
    Object obj2(1.0);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 2.72);
}

// Test copy() method
TEST(ObjectRealTest_2745, CopyMethod_2745) {
    Object obj(6.28);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 6.28);
}

// Test deepCopy() method
TEST(ObjectRealTest_2745, DeepCopyMethod_2745) {
    Object obj(9.81);
    Object deepCopied = obj.deepCopy();
    EXPECT_TRUE(deepCopied.isReal());
    EXPECT_DOUBLE_EQ(deepCopied.getReal(), 9.81);
}

// Test setToNull
TEST(ObjectRealTest_2745, SetToNull_2745) {
    Object obj(1.23);
    EXPECT_TRUE(obj.isReal());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isReal());
}

// Test default constructor
TEST(ObjectDefaultTest_2745, DefaultConstructor_2745) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// Test bool constructor
TEST(ObjectBoolTest_2745, ConstructWithTrue_2745) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
}

TEST(ObjectBoolTest_2745, ConstructWithFalse_2745) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), false);
}

TEST(ObjectBoolTest_2745, GetBoolWithDefaultValue_2745) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

// Test int constructor
TEST(ObjectIntTest_2745, ConstructWithInt_2745) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectIntTest_2745, ConstructWithZero_2745) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST(ObjectIntTest_2745, ConstructWithNegativeInt_2745) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST(ObjectIntTest_2745, GetNumFromInt_2745) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNum(), 10.0);
}

TEST(ObjectIntTest_2745, GetIntOrInt64FromInt_2745) {
    Object obj(55);
    EXPECT_EQ(obj.getIntOrInt64(), 55LL);
}

// Test int64 constructor
TEST(ObjectInt64Test_2745, ConstructWithInt64_2745) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectInt64Test_2745, GetIntOrInt64FromInt64_2745) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test static factory methods
TEST(ObjectStaticTest_2745, NullFactory_2745) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST(ObjectStaticTest_2745, EofFactory_2745) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST(ObjectStaticTest_2745, ErrorFactory_2745) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// Test string constructor
TEST(ObjectStringTest_2745, ConstructWithString_2745) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// Test name constructor
TEST(ObjectNameTest_2745, ConstructWithName_2745) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST(ObjectNameTest_2745, IsNameWithMatchingString_2745) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

// Test cmd constructor
TEST(ObjectCmdTest_2745, ConstructWithCmd_2745) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST(ObjectCmdTest_2745, IsCmdWithMatchingString_2745) {
    Object obj(objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// Test getNumWithDefaultValue for non-numeric types
TEST(ObjectNonNumericTest_2745, GetNumWithDefaultValueNonNum_2745) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

TEST(ObjectNonNumericTest_2745, GetBoolWithDefaultValueNonBool_2745) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test hex string constructor
TEST(ObjectHexStringTest_2745, ConstructWithHexString_2745) {
    Object obj(objHexString, "48656C6C6F");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_NE(obj.getHexString(), nullptr);
}

// Test that real is not int or int64
TEST(ObjectRealTest_2745, RealIsNotIntOrInt64_2745) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test negative zero
TEST(ObjectRealTest_2745, NegativeZero_2745) {
    Object obj(-0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -0.0);
}
