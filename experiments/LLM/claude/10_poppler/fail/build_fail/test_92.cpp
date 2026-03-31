#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_92 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Constructor and Type Tests
// =============================================================================

TEST_F(ObjectTest_92, DefaultConstructorCreatesNoneObject_92) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_92, BoolConstructorCreatesBoolObject_92) {
    Object objTrue(true);
    EXPECT_TRUE(objTrue.isBool());
    EXPECT_EQ(objTrue.getType(), objBool);
    EXPECT_TRUE(objTrue.getBool());

    Object objFalse(false);
    EXPECT_TRUE(objFalse.isBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectTest_92, IntConstructorCreatesIntObject_92) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_92, IntConstructorWithZero_92) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_92, IntConstructorWithNegativeValue_92) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_92, IntConstructorWithMaxInt_92) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_92, IntConstructorWithMinInt_92) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_92, RealConstructorCreatesRealObject_92) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_92, RealConstructorWithZero_92) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_92, RealConstructorWithNegativeValue_92) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_92, Int64ConstructorCreatesInt64Object_92) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_92, Int64ConstructorWithZero_92) {
    Object obj(0LL);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

TEST_F(ObjectTest_92, Int64ConstructorWithNegativeValue_92) {
    long long val = -1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// =============================================================================
// Static Factory Method Tests
// =============================================================================

TEST_F(ObjectTest_92, NullFactoryCreatesNullObject_92) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_92, EofFactoryCreatesEofObject_92) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_92, ErrorFactoryCreatesErrorObject_92) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// isNum and getNum Tests
// =============================================================================

TEST_F(ObjectTest_92, IntIsNum_92) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_92, RealIsNum_92) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_92, NullIsNotNum_92) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// =============================================================================
// isIntOrInt64 and getIntOrInt64 Tests
// =============================================================================

TEST_F(ObjectTest_92, IntIsIntOrInt64_92) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_92, Int64IsIntOrInt64_92) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_92, RealIsNotIntOrInt64_92) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// =============================================================================
// Type Check Boolean Methods
// =============================================================================

TEST_F(ObjectTest_92, IsBoolReturnsTrueForBool_92) {
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
}

TEST_F(ObjectTest_92, IsIntReturnsTrueForInt_92) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_92, IsRealReturnsTrueForReal_92) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_92, IsNullReturnsTrueForNull_92) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_92, IsErrorReturnsTrueForError_92) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_92, IsEOFReturnsTrueForEOF_92) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_92, IsNoneReturnsTrueForDefault_92) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_FALSE(obj.isNull());
}

// =============================================================================
// Move Constructor and Move Assignment Tests
// =============================================================================

TEST_F(ObjectTest_92, MoveConstructorTransfersOwnership_92) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);

    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically none or dead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

TEST_F(ObjectTest_92, MoveAssignmentTransfersOwnership_92) {
    Object obj1(42);
    Object obj2(3.14);

    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// =============================================================================
// setToNull Test
// =============================================================================

TEST_F(ObjectTest_92, SetToNullChangesTypeToNull_92) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// String Object Tests
// =============================================================================

TEST_F(ObjectTest_92, StringConstructorCreatesStringObject_92) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_92, StdStringConstructorCreatesStringObject_92) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// =============================================================================
// Name Object Tests
// =============================================================================

TEST_F(ObjectTest_92, NameConstructorCreatesNameObject_92) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_92, IsNameWithMatchingString_92) {
    Object obj(objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
    EXPECT_FALSE(obj.isName("Page"));
}

TEST_F(ObjectTest_92, GetNameString_92) {
    Object obj(objName, "SomeName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "SomeName");
}

// =============================================================================
// Cmd Object Tests
// =============================================================================

TEST_F(ObjectTest_92, CmdConstructorCreatesCmdObject_92) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_92, IsCmdWithMatchingString_92) {
    Object obj(objCmd, "ET");
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// =============================================================================
// HexString Object Tests
// =============================================================================

TEST_F(ObjectTest_92, HexStringConstructor_92) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Copy Tests
// =============================================================================

TEST_F(ObjectTest_92, CopyIntObject_92) {
    Object obj1(42);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_92, CopyBoolObject_92) {
    Object obj1(true);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isBool());
    EXPECT_TRUE(obj2.getBool());
}

TEST_F(ObjectTest_92, CopyRealObject_92) {
    Object obj1(2.5);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 2.5);
}

TEST_F(ObjectTest_92, CopyNullObject_92) {
    Object obj1 = Object::null();
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isNull());
}

TEST_F(ObjectTest_92, CopyNameObject_92) {
    Object obj1(objName, "TestName");
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "TestName");
}

// =============================================================================
// getNum with ok parameter
// =============================================================================

TEST_F(ObjectTest_92, GetNumWithOkParamForInt_92) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_92, GetNumWithOkParamForReal_92) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// =============================================================================
// getNumWithDefaultValue Tests
// =============================================================================

TEST_F(ObjectTest_92, GetNumWithDefaultValueForInt_92) {
    Object obj(42);
    double val = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_92, GetNumWithDefaultValueForReal_92) {
    Object obj(3.14);
    double val = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(ObjectTest_92, GetNumWithDefaultValueForNonNum_92) {
    Object obj = Object::null();
    double val = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(val, 99.0);
}

// =============================================================================
// getBoolWithDefaultValue Tests
// =============================================================================

TEST_F(ObjectTest_92, GetBoolWithDefaultValueForBoolTrue_92) {
    Object obj(true);
    bool val = obj.getBoolWithDefaultValue(false);
    EXPECT_TRUE(val);
}

TEST_F(ObjectTest_92, GetBoolWithDefaultValueForBoolFalse_92) {
    Object obj(false);
    bool val = obj.getBoolWithDefaultValue(true);
    EXPECT_FALSE(val);
}

TEST_F(ObjectTest_92, GetBoolWithDefaultValueForNonBool_92) {
    Object obj(42);
    bool val = obj.getBoolWithDefaultValue(true);
    EXPECT_TRUE(val);
}

// =============================================================================
// getTypeName Tests
// =============================================================================

TEST_F(ObjectTest_92, GetTypeNameForInt_92) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_92, GetTypeNameForBool_92) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_92, GetTypeNameForNull_92) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// =============================================================================
// Array Object Tests
// =============================================================================

TEST_F(ObjectTest_92, ArrayObjectBasicOperations_92) {
    // Create array through the Object constructor
    // We need to create an Array first - but Array requires an XRef
    // We'll use nullptr for XRef if the constructor allows it
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_92, ArrayAddAndGetLength_92) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(3.14));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_92, ArrayGetElement_92) {
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

TEST_F(ObjectTest_92, ArrayGetNF_92) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));

    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_92, ArrayRemove_92) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);

    Object elem0 = obj.arrayGet(0);
    EXPECT_EQ(elem0.getInt(), 1);
    Object elem1 = obj.arrayGet(1);
    EXPECT_EQ(elem1.getInt(), 3);
}

// =============================================================================
// Dict Object Tests
// =============================================================================

TEST_F(ObjectTest_92, DictObjectBasicOperations_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_92, DictAddAndLookup_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_92, DictSetOverwritesExisting_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_92, DictRemove_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 2);

    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_92, DictGetKey_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Alpha", Object(1));
    obj.dictAdd("Beta", Object(2));

    const char *key0 = obj.dictGetKey(0);
    const char *key1 = obj.dictGetKey(1);
    EXPECT_NE(key0, nullptr);
    EXPECT_NE(key1, nullptr);
}

TEST_F(ObjectTest_92, DictGetVal_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));

    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_92, DictGetValNF_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));

    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_92, DictLookupNF_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));

    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_92, DictLookupNonExistentKey_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));

    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

// =============================================================================
// Destructor and Cleanup
// =============================================================================

TEST_F(ObjectTest_92, DestructorDoesNotCrashForPrimitives_92) {
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
    // If we get here without crashing, the test passes
    SUCCEED();
}

// =============================================================================
// Int64 boundary tests
// =============================================================================

TEST_F(ObjectTest_92, Int64MaxValue_92) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_92, Int64MinValue_92) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// =============================================================================
// Multiple type checks on same object
// =============================================================================

TEST_F(ObjectTest_92, OnlyOneTypeCheckReturnsTrue_92) {
    Object obj(42);
    int trueCount = 0;
    trueCount += obj.isBool() ? 1 : 0;
    trueCount += obj.isInt() ? 1 : 0;
    trueCount += obj.isReal() ? 1 : 0;
    trueCount += obj.isString() ? 1 : 0;
    trueCount += obj.isHexString() ? 1 : 0;
    trueCount += obj.isName() ? 1 : 0;
    trueCount += obj.isNull() ? 1 : 0;
    trueCount += obj.isArray() ? 1 : 0;
    trueCount += obj.isDict() ? 1 : 0;
    trueCount += obj.isStream() ? 1 : 0;
    trueCount += obj.isRef() ? 1 : 0;
    trueCount += obj.isCmd() ? 1 : 0;
    trueCount += obj.isError() ? 1 : 0;
    trueCount += obj.isEOF() ? 1 : 0;
    trueCount += obj.isNone() ? 1 : 0;
    trueCount += obj.isInt64() ? 1 : 0;
    EXPECT_EQ(trueCount, 1);
}

// =============================================================================
// DeepCopy Tests
// =============================================================================

TEST_F(ObjectTest_92, DeepCopyIntObject_92) {
    Object obj1(42);
    Object obj2 = obj1.deepCopy();
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_92, DeepCopyNameObject_92) {
    Object obj1(objName, "TestDeepCopy");
    Object obj2 = obj1.deepCopy();
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "TestDeepCopy");
}

// =============================================================================
// String takeString test
// =============================================================================

TEST_F(ObjectTest_92, TakeStringTransfersOwnership_92) {
    Object obj(std::make_unique<GooString>("hello world"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// =============================================================================
// getArray and getDict accessors
// =============================================================================

TEST_F(ObjectTest_92, GetArrayReturnsArrayPointer_92) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_92, GetDictReturnsDictPointer_92) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}
