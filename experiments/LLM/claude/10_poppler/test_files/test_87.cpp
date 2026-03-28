#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_87 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_87, DefaultConstructor_IsNone_87) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_87, BoolConstructor_True_87) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_87, BoolConstructor_False_87) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_87, IntConstructor_87) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_87, IntConstructor_Negative_87) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_87, IntConstructor_Zero_87) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_87, RealConstructor_87) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_87, RealConstructor_Zero_87) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_87, RealConstructor_Negative_87) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_87, Int64Constructor_87) {
    long long val = 9223372036854775807LL; // max int64
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_87, Int64Constructor_Negative_87) {
    long long val = -9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_87, Int64Constructor_Zero_87) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

// ==================== isInt64 Tests (Focus of the partial code) ====================

TEST_F(ObjectTest_87, IsInt64_ReturnsTrueForInt64Object_87) {
    Object obj(static_cast<long long>(12345));
    EXPECT_TRUE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForIntObject_87) {
    Object obj(42);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForRealObject_87) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForBoolObject_87) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForNullObject_87) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForNoneObject_87) {
    Object obj;
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForErrorObject_87) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForEOFObject_87) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isInt64());
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_87, NullObject_87) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_87, EofObject_87) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_87, ErrorObject_87) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Exclusivity ====================

TEST_F(ObjectTest_87, IntIsNotOtherTypes_87) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
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
}

TEST_F(ObjectTest_87, Int64IsNotOtherTypes_87) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isInt64());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
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
}

// ==================== isNum Tests ====================

TEST_F(ObjectTest_87, IsNum_TrueForInt_87) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_87, IsNum_TrueForReal_87) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_87, IsNum_FalseForBool_87) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// ==================== isIntOrInt64 Tests ====================

TEST_F(ObjectTest_87, IsIntOrInt64_TrueForInt_87) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_87, IsIntOrInt64_TrueForInt64_87) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_87, IsIntOrInt64_FalseForReal_87) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_87, IsIntOrInt64_FalseForBool_87) {
    Object obj(true);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_87, GetNum_FromInt_87) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_87, GetNum_FromReal_87) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_87, GetIntOrInt64_FromInt_87) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_87, GetIntOrInt64_FromInt64_87) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_87, GetNumWithDefaultValue_FromInt_87) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_87, GetNumWithDefaultValue_FromReal_87) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_87, GetNumWithDefaultValue_NonNumReturnsDefault_87) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_87, GetNumWithDefaultValue_NullReturnsDefault_87) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(5.0), 5.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_87, GetBoolWithDefaultValue_FromBoolTrue_87) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_87, GetBoolWithDefaultValue_FromBoolFalse_87) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_87, GetBoolWithDefaultValue_NonBoolReturnsDefault_87) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_87, MoveConstructor_Int_87) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_87, MoveConstructor_Int64_87) {
    Object obj1(static_cast<long long>(12345));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), 12345LL);
}

TEST_F(ObjectTest_87, MoveAssignment_Int_87) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_87, MoveAssignment_Int64_87) {
    Object obj1(static_cast<long long>(99999));
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), 99999LL);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_87, SetToNull_FromInt_87) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_87, SetToNull_FromInt64_87) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isInt64());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt64());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_87, Copy_IntObject_87) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_87, Copy_Int64Object_87) {
    Object obj(static_cast<long long>(123456789));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), 123456789LL);
}

TEST_F(ObjectTest_87, Copy_BoolObject_87) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_87, Copy_RealObject_87) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_87, Copy_NullObject_87) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// ==================== String Constructor Tests ====================

TEST_F(ObjectTest_87, StringConstructor_StdString_87) {
    Object obj(objName, std::string("TestName"));
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_87, CmdConstructor_87) {
    Object obj(objCmd, std::string("TestCmd"));
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

TEST_F(ObjectTest_87, IsName_WithMatchingName_87) {
    Object obj(objName, std::string("Foo"));
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_87, IsCmd_WithMatchingCmd_87) {
    Object obj(objCmd, std::string("DoSomething"));
    EXPECT_TRUE(obj.isCmd("DoSomething"));
    EXPECT_FALSE(obj.isCmd("DoOther"));
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_87, GetTypeName_Int_87) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_87, GetTypeName_Int64_87) {
    Object obj(static_cast<long long>(42));
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_87, GetTypeName_Null_87) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== Boundary: Large Int64 Values ====================

TEST_F(ObjectTest_87, Int64_MaxValue_87) {
    long long maxVal = 9223372036854775807LL;
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_87, Int64_MinValue_87) {
    long long minVal = -9223372036854775807LL - 1;
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// ==================== Boundary: Int edge values ====================

TEST_F(ObjectTest_87, Int_MaxValue_87) {
    Object obj(2147483647);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 2147483647);
}

TEST_F(ObjectTest_87, Int_MinValue_87) {
    Object obj(-2147483647 - 1);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -2147483647 - 1);
}
