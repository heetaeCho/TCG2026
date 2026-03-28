#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "GooString.h"

// Helper to create an XRef-less environment for basic tests
// We test Object as a black box based on its public interface.

class ObjectTest_81 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Default constructor tests
// =============================================================================

TEST_F(ObjectTest_81, DefaultConstructorCreatesNoneObject_81) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// =============================================================================
// Bool tests
// =============================================================================

TEST_F(ObjectTest_81, BoolConstructorTrue_81) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_81, BoolConstructorFalse_81) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_81, BoolIsNotOtherTypes_81) {
    Object obj(true);
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
}

// =============================================================================
// Int tests
// =============================================================================

TEST_F(ObjectTest_81, IntConstructor_81) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_81, IntIsNum_81) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_81, IntIsIntOrInt64_81) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42);
}

TEST_F(ObjectTest_81, IntNegativeValue_81) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_81, IntZero_81) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// =============================================================================
// Real tests
// =============================================================================

TEST_F(ObjectTest_81, RealConstructor_81) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_81, RealIsNum_81) {
    Object obj(2.718);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_81, RealIsNotInt_81) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_81, RealZero_81) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_81, RealNegative_81) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

// =============================================================================
// String tests
// =============================================================================

TEST_F(ObjectTest_81, StringConstructorFromGooString_81) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_81, StringConstructorFromStdString_81) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_81, StringIsNotOtherTypes_81) {
    auto gs = std::make_unique<GooString>("test");
    Object obj(std::move(gs));
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
}

// =============================================================================
// HexString tests
// =============================================================================

TEST_F(ObjectTest_81, HexStringConstructor_81) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Name tests
// =============================================================================

TEST_F(ObjectTest_81, NameConstructor_81) {
    Object obj(objName, "FontName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "FontName");
}

TEST_F(ObjectTest_81, NameMatchingCheck_81) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
    EXPECT_FALSE(obj.isName("Subtype"));
}

TEST_F(ObjectTest_81, NameEmptyString_81) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_TRUE(obj.isName(""));
}

// =============================================================================
// Null tests
// =============================================================================

TEST_F(ObjectTest_81, NullStaticFactory_81) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_81, NullIsNotOtherTypes_81) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
}

// =============================================================================
// Error tests
// =============================================================================

TEST_F(ObjectTest_81, ErrorStaticFactory_81) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// EOF tests
// =============================================================================

TEST_F(ObjectTest_81, EofStaticFactory_81) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// =============================================================================
// Int64 tests
// =============================================================================

TEST_F(ObjectTest_81, Int64Constructor_81) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_81, Int64IsIntOrInt64_81) {
    long long val = 123456789LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_81, Int64IsNotInt_81) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_FALSE(obj.isInt());
    EXPECT_TRUE(obj.isInt64());
}

// =============================================================================
// Cmd tests
// =============================================================================

TEST_F(ObjectTest_81, CmdConstructor_81) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_81, CmdMatchingCheck_81) {
    Object obj(objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// =============================================================================
// Move semantics tests
// =============================================================================

TEST_F(ObjectTest_81, MoveConstructor_81) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_81, MoveAssignment_81) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// =============================================================================
// setToNull tests
// =============================================================================

TEST_F(ObjectTest_81, SetToNull_81) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Copy tests
// =============================================================================

TEST_F(ObjectTest_81, CopyInt_81) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_81, CopyBool_81) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_81, CopyReal_81) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_81, CopyNull_81) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_81, CopyString_81) {
    Object obj(std::make_unique<GooString>("test"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "test");
}

TEST_F(ObjectTest_81, CopyName_81) {
    Object obj(objName, "MyName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "MyName");
}

// =============================================================================
// Array tests
// =============================================================================

TEST_F(ObjectTest_81, ArrayConstructorAndLength_81) {
    // Create an Array - requires an XRef, but we can try with nullptr
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_81, ArrayAddAndGet_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_81, ArrayAddMultipleElements_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    EXPECT_EQ(obj.arrayGet(0).getInt(), 1);
    EXPECT_EQ(obj.arrayGet(1).getInt(), 2);
    EXPECT_EQ(obj.arrayGet(2).getInt(), 3);
}

TEST_F(ObjectTest_81, ArrayRemove_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    EXPECT_EQ(obj.arrayGet(0).getInt(), 10);
    EXPECT_EQ(obj.arrayGet(1).getInt(), 30);
}

TEST_F(ObjectTest_81, ArrayGetNF_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

// =============================================================================
// Dict tests
// =============================================================================

TEST_F(ObjectTest_81, DictConstructorAndLength_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_81, DictAddAndLookup_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_81, DictSetOverwritesValue_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_81, DictRemove_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("A");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("A");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_81, DictGetKey_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(55));
    EXPECT_STREQ(obj.dictGetKey(0), "MyKey");
}

TEST_F(ObjectTest_81, DictGetVal_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("X", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_81, DictGetValNF_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Y", Object(88));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 88);
}

TEST_F(ObjectTest_81, DictLookupNF_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Z", Object(99));
    const Object &val = obj.dictLookupNF("Z");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_81, DictLookupNonExistentKey_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

// =============================================================================
// isStream tests (the provided partial code)
// =============================================================================

TEST_F(ObjectTest_81, IsStreamReturnsFalseForNonStream_81) {
    Object obj(42);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_81, IsStreamReturnsFalseForNull_81) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_81, IsStreamReturnsFalseForDict_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_81, IsStreamReturnsFalseForArray_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_81, IsStreamReturnsFalseForBool_81) {
    Object obj(true);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_81, IsStreamReturnsFalseForString_81) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_FALSE(obj.isStream());
}

// =============================================================================
// getTypeName tests
// =============================================================================

TEST_F(ObjectTest_81, GetTypeNameForBool_81) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_81, GetTypeNameForInt_81) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_81, GetTypeNameForNull_81) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// =============================================================================
// getNum with ok parameter tests
// =============================================================================

TEST_F(ObjectTest_81, GetNumWithOkForInt_81) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_81, GetNumWithOkForReal_81) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// =============================================================================
// getNumWithDefaultValue tests
// =============================================================================

TEST_F(ObjectTest_81, GetNumWithDefaultValueForInt_81) {
    Object obj(42);
    double val = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_81, GetNumWithDefaultValueForNonNumeric_81) {
    Object obj = Object::null();
    double val = obj.getNumWithDefaultValue(99.9);
    EXPECT_DOUBLE_EQ(val, 99.9);
}

// =============================================================================
// getBoolWithDefaultValue tests
// =============================================================================

TEST_F(ObjectTest_81, GetBoolWithDefaultValueForBool_81) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_81, GetBoolWithDefaultValueForNonBool_81) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// =============================================================================
// takeString test
// =============================================================================

TEST_F(ObjectTest_81, TakeString_81) {
    Object obj(std::make_unique<GooString>("take me"));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "take me");
}

// =============================================================================
// getNameString test
// =============================================================================

TEST_F(ObjectTest_81, GetNameString_81) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// =============================================================================
// Multiple moves test
// =============================================================================

TEST_F(ObjectTest_81, MultipleMoveAssignments_81) {
    Object obj1(1);
    Object obj2(2.0);
    Object obj3(true);

    obj3 = std::move(obj2);
    EXPECT_TRUE(obj3.isReal());
    EXPECT_DOUBLE_EQ(obj3.getReal(), 2.0);

    obj3 = std::move(obj1);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 1);
}

// =============================================================================
// Deep copy test
// =============================================================================

TEST_F(ObjectTest_81, DeepCopyInt_81) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_81, DeepCopyArray_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isArray());
    EXPECT_EQ(deep.arrayGetLength(), 2);
    EXPECT_EQ(deep.arrayGet(0).getInt(), 10);
    EXPECT_EQ(deep.arrayGet(1).getInt(), 20);
}

// =============================================================================
// Type cross-check boundary tests
// =============================================================================

TEST_F(ObjectTest_81, ErrorIsNotEOF_81) {
    Object err = Object::error();
    EXPECT_FALSE(err.isEOF());
    EXPECT_FALSE(err.isNone());
    EXPECT_FALSE(err.isNull());
}

TEST_F(ObjectTest_81, EOFIsNotError_81) {
    Object eof = Object::eof();
    EXPECT_FALSE(eof.isError());
    EXPECT_FALSE(eof.isNone());
    EXPECT_FALSE(eof.isNull());
}

TEST_F(ObjectTest_81, NoneIsNotNull_81) {
    Object none;
    EXPECT_TRUE(none.isNone());
    EXPECT_FALSE(none.isNull());
    EXPECT_FALSE(none.isError());
    EXPECT_FALSE(none.isEOF());
}

// =============================================================================
// Dict with multiple entries
// =============================================================================

TEST_F(ObjectTest_81, DictMultipleEntries_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2.5));
    obj.dictAdd("C", Object(true));
    obj.dictAdd("D", Object(objName, "TestName"));

    EXPECT_EQ(obj.dictGetLength(), 4);
    EXPECT_EQ(obj.dictLookup("A").getInt(), 1);
    EXPECT_DOUBLE_EQ(obj.dictLookup("B").getReal(), 2.5);
    EXPECT_TRUE(obj.dictLookup("C").getBool());
    EXPECT_STREQ(obj.dictLookup("D").getName(), "TestName");
}

// =============================================================================
// Array with mixed types
// =============================================================================

TEST_F(ObjectTest_81, ArrayMixedTypes_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    obj.arrayAdd(Object::null());

    EXPECT_EQ(obj.arrayGetLength(), 4);
    EXPECT_TRUE(obj.arrayGet(0).isInt());
    EXPECT_TRUE(obj.arrayGet(1).isReal());
    EXPECT_TRUE(obj.arrayGet(2).isBool());
    EXPECT_TRUE(obj.arrayGet(3).isNull());
}

// =============================================================================
// getArray and getDict tests
// =============================================================================

TEST_F(ObjectTest_81, GetArrayReturnsNonNull_81) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_NE(obj.getArray(), nullptr);
}

TEST_F(ObjectTest_81, GetDictReturnsNonNull_81) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_NE(obj.getDict(), nullptr);
}

// =============================================================================
// Int boundary values
// =============================================================================

TEST_F(ObjectTest_81, IntMaxValue_81) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_81, IntMinValue_81) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_81, Int64MaxValue_81) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_81, Int64MinValue_81) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}
