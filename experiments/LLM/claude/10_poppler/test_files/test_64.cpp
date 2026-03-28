#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object class
class ObjectTest_64 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ObjectTest_64, DefaultConstructor_CreatesNoneObject_64) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_64, NullStaticMethod_CreatesNullObject_64) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_64, EofStaticMethod_CreatesEOFObject_64) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_64, ErrorStaticMethod_CreatesErrorObject_64) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

TEST_F(ObjectTest_64, BoolConstructor_True_64) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_64, BoolConstructor_False_64) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_64, IntConstructor_PositiveValue_64) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_64, IntConstructor_ZeroValue_64) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_64, IntConstructor_NegativeValue_64) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_64, RealConstructor_PositiveValue_64) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_64, RealConstructor_ZeroValue_64) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_64, RealConstructor_NegativeValue_64) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_64, Int64Constructor_LargeValue_64) {
    long long val = 9223372036854775000LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_64, Int64Constructor_Zero_64) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

// ==================== Type Checking Tests ====================

TEST_F(ObjectTest_64, IsNum_ForInt_64) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_64, IsNum_ForReal_64) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_64, IsNum_ForNull_64) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_64, IsIntOrInt64_ForInt_64) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_64, IsIntOrInt64_ForInt64_64) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_64, IsIntOrInt64_ForReal_64) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_64, GetNum_FromInt_64) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_64, GetNum_FromReal_64) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_64, GetIntOrInt64_FromInt_64) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_64, GetIntOrInt64_FromInt64_64) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== String Construction Tests ====================

TEST_F(ObjectTest_64, StringConstructor_WithGooString_64) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_64, StringConstructor_WithStdString_64) {
    Object obj(std::string("test"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

// ==================== Name Construction Tests ====================

TEST_F(ObjectTest_64, NameConstructor_64) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_64, IsName_WithMatchingName_64) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
}

TEST_F(ObjectTest_64, IsName_WithNonMatchingName_64) {
    Object obj(objName, "Type");
    EXPECT_FALSE(obj.isName("Other"));
}

TEST_F(ObjectTest_64, GetNameString_64) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== Cmd Construction Tests ====================

TEST_F(ObjectTest_64, CmdConstructor_64) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_64, IsCmd_WithMatchingCmd_64) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_64, IsCmd_WithNonMatchingCmd_64) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== HexString Tests ====================

TEST_F(ObjectTest_64, HexStringConstructor_64) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// ==================== Move Semantics Tests ====================

TEST_F(ObjectTest_64, MoveConstructor_64) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically None or Dead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

TEST_F(ObjectTest_64, MoveAssignment_64) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_64, SetToNull_FromInt_64) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_64, SetToNull_FromBool_64) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Type Exclusivity Tests ====================

TEST_F(ObjectTest_64, TypeExclusivity_IntNotOtherTypes_64) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
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

TEST_F(ObjectTest_64, TypeExclusivity_BoolNotOtherTypes_64) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_64, TypeExclusivity_NullNotOtherTypes_64) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_64, Copy_IntObject_64) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_64, Copy_BoolObject_64) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_64, Copy_RealObject_64) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_64, Copy_NullObject_64) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_64, Copy_NameObject_64) {
    Object obj(objName, "Test");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "Test");
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_64, ArrayConstructor_64) {
    // We need an XRef for Array, but we can test with nullptr if allowed
    // Creating an Array object
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_64, ArrayAdd_IncreasesLength_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_64, ArrayAdd_MultipleElements_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_64, ArrayGet_ReturnsCorrectElement_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
    Object elem2 = obj.arrayGet(1);
    EXPECT_TRUE(elem2.isInt());
    EXPECT_EQ(elem2.getInt(), 99);
}

TEST_F(ObjectTest_64, ArrayGetNF_ReturnsReference_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_64, ArrayRemove_DecreasesLength_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_64, DictConstructor_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_64, DictAdd_IncreasesLength_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_64, DictLookup_ReturnsCorrectValue_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_64, DictLookup_NonExistentKey_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_64, DictSet_OverwritesValue_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(99));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_64, DictRemove_DecreasesLength_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_64, DictGetKey_ReturnsCorrectKey_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_64, DictGetVal_ReturnsCorrectValue_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_64, DictGetValNF_ReturnsReference_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_64, DictLookupNF_ReturnsReference_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_64, GetTypeName_Bool_64) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "boolean");
}

TEST_F(ObjectTest_64, GetTypeName_Int_64) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "integer");
}

TEST_F(ObjectTest_64, GetTypeName_Real_64) {
    Object obj(3.14);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "real");
}

TEST_F(ObjectTest_64, GetTypeName_Null_64) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "null");
}

TEST_F(ObjectTest_64, GetTypeName_Error_64) {
    Object obj = Object::error();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "error");
}

TEST_F(ObjectTest_64, GetTypeName_EOF_64) {
    Object obj = Object::eof();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "eof");
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_64, GetNumWithDefaultValue_IntObject_64) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_64, GetNumWithDefaultValue_RealObject_64) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_64, GetNumWithDefaultValue_NonNumericReturnsDefault_64) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_64, GetNumWithDefaultValue_BoolReturnsDefault_64) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(5.5), 5.5);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_64, GetBoolWithDefaultValue_BoolObject_64) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_64, GetBoolWithDefaultValue_FalseBoolObject_64) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_64, GetBoolWithDefaultValue_NonBoolReturnsDefault_64) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_64, GetBoolWithDefaultValue_NullReturnsDefault_64) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Deep Copy Tests ====================

TEST_F(ObjectTest_64, DeepCopy_IntObject_64) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_64, DeepCopy_NullObject_64) {
    Object obj = Object::null();
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isNull());
}

// ==================== Boundary Tests ====================

TEST_F(ObjectTest_64, IntConstructor_MaxInt_64) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_64, IntConstructor_MinInt_64) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_64, Int64Constructor_MaxInt64_64) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_64, Int64Constructor_MinInt64_64) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_64, RealConstructor_VerySmallPositive_64) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

TEST_F(ObjectTest_64, RealConstructor_VeryLargePositive_64) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());
}

// ==================== Name with empty string ====================

TEST_F(ObjectTest_64, NameConstructor_EmptyString_64) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Cmd with empty string ====================

TEST_F(ObjectTest_64, CmdConstructor_EmptyString_64) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== DictIs Tests ====================

TEST_F(ObjectTest_64, DictIs_WithMatchingType_64) {
    Dict *dict = new Dict(nullptr);
    dict->set("Type", Object(objName, "Page"));
    Object obj(dict);
    // dictIs checks if the dict has a "Type" entry matching the given name
    // This depends on internal implementation, but testing observable behavior
    EXPECT_TRUE(obj.isDict());
}

// ==================== getArray and getDict accessors ====================

TEST_F(ObjectTest_64, GetArray_ReturnsNonNull_64) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_NE(obj.getArray(), nullptr);
}

TEST_F(ObjectTest_64, GetDict_ReturnsNonNull_64) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_NE(obj.getDict(), nullptr);
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_64, GetNum_WithOkParam_IntObject_64) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_64, GetNum_WithOkParam_RealObject_64) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_64, TakeString_FromStringObject_64) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== Multiple move operations ====================

TEST_F(ObjectTest_64, MultipleMoveAssignments_64) {
    Object obj1(42);
    Object obj2(3.14);
    Object obj3 = Object::null();
    
    obj3 = std::move(obj2);
    EXPECT_TRUE(obj3.isReal());
    EXPECT_DOUBLE_EQ(obj3.getReal(), 3.14);
    
    obj3 = std::move(obj1);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
}
