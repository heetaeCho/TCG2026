#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_100 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ObjectTest_100, DefaultConstructor_CreatesNoneObject_100) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_100, BoolConstructor_True_100) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_100, BoolConstructor_False_100) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), false);
}

TEST_F(ObjectTest_100, IntConstructor_100) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_100, IntConstructor_Zero_100) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_100, IntConstructor_Negative_100) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_100, RealConstructor_100) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_100, RealConstructor_Zero_100) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_100, Int64Constructor_100) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_100, NameConstructor_100) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_100, CmdConstructor_100) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

// ==================== getNameString Tests ====================

TEST_F(ObjectTest_100, GetNameString_ReturnsCorrectString_100) {
    Object obj(objName, "MyName");
    EXPECT_TRUE(obj.isName());
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "MyName");
}

TEST_F(ObjectTest_100, GetNameString_EmptyName_100) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "");
}

TEST_F(ObjectTest_100, GetNameString_LongName_100) {
    std::string longName(256, 'A');
    Object obj(objName, longName.c_str());
    EXPECT_TRUE(obj.isName());
    std::string name = obj.getNameString();
    EXPECT_EQ(name, longName);
}

TEST_F(ObjectTest_100, GetNameString_SpecialCharacters_100) {
    Object obj(objName, "Name/With#Special");
    EXPECT_TRUE(obj.isName());
    std::string name = obj.getNameString();
    EXPECT_EQ(name, "Name/With#Special");
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_100, NullFactory_100) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_100, EofFactory_100) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_100, ErrorFactory_100) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== Type Check Tests ====================

TEST_F(ObjectTest_100, IsBool_TrueForBool_100) {
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

TEST_F(ObjectTest_100, IsInt_TrueForInt_100) {
    Object obj(10);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isName());
}

TEST_F(ObjectTest_100, IsReal_TrueForReal_100) {
    Object obj(2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_100, IsNum_TrueForInt_100) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_100, IsNum_TrueForReal_100) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_100, IsNum_FalseForBool_100) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_100, IsIntOrInt64_TrueForInt_100) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_100, IsIntOrInt64_TrueForInt64_100) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_100, IsIntOrInt64_FalseForReal_100) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_100, GetNum_FromInt_100) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_100, GetNum_FromReal_100) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

TEST_F(ObjectTest_100, GetNum_WithOkParam_Int_100) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

TEST_F(ObjectTest_100, GetNum_WithOkParam_Real_100) {
    Object obj(10.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.5);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_100, GetIntOrInt64_FromInt_100) {
    Object obj(99);
    EXPECT_EQ(obj.getIntOrInt64(), 99LL);
}

TEST_F(ObjectTest_100, GetIntOrInt64_FromInt64_100) {
    long long bigVal = 123456789012345LL;
    Object obj(bigVal);
    EXPECT_EQ(obj.getIntOrInt64(), bigVal);
}

// ==================== isName with argument Tests ====================

TEST_F(ObjectTest_100, IsNameWithArg_MatchingName_100) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_100, IsNameWithArg_NonMatchingName_100) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_100, IsNameWithArg_NotAName_100) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("TestName"));
}

// ==================== isCmd with argument Tests ====================

TEST_F(ObjectTest_100, IsCmdWithArg_MatchingCmd_100) {
    Object obj(objCmd, "BI");
    EXPECT_TRUE(obj.isCmd("BI"));
}

TEST_F(ObjectTest_100, IsCmdWithArg_NonMatchingCmd_100) {
    Object obj(objCmd, "BI");
    EXPECT_FALSE(obj.isCmd("EI"));
}

TEST_F(ObjectTest_100, IsCmdWithArg_NotACmd_100) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("BI"));
}

// ==================== Move Semantics Tests ====================

TEST_F(ObjectTest_100, MoveConstructor_100) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically objNone or objDead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead);
}

TEST_F(ObjectTest_100, MoveAssignment_100) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_100, SetToNull_FromInt_100) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_100, SetToNull_FromBool_100) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== Copy Tests ====================

TEST_F(ObjectTest_100, Copy_IntObject_100) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_100, Copy_BoolObject_100) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_EQ(copied.getBool(), true);
}

TEST_F(ObjectTest_100, Copy_RealObject_100) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_100, Copy_NameObject_100) {
    Object obj(objName, "CopyTest");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyTest");
    EXPECT_EQ(copied.getNameString(), "CopyTest");
}

TEST_F(ObjectTest_100, Copy_NullObject_100) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_100, GetNumWithDefaultValue_IntObject_100) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_100, GetNumWithDefaultValue_RealObject_100) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_100, GetNumWithDefaultValue_NonNumericObject_100) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_100, GetNumWithDefaultValue_NullObject_100) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(55.5), 55.5);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_100, GetBoolWithDefaultValue_BoolObjectTrue_100) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_100, GetBoolWithDefaultValue_BoolObjectFalse_100) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_100, GetBoolWithDefaultValue_NonBoolObject_100) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_100, GetTypeName_Bool_100) {
    Object obj(true);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_Int_100) {
    Object obj(42);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_Real_100) {
    Object obj(3.14);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_Name_100) {
    Object obj(objName, "test");
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_Null_100) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_Error_100) {
    Object obj = Object::error();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_EOF_100) {
    Object obj = Object::eof();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_100, GetTypeName_None_100) {
    Object obj;
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ==================== String Constructor Tests ====================

TEST_F(ObjectTest_100, StringConstructor_FromGooString_100) {
    auto gs = std::make_unique<GooString>("Hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    const GooString *s = obj.getString();
    EXPECT_NE(s, nullptr);
}

TEST_F(ObjectTest_100, StringConstructor_FromStdString_100) {
    std::string str = "TestString";
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    const GooString *s = obj.getString();
    EXPECT_NE(s, nullptr);
}

// ==================== HexString Tests ====================

TEST_F(ObjectTest_100, HexStringConstructor_100) {
    Object obj(objHexString, "48656C6C6F");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    const GooString *s = obj.getHexString();
    EXPECT_NE(s, nullptr);
}

// ==================== Array Tests ====================

TEST_F(ObjectTest_100, ArrayObject_GetLength_100) {
    Object obj(new Array(nullptr));
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_100, ArrayObject_AddAndGetLength_100) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
}

TEST_F(ObjectTest_100, ArrayObject_AddAndGet_100) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(100));
    EXPECT_EQ(obj.arrayGetLength(), 2);
    
    Object elem1 = obj.arrayGet(0);
    EXPECT_TRUE(elem1.isInt());
    EXPECT_EQ(elem1.getInt(), 42);
    
    Object elem2 = obj.arrayGet(1);
    EXPECT_TRUE(elem2.isInt());
    EXPECT_EQ(elem2.getInt(), 100);
}

TEST_F(ObjectTest_100, ArrayObject_GetNF_100) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(42));
    
    const Object &elem = obj.arrayGetNF(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_100, ArrayObject_Remove_100) {
    Object obj(new Array(nullptr));
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    
    Object first = obj.arrayGet(0);
    EXPECT_EQ(first.getInt(), 1);
    
    Object second = obj.arrayGet(1);
    EXPECT_EQ(second.getInt(), 3);
}

// ==================== Dict Tests ====================

TEST_F(ObjectTest_100, DictObject_GetLength_100) {
    Object obj(new Dict(nullptr));
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_100, DictObject_AddAndLookup_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_100, DictObject_Set_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictSet("key1", Object(100));
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_100, DictObject_Remove_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("key1", Object(42));
    obj.dictAdd("key2", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 2);
    
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_100, DictObject_LookupNonexistent_100) {
    Object obj(new Dict(nullptr));
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_100, DictObject_GetKey_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    
    const char *key = obj.dictGetKey(0);
    EXPECT_NE(key, nullptr);
    EXPECT_STREQ(key, "mykey");
}

TEST_F(ObjectTest_100, DictObject_GetVal_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_100, DictObject_GetValNF_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_100, DictObject_LookupNF_100) {
    Object obj(new Dict(nullptr));
    obj.dictAdd("mykey", Object(42));
    
    const Object &val = obj.dictLookupNF("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// ==================== Multiple Name Operations ====================

TEST_F(ObjectTest_100, GetName_ReturnsConstChar_100) {
    Object obj(objName, "SomeName");
    const char *name = obj.getName();
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "SomeName");
}

TEST_F(ObjectTest_100, GetNameString_ConsistentWithGetName_100) {
    Object obj(objName, "ConsistencyTest");
    const char *cName = obj.getName();
    std::string sName = obj.getNameString();
    EXPECT_EQ(sName, std::string(cName));
}

// ==================== Deep Copy Tests ====================

TEST_F(ObjectTest_100, DeepCopy_IntObject_100) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_100, DeepCopy_NameObject_100) {
    Object obj(objName, "DeepCopyName");
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isName());
    EXPECT_EQ(deep.getNameString(), "DeepCopyName");
}

// ==================== Int boundary tests ====================

TEST_F(ObjectTest_100, IntConstructor_MaxInt_100) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_100, IntConstructor_MinInt_100) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_100, Int64Constructor_MinInt64_100) {
    long long minVal = std::numeric_limits<long long>::min();
    Object obj(minVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), minVal);
}

// ==================== Real boundary tests ====================

TEST_F(ObjectTest_100, RealConstructor_NegativeValue_100) {
    Object obj(-99.99);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -99.99);
}

TEST_F(ObjectTest_100, RealConstructor_VerySmallValue_100) {
    Object obj(1e-300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-300);
}

// ==================== Print Test ====================

TEST_F(ObjectTest_100, Print_IntObject_DoesNotCrash_100) {
    Object obj(42);
    // Just ensure print doesn't crash; we can't easily check output
    FILE *f = tmpfile();
    if (f) {
        obj.print(f);
        fclose(f);
    }
}

TEST_F(ObjectTest_100, Print_NameObject_DoesNotCrash_100) {
    Object obj(objName, "PrintTest");
    FILE *f = tmpfile();
    if (f) {
        obj.print(f);
        fclose(f);
    }
}

TEST_F(ObjectTest_100, Print_NullObject_DoesNotCrash_100) {
    Object obj = Object::null();
    FILE *f = tmpfile();
    if (f) {
        obj.print(f);
        fclose(f);
    }
}
