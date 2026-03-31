#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_69 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ObjectTest_69, DefaultConstructor_IsNone_69) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_69, BoolConstructor_True_69) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_69, BoolConstructor_False_69) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_69, IntConstructor_69) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_69, IntConstructor_Zero_69) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_69, IntConstructor_Negative_69) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_69, RealConstructor_69) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_69, RealConstructor_Zero_69) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_69, RealConstructor_Negative_69) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_69, Int64Constructor_69) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_69, StringConstructor_69) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_69, NameConstructor_69) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_69, CmdConstructor_69) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

TEST_F(ObjectTest_69, HexStringConstructor_69) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Static Factory Tests ====================

TEST_F(ObjectTest_69, NullFactory_69) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_69, EofFactory_69) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_69, ErrorFactory_69) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_69, SetToNull_FromInt_69) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_69, SetToNull_FromBool_69) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromReal_69) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isReal());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromString_69) {
    Object obj(std::string("test"));
    EXPECT_TRUE(obj.isString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromName_69) {
    Object obj(objName, "SomeName");
    EXPECT_TRUE(obj.isName());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromNull_69) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromNone_69) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_69, SetToNull_FromError_69) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromEOF_69) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromInt64_69) {
    Object obj((long long)12345678901234LL);
    EXPECT_TRUE(obj.isInt64());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromCmd_69) {
    Object obj(objCmd, "cmd");
    EXPECT_TRUE(obj.isCmd());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Type Check Tests ====================

TEST_F(ObjectTest_69, IsNum_Int_69) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_69, IsNum_Real_69) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_69, IsNum_Bool_NotNum_69) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_69, IsIntOrInt64_Int_69) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_69, IsIntOrInt64_Int64_69) {
    Object obj((long long)42LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_69, IsIntOrInt64_Real_69) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_69, GetNum_FromInt_69) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_69, GetNum_FromReal_69) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_69, GetIntOrInt64_FromInt_69) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_69, GetIntOrInt64_FromInt64_69) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== Move Semantics Tests ====================

TEST_F(ObjectTest_69, MoveConstructor_69) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // obj1 should be in a valid but unspecified state (likely none or dead)
}

TEST_F(ObjectTest_69, MoveAssignment_69) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_69, Copy_Int_69) {
    Object obj1(42);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_69, Copy_Bool_69) {
    Object obj1(true);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isBool());
    EXPECT_TRUE(obj2.getBool());
}

TEST_F(ObjectTest_69, Copy_Real_69) {
    Object obj1(2.718);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 2.718);
}

TEST_F(ObjectTest_69, Copy_String_69) {
    Object obj1(std::string("hello"));
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isString());
}

TEST_F(ObjectTest_69, Copy_Name_69) {
    Object obj1(objName, "MyName");
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "MyName");
}

TEST_F(ObjectTest_69, Copy_Null_69) {
    Object obj1 = Object::null();
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isNull());
}

// ==================== isName with argument Tests ====================

TEST_F(ObjectTest_69, IsName_WithMatchingName_69) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_69, IsName_WithNonMatchingName_69) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_69, IsName_OnNonNameObject_69) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ==================== isCmd with argument Tests ====================

TEST_F(ObjectTest_69, IsCmd_WithMatchingCmd_69) {
    Object obj(objCmd, "myCmd");
    EXPECT_TRUE(obj.isCmd("myCmd"));
}

TEST_F(ObjectTest_69, IsCmd_WithNonMatchingCmd_69) {
    Object obj(objCmd, "myCmd");
    EXPECT_FALSE(obj.isCmd("otherCmd"));
}

TEST_F(ObjectTest_69, IsCmd_OnNonCmdObject_69) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ==================== getNameString Tests ====================

TEST_F(ObjectTest_69, GetNameString_69) {
    Object obj(objName, "SomeName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "SomeName");
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_69, GetNumWithDefaultValue_FromInt_69) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_69, GetNumWithDefaultValue_FromReal_69) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_69, GetNumWithDefaultValue_FromNonNum_69) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_69, GetNumWithDefaultValue_FromBool_69) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(77.7), 77.7);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_69, GetBoolWithDefaultValue_FromBoolTrue_69) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_69, GetBoolWithDefaultValue_FromBoolFalse_69) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_69, GetBoolWithDefaultValue_FromNonBool_69) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_69, GetBoolWithDefaultValue_FromNull_69) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_69, GetTypeName_Bool_69) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_69, GetTypeName_Int_69) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_69, GetTypeName_Null_69) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== Exclusive Type Tests ====================

TEST_F(ObjectTest_69, TypeExclusivity_Int_69) {
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

TEST_F(ObjectTest_69, TypeExclusivity_Bool_69) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
}

TEST_F(ObjectTest_69, TypeExclusivity_Null_69) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_69, ArrayConstruction_69) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_69, ArrayGetLength_Empty_69) {
    Object obj(new Array(nullptr));
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_69, ArrayAdd_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_69, ArrayAddMultiple_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_69, ArrayGet_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_69, ArrayGetNF_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_69, ArrayRemove_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_69, DictConstruction_69) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_69, DictGetLength_Empty_69) {
    Object obj(new Dict(nullptr));
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_69, DictAdd_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_69, DictLookup_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(123));
    Object val = obj.dictLookup("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 123);
}

TEST_F(ObjectTest_69, DictLookup_NonExistent_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(1));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_69, DictLookupNF_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("testkey", Object(77));
    const Object &val = obj.dictLookupNF("testkey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_69, DictSet_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key", Object(1));
    obj.dictSet("key", Object(2));
    Object val = obj.dictLookup("key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_69, DictRemove_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(1));
    obj.dictAdd("key2", Object(2));
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_69, DictGetKey_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_69, DictGetVal_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_69, DictGetValNF_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key", Object(66));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 66);
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_69, TakeString_69) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> str = obj.takeString();
    EXPECT_NE(str, nullptr);
}

// ==================== getNum with ok parameter Tests ====================

TEST_F(ObjectTest_69, GetNum_WithOk_FromInt_69) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_69, GetNum_WithOk_FromReal_69) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Multiple setToNull calls ====================

TEST_F(ObjectTest_69, SetToNull_MultipleCalls_69) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Boundary value tests ====================

TEST_F(ObjectTest_69, IntBoundary_MaxInt_69) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_69, IntBoundary_MinInt_69) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_69, Int64Boundary_MaxInt64_69) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_69, Int64Boundary_MinInt64_69) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

TEST_F(ObjectTest_69, RealBoundary_SmallPositive_69) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

TEST_F(ObjectTest_69, EmptyString_69) {
    Object obj(std::string(""));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_69, EmptyName_69) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Array with mixed types ====================

TEST_F(ObjectTest_69, ArrayWithMixedTypes_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    obj.arrayAdd(Object::null());
    EXPECT_EQ(obj.arrayGetLength(), 4);

    Object e0 = obj.arrayGet(0);
    EXPECT_TRUE(e0.isInt());
    EXPECT_EQ(e0.getInt(), 42);

    Object e1 = obj.arrayGet(1);
    EXPECT_TRUE(e1.isReal());
    EXPECT_DOUBLE_EQ(e1.getReal(), 3.14);

    Object e2 = obj.arrayGet(2);
    EXPECT_TRUE(e2.isBool());
    EXPECT_TRUE(e2.getBool());

    Object e3 = obj.arrayGet(3);
    EXPECT_TRUE(e3.isNull());
}

// ==================== Dict with multiple entries ====================

TEST_F(ObjectTest_69, DictMultipleEntries_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("int", Object(42));
    obj.dictAdd("real", Object(3.14));
    obj.dictAdd("bool", Object(true));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object v1 = obj.dictLookup("int");
    EXPECT_TRUE(v1.isInt());
    EXPECT_EQ(v1.getInt(), 42);

    Object v2 = obj.dictLookup("real");
    EXPECT_TRUE(v2.isReal());
    EXPECT_DOUBLE_EQ(v2.getReal(), 3.14);

    Object v3 = obj.dictLookup("bool");
    EXPECT_TRUE(v3.isBool());
    EXPECT_TRUE(v3.getBool());
}

// ==================== Move from complex objects ====================

TEST_F(ObjectTest_69, MoveFromArray_69) {
    Object obj1(new Array(nullptr));
    obj1.arrayAdd(Object(1));
    obj1.arrayAdd(Object(2));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isArray());
    EXPECT_EQ(obj2.arrayGetLength(), 2);
}

TEST_F(ObjectTest_69, MoveFromDict_69) {
    Object obj1(new Dict(nullptr));
    obj1.dictAdd("key", Object(42));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isDict());
    EXPECT_EQ(obj2.dictGetLength(), 1);
}

// ==================== SetToNull after complex operations ====================

TEST_F(ObjectTest_69, SetToNull_FromArray_69) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromDict_69) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key", Object(42));
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_69, SetToNull_FromHexString_69) {
    Object obj(objHexString, "ABCDEF");
    EXPECT_TRUE(obj.isHexString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}
