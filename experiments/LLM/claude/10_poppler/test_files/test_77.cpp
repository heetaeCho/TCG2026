#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_77 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for default constructor and type checks
// =============================================================================

TEST_F(ObjectTest_77, DefaultConstructorCreatesNoneType_77) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_77, DefaultConstructorIsNotBool_77) {
    Object obj;
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_77, DefaultConstructorIsNotInt_77) {
    Object obj;
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_77, DefaultConstructorIsNotName_77) {
    Object obj;
    EXPECT_FALSE(obj.isName());
}

// =============================================================================
// Tests for Bool construction
// =============================================================================

TEST_F(ObjectTest_77, BoolConstructorTrue_77) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_77, BoolConstructorFalse_77) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_77, BoolIsNotInt_77) {
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
// Tests for Int construction
// =============================================================================

TEST_F(ObjectTest_77, IntConstructorPositive_77) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_77, IntConstructorZero_77) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_77, IntConstructorNegative_77) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_77, IntIsNum_77) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 5.0);
}

TEST_F(ObjectTest_77, IntIsIntOrInt64_77) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// =============================================================================
// Tests for Real construction
// =============================================================================

TEST_F(ObjectTest_77, RealConstructorPositive_77) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_77, RealConstructorZero_77) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_77, RealConstructorNegative_77) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_77, RealIsNum_77) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 1.5);
}

TEST_F(ObjectTest_77, RealIsNotInt_77) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

// =============================================================================
// Tests for Int64 construction
// =============================================================================

TEST_F(ObjectTest_77, Int64Constructor_77) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_77, Int64IsIntOrInt64_77) {
    long long val = 999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_77, Int64GetIntOrInt64_77) {
    long long val = 12345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// =============================================================================
// Tests for Name construction
// =============================================================================

TEST_F(ObjectTest_77, NameConstructor_77) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_77, NameIsNameWithMatchingString_77) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
}

TEST_F(ObjectTest_77, NameIsNameWithNonMatchingString_77) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_77, NameIsNotOtherTypes_77) {
    Object obj(objName, "SomeName");
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
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

TEST_F(ObjectTest_77, NameGetNameString_77) {
    Object obj(objName, "Hello");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "Hello");
}

TEST_F(ObjectTest_77, NameEmptyString_77) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// =============================================================================
// Tests for Cmd construction
// =============================================================================

TEST_F(ObjectTest_77, CmdConstructor_77) {
    Object obj(objCmd, "myCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "myCmd");
}

TEST_F(ObjectTest_77, CmdIsCmdWithMatchingString_77) {
    Object obj(objCmd, "test");
    EXPECT_TRUE(obj.isCmd("test"));
}

TEST_F(ObjectTest_77, CmdIsCmdWithNonMatchingString_77) {
    Object obj(objCmd, "test");
    EXPECT_FALSE(obj.isCmd("other"));
}

// =============================================================================
// Tests for Static factory methods
// =============================================================================

TEST_F(ObjectTest_77, NullFactory_77) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_77, EofFactory_77) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_77, ErrorFactory_77) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// Tests for Null type checks
// =============================================================================

TEST_F(ObjectTest_77, NullIsNotBool_77) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
}

// =============================================================================
// Tests for Move semantics
// =============================================================================

TEST_F(ObjectTest_77, MoveConstructor_77) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_77, MoveAssignment_77) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_77, MoveConstructorName_77) {
    Object obj1(objName, "MovedName");
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "MovedName");
}

// =============================================================================
// Tests for setToNull
// =============================================================================

TEST_F(ObjectTest_77, SetToNullFromInt_77) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_77, SetToNullFromBool_77) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_77, SetToNullFromName_77) {
    Object obj(objName, "test");
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Tests for copy
// =============================================================================

TEST_F(ObjectTest_77, CopyInt_77) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_77, CopyBool_77) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_77, CopyReal_77) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_77, CopyName_77) {
    Object obj(objName, "CopyMe");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyMe");
}

TEST_F(ObjectTest_77, CopyNull_77) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_77, CopyError_77) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_77, CopyEof_77) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// =============================================================================
// Tests for getTypeName
// =============================================================================

TEST_F(ObjectTest_77, GetTypeNameBool_77) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_77, GetTypeNameInt_77) {
    Object obj(5);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_77, GetTypeNameNull_77) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_77, GetTypeNameName_77) {
    Object obj(objName, "test");
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// =============================================================================
// Tests for getNumWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_77, GetNumWithDefaultValueFromInt_77) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 10.0);
}

TEST_F(ObjectTest_77, GetNumWithDefaultValueFromReal_77) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_77, GetNumWithDefaultValueFromNonNum_77) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_77, GetNumWithDefaultValueFromBool_77) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// =============================================================================
// Tests for getBoolWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_77, GetBoolWithDefaultValueFromBool_77) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_77, GetBoolWithDefaultValueFromNonBool_77) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_77, GetBoolWithDefaultValueFromNullReturnDefault_77) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// =============================================================================
// Tests for String construction
// =============================================================================

TEST_F(ObjectTest_77, StringConstructorFromStdString_77) {
    std::string s = "hello";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_77, HexStringConstruction_77) {
    Object obj(objHexString, "ABCD");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Tests for Array operations
// =============================================================================

TEST_F(ObjectTest_77, ArrayConstructorAndGetLength_77) {
    // Create an array object
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_77, ArrayAddAndGetLength_77) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_77, ArrayAddMultiple_77) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_77, ArrayGetElement_77) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_77, ArrayGetNF_77) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_77, ArrayRemove_77) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

// =============================================================================
// Tests for Dict operations
// =============================================================================

TEST_F(ObjectTest_77, DictConstructorAndGetLength_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_77, DictAddAndLookup_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_77, DictSetOverwrite_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_77, DictRemove_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_77, DictGetKey_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(5));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_77, DictGetVal_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_77, DictGetValNF_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(55));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_77, DictLookupNF_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("SomeKey", Object(33));
    const Object &val = obj.dictLookupNF("SomeKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 33);
}

TEST_F(ObjectTest_77, DictLookupNonExistent_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_77, DictMultipleEntries_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// =============================================================================
// Tests for isNum behavior
// =============================================================================

TEST_F(ObjectTest_77, IsNumForInt_77) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_77, IsNumForReal_77) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_77, IsNumForBool_77) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_77, IsNumForNull_77) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// =============================================================================
// Tests for getNum with ok parameter
// =============================================================================

TEST_F(ObjectTest_77, GetNumWithOkFromInt_77) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_77, GetNumWithOkFromReal_77) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// =============================================================================
// Tests for deep copy
// =============================================================================

TEST_F(ObjectTest_77, DeepCopyInt_77) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_77, DeepCopyName_77) {
    Object obj(objName, "DeepName");
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "DeepName");
}

// =============================================================================
// Tests for String takeString
// =============================================================================

TEST_F(ObjectTest_77, TakeStringFromStringObject_77) {
    std::string s = "takeMe";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// =============================================================================
// Boundary: Int max/min values
// =============================================================================

TEST_F(ObjectTest_77, IntMaxValue_77) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_77, IntMinValue_77) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_77, Int64MaxValue_77) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_77, Int64MinValue_77) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_77, RealLargeValue_77) {
    Object obj(1e300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e300);
}

TEST_F(ObjectTest_77, RealSmallValue_77) {
    Object obj(1e-300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-300);
}

// =============================================================================
// Tests for print (just ensure it doesn't crash)
// =============================================================================

TEST_F(ObjectTest_77, PrintIntToStdout_77) {
    Object obj(42);
    // Just verify it doesn't crash
    obj.print(stdout);
}

TEST_F(ObjectTest_77, PrintNullToStdout_77) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_77, PrintNameToStdout_77) {
    Object obj(objName, "PrintTest");
    obj.print(stdout);
}

// =============================================================================
// Tests for move semantics with various types
// =============================================================================

TEST_F(ObjectTest_77, MoveAssignmentReal_77) {
    Object obj1(3.14);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

TEST_F(ObjectTest_77, MoveAssignmentBool_77) {
    Object obj1(false);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isBool());
    EXPECT_FALSE(obj2.getBool());
}

TEST_F(ObjectTest_77, MoveAssignmentNull_77) {
    Object obj1 = Object::null();
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isNull());
}

TEST_F(ObjectTest_77, MoveAssignmentError_77) {
    Object obj1 = Object::error();
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isError());
}

// =============================================================================
// Tests for String object
// =============================================================================

TEST_F(ObjectTest_77, StringObjectGetString_77) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    const GooString *gs = obj.getString();
    EXPECT_NE(gs, nullptr);
}

// =============================================================================
// Tests for Cmd type specifics
// =============================================================================

TEST_F(ObjectTest_77, CmdIsNotName_77) {
    Object obj(objCmd, "command");
    EXPECT_FALSE(obj.isName());
    EXPECT_TRUE(obj.isCmd());
}

TEST_F(ObjectTest_77, NameIsNotCmd_77) {
    Object obj(objName, "name");
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isCmd());
}

// =============================================================================
// Tests: Multiple setToNull calls
// =============================================================================

TEST_F(ObjectTest_77, SetToNullMultipleTimes_77) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Tests for Dict with dictIs
// =============================================================================

TEST_F(ObjectTest_77, DictIsWithType_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    // dictIs checks the /Type entry in the dict
    obj.dictAdd("Type", Object(objName, "Page"));
    EXPECT_TRUE(obj.dictIs("Page"));
    EXPECT_FALSE(obj.dictIs("Font"));
}

// =============================================================================
// Tests for isDict with type
// =============================================================================

TEST_F(ObjectTest_77, IsDictWithType_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(obj.isDict("Catalog"));
    EXPECT_FALSE(obj.isDict("Page"));
}

TEST_F(ObjectTest_77, IsDictWithoutTypeEntry_77) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_FALSE(obj.isDict("SomeType"));
}
