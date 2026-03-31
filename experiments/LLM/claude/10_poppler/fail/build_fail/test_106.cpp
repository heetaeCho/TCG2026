#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_106 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Type Tests ====================

TEST_F(ObjectTest_106, DefaultConstructor_IsNone_106) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_106, BoolConstructor_True_106) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_106, BoolConstructor_False_106) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_106, IntConstructor_106) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_106, IntConstructor_Negative_106) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_106, IntConstructor_Zero_106) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_106, RealConstructor_106) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_106, RealConstructor_Zero_106) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_106, RealConstructor_Negative_106) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_106, Int64Constructor_106) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_106, Int64Constructor_Negative_106) {
    long long val = -9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_106, NullFactory_106) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_106, EofFactory_106) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_106, ErrorFactory_106) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== isNum and getNum Tests ====================

TEST_F(ObjectTest_106, IsNum_Int_106) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 5.0);
}

TEST_F(ObjectTest_106, IsNum_Real_106) {
    Object obj(2.5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.5);
}

TEST_F(ObjectTest_106, IsNum_Null_106) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// ==================== isIntOrInt64 and getIntOrInt64 Tests ====================

TEST_F(ObjectTest_106, IsIntOrInt64_Int_106) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_106, IsIntOrInt64_Int64_106) {
    long long val = 123456789012LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_106, IsIntOrInt64_Real_106) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== Type Checking Negative Tests ====================

TEST_F(ObjectTest_106, IsBool_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_106, IsInt_OnBool_106) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_106, IsReal_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_106, IsString_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_106, IsArray_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_106, IsDict_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_106, IsStream_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_106, IsRef_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_106, IsCmd_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_106, IsError_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_106, IsEOF_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_106, IsNone_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_106, IsNull_OnInt_106) {
    Object obj(42);
    EXPECT_FALSE(obj.isNull());
}

// ==================== Move Semantics ====================

TEST_F(ObjectTest_106, MoveConstructor_106) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically objNone)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_106, MoveAssignment_106) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_106, MoveConstructor_Bool_106) {
    Object obj1(true);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isBool());
    EXPECT_TRUE(obj2.getBool());
}

TEST_F(ObjectTest_106, MoveAssignment_Real_106) {
    Object obj1(3.14);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

// ==================== setToNull ====================

TEST_F(ObjectTest_106, SetToNull_FromInt_106) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_106, SetToNull_FromBool_106) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_106, SetToNull_FromNone_106) {
    Object obj;
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== String Construction ====================

TEST_F(ObjectTest_106, StringConstructor_GooString_106) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_106, StringConstructor_StdString_106) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

// ==================== Name Construction ====================

TEST_F(ObjectTest_106, NameConstructor_106) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    ASSERT_NE(obj.getName(), nullptr);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_106, IsName_WithMatch_106) {
    Object obj(objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
}

TEST_F(ObjectTest_106, IsName_WithNoMatch_106) {
    Object obj(objName, "Catalog");
    EXPECT_FALSE(obj.isName("Pages"));
}

TEST_F(ObjectTest_106, NameString_106) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== Cmd Construction ====================

TEST_F(ObjectTest_106, CmdConstructor_106) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    ASSERT_NE(obj.getCmd(), nullptr);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_106, IsCmd_WithMatch_106) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_106, IsCmd_WithNoMatch_106) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== HexString Construction ====================

TEST_F(ObjectTest_106, HexStringConstructor_106) {
    Object obj(objHexString, "48656C6C6F");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// ==================== getTypeName ====================

TEST_F(ObjectTest_106, GetTypeName_Bool_106) {
    Object obj(true);
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "boolean");
}

TEST_F(ObjectTest_106, GetTypeName_Int_106) {
    Object obj(42);
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "integer");
}

TEST_F(ObjectTest_106, GetTypeName_Real_106) {
    Object obj(3.14);
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "real");
}

TEST_F(ObjectTest_106, GetTypeName_Null_106) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "null");
}

TEST_F(ObjectTest_106, GetTypeName_Error_106) {
    Object obj = Object::error();
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "error");
}

TEST_F(ObjectTest_106, GetTypeName_EOF_106) {
    Object obj = Object::eof();
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "eof");
}

TEST_F(ObjectTest_106, GetTypeName_None_106) {
    Object obj;
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "none");
}

// ==================== getNumWithDefaultValue ====================

TEST_F(ObjectTest_106, GetNumWithDefaultValue_Int_106) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 10.0);
}

TEST_F(ObjectTest_106, GetNumWithDefaultValue_Real_106) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 2.5);
}

TEST_F(ObjectTest_106, GetNumWithDefaultValue_NonNum_106) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_106, GetNumWithDefaultValue_Bool_106) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue ====================

TEST_F(ObjectTest_106, GetBoolWithDefaultValue_Bool_106) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_106, GetBoolWithDefaultValue_NonBool_106) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_106, GetBoolWithDefaultValue_NonBool_DefaultTrue_106) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== copy ====================

TEST_F(ObjectTest_106, Copy_Int_106) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_106, Copy_Bool_106) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_106, Copy_Real_106) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_106, Copy_Null_106) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_106, Copy_Name_106) {
    Object obj(objName, "Test");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "Test");
}

TEST_F(ObjectTest_106, Copy_String_106) {
    Object obj(std::make_unique<GooString>("hello"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
}

TEST_F(ObjectTest_106, Copy_Int64_106) {
    long long val = 123456789012LL;
    Object obj(val);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), val);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_106, Array_Basic_106) {
    // Create an Array object (requires XRef, but let's try with nullptr)
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_106, Array_AddAndGetLength_106) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_106, Array_Get_106) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(99));
    Object val = obj.arrayGet(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
    Object val2 = obj.arrayGet(1);
    EXPECT_TRUE(val2.isInt());
    EXPECT_EQ(val2.getInt(), 99);
}

TEST_F(ObjectTest_106, Array_GetNF_106) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &val = obj.arrayGetNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_106, Array_Remove_106) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    // After removing index 1, the element at index 1 should be the old element at index 2
    Object val = obj.arrayGet(1);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 3);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_106, Dict_Basic_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_106, Dict_AddAndLookup_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_106, Dict_LookupNonExistent_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_106, Dict_SetOverwrite_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(99));
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_106, Dict_Remove_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_106, Dict_GetKey_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Alpha", Object(1));
    const char *key = obj.dictGetKey(0);
    ASSERT_NE(key, nullptr);
    EXPECT_STREQ(key, "Alpha");
}

TEST_F(ObjectTest_106, Dict_GetVal_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_106, Dict_GetValNF_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_106, Dict_LookupNF_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_106, GetNum_WithOk_Int_106) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_106, GetNum_WithOk_Real_106) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ObjectTest_106, IntBoundary_MaxInt_106) {
    Object obj(INT_MAX);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MAX);
}

TEST_F(ObjectTest_106, IntBoundary_MinInt_106) {
    Object obj(INT_MIN);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), INT_MIN);
}

TEST_F(ObjectTest_106, Int64Boundary_MaxInt64_106) {
    long long val = LLONG_MAX;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_106, Int64Boundary_MinInt64_106) {
    long long val = LLONG_MIN;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_106, EmptyName_106) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_106, EmptyCmd_106) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Multiple Moves ====================

TEST_F(ObjectTest_106, ChainedMoveAssignment_106) {
    Object obj1(42);
    Object obj2(3.14);
    Object obj3;
    obj3 = std::move(obj2);
    obj3 = std::move(obj1);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);
}

// ==================== Destructor Safety ====================

TEST_F(ObjectTest_106, DestructorAfterMove_106) {
    Object *obj1 = new Object(42);
    Object obj2(std::move(*obj1));
    delete obj1; // Should not crash
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== takeString ====================

TEST_F(ObjectTest_106, TakeString_106) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> str = obj.takeString();
    ASSERT_NE(str, nullptr);
}

// ==================== Dict Multiple Entries ====================

TEST_F(ObjectTest_106, Dict_MultipleEntries_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object valA = obj.dictLookup("A");
    EXPECT_EQ(valA.getInt(), 1);
    Object valB = obj.dictLookup("B");
    EXPECT_EQ(valB.getInt(), 2);
    Object valC = obj.dictLookup("C");
    EXPECT_EQ(valC.getInt(), 3);
}

// ==================== Array with Mixed Types ====================

TEST_F(ObjectTest_106, Array_MixedTypes_106) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    obj.arrayAdd(Object::null());

    EXPECT_EQ(obj.arrayGetLength(), 4);

    Object v0 = obj.arrayGet(0);
    EXPECT_TRUE(v0.isInt());
    EXPECT_EQ(v0.getInt(), 42);

    Object v1 = obj.arrayGet(1);
    EXPECT_TRUE(v1.isReal());
    EXPECT_DOUBLE_EQ(v1.getReal(), 3.14);

    Object v2 = obj.arrayGet(2);
    EXPECT_TRUE(v2.isBool());
    EXPECT_TRUE(v2.getBool());

    Object v3 = obj.arrayGet(3);
    EXPECT_TRUE(v3.isNull());
}

// ==================== Dict set new key ====================

TEST_F(ObjectTest_106, Dict_SetNewKey_106) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictSet("NewKey", Object(77));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("NewKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// ==================== getRefGen (the specific method in focus) ====================

// Note: getRefGen requires the object to be of type objRef.
// We need a way to construct a ref object. Based on the interface, there doesn't
// seem to be a direct public constructor for ref objects visible here, but
// the copy method and Ref struct suggest there might be one. Since we can't
// find an explicit constructor, we test via observable behavior if possible.

// If there's a static or factory method to create ref objects not shown in the
// partial interface, we test what we can.

// ==================== deepCopy ====================

TEST_F(ObjectTest_106, DeepCopy_Int_106) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_106, DeepCopy_String_106) {
    Object obj(std::make_unique<GooString>("deep"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    ASSERT_NE(deep.getString(), nullptr);
}

// ==================== print (smoke test) ====================

TEST_F(ObjectTest_106, Print_Int_NoFault_106) {
    Object obj(42);
    // Just ensure it doesn't crash
    obj.print(stdout);
}

TEST_F(ObjectTest_106, Print_Null_NoFault_106) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_106, Print_Bool_NoFault_106) {
    Object obj(true);
    obj.print(stdout);
}
