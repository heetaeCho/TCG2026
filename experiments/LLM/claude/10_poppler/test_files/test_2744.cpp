#include <gtest/gtest.h>
#include "Object.h"

// Test constructing an Object with an int value
TEST(ObjectTest_2744, ConstructWithInt_2744) {
    Object obj(42);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test that isInt returns true for int objects
TEST(ObjectTest_2744, IsIntReturnsTrue_2744) {
    Object obj(100);
    EXPECT_TRUE(obj.isInt());
}

// Test that other type checks return false for int objects
TEST(ObjectTest_2744, OtherTypeChecksFalseForInt_2744) {
    Object obj(10);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
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

// Test constructing with zero
TEST(ObjectTest_2744, ConstructWithZero_2744) {
    Object obj(0);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test constructing with negative int
TEST(ObjectTest_2744, ConstructWithNegativeInt_2744) {
    Object obj(-999);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -999);
}

// Test constructing with INT_MAX
TEST(ObjectTest_2744, ConstructWithIntMax_2744) {
    Object obj(INT_MAX);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

// Test constructing with INT_MIN
TEST(ObjectTest_2744, ConstructWithIntMin_2744) {
    Object obj(INT_MIN);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

// Test isNum returns true for int objects (int is a number)
TEST(ObjectTest_2744, IsNumReturnsTrueForInt_2744) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

// Test isIntOrInt64 returns true for int objects
TEST(ObjectTest_2744, IsIntOrInt64ReturnsTrueForInt_2744) {
    Object obj(5);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test getNum returns the int value as double
TEST(ObjectTest_2744, GetNumReturnsDoubleForInt_2744) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

// Test getIntOrInt64 returns the int value as long long
TEST(ObjectTest_2744, GetIntOrInt64ReturnsValueForInt_2744) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// Test constructing a bool Object
TEST(ObjectTest_2744, ConstructWithBool_2744) {
    Object obj(true);
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test constructing a bool Object with false
TEST(ObjectTest_2744, ConstructWithBoolFalse_2744) {
    Object obj(false);
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test constructing a real (double) Object
TEST(ObjectTest_2744, ConstructWithDouble_2744) {
    Object obj(3.14);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

// Test constructing a real Object with zero
TEST(ObjectTest_2744, ConstructWithDoubleZero_2744) {
    Object obj(0.0);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

// Test constructing a real Object with negative value
TEST(ObjectTest_2744, ConstructWithNegativeDouble_2744) {
    Object obj(-2.5);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

// Test isNum returns true for real objects
TEST(ObjectTest_2744, IsNumReturnsTrueForReal_2744) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

// Test getNum for real objects
TEST(ObjectTest_2744, GetNumForReal_2744) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

// Test constructing an int64 Object
TEST(ObjectTest_2744, ConstructWithInt64_2744) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test isIntOrInt64 returns true for int64 objects
TEST(ObjectTest_2744, IsIntOrInt64ReturnsTrueForInt64_2744) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test static null factory
TEST(ObjectTest_2744, StaticNullFactory_2744) {
    Object obj = Object::null();
    EXPECT_EQ(obj.getType(), objNull);
    EXPECT_TRUE(obj.isNull());
}

// Test static eof factory
TEST(ObjectTest_2744, StaticEofFactory_2744) {
    Object obj = Object::eof();
    EXPECT_EQ(obj.getType(), objEOF);
    EXPECT_TRUE(obj.isEOF());
}

// Test static error factory
TEST(ObjectTest_2744, StaticErrorFactory_2744) {
    Object obj = Object::error();
    EXPECT_EQ(obj.getType(), objError);
    EXPECT_TRUE(obj.isError());
}

// Test default constructor creates objNone
TEST(ObjectTest_2744, DefaultConstructorCreatesNone_2744) {
    Object obj;
    EXPECT_EQ(obj.getType(), objNone);
    EXPECT_TRUE(obj.isNone());
}

// Test move constructor
TEST(ObjectTest_2744, MoveConstructor_2744) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_EQ(obj2.getType(), objInt);
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test move assignment operator
TEST(ObjectTest_2744, MoveAssignment_2744) {
    Object obj1(42);
    Object obj2(99);
    obj2 = std::move(obj1);
    EXPECT_EQ(obj2.getType(), objInt);
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test setToNull
TEST(ObjectTest_2744, SetToNull_2744) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// Test constructing a name object
TEST(ObjectTest_2744, ConstructNameObject_2744) {
    Object obj(objName, "TestName");
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test isName with matching name
TEST(ObjectTest_2744, IsNameWithMatchingString_2744) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

// Test constructing a cmd object
TEST(ObjectTest_2744, ConstructCmdObject_2744) {
    Object obj(objCmd, "myCmd");
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "myCmd");
}

// Test isCmd with matching command
TEST(ObjectTest_2744, IsCmdWithMatchingString_2744) {
    Object obj(objCmd, "doSomething");
    EXPECT_TRUE(obj.isCmd("doSomething"));
    EXPECT_FALSE(obj.isCmd("doOther"));
}

// Test constructing a string object
TEST(ObjectTest_2744, ConstructStringObject_2744) {
    Object obj(std::string("hello"));
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

// Test copy method preserves type and value
TEST(ObjectTest_2744, CopyPreservesIntValue_2744) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objInt);
    EXPECT_EQ(copied.getInt(), 42);
}

// Test copy of bool
TEST(ObjectTest_2744, CopyPreservesBoolValue_2744) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objBool);
    EXPECT_TRUE(copied.getBool());
}

// Test copy of real
TEST(ObjectTest_2744, CopyPreservesRealValue_2744) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objReal);
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

// Test copy of null
TEST(ObjectTest_2744, CopyPreservesNull_2744) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// Test getTypeName for int
TEST(ObjectTest_2744, GetTypeNameForInt_2744) {
    Object obj(5);
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
}

// Test getTypeName for null
TEST(ObjectTest_2744, GetTypeNameForNull_2744) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
}

// Test getNumWithDefaultValue for int
TEST(ObjectTest_2744, GetNumWithDefaultValueForInt_2744) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 7.0);
}

// Test getNumWithDefaultValue for non-numeric
TEST(ObjectTest_2744, GetNumWithDefaultValueForNonNumeric_2744) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// Test getBoolWithDefaultValue for bool object
TEST(ObjectTest_2744, GetBoolWithDefaultValueForBool_2744) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

// Test getBoolWithDefaultValue for non-bool object
TEST(ObjectTest_2744, GetBoolWithDefaultValueForNonBool_2744) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test constructing name with empty string
TEST(ObjectTest_2744, ConstructNameWithEmptyString_2744) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Test getNameString
TEST(ObjectTest_2744, GetNameString_2744) {
    Object obj(objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// Test deepCopy for int
TEST(ObjectTest_2744, DeepCopyForInt_2744) {
    Object obj(99);
    Object deep = obj.deepCopy();
    EXPECT_EQ(deep.getType(), objInt);
    EXPECT_EQ(deep.getInt(), 99);
}

// Test move constructor leaves source in valid state
TEST(ObjectTest_2744, MoveConstructorLeavesSourceValid_2744) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // After move, obj1 should be in some valid state (likely objNone or objDead)
    // We just verify obj2 is correct
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test constructing int64 with zero
TEST(ObjectTest_2744, ConstructInt64WithZero_2744) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), 0LL);
}

// Test constructing int64 with negative value
TEST(ObjectTest_2744, ConstructInt64WithNegative_2744) {
    long long val = -9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test getNum with ok parameter for int
TEST(ObjectTest_2744, GetNumWithOkForInt_2744) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

// Test getNum with ok parameter for non-numeric
TEST(ObjectTest_2744, GetNumWithOkForNonNumeric_2744) {
    Object obj = Object::null();
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_FALSE(ok);
}

// Test multiple moves
TEST(ObjectTest_2744, MultipleMoves_2744) {
    Object obj1(123);
    Object obj2(std::move(obj1));
    Object obj3(std::move(obj2));
    EXPECT_EQ(obj3.getType(), objInt);
    EXPECT_EQ(obj3.getInt(), 123);
}

// Test constructing hex string object
TEST(ObjectTest_2744, ConstructHexStringObject_2744) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_TRUE(obj.isHexString());
    ASSERT_NE(obj.getHexString(), nullptr);
}
