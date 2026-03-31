#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_105 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_105, DefaultConstructor_IsNone_105) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_105, BoolConstructor_True_105) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_105, BoolConstructor_False_105) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_105, IntConstructor_105) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_105, IntConstructor_Negative_105) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_105, IntConstructor_Zero_105) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_105, RealConstructor_105) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_105, RealConstructor_Zero_105) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_105, RealConstructor_Negative_105) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_105, Int64Constructor_105) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_105, Int64Constructor_Negative_105) {
    long long val = -123456789012345LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_105, NullFactory_105) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_105, EofFactory_105) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_105, ErrorFactory_105) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Methods ====================

TEST_F(ObjectTest_105, IsNum_ForInt_105) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_105, IsNum_ForReal_105) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_105, IsNum_ForNonNumeric_105) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_105, IsIntOrInt64_ForInt_105) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_105, IsIntOrInt64_ForInt64_105) {
    Object obj(123456789012345LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_105, IsIntOrInt64_ForReal_105) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_105, GetNum_FromInt_105) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_105, GetNum_FromReal_105) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_105, GetIntOrInt64_FromInt_105) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_105, GetIntOrInt64_FromInt64_105) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_105, GetNumWithDefaultValue_ForInt_105) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 42.0);
}

TEST_F(ObjectTest_105, GetNumWithDefaultValue_ForReal_105) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

TEST_F(ObjectTest_105, GetNumWithDefaultValue_ForNonNumeric_105) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_105, GetNumWithDefaultValue_ForNull_105) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(55.5), 55.5);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_105, GetBoolWithDefaultValue_ForBool_105) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_105, GetBoolWithDefaultValue_ForNonBool_105) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_105, GetBoolWithDefaultValue_DefaultTrue_105) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== Move Semantics ====================

TEST_F(ObjectTest_105, MoveConstructor_105) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // obj1 should be in a valid but unspecified state (typically none or dead)
}

TEST_F(ObjectTest_105, MoveAssignment_105) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_105, SetToNull_FromInt_105) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_105, SetToNull_FromBool_105) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== String Constructor Tests ====================

TEST_F(ObjectTest_105, StringConstructor_Name_105) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_105, StringConstructor_Cmd_105) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

TEST_F(ObjectTest_105, IsName_WithMatching_105) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName("MyName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_105, IsCmd_WithMatching_105) {
    Object obj(objCmd, "MyCmd");
    EXPECT_TRUE(obj.isCmd("MyCmd"));
    EXPECT_FALSE(obj.isCmd("OtherCmd"));
}

TEST_F(ObjectTest_105, GetNameString_105) {
    Object obj(objName, "TestName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "TestName");
}

// ==================== String Object Tests ====================

TEST_F(ObjectTest_105, StringObjectFromRvalue_105) {
    Object obj(objString, std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_105, HexStringObject_105) {
    Object obj(objHexString, std::string("ABCD"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_105, Copy_IntObject_105) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_105, Copy_BoolObject_105) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_105, Copy_RealObject_105) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_105, Copy_NullObject_105) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_105, Copy_NameObject_105) {
    Object obj(objName, "CopyTest");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyTest");
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_105, GetTypeName_Bool_105) {
    Object obj(true);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_105, GetTypeName_Int_105) {
    Object obj(42);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_105, GetTypeName_Null_105) {
    Object obj = Object::null();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_105, GetTypeName_None_105) {
    Object obj;
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_105, ArrayObject_105) {
    // Create an Array object - need to verify we can create and use it
    // Since Array requires an XRef, we test with nullptr if possible
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_105, ArrayAdd_105) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_105, ArrayGet_105) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_105, ArrayRemove_105) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_105, ArrayGetNF_105) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object& elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_105, ArrayMultipleElements_105) {
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

// ==================== Dict Tests ====================

TEST_F(ObjectTest_105, DictObject_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_105, DictAdd_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_105, DictLookup_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_105, DictLookup_NonExistent_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_105, DictSet_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_105, DictRemove_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_105, DictGetKey_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(42));
    const char* key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_105, DictGetVal_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_105, DictGetValNF_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    const Object& val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_105, DictLookupNF_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(42));
    const Object& val = obj.dictLookupNF("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_105, DictMultipleEntries_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// ==================== Negative Type Checks ====================

TEST_F(ObjectTest_105, IntIsNotBool_105) {
    Object obj(42);
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

TEST_F(ObjectTest_105, BoolIsNotInt_105) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_105, NullIsNotOtherTypes_105) {
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

// ==================== DeepCopy Tests ====================

TEST_F(ObjectTest_105, DeepCopy_IntObject_105) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_105, DeepCopy_NameObject_105) {
    Object obj(objName, "DeepCopyTest");
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "DeepCopyTest");
}

// ==================== Boundary Value Tests ====================

TEST_F(ObjectTest_105, IntMaxValue_105) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_105, IntMinValue_105) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_105, Int64MaxValue_105) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_105, Int64MinValue_105) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_105, RealMaxValue_105) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());
}

TEST_F(ObjectTest_105, RealMinPositiveValue_105) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

// ==================== Empty String/Name Tests ====================

TEST_F(ObjectTest_105, EmptyName_105) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_105, EmptyCmd_105) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== getNum with ok parameter Tests ====================

TEST_F(ObjectTest_105, GetNumWithOk_ForInt_105) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_105, GetNumWithOk_ForReal_105) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Destructor / RAII Tests ====================

TEST_F(ObjectTest_105, DestructorDoesNotCrash_Int_105) {
    { Object obj(42); }
    SUCCEED();
}

TEST_F(ObjectTest_105, DestructorDoesNotCrash_Name_105) {
    { Object obj(objName, "test"); }
    SUCCEED();
}

TEST_F(ObjectTest_105, DestructorDoesNotCrash_Array_105) {
    { Object obj(new Array(nullptr)); }
    SUCCEED();
}

TEST_F(ObjectTest_105, DestructorDoesNotCrash_Dict_105) {
    { Object obj(new Dict(nullptr)); }
    SUCCEED();
}

// ==================== getArray / getDict accessor Tests ====================

TEST_F(ObjectTest_105, GetArray_ReturnsNonNull_105) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_105, GetDict_ReturnsNonNull_105) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}

// ==================== MoveAssignment self-consistency ====================

TEST_F(ObjectTest_105, MoveAssignment_DifferentTypes_105) {
    Object obj1(42);
    Object obj2(true);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isBool());
    EXPECT_TRUE(obj1.getBool());
}

TEST_F(ObjectTest_105, MoveAssignment_ToNull_105) {
    Object obj1(42);
    Object obj2 = Object::null();
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isNull());
}
