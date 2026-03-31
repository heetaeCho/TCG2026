#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_86 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Construction ====================

TEST_F(ObjectTest_86, DefaultConstructorCreatesNoneObject_86) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// ==================== Type Checking Methods ====================

TEST_F(ObjectTest_86, BoolObjectIsBool_86) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_86, IntObjectIsInt_86) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_86, RealObjectIsReal_86) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_86, Int64ObjectIsInt64_86) {
    Object obj(static_cast<long long>(123456789012345LL));
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objInt64);
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_86, NullObjectIsNull_86) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isError());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_86, EofObjectIsEOF_86) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_86, ErrorObjectIsError_86) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNone());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Value Getters ====================

TEST_F(ObjectTest_86, GetBoolReturnsCorrectValue_86) {
    Object objTrue(true);
    Object objFalse(false);
    EXPECT_TRUE(objTrue.getBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectTest_86, GetIntReturnsCorrectValue_86) {
    Object obj(42);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_86, GetIntNegativeValue_86) {
    Object obj(-100);
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_86, GetIntZeroValue_86) {
    Object obj(0);
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_86, GetRealReturnsCorrectValue_86) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_86, GetNumFromInt_86) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_86, GetNumFromReal_86) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_86, GetInt64ReturnsCorrectValue_86) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_86, GetIntOrInt64FromInt_86) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_86, GetIntOrInt64FromInt64_86) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// ==================== String Objects ====================

TEST_F(ObjectTest_86, StringObjectIsString_86) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
    EXPECT_FALSE(obj.isName());
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_86, StringObjectGetStringValue_86) {
    Object obj(std::make_unique<GooString>("test string"));
    EXPECT_TRUE(obj.isString());
    const GooString *str = obj.getString();
    EXPECT_NE(str, nullptr);
}

TEST_F(ObjectTest_86, HexStringObject_86) {
    Object obj(objHexString, std::string_view("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_EQ(obj.getType(), objHexString);
}

// ==================== Name Objects ====================

TEST_F(ObjectTest_86, NameObjectIsName_86) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objName);
}

TEST_F(ObjectTest_86, NameObjectGetName_86) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_86, IsNameWithMatchingName_86) {
    Object obj(objName, "Type");
    EXPECT_TRUE(obj.isName("Type"));
    EXPECT_FALSE(obj.isName("Other"));
}

TEST_F(ObjectTest_86, IsNameWithNonMatchingName_86) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("Bar"));
}

// ==================== Cmd Objects ====================

TEST_F(ObjectTest_86, CmdObjectIsCmd_86) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_FALSE(obj.isName());
    EXPECT_EQ(obj.getType(), objCmd);
}

TEST_F(ObjectTest_86, CmdObjectGetCmd_86) {
    Object obj(objCmd, "ET");
    EXPECT_STREQ(obj.getCmd(), "ET");
}

TEST_F(ObjectTest_86, IsCmdWithMatchingCmd_86) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== Move Semantics ====================

TEST_F(ObjectTest_86, MoveConstructor_86) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);

    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_86, MoveAssignment_86) {
    Object obj1(42);
    Object obj2;
    EXPECT_TRUE(obj2.isNone());

    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull ====================

TEST_F(ObjectTest_86, SetToNull_86) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

// ==================== Copy ====================

TEST_F(ObjectTest_86, CopyIntObject_86) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_86, CopyBoolObject_86) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_86, CopyRealObject_86) {
    Object obj(1.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 1.5);
}

TEST_F(ObjectTest_86, CopyNullObject_86) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_86, CopyNameObject_86) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== getTypeName ====================

TEST_F(ObjectTest_86, GetTypeNameForBool_86) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_86, GetTypeNameForInt_86) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_86, GetTypeNameForNull_86) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== getNumWithDefaultValue ====================

TEST_F(ObjectTest_86, GetNumWithDefaultValueFromInt_86) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_86, GetNumWithDefaultValueFromReal_86) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_86, GetNumWithDefaultValueFromNonNum_86) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST_F(ObjectTest_86, GetNumWithDefaultValueFromNone_86) {
    Object obj;
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue ====================

TEST_F(ObjectTest_86, GetBoolWithDefaultValueFromBool_86) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_86, GetBoolWithDefaultValueFromNonBool_86) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_86, GetBoolWithDefaultValueFromNone_86) {
    Object obj;
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array Operations ====================

TEST_F(ObjectTest_86, ArrayObjectCreation_86) {
    // Create an array object
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_86, ArrayGetLength_86) {
    Object obj(new Array(nullptr));
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_86, ArrayAddAndGetLength_86) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

TEST_F(ObjectTest_86, ArrayGetElement_86) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(100));

    Object elem0 = obj.arrayGet(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 42);

    Object elem1 = obj.arrayGet(1);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 100);
}

TEST_F(ObjectTest_86, ArrayGetNF_86) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));

    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_86, ArrayRemoveElement_86) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// ==================== Dict Operations ====================

TEST_F(ObjectTest_86, DictObjectCreation_86) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_86, DictGetLength_86) {
    Object obj(new Dict(nullptr));
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_86, DictAddAndGetLength_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictAdd("Key2", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 2);
}

TEST_F(ObjectTest_86, DictLookup_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("MyKey", Object(42));

    Object val = obj.dictLookup("MyKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_86, DictLookupNonExistentKey_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));

    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_86, DictLookupNF_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));

    const Object &val = obj.dictLookupNF("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_86, DictGetKey_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Alpha", Object(1));

    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "Alpha");
}

TEST_F(ObjectTest_86, DictGetVal_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(99));

    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_86, DictGetValNF_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(99));

    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_86, DictSet_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(100));

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_86, DictRemove_86) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(42));
    obj.dictAdd("Key2", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 2);

    obj.dictRemove("Key1");
    EXPECT_EQ(obj.dictGetLength(), 1);

    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isNull());
}

// ==================== isNone Specific Tests ====================

TEST_F(ObjectTest_86, IsNoneTrueForDefaultObject_86) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForIntObject_86) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForNullObject_86) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForErrorObject_86) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForEofObject_86) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForBoolObject_86) {
    Object obj(false);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_86, IsNoneFalseForRealObject_86) {
    Object obj(0.0);
    EXPECT_FALSE(obj.isNone());
}

// ==================== Boundary Values ====================

TEST_F(ObjectTest_86, IntMaxValue_86) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_86, IntMinValue_86) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_86, RealZero_86) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_86, RealNegative_86) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

TEST_F(ObjectTest_86, Int64MaxValue_86) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_86, Int64MinValue_86) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== String with std::string ====================

TEST_F(ObjectTest_86, StringFromStdString_86) {
    std::string s = "hello world";
    Object obj(std::make_unique<GooString>(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ==================== Name string ====================

TEST_F(ObjectTest_86, NameGetNameString_86) {
    Object obj(objName, "TestNameStr");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestNameStr");
}

// ==================== Multiple type transitions via move ====================

TEST_F(ObjectTest_86, MoveAssignmentReplacesType_86) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());

    obj = Object(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_86, MoveAssignmentToNone_86) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());

    obj = Object();
    EXPECT_TRUE(obj.isNone());
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_86, GetNumWithOkFromInt_86) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_86, GetNumWithOkFromReal_86) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== deepCopy ====================

TEST_F(ObjectTest_86, DeepCopyInt_86) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_86, DeepCopyBool_86) {
    Object obj(true);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isBool());
    EXPECT_TRUE(deep.getBool());
}

// ==================== takeString ====================

TEST_F(ObjectTest_86, TakeString_86) {
    Object obj(std::make_unique<GooString>("take me"));
    EXPECT_TRUE(obj.isString());
    std::unique_ptr<GooString> taken = obj.takeString();
    EXPECT_NE(taken, nullptr);
}

// ==================== Empty name ====================

TEST_F(ObjectTest_86, EmptyNameObject_86) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// ==================== isNum ====================

TEST_F(ObjectTest_86, IsNumForInt_86) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_86, IsNumForReal_86) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_86, IsNumForBool_86) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_86, IsNumForString_86) {
    Object obj(std::make_unique<GooString>("123"));
    EXPECT_FALSE(obj.isNum());
}
