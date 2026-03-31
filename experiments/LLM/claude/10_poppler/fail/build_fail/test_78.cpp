#include <gtest/gtest.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "GooString.h"
#include <memory>
#include <string>

// Helper to create a minimal XRef-less environment
// We test only through the public interface of Object.

class ObjectTest_78 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Test default constructor
// ============================================================
TEST_F(ObjectTest_78, DefaultConstructorIsNone_78) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// ============================================================
// Test isNull and null factory
// ============================================================
TEST_F(ObjectTest_78, NullFactoryCreatesNullObject_78) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_78, DefaultConstructedIsNotNull_78) {
    Object obj;
    EXPECT_FALSE(obj.isNull());
}

// ============================================================
// Test setToNull
// ============================================================
TEST_F(ObjectTest_78, SetToNullMakesObjectNull_78) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// ============================================================
// Test Bool
// ============================================================
TEST_F(ObjectTest_78, BoolConstructorTrue_78) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_78, BoolConstructorFalse_78) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), false);
}

TEST_F(ObjectTest_78, BoolIsNotOtherTypes_78) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isName());
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

// ============================================================
// Test Int
// ============================================================
TEST_F(ObjectTest_78, IntConstructor_78) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_78, IntConstructorNegative_78) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_78, IntConstructorZero_78) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// ============================================================
// Test Real
// ============================================================
TEST_F(ObjectTest_78, RealConstructor_78) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
    EXPECT_FALSE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_78, RealConstructorZero_78) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_78, RealConstructorNegative_78) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

// ============================================================
// Test Int64
// ============================================================
TEST_F(ObjectTest_78, Int64Constructor_78) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_78, Int64GetIntOrInt64_78) {
    long long val = 123456789LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_78, IntGetIntOrInt64_78) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// ============================================================
// Test String
// ============================================================
TEST_F(ObjectTest_78, StringConstructor_78) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_78, StringConstructorFromStdString_78) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ============================================================
// Test HexString
// ============================================================
TEST_F(ObjectTest_78, HexStringConstructor_78) {
    Object obj(objHexString, std::string_view("AABB"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ============================================================
// Test Name
// ============================================================
TEST_F(ObjectTest_78, NameConstructor_78) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_78, NameIsSpecificName_78) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_78, NameGetNameString_78) {
    Object obj(objName, "MyName");
    std::string s = obj.getNameString();
    EXPECT_EQ(s, "MyName");
}

// ============================================================
// Test Cmd
// ============================================================
TEST_F(ObjectTest_78, CmdConstructor_78) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_TRUE(obj.isCmd("q"));
    EXPECT_FALSE(obj.isCmd("Q"));
    EXPECT_STREQ(obj.getCmd(), "q");
    EXPECT_EQ(obj.getType(), objCmd);
}

// ============================================================
// Test Error
// ============================================================
TEST_F(ObjectTest_78, ErrorFactory_78) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ============================================================
// Test EOF
// ============================================================
TEST_F(ObjectTest_78, EofFactory_78) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// ============================================================
// Test Move Constructor
// ============================================================
TEST_F(ObjectTest_78, MoveConstructor_78) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ============================================================
// Test Move Assignment
// ============================================================
TEST_F(ObjectTest_78, MoveAssignment_78) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ============================================================
// Test copy()
// ============================================================
TEST_F(ObjectTest_78, CopyInt_78) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_78, CopyBool_78) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_EQ(copied.getBool(), true);
}

TEST_F(ObjectTest_78, CopyReal_78) {
    Object obj(2.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.5);
}

TEST_F(ObjectTest_78, CopyNull_78) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_78, CopyString_78) {
    auto str = std::make_unique<GooString>("test");
    Object obj(std::move(str));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "test");
}

TEST_F(ObjectTest_78, CopyName_78) {
    Object obj(objName, "CopyMe");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyMe");
}

// ============================================================
// Test getNumWithDefaultValue
// ============================================================
TEST_F(ObjectTest_78, GetNumWithDefaultValueForInt_78) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_78, GetNumWithDefaultValueForReal_78) {
    Object obj(1.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 1.5);
}

TEST_F(ObjectTest_78, GetNumWithDefaultValueForNonNum_78) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ============================================================
// Test getBoolWithDefaultValue
// ============================================================
TEST_F(ObjectTest_78, GetBoolWithDefaultValueForBool_78) {
    Object obj(true);
    EXPECT_EQ(obj.getBoolWithDefaultValue(false), true);
}

TEST_F(ObjectTest_78, GetBoolWithDefaultValueForNonBool_78) {
    Object obj(42);
    EXPECT_EQ(obj.getBoolWithDefaultValue(true), true);
}

// ============================================================
// Test getNum with ok parameter
// ============================================================
TEST_F(ObjectTest_78, GetNumWithOkForInt_78) {
    Object obj(5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 5.0);
}

TEST_F(ObjectTest_78, GetNumWithOkForReal_78) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// ============================================================
// Test getTypeName
// ============================================================
TEST_F(ObjectTest_78, GetTypeNameBool_78) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_78, GetTypeNameInt_78) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_78, GetTypeNameNull_78) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ============================================================
// Test Array operations
// ============================================================
TEST_F(ObjectTest_78, ArrayConstructorAndBasicOps_78) {
    // We need an XRef* for Array, passing nullptr for basic tests
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_78, ArrayAddAndGetLength_78) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_78, ArrayGetReturnsCorrectValue_78) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));

    Object val0 = obj.arrayGet(0);
    EXPECT_TRUE(val0.isInt());
    EXPECT_EQ(val0.getInt(), 42);

    Object val1 = obj.arrayGet(1);
    EXPECT_TRUE(val1.isInt());
    EXPECT_EQ(val1.getInt(), 99);
}

TEST_F(ObjectTest_78, ArrayGetNF_78) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(7));
    const Object &ref = obj.arrayGetNF(0);
    EXPECT_TRUE(ref.isInt());
    EXPECT_EQ(ref.getInt(), 7);
}

TEST_F(ObjectTest_78, ArrayRemove_78) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);

    Object val0 = obj.arrayGet(0);
    EXPECT_EQ(val0.getInt(), 1);
    Object val1 = obj.arrayGet(1);
    EXPECT_EQ(val1.getInt(), 3);
}

// ============================================================
// Test Dict operations
// ============================================================
TEST_F(ObjectTest_78, DictConstructorAndBasicOps_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_78, DictAddAndLookup_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_78, DictLookupNonExistent_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_78, DictSetOverwrite_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(99));

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_78, DictRemove_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);

    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());

    Object val2 = obj.dictLookup("key2");
    EXPECT_TRUE(val2.isInt());
    EXPECT_EQ(val2.getInt(), 99);
}

TEST_F(ObjectTest_78, DictGetKey_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("alpha", Object(1));
    const char *key = obj.dictGetKey(0);
    EXPECT_NE(key, nullptr);
    EXPECT_STREQ(key, "alpha");
}

TEST_F(ObjectTest_78, DictGetVal_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_78, DictGetValNF_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(55));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_78, DictLookupNF_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(77));
    const Object &val = obj.dictLookupNF("key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// ============================================================
// Test isDict with type checking
// ============================================================
TEST_F(ObjectTest_78, IsDictWithType_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    // An empty dict without a type set — dictIs for a specific type
    // should behave based on the dict's type entry
    EXPECT_TRUE(obj.isDict());
}

// ============================================================
// Test takeString
// ============================================================
TEST_F(ObjectTest_78, TakeStringTransfersOwnership_78) {
    auto str = std::make_unique<GooString>("takeMe");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "takeMe");
}

// ============================================================
// Test isNum for various types
// ============================================================
TEST_F(ObjectTest_78, IsNumForInt_78) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_78, IsNumForReal_78) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_78, IsNumForNonNumeric_78) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_78, IsNumForBool_78) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// ============================================================
// Test isIntOrInt64
// ============================================================
TEST_F(ObjectTest_78, IsIntOrInt64ForInt_78) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_78, IsIntOrInt64ForInt64_78) {
    Object obj(static_cast<long long>(10));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_78, IsIntOrInt64ForReal_78) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ============================================================
// Test type exclusivity
// ============================================================
TEST_F(ObjectTest_78, TypeExclusivityNull_78) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
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
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_78, TypeExclusivityError_78) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_78, TypeExclusivityEOF_78) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
}

// ============================================================
// Test deep copy
// ============================================================
TEST_F(ObjectTest_78, DeepCopyInt_78) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_78, DeepCopyString_78) {
    auto str = std::make_unique<GooString>("deep");
    Object obj(std::move(str));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deep");
}

// ============================================================
// Test multiple dict entries
// ============================================================
TEST_F(ObjectTest_78, DictMultipleEntries_78) {
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

// ============================================================
// Test getArray and getDict accessors
// ============================================================
TEST_F(ObjectTest_78, GetArrayReturnsNonNull_78) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_78, GetDictReturnsNonNull_78) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}

// ============================================================
// Test print (just ensure it doesn't crash)
// ============================================================
TEST_F(ObjectTest_78, PrintIntDoesNotCrash_78) {
    Object obj(42);
    // Print to stdout; we just verify no crash
    obj.print(stdout);
}

TEST_F(ObjectTest_78, PrintNullDoesNotCrash_78) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_78, PrintStringDoesNotCrash_78) {
    auto str = std::make_unique<GooString>("printme");
    Object obj(std::move(str));
    obj.print(stdout);
}
