#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Array.h"

// Test fixture for Object tests
class ObjectTest_2751 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates objNone
TEST_F(ObjectTest_2751, DefaultConstructorCreatesNone_2751) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// Test bool constructor
TEST_F(ObjectTest_2751, BoolConstructorTrue_2751) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2751, BoolConstructorFalse_2751) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test int constructor
TEST_F(ObjectTest_2751, IntConstructor_2751) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2751, IntConstructorZero_2751) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2751, IntConstructorNegative_2751) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

// Test real (double) constructor
TEST_F(ObjectTest_2751, RealConstructor_2751) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2751, RealConstructorZero_2751) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2751, RealConstructorNegative_2751) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

// Test int64 constructor
TEST_F(ObjectTest_2751, Int64Constructor_2751) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

// Test isNum for int and real
TEST_F(ObjectTest_2751, IsNumForInt_2751) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2751, IsNumForReal_2751) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2751, IsNumForBool_2751) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// Test getNum for int and real
TEST_F(ObjectTest_2751, GetNumFromInt_2751) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_2751, GetNumFromReal_2751) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// Test isIntOrInt64
TEST_F(ObjectTest_2751, IsIntOrInt64ForInt_2751) {
    Object obj(10);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2751, IsIntOrInt64ForInt64_2751) {
    Object obj(static_cast<long long>(10));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2751, IsIntOrInt64ForReal_2751) {
    Object obj(10.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test getIntOrInt64
TEST_F(ObjectTest_2751, GetIntOrInt64FromInt_2751) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2751, GetIntOrInt64FromInt64_2751) {
    long long val = 123456789012LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test static factory methods
TEST_F(ObjectTest_2751, NullFactory_2751) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2751, EofFactory_2751) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_2751, ErrorFactory_2751) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// Test move constructor
TEST_F(ObjectTest_2751, MoveConstructor_2751) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test move assignment
TEST_F(ObjectTest_2751, MoveAssignment_2751) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test setToNull
TEST_F(ObjectTest_2751, SetToNull_2751) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// Test string constructor
TEST_F(ObjectTest_2751, StringConstructorFromUniquePtr_2751) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_2751, StringConstructorFromStdString_2751) {
    Object obj(std::string("world"));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// Test name constructor
TEST_F(ObjectTest_2751, NameConstructor_2751) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test isName with string_view comparison
TEST_F(ObjectTest_2751, IsNameWithMatch_2751) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

// Test cmd constructor
TEST_F(ObjectTest_2751, CmdConstructor_2751) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

// Test isCmd with string_view comparison
TEST_F(ObjectTest_2751, IsCmdWithMatch_2751) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// Test Array constructor
TEST_F(ObjectTest_2751, ArrayConstructor_2751) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.getArray(), arr);
}

// Test array operations through Object
TEST_F(ObjectTest_2751, ArrayGetLength_2751) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_2751, ArrayAddAndGetLength_2751) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_2751, ArrayGetElement_2751) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));
    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 42);
    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 99);
}

TEST_F(ObjectTest_2751, ArrayGetNF_2751) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(77));
    const Object &elemNF = obj.arrayGetNF(0);
    EXPECT_TRUE(elemNF.isInt());
    EXPECT_EQ(elemNF.getInt(), 77);
}

TEST_F(ObjectTest_2751, ArrayRemove_2751) {
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

// Test Dict constructor
TEST_F(ObjectTest_2751, DictConstructor_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.getDict(), dict);
}

// Test dict operations through Object
TEST_F(ObjectTest_2751, DictGetLength_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_2751, DictAddAndLookup_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2751, DictSetOverwrite_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_2751, DictRemove_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("A");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("A");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2751, DictLookupNonExistent_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2751, DictGetKey_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(99));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_2751, DictGetVal_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_2751, DictGetValNF_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(77));
    const Object &valNF = obj.dictGetValNF(0);
    EXPECT_TRUE(valNF.isInt());
    EXPECT_EQ(valNF.getInt(), 77);
}

TEST_F(ObjectTest_2751, DictLookupNF_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Hello", Object(33));
    const Object &valNF = obj.dictLookupNF("Hello");
    EXPECT_TRUE(valNF.isInt());
    EXPECT_EQ(valNF.getInt(), 33);
}

// Test type checking methods are mutually exclusive
TEST_F(ObjectTest_2751, TypeCheckingMutuallyExclusive_2751) {
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

// Test getTypeName
TEST_F(ObjectTest_2751, GetTypeName_2751) {
    Object intObj(42);
    const char *name = intObj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_2751, GetTypeNameNull_2751) {
    Object nullObj = Object::null();
    const char *name = nullObj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test copy
TEST_F(ObjectTest_2751, CopyInt_2751) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_2751, CopyBool_2751) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2751, CopyReal_2751) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_2751, CopyNull_2751) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// Test getNumWithDefaultValue
TEST_F(ObjectTest_2751, GetNumWithDefaultValueFromNum_2751) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_2751, GetNumWithDefaultValueFromNonNum_2751) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

// Test getBoolWithDefaultValue
TEST_F(ObjectTest_2751, GetBoolWithDefaultValueFromBool_2751) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2751, GetBoolWithDefaultValueFromNonBool_2751) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test hex string constructor
TEST_F(ObjectTest_2751, HexStringConstructor_2751) {
    auto str = std::make_unique<GooString>("ABCD");
    Object obj(objHexString, str->toStr());
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// Test getNameString
TEST_F(ObjectTest_2751, GetNameString_2751) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// Test move assignment from different type
TEST_F(ObjectTest_2751, MoveAssignmentDifferentTypes_2751) {
    Object obj1(42);
    Object obj2(3.14);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isReal());
    EXPECT_DOUBLE_EQ(obj1.getReal(), 3.14);
}

// Test that moved-from object is in valid state
TEST_F(ObjectTest_2751, MovedFromObjectState_2751) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    // After move, obj1 should be in a valid state (typically objNone)
    EXPECT_TRUE(obj1.isNone());
}

// Test multiple dict additions
TEST_F(ObjectTest_2751, DictMultipleAdditions_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    for (int i = 0; i < 10; i++) {
        obj.dictAdd(std::string("Key") + std::to_string(i), Object(i));
    }
    EXPECT_EQ(obj.dictGetLength(), 10);
    for (int i = 0; i < 10; i++) {
        Object val = obj.dictLookup(std::string("Key") + std::to_string(i));
        EXPECT_TRUE(val.isInt());
        EXPECT_EQ(val.getInt(), i);
    }
}

// Test array with various types
TEST_F(ObjectTest_2751, ArrayMixedTypes_2751) {
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

// Test boundary: large int
TEST_F(ObjectTest_2751, LargeIntValue_2751) {
    Object obj(INT_MAX);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

TEST_F(ObjectTest_2751, MinIntValue_2751) {
    Object obj(INT_MIN);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

// Test boundary: large int64
TEST_F(ObjectTest_2751, LargeInt64Value_2751) {
    long long val = LLONG_MAX;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test self-move assignment safety
TEST_F(ObjectTest_2751, SelfMoveAssignment_2751) {
    Object obj(42);
    obj = std::move(obj);
    // Should not crash; behavior may vary but should remain valid
}

// Test getNum with ok parameter
TEST_F(ObjectTest_2751, GetNumWithOkParam_2751) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

// Test empty name
TEST_F(ObjectTest_2751, EmptyName_2751) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Test dictIs
TEST_F(ObjectTest_2751, DictIsType_2751) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    // dictIs checks the dict's type field - without setting it, it should return false for arbitrary types
    // This tests the interface works without crashing
    bool result = obj.dictIs("Page");
    // Result depends on dict type; we just verify it doesn't crash
    (void)result;
}
