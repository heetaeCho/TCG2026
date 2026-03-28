#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "Stream.h"
#include "GooString.h"

// Helper to create a minimal XRef-free environment
// We test Object's public interface as a black box.

class ObjectTest_103 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction and Type Tests ---

TEST_F(ObjectTest_103, DefaultConstructor_IsNone_103) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_103, BoolConstructor_True_103) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_103, BoolConstructor_False_103) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_103, IntConstructor_103) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_103, IntConstructor_Negative_103) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_103, IntConstructor_Zero_103) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_103, RealConstructor_103) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_103, RealConstructor_Zero_103) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_103, RealConstructor_Negative_103) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_103, Int64Constructor_103) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_103, StringConstructor_103) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_103, StringConstructor_StdString_103) {
    Object obj(std::string("world"));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_103, NameConstructor_103) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_103, CmdConstructor_103) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_103, HexStringConstructor_103) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// --- Static Factory Methods ---

TEST_F(ObjectTest_103, NullFactory_103) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_103, EofFactory_103) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_103, ErrorFactory_103) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// --- Type Checking Methods ---

TEST_F(ObjectTest_103, IsNum_ForInt_103) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_103, IsNum_ForReal_103) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_103, IsNum_ForNonNumeric_103) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_103, IsIntOrInt64_ForInt_103) {
    Object obj(5);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_103, IsIntOrInt64_ForInt64_103) {
    Object obj(static_cast<long long>(123456789012LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_103, IsIntOrInt64_ForReal_103) {
    Object obj(1.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// --- getNum ---

TEST_F(ObjectTest_103, GetNum_FromInt_103) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_103, GetNum_FromReal_103) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_103, GetNum_WithOkFlag_103) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

// --- getIntOrInt64 ---

TEST_F(ObjectTest_103, GetIntOrInt64_FromInt_103) {
    Object obj(99);
    EXPECT_EQ(obj.getIntOrInt64(), 99LL);
}

TEST_F(ObjectTest_103, GetIntOrInt64_FromInt64_103) {
    long long bigVal = 8000000000LL;
    Object obj(bigVal);
    EXPECT_EQ(obj.getIntOrInt64(), bigVal);
}

// --- getNumWithDefaultValue ---

TEST_F(ObjectTest_103, GetNumWithDefaultValue_IntValue_103) {
    Object obj(5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 5.0);
}

TEST_F(ObjectTest_103, GetNumWithDefaultValue_NonNumeric_103) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_103, GetNumWithDefaultValue_RealValue_103) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

// --- getBoolWithDefaultValue ---

TEST_F(ObjectTest_103, GetBoolWithDefaultValue_BoolTrue_103) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_103, GetBoolWithDefaultValue_NonBool_103) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_103, GetBoolWithDefaultValue_BoolFalse_103) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

// --- Move Semantics ---

TEST_F(ObjectTest_103, MoveConstructor_103) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically objNone or objDead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

TEST_F(ObjectTest_103, MoveAssignment_103) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// --- setToNull ---

TEST_F(ObjectTest_103, SetToNull_103) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// --- copy ---

TEST_F(ObjectTest_103, Copy_Int_103) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_103, Copy_Bool_103) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_103, Copy_Real_103) {
    Object obj(1.23);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 1.23);
}

TEST_F(ObjectTest_103, Copy_Null_103) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_103, Copy_String_103) {
    Object obj(std::make_unique<GooString>("test"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "test");
}

TEST_F(ObjectTest_103, Copy_Name_103) {
    Object obj(objName, "myname");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "myname");
}

// --- isName with parameter ---

TEST_F(ObjectTest_103, IsName_MatchingName_103) {
    Object obj(objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
}

TEST_F(ObjectTest_103, IsName_NonMatchingName_103) {
    Object obj(objName, "Catalog");
    EXPECT_FALSE(obj.isName("Pages"));
}

TEST_F(ObjectTest_103, IsName_NotAName_103) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// --- isCmd with parameter ---

TEST_F(ObjectTest_103, IsCmd_Matching_103) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_103, IsCmd_NonMatching_103) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

TEST_F(ObjectTest_103, IsCmd_NotACmd_103) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("BT"));
}

// --- getTypeName ---

TEST_F(ObjectTest_103, GetTypeName_Bool_103) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "boolean");
}

TEST_F(ObjectTest_103, GetTypeName_Int_103) {
    Object obj(1);
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "integer");
}

TEST_F(ObjectTest_103, GetTypeName_Real_103) {
    Object obj(1.0);
    EXPECT_STREQ(obj.getTypeName(), "real");
}

TEST_F(ObjectTest_103, GetTypeName_Null_103) {
    Object obj = Object::null();
    EXPECT_STREQ(obj.getTypeName(), "null");
}

TEST_F(ObjectTest_103, GetTypeName_Error_103) {
    Object obj = Object::error();
    EXPECT_STREQ(obj.getTypeName(), "error");
}

TEST_F(ObjectTest_103, GetTypeName_EOF_103) {
    Object obj = Object::eof();
    EXPECT_STREQ(obj.getTypeName(), "eof");
}

TEST_F(ObjectTest_103, GetTypeName_None_103) {
    Object obj;
    EXPECT_STREQ(obj.getTypeName(), "none");
}

// --- Array Operations ---

TEST_F(ObjectTest_103, ArrayConstructor_103) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_NE(obj.getArray(), nullptr);
}

TEST_F(ObjectTest_103, ArrayGetLength_Empty_103) {
    Object obj(new Array(nullptr));
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_103, ArrayAdd_IncreasesLength_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_103, ArrayAdd_MultipleElements_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_103, ArrayGet_ReturnsCorrectValue_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_103, ArrayGetNF_ReturnsCorrectRef_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_103, ArrayRemove_DecreasesLength_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

// --- Dict Operations ---

TEST_F(ObjectTest_103, DictConstructor_103) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_NE(obj.getDict(), nullptr);
}

TEST_F(ObjectTest_103, DictGetLength_Empty_103) {
    Object obj(new Dict(nullptr));
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_103, DictAdd_IncreasesLength_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_103, DictLookup_ExistingKey_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Catalog"));
    Object val = obj.dictLookup("Type");
    EXPECT_TRUE(val.isName());
    EXPECT_TRUE(val.isName("Catalog"));
}

TEST_F(ObjectTest_103, DictLookup_NonExistingKey_103) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_103, DictSet_OverwritesExisting_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key", Object(1));
    obj.dictSet("Key", Object(2));
    Object val = obj.dictLookup("Key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_103, DictRemove_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(1));
    obj.dictAdd("Key2", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_103, DictGetKey_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("MyKey", Object(42));
    EXPECT_STREQ(obj.dictGetKey(0), "MyKey");
}

TEST_F(ObjectTest_103, DictGetVal_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_103, DictGetValNF_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key", Object(55));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_103, DictLookupNF_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("X", Object(33));
    const Object &val = obj.dictLookupNF("X");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 33);
}

TEST_F(ObjectTest_103, DictIs_Matching_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(obj.dictIs("Catalog"));
}

TEST_F(ObjectTest_103, DictIs_NonMatching_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Catalog"));
    EXPECT_FALSE(obj.dictIs("Pages"));
}

TEST_F(ObjectTest_103, DictIs_NoTypeKey_103) {
    Object obj(new Dict(nullptr));
    EXPECT_FALSE(obj.dictIs("Catalog"));
}

TEST_F(ObjectTest_103, IsDict_WithType_Matching_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Font"));
    EXPECT_TRUE(obj.isDict("Font"));
}

TEST_F(ObjectTest_103, IsDict_WithType_NonMatching_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Font"));
    EXPECT_FALSE(obj.isDict("Page"));
}

// --- takeString ---

TEST_F(ObjectTest_103, TakeString_103) {
    Object obj(std::make_unique<GooString>("takeMe"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "takeMe");
}

// --- getNameString ---

TEST_F(ObjectTest_103, GetNameString_103) {
    Object obj(objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// --- Boundary: Int Limits ---

TEST_F(ObjectTest_103, IntConstructor_MaxInt_103) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_103, IntConstructor_MinInt_103) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_103, Int64Constructor_MaxInt64_103) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_103, Int64Constructor_MinInt64_103) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// --- Negative type checks ---

TEST_F(ObjectTest_103, IntIsNotBool_103) {
    Object obj(5);
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

TEST_F(ObjectTest_103, BoolIsNotInt_103) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_103, NullIsNotOtherTypes_103) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
}

// --- Empty string ---

TEST_F(ObjectTest_103, EmptyStringConstructor_103) {
    Object obj(std::make_unique<GooString>(""));
    EXPECT_TRUE(obj.isString());
    EXPECT_STREQ(obj.getString()->c_str(), "");
}

TEST_F(ObjectTest_103, EmptyName_103) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// --- print (just ensure it doesn't crash) ---

TEST_F(ObjectTest_103, Print_Int_NoCrash_103) {
    Object obj(42);
    // Just ensure no crash; output goes to stdout
    obj.print(stdout);
}

TEST_F(ObjectTest_103, Print_Null_NoCrash_103) {
    Object obj = Object::null();
    obj.print(stdout);
}

TEST_F(ObjectTest_103, Print_Bool_NoCrash_103) {
    Object obj(true);
    obj.print(stdout);
}

TEST_F(ObjectTest_103, Print_String_NoCrash_103) {
    Object obj(std::make_unique<GooString>("printme"));
    obj.print(stdout);
}

// --- deepCopy ---

TEST_F(ObjectTest_103, DeepCopy_Int_103) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_103, DeepCopy_String_103) {
    Object obj(std::make_unique<GooString>("deep"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deep");
}

// --- Destructor (just ensure no crash on scope exit) ---

TEST_F(ObjectTest_103, Destructor_Int_NoCrash_103) {
    { Object obj(42); }
    SUCCEED();
}

TEST_F(ObjectTest_103, Destructor_String_NoCrash_103) {
    { Object obj(std::make_unique<GooString>("cleanup")); }
    SUCCEED();
}

TEST_F(ObjectTest_103, Destructor_Array_NoCrash_103) {
    { Object obj(new Array(nullptr)); }
    SUCCEED();
}

TEST_F(ObjectTest_103, Destructor_Dict_NoCrash_103) {
    { Object obj(new Dict(nullptr)); }
    SUCCEED();
}

// --- Multiple dict operations ---

TEST_F(ObjectTest_103, DictMultipleAdd_103) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
    
    Object a = obj.dictLookup("A");
    Object b = obj.dictLookup("B");
    Object c = obj.dictLookup("C");
    
    EXPECT_EQ(a.getInt(), 1);
    EXPECT_EQ(b.getInt(), 2);
    EXPECT_EQ(c.getInt(), 3);
}

// --- Array with mixed types ---

TEST_F(ObjectTest_103, ArrayMixedTypes_103) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    obj.arrayAdd(Object::null());
    
    EXPECT_EQ(obj.arrayGetLength(), 4);
    
    Object e0 = obj.arrayGet(0);
    EXPECT_TRUE(e0.isInt());
    EXPECT_EQ(e0.getInt(), 42);
    
    Object e1 = obj.arrayGet(1);
    EXPECT_TRUE(e1.isReal());
    EXPECT_DOUBLE_EQ(e1.getReal(), 3.14);
    
    Object e2 = obj.arrayGet(2);
    EXPECT_TRUE(e2.isBool());
    EXPECT_TRUE(e2.getBool());
    
    Object e3 = obj.arrayGet(3);
    EXPECT_TRUE(e3.isNull());
}
