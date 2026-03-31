#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_83 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for default constructor and type checking
// =============================================================================

TEST_F(ObjectTest_83, DefaultConstructor_IsNone_83) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_83, DefaultConstructor_IsNotCmd_83) {
    Object obj;
    EXPECT_FALSE(obj.isCmd());
}

// =============================================================================
// Tests for isCmd()
// =============================================================================

TEST_F(ObjectTest_83, CmdObject_IsCmd_83) {
    Object obj(objCmd, "test");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
}

TEST_F(ObjectTest_83, CmdObject_IsCmdWithMatchingName_83) {
    Object obj(objCmd, "mycommand");
    EXPECT_TRUE(obj.isCmd("mycommand"));
}

TEST_F(ObjectTest_83, CmdObject_IsCmdWithNonMatchingName_83) {
    Object obj(objCmd, "mycommand");
    EXPECT_FALSE(obj.isCmd("othercommand"));
}

TEST_F(ObjectTest_83, CmdObject_GetCmd_83) {
    Object obj(objCmd, "testcmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "testcmd");
}

TEST_F(ObjectTest_83, CmdObject_EmptyString_83) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// =============================================================================
// Tests for Bool object
// =============================================================================

TEST_F(ObjectTest_83, BoolObject_True_83) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_83, BoolObject_False_83) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
    EXPECT_FALSE(obj.isCmd());
}

// =============================================================================
// Tests for Int object
// =============================================================================

TEST_F(ObjectTest_83, IntObject_PositiveValue_83) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_83, IntObject_Zero_83) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_83, IntObject_Negative_83) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

// =============================================================================
// Tests for Real object
// =============================================================================

TEST_F(ObjectTest_83, RealObject_PositiveValue_83) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_83, RealObject_Zero_83) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_83, RealObject_Negative_83) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

// =============================================================================
// Tests for Int64 object
// =============================================================================

TEST_F(ObjectTest_83, Int64Object_LargeValue_83) {
    long long val = 1LL << 40;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_83, Int64Object_GetIntOrInt64_83) {
    long long val = 123456789LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// =============================================================================
// Tests for String object
// =============================================================================

TEST_F(ObjectTest_83, StringObject_83) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_83, StringObjectFromStdString_83) {
    Object obj(std::string("hello world"));
    EXPECT_TRUE(obj.isString());
}

// =============================================================================
// Tests for HexString object
// =============================================================================

TEST_F(ObjectTest_83, HexStringObject_83) {
    Object obj(objHexString, "AABB");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_NE(obj.getHexString(), nullptr);
}

// =============================================================================
// Tests for Name object
// =============================================================================

TEST_F(ObjectTest_83, NameObject_83) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_STREQ(obj.getName(), "Type");
}

TEST_F(ObjectTest_83, NameObject_IsNameWithMatch_83) {
    Object obj(objName, "Font");
    EXPECT_TRUE(obj.isName("Font"));
}

TEST_F(ObjectTest_83, NameObject_IsNameWithNoMatch_83) {
    Object obj(objName, "Font");
    EXPECT_FALSE(obj.isName("Page"));
}

// =============================================================================
// Tests for Null object
// =============================================================================

TEST_F(ObjectTest_83, NullObject_83) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objNull);
}

// =============================================================================
// Tests for EOF object
// =============================================================================

TEST_F(ObjectTest_83, EofObject_83) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objEOF);
}

// =============================================================================
// Tests for Error object
// =============================================================================

TEST_F(ObjectTest_83, ErrorObject_83) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// Tests for move constructor/assignment
// =============================================================================

TEST_F(ObjectTest_83, MoveConstructor_CmdObject_83) {
    Object obj1(objCmd, "movecmd");
    EXPECT_TRUE(obj1.isCmd());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isCmd());
    EXPECT_STREQ(obj2.getCmd(), "movecmd");
}

TEST_F(ObjectTest_83, MoveAssignment_CmdObject_83) {
    Object obj1(objCmd, "assigncmd");
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isCmd());
    EXPECT_STREQ(obj2.getCmd(), "assigncmd");
}

TEST_F(ObjectTest_83, MoveConstructor_IntObject_83) {
    Object obj1(99);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 99);
}

// =============================================================================
// Tests for setToNull
// =============================================================================

TEST_F(ObjectTest_83, SetToNull_FromCmd_83) {
    Object obj(objCmd, "test");
    EXPECT_TRUE(obj.isCmd());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_83, SetToNull_FromInt_83) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

// =============================================================================
// Tests for copy
// =============================================================================

TEST_F(ObjectTest_83, Copy_IntObject_83) {
    Object obj(123);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 123);
}

TEST_F(ObjectTest_83, Copy_BoolObject_83) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_83, Copy_RealObject_83) {
    Object obj(1.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 1.5);
}

TEST_F(ObjectTest_83, Copy_NameObject_83) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

TEST_F(ObjectTest_83, Copy_CmdObject_83) {
    Object obj(objCmd, "testcmd");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isCmd());
    EXPECT_STREQ(copied.getCmd(), "testcmd");
}

TEST_F(ObjectTest_83, Copy_NullObject_83) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// =============================================================================
// Tests for getTypeName
// =============================================================================

TEST_F(ObjectTest_83, GetTypeName_Int_83) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_83, GetTypeName_Cmd_83) {
    Object obj(objCmd, "test");
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_83, GetTypeName_Null_83) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// =============================================================================
// Tests for getNumWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_83, GetNumWithDefaultValue_IntReturnsNum_83) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_83, GetNumWithDefaultValue_RealReturnsNum_83) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 2.5);
}

TEST_F(ObjectTest_83, GetNumWithDefaultValue_NonNumReturnsDefault_83) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_83, GetNumWithDefaultValue_CmdReturnsDefault_83) {
    Object obj(objCmd, "test");
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// =============================================================================
// Tests for getBoolWithDefaultValue
// =============================================================================

TEST_F(ObjectTest_83, GetBoolWithDefaultValue_BoolReturnsBool_83) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_83, GetBoolWithDefaultValue_NonBoolReturnsDefault_83) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// =============================================================================
// Tests for type exclusivity
// =============================================================================

TEST_F(ObjectTest_83, TypeExclusivity_Cmd_83) {
    Object obj(objCmd, "test");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNum());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_83, TypeExclusivity_Bool_83) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_83, TypeExclusivity_Int_83) {
    Object obj(5);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isInt64());
}

// =============================================================================
// Tests for Array operations
// =============================================================================

TEST_F(ObjectTest_83, ArrayObject_BasicOperations_83) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.arrayGetLength(), 0);

    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);

    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_83, ArrayObject_AddMultipleElements_83) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_83, ArrayObject_RemoveElement_83) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_83, ArrayObject_GetNF_83) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(77));
    const Object &nf = obj.arrayGetNF(0);
    EXPECT_TRUE(nf.isInt());
    EXPECT_EQ(nf.getInt(), 77);
}

// =============================================================================
// Tests for Dict operations
// =============================================================================

TEST_F(ObjectTest_83, DictObject_BasicOperations_83) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_83, DictObject_AddAndLookup_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_83, DictObject_SetOverwrites_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key", Object(1));
    obj.dictSet("key", Object(2));

    Object val = obj.dictLookup("key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_83, DictObject_Remove_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("a");
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_83, DictObject_LookupNonExistent_83) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_83, DictObject_GetKey_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_83, DictObject_GetVal_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("k", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_83, DictObject_GetValNF_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("k", Object(77));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_83, DictObject_LookupNF_83) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("k", Object(33));
    const Object &val = obj.dictLookupNF("k");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 33);
}

// =============================================================================
// Tests for getNum with ok parameter
// =============================================================================

TEST_F(ObjectTest_83, GetNumWithOk_IntOk_83) {
    Object obj(5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 5.0);
}

TEST_F(ObjectTest_83, GetNumWithOk_RealOk_83) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// =============================================================================
// Tests for string takeString
// =============================================================================

TEST_F(ObjectTest_83, TakeString_83) {
    Object obj(std::make_unique<GooString>("takeMe"));
    EXPECT_TRUE(obj.isString());
    auto str = obj.takeString();
    EXPECT_NE(str, nullptr);
}

// =============================================================================
// Tests for Name string retrieval
// =============================================================================

TEST_F(ObjectTest_83, NameObject_GetNameString_83) {
    Object obj(objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// =============================================================================
// Tests for deepCopy
// =============================================================================

TEST_F(ObjectTest_83, DeepCopy_IntObject_83) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_83, DeepCopy_StringObject_83) {
    Object obj(std::make_unique<GooString>("deepcopy"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
}

// =============================================================================
// Tests for isCmd with string_view variant
// =============================================================================

TEST_F(ObjectTest_83, CmdObject_IsCmdStringView_EmptyCmd_83) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd(""));
    EXPECT_FALSE(obj.isCmd("notempty"));
}

TEST_F(ObjectTest_83, CmdObject_IsCmdStringView_LongName_83) {
    Object obj(objCmd, "averylongcommandname");
    EXPECT_TRUE(obj.isCmd("averylongcommandname"));
    EXPECT_FALSE(obj.isCmd("averylongcommandnam"));
}

// =============================================================================
// Boundary: isNum for various types
// =============================================================================

TEST_F(ObjectTest_83, IsNum_OnlyForIntAndReal_83) {
    Object intObj(10);
    Object realObj(1.5);
    Object boolObj(true);
    Object nullObj = Object::null();

    EXPECT_TRUE(intObj.isNum());
    EXPECT_TRUE(realObj.isNum());
    EXPECT_FALSE(boolObj.isNum());
    EXPECT_FALSE(nullObj.isNum());
}

// =============================================================================
// Boundary: isIntOrInt64
// =============================================================================

TEST_F(ObjectTest_83, IsIntOrInt64_83) {
    Object intObj(10);
    Object int64Obj(100LL);
    Object realObj(1.5);

    EXPECT_TRUE(intObj.isIntOrInt64());
    EXPECT_TRUE(int64Obj.isIntOrInt64());
    EXPECT_FALSE(realObj.isIntOrInt64());
}
