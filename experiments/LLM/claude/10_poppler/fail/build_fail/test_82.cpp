#include <gtest/gtest.h>
#include "Object.h"

class ObjectTest_82 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for default constructor and type checking
// =============================================================================

TEST_F(ObjectTest_82, DefaultConstructorCreatesNoneObject_82) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// =============================================================================
// Tests for bool object
// =============================================================================

TEST_F(ObjectTest_82, BoolConstructorTrue_82) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_82, BoolConstructorFalse_82) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_82, BoolIsNotOtherTypes_82) {
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
// Tests for int object
// =============================================================================

TEST_F(ObjectTest_82, IntConstructor_82) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_82, IntConstructorNegative_82) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_82, IntConstructorZero_82) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_82, IntIsNum_82) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_82, IntGetNum_82) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_82, IntGetIntOrInt64_82) {
    Object obj(123);
    EXPECT_EQ(obj.getIntOrInt64(), 123LL);
}

// =============================================================================
// Tests for real (double) object
// =============================================================================

TEST_F(ObjectTest_82, RealConstructor_82) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_82, RealIsNum_82) {
    Object obj(2.5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.5);
}

TEST_F(ObjectTest_82, RealIsNotInt_82) {
    Object obj(1.0);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_82, RealNegativeValue_82) {
    Object obj(-0.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -0.5);
}

TEST_F(ObjectTest_82, RealZeroValue_82) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

// =============================================================================
// Tests for Int64 object
// =============================================================================

TEST_F(ObjectTest_82, Int64Constructor_82) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_82, Int64IsIntOrInt64_82) {
    long long val = 12345LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_82, Int64IsNum_82) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_TRUE(obj.isNum());
}

// =============================================================================
// Tests for string object
// =============================================================================

TEST_F(ObjectTest_82, StringConstructorFromRvalueString_82) {
    std::string s = "hello";
    Object obj(objString, std::string(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_82, StringConstructorFromStringView_82) {
    Object obj(objString, std::string_view("test"));
    EXPECT_TRUE(obj.isString());
}

// =============================================================================
// Tests for hex string object
// =============================================================================

TEST_F(ObjectTest_82, HexStringConstructor_82) {
    Object obj(objHexString, std::string("ABCD"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Tests for name object
// =============================================================================

TEST_F(ObjectTest_82, NameConstructor_82) {
    Object obj(objName, std::string("MyName"));
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_NE(obj.getName(), nullptr);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_82, NameIsNameWithMatch_82) {
    Object obj(objName, std::string("Type"));
    EXPECT_TRUE(obj.isName("Type"));
}

TEST_F(ObjectTest_82, NameIsNameWithNoMatch_82) {
    Object obj(objName, std::string("Type"));
    EXPECT_FALSE(obj.isName("Other"));
}

TEST_F(ObjectTest_82, NameGetNameString_82) {
    Object obj(objName, std::string("Catalog"));
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "Catalog");
}

// =============================================================================
// Tests for cmd object
// =============================================================================

TEST_F(ObjectTest_82, CmdConstructor_82) {
    Object obj(objCmd, std::string("BT"));
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_82, CmdIsCmdWithMatch_82) {
    Object obj(objCmd, std::string("ET"));
    EXPECT_TRUE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_82, CmdIsCmdWithNoMatch_82) {
    Object obj(objCmd, std::string("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// =============================================================================
// Tests for null object
// =============================================================================

TEST_F(ObjectTest_82, NullStaticFactory_82) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_82, SetToNull_82) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Tests for error object
// =============================================================================

TEST_F(ObjectTest_82, ErrorStaticFactory_82) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// Tests for EOF object
// =============================================================================

TEST_F(ObjectTest_82, EofStaticFactory_82) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// =============================================================================
// Tests for isRef
// =============================================================================

TEST_F(ObjectTest_82, NonRefObjectIsNotRef_82) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, NullObjectIsNotRef_82) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, BoolObjectIsNotRef_82) {
    Object obj(true);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, RealObjectIsNotRef_82) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, ErrorObjectIsNotRef_82) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, EofObjectIsNotRef_82) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, NoneObjectIsNotRef_82) {
    Object obj;
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, NameObjectIsNotRef_82) {
    Object obj(objName, std::string("Test"));
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, CmdObjectIsNotRef_82) {
    Object obj(objCmd, std::string("q"));
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, StringObjectIsNotRef_82) {
    Object obj(objString, std::string("hello"));
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_82, Int64ObjectIsNotRef_82) {
    long long val = 42LL;
    Object obj(val);
    EXPECT_FALSE(obj.isRef());
}

// =============================================================================
// Tests for move constructor and assignment
// =============================================================================

TEST_F(ObjectTest_82, MoveConstructor_82) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_82, MoveAssignment_82) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_82, MoveAssignmentReplacesExisting_82) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// =============================================================================
// Tests for copy()
// =============================================================================

TEST_F(ObjectTest_82, CopyInt_82) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_82, CopyBool_82) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_82, CopyReal_82) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_82, CopyNull_82) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_82, CopyError_82) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_82, CopyName_82) {
    Object obj(objName, std::string("TestName"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// =============================================================================
// Tests for getTypeName
// =============================================================================

TEST_F(ObjectTest_82, GetTypeNameBool_82) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_82, GetTypeNameInt_82) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_82, GetTypeNameNull_82) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// =============================================================================
// Tests for getNumWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_82, GetNumWithDefaultValueForInt_82) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_82, GetNumWithDefaultValueForReal_82) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_82, GetNumWithDefaultValueForNonNum_82) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_82, GetNumWithDefaultValueForBool_82) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(55.5), 55.5);
}

// =============================================================================
// Tests for getBoolWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_82, GetBoolWithDefaultValueForBool_82) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_82, GetBoolWithDefaultValueForNonBool_82) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_82, GetBoolWithDefaultValueForNonBoolTrue_82) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// =============================================================================
// Tests for Array operations
// =============================================================================

TEST_F(ObjectTest_82, ArrayConstructorAndOperations_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_82, ArrayAddAndGetLength_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_82, ArrayGet_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_82, ArrayGetNF_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(77));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 77);
}

TEST_F(ObjectTest_82, ArrayRemove_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_82, ArrayIsNotRef_82) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_FALSE(obj.isRef());
}

// =============================================================================
// Tests for Dict operations
// =============================================================================

TEST_F(ObjectTest_82, DictConstructorAndOperations_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_82, DictAddAndLookup_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_82, DictSetOverwritesExisting_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(10));
    obj.dictSet("Key", Object(20));
    Object val = obj.dictLookup("Key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 20);
}

TEST_F(ObjectTest_82, DictRemove_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(1));
    obj.dictAdd("Key2", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_82, DictLookupNonExistent_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_82, DictGetKey_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(99));
    const char *key = obj.dictGetKey(0);
    EXPECT_NE(key, nullptr);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_82, DictGetVal_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_82, DictGetValNF_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(66));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 66);
}

TEST_F(ObjectTest_82, DictLookupNF_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(77));
    const Object &val = obj.dictLookupNF("K");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_82, DictIsNotRef_82) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_FALSE(obj.isRef());
}

// =============================================================================
// Tests for getNum with ok parameter
// =============================================================================

TEST_F(ObjectTest_82, GetNumWithOkForInt_82) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_82, GetNumWithOkForReal_82) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// =============================================================================
// Tests for type cross-checking
// =============================================================================

TEST_F(ObjectTest_82, AllTypeMutuallyExclusiveForInt_82) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
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

TEST_F(ObjectTest_82, AllTypeMutuallyExclusiveForNull_82) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
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

// =============================================================================
// Tests for deepCopy
// =============================================================================

TEST_F(ObjectTest_82, DeepCopyInt_82) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_82, DeepCopyName_82) {
    Object obj(objName, std::string("DeepName"));
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "DeepName");
}

// =============================================================================
// Tests for HexString type check
// =============================================================================

TEST_F(ObjectTest_82, HexStringIsNotString_82) {
    Object obj(objHexString, std::string("FF00"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_82, StringIsNotHexString_82) {
    Object obj(objString, std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
}

// =============================================================================
// Tests for destructor (no crash)
// =============================================================================

TEST_F(ObjectTest_82, DestructorNoCrash_82) {
    {
        Object obj(42);
    }
    {
        Object obj(3.14);
    }
    {
        Object obj(true);
    }
    {
        Object obj = Object::null();
    }
    {
        Object obj(objName, std::string("test"));
    }
    {
        Object obj(objString, std::string("test"));
    }
    SUCCEED();
}

// =============================================================================
// Boundary Tests
// =============================================================================

TEST_F(ObjectTest_82, IntMaxBoundary_82) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_82, IntMinBoundary_82) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_82, Int64MaxBoundary_82) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_82, Int64MinBoundary_82) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_82, EmptyNameString_82) {
    Object obj(objName, std::string(""));
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_82, EmptyStringObject_82) {
    Object obj(objString, std::string(""));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_82, EmptyCmdString_82) {
    Object obj(objCmd, std::string(""));
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}
