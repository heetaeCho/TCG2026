#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object class
class ObjectTest_75 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor and Type Tests ====================

TEST_F(ObjectTest_75, DefaultConstructor_IsNone_75) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_75, BoolConstructor_True_75) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_75, BoolConstructor_False_75) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_75, IntConstructor_75) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_75, IntConstructor_Zero_75) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_75, IntConstructor_Negative_75) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_75, RealConstructor_75) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_75, RealConstructor_Zero_75) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_75, RealConstructor_Negative_75) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_75, Int64Constructor_75) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_75, StringConstructor_WithGooString_75) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_75, StringConstructor_WithStdString_75) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_75, NameConstructor_75) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_75, CmdConstructor_75) {
    Object obj(objCmd, "MyCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "MyCmd");
}

TEST_F(ObjectTest_75, HexStringConstructor_75) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_75, NullFactory_75) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_75, EofFactory_75) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_75, ErrorFactory_75) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking (is* methods) ====================

TEST_F(ObjectTest_75, IsBool_OnNonBool_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_75, IsInt_OnNonInt_75) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_75, IsReal_OnNonReal_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_75, IsString_OnNonString_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_75, IsString_OnString_75) {
    std::string s = "hello";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_75, IsHexString_OnNonHexString_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_75, IsName_OnNonName_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isName());
}

TEST_F(ObjectTest_75, IsNull_OnNonNull_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_75, IsArray_OnNonArray_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_75, IsDict_OnNonDict_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_75, IsStream_OnNonStream_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_75, IsRef_OnNonRef_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_75, IsCmd_OnNonCmd_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_75, IsError_OnNonError_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_75, IsEOF_OnNonEOF_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_75, IsNone_OnNonNone_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_75, IsInt64_OnNonInt64_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isInt64());
}

// ==================== isNum Tests ====================

TEST_F(ObjectTest_75, IsNum_OnInt_75) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_75, IsNum_OnReal_75) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_75, IsNum_OnNonNum_75) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// ==================== isIntOrInt64 Tests ====================

TEST_F(ObjectTest_75, IsIntOrInt64_OnInt_75) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_75, IsIntOrInt64_OnInt64_75) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_75, IsIntOrInt64_OnReal_75) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_75, GetNum_OnInt_75) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_75, GetNum_OnReal_75) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_75, GetIntOrInt64_OnInt_75) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_75, GetIntOrInt64_OnInt64_75) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== isName with argument Tests ====================

TEST_F(ObjectTest_75, IsName_WithMatchingName_75) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_75, IsName_WithNonMatchingName_75) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_75, IsName_OnNonNameObject_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ==================== isCmd with argument Tests ====================

TEST_F(ObjectTest_75, IsCmd_WithMatchingCmd_75) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd("TestCmd"));
}

TEST_F(ObjectTest_75, IsCmd_WithNonMatchingCmd_75) {
    Object obj(objCmd, "TestCmd");
    EXPECT_FALSE(obj.isCmd("OtherCmd"));
}

TEST_F(ObjectTest_75, IsCmd_OnNonCmdObject_75) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_75, MoveConstructor_75) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_75, MoveAssignment_75) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_75, SetToNull_75) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== copy Tests ====================

TEST_F(ObjectTest_75, Copy_Int_75) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_75, Copy_Bool_75) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_75, Copy_Real_75) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_75, Copy_Null_75) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_75, Copy_String_75) {
    std::string s = "hello";
    Object obj(std::move(s));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

TEST_F(ObjectTest_75, Copy_Name_75) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_75, GetTypeName_Bool_75) {
    Object obj(true);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_75, GetTypeName_Int_75) {
    Object obj(42);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_75, GetTypeName_Null_75) {
    Object obj = Object::null();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_75, GetNumWithDefaultValue_OnInt_75) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_75, GetNumWithDefaultValue_OnReal_75) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_75, GetNumWithDefaultValue_OnNonNum_75) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_75, GetBoolWithDefaultValue_OnBool_75) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_75, GetBoolWithDefaultValue_OnBoolFalse_75) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_75, GetBoolWithDefaultValue_OnNonBool_75) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_75, GetBoolWithDefaultValue_OnNonBoolFalseDefault_75) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array Operations ====================

TEST_F(ObjectTest_75, ArrayObject_Creation_75) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_75, ArrayGetLength_Empty_75) {
    Object obj(new Array(nullptr));
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_75, ArrayAdd_And_GetLength_75) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_75, ArrayAdd_Multiple_75) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_75, ArrayGet_75) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_75, ArrayGetNF_75) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    const Object& elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_75, ArrayRemove_75) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

// ==================== Dict Operations ====================

TEST_F(ObjectTest_75, DictObject_Creation_75) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_75, DictGetLength_Empty_75) {
    Object obj(new Dict(nullptr));
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_75, DictAdd_And_GetLength_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_75, DictAdd_Multiple_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(1));
    obj.dictAdd("key2", Object(2));
    obj.dictAdd("key3", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

TEST_F(ObjectTest_75, DictLookup_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(99));
    Object val = obj.dictLookup("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_75, DictLookup_NonExistent_75) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_75, DictLookupNF_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(77));
    const Object& val = obj.dictLookupNF("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_75, DictGetKey_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("testkey", Object(1));
    const char* key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "testkey");
}

TEST_F(ObjectTest_75, DictGetVal_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_75, DictGetValNF_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    const Object& val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_75, DictSet_UpdatesExisting_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_75, DictRemove_75) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(43));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

// ==================== getNameString Tests ====================

TEST_F(ObjectTest_75, GetNameString_75) {
    Object obj(objName, "SomeName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "SomeName");
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_75, TakeString_75) {
    std::string s = "take me";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_75, GetNum_WithOk_OnInt_75) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_75, GetNum_WithOk_OnReal_75) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Destructor and Lifecycle ====================

TEST_F(ObjectTest_75, DestructorDoesNotCrash_Int_75) {
    { Object obj(42); }
    SUCCEED();
}

TEST_F(ObjectTest_75, DestructorDoesNotCrash_String_75) {
    { 
        std::string s = "test";
        Object obj(std::move(s)); 
    }
    SUCCEED();
}

TEST_F(ObjectTest_75, DestructorDoesNotCrash_Null_75) {
    { Object obj = Object::null(); }
    SUCCEED();
}

TEST_F(ObjectTest_75, DestructorDoesNotCrash_Array_75) {
    { Object obj(new Array(nullptr)); }
    SUCCEED();
}

TEST_F(ObjectTest_75, DestructorDoesNotCrash_Dict_75) {
    { Object obj(new Dict(nullptr)); }
    SUCCEED();
}

// ==================== Edge Cases ====================

TEST_F(ObjectTest_75, MoveAssignmentOverwrite_75) {
    Object obj1(42);
    Object obj2(3.14);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isReal());
    EXPECT_DOUBLE_EQ(obj1.getReal(), 3.14);
}

TEST_F(ObjectTest_75, EmptyStringConstruction_75) {
    std::string s = "";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_75, NameWithEmptyString_75) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
}

TEST_F(ObjectTest_75, IntMaxValue_75) {
    Object obj(INT_MAX);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

TEST_F(ObjectTest_75, IntMinValue_75) {
    Object obj(INT_MIN);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

TEST_F(ObjectTest_75, Int64MaxValue_75) {
    long long val = LLONG_MAX;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_75, RealInfinity_75) {
    Object obj(std::numeric_limits<double>::infinity());
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectTest_75, CopyPreservesOriginal_75) {
    Object obj(42);
    Object copied = obj.copy();
    // Original should still be valid
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    // Copy should also be valid
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}
