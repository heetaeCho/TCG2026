#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_107 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_107, DefaultConstructor_IsNone_107) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_107, BoolConstructor_True_107) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_107, BoolConstructor_False_107) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_107, IntConstructor_107) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_107, IntConstructor_Negative_107) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_107, IntConstructor_Zero_107) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_107, RealConstructor_107) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_107, RealConstructor_Zero_107) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_107, RealConstructor_Negative_107) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_107, Int64Constructor_107) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_107, CmdConstructor_107) {
    Object obj(objCmd, "test_cmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "test_cmd");
}

TEST_F(ObjectTest_107, NameConstructor_107) {
    Object obj(objName, "test_name");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "test_name");
}

TEST_F(ObjectTest_107, StringConstructor_WithGooString_107) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_107, StringConstructor_WithStdString_107) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_107, NullFactory_107) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_107, EofFactory_107) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_107, ErrorFactory_107) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Tests ====================

TEST_F(ObjectTest_107, IsNum_ForInt_107) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_107, IsNum_ForReal_107) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_107, IsNum_ForBool_ReturnsFalse_107) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_107, IsIntOrInt64_ForInt_107) {
    Object obj(5);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_107, IsIntOrInt64_ForInt64_107) {
    long long val = 12345678901LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_107, IsIntOrInt64_ForReal_ReturnsFalse_107) {
    Object obj(1.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_107, GetNum_FromInt_107) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_107, GetNum_FromReal_107) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_107, GetNum_WithOkParam_107) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_107, GetIntOrInt64_FromInt_107) {
    Object obj(123);
    EXPECT_EQ(obj.getIntOrInt64(), 123LL);
}

TEST_F(ObjectTest_107, GetIntOrInt64_FromInt64_107) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getCmd Tests ====================

TEST_F(ObjectTest_107, GetCmd_ReturnsCorrectString_107) {
    Object obj(objCmd, "mycommand");
    EXPECT_STREQ(obj.getCmd(), "mycommand");
}

TEST_F(ObjectTest_107, GetCmd_EmptyString_107) {
    Object obj(objCmd, "");
    EXPECT_STREQ(obj.getCmd(), "");
}

TEST_F(ObjectTest_107, IsCmd_WithMatchingName_107) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_107, IsCmd_WithNonMatchingName_107) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== isName with string_view Tests ====================

TEST_F(ObjectTest_107, IsName_WithMatchingName_107) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
}

TEST_F(ObjectTest_107, IsName_WithNonMatchingName_107) {
    Object obj(objName, "Type");
    EXPECT_FALSE(obj.isName("Font"));
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_107, MoveConstructor_107) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, original should be in a valid but unspecified state (typically objNone)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_107, MoveAssignment_107) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_107, SetToNull_FromInt_107) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_107, SetToNull_FromNone_107) {
    Object obj;
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_107, GetTypeName_Bool_107) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_107, GetTypeName_Int_107) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_107, GetTypeName_Null_107) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== copy Tests ====================

TEST_F(ObjectTest_107, Copy_Int_107) {
    Object obj(99);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 99);
}

TEST_F(ObjectTest_107, Copy_Bool_107) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_107, Copy_Real_107) {
    Object obj(1.23);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 1.23);
}

TEST_F(ObjectTest_107, Copy_Null_107) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_107, Copy_Cmd_107) {
    Object obj(objCmd, "test");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isCmd());
    EXPECT_STREQ(copied.getCmd(), "test");
}

TEST_F(ObjectTest_107, Copy_Name_107) {
    Object obj(objName, "myname");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "myname");
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_107, GetNumWithDefaultValue_IntObject_107) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_107, GetNumWithDefaultValue_RealObject_107) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_107, GetNumWithDefaultValue_NonNumObject_107) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_107, GetBoolWithDefaultValue_BoolObject_107) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_107, GetBoolWithDefaultValue_NonBoolObject_107) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_107, GetBoolWithDefaultValue_NonBoolReturnsDefault_107) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== HexString Tests ====================

TEST_F(ObjectTest_107, HexStringConstructor_107) {
    Object obj(objHexString, std::string("AABB"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== getName / getNameString Tests ====================

TEST_F(ObjectTest_107, GetName_107) {
    Object obj(objName, "TestName");
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_107, GetNameString_107) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== Exclusive type checks ====================

TEST_F(ObjectTest_107, TypeExclusivity_Bool_107) {
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

TEST_F(ObjectTest_107, TypeExclusivity_Int_107) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_107, TypeExclusivity_Error_107) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_107, TypeExclusivity_EOF_107) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ==================== Boundary value tests ====================

TEST_F(ObjectTest_107, IntConstructor_MaxInt_107) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_107, IntConstructor_MinInt_107) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_107, Int64Constructor_MaxInt64_107) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_107, Int64Constructor_MinInt64_107) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_107, RealConstructor_VeryLargeValue_107) {
    Object obj(1e308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e308);
}

TEST_F(ObjectTest_107, RealConstructor_VerySmallValue_107) {
    Object obj(1e-308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-308);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_107, ArrayObject_107) {
    // Create an array object via an Array pointer
    // We need a valid Array - but since we don't have XRef, we try with nullptr
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_107, ArrayAdd_107) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_107, ArrayGet_107) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_107, ArrayRemove_107) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_107, ArrayGetNF_107) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_107, DictObject_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_107, DictAdd_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_107, DictLookup_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(123));
    Object val = obj.dictLookup("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 123);
}

TEST_F(ObjectTest_107, DictLookup_NotFound_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_107, DictSet_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(1));
    obj.dictSet("key", Object(2));
    Object val = obj.dictLookup("key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_107, DictRemove_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(1));
    obj.dictAdd("key2", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_107, DictGetKey_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("alpha", Object(1));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "alpha");
}

TEST_F(ObjectTest_107, DictGetVal_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("beta", Object(99));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_107, DictGetValNF_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("gamma", Object(77));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_107, DictLookupNF_107) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("delta", Object(55));
    const Object &val = obj.dictLookupNF("delta");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// ==================== String Tests ====================

TEST_F(ObjectTest_107, TakeString_107) {
    Object obj(std::make_unique<GooString>("takeMe"));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    // After takeString, the string should have been moved out
}

// ==================== deepCopy Tests ====================

TEST_F(ObjectTest_107, DeepCopy_Int_107) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_107, DeepCopy_String_107) {
    Object obj(std::make_unique<GooString>("deep"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_NE(deep.getString(), nullptr);
}

// ==================== Multiple Moves ====================

TEST_F(ObjectTest_107, MultipleMoves_107) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    Object obj3(std::move(obj2));
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
    EXPECT_TRUE(obj2.isNone());
}
