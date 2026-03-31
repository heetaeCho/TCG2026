#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "GooString.h"

// Helper to create an XRef-free environment
// We test Object as a black box based on its public interface.

class ObjectTest_67 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Construction and Type Checking Tests =====

TEST_F(ObjectTest_67, DefaultConstructor_IsNone_67) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_67, BoolConstructor_True_67) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_67, BoolConstructor_False_67) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_67, IntConstructor_67) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_67, IntConstructor_Zero_67) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_67, IntConstructor_Negative_67) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_67, RealConstructor_67) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_67, RealConstructor_Zero_67) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_67, RealConstructor_Negative_67) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_67, Int64Constructor_67) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_67, NullFactory_67) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_67, EofFactory_67) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_67, ErrorFactory_67) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ===== String Construction =====

TEST_F(ObjectTest_67, StringConstructor_GooString_67) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_67, StringConstructor_StdString_67) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "world");
}

TEST_F(ObjectTest_67, NameConstructor_67) {
    Object obj(objName, "myName");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "myName");
}

TEST_F(ObjectTest_67, CmdConstructor_67) {
    Object obj(objCmd, "myCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "myCmd");
}

// ===== isName / isCmd with parameter =====

TEST_F(ObjectTest_67, IsNameWithParam_Match_67) {
    Object obj(objName, "testName");
    EXPECT_TRUE(obj.isName("testName"));
}

TEST_F(ObjectTest_67, IsNameWithParam_NoMatch_67) {
    Object obj(objName, "testName");
    EXPECT_FALSE(obj.isName("otherName"));
}

TEST_F(ObjectTest_67, IsCmdWithParam_Match_67) {
    Object obj(objCmd, "testCmd");
    EXPECT_TRUE(obj.isCmd("testCmd"));
}

TEST_F(ObjectTest_67, IsCmdWithParam_NoMatch_67) {
    Object obj(objCmd, "testCmd");
    EXPECT_FALSE(obj.isCmd("otherCmd"));
}

// ===== isNum tests =====

TEST_F(ObjectTest_67, IsNum_Int_67) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_67, IsNum_Real_67) {
    Object obj(5.0);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_67, IsNum_Bool_NotNum_67) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// ===== getNum tests =====

TEST_F(ObjectTest_67, GetNum_FromInt_67) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_67, GetNum_FromReal_67) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// ===== isIntOrInt64 / getIntOrInt64 =====

TEST_F(ObjectTest_67, IsIntOrInt64_Int_67) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_67, IsIntOrInt64_Int64_67) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ===== Move constructor and assignment =====

TEST_F(ObjectTest_67, MoveConstructor_67) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid state (typically none)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_67, MoveAssignment_67) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
}

// ===== setToNull =====

TEST_F(ObjectTest_67, SetToNull_FromInt_67) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_67, SetToNull_FromNone_67) {
    Object obj;
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ===== Copy =====

TEST_F(ObjectTest_67, Copy_Int_67) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_67, Copy_Real_67) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_67, Copy_Bool_67) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_67, Copy_Null_67) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_67, Copy_String_67) {
    Object obj(std::make_unique<GooString>("test"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "test");
}

TEST_F(ObjectTest_67, Copy_Name_67) {
    Object obj(objName, "aName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "aName");
}

// ===== Type exclusivity tests =====

TEST_F(ObjectTest_67, TypeExclusivity_Int_67) {
    Object obj(10);
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

TEST_F(ObjectTest_67, TypeExclusivity_Bool_67) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

// ===== getTypeName =====

TEST_F(ObjectTest_67, GetTypeName_Int_67) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_67, GetTypeName_Bool_67) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_67, GetTypeName_Null_67) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ===== getNumWithDefaultValue =====

TEST_F(ObjectTest_67, GetNumWithDefaultValue_FromInt_67) {
    Object obj(5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 5.0);
}

TEST_F(ObjectTest_67, GetNumWithDefaultValue_FromReal_67) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 2.5);
}

TEST_F(ObjectTest_67, GetNumWithDefaultValue_NonNumeric_67) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_67, GetNumWithDefaultValue_Null_67) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ===== getBoolWithDefaultValue =====

TEST_F(ObjectTest_67, GetBoolWithDefaultValue_FromBool_67) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_67, GetBoolWithDefaultValue_NonBool_67) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_67, GetBoolWithDefaultValue_NonBool_DefaultFalse_67) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ===== Array operations =====

TEST_F(ObjectTest_67, ArrayConstructor_67) {
    // Create a simple array
    // Note: Array requires an XRef*, but we can try with nullptr for basic tests
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_67, ArrayGetLength_Empty_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_67, ArrayAdd_And_GetLength_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_67, ArrayAdd_Multiple_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_67, ArrayGet_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_67, ArrayGetNF_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_67, ArrayRemove_67) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 2);
}

// ===== Dict operations =====

TEST_F(ObjectTest_67, DictConstructor_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getDict(), dict);
}

TEST_F(ObjectTest_67, DictGetLength_Empty_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_67, DictAdd_And_Lookup_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_67, DictSet_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_67, DictRemove_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_67, DictLookup_NonExistent_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_67, DictGetKey_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("myKey", Object(1));
    const char *key = obj.dictGetKey(0);
    EXPECT_NE(key, nullptr);
    EXPECT_STREQ(key, "myKey");
}

TEST_F(ObjectTest_67, DictGetVal_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_67, DictGetValNF_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k", Object(88));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 88);
}

TEST_F(ObjectTest_67, DictLookupNF_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k2", Object(55));
    const Object &val = obj.dictLookupNF("k2");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_67, DictMultipleEntries_67) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// ===== takeString =====

TEST_F(ObjectTest_67, TakeString_67) {
    Object obj(std::make_unique<GooString>("takeMe"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "takeMe");
}

// ===== getNameString =====

TEST_F(ObjectTest_67, GetNameString_67) {
    Object obj(objName, "testNameStr");
    std::string ns = obj.getNameString();
    EXPECT_EQ(ns, "testNameStr");
}

// ===== getNum with ok parameter =====

TEST_F(ObjectTest_67, GetNumWithOk_Int_67) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

TEST_F(ObjectTest_67, GetNumWithOk_Real_67) {
    Object obj(1.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 1.5);
}

// ===== HexString =====

TEST_F(ObjectTest_67, HexStringConstructor_67) {
    Object obj(objHexString, "ABCD");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ===== Edge cases with copy of error/eof/none =====

TEST_F(ObjectTest_67, Copy_Error_67) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_67, Copy_EOF_67) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// ===== Move self-consistency =====

TEST_F(ObjectTest_67, MoveChain_67) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    Object obj3(std::move(obj2));
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
    EXPECT_TRUE(obj2.isNone());
}

// ===== Deep copy =====

TEST_F(ObjectTest_67, DeepCopy_Int_67) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_67, DeepCopy_String_67) {
    Object obj(std::make_unique<GooString>("deep"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deep");
}

// ===== Int boundary values =====

TEST_F(ObjectTest_67, IntConstructor_MaxInt_67) {
    int maxVal = std::numeric_limits<int>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), maxVal);
}

TEST_F(ObjectTest_67, IntConstructor_MinInt_67) {
    int minVal = std::numeric_limits<int>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), minVal);
}

TEST_F(ObjectTest_67, Int64Constructor_MinInt64_67) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// ===== Empty string =====

TEST_F(ObjectTest_67, EmptyString_67) {
    Object obj(std::make_unique<GooString>(""));
    EXPECT_TRUE(obj.isString());
    EXPECT_STREQ(obj.getString()->c_str(), "");
}

TEST_F(ObjectTest_67, EmptyName_67) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ===== Print (just check it doesn't crash) =====

TEST_F(ObjectTest_67, Print_Int_NoCrash_67) {
    Object obj(42);
    // Print to stdout; just ensure no crash
    obj.print(stdout);
}

TEST_F(ObjectTest_67, Print_Null_NoCrash_67) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_67, Print_String_NoCrash_67) {
    Object obj(std::make_unique<GooString>("printTest"));
    obj.print(stdout);
}
