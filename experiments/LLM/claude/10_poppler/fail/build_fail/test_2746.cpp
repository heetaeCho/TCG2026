#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "GooString.h"

// Test fixture for Object tests
class ObjectTest_2746 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ObjectTest_2746, DefaultConstructor_CreatesNoneObject_2746) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_2746, BoolConstructor_True_2746) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_2746, BoolConstructor_False_2746) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_2746, IntConstructor_PositiveValue_2746) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_2746, IntConstructor_Zero_2746) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_2746, IntConstructor_NegativeValue_2746) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_2746, RealConstructor_PositiveValue_2746) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_2746, RealConstructor_Zero_2746) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_2746, RealConstructor_NegativeValue_2746) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_2746, GooStringConstructor_ValidString_2746) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_2746, GooStringConstructor_EmptyString_2746) {
    auto str = std::make_unique<GooString>("");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "");
}

TEST_F(ObjectTest_2746, Int64Constructor_LargeValue_2746) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2746, Int64Constructor_Zero_2746) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), 0LL);
}

// ==================== Static Factory Tests ====================

TEST_F(ObjectTest_2746, NullFactory_CreatesNullObject_2746) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2746, EofFactory_CreatesEofObject_2746) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_2746, ErrorFactory_CreatesErrorObject_2746) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Checking Tests ====================

TEST_F(ObjectTest_2746, IsBool_ReturnsTrueForBool_2746) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_2746, IsInt_ReturnsTrueForInt_2746) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_2746, IsReal_ReturnsTrueForReal_2746) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_2746, IsNum_ReturnsTrueForIntAndReal_2746) {
    Object intObj(42);
    Object realObj(3.14);
    Object boolObj(true);

    EXPECT_TRUE(intObj.isNum());
    EXPECT_TRUE(realObj.isNum());
    EXPECT_FALSE(boolObj.isNum());
}

TEST_F(ObjectTest_2746, IsIntOrInt64_ReturnsTrueForBothTypes_2746) {
    Object intObj(42);
    long long val = 123456789LL;
    Object int64Obj(val);
    Object realObj(3.14);

    EXPECT_TRUE(intObj.isIntOrInt64());
    EXPECT_TRUE(int64Obj.isIntOrInt64());
    EXPECT_FALSE(realObj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_2746, GetNum_ReturnsIntAsDouble_2746) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_2746, GetNum_ReturnsRealValue_2746) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_2746, GetIntOrInt64_FromInt_2746) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_2746, GetIntOrInt64_FromInt64_2746) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== Move Constructor and Assignment Tests ====================

TEST_F(ObjectTest_2746, MoveConstructor_TransfersOwnership_2746) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid state (typically none)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_2746, MoveAssignment_TransfersOwnership_2746) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_2746, MoveConstructor_StringObject_2746) {
    auto str = std::make_unique<GooString>("test");
    Object obj1(std::move(str));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isString());
    EXPECT_STREQ(obj2.getString()->c_str(), "test");
    EXPECT_TRUE(obj1.isNone());
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_2746, SetToNull_ChangesTypeToNull_2746) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_2746, SetToNull_FromBool_2746) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_2746, Copy_IntObject_2746) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_2746, Copy_BoolObject_2746) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_2746, Copy_RealObject_2746) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_2746, Copy_StringObject_2746) {
    auto str = std::make_unique<GooString>("copytest");
    Object obj(std::move(str));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "copytest");
}

TEST_F(ObjectTest_2746, Copy_NullObject_2746) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_2746, Copy_ErrorObject_2746) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_2746, Copy_EofObject_2746) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_2746, GetTypeName_Bool_2746) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2746, GetTypeName_Int_2746) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_2746, GetTypeName_Null_2746) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== String Constructor with std::string&& ====================

TEST_F(ObjectTest_2746, StdStringConstructor_2746) {
    std::string s = "stdstring";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "stdstring");
}

TEST_F(ObjectTest_2746, StdStringConstructor_Empty_2746) {
    std::string s = "";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "");
}

// ==================== Name/Cmd Object Tests ====================

TEST_F(ObjectTest_2746, NameObject_ConstructAndCheck_2746) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_2746, NameObject_IsNameWithMatch_2746) {
    Object obj(objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
    EXPECT_FALSE(obj.isName("Page"));
}

TEST_F(ObjectTest_2746, CmdObject_ConstructAndCheck_2746) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_2746, CmdObject_IsCmdWithMatch_2746) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== HexString Tests ====================

TEST_F(ObjectTest_2746, HexStringObject_ConstructAndCheck_2746) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_2746, GetNumWithDefaultValue_IntObject_2746) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_2746, GetNumWithDefaultValue_RealObject_2746) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_2746, GetNumWithDefaultValue_NonNumericReturnsDefault_2746) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_2746, GetNumWithDefaultValue_NullReturnsDefault_2746) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(55.5), 55.5);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_2746, GetBoolWithDefaultValue_BoolObject_2746) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_2746, GetBoolWithDefaultValue_FalseObject_2746) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_2746, GetBoolWithDefaultValue_NonBoolReturnsDefault_2746) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_2746, TakeString_ReturnsStringAndInvalidatesObject_2746) {
    auto str = std::make_unique<GooString>("takeMe");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    auto taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "takeMe");
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_2746, ArrayObject_GetLength_2746) {
    // Create an array object through the Array class
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_2746, ArrayObject_AddAndGetLength_2746) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(3.14));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_2746, ArrayObject_ArrayGet_2746) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(100));

    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);

    Object elem2 = obj.arrayGet(1);
    EXPECT_TRUE(elem2.isInt());
    EXPECT_EQ(elem2.getInt(), 100);
}

TEST_F(ObjectTest_2746, ArrayObject_ArrayRemove_2746) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);

    Object elem = obj.arrayGet(0);
    EXPECT_EQ(elem.getInt(), 10);
    Object elem2 = obj.arrayGet(1);
    EXPECT_EQ(elem2.getInt(), 30);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_2746, DictObject_GetLength_2746) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_2746, DictObject_AddAndLookup_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_2746, DictObject_SetOverwritesValue_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_2746, DictObject_Remove_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(99));
    EXPECT_EQ(obj.dictGetLength(), 2);

    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2746, DictObject_LookupNonExistent_2746) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_2746, DictObject_GetKey_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_2746, DictObject_GetVal_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== Name String Tests ====================

TEST_F(ObjectTest_2746, GetNameString_ReturnsString_2746) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

TEST_F(ObjectTest_2746, NameObject_EmptyName_2746) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== Deep Copy Tests ====================

TEST_F(ObjectTest_2746, DeepCopy_IntObject_2746) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_2746, DeepCopy_StringObject_2746) {
    auto str = std::make_unique<GooString>("deepcopy");
    Object obj(std::move(str));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deepcopy");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ObjectTest_2746, IntConstructor_MaxInt_2746) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_2746, IntConstructor_MinInt_2746) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_2746, Int64Constructor_MinValue_2746) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_2746, RealConstructor_VerySmallPositive_2746) {
    double val = std::numeric_limits<double>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), val);
}

TEST_F(ObjectTest_2746, RealConstructor_Infinity_2746) {
    double val = std::numeric_limits<double>::infinity();
    Object obj(val);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), val);
}

// ==================== Multiple Type Negative Tests ====================

TEST_F(ObjectTest_2746, NullObject_IsNotOtherTypes_2746) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
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
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_2746, ErrorObject_IsNotOtherTypes_2746) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_2746, EofObject_IsNotOtherTypes_2746) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_2746, GetNumWithOk_IntObject_2746) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_2746, GetNumWithOk_RealObject_2746) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(ObjectTest_2746, GetNumWithOk_NonNumericObject_2746) {
    Object obj(true);
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_FALSE(ok);
}

// ==================== Dict isDict with type Tests ====================

TEST_F(ObjectTest_2746, DictObject_IsDictWithoutType_2746) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
}

// ==================== Move Assignment from different types ====================

TEST_F(ObjectTest_2746, MoveAssignment_FromIntToString_2746) {
    Object obj1(42);
    auto str = std::make_unique<GooString>("replace");
    Object obj2(std::move(str));

    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isString());
    EXPECT_STREQ(obj1.getString()->c_str(), "replace");
    EXPECT_TRUE(obj2.isNone());
}

TEST_F(ObjectTest_2746, MoveAssignment_FromStringToNull_2746) {
    auto str = std::make_unique<GooString>("test");
    Object obj1(std::move(str));
    Object obj2 = Object::null();

    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isNull());
}

// ==================== Multiple array operations ====================

TEST_F(ObjectTest_2746, ArrayObject_ArrayGetNF_2746) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));

    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

// ==================== Dict dictGetValNF Tests ====================

TEST_F(ObjectTest_2746, DictObject_GetValNF_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));

    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== Dict dictLookupNF Tests ====================

TEST_F(ObjectTest_2746, DictObject_LookupNF_2746) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));

    const Object &val = obj.dictLookupNF("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}
