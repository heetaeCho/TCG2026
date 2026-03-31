#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_89 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Type Tests ====================

TEST_F(ObjectTest_89, DefaultConstructor_IsNone_89) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_89, BoolConstructor_IsBool_89) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_89, BoolConstructorFalse_89) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_89, IntConstructor_IsInt_89) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_89, IntConstructorNegative_89) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_89, IntConstructorZero_89) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_89, RealConstructor_IsReal_89) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_89, RealConstructorZero_89) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_89, RealConstructorNegative_89) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_89, Int64Constructor_IsInt64_89) {
    Object obj(static_cast<long long>(1234567890123LL));
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), 1234567890123LL);
}

TEST_F(ObjectTest_89, NameConstructor_IsName_89) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_89, CmdConstructor_IsCmd_89) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

// ==================== Static Factory Methods ====================

TEST_F(ObjectTest_89, NullFactory_IsNull_89) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_89, EofFactory_IsEOF_89) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_89, ErrorFactory_IsError_89) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== isName(string_view) Tests ====================

TEST_F(ObjectTest_89, IsNameWithMatchingString_ReturnsTrue_89) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
}

TEST_F(ObjectTest_89, IsNameWithNonMatchingString_ReturnsFalse_89) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("Bar"));
}

TEST_F(ObjectTest_89, IsNameOnNonNameObject_ReturnsFalse_89) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("SomeName"));
}

TEST_F(ObjectTest_89, IsNameOnNullObject_ReturnsFalse_89) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isName("SomeName"));
}

TEST_F(ObjectTest_89, IsNameOnBoolObject_ReturnsFalse_89) {
    Object obj(true);
    EXPECT_FALSE(obj.isName("true"));
}

TEST_F(ObjectTest_89, IsNameEmptyString_89) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName(""));
    EXPECT_FALSE(obj.isName("notempty"));
}

TEST_F(ObjectTest_89, IsNameCaseSensitive_89) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("foo"));
    EXPECT_FALSE(obj.isName("FOO"));
    EXPECT_TRUE(obj.isName("Foo"));
}

TEST_F(ObjectTest_89, IsNameWithSubstring_ReturnsFalse_89) {
    Object obj(objName, "FooBar");
    EXPECT_FALSE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
    EXPECT_TRUE(obj.isName("FooBar"));
}

TEST_F(ObjectTest_89, IsNameWithSuperstring_ReturnsFalse_89) {
    Object obj(objName, "Foo");
    EXPECT_FALSE(obj.isName("FooBar"));
}

// ==================== isCmd(string_view) Tests ====================

TEST_F(ObjectTest_89, IsCmdWithMatchingString_ReturnsTrue_89) {
    Object obj(objCmd, "BI");
    EXPECT_TRUE(obj.isCmd("BI"));
}

TEST_F(ObjectTest_89, IsCmdWithNonMatchingString_ReturnsFalse_89) {
    Object obj(objCmd, "BI");
    EXPECT_FALSE(obj.isCmd("EI"));
}

TEST_F(ObjectTest_89, IsCmdOnNonCmdObject_ReturnsFalse_89) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("something"));
}

// ==================== Type Query Methods ====================

TEST_F(ObjectTest_89, IsNumForInt_ReturnsTrue_89) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_89, IsNumForReal_ReturnsTrue_89) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_89, IsNumForBool_ReturnsFalse_89) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_89, IsIntOrInt64ForInt_ReturnsTrue_89) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_89, IsIntOrInt64ForInt64_ReturnsTrue_89) {
    Object obj(static_cast<long long>(42LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_89, IsIntOrInt64ForReal_ReturnsFalse_89) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== getNum Tests ====================

TEST_F(ObjectTest_89, GetNumFromInt_89) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_89, GetNumFromReal_89) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// ==================== getIntOrInt64 Tests ====================

TEST_F(ObjectTest_89, GetIntOrInt64FromInt_89) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_89, GetIntOrInt64FromInt64_89) {
    Object obj(static_cast<long long>(1234567890123LL));
    EXPECT_EQ(obj.getIntOrInt64(), 1234567890123LL);
}

// ==================== Move Semantics ====================

TEST_F(ObjectTest_89, MoveConstructor_89) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // obj1 should be in a valid but unspecified state (likely none or dead)
    EXPECT_TRUE(obj1.isNone() || obj1.getType() == objDead || obj1.isNull());
}

TEST_F(ObjectTest_89, MoveAssignment_89) {
    Object obj1(42);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== setToNull Tests ====================

TEST_F(ObjectTest_89, SetToNull_89) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ==================== copy Tests ====================

TEST_F(ObjectTest_89, CopyInt_89) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_89, CopyReal_89) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_89, CopyBool_89) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_89, CopyNull_89) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_89, CopyName_89) {
    Object obj(objName, "TestName");
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "TestName");
}

// ==================== getTypeName Tests ====================

TEST_F(ObjectTest_89, GetTypeName_Bool_89) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_89, GetTypeName_Int_89) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_89, GetTypeName_Null_89) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== getNumWithDefaultValue Tests ====================

TEST_F(ObjectTest_89, GetNumWithDefaultValue_FromInt_89) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_89, GetNumWithDefaultValue_FromReal_89) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_89, GetNumWithDefaultValue_FromNonNum_89) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_89, GetNumWithDefaultValue_FromBool_89) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(77.0), 77.0);
}

// ==================== getBoolWithDefaultValue Tests ====================

TEST_F(ObjectTest_89, GetBoolWithDefaultValue_FromBoolTrue_89) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_89, GetBoolWithDefaultValue_FromBoolFalse_89) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_89, GetBoolWithDefaultValue_FromNonBool_89) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_89, GetBoolWithDefaultValue_FromNonBoolDefaultFalse_89) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ==================== Negative Type Checks ====================

TEST_F(ObjectTest_89, IntIsNotBool_89) {
    Object obj(42);
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

TEST_F(ObjectTest_89, NoneIsNotAnythingElse_89) {
    Object obj;
    EXPECT_FALSE(obj.isBool());
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
    EXPECT_TRUE(obj.isNone());
}

// ==================== String Construction ====================

TEST_F(ObjectTest_89, StringConstructor_IsString_89) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_89, NameGetNameString_89) {
    Object obj(objName, "TestName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestName");
}

// ==================== Boundary: Name with special characters ====================

TEST_F(ObjectTest_89, IsNameWithSpecialChars_89) {
    Object obj(objName, "Name/With#Special");
    EXPECT_TRUE(obj.isName("Name/With#Special"));
    EXPECT_FALSE(obj.isName("Name/With"));
}

TEST_F(ObjectTest_89, IsNameWithSpaces_89) {
    Object obj(objName, "Name With Spaces");
    EXPECT_TRUE(obj.isName("Name With Spaces"));
    EXPECT_FALSE(obj.isName("NameWithSpaces"));
}

// ==================== getNum with ok parameter ====================

TEST_F(ObjectTest_89, GetNumWithOk_FromInt_89) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_89, GetNumWithOk_FromReal_89) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}
