#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object class
class ObjectTest_72 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_72, DefaultConstructorCreatesNoneObject_72) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_72, BoolConstructorCreatesBoolObject_72) {
    Object objTrue(true);
    EXPECT_TRUE(objTrue.isBool());
    EXPECT_EQ(objTrue.getType(), objBool);
    EXPECT_TRUE(objTrue.getBool());

    Object objFalse(false);
    EXPECT_TRUE(objFalse.isBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectTest_72, IntConstructorCreatesIntObject_72) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_72, IntConstructorWithZero_72) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_72, IntConstructorWithNegative_72) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_72, RealConstructorCreatesRealObject_72) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_72, RealConstructorWithZero_72) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_72, RealConstructorWithNegative_72) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_72, Int64ConstructorCreatesInt64Object_72) {
    long long val = 9223372036854775807LL; // max long long
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_72, StringConstructorCreatesStringObject_72) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_72, NameConstructorCreatesNameObject_72) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_72, CmdConstructorCreatesCmdObject_72) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

TEST_F(ObjectTest_72, HexStringConstructor_72) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_72, NullFactoryCreatesNullObject_72) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_72, EofFactoryCreatesEofObject_72) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_72, ErrorFactoryCreatesErrorObject_72) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking (is*) Methods ====================

TEST_F(ObjectTest_72, IsIntReturnsTrueForInt_72) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isString());
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
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_72, IsNumReturnsTrueForInt_72) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_72, IsNumReturnsTrueForReal_72) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_72, IsNumReturnsFalseForNonNumeric_72) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_72, IsIntOrInt64ReturnsTrueForInt_72) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_72, IsIntOrInt64ReturnsTrueForInt64_72) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_72, IsIntOrInt64ReturnsFalseForReal_72) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_72, GetNumReturnsIntAsDouble_72) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_72, GetNumReturnsRealValue_72) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_72, GetNumWithOkFlagForInt_72) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_72, GetNumWithOkFlagForReal_72) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_72, GetIntOrInt64ReturnsIntValue_72) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_72, GetIntOrInt64ReturnsInt64Value_72) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_72, MoveConstructorTransfersOwnership_72) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_72, MoveAssignmentTransfersOwnership_72) {
    Object obj1(42);
    Object obj2(3.14);
    
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== Copy Method ====================

TEST_F(ObjectTest_72, CopyCreatesIdenticalObject_72) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_72, CopyOfBoolObject_72) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_72, CopyOfRealObject_72) {
    Object obj(2.71828);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.71828);
}

TEST_F(ObjectTest_72, CopyOfNullObject_72) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_72, CopyOfStringObject_72) {
    Object obj(std::string("test string"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

TEST_F(ObjectTest_72, CopyOfNameObject_72) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== setToNull ====================

TEST_F(ObjectTest_72, SetToNullChangesObjectToNull_72) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// ==================== isName with string parameter ====================

TEST_F(ObjectTest_72, IsNameWithMatchingString_72) {
    Object obj(objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
}

TEST_F(ObjectTest_72, IsNameWithNonMatchingString_72) {
    Object obj(objName, "Catalog");
    EXPECT_FALSE(obj.isName("Page"));
}

TEST_F(ObjectTest_72, IsNameReturnsFalseForNonNameObject_72) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ==================== isCmd with string parameter ====================

TEST_F(ObjectTest_72, IsCmdWithMatchingString_72) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_72, IsCmdWithNonMatchingString_72) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_72, IsCmdReturnsFalseForNonCmdObject_72) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ==================== getTypeName ====================

TEST_F(ObjectTest_72, GetTypeNameForBool_72) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_72, GetTypeNameForInt_72) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_72, GetTypeNameForNull_72) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== getNumWithDefaultValue ====================

TEST_F(ObjectTest_72, GetNumWithDefaultValueReturnsValueForInt_72) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_72, GetNumWithDefaultValueReturnsValueForReal_72) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_72, GetNumWithDefaultValueReturnsDefaultForNonNum_72) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

// ==================== getBoolWithDefaultValue ====================

TEST_F(ObjectTest_72, GetBoolWithDefaultValueReturnsBoolValue_72) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_72, GetBoolWithDefaultValueReturnsDefaultForNonBool_72) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== getNameString ====================

TEST_F(ObjectTest_72, GetNameStringReturnsCorrectString_72) {
    Object obj(objName, "TestName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "TestName");
}

// ==================== Array Operations ====================

TEST_F(ObjectTest_72, ArrayObjectCreation_72) {
    // Create an Array - we need to create it without XRef for simple tests
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_72, ArrayGetLengthOnEmptyArray_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_72, ArrayAddIncreasesLength_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_72, ArrayAddMultipleElements_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_72, ArrayGetReturnsCorrectElement_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_72, ArrayGetNFReturnsCorrectElement_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_72, ArrayRemoveDecreasesLength_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

// ==================== Dict Operations ====================

TEST_F(ObjectTest_72, DictObjectCreation_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_72, DictGetLengthOnEmptyDict_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_72, DictAddIncreasesLength_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_72, DictLookupReturnsCorrectValue_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("TestKey", Object(42));
    Object val = obj.dictLookup("TestKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_72, DictLookupNFReturnsCorrectValue_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("TestKey", Object(42));
    const Object &val = obj.dictLookupNF("TestKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_72, DictLookupNonExistentKeyReturnsNull_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_72, DictSetOverwritesExistingValue_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(42));
    obj.dictSet("Key", Object(100));
    Object val = obj.dictLookup("Key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_72, DictRemoveDecreasesLength_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(1));
    obj.dictAdd("Key2", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_72, DictGetKeyReturnsCorrectKey_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_72, DictGetValReturnsCorrectValue_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_72, DictGetValNFReturnsCorrectValue_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== Boundary Conditions ====================

TEST_F(ObjectTest_72, IntMaxValue_72) {
    Object obj(INT_MAX);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

TEST_F(ObjectTest_72, IntMinValue_72) {
    Object obj(INT_MIN);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

TEST_F(ObjectTest_72, Int64MaxValue_72) {
    long long maxVal = LLONG_MAX;
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_72, Int64MinValue_72) {
    long long minVal = LLONG_MIN;
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

TEST_F(ObjectTest_72, EmptyStringName_72) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_72, EmptyStringCmd_72) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Error and EOF types ====================

TEST_F(ObjectTest_72, ErrorObjectIsNotOtherTypes_72) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_72, EOFObjectIsNotOtherTypes_72) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
}

// ==================== Multiple operations on same object ====================

TEST_F(ObjectTest_72, SetToNullThenCheckType_72) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_72, MoveAssignDifferentTypes_72) {
    Object intObj(42);
    Object realObj(3.14);
    
    intObj = std::move(realObj);
    EXPECT_TRUE(intObj.isReal());
    EXPECT_DOUBLE_EQ(intObj.getReal(), 3.14);
}

// ==================== getArray and getDict accessors ====================

TEST_F(ObjectTest_72, GetArrayReturnsNonNull_72) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_NE(obj.getArray(), nullptr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_72, GetDictReturnsNonNull_72) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_NE(obj.getDict(), nullptr);
    EXPECT_EQ(obj.getDict(), dict);
}

// ==================== DeepCopy Test ====================

TEST_F(ObjectTest_72, DeepCopyOfInt_72) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_72, DeepCopyOfReal_72) {
    Object obj(3.14);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isReal());
    EXPECT_DOUBLE_EQ(deep.getReal(), 3.14);
}

TEST_F(ObjectTest_72, DeepCopyOfString_72) {
    Object obj(std::string("deep copy test"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
}

TEST_F(ObjectTest_72, DeepCopyOfNull_72) {
    Object obj = Object::null();
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isNull());
}
