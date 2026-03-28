#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "GooString.h"

// Test fixture
class ObjectTest_70 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(ObjectTest_70, DefaultConstructorCreatesNoneType_70) {
    Object obj;
    EXPECT_EQ(obj.getType(), objNone);
    EXPECT_TRUE(obj.isNone());
}

// ==================== Bool Constructor Tests ====================

TEST_F(ObjectTest_70, BoolConstructorTrue_70) {
    Object obj(true);
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_70, BoolConstructorFalse_70) {
    Object obj(false);
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// ==================== Int Constructor Tests ====================

TEST_F(ObjectTest_70, IntConstructor_70) {
    Object obj(42);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_70, IntConstructorZero_70) {
    Object obj(0);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_70, IntConstructorNegative_70) {
    Object obj(-100);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_70, IntIsNum_70) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_70, IntIsIntOrInt64_70) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// ==================== Real Constructor Tests ====================

TEST_F(ObjectTest_70, RealConstructor_70) {
    Object obj(3.14);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_70, RealConstructorZero_70) {
    Object obj(0.0);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_70, RealIsNum_70) {
    Object obj(2.718);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_70, RealConstructorNegative_70) {
    Object obj(-1.5);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

// ==================== Int64 Constructor Tests ====================

TEST_F(ObjectTest_70, Int64Constructor_70) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_70, Int64IsIntOrInt64_70) {
    long long val = 123456789LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== String Constructor Tests ====================

TEST_F(ObjectTest_70, StringConstructorFromGooString_70) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_70, StringConstructorFromStdString_70) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ==================== Name Constructor Tests ====================

TEST_F(ObjectTest_70, NameConstructor_70) {
    Object obj(objName, "TestName");
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_70, NameIsNameMatching_70) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_70, NameGetNameString_70) {
    Object obj(objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// ==================== Cmd Constructor Tests ====================

TEST_F(ObjectTest_70, CmdConstructor_70) {
    Object obj(objCmd, "q");
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_70, CmdIsCmdMatching_70) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== HexString Constructor Tests ====================

TEST_F(ObjectTest_70, HexStringConstructor_70) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_TRUE(obj.isHexString());
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_70, NullStaticFactory_70) {
    Object obj = Object::null();
    EXPECT_EQ(obj.getType(), objNull);
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_70, EofStaticFactory_70) {
    Object obj = Object::eof();
    EXPECT_EQ(obj.getType(), objEOF);
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_70, ErrorStaticFactory_70) {
    Object obj = Object::error();
    EXPECT_EQ(obj.getType(), objError);
    EXPECT_TRUE(obj.isError());
}

// ==================== Type Checking - Negative Cases ====================

TEST_F(ObjectTest_70, IntIsNotBool_70) {
    Object obj(42);
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

TEST_F(ObjectTest_70, BoolIsNotOtherTypes_70) {
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
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_70, NullIsNotOtherTypes_70) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ==================== Move Constructor Tests ====================

TEST_F(ObjectTest_70, MoveConstructor_70) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_EQ(obj2.getType(), objInt);
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_70, MoveAssignment_70) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_EQ(obj2.getType(), objInt);
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_70, SetToNull_70) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// ==================== copy Tests ====================

TEST_F(ObjectTest_70, CopyInt_70) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objInt);
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_70, CopyBool_70) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objBool);
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_70, CopyReal_70) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objReal);
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_70, CopyNull_70) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_70, CopyName_70) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

TEST_F(ObjectTest_70, CopyString_70) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_70, GetNumWithOkInt_70) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_70, GetNumWithOkReal_70) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== getNumWithDefaultValue ====================

TEST_F(ObjectTest_70, GetNumWithDefaultValueInt_70) {
    Object obj(42);
    double val = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_70, GetNumWithDefaultValueNonNum_70) {
    Object obj = Object::null();
    double val = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(val, 99.0);
}

// ==================== getBoolWithDefaultValue ====================

TEST_F(ObjectTest_70, GetBoolWithDefaultValueTrue_70) {
    Object obj(true);
    bool val = obj.getBoolWithDefaultValue(false);
    EXPECT_TRUE(val);
}

TEST_F(ObjectTest_70, GetBoolWithDefaultValueNonBool_70) {
    Object obj(42);
    bool val = obj.getBoolWithDefaultValue(true);
    EXPECT_TRUE(val);
}

TEST_F(ObjectTest_70, GetBoolWithDefaultValueNonBoolFalse_70) {
    Object obj(42);
    bool val = obj.getBoolWithDefaultValue(false);
    EXPECT_FALSE(val);
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_70, GetTypeNameBool_70) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_70, GetTypeNameInt_70) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_70, GetTypeNameNull_70) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_70, GetTypeNameNone_70) {
    Object obj;
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_70, ArrayConstructorAndType_70) {
    // We need an XRef* for Array but let's try with nullptr if possible
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_70, ArrayGetLength_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_70, ArrayAddAndGetLength_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_70, ArrayAddMultipleAndGet_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 10);

    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 20);

    Object elem2 = obj.arrayGet(2);
    EXPECT_TRUE(elem2.isInt());
    EXPECT_EQ(elem2.getInt(), 30);
}

TEST_F(ObjectTest_70, ArrayGetNF_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_70, ArrayRemove_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_EQ(elem.getInt(), 20);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_70, DictConstructorAndType_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getDict(), dict);
}

TEST_F(ObjectTest_70, DictGetLengthEmpty_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_70, DictAddAndLookup_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_70, DictSetOverwrite_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_70, DictRemove_70) {
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

TEST_F(ObjectTest_70, DictGetKey_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_70, DictGetVal_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_70, DictGetValNF_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_70, DictLookupNF_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_70, DictLookupNonExistentKey_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_70, DictAddMultipleEntries_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_70, TakeString_70) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== Boundary: Large Int ====================

TEST_F(ObjectTest_70, LargeIntValue_70) {
    int largeVal = 2147483647; // INT_MAX
    Object obj(largeVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), largeVal);
}

TEST_F(ObjectTest_70, MinIntValue_70) {
    int minVal = -2147483647 - 1; // INT_MIN
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), minVal);
}

// ==================== Move semantics - source becomes dead/none ====================

TEST_F(ObjectTest_70, MoveConstructorSourceBecomesNone_70) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // After move, obj1 should be in a valid but unspecified state
    // Typically it becomes objNone or objDead
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_70, MoveAssignmentSourceBecomesNone_70) {
    Object obj1(3.14);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

// ==================== Error / EOF / None type checks ====================

TEST_F(ObjectTest_70, ErrorType_70) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_70, EOFType_70) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_70, NoneType_70) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
}

// ==================== deepCopy Tests ====================

TEST_F(ObjectTest_70, DeepCopyInt_70) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_70, DeepCopyString_70) {
    auto gs = std::make_unique<GooString>("test");
    Object obj(std::move(gs));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
}

// ==================== Real edge cases ====================

TEST_F(ObjectTest_70, RealNegativeZero_70) {
    Object obj(-0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_70, RealVerySmall_70) {
    Object obj(1e-300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-300);
}

// ==================== Int64 edge cases ====================

TEST_F(ObjectTest_70, Int64Zero_70) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

TEST_F(ObjectTest_70, Int64Negative_70) {
    long long val = -9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== print Tests (just ensure no crash) ====================

TEST_F(ObjectTest_70, PrintInt_70) {
    Object obj(42);
    // Just verify it doesn't crash when printing to stdout
    obj.print(stdout);
}

TEST_F(ObjectTest_70, PrintNull_70) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_70, PrintBool_70) {
    Object obj(true);
    obj.print(stdout);
}

TEST_F(ObjectTest_70, PrintName_70) {
    Object obj(objName, "TestName");
    obj.print(stdout);
}

// ==================== Destructor / cleanup (no crash) ====================

TEST_F(ObjectTest_70, DestructorDoesNotCrashForInt_70) {
    { Object obj(42); }
    SUCCEED();
}

TEST_F(ObjectTest_70, DestructorDoesNotCrashForString_70) {
    { Object obj(std::make_unique<GooString>("test")); }
    SUCCEED();
}

TEST_F(ObjectTest_70, DestructorDoesNotCrashForArray_70) {
    { Object obj(new Array(nullptr)); }
    SUCCEED();
}

TEST_F(ObjectTest_70, DestructorDoesNotCrashForDict_70) {
    { Object obj(new Dict(nullptr)); }
    SUCCEED();
}

// ==================== Empty name and cmd ====================

TEST_F(ObjectTest_70, EmptyNameString_70) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_70, EmptyCmdString_70) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Dict with string values ====================

TEST_F(ObjectTest_70, DictWithStringValues_70) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Name", Object(objName, "Test"));
    Object val = obj.dictLookup("Name");
    EXPECT_TRUE(val.isName());
    EXPECT_STREQ(val.getName(), "Test");
}

// ==================== Array with mixed types ====================

TEST_F(ObjectTest_70, ArrayWithMixedTypes_70) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    obj.arrayAdd(Object::null());

    EXPECT_EQ(obj.arrayGetLength(), 4);

    Object e0 = obj.arrayGet(0);
    EXPECT_TRUE(e0.isInt());

    Object e1 = obj.arrayGet(1);
    EXPECT_TRUE(e1.isReal());

    Object e2 = obj.arrayGet(2);
    EXPECT_TRUE(e2.isBool());

    Object e3 = obj.arrayGet(3);
    EXPECT_TRUE(e3.isNull());
}
