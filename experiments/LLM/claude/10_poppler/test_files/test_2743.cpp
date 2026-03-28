#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_2743 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ObjectTest_2743, DefaultConstructor_CreatesNoneType_2743) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_2743, BoolConstructor_True_2743) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2743, BoolConstructor_False_2743) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_2743, IntConstructor_PositiveValue_2743) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2743, IntConstructor_Zero_2743) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2743, IntConstructor_NegativeValue_2743) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_2743, RealConstructor_PositiveValue_2743) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2743, RealConstructor_Zero_2743) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2743, RealConstructor_NegativeValue_2743) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_2743, Int64Constructor_LargeValue_2743) {
    long long val = 9223372036854775807LL; // max long long
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2743, Int64Constructor_Zero_2743) {
    Object obj(0LL);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

TEST_F(ObjectTest_2743, Int64Constructor_NegativeValue_2743) {
    long long val = -9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2743, StringConstructor_WithString_2743) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_2743, NullFactory_2743) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2743, EofFactory_2743) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_2743, ErrorFactory_2743) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Tests ====================

TEST_F(ObjectTest_2743, IsBool_ReturnsTrueForBool_2743) {
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

TEST_F(ObjectTest_2743, IsInt_ReturnsTrueForInt_2743) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_2743, IsReal_ReturnsTrueForReal_2743) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_2743, IsNum_ReturnsTrueForInt_2743) {
    Object obj(10);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2743, IsNum_ReturnsTrueForReal_2743) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_2743, IsNum_ReturnsFalseForBool_2743) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_2743, IsIntOrInt64_ReturnsTrueForInt_2743) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2743, IsIntOrInt64_ReturnsTrueForInt64_2743) {
    Object obj(42LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_2743, IsIntOrInt64_ReturnsFalseForReal_2743) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_2743, GetNum_FromInt_2743) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_2743, GetNum_FromReal_2743) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_2743, GetNum_WithOkParam_FromInt_2743) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_2743, GetNum_WithOkParam_FromReal_2743) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_2743, GetIntOrInt64_FromInt_2743) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2743, GetIntOrInt64_FromInt64_2743) {
    long long val = 123456789012345LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_2743, GetNumWithDefaultValue_FromInt_2743) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_2743, GetNumWithDefaultValue_FromReal_2743) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 2.5);
}

TEST_F(ObjectTest_2743, GetNumWithDefaultValue_NonNumericReturnsDefault_2743) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_2743, GetNumWithDefaultValue_NullReturnsDefault_2743) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_2743, GetBoolWithDefaultValue_FromBoolTrue_2743) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2743, GetBoolWithDefaultValue_FromBoolFalse_2743) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2743, GetBoolWithDefaultValue_NonBoolReturnsDefault_2743) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2743, GetBoolWithDefaultValue_NullReturnsDefault_2743) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Move Constructor and Assignment ====================

TEST_F(ObjectTest_2743, MoveConstructor_Int_2743) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // obj1 should be in a valid but unspecified state (typically dead or none)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead || obj1.getType() == objNone);
}

TEST_F(ObjectTest_2743, MoveConstructor_Bool_2743) {
    Object obj1(true);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isBool());
    EXPECT_TRUE(obj2.getBool());
}

TEST_F(ObjectTest_2743, MoveAssignment_Int_2743) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_2743, MoveAssignment_Real_2743) {
    Object obj1(3.14);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_2743, SetToNull_FromInt_2743) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_2743, SetToNull_FromBool_2743) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_2743, SetToNull_AlreadyNull_2743) {
    Object obj = Object::null();
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== copy Tests ====================

TEST_F(ObjectTest_2743, Copy_Int_2743) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_2743, Copy_Bool_2743) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2743, Copy_Real_2743) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_2743, Copy_Null_2743) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_2743, Copy_Error_2743) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_2743, Copy_EOF_2743) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

TEST_F(ObjectTest_2743, Copy_Int64_2743) {
    Object obj(123456789012345LL);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt64());
    EXPECT_EQ(copied.getInt64(), 123456789012345LL);
}

// ==================== Name Object Tests ====================

TEST_F(ObjectTest_2743, NameObject_Creation_2743) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_2743, NameObject_IsNameWithMatch_2743) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_2743, NameObject_IsNameWithNoMatch_2743) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_2743, NameObject_GetNameString_2743) {
    Object obj(objName, "MyName");
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "MyName");
}

TEST_F(ObjectTest_2743, NameObject_EmptyName_2743) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Cmd Object Tests ====================

TEST_F(ObjectTest_2743, CmdObject_Creation_2743) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_2743, CmdObject_IsCmdWithMatch_2743) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_2743, CmdObject_IsCmdWithNoMatch_2743) {
    Object obj(objCmd, "BT");
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== String Object Tests ====================

TEST_F(ObjectTest_2743, StringObject_WithStdString_2743) {
    Object obj(std::string("hello world"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_2743, StringObject_Copy_2743) {
    Object obj(std::string("test string"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    ASSERT_NE(copied.getString(), nullptr);
}

// ==================== HexString Object Tests ====================

TEST_F(ObjectTest_2743, HexStringObject_Creation_2743) {
    Object obj(objHexString, std::string("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_2743, GetTypeName_Bool_2743) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_Int_2743) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_Real_2743) {
    Object obj(3.14);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_Null_2743) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_Error_2743) {
    Object obj = Object::error();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_EOF_2743) {
    Object obj = Object::eof();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2743, GetTypeName_None_2743) {
    Object obj;
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== Boundary Value Tests ====================

TEST_F(ObjectTest_2743, IntConstructor_MaxInt_2743) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_2743, IntConstructor_MinInt_2743) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_2743, Int64Constructor_MaxInt64_2743) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2743, Int64Constructor_MinInt64_2743) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2743, RealConstructor_VerySmall_2743) {
    double val = std::numeric_limits<double>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), val);
}

TEST_F(ObjectTest_2743, RealConstructor_VeryLarge_2743) {
    double val = std::numeric_limits<double>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), val);
}

TEST_F(ObjectTest_2743, RealConstructor_NegativeInfinity_2743) {
    double val = -std::numeric_limits<double>::infinity();
    Object obj(val);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), val);
}

// ==================== Array Object Tests ====================

TEST_F(ObjectTest_2743, ArrayObject_Creation_2743) {
    // Creating an Array requires a valid XRef, but we can test basic array object behavior
    // by constructing an Array with nullptr if implementation allows
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.getArray(), arr);
}

TEST_F(ObjectTest_2743, ArrayObject_GetLength_2743) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_2743, ArrayObject_AddAndGetLength_2743) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_2743, ArrayObject_AddMultipleAndGet_2743) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 1);

    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 2);

    Object elem2 = obj.arrayGet(2);
    EXPECT_TRUE(elem2.isInt());
    EXPECT_EQ(elem2.getInt(), 3);
}

TEST_F(ObjectTest_2743, ArrayObject_Remove_2743) {
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

TEST_F(ObjectTest_2743, ArrayObject_ArrayGetNF_2743) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

// ==================== Dict Object Tests ====================

TEST_F(ObjectTest_2743, DictObject_Creation_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.getDict(), dict);
}

TEST_F(ObjectTest_2743, DictObject_GetLength_Empty_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_2743, DictObject_AddAndLookup_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2743, DictObject_SetOverwritesValue_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_2743, DictObject_Remove_2743) {
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

TEST_F(ObjectTest_2743, DictObject_LookupNonExistent_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2743, DictObject_GetKey_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("TestKey", Object(42));
    EXPECT_STREQ(obj.dictGetKey(0), "TestKey");
}

TEST_F(ObjectTest_2743, DictObject_GetVal_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2743, DictObject_GetValNF_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2743, DictObject_LookupNF_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2743, DictObject_MultipleEntries_2743) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    obj.dictAdd("C", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// ==================== deepCopy Tests ====================

TEST_F(ObjectTest_2743, DeepCopy_Int_2743) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_2743, DeepCopy_Bool_2743) {
    Object obj(true);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isBool());
    EXPECT_TRUE(deep.getBool());
}

TEST_F(ObjectTest_2743, DeepCopy_Real_2743) {
    Object obj(3.14);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isReal());
    EXPECT_DOUBLE_EQ(deep.getReal(), 3.14);
}

// ==================== Destructor and cleanup ====================

TEST_F(ObjectTest_2743, Destructor_NoLeak_Int_2743) {
    // This test ensures no crash on destruction
    {
        Object obj(42);
    }
    SUCCEED();
}

TEST_F(ObjectTest_2743, Destructor_NoLeak_String_2743) {
    {
        Object obj(std::string("test"));
    }
    SUCCEED();
}

TEST_F(ObjectTest_2743, Destructor_NoLeak_Array_2743) {
    {
        Array *arr = new Array(nullptr);
        Object obj(arr);
    }
    SUCCEED();
}

TEST_F(ObjectTest_2743, Destructor_NoLeak_Dict_2743) {
    {
        Dict *dict = new Dict(nullptr);
        Object obj(dict);
    }
    SUCCEED();
}

// ==================== Multiple operations ====================

TEST_F(ObjectTest_2743, MoveAssignment_OverwriteExisting_2743) {
    Object obj1(42);
    Object obj2(3.14);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isReal());
    EXPECT_DOUBLE_EQ(obj1.getReal(), 3.14);
}

TEST_F(ObjectTest_2743, SetToNull_ThenMoveAssign_2743) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    Object obj2(100);
    obj = std::move(obj2);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 100);
}

// ==================== getNum for Int64 ====================

TEST_F(ObjectTest_2743, IsNum_Int64_2743) {
    Object obj(42LL);
    // Int64 may or may not be considered "num" depending on implementation
    // Test that getIntOrInt64 works
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// ==================== String Object with GooString ====================

TEST_F(ObjectTest_2743, StringObject_WithGooString_2743) {
    auto gs = std::make_unique<GooString>("test goo");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_2743, StringObject_TakeString_2743) {
    Object obj(std::string("take me"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
}

// ==================== Copy preserves independence ====================

TEST_F(ObjectTest_2743, Copy_IntIndependent_2743) {
    Object obj(42);
    Object copied = obj.copy();
    // Original and copy should be independent
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}
