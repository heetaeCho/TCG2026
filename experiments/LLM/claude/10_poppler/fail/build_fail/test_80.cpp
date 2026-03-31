#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "Object.h"
#include "Array.h"
#include "Dict.h"

// Test fixture for Object tests
class ObjectTest_80 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== Type checking tests ====================

TEST_F(ObjectTest_80, DefaultConstructorIsNone_80) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_80, BoolConstructor_80) {
    Object objTrue(true);
    EXPECT_TRUE(objTrue.isBool());
    EXPECT_TRUE(objTrue.getBool());
    EXPECT_EQ(objTrue.getType(), objBool);

    Object objFalse(false);
    EXPECT_TRUE(objFalse.isBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectTest_80, IntConstructor_80) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_80, IntConstructorNegative_80) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_80, IntConstructorZero_80) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_80, RealConstructor_80) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_TRUE(obj.isNum());
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_80, RealConstructorZero_80) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_80, Int64Constructor_80) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_80, StringConstructor_80) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_80, NameConstructor_80) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_80, CmdConstructor_80) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

TEST_F(ObjectTest_80, NullObject_80) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_80, EofObject_80) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_80, ErrorObject_80) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== isDict tests (the focus method) ====================

TEST_F(ObjectTest_80, IsDictReturnsTrueForDict_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForNull_80) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForBool_80) {
    Object obj(true);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForInt_80) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForReal_80) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForString_80) {
    Object obj(std::string("test"));
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForName_80) {
    Object obj(objName, "name");
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForArray_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isArray());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForCmd_80) {
    Object obj(objCmd, "cmd");
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForError_80) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForEOF_80) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForNone_80) {
    Object obj;
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_80, IsDictReturnsFalseForInt64_80) {
    Object obj((long long)12345);
    EXPECT_FALSE(obj.isDict());
}

// ==================== Negative type checks ====================

TEST_F(ObjectTest_80, DictIsNotOtherTypes_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNum());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isDict());
}

// ==================== Move semantics tests ====================

TEST_F(ObjectTest_80, MoveConstructor_80) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_80, MoveAssignment_80) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_80, MoveDictObject_80) {
    Dict *dict = new Dict(nullptr);
    Object obj1(dict);
    EXPECT_TRUE(obj1.isDict());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isDict());
}

// ==================== setToNull tests ====================

TEST_F(ObjectTest_80, SetToNull_80) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_80, SetToNullOnDict_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isDict());
}

// ==================== getNum tests ====================

TEST_F(ObjectTest_80, GetNumFromInt_80) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_80, GetNumFromReal_80) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

// ==================== getNumWithDefaultValue tests ====================

TEST_F(ObjectTest_80, GetNumWithDefaultValueFromInt_80) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_80, GetNumWithDefaultValueFromNonNumeric_80) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ==================== getBoolWithDefaultValue tests ====================

TEST_F(ObjectTest_80, GetBoolWithDefaultValueFromBool_80) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_80, GetBoolWithDefaultValueFromNonBool_80) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Name comparison tests ====================

TEST_F(ObjectTest_80, IsNameWithMatchingString_80) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_80, IsNameOnNonNameObject_80) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ==================== Cmd comparison tests ====================

TEST_F(ObjectTest_80, IsCmdWithMatchingString_80) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_80, IsCmdOnNonCmdObject_80) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ==================== Copy tests ====================

TEST_F(ObjectTest_80, CopyInt_80) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_80, CopyBool_80) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_80, CopyNull_80) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_80, CopyReal_80) {
    Object obj(1.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 1.5);
}

// ==================== Dict operations tests ====================

TEST_F(ObjectTest_80, DictGetLength_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_80, DictAddAndLookup_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_80, DictSetOverwritesValue_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(99));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_80, DictRemove_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_80, DictLookupNonExistentKey_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_80, DictGetKey_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(10));
    EXPECT_STREQ(obj.dictGetKey(0), "mykey");
}

TEST_F(ObjectTest_80, DictGetVal_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// ==================== Array operations tests ====================

TEST_F(ObjectTest_80, ArrayGetLength_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_80, ArrayAddAndGet_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object val = obj.arrayGet(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_80, ArrayRemove_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_80, ArrayMultipleElements_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    Object v0 = obj.arrayGet(0);
    Object v1 = obj.arrayGet(1);
    Object v2 = obj.arrayGet(2);
    EXPECT_EQ(v0.getInt(), 10);
    EXPECT_EQ(v1.getInt(), 20);
    EXPECT_EQ(v2.getInt(), 30);
}

// ==================== getTypeName test ====================

TEST_F(ObjectTest_80, GetTypeName_80) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_80, GetTypeNameForDict_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== HexString test ====================

TEST_F(ObjectTest_80, HexStringConstructor_80) {
    Object obj(objHexString, "ABCD");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== getDict on dict object ====================

TEST_F(ObjectTest_80, GetDictReturnsNonNull_80) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_NE(obj.getDict(), nullptr);
}

// ==================== getArray on array object ====================

TEST_F(ObjectTest_80, GetArrayReturnsNonNull_80) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_NE(obj.getArray(), nullptr);
}

// ==================== Boundary: Int max/min ====================

TEST_F(ObjectTest_80, IntMaxValue_80) {
    Object obj(INT_MAX);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

TEST_F(ObjectTest_80, IntMinValue_80) {
    Object obj(INT_MIN);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

// ==================== IntOrInt64 tests ====================

TEST_F(ObjectTest_80, GetIntOrInt64FromInt_80) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_80, GetIntOrInt64FromInt64_80) {
    long long val = 1234567890123LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== isNum tests ====================

TEST_F(ObjectTest_80, IsNumForInt_80) {
    Object obj(1);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_80, IsNumForReal_80) {
    Object obj(1.0);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_80, IsNumForNonNumeric_80) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// ==================== Empty name tests ====================

TEST_F(ObjectTest_80, EmptyName_80) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Multiple dict operations ====================

TEST_F(ObjectTest_80, DictMultipleAdditions_80) {
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
