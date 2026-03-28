#include <gtest/gtest.h>
#include "Object.h"

// Test creating an Object with a long long (int64) value
TEST(ObjectInt64Test_2750, ConstructorSetsTypeToInt64_2750) {
    Object obj(static_cast<long long>(42));
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST(ObjectInt64Test_2750, ConstructorSetsInt64Value_2750) {
    Object obj(static_cast<long long>(42));
    EXPECT_EQ(obj.getInt64(), 42);
}

TEST(ObjectInt64Test_2750, IsInt64ReturnsTrue_2750) {
    Object obj(static_cast<long long>(100));
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectInt64Test_2750, IsIntReturnsFalseForInt64_2750) {
    Object obj(static_cast<long long>(100));
    EXPECT_FALSE(obj.isInt());
}

TEST(ObjectInt64Test_2750, IsIntOrInt64ReturnsTrueForInt64_2750) {
    Object obj(static_cast<long long>(100));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectInt64Test_2750, NegativeInt64Value_2750) {
    Object obj(static_cast<long long>(-999999999999LL));
    EXPECT_EQ(obj.getInt64(), -999999999999LL);
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectInt64Test_2750, ZeroInt64Value_2750) {
    Object obj(static_cast<long long>(0));
    EXPECT_EQ(obj.getInt64(), 0);
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectInt64Test_2750, MaxInt64Value_2750) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_EQ(obj.getInt64(), maxVal);
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectInt64Test_2750, MinInt64Value_2750) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_EQ(obj.getInt64(), minVal);
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectInt64Test_2750, GetIntOrInt64ReturnsCorrectValue_2750) {
    Object obj(static_cast<long long>(123456789012LL));
    EXPECT_EQ(obj.getIntOrInt64(), 123456789012LL);
}

TEST(ObjectInt64Test_2750, IsNotBool_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isBool());
}

TEST(ObjectInt64Test_2750, IsNotReal_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isReal());
}

TEST(ObjectInt64Test_2750, IsNum_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectInt64Test_2750, IsNotString_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isString());
}

TEST(ObjectInt64Test_2750, IsNotNull_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isNull());
}

TEST(ObjectInt64Test_2750, IsNotArray_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isArray());
}

TEST(ObjectInt64Test_2750, IsNotDict_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isDict());
}

TEST(ObjectInt64Test_2750, IsNotStream_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isStream());
}

TEST(ObjectInt64Test_2750, IsNotRef_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isRef());
}

TEST(ObjectInt64Test_2750, IsNotCmd_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isCmd());
}

TEST(ObjectInt64Test_2750, IsNotError_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isError());
}

TEST(ObjectInt64Test_2750, IsNotEOF_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isEOF());
}

TEST(ObjectInt64Test_2750, IsNotNone_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isNone());
}

TEST(ObjectInt64Test_2750, IsNotName_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isName());
}

TEST(ObjectInt64Test_2750, IsNotHexString_2750) {
    Object obj(static_cast<long long>(1));
    EXPECT_FALSE(obj.isHexString());
}

TEST(ObjectInt64Test_2750, GetNumReturnsDoubleValue_2750) {
    Object obj(static_cast<long long>(42));
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST(ObjectInt64Test_2750, GetTypeName_2750) {
    Object obj(static_cast<long long>(42));
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test move constructor
TEST(ObjectInt64Test_2750, MoveConstructor_2750) {
    Object obj1(static_cast<long long>(12345LL));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), 12345LL);
}

// Test move assignment operator
TEST(ObjectInt64Test_2750, MoveAssignment_2750) {
    Object obj1(static_cast<long long>(67890LL));
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), 67890LL);
}

// Test setToNull
TEST(ObjectInt64Test_2750, SetToNull_2750) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isInt64());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt64());
}

// Test copy
TEST(ObjectInt64Test_2750, CopyCreatesIdenticalObject_2750) {
    Object obj(static_cast<long long>(999LL));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), 999LL);
}

// Test deep copy
TEST(ObjectInt64Test_2750, DeepCopyCreatesIdenticalObject_2750) {
    Object obj(static_cast<long long>(888LL));
    Object deepCopied = obj.deepCopy();
    EXPECT_TRUE(deepCopied.isInt64());
    EXPECT_EQ(deepCopied.getInt64(), 888LL);
}

// Test static factory methods for comparison
TEST(ObjectStaticFactoryTest_2750, NullObject_2750) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt64());
}

TEST(ObjectStaticFactoryTest_2750, EofObject_2750) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isInt64());
}

TEST(ObjectStaticFactoryTest_2750, ErrorObject_2750) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isInt64());
}

// Test default constructor
TEST(ObjectDefaultTest_2750, DefaultConstructorIsNone_2750) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
}

// Test bool constructor
TEST(ObjectBoolTest_2750, BoolTrueConstructor_2750) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

TEST(ObjectBoolTest_2750, BoolFalseConstructor_2750) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test int constructor
TEST(ObjectIntTest_2750, IntConstructor_2750) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectIntTest_2750, IntGetNum_2750) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST(ObjectIntTest_2750, IntIsNum_2750) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

// Test double constructor
TEST(ObjectRealTest_2750, RealConstructor_2750) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectRealTest_2750, RealGetNum_2750) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

// Test getNumWithDefaultValue
TEST(ObjectInt64Test_2750, GetNumWithDefaultValueReturnsNum_2750) {
    Object obj(static_cast<long long>(42));
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST(ObjectStaticFactoryTest_2750, GetNumWithDefaultValueReturnsDefault_2750) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// Test getBoolWithDefaultValue
TEST(ObjectBoolTest_2750, GetBoolWithDefaultValueReturnsBool_2750) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST(ObjectStaticFactoryTest_2750, GetBoolWithDefaultValueReturnsDefault_2750) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// Test large positive and negative int64
TEST(ObjectInt64Test_2750, LargePositiveValue_2750) {
    Object obj(static_cast<long long>(9999999999999999LL));
    EXPECT_EQ(obj.getInt64(), 9999999999999999LL);
}

TEST(ObjectInt64Test_2750, LargeNegativeValue_2750) {
    Object obj(static_cast<long long>(-9999999999999999LL));
    EXPECT_EQ(obj.getInt64(), -9999999999999999LL);
}

// Test that int and int64 are distinct types
TEST(ObjectDistinctTypes_2750, IntAndInt64AreDifferentTypes_2750) {
    Object intObj(42);
    Object int64Obj(static_cast<long long>(42));
    EXPECT_EQ(intObj.getType(), objInt);
    EXPECT_EQ(int64Obj.getType(), objInt64);
    EXPECT_NE(intObj.getType(), int64Obj.getType());
}

// Test getIntOrInt64 for int type
TEST(ObjectIntTest_2750, GetIntOrInt64ForInt_2750) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}
