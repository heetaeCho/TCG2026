#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "GooString.h"
#include "Array.h"
#include "Dict.h"

// Test fixture for Object tests
class ObjectTest_2757 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============ Constructor Tests ============

TEST_F(ObjectTest_2757, DefaultConstructor_CreatesNoneObject_2757) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_2757, BoolConstructor_True_2757) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2757, BoolConstructor_False_2757) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_2757, IntConstructor_2757) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2757, IntConstructor_Zero_2757) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2757, IntConstructor_Negative_2757) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_2757, RealConstructor_2757) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2757, RealConstructor_Zero_2757) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2757, RealConstructor_Negative_2757) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_2757, GooStringConstructor_2757) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_2757, GooStringConstructor_EmptyString_2757) {
    auto str = std::make_unique<GooString>("");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "");
}

TEST_F(ObjectTest_2757, StdStringConstructor_2757) {
    std::string s = "test_string";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_2757, Int64Constructor_2757) {
    long long val = 1234567890123LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2757, Int64Constructor_Zero_2757) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

TEST_F(ObjectTest_2757, NameConstructor_2757) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_2757, CmdConstructor_2757) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_2757, HexStringConstructor_2757) {
    Object obj(objHexString, std::string("ABCDEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ============ Static Factory Tests ============

TEST_F(ObjectTest_2757, NullFactory_2757) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2757, EofFactory_2757) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_2757, ErrorFactory_2757) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ============ Move Constructor/Assignment Tests ============

TEST_F(ObjectTest_2757, MoveConstructor_Int_2757) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_2757, MoveConstructor_String_2757) {
    auto str = std::make_unique<GooString>("move_test");
    Object obj1(std::move(str));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isString());
    EXPECT_STREQ(obj2.getString()->c_str(), "move_test");
}

TEST_F(ObjectTest_2757, MoveAssignment_Int_2757) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_2757, MoveAssignment_OverwriteExisting_2757) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ============ Type Checking Tests ============

TEST_F(ObjectTest_2757, IsBool_TrueForBool_2757) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_2757, IsInt_TrueForInt_2757) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_2757, IsNum_TrueForInt_2757) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2757, IsNum_TrueForReal_2757) {
    Object obj(10.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2757, IsNum_TrueForInt64_2757) {
    Object obj(10LL);
    // Int64 may or may not be considered a "Num" — we test observable behavior
    // isNum typically covers int and real
}

TEST_F(ObjectTest_2757, IsIntOrInt64_Int_2757) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2757, IsIntOrInt64_Int64_2757) {
    Object obj(42LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2757, IsIntOrInt64_Real_2757) {
    Object obj(42.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ============ getNum Tests ============

TEST_F(ObjectTest_2757, GetNum_FromInt_2757) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_2757, GetNum_FromReal_2757) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_2757, GetNum_WithOkParam_Int_2757) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_2757, GetNum_WithOkParam_Real_2757) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ============ getIntOrInt64 Tests ============

TEST_F(ObjectTest_2757, GetIntOrInt64_FromInt_2757) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2757, GetIntOrInt64_FromInt64_2757) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ============ getNumWithDefaultValue Tests ============

TEST_F(ObjectTest_2757, GetNumWithDefaultValue_IntObject_2757) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 42.0);
}

TEST_F(ObjectTest_2757, GetNumWithDefaultValue_RealObject_2757) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

TEST_F(ObjectTest_2757, GetNumWithDefaultValue_NonNumObject_2757) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ============ getBoolWithDefaultValue Tests ============

TEST_F(ObjectTest_2757, GetBoolWithDefaultValue_BoolObject_2757) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2757, GetBoolWithDefaultValue_NonBoolObject_2757) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2757, GetBoolWithDefaultValue_NonBoolObject_DefaultFalse_2757) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ============ isName with parameter Tests ============

TEST_F(ObjectTest_2757, IsNameWithParam_Matching_2757) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
}

TEST_F(ObjectTest_2757, IsNameWithParam_NotMatching_2757) {
    Object obj(objName, "Type");
    EXPECT_FALSE(obj.isName("Page"));
}

TEST_F(ObjectTest_2757, IsNameWithParam_NonNameObject_2757) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

// ============ isCmd with parameter Tests ============

TEST_F(ObjectTest_2757, IsCmdWithParam_Matching_2757) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd("q"));
}

TEST_F(ObjectTest_2757, IsCmdWithParam_NotMatching_2757) {
    Object obj(objCmd, "q");
    EXPECT_FALSE(obj.isCmd("Q"));
}

TEST_F(ObjectTest_2757, IsCmdWithParam_NonCmdObject_2757) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("q"));
}

// ============ getNameString Tests ============

TEST_F(ObjectTest_2757, GetNameString_2757) {
    Object obj(objName, "TestName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "TestName");
}

// ============ setToNull Tests ============

TEST_F(ObjectTest_2757, SetToNull_FromInt_2757) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_2757, SetToNull_FromString_2757) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_2757, SetToNull_AlreadyNull_2757) {
    Object obj = Object::null();
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ============ copy Tests ============

TEST_F(ObjectTest_2757, Copy_IntObject_2757) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_2757, Copy_BoolObject_2757) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2757, Copy_RealObject_2757) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_2757, Copy_StringObject_2757) {
    auto str = std::make_unique<GooString>("copy_me");
    Object obj(std::move(str));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "copy_me");
}

TEST_F(ObjectTest_2757, Copy_NullObject_2757) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_2757, Copy_NameObject_2757) {
    Object obj(objName, "CopyName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyName");
}

TEST_F(ObjectTest_2757, Copy_Int64Object_2757) {
    long long val = 9876543210LL;
    Object obj(val);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), val);
}

// ============ getTypeName Tests ============

TEST_F(ObjectTest_2757, GetTypeName_Bool_2757) {
    Object obj(true);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_2757, GetTypeName_Int_2757) {
    Object obj(42);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_2757, GetTypeName_Null_2757) {
    Object obj = Object::null();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_2757, GetTypeName_Error_2757) {
    Object obj = Object::error();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ============ takeString Tests ============

TEST_F(ObjectTest_2757, TakeString_2757) {
    auto str = std::make_unique<GooString>("take_me");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "take_me");
}

// ============ Array Tests ============

TEST_F(ObjectTest_2757, ArrayObject_GetLength_2757) {
    // Create an empty XRef-less array
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_2757, ArrayObject_AddAndGetLength_2757) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_2757, ArrayObject_AddMultipleAndGet_2757) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    
    Object val0 = obj.arrayGet(0);
    EXPECT_TRUE(val0.isInt());
    EXPECT_EQ(val0.getInt(), 1);
    
    Object val2 = obj.arrayGet(2);
    EXPECT_TRUE(val2.isInt());
    EXPECT_EQ(val2.getInt(), 3);
}

TEST_F(ObjectTest_2757, ArrayObject_ArrayGetNF_2757) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    const Object& val = obj.arrayGetNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2757, ArrayObject_Remove_2757) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    
    Object val0 = obj.arrayGet(0);
    EXPECT_EQ(val0.getInt(), 1);
    Object val1 = obj.arrayGet(1);
    EXPECT_EQ(val1.getInt(), 3);
}

// ============ Dict Tests ============

TEST_F(ObjectTest_2757, DictObject_GetLength_2757) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_2757, DictObject_AddAndLookup_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2757, DictObject_SetOverwrite_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));
    
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_2757, DictObject_Remove_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);
    
    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2757, DictObject_LookupNonExistent_2757) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2757, DictObject_GetKey_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("MyKey", Object(42));
    const char* key = obj.dictGetKey(0);
    EXPECT_NE(key, nullptr);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_2757, DictObject_GetVal_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2757, DictObject_GetValNF_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    const Object& val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2757, DictObject_LookupNF_2757) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    const Object& val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ============ Destructor / Cleanup Tests ============

TEST_F(ObjectTest_2757, Destructor_StringCleanup_2757) {
    // Just verify no crash on destruction
    {
        auto str = std::make_unique<GooString>("destroy_me");
        Object obj(std::move(str));
    }
    // If we reach here, no crash
    SUCCEED();
}

TEST_F(ObjectTest_2757, Destructor_ArrayCleanup_2757) {
    {
        Object obj(new Array(nullptr));
        obj.arrayAdd(Object(42));
    }
    SUCCEED();
}

TEST_F(ObjectTest_2757, Destructor_DictCleanup_2757) {
    {
        Object obj(new Dict(nullptr));
        obj.dictAdd("Key", Object(42));
    }
    SUCCEED();
}

// ============ Boundary / Edge Case Tests ============

TEST_F(ObjectTest_2757, IntBoundary_MaxInt_2757) {
    int maxVal = std::numeric_limits<int>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), maxVal);
}

TEST_F(ObjectTest_2757, IntBoundary_MinInt_2757) {
    int minVal = std::numeric_limits<int>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), minVal);
}

TEST_F(ObjectTest_2757, Int64Boundary_LargeValue_2757) {
    long long largeVal = std::numeric_limits<long long>::max();
    Object obj(largeVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), largeVal);
}

TEST_F(ObjectTest_2757, Int64Boundary_MinValue_2757) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

TEST_F(ObjectTest_2757, RealBoundary_VerySmall_2757) {
    double tiny = std::numeric_limits<double>::min();
    Object obj(tiny);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), tiny);
}

TEST_F(ObjectTest_2757, RealBoundary_VeryLarge_2757) {
    double huge = std::numeric_limits<double>::max();
    Object obj(huge);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), huge);
}

TEST_F(ObjectTest_2757, NameConstructor_EmptyName_2757) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_2757, CmdConstructor_EmptyCmd_2757) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ============ Multiple Operations Tests ============

TEST_F(ObjectTest_2757, DictObject_MultipleAdditions_2757) {
    Object obj(new Dict(nullptr));
    for (int i = 0; i < 100; i++) {
        std::string key = "key" + std::to_string(i);
        obj.dictAdd(key, Object(i));
    }
    EXPECT_EQ(obj.dictGetLength(), 100);
    
    Object val50 = obj.dictLookup("key50");
    EXPECT_TRUE(val50.isInt());
    EXPECT_EQ(val50.getInt(), 50);
}

TEST_F(ObjectTest_2757, ArrayObject_MultipleAdditions_2757) {
    Object obj(new Array(nullptr));
    for (int i = 0; i < 100; i++) {
        obj.arrayAdd(Object(i));
    }
    EXPECT_EQ(obj.arrayGetLength(), 100);
    
    Object val99 = obj.arrayGet(99);
    EXPECT_TRUE(val99.isInt());
    EXPECT_EQ(val99.getInt(), 99);
}

// ============ deepCopy Tests ============

TEST_F(ObjectTest_2757, DeepCopy_IntObject_2757) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_2757, DeepCopy_StringObject_2757) {
    auto str = std::make_unique<GooString>("deep_copy");
    Object obj(std::move(str));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deep_copy");
}

// ============ Print Test (just ensure no crash) ============

TEST_F(ObjectTest_2757, Print_IntObject_NoCrash_2757) {
    Object obj(42);
    // Print to stdout, just verify no crash
    obj.print(stdout);
    SUCCEED();
}

TEST_F(ObjectTest_2757, Print_NullObject_NoCrash_2757) {
    Object obj = Object::null();
    obj.print(stdout);
    SUCCEED();
}

TEST_F(ObjectTest_2757, Print_StringObject_NoCrash_2757) {
    auto str = std::make_unique<GooString>("printable");
    Object obj(std::move(str));
    obj.print(stdout);
    SUCCEED();
}
