#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "GooString.h"
#include <memory>
#include <cstring>

// Test fixture for Object tests
class ObjectTest_2752 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates objNone
TEST_F(ObjectTest_2752, DefaultConstructorCreatesNone_2752) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// Test bool constructor
TEST_F(ObjectTest_2752, BoolConstructorTrue_2752) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2752, BoolConstructorFalse_2752) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test int constructor
TEST_F(ObjectTest_2752, IntConstructor_2752) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2752, IntConstructorZero_2752) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2752, IntConstructorNegative_2752) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

// Test double/real constructor
TEST_F(ObjectTest_2752, RealConstructor_2752) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2752, RealConstructorZero_2752) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2752, RealConstructorNegative_2752) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

// Test int64 constructor
TEST_F(ObjectTest_2752, Int64Constructor_2752) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

// Test isNum for int and real
TEST_F(ObjectTest_2752, IsNumForInt_2752) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2752, IsNumForReal_2752) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2752, IsNumForBool_2752) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// Test getNum for int
TEST_F(ObjectTest_2752, GetNumFromInt_2752) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

// Test getNum for real
TEST_F(ObjectTest_2752, GetNumFromReal_2752) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// Test isIntOrInt64
TEST_F(ObjectTest_2752, IsIntOrInt64ForInt_2752) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2752, IsIntOrInt64ForInt64_2752) {
    long long val = 123456789012LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2752, IsIntOrInt64ForReal_2752) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test getIntOrInt64
TEST_F(ObjectTest_2752, GetIntOrInt64FromInt_2752) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2752, GetIntOrInt64FromInt64_2752) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test string constructor
TEST_F(ObjectTest_2752, StringConstructor_2752) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

// Test string constructor with std::string
TEST_F(ObjectTest_2752, StdStringConstructor_2752) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// Test name constructor
TEST_F(ObjectTest_2752, NameConstructor_2752) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test isName with matching name
TEST_F(ObjectTest_2752, IsNameWithMatchingString_2752) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
    EXPECT_FALSE(obj.isName("Other"));
}

// Test cmd constructor
TEST_F(ObjectTest_2752, CmdConstructor_2752) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

// Test isCmd with matching cmd
TEST_F(ObjectTest_2752, IsCmdWithMatchingString_2752) {
    Object obj(objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// Test null static factory
TEST_F(ObjectTest_2752, NullFactory_2752) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// Test eof static factory
TEST_F(ObjectTest_2752, EofFactory_2752) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// Test error static factory
TEST_F(ObjectTest_2752, ErrorFactory_2752) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// Test Dict constructor
TEST_F(ObjectTest_2752, DictConstructor_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    Object obj(d);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.getDict(), d);
}

// Test Array constructor
TEST_F(ObjectTest_2752, ArrayConstructor_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    Object obj(a);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.getArray(), a);
}

// Test move constructor
TEST_F(ObjectTest_2752, MoveConstructor_2752) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid state (typically none or dead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

// Test move assignment
TEST_F(ObjectTest_2752, MoveAssignment_2752) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test setToNull
TEST_F(ObjectTest_2752, SetToNull_2752) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// Test type checking functions return false for wrong types
TEST_F(ObjectTest_2752, TypeCheckFalseForWrongType_2752) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
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

// Test getTypeName
TEST_F(ObjectTest_2752, GetTypeNameBool_2752) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2752, GetTypeNameInt_2752) {
    Object obj(10);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2752, GetTypeNameNull_2752) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// Test getNumWithDefaultValue
TEST_F(ObjectTest_2752, GetNumWithDefaultValueForNum_2752) {
    Object obj(3.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.5);
}

TEST_F(ObjectTest_2752, GetNumWithDefaultValueForNonNum_2752) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_2752, GetNumWithDefaultValueForInt_2752) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 7.0);
}

// Test getBoolWithDefaultValue
TEST_F(ObjectTest_2752, GetBoolWithDefaultValueForBool_2752) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2752, GetBoolWithDefaultValueForNonBool_2752) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test copy
TEST_F(ObjectTest_2752, CopyInt_2752) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_2752, CopyBool_2752) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2752, CopyReal_2752) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_2752, CopyNull_2752) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_2752, CopyName_2752) {
    Object obj(objName, "MyName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "MyName");
}

// Test Dict operations through Object
TEST_F(ObjectTest_2752, DictGetLength_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("key1", Object(1));
    d->add("key2", Object(2));
    Object obj(d);
    EXPECT_EQ(obj.dictGetLength(), 2);
}

TEST_F(ObjectTest_2752, DictLookup_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("mykey", Object(99));
    Object obj(d);
    Object val = obj.dictLookup("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_2752, DictLookupMissing_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    Object obj(d);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2752, DictAdd_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    Object obj(d);
    obj.dictAdd("newkey", Object(123));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("newkey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 123);
}

TEST_F(ObjectTest_2752, DictSet_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("key", Object(1));
    Object obj(d);
    obj.dictSet("key", Object(2));
    Object val = obj.dictLookup("key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_2752, DictRemove_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("key1", Object(1));
    d->add("key2", Object(2));
    Object obj(d);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2752, DictGetKey_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("alpha", Object(1));
    Object obj(d);
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "alpha");
}

TEST_F(ObjectTest_2752, DictGetVal_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("key", Object(55));
    Object obj(d);
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// Test dictIs
TEST_F(ObjectTest_2752, DictIs_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("Type", Object(objName, "Page"));
    Object obj(d);
    EXPECT_TRUE(obj.isDict("Page"));
    EXPECT_FALSE(obj.isDict("Catalog"));
}

// Test Array operations through Object
TEST_F(ObjectTest_2752, ArrayGetLength_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    a->add(Object(1));
    a->add(Object(2));
    a->add(Object(3));
    Object obj(a);
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_2752, ArrayGet_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    a->add(Object(10));
    a->add(Object(20));
    Object obj(a);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 10);
    elem = obj.arrayGet(1);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 20);
}

TEST_F(ObjectTest_2752, ArrayAdd_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    Object obj(a);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_2752, ArrayRemove_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    a->add(Object(1));
    a->add(Object(2));
    a->add(Object(3));
    Object obj(a);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object elem0 = obj.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 1);
    Object elem1 = obj.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 3);
}

// Test getNameString
TEST_F(ObjectTest_2752, GetNameString_2752) {
    Object obj(objName, "TestNameStr");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestNameStr");
}

// Test hex string constructor
TEST_F(ObjectTest_2752, HexStringConstructor_2752) {
    auto str = std::make_unique<GooString>("AABB");
    Object obj(objHexString, std::string_view("AABB"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// Test getNum with ok parameter
TEST_F(ObjectTest_2752, GetNumWithOkParameter_2752) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(ObjectTest_2752, GetNumWithOkParameterForNonNum_2752) {
    Object obj = Object::null();
    bool ok = true;
    double val = obj.getNum(&ok);
    EXPECT_FALSE(ok);
}

// Test boundary: very large int64
TEST_F(ObjectTest_2752, Int64BoundaryMax_2752) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2752, Int64BoundaryMin_2752) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test boundary: INT_MAX and INT_MIN for int
TEST_F(ObjectTest_2752, IntBoundaryMax_2752) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_2752, IntBoundaryMin_2752) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

// Test empty Dict
TEST_F(ObjectTest_2752, EmptyDict_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    Object obj(d);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

// Test empty Array
TEST_F(ObjectTest_2752, EmptyArray_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    Object obj(a);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

// Test takeString
TEST_F(ObjectTest_2752, TakeString_2752) {
    Object obj(std::string("hello world"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// Test move assignment overwrite
TEST_F(ObjectTest_2752, MoveAssignmentOverwrite_2752) {
    Object obj1(42);
    Object obj2(3.14);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isReal());
    EXPECT_DOUBLE_EQ(obj1.getReal(), 3.14);
}

// Test multiple type transitions with setToNull
TEST_F(ObjectTest_2752, MultipleSetToNull_2752) {
    Object obj(100);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    obj = Object(true);
    EXPECT_TRUE(obj.isBool());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// Test name with empty string
TEST_F(ObjectTest_2752, NameEmptyString_2752) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Test cmd with empty string
TEST_F(ObjectTest_2752, CmdEmptyString_2752) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// Test isName returns false for non-name object
TEST_F(ObjectTest_2752, IsNameStringForNonName_2752) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// Test isCmd returns false for non-cmd object
TEST_F(ObjectTest_2752, IsCmdStringForNonCmd_2752) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// Test dictLookupNF
TEST_F(ObjectTest_2752, DictLookupNF_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("testkey", Object(77));
    Object obj(d);
    const Object &val = obj.dictLookupNF("testkey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// Test arrayGetNF
TEST_F(ObjectTest_2752, ArrayGetNF_2752) {
    Array *a = new Array(static_cast<XRef *>(nullptr));
    a->add(Object(33));
    Object obj(a);
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 33);
}

// Test dictGetValNF
TEST_F(ObjectTest_2752, DictGetValNF_2752) {
    Dict *d = new Dict(static_cast<XRef *>(nullptr));
    d->add("k", Object(88));
    Object obj(d);
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 88);
}
