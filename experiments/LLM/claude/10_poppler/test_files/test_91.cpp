#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_91 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_91, DefaultConstructorCreatesNoneObject_91) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_91, BoolConstructorTrue_91) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_91, BoolConstructorFalse_91) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_91, IntConstructor_91) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_91, IntConstructorNegative_91) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_91, IntConstructorZero_91) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_91, RealConstructor_91) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_91, RealConstructorZero_91) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_91, RealConstructorNegative_91) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_91, Int64Constructor_91) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_91, Int64ConstructorNegative_91) {
    long long val = -(1LL << 40);
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_91, StringConstructorFromGooString_91) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_91, StringConstructorFromStdString_91) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_91, NameConstructor_91) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_91, CmdConstructor_91) {
    Object obj(objCmd, "myCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "myCmd");
}

TEST_F(ObjectTest_91, HexStringConstructor_91) {
    Object obj(objHexString, std::string("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_91, NullFactory_91) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_91, EofFactory_91) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_91, ErrorFactory_91) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Methods ====================

TEST_F(ObjectTest_91, IsBoolReturnsTrueForBool_91) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
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

TEST_F(ObjectTest_91, IsIntReturnsTrueForInt_91) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_91, IsNumReturnsTrueForInt_91) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_91, IsNumReturnsTrueForReal_91) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_91, IsNumReturnsTrueForInt64_91) {
    Object obj(static_cast<long long>(100));
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_91, IsIntOrInt64ForInt_91) {
    Object obj(5);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_91, IsIntOrInt64ForInt64_91) {
    Object obj(static_cast<long long>(5));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_91, IsIntOrInt64ForReal_91) {
    Object obj(5.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== Getter Methods ====================

TEST_F(ObjectTest_91, GetBoolTrue_91) {
    Object obj(true);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_91, GetBoolFalse_91) {
    Object obj(false);
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_91, GetIntValue_91) {
    Object obj(12345);
    EXPECT_EQ(obj.getInt(), 12345);
}

TEST_F(ObjectTest_91, GetRealValue_91) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getReal(), 2.718);
}

TEST_F(ObjectTest_91, GetNumFromInt_91) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_91, GetNumFromReal_91) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

TEST_F(ObjectTest_91, GetNumFromInt64_91) {
    Object obj(static_cast<long long>(999));
    EXPECT_DOUBLE_EQ(obj.getNum(), 999.0);
}

TEST_F(ObjectTest_91, GetNumWithOkFlag_91) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(ObjectTest_91, GetInt64Value_91) {
    long long val = 1LL << 35;
    Object obj(val);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_91, GetIntOrInt64FromInt_91) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_91, GetIntOrInt64FromInt64_91) {
    long long val = 1LL << 35;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_91, GetName_91) {
    Object obj(objName, "TestName");
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_91, GetNameString_91) {
    Object obj(objName, "TestName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "TestName");
}

TEST_F(ObjectTest_91, GetCmd_91) {
    Object obj(objCmd, "TestCmd");
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

// ==================== Name and Cmd comparison ====================

TEST_F(ObjectTest_91, IsNameWithMatchingString_91) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
}

TEST_F(ObjectTest_91, IsNameWithNonMatchingString_91) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_91, IsCmdWithMatchingString_91) {
    Object obj(objCmd, "mycmd");
    EXPECT_TRUE(obj.isCmd("mycmd"));
}

TEST_F(ObjectTest_91, IsCmdWithNonMatchingString_91) {
    Object obj(objCmd, "mycmd");
    EXPECT_FALSE(obj.isCmd("othercmd"));
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_91, MoveConstructor_91) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically None or Dead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

TEST_F(ObjectTest_91, MoveAssignment_91) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_91, MoveAssignmentOverwrites_91) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull ====================

TEST_F(ObjectTest_91, SetToNull_91) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_91, SetToNullFromBool_91) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy ====================

TEST_F(ObjectTest_91, CopyInt_91) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_91, CopyBool_91) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_91, CopyReal_91) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_91, CopyNull_91) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_91, CopyName_91) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

TEST_F(ObjectTest_91, CopyString_91) {
    Object obj(std::string("hello"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_NE(copied.getString(), nullptr);
}

// ==================== getTypeName ====================

TEST_F(ObjectTest_91, GetTypeNameBool_91) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_91, GetTypeNameInt_91) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_91, GetTypeNameNull_91) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== getNumWithDefaultValue ====================

TEST_F(ObjectTest_91, GetNumWithDefaultValueFromInt_91) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_91, GetNumWithDefaultValueFromReal_91) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_91, GetNumWithDefaultValueFromNonNumeric_91) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_91, GetNumWithDefaultValueFromBool_91) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ==================== getBoolWithDefaultValue ====================

TEST_F(ObjectTest_91, GetBoolWithDefaultValueFromBool_91) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_91, GetBoolWithDefaultValueFromBoolFalse_91) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_91, GetBoolWithDefaultValueFromNonBool_91) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_91, GetBoolWithDefaultValueFromNull_91) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array Operations ====================

TEST_F(ObjectTest_91, ArrayConstructorAndBasicOps_91) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_91, ArrayAddAndGetLength_91) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_91, ArrayGetElement_91) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));
    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 42);
    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 99);
}

TEST_F(ObjectTest_91, ArrayGetNF_91) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_91, ArrayRemove_91) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object first = obj.arrayGet(0);
    EXPECT_EQ(first.getInt(), 1);
    Object second = obj.arrayGet(1);
    EXPECT_EQ(second.getInt(), 3);
}

// ==================== Dict Operations ====================

TEST_F(ObjectTest_91, DictConstructorAndBasicOps_91) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_91, DictAddAndLookup_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_91, DictSetOverwrite_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_91, DictRemove_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_91, DictGetKey_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("myKey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "myKey");
}

TEST_F(ObjectTest_91, DictGetVal_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("myKey", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_91, DictGetValNF_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("myKey", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_91, DictLookupNonExistentKey_91) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_91, DictLookupNF_91) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    const Object &val = obj.dictLookupNF("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== TakeString ====================

TEST_F(ObjectTest_91, TakeString_91) {
    Object obj(std::string("test"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ObjectTest_91, IntMaxValue_91) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_91, IntMinValue_91) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_91, Int64MaxValue_91) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_91, Int64MinValue_91) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_91, EmptyNameString_91) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_91, EmptyString_91) {
    Object obj(std::string(""));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_91, EmptyCmdString_91) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Multiple moves ====================

TEST_F(ObjectTest_91, ChainedMoveAssignment_91) {
    Object obj1(42);
    Object obj2(3.14);
    Object obj3;
    obj3 = std::move(obj2);
    obj3 = std::move(obj1);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
}

// ==================== Dict with multiple entries ====================

TEST_F(ObjectTest_91, DictMultipleEntries_91) {
    Object obj(new Dict(nullptr));
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

// ==================== Array with mixed types ====================

TEST_F(ObjectTest_91, ArrayWithMixedTypes_91) {
    Object obj(new Array(nullptr));
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

// ==================== DeepCopy ====================

TEST_F(ObjectTest_91, DeepCopyInt_91) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_91, DeepCopyString_91) {
    Object obj(std::string("deep copy test"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_NE(deep.getString(), nullptr);
}

// ==================== isName with non-name object ====================

TEST_F(ObjectTest_91, IsNameStringOnNonNameObject_91) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("something"));
}

TEST_F(ObjectTest_91, IsCmdStringOnNonCmdObject_91) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("something"));
}
