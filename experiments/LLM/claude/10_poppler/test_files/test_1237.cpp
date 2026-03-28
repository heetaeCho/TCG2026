#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_1237 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Type checking tests ====================

TEST_F(ObjectTest_1237, DefaultConstructorCreatesNoneObject_1237) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_1237, NullObjectIsNull_1237) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_1237, ErrorObjectIsError_1237) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

TEST_F(ObjectTest_1237, EofObjectIsEOF_1237) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// ==================== Bool tests ====================

TEST_F(ObjectTest_1237, BoolObjectTrue_1237) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_1237, BoolObjectFalse_1237) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_1237, BoolObjectIsNotInt_1237) {
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
}

// ==================== Int tests ====================

TEST_F(ObjectTest_1237, IntObjectCreation_1237) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_1237, IntObjectNegativeValue_1237) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_1237, IntObjectZero_1237) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_1237, IntObjectIsNum_1237) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_1237, IntGetNum_1237) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

// ==================== Real tests ====================

TEST_F(ObjectTest_1237, RealObjectCreation_1237) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_1237, RealObjectIsNum_1237) {
    Object obj(2.5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.5);
}

TEST_F(ObjectTest_1237, RealObjectNegative_1237) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

TEST_F(ObjectTest_1237, RealObjectZero_1237) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_1237, RealIsNotIntOrInt64_1237) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== Int64 tests ====================

TEST_F(ObjectTest_1237, Int64ObjectCreation_1237) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_1237, Int64ObjectIsIntOrInt64_1237) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_1237, Int64GetIntOrInt64_1237) {
    long long val = 500LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), 500LL);
}

// ==================== Name tests ====================

TEST_F(ObjectTest_1237, NameObjectCreation_1237) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_1237, IsNameWithMatchingName_1237) {
    Object obj(objName, "FooBar");
    EXPECT_TRUE(obj.isName("FooBar"));
}

TEST_F(ObjectTest_1237, IsNameWithNonMatchingName_1237) {
    Object obj(objName, "FooBar");
    EXPECT_FALSE(obj.isName("Baz"));
}

TEST_F(ObjectTest_1237, IsNameOnNonNameObject_1237) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsNameEmptyString_1237) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName(""));
    EXPECT_FALSE(obj.isName("notempty"));
}

TEST_F(ObjectTest_1237, IsNameWithEmptyStringOnNonEmpty_1237) {
    Object obj(objName, "SomeName");
    EXPECT_FALSE(obj.isName(""));
}

TEST_F(ObjectTest_1237, NameGetNameString_1237) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== String tests ====================

TEST_F(ObjectTest_1237, StringObjectCreation_1237) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_1237, HexStringObjectCreation_1237) {
    Object obj(objHexString, "ABCDEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== Cmd tests ====================

TEST_F(ObjectTest_1237, CmdObjectCreation_1237) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_1237, IsCmdWithMatchingCmd_1237) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_1237, IsCmdWithNonMatchingCmd_1237) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_1237, IsCmdOnNonCmdObject_1237) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("BT"));
}

// ==================== Move semantics tests ====================

TEST_F(ObjectTest_1237, MoveConstructor_1237) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, original should be in a valid but unspecified state (typically dead or none)
}

TEST_F(ObjectTest_1237, MoveAssignment_1237) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull tests ====================

TEST_F(ObjectTest_1237, SetToNull_1237) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy tests ====================

TEST_F(ObjectTest_1237, CopyInt_1237) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_1237, CopyBool_1237) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_1237, CopyReal_1237) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_1237, CopyNull_1237) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_1237, CopyName_1237) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== getTypeName tests ====================

TEST_F(ObjectTest_1237, GetTypeNameBool_1237) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_1237, GetTypeNameInt_1237) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_1237, GetTypeNameNull_1237) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== getNumWithDefaultValue tests ====================

TEST_F(ObjectTest_1237, GetNumWithDefaultValueInt_1237) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_1237, GetNumWithDefaultValueReal_1237) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_1237, GetNumWithDefaultValueNonNumeric_1237) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_1237, GetNumWithDefaultValueBool_1237) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(55.0), 55.0);
}

// ==================== getBoolWithDefaultValue tests ====================

TEST_F(ObjectTest_1237, GetBoolWithDefaultValueTrue_1237) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_1237, GetBoolWithDefaultValueFalse_1237) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_1237, GetBoolWithDefaultValueNonBool_1237) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_1237, GetBoolWithDefaultValueNonBoolFalse_1237) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array tests ====================

TEST_F(ObjectTest_1237, ArrayObjectCreation_1237) {
    // Create a simple array using the Array constructor
    // We need an XRef, but for a standalone test we might use nullptr if the implementation allows
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_1237, ArrayGetLength_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_1237, ArrayAddAndGetLength_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_1237, ArrayAddAndGet_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0, 0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_1237, ArrayAddMultipleElements_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_1237, ArrayRemove_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object elem0 = obj.arrayGet(0, 0);
    EXPECT_EQ(elem0.getInt(), 10);
    Object elem1 = obj.arrayGet(1, 0);
    EXPECT_EQ(elem1.getInt(), 30);
}

TEST_F(ObjectTest_1237, ArrayGetNF_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

// ==================== Dict tests ====================

TEST_F(ObjectTest_1237, DictObjectCreation_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_1237, DictGetLengthEmpty_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_1237, DictAddAndLookup_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1", 0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_1237, DictSetOverwrite_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1", 0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_1237, DictRemove_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(99));
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1", 0);
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_1237, DictLookupNonExistentKey_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent", 0);
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_1237, DictGetKey_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_1237, DictGetVal_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_1237, DictGetValNF_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_1237, DictLookupNF_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== Static factory method tests ====================

TEST_F(ObjectTest_1237, NullStaticFactory_1237) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_1237, ErrorStaticFactory_1237) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_1237, EofStaticFactory_1237) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
}

// ==================== Cross-type checks ====================

TEST_F(ObjectTest_1237, IntIsNotBool_1237) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_1237, RealIsNotInt_1237) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_1237, NameIsNotString_1237) {
    Object obj(objName, "test");
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_1237, CmdIsNotName_1237) {
    Object obj(objCmd, "q");
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isString());
}

// ==================== getNum with ok parameter tests ====================

TEST_F(ObjectTest_1237, GetNumWithOkInt_1237) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_1237, GetNumWithOkReal_1237) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Deep copy test ====================

TEST_F(ObjectTest_1237, DeepCopyInt_1237) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_1237, DeepCopyName_1237) {
    Object obj(objName, "DeepName");
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "DeepName");
    EXPECT_TRUE(copied.isName("DeepName"));
}

// ==================== Edge cases ====================

TEST_F(ObjectTest_1237, IsNameCalledOnBoolObject_1237) {
    Object obj(true);
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsNameCalledOnNullObject_1237) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsNameCalledOnRealObject_1237) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsNameCalledOnErrorObject_1237) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsNameCalledOnEofObject_1237) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_1237, IsCmdCalledOnNameObject_1237) {
    Object obj(objName, "test");
    EXPECT_FALSE(obj.isCmd("test"));
}

TEST_F(ObjectTest_1237, IsNameCaseSensitive_1237) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
    EXPECT_FALSE(obj.isName("testname"));
    EXPECT_FALSE(obj.isName("TESTNAME"));
}

TEST_F(ObjectTest_1237, IsNamePartialMatch_1237) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("Test"));
    EXPECT_FALSE(obj.isName("TestNameExtra"));
}

// ==================== Multiple dict operations tests ====================

TEST_F(ObjectTest_1237, DictMultipleAdditions_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object valA = obj.dictLookup("A", 0);
    Object valB = obj.dictLookup("B", 0);
    Object valC = obj.dictLookup("C", 0);
    EXPECT_EQ(valA.getInt(), 1);
    EXPECT_EQ(valB.getInt(), 2);
    EXPECT_EQ(valC.getInt(), 3);
}

// ==================== GetArray and GetDict accessors ====================

TEST_F(ObjectTest_1237, GetArrayAccessor_1237) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_1237, GetDictAccessor_1237) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}
