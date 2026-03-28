#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test default constructor
TEST(ObjectTest_66, DefaultConstructorCreatesNoneType_66) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// Test bool constructor
TEST(ObjectTest_66, BoolConstructorTrue_66) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST(ObjectTest_66, BoolConstructorFalse_66) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test int constructor
TEST(ObjectTest_66, IntConstructor_66) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST(ObjectTest_66, IntConstructorNegative_66) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST(ObjectTest_66, IntConstructorZero_66) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test real (double) constructor
TEST(ObjectTest_66, RealConstructor_66) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST(ObjectTest_66, RealConstructorZero_66) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST(ObjectTest_66, RealConstructorNegative_66) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

// Test int64 constructor
TEST(ObjectTest_66, Int64Constructor_66) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

// Test isNum for int and real
TEST(ObjectTest_66, IsNumForInt_66) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectTest_66, IsNumForReal_66) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectTest_66, IsNumForNonNumeric_66) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// Test getNum for int and real
TEST(ObjectTest_66, GetNumFromInt_66) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST(ObjectTest_66, GetNumFromReal_66) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// Test isIntOrInt64
TEST(ObjectTest_66, IsIntOrInt64ForInt_66) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectTest_66, IsIntOrInt64ForInt64_66) {
    long long val = 100000000000LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectTest_66, IsIntOrInt64ForReal_66) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test getIntOrInt64
TEST(ObjectTest_66, GetIntOrInt64FromInt_66) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST(ObjectTest_66, GetIntOrInt64FromInt64_66) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test static factory methods
TEST(ObjectTest_66, NullFactory_66) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST(ObjectTest_66, EofFactory_66) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST(ObjectTest_66, ErrorFactory_66) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// Test string constructor
TEST(ObjectTest_66, StringConstructorFromGooString_66) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST(ObjectTest_66, StringConstructorFromStdString_66) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// Test name constructor
TEST(ObjectTest_66, NameConstructor_66) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST(ObjectTest_66, IsNameWithMatchingName_66) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName("MyName"));
}

TEST(ObjectTest_66, IsNameWithNonMatchingName_66) {
    Object obj(objName, "MyName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

// Test cmd constructor
TEST(ObjectTest_66, CmdConstructor_66) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST(ObjectTest_66, IsCmdWithMatchingCmd_66) {
    Object obj(objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
}

TEST(ObjectTest_66, IsCmdWithNonMatchingCmd_66) {
    Object obj(objCmd, "ET");
    EXPECT_FALSE(obj.isCmd("BT"));
}

// Test hex string constructor
TEST(ObjectTest_66, HexStringConstructor_66) {
    Object obj(objHexString, "ABCDEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// Test move constructor
TEST(ObjectTest_66, MoveConstructor_66) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test move assignment
TEST(ObjectTest_66, MoveAssignment_66) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test setToNull
TEST(ObjectTest_66, SetToNull_66) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// Test type checking - ensure mutual exclusivity
TEST(ObjectTest_66, TypeCheckMutualExclusivity_66) {
    Object intObj(10);
    EXPECT_TRUE(intObj.isInt());
    EXPECT_FALSE(intObj.isBool());
    EXPECT_FALSE(intObj.isReal());
    EXPECT_FALSE(intObj.isString());
    EXPECT_FALSE(intObj.isName());
    EXPECT_FALSE(intObj.isNull());
    EXPECT_FALSE(intObj.isArray());
    EXPECT_FALSE(intObj.isDict());
    EXPECT_FALSE(intObj.isStream());
    EXPECT_FALSE(intObj.isRef());
    EXPECT_FALSE(intObj.isCmd());
    EXPECT_FALSE(intObj.isError());
    EXPECT_FALSE(intObj.isEOF());
    EXPECT_FALSE(intObj.isNone());
    EXPECT_FALSE(intObj.isInt64());
    EXPECT_FALSE(intObj.isHexString());
}

// Test copy
TEST(ObjectTest_66, CopyInt_66) {
    Object obj(123);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 123);
}

TEST(ObjectTest_66, CopyReal_66) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST(ObjectTest_66, CopyBool_66) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST(ObjectTest_66, CopyNull_66) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST(ObjectTest_66, CopyName_66) {
    Object obj(objName, "test");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "test");
}

TEST(ObjectTest_66, CopyString_66) {
    Object obj(std::string("hello"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

// Test getNumWithDefaultValue
TEST(ObjectTest_66, GetNumWithDefaultValueForNum_66) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST(ObjectTest_66, GetNumWithDefaultValueForNonNum_66) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// Test getBoolWithDefaultValue
TEST(ObjectTest_66, GetBoolWithDefaultValueForBool_66) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST(ObjectTest_66, GetBoolWithDefaultValueForNonBool_66) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST(ObjectTest_66, GetBoolWithDefaultValueFalseForNonBool_66) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test getTypeName
TEST(ObjectTest_66, GetTypeNameForInt_66) {
    Object obj(1);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST(ObjectTest_66, GetTypeNameForNull_66) {
    Object obj = Object::null();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST(ObjectTest_66, GetTypeNameForError_66) {
    Object obj = Object::error();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test getNameString
TEST(ObjectTest_66, GetNameString_66) {
    Object obj(objName, "TestNameStr");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestNameStr");
}

// Test Array operations
TEST(ObjectTest_66, ArrayOperations_66) {
    Object arrObj(new Array(nullptr));
    EXPECT_TRUE(arrObj.isArray());
    EXPECT_EQ(arrObj.arrayGetLength(), 0);
    
    arrObj.arrayAdd(Object(42));
    EXPECT_EQ(arrObj.arrayGetLength(), 1);
    
    Object elem = arrObj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST(ObjectTest_66, ArrayAddMultipleElements_66) {
    Object arrObj(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(2));
    arrObj.arrayAdd(Object(3));
    EXPECT_EQ(arrObj.arrayGetLength(), 3);
    
    Object e0 = arrObj.arrayGet(0);
    Object e1 = arrObj.arrayGet(1);
    Object e2 = arrObj.arrayGet(2);
    EXPECT_EQ(e0.getInt(), 1);
    EXPECT_EQ(e1.getInt(), 2);
    EXPECT_EQ(e2.getInt(), 3);
}

TEST(ObjectTest_66, ArrayRemove_66) {
    Object arrObj(new Array(nullptr));
    arrObj.arrayAdd(Object(10));
    arrObj.arrayAdd(Object(20));
    arrObj.arrayAdd(Object(30));
    EXPECT_EQ(arrObj.arrayGetLength(), 3);
    
    arrObj.arrayRemove(1);
    EXPECT_EQ(arrObj.arrayGetLength(), 2);
    
    Object e0 = arrObj.arrayGet(0);
    Object e1 = arrObj.arrayGet(1);
    EXPECT_EQ(e0.getInt(), 10);
    EXPECT_EQ(e1.getInt(), 30);
}

TEST(ObjectTest_66, ArrayGetNF_66) {
    Object arrObj(new Array(nullptr));
    arrObj.arrayAdd(Object(42));
    const Object& nf = arrObj.arrayGetNF(0);
    EXPECT_TRUE(nf.isInt());
    EXPECT_EQ(nf.getInt(), 42);
}

// Test Dict operations
TEST(ObjectTest_66, DictOperations_66) {
    Object dictObj(new Dict(nullptr));
    EXPECT_TRUE(dictObj.isDict());
    EXPECT_EQ(dictObj.dictGetLength(), 0);
    
    dictObj.dictAdd("key1", Object(100));
    EXPECT_EQ(dictObj.dictGetLength(), 1);
    
    Object val = dictObj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST(ObjectTest_66, DictSet_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("key1", Object(100));
    dictObj.dictSet("key1", Object(200));
    
    Object val = dictObj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 200);
}

TEST(ObjectTest_66, DictRemove_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("key1", Object(100));
    dictObj.dictAdd("key2", Object(200));
    EXPECT_EQ(dictObj.dictGetLength(), 2);
    
    dictObj.dictRemove("key1");
    EXPECT_EQ(dictObj.dictGetLength(), 1);
    
    Object val = dictObj.dictLookup("key1");
    EXPECT_FALSE(val.isInt());
}

TEST(ObjectTest_66, DictLookupNonExistent_66) {
    Object dictObj(new Dict(nullptr));
    Object val = dictObj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST(ObjectTest_66, DictGetKey_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("mykey", Object(42));
    const char* key = dictObj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST(ObjectTest_66, DictGetVal_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("mykey", Object(42));
    Object val = dictObj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST(ObjectTest_66, DictGetValNF_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("mykey", Object(42));
    const Object& val = dictObj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST(ObjectTest_66, DictLookupNF_66) {
    Object dictObj(new Dict(nullptr));
    dictObj.dictAdd("mykey", Object(42));
    const Object& val = dictObj.dictLookupNF("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test getNum with ok parameter
TEST(ObjectTest_66, GetNumWithOkParamSuccess_66) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

// Test takeString
TEST(ObjectTest_66, TakeString_66) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// Test Int boundary values
TEST(ObjectTest_66, IntMaxValue_66) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST(ObjectTest_66, IntMinValue_66) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

// Test Int64 boundary values
TEST(ObjectTest_66, Int64MaxValue_66) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectTest_66, Int64MinValue_66) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test moving an object leaves source in valid state
TEST(ObjectTest_66, MoveConstructorLeavesSourceNone_66) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // After move, obj1 should be in a valid state (typically none)
    EXPECT_TRUE(obj1.isNone());
}

TEST(ObjectTest_66, MoveAssignmentLeavesSourceNone_66) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj1.isNone());
}

// Test copy of error object
TEST(ObjectTest_66, CopyError_66) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

// Test copy of EOF object
TEST(ObjectTest_66, CopyEof_66) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// Test empty name
TEST(ObjectTest_66, EmptyName_66) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Test empty cmd
TEST(ObjectTest_66, EmptyCmd_66) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// Test print does not crash
TEST(ObjectTest_66, PrintDoesNotCrash_66) {
    Object obj(42);
    // Just ensure it doesn't crash
    obj.print(stdout);
}

// Test deepCopy for simple types
TEST(ObjectTest_66, DeepCopyInt_66) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST(ObjectTest_66, DeepCopyString_66) {
    Object obj(std::string("deep"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
}
