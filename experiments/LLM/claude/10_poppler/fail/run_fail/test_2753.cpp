#include <gtest/gtest.h>
#include <memory>
#include <cstring>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_2753 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ObjectTest_2753, DefaultConstructor_CreatesNoneObject_2753) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_2753, BoolConstructor_True_2753) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2753, BoolConstructor_False_2753) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_2753, IntConstructor_PositiveValue_2753) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2753, IntConstructor_Zero_2753) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2753, IntConstructor_NegativeValue_2753) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_2753, RealConstructor_PositiveValue_2753) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2753, RealConstructor_Zero_2753) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2753, RealConstructor_NegativeValue_2753) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_2753, Int64Constructor_2753) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2753, Int64Constructor_NegativeValue_2753) {
    long long val = -9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== Move Constructor Tests ====================

TEST_F(ObjectTest_2753, MoveConstructor_IntObject_2753) {
    Object src(42);
    EXPECT_TRUE(src.isInt());
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isInt());
    EXPECT_EQ(dst.getInt(), 42);
    // After move, source should be dead
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_BoolObject_2753) {
    Object src(true);
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isBool());
    EXPECT_TRUE(dst.getBool());
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_RealObject_2753) {
    Object src(1.5);
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isReal());
    EXPECT_DOUBLE_EQ(dst.getReal(), 1.5);
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_NullObject_2753) {
    Object src = Object::null();
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isNull());
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_NoneObject_2753) {
    Object src;
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isNone());
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_ErrorObject_2753) {
    Object src = Object::error();
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isError());
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_EOFObject_2753) {
    Object src = Object::eof();
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isEOF());
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveConstructor_Int64Object_2753) {
    long long val = 123456789012345LL;
    Object src(val);
    Object dst(std::move(src));
    EXPECT_TRUE(dst.isInt64());
    EXPECT_EQ(dst.getInt64(), val);
    EXPECT_EQ(src.getType(), objDead);
}

// ==================== Move Assignment Tests ====================

TEST_F(ObjectTest_2753, MoveAssignment_IntToNone_2753) {
    Object src(99);
    Object dst;
    dst = std::move(src);
    EXPECT_TRUE(dst.isInt());
    EXPECT_EQ(dst.getInt(), 99);
    EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectTest_2753, MoveAssignment_RealToBool_2753) {
    Object src(2.5);
    Object dst(false);
    dst = std::move(src);
    EXPECT_TRUE(dst.isReal());
    EXPECT_DOUBLE_EQ(dst.getReal(), 2.5);
}

// ==================== Static Factory Tests ====================

TEST_F(ObjectTest_2753, NullFactory_2753) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2753, EofFactory_2753) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_2753, ErrorFactory_2753) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Check Tests ====================

TEST_F(ObjectTest_2753, TypeCheckBool_2753) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNum());
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

TEST_F(ObjectTest_2753, TypeCheckInt_IsNum_2753) {
    Object obj(5);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_2753, TypeCheckReal_IsNum_2753) {
    Object obj(5.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2753, TypeCheckInt64_IsIntOrInt64_2753) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_FALSE(obj.isInt());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_2753, GetNum_FromInt_2753) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNum(), 10.0);
}

TEST_F(ObjectTest_2753, GetNum_FromReal_2753) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_2753, GetNumWithOk_FromInt_2753) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

TEST_F(ObjectTest_2753, GetNumWithOk_FromReal_2753) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_2753, GetIntOrInt64_FromInt_2753) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2753, GetIntOrInt64_FromInt64_2753) {
    long long val = 1234567890123LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_2753, GetNumWithDefaultValue_IntObject_2753) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 7.0);
}

TEST_F(ObjectTest_2753, GetNumWithDefaultValue_RealObject_2753) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 7.5);
}

TEST_F(ObjectTest_2753, GetNumWithDefaultValue_NonNumericObject_2753) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_2753, GetNumWithDefaultValue_BoolObject_2753) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_2753, GetBoolWithDefaultValue_BoolObjectTrue_2753) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2753, GetBoolWithDefaultValue_BoolObjectFalse_2753) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2753, GetBoolWithDefaultValue_NonBoolObject_2753) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2753, GetBoolWithDefaultValue_NullObject_2753) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_2753, SetToNull_FromInt_2753) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2753, SetToNull_FromBool_2753) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_2753, SetToNull_FromNone_2753) {
    Object obj;
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== String Object Tests ====================

TEST_F(ObjectTest_2753, StringConstructor_FromRvalueString_2753) {
    Object obj(ObjType::objString, std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_2753, NameConstructor_2753) {
    Object obj(ObjType::objName, "testname");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "testname");
}

TEST_F(ObjectTest_2753, CmdConstructor_2753) {
    Object obj(ObjType::objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_2753, HexStringConstructor_2753) {
    Object obj(ObjType::objHexString, std::string("ABCDEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== isName with string comparison ====================

TEST_F(ObjectTest_2753, IsNameWithMatch_2753) {
    Object obj(ObjType::objName, "Page");
    EXPECT_TRUE(obj.isName("Page"));
    EXPECT_FALSE(obj.isName("Catalog"));
}

TEST_F(ObjectTest_2753, IsNameWithNonNameObject_2753) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ==================== isCmd with string comparison ====================

TEST_F(ObjectTest_2753, IsCmdWithMatch_2753) {
    Object obj(ObjType::objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_2753, IsCmdWithNonCmdObject_2753) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("BT"));
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_2753, GetTypeName_Bool_2753) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2753, GetTypeName_Int_2753) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2753, GetTypeName_Null_2753) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2753, GetTypeName_Error_2753) {
    Object obj = Object::error();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2753, GetTypeName_EOF_2753) {
    Object obj = Object::eof();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2753, GetTypeName_None_2753) {
    Object obj;
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_2753, Copy_IntObject_2753) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
    // Original should still be valid
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2753, Copy_BoolObject_2753) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2753, Copy_RealObject_2753) {
    Object obj(2.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.5);
}

TEST_F(ObjectTest_2753, Copy_NullObject_2753) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_2753, Copy_Int64Object_2753) {
    long long val = 9876543210LL;
    Object obj(val);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), val);
}

// ==================== Name string access ====================

TEST_F(ObjectTest_2753, GetNameString_2753) {
    Object obj(ObjType::objName, "TestName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "TestName");
}

// ==================== Multiple moves chain ====================

TEST_F(ObjectTest_2753, ChainedMoveConstructor_2753) {
    Object a(42);
    Object b(std::move(a));
    Object c(std::move(b));
    EXPECT_TRUE(c.isInt());
    EXPECT_EQ(c.getInt(), 42);
    EXPECT_EQ(a.getType(), objDead);
    EXPECT_EQ(b.getType(), objDead);
}

TEST_F(ObjectTest_2753, ChainedMoveAssignment_2753) {
    Object a(42);
    Object b;
    Object c;
    b = std::move(a);
    c = std::move(b);
    EXPECT_TRUE(c.isInt());
    EXPECT_EQ(c.getInt(), 42);
    EXPECT_EQ(a.getType(), objDead);
    EXPECT_EQ(b.getType(), objDead);
}

// ==================== String constructor with unique_ptr ====================

TEST_F(ObjectTest_2753, StringConstructor_GooString_2753) {
    auto str = std::make_unique<GooString>("test string");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ==================== Boundary: Large int values ====================

TEST_F(ObjectTest_2753, IntConstructor_MaxInt_2753) {
    int maxVal = std::numeric_limits<int>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), maxVal);
}

TEST_F(ObjectTest_2753, IntConstructor_MinInt_2753) {
    int minVal = std::numeric_limits<int>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), minVal);
}

TEST_F(ObjectTest_2753, RealConstructor_VerySmall_2753) {
    double tiny = 1e-300;
    Object obj(tiny);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), tiny);
}

TEST_F(ObjectTest_2753, RealConstructor_VeryLarge_2753) {
    double huge = 1e300;
    Object obj(huge);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), huge);
}

// ==================== Name constructor with empty string ====================

TEST_F(ObjectTest_2753, NameConstructor_EmptyString_2753) {
    Object obj(ObjType::objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Cmd constructor with empty string ====================

TEST_F(ObjectTest_2753, CmdConstructor_EmptyString_2753) {
    Object obj(ObjType::objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Destructor safety (no crash) ====================

TEST_F(ObjectTest_2753, DestructorSafety_DefaultObject_2753) {
    { Object obj; }
    SUCCEED();
}

TEST_F(ObjectTest_2753, DestructorSafety_MovedFromObject_2753) {
    Object a(42);
    Object b(std::move(a));
    // 'a' is now dead, destructor should not crash
    SUCCEED();
}

TEST_F(ObjectTest_2753, DestructorSafety_NullObject_2753) {
    { Object obj = Object::null(); }
    SUCCEED();
}

// ==================== Multiple type objects lifecycle ====================

TEST_F(ObjectTest_2753, MultipleObjectsLifecycle_2753) {
    Object boolObj(true);
    Object intObj(42);
    Object realObj(3.14);
    Object nullObj = Object::null();
    Object errObj = Object::error();
    Object eofObj = Object::eof();
    
    EXPECT_TRUE(boolObj.isBool());
    EXPECT_TRUE(intObj.isInt());
    EXPECT_TRUE(realObj.isReal());
    EXPECT_TRUE(nullObj.isNull());
    EXPECT_TRUE(errObj.isError());
    EXPECT_TRUE(eofObj.isEOF());
}
