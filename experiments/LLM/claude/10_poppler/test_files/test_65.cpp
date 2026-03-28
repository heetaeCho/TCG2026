#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_65 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(ObjectTest_65, DefaultConstructorCreatesNoneType_65) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// ==================== Static Factory Method Tests ====================

TEST_F(ObjectTest_65, NullFactoryCreatesNullObject_65) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_65, EofFactoryCreatesEofObject_65) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_65, ErrorFactoryCreatesErrorObject_65) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Bool Constructor Tests ====================

TEST_F(ObjectTest_65, BoolConstructorTrue_65) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_65, BoolConstructorFalse_65) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// ==================== Int Constructor Tests ====================

TEST_F(ObjectTest_65, IntConstructorPositive_65) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_65, IntConstructorZero_65) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_65, IntConstructorNegative_65) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_65, IntIsNum_65) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_65, IntGetNum_65) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_65, IntGetIntOrInt64_65) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// ==================== Real Constructor Tests ====================

TEST_F(ObjectTest_65, RealConstructorPositive_65) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_65, RealConstructorZero_65) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_65, RealConstructorNegative_65) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_65, RealIsNum_65) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_65, RealGetNum_65) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== Int64 Constructor Tests ====================

TEST_F(ObjectTest_65, Int64Constructor_65) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_65, Int64IsIntOrInt64_65) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_65, Int64IsNum_65) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_TRUE(obj.isNum());
}

// ==================== String Constructor Tests ====================

TEST_F(ObjectTest_65, StringConstructorFromGooString_65) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_65, StringConstructorFromStdString_65) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ==================== Name Constructor Tests ====================

TEST_F(ObjectTest_65, NameConstructor_65) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_65, NameIsNameWithMatchingString_65) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
}

TEST_F(ObjectTest_65, NameIsNameWithNonMatchingString_65) {
    Object obj(objName, "Type");
    EXPECT_FALSE(obj.isName("NotType"));
}

TEST_F(ObjectTest_65, NameGetNameString_65) {
    Object obj(objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// ==================== Cmd Constructor Tests ====================

TEST_F(ObjectTest_65, CmdConstructor_65) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_65, CmdIsCmdWithMatchingString_65) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_65, CmdIsCmdWithNonMatchingString_65) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== HexString Constructor Tests ====================

TEST_F(ObjectTest_65, HexStringConstructor_65) {
    Object obj(objHexString, "ABCDEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Type Check Negative Tests ====================

TEST_F(ObjectTest_65, IntIsNotBool_65) {
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

TEST_F(ObjectTest_65, BoolIsNotOtherTypes_65) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_65, NullIsNotOtherTypes_65) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ==================== Move Constructor Tests ====================

TEST_F(ObjectTest_65, MoveConstructor_65) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically None or Dead)
}

// ==================== Move Assignment Tests ====================

TEST_F(ObjectTest_65, MoveAssignment_65) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_65, SetToNullFromInt_65) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_65, SetToNullFromBool_65) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_65, CopyInt_65) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_65, CopyBool_65) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_65, CopyReal_65) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_65, CopyNull_65) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_65, CopyName_65) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

TEST_F(ObjectTest_65, CopyString_65) {
    Object obj(std::string("hello"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_65, GetTypeNameBool_65) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_65, GetTypeNameInt_65) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_65, GetTypeNameNull_65) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_65, GetTypeNameNone_65) {
    Object obj;
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_65, GetNumWithDefaultValueForInt_65) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_65, GetNumWithDefaultValueForReal_65) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_65, GetNumWithDefaultValueForNonNumeric_65) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_65, GetNumWithDefaultValueForBool_65) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(77.7), 77.7);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_65, GetBoolWithDefaultValueForBoolTrue_65) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_65, GetBoolWithDefaultValueForBoolFalse_65) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_65, GetBoolWithDefaultValueForNonBool_65) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_65, GetBoolWithDefaultValueForNonBoolFalse_65) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_65, ArrayConstructorAndBasicOps_65) {
    // Create an Array object - need to pass an Array pointer
    // Array requires an XRef, passing nullptr for basic test
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_65, ArrayAddAndGetLength_65) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_65, ArrayGetElement_65) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(100));
    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 42);
    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 100);
}

TEST_F(ObjectTest_65, ArrayGetNF_65) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elemNF = obj.arrayGetNF(0);
    EXPECT_TRUE(elemNF.isInt());
    EXPECT_EQ(elemNF.getInt(), 42);
}

TEST_F(ObjectTest_65, ArrayRemoveElement_65) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object elem0 = obj.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 10);
    Object elem1 = obj.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 30);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_65, DictConstructorAndBasicOps_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_65, DictAddAndLookup_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_65, DictSetOverwritesValue_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_65, DictRemove_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_65, DictLookupNonExistentKey_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_65, DictGetKey_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    EXPECT_STREQ(obj.dictGetKey(0), "mykey");
}

TEST_F(ObjectTest_65, DictGetVal_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_65, DictGetValNF_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_65, DictLookupNF_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("testkey", Object(77));
    const Object &val = obj.dictLookupNF("testkey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// ==================== Deep Copy Tests ====================

TEST_F(ObjectTest_65, DeepCopyInt_65) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_65, DeepCopyString_65) {
    Object obj(std::string("deep copy test"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
}

// ==================== Edge Cases ====================

TEST_F(ObjectTest_65, IntMaxValue_65) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_65, IntMinValue_65) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_65, Int64MaxValue_65) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_65, RealVerySmallValue_65) {
    Object obj(1e-300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-300);
}

TEST_F(ObjectTest_65, RealVeryLargeValue_65) {
    Object obj(1e300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e300);
}

TEST_F(ObjectTest_65, EmptyNameString_65) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_65, EmptyCmdString_65) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Multiple Move Operations ====================

TEST_F(ObjectTest_65, MultipleMoves_65) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    Object obj3;
    obj3 = std::move(obj2);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_65, GetNumWithOkForInt_65) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_65, GetNumWithOkForReal_65) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_65, TakeString_65) {
    Object obj(std::string("take me"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== Dict with Type Tests ====================

TEST_F(ObjectTest_65, DictIsWithType_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(obj.dictIs("Catalog"));
    EXPECT_FALSE(obj.dictIs("Page"));
}

TEST_F(ObjectTest_65, IsDictWithType_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Type", Object(objName, "Font"));
    EXPECT_TRUE(obj.isDict("Font"));
    EXPECT_FALSE(obj.isDict("Page"));
}

// ==================== Print Tests ====================

TEST_F(ObjectTest_65, PrintIntToStdout_65) {
    Object obj(42);
    // Just ensure print doesn't crash
    testing::internal::CaptureStdout();
    obj.print(stdout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(ObjectTest_65, PrintNullToStdout_65) {
    Object obj = Object::null();
    testing::internal::CaptureStdout();
    obj.print(stdout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

// ==================== Array with various types ====================

TEST_F(ObjectTest_65, ArrayWithMixedTypes_65) {
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

// ==================== Dict with multiple keys ====================

TEST_F(ObjectTest_65, DictMultipleKeys_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object va = obj.dictLookup("a");
    EXPECT_EQ(va.getInt(), 1);
    Object vb = obj.dictLookup("b");
    EXPECT_EQ(vb.getInt(), 2);
    Object vc = obj.dictLookup("c");
    EXPECT_EQ(vc.getInt(), 3);
}

// ==================== Accessor pointer retrieval ====================

TEST_F(ObjectTest_65, GetArrayPointer_65) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_65, GetDictPointer_65) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}
