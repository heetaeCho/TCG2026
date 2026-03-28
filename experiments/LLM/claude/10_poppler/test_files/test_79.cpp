#include <gtest/gtest.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"

// Helper to create an XRef-less Array
// We need a minimal setup for Array and Dict objects

class ObjectTest_79 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for default constructor and type checks
// =============================================================================

TEST_F(ObjectTest_79, DefaultConstructorIsNone_79) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_79, NullObjectIsNull_79) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_79, EofObjectIsEOF_79) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_79, ErrorObjectIsError_79) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// Tests for bool type
// =============================================================================

TEST_F(ObjectTest_79, BoolConstructorTrue_79) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_79, BoolConstructorFalse_79) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_79, BoolIsNotInt_79) {
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
// Tests for int type
// =============================================================================

TEST_F(ObjectTest_79, IntConstructor_79) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_79, IntIsNum_79) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_79, IntIsIntOrInt64_79) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_79, IntNegativeValue_79) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_79, IntZeroValue_79) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// =============================================================================
// Tests for real (double) type
// =============================================================================

TEST_F(ObjectTest_79, RealConstructor_79) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_79, RealIsNum_79) {
    Object obj(2.718);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_79, RealIsNotInt_79) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_79, RealZero_79) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_79, RealNegative_79) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

// =============================================================================
// Tests for int64 type
// =============================================================================

TEST_F(ObjectTest_79, Int64Constructor_79) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_79, Int64IsIntOrInt64_79) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_79, Int64IsNotInt_79) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_FALSE(obj.isInt());
}

// =============================================================================
// Tests for string type
// =============================================================================

TEST_F(ObjectTest_79, StringConstructor_79) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_79, StdStringConstructor_79) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// =============================================================================
// Tests for hex string type
// =============================================================================

TEST_F(ObjectTest_79, HexStringConstructor_79) {
    Object obj(ObjType::objHexString, std::string_view("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Tests for name type
// =============================================================================

TEST_F(ObjectTest_79, NameConstructor_79) {
    Object obj(ObjType::objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_79, NameMatchesSpecificName_79) {
    Object obj(ObjType::objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
    EXPECT_FALSE(obj.isName("Page"));
}

TEST_F(ObjectTest_79, NameGetNameString_79) {
    Object obj(ObjType::objName, "MyName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "MyName");
}

// =============================================================================
// Tests for cmd type
// =============================================================================

TEST_F(ObjectTest_79, CmdConstructor_79) {
    Object obj(ObjType::objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_79, CmdMatchesSpecificCmd_79) {
    Object obj(ObjType::objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// =============================================================================
// Tests for isArray
// =============================================================================

TEST_F(ObjectTest_79, IsArrayReturnsFalseForNonArray_79) {
    Object obj(42);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForNull_79) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForBool_79) {
    Object obj(true);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForReal_79) {
    Object obj(1.0);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForString_79) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForNone_79) {
    Object obj;
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForError_79) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, IsArrayReturnsFalseForEOF_79) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_79, ArrayConstructorIsArray_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.getArray(), arr);
}

// =============================================================================
// Tests for array operations
// =============================================================================

TEST_F(ObjectTest_79, ArrayGetLength_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_79, ArrayAddAndGetLength_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_79, ArrayGetElement_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));
    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 42);
    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 99);
}

TEST_F(ObjectTest_79, ArrayGetNF_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(7));
    const Object &elemNF = obj.arrayGetNF(0);
    EXPECT_TRUE(elemNF.isInt());
    EXPECT_EQ(elemNF.getInt(), 7);
}

TEST_F(ObjectTest_79, ArrayRemove_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object elem0 = obj.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 1);
    Object elem1 = obj.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 3);
}

// =============================================================================
// Tests for dict type
// =============================================================================

TEST_F(ObjectTest_79, DictConstructorIsDict_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.getDict(), dict);
}

TEST_F(ObjectTest_79, IsDictReturnsFalseForNonDict_79) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_79, DictGetLength_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_79, DictAddAndLookup_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_79, DictSetOverwrite_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_79, DictRemove_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_79, DictGetKey_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Alpha", Object(1));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "Alpha");
}

TEST_F(ObjectTest_79, DictGetVal_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_79, DictGetValNF_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(77));
    const Object &valNF = obj.dictGetValNF(0);
    EXPECT_TRUE(valNF.isInt());
    EXPECT_EQ(valNF.getInt(), 77);
}

TEST_F(ObjectTest_79, DictLookupNF_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Foo", Object(33));
    const Object &valNF = obj.dictLookupNF("Foo");
    EXPECT_TRUE(valNF.isInt());
    EXPECT_EQ(valNF.getInt(), 33);
}

TEST_F(ObjectTest_79, DictLookupNonExistentKey_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

// =============================================================================
// Tests for move semantics
// =============================================================================

TEST_F(ObjectTest_79, MoveConstructor_79) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_79, MoveAssignment_79) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// =============================================================================
// Tests for copy
// =============================================================================

TEST_F(ObjectTest_79, CopyInt_79) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_79, CopyBool_79) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_79, CopyReal_79) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_79, CopyNull_79) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// =============================================================================
// Tests for setToNull
// =============================================================================

TEST_F(ObjectTest_79, SetToNull_79) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Tests for getNumWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_79, GetNumWithDefaultValueReturnsNumForInt_79) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_79, GetNumWithDefaultValueReturnsNumForReal_79) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_79, GetNumWithDefaultValueReturnsDefaultForNonNum_79) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

// =============================================================================
// Tests for getBoolWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_79, GetBoolWithDefaultValueReturnsBoolForBool_79) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_79, GetBoolWithDefaultValueReturnsDefaultForNonBool_79) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// =============================================================================
// Tests for getTypeName
// =============================================================================

TEST_F(ObjectTest_79, GetTypeNameForInt_79) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_79, GetTypeNameForNull_79) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// =============================================================================
// Tests for getNum with ok parameter
// =============================================================================

TEST_F(ObjectTest_79, GetNumWithOkForInt_79) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

TEST_F(ObjectTest_79, GetNumWithOkForReal_79) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// =============================================================================
// Tests for mutual exclusivity of type checks
// =============================================================================

TEST_F(ObjectTest_79, OnlyOneTypeCheckTrueForInt_79) {
    Object obj(42);
    int trueCount = 0;
    trueCount += obj.isBool() ? 1 : 0;
    trueCount += obj.isInt() ? 1 : 0;
    trueCount += obj.isReal() ? 1 : 0;
    trueCount += obj.isString() ? 1 : 0;
    trueCount += obj.isHexString() ? 1 : 0;
    trueCount += obj.isName() ? 1 : 0;
    trueCount += obj.isNull() ? 1 : 0;
    trueCount += obj.isArray() ? 1 : 0;
    trueCount += obj.isDict() ? 1 : 0;
    trueCount += obj.isStream() ? 1 : 0;
    trueCount += obj.isRef() ? 1 : 0;
    trueCount += obj.isCmd() ? 1 : 0;
    trueCount += obj.isError() ? 1 : 0;
    trueCount += obj.isEOF() ? 1 : 0;
    trueCount += obj.isNone() ? 1 : 0;
    trueCount += obj.isInt64() ? 1 : 0;
    EXPECT_EQ(trueCount, 1);
}

TEST_F(ObjectTest_79, OnlyOneTypeCheckTrueForBool_79) {
    Object obj(false);
    int trueCount = 0;
    trueCount += obj.isBool() ? 1 : 0;
    trueCount += obj.isInt() ? 1 : 0;
    trueCount += obj.isReal() ? 1 : 0;
    trueCount += obj.isString() ? 1 : 0;
    trueCount += obj.isHexString() ? 1 : 0;
    trueCount += obj.isName() ? 1 : 0;
    trueCount += obj.isNull() ? 1 : 0;
    trueCount += obj.isArray() ? 1 : 0;
    trueCount += obj.isDict() ? 1 : 0;
    trueCount += obj.isStream() ? 1 : 0;
    trueCount += obj.isRef() ? 1 : 0;
    trueCount += obj.isCmd() ? 1 : 0;
    trueCount += obj.isError() ? 1 : 0;
    trueCount += obj.isEOF() ? 1 : 0;
    trueCount += obj.isNone() ? 1 : 0;
    trueCount += obj.isInt64() ? 1 : 0;
    EXPECT_EQ(trueCount, 1);
}

// =============================================================================
// Tests for takeString
// =============================================================================

TEST_F(ObjectTest_79, TakeString_79) {
    Object obj(std::make_unique<GooString>("hello world"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// =============================================================================
// Tests for multiple dict operations
// =============================================================================

TEST_F(ObjectTest_79, DictMultipleKeys_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object valA = obj.dictLookup("A");
    EXPECT_EQ(valA.getInt(), 1);
    Object valB = obj.dictLookup("B");
    EXPECT_EQ(valB.getInt(), 2);
    Object valC = obj.dictLookup("C");
    EXPECT_EQ(valC.getInt(), 3);
}

// =============================================================================
// Test deep copy of array
// =============================================================================

TEST_F(ObjectTest_79, DeepCopyArray_79) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));

    Object deepCopied = obj.deepCopy();
    EXPECT_TRUE(deepCopied.isArray());
    EXPECT_EQ(deepCopied.arrayGetLength(), 2);

    Object elem0 = deepCopied.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 10);
    Object elem1 = deepCopied.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 20);
}

// =============================================================================
// Test deep copy of dict
// =============================================================================

TEST_F(ObjectTest_79, DeepCopyDict_79) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("X", Object(42));

    Object deepCopied = obj.deepCopy();
    EXPECT_TRUE(deepCopied.isDict());
    EXPECT_EQ(deepCopied.dictGetLength(), 1);

    Object val = deepCopied.dictLookup("X");
    EXPECT_EQ(val.getInt(), 42);
}
