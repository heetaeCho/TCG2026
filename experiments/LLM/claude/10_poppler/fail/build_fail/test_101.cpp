#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"

// Helper to create an XRef-less Array
// We need a minimal setup for Array and Dict objects

class ObjectTest_101 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Type Construction Tests ====================

TEST_F(ObjectTest_101, DefaultConstructorCreatesNoneObject_101) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_101, BoolConstructorTrue_101) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_101, BoolConstructorFalse_101) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_101, IntConstructor_101) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_101, IntConstructorZero_101) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_101, IntConstructorNegative_101) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_101, RealConstructor_101) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_101, RealConstructorZero_101) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_101, Int64Constructor_101) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_101, NullStaticFactory_101) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_101, EofStaticFactory_101) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_101, ErrorStaticFactory_101) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== isNum Tests ====================

TEST_F(ObjectTest_101, IsNumForInt_101) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_101, IsNumForReal_101) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_101, IsNumForBool_101) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_101, GetNumFromInt_101) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_101, GetNumFromReal_101) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// ==================== isIntOrInt64 Tests ====================

TEST_F(ObjectTest_101, IsIntOrInt64ForInt_101) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_101, IsIntOrInt64ForInt64_101) {
    Object obj((long long)10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_101, IsIntOrInt64ForReal_101) {
    Object obj(10.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_101, GetIntOrInt64FromInt_101) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_101, GetIntOrInt64FromInt64_101) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== Type Predicate Tests ====================

TEST_F(ObjectTest_101, TypePredicatesForNone_101) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_FALSE(obj.isBool());
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
    EXPECT_FALSE(obj.isInt64());
}

// ==================== Move Constructor Tests ====================

TEST_F(ObjectTest_101, MoveConstructor_101) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically none or dead)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_101, MoveAssignment_101) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_101, SetToNull_101) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== String Construction Tests ====================

TEST_F(ObjectTest_101, StringConstructorFromGooString_101) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_101, StringConstructorFromStdString_101) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

// ==================== Name Construction Tests ====================

TEST_F(ObjectTest_101, NameConstructor_101) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_101, IsNameWithMatchingName_101) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_101, GetNameString_101) {
    Object obj(objName, "SomeName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "SomeName");
}

// ==================== Cmd Construction Tests ====================

TEST_F(ObjectTest_101, CmdConstructor_101) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_101, IsCmdWithMatchingCmd_101) {
    Object obj(objCmd, "Q");
    EXPECT_TRUE(obj.isCmd("Q"));
    EXPECT_FALSE(obj.isCmd("q"));
}

// ==================== HexString Construction Tests ====================

TEST_F(ObjectTest_101, HexStringConstructor_101) {
    Object obj(objHexString, "ABCD");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_101, ArrayConstructorAndGetArray_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_101, ArrayGetLength_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_101, ArrayAddAndGetLength_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_101, ArrayGetElement_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_101, ArrayGetNF_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_101, ArrayRemove_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    // Element at index 0 should still be 1
    Object elem0 = obj.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 1);
    // Element at index 1 should now be 3
    Object elem1 = obj.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 3);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_101, DictConstructorAndGetDict_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.getDict(), dict);
}

TEST_F(ObjectTest_101, DictGetLength_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_101, DictAddAndLookup_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_101, DictSetOverwritesValue_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    obj.dictSet("key1", Object(200));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 200);
}

TEST_F(ObjectTest_101, DictRemove_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    obj.dictAdd("key2", Object(200));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_101, DictGetKey_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_101, DictGetVal_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_101, DictGetValNF_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k", Object(88));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 88);
}

TEST_F(ObjectTest_101, DictLookupNF_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("k2", Object(55));
    const Object &val = obj.dictLookupNF("k2");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_101, DictLookupMissing_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_101, CopyInt_101) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_101, CopyBool_101) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_101, CopyReal_101) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_101, CopyNull_101) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_101, CopyName_101) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_101, GetTypeNameBool_101) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "boolean");
}

TEST_F(ObjectTest_101, GetTypeNameInt_101) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "integer");
}

TEST_F(ObjectTest_101, GetTypeNameReal_101) {
    Object obj(1.0);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "real");
}

TEST_F(ObjectTest_101, GetTypeNameNull_101) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "null");
}

TEST_F(ObjectTest_101, GetTypeNameError_101) {
    Object obj = Object::error();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "error");
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_101, GetNumWithDefaultValueFromInt_101) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_101, GetNumWithDefaultValueFromReal_101) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

TEST_F(ObjectTest_101, GetNumWithDefaultValueFromNonNum_101) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_101, GetNumWithDefaultValueFromNull_101) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_101, GetBoolWithDefaultValueFromBool_101) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_101, GetBoolWithDefaultValueFromNonBool_101) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_101, GetBoolWithDefaultValueFromNonBoolTrue_101) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== takeString Test ====================

TEST_F(ObjectTest_101, TakeStringTransfersOwnership_101) {
    auto str = std::make_unique<GooString>("test");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "test");
}

// ==================== Multiple dict entries ====================

TEST_F(ObjectTest_101, DictMultipleEntries_101) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
    
    Object va = obj.dictLookup("a");
    Object vb = obj.dictLookup("b");
    Object vc = obj.dictLookup("c");
    EXPECT_EQ(va.getInt(), 1);
    EXPECT_EQ(vb.getInt(), 2);
    EXPECT_EQ(vc.getInt(), 3);
}

// ==================== Array with different types ====================

TEST_F(ObjectTest_101, ArrayWithMixedTypes_101) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
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

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_101, GetNumWithOkParameterForInt_101) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

TEST_F(ObjectTest_101, GetNumWithOkParameterForReal_101) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// ==================== Move semantics with arrays ====================

TEST_F(ObjectTest_101, MoveConstructorWithArray_101) {
    Array *arr = new Array(nullptr);
    Object obj1(arr);
    obj1.arrayAdd(Object(10));
    
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isArray());
    EXPECT_EQ(obj2.arrayGetLength(), 1);
    Object elem = obj2.arrayGet(0);
    EXPECT_EQ(elem.getInt(), 10);
}

// ==================== Move assignment with dict ====================

TEST_F(ObjectTest_101, MoveAssignmentWithDict_101) {
    Dict *dict = new Dict(nullptr);
    Object obj1(dict);
    obj1.dictAdd("x", Object(99));
    
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isDict());
    EXPECT_EQ(obj2.dictGetLength(), 1);
    Object val = obj2.dictLookup("x");
    EXPECT_EQ(val.getInt(), 99);
}

// ==================== Int64 boundary ====================

TEST_F(ObjectTest_101, Int64NegativeValue_101) {
    long long val = -9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== DeepCopy test ====================

TEST_F(ObjectTest_101, DeepCopyInt_101) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_101, DeepCopyString_101) {
    auto str = std::make_unique<GooString>("deep");
    Object obj(std::move(str));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deep");
}
