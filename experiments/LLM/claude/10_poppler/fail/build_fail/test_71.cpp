#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_71 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Constructor and Type Tests =====

TEST_F(ObjectTest_71, DefaultConstructorCreatesNoneType_71) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_71, BoolConstructorTrue_71) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_71, BoolConstructorFalse_71) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_71, IntConstructor_71) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_71, IntConstructorZero_71) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_71, IntConstructorNegative_71) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_71, RealConstructor_71) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_71, RealConstructorZero_71) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_71, RealConstructorNegative_71) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_71, Int64Constructor_71) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_71, StringConstructorWithGooString_71) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_71, StringConstructorWithStdString_71) {
    std::string s = "test";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_71, NameConstructor_71) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_71, CmdConstructor_71) {
    Object obj(objCmd, "myCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "myCmd");
}

TEST_F(ObjectTest_71, HexStringConstructor_71) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ===== Static Factory Methods =====

TEST_F(ObjectTest_71, NullFactory_71) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_71, EofFactory_71) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_71, ErrorFactory_71) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ===== Type Checking Methods (Negative cases) =====

TEST_F(ObjectTest_71, BoolIsNotInt_71) {
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
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_71, IntIsNotBool_71) {
    Object obj(10);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_71, NullIsNotOtherTypes_71) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ===== isNum tests =====

TEST_F(ObjectTest_71, IntIsNum_71) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_71, RealIsNum_71) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_71, BoolIsNotNum_71) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// ===== isIntOrInt64 tests =====

TEST_F(ObjectTest_71, IntIsIntOrInt64_71) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_71, Int64IsIntOrInt64_71) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_71, RealIsNotIntOrInt64_71) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ===== getNum tests =====

TEST_F(ObjectTest_71, GetNumFromInt_71) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_71, GetNumFromReal_71) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// ===== getIntOrInt64 tests =====

TEST_F(ObjectTest_71, GetIntOrInt64FromInt_71) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_71, GetIntOrInt64FromInt64_71) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ===== getNumWithDefaultValue tests =====

TEST_F(ObjectTest_71, GetNumWithDefaultValueFromInt_71) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_71, GetNumWithDefaultValueFromReal_71) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 2.5);
}

TEST_F(ObjectTest_71, GetNumWithDefaultValueFromNonNum_71) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_71, GetNumWithDefaultValueFromNull_71) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ===== getBoolWithDefaultValue tests =====

TEST_F(ObjectTest_71, GetBoolWithDefaultValueFromBool_71) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_71, GetBoolWithDefaultValueFromNonBool_71) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_71, GetBoolWithDefaultValueFalseFromNonBool_71) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ===== Move constructor and assignment =====

TEST_F(ObjectTest_71, MoveConstructor_71) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_71, MoveAssignment_71) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ===== setToNull =====

TEST_F(ObjectTest_71, SetToNull_71) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ===== isName with argument =====

TEST_F(ObjectTest_71, IsNameWithMatchingString_71) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_71, IsNameWithNonMatchingString_71) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_71, IsNameOnNonNameObject_71) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ===== isCmd with argument =====

TEST_F(ObjectTest_71, IsCmdWithMatchingString_71) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_71, IsCmdWithNonMatchingString_71) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_71, IsCmdOnNonCmdObject_71) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ===== getTypeName =====

TEST_F(ObjectTest_71, GetTypeNameBool_71) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_71, GetTypeNameInt_71) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_71, GetTypeNameNull_71) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ===== copy =====

TEST_F(ObjectTest_71, CopyBool_71) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_71, CopyInt_71) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_71, CopyReal_71) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_71, CopyNull_71) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_71, CopyName_71) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

TEST_F(ObjectTest_71, CopyCmd_71) {
    Object obj(objCmd, "BT");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isCmd());
    EXPECT_STREQ(copied.getCmd(), "BT");
}

TEST_F(ObjectTest_71, CopyString_71) {
    Object obj(std::string("hello"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_NE(copied.getString(), nullptr);
}

TEST_F(ObjectTest_71, CopyInt64_71) {
    long long val = 1LL << 40;
    Object obj(val);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), val);
}

TEST_F(ObjectTest_71, CopyError_71) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_71, CopyEOF_71) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// ===== Array operations =====

TEST_F(ObjectTest_71, ArrayConstructorAndLength_71) {
    // We need to create an Array object - Array requires an XRef* which can be nullptr
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_71, ArrayAddAndGet_71) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_71, ArrayAddMultiple_71) {
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

TEST_F(ObjectTest_71, ArrayRemove_71) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    EXPECT_EQ(obj.arrayGet(0).getInt(), 10);
    EXPECT_EQ(obj.arrayGet(1).getInt(), 30);
}

TEST_F(ObjectTest_71, ArrayGetNF_71) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

// ===== Dict operations =====

TEST_F(ObjectTest_71, DictConstructorAndLength_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_71, DictAddAndLookup_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_71, DictSetOverwrite_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_71, DictRemove_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(99));
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_71, DictLookupNonExistent_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_71, DictGetKey_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_71, DictGetVal_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_71, DictGetValNF_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_71, DictLookupNF_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const Object &val = obj.dictLookupNF("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ===== getNameString =====

TEST_F(ObjectTest_71, GetNameString_71) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ===== Boundary: empty string name =====

TEST_F(ObjectTest_71, EmptyNameString_71) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ===== Boundary: empty cmd string =====

TEST_F(ObjectTest_71, EmptyCmdString_71) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ===== Boundary: large int =====

TEST_F(ObjectTest_71, MaxInt_71) {
    int maxVal = std::numeric_limits<int>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), maxVal);
}

TEST_F(ObjectTest_71, MinInt_71) {
    int minVal = std::numeric_limits<int>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), minVal);
}

// ===== Boundary: large int64 =====

TEST_F(ObjectTest_71, MaxInt64_71) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_71, MinInt64_71) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// ===== Destructor doesn't crash after move =====

TEST_F(ObjectTest_71, DestructorAfterMove_71) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // obj1 should be in a valid state after move; destructor shouldn't crash
}

// ===== getNum with ok parameter =====

TEST_F(ObjectTest_71, GetNumWithOkFromInt_71) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_71, GetNumWithOkFromReal_71) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ===== takeString =====

TEST_F(ObjectTest_71, TakeString_71) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ===== Dict multiple entries =====

TEST_F(ObjectTest_71, DictMultipleEntries_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
    EXPECT_EQ(obj.dictLookup("a").getInt(), 1);
    EXPECT_EQ(obj.dictLookup("b").getInt(), 2);
    EXPECT_EQ(obj.dictLookup("c").getInt(), 3);
}

// ===== Copy preserves independence =====

TEST_F(ObjectTest_71, CopyIndependenceInt_71) {
    Object obj1(42);
    Object obj2 = obj1.copy();
    obj1.setToNull();
    EXPECT_TRUE(obj1.isNull());
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ===== Move constructor leaves source in valid state =====

TEST_F(ObjectTest_71, MoveConstructorSourceState_71) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // After move, obj1 should be in some defined state (likely dead or none)
    // Just ensure no crash when calling getType
    obj1.getType();
}

// ===== Move assignment leaves source in valid state =====

TEST_F(ObjectTest_71, MoveAssignmentSourceState_71) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // obj1 should not crash
    obj1.getType();
}

// ===== Array with mixed types =====

TEST_F(ObjectTest_71, ArrayMixedTypes_71) {
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

// ===== Dict with string values =====

TEST_F(ObjectTest_71, DictWithStringValues_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("name", Object(objName, "SomeName"));
    Object val = obj.dictLookup("name");
    EXPECT_TRUE(val.isName());
    EXPECT_STREQ(val.getName(), "SomeName");
}

// ===== HexString =====

TEST_F(ObjectTest_71, HexStringNotString_71) {
    Object obj(objHexString, "FF00");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
}

// ===== print doesn't crash =====

TEST_F(ObjectTest_71, PrintDoesNotCrash_71) {
    Object obj(42);
    // Just ensure print doesn't crash; output goes to stdout
    obj.print(stdout);
}

TEST_F(ObjectTest_71, PrintBoolDoesNotCrash_71) {
    Object obj(true);
    obj.print(stdout);
}

TEST_F(ObjectTest_71, PrintNullDoesNotCrash_71) {
    Object obj = Object::null();
    obj.print(stdout);
}

// ===== getArray and getDict accessors =====

TEST_F(ObjectTest_71, GetArrayAccessor_71) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_71, GetDictAccessor_71) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}
