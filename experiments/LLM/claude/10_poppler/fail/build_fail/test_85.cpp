#include <gtest/gtest.h>
#include "Object.h"

class ObjectTest_85 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Type Check Tests ====================

TEST_F(ObjectTest_85, DefaultConstructorCreatesNoneObject_85) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_85, BoolConstructorCreatesBoolObject_85) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_85, BoolFalseConstructor_85) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_85, IntConstructorCreatesIntObject_85) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_85, IntNegativeValue_85) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_85, IntZeroValue_85) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_85, RealConstructorCreatesRealObject_85) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_85, RealZeroValue_85) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_85, RealNegativeValue_85) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_85, Int64ConstructorCreatesInt64Object_85) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_85, NullStaticFactory_85) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_85, EofStaticFactory_85) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_85, ErrorStaticFactory_85) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== isEOF Specific Tests ====================

TEST_F(ObjectTest_85, IsEOFReturnsTrueForEOFObject_85) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForNullObject_85) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForErrorObject_85) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForBoolObject_85) {
    Object obj(true);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForIntObject_85) {
    Object obj(42);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForRealObject_85) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForNoneObject_85) {
    Object obj;
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_85, IsEOFReturnsFalseForInt64Object_85) {
    Object obj((long long)123456789LL);
    EXPECT_FALSE(obj.isEOF());
}

// ==================== Type Exclusivity Tests ====================

TEST_F(ObjectTest_85, BoolIsNotOtherTypes_85) {
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
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_85, IntIsNotOtherTypes_85) {
    Object obj(10);
    EXPECT_FALSE(obj.isBool());
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_85, NullIsNotOtherTypes_85) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isNone());
}

// ==================== isNum Tests ====================

TEST_F(ObjectTest_85, IsNumTrueForInt_85) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_85, IsNumTrueForReal_85) {
    Object obj(5.0);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_85, IsNumFalseForBool_85) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_85, IsNumFalseForNull_85) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// ==================== isIntOrInt64 Tests ====================

TEST_F(ObjectTest_85, IsIntOrInt64TrueForInt_85) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_85, IsIntOrInt64TrueForInt64_85) {
    Object obj((long long)42LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_85, IsIntOrInt64FalseForReal_85) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_85, GetNumFromInt_85) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_85, GetNumFromReal_85) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_85, GetIntOrInt64FromInt_85) {
    Object obj(99);
    EXPECT_EQ(obj.getIntOrInt64(), 99LL);
}

TEST_F(ObjectTest_85, GetIntOrInt64FromInt64_85) {
    Object obj((long long)9999999999LL);
    EXPECT_EQ(obj.getIntOrInt64(), 9999999999LL);
}

// ==================== Move Semantics Tests ====================

TEST_F(ObjectTest_85, MoveConstructor_85) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_85, MoveAssignment_85) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_85, MoveConstructorEOF_85) {
    Object obj1 = Object::eof();
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isEOF());
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_85, SetToNullFromInt_85) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_85, SetToNullFromEOF_85) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isEOF());
}

// ==================== String Object Tests ====================

TEST_F(ObjectTest_85, StringObjectFromString_85) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_85, StringObjectFromStdString_85) {
    Object obj(std::string("world"));
    EXPECT_TRUE(obj.isString());
}

// ==================== HexString Object Tests ====================

TEST_F(ObjectTest_85, HexStringObject_85) {
    Object obj(objHexString, std::string("ABCDEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== Name Object Tests ====================

TEST_F(ObjectTest_85, NameObject_85) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_85, NameObjectIsNameCheck_85) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

// ==================== Cmd Object Tests ====================

TEST_F(ObjectTest_85, CmdObject_85) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_85, CmdObjectIsCmdCheck_85) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_85, CopyInt_85) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_85, CopyBool_85) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_85, CopyReal_85) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_85, CopyNull_85) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_85, CopyEOF_85) {
    Object obj = Object::eof();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isEOF());
}

TEST_F(ObjectTest_85, CopyError_85) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_85, CopyNone_85) {
    Object obj;
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNone());
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_85, GetTypeNameBool_85) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_85, GetTypeNameInt_85) {
    Object obj(1);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_85, GetTypeNameNull_85) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_85, GetTypeNameEOF_85) {
    Object obj = Object::eof();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_85, GetNumWithDefaultValueFromInt_85) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 10.0);
}

TEST_F(ObjectTest_85, GetNumWithDefaultValueFromReal_85) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_85, GetNumWithDefaultValueFromNonNum_85) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_85, GetNumWithDefaultValueFromBool_85) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_85, GetBoolWithDefaultValueFromBoolTrue_85) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_85, GetBoolWithDefaultValueFromBoolFalse_85) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_85, GetBoolWithDefaultValueFromNonBool_85) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_85, GetBoolWithDefaultValueFromNonBoolFalse_85) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_85, ArrayObject_85) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
}

TEST_F(ObjectTest_85, ArrayGetLength_85) {
    Object obj(new Array(nullptr));
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_85, ArrayAddAndGetLength_85) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_85, ArrayAddMultiple_85) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

TEST_F(ObjectTest_85, ArrayGetElement_85) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_85, ArrayGetNF_85) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(99));
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 99);
}

TEST_F(ObjectTest_85, ArrayRemove_85) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    obj.arrayRemove(0);
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_85, DictObject_85) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

TEST_F(ObjectTest_85, DictGetLength_85) {
    Object obj(new Dict(nullptr));
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_85, DictAddAndLookup_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key1", Object(123));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 123);
}

TEST_F(ObjectTest_85, DictSetOverwrite_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key", Object(1));
    obj.dictSet("Key", Object(2));
    Object val = obj.dictLookup("Key");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 2);
}

TEST_F(ObjectTest_85, DictRemove_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Key", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    obj.dictRemove("Key");
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_85, DictLookupNonExistent_85) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("NonExistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_85, DictGetKey_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("MyKey", Object(10));
    const char *key = obj.dictGetKey(0);
    EXPECT_STREQ(key, "MyKey");
}

TEST_F(ObjectTest_85, DictGetVal_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("K", Object(55));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

TEST_F(ObjectTest_85, DictGetValNF_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("K", Object(77));
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_85, DictLookupNF_85) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("Test", Object(33));
    const Object &val = obj.dictLookupNF("Test");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 33);
}

// ==================== Boundary / Edge Case Tests ====================

TEST_F(ObjectTest_85, IntMaxValue_85) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_85, IntMinValue_85) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_85, Int64MaxValue_85) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_85, Int64MinValue_85) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_85, RealInfinity_85) {
    Object obj(std::numeric_limits<double>::infinity());
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getReal(), std::numeric_limits<double>::infinity());
}

TEST_F(ObjectTest_85, EmptyName_85) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_85, EmptyCmd_85) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// ==================== Destructor / Cleanup Tests ====================

TEST_F(ObjectTest_85, DestructorDoesNotCrash_85) {
    {
        Object obj(42);
    }
    {
        Object obj = Object::null();
    }
    {
        Object obj = Object::eof();
    }
    {
        Object obj = Object::error();
    }
    {
        Object obj(new Array(nullptr));
    }
    {
        Object obj(new Dict(nullptr));
    }
    SUCCEED();
}

// ==================== getNum with ok parameter Tests ====================

TEST_F(ObjectTest_85, GetNumWithOkFromInt_85) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_85, GetNumWithOkFromReal_85) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== Name String Tests ====================

TEST_F(ObjectTest_85, GetNameString_85) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== Multiple Move Operations ====================

TEST_F(ObjectTest_85, ChainedMoveAssignment_85) {
    Object obj1(10);
    Object obj2(20);
    Object obj3;
    obj3 = std::move(obj2);
    obj3 = std::move(obj1);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 10);
}

// ==================== takeString Tests ====================

TEST_F(ObjectTest_85, TakeString_85) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_TRUE(obj.isString());
    auto str = obj.takeString();
    EXPECT_NE(str, nullptr);
}
