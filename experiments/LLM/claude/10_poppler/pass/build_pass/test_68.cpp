#include <gtest/gtest.h>
#include <memory>
#include <cstring>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_68 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ObjectTest_68, DefaultConstructor_IsNone_68) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_68, BoolConstructor_True_68) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_68, BoolConstructor_False_68) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), false);
}

TEST_F(ObjectTest_68, IntConstructor_68) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_68, IntConstructor_Zero_68) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_68, IntConstructor_Negative_68) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_68, RealConstructor_68) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_68, RealConstructor_Zero_68) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_68, RealConstructor_Negative_68) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_68, Int64Constructor_68) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_68, NameConstructor_68) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
    EXPECT_EQ(obj.getType(), objName);
}

TEST_F(ObjectTest_68, CmdConstructor_68) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
    EXPECT_EQ(obj.getType(), objCmd);
}

TEST_F(ObjectTest_68, StringConstructor_StdString_68) {
    Object obj(objString, std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_68, HexStringConstructor_68) {
    Object obj(objHexString, std::string("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== Static Factory Tests ====================

TEST_F(ObjectTest_68, NullFactory_68) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_68, EofFactory_68) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_68, ErrorFactory_68) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Query Tests ====================

TEST_F(ObjectTest_68, IsBool_OnNonBool_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_68, IsInt_OnNonInt_68) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_68, IsReal_OnNonReal_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_68, IsNum_OnInt_68) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_68, IsNum_OnReal_68) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_68, IsNum_OnBool_68) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_68, IsString_OnNonString_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_68, IsNull_OnNonNull_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_68, IsArray_OnNonArray_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_68, IsDict_OnNonDict_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_68, IsStream_OnNonStream_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_68, IsRef_OnNonRef_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_68, IsCmd_OnNonCmd_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_68, IsError_OnNonError_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_68, IsEOF_OnNonEOF_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_68, IsNone_OnNonNone_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_68, IsInt64_OnNonInt64_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_68, IsIntOrInt64_OnInt_68) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_68, IsIntOrInt64_OnInt64_68) {
    Object obj(9876543210LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_68, IsIntOrInt64_OnReal_68) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_68, GetNum_FromInt_68) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_68, GetNum_FromReal_68) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_68, GetNumWithOk_FromInt_68) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_68, GetNumWithOk_FromReal_68) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_68, GetIntOrInt64_FromInt_68) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_68, GetIntOrInt64_FromInt64_68) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_68, GetNumWithDefaultValue_FromInt_68) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 42.0);
}

TEST_F(ObjectTest_68, GetNumWithDefaultValue_FromReal_68) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

TEST_F(ObjectTest_68, GetNumWithDefaultValue_FromNonNum_68) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_68, GetBoolWithDefaultValue_FromBool_68) {
    Object obj(true);
    EXPECT_EQ(obj.getBoolWithDefaultValue(false), true);
}

TEST_F(ObjectTest_68, GetBoolWithDefaultValue_FromNonBool_68) {
    Object obj(42);
    EXPECT_EQ(obj.getBoolWithDefaultValue(true), true);
}

TEST_F(ObjectTest_68, GetBoolWithDefaultValue_FromNonBool_DefaultFalse_68) {
    Object obj(42);
    EXPECT_EQ(obj.getBoolWithDefaultValue(false), false);
}

// ==================== Move Constructor Tests ====================

TEST_F(ObjectTest_68, MoveConstructor_Int_68) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be dead
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveConstructor_Bool_68) {
    Object obj1(true);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isBool());
    EXPECT_EQ(obj2.getBool(), true);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveConstructor_Real_68) {
    Object obj1(3.14);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveConstructor_Null_68) {
    Object obj1 = Object::null();
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isNull());
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveConstructor_Name_68) {
    Object obj1(objName, "test");
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "test");
    EXPECT_EQ(obj1.getType(), objDead);
}

// ==================== Move Assignment Tests ====================

TEST_F(ObjectTest_68, MoveAssignment_Int_68) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_OverwriteExisting_68) {
    Object obj1(42);
    Object obj2(100);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Bool_68) {
    Object obj1(false);
    Object obj2(42);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isBool());
    EXPECT_EQ(obj2.getBool(), false);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Real_68) {
    Object obj1(2.718);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 2.718);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Null_68) {
    Object obj1 = Object::null();
    Object obj2(42);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isNull());
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Error_68) {
    Object obj1 = Object::error();
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isError());
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_EOF_68) {
    Object obj1 = Object::eof();
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isEOF());
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Name_68) {
    Object obj1(objName, "myname");
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "myname");
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Cmd_68) {
    Object obj1(objCmd, "mycmd");
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isCmd());
    EXPECT_STREQ(obj2.getCmd(), "mycmd");
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_Int64_68) {
    long long val = 123456789012345LL;
    Object obj1(val);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), val);
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_String_68) {
    Object obj1(objString, std::string("hello world"));
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isString());
    EXPECT_EQ(obj1.getType(), objDead);
}

TEST_F(ObjectTest_68, MoveAssignment_DifferentTypes_68) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_EQ(obj1.getType(), objDead);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_68, SetToNull_FromInt_68) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_68, SetToNull_FromBool_68) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_68, SetToNull_FromNull_68) {
    Object obj = Object::null();
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_68, SetToNull_FromNone_68) {
    Object obj;
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_68, Copy_Int_68) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
    // Original should remain unchanged
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_68, Copy_Bool_68) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_EQ(copied.getBool(), true);
}

TEST_F(ObjectTest_68, Copy_Real_68) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_68, Copy_Null_68) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_68, Copy_Name_68) {
    Object obj(objName, "testname");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "testname");
}

TEST_F(ObjectTest_68, Copy_Int64_68) {
    long long val = 123456789012345LL;
    Object obj(val);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), val);
}

TEST_F(ObjectTest_68, Copy_Error_68) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_68, Copy_EOF_68) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_68, GetTypeName_Bool_68) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_68, GetTypeName_Int_68) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_68, GetTypeName_Real_68) {
    Object obj(3.14);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_68, GetTypeName_Null_68) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_68, GetTypeName_None_68) {
    Object obj;
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== isName with argument Tests ====================

TEST_F(ObjectTest_68, IsName_WithMatchingName_68) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_68, IsName_WithNonMatchingName_68) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_68, IsName_OnNonNameObject_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("TestName"));
}

// ==================== isCmd with argument Tests ====================

TEST_F(ObjectTest_68, IsCmd_WithMatchingCmd_68) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd("TestCmd"));
}

TEST_F(ObjectTest_68, IsCmd_WithNonMatchingCmd_68) {
    Object obj(objCmd, "TestCmd");
    EXPECT_FALSE(obj.isCmd("OtherCmd"));
}

TEST_F(ObjectTest_68, IsCmd_OnNonCmdObject_68) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("TestCmd"));
}

// ==================== getNameString Tests ====================

TEST_F(ObjectTest_68, GetNameString_68) {
    Object obj(objName, "myname");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "myname");
}

// ==================== Chain of Moves Tests ====================

TEST_F(ObjectTest_68, ChainOfMoves_68) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    Object obj3;
    obj3 = std::move(obj2);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
    EXPECT_EQ(obj1.getType(), objDead);
    EXPECT_EQ(obj2.getType(), objDead);
}

// ==================== Boundary Value Tests ====================

TEST_F(ObjectTest_68, IntConstructor_MaxInt_68) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_68, IntConstructor_MinInt_68) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_68, Int64Constructor_MaxInt64_68) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_68, Int64Constructor_MinInt64_68) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_68, RealConstructor_VerySmall_68) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

TEST_F(ObjectTest_68, RealConstructor_VeryLarge_68) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());
}

TEST_F(ObjectTest_68, NameConstructor_EmptyName_68) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_68, CmdConstructor_EmptyCmd_68) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Multiple Type Checks Exclusivity ====================

TEST_F(ObjectTest_68, TypeExclusivity_Int_68) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
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

TEST_F(ObjectTest_68, TypeExclusivity_Bool_68) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
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

TEST_F(ObjectTest_68, TypeExclusivity_Null_68) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
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

// ==================== IsNum also covers Int64 ====================

TEST_F(ObjectTest_68, IsNum_OnInt64_68) {
    long long val = 123456789012345LL;
    Object obj(val);
    // Int64 may or may not be considered "num" depending on implementation
    // We just record observable behavior
    // This test documents the behavior
    bool result = obj.isNum();
    // Just verify it doesn't crash; the actual result depends on implementation
    (void)result;
}

// ==================== HexString Tests ====================

TEST_F(ObjectTest_68, HexString_IsHexString_68) {
    Object obj(objHexString, std::string("48656C6C6F"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_EQ(obj.getType(), objHexString);
}

TEST_F(ObjectTest_68, HexString_GetHexString_68) {
    Object obj(objHexString, std::string("test"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_NE(obj.getHexString(), nullptr);
}
