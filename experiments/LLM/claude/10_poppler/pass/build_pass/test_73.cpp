#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_73 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== isReal() tests =====================

TEST_F(ObjectTest_73, IsRealReturnsTrueForRealObject_73) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForIntObject_73) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForBoolObject_73) {
    Object obj(true);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForNullObject_73) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForNoneObject_73) {
    Object obj;
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForErrorObject_73) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForEOFObject_73) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForInt64Object_73) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForStringObject_73) {
    Object obj(std::string("hello"));
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForNameObject_73) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_73, IsRealReturnsFalseForCmdObject_73) {
    Object obj(objCmd, "testCmd");
    EXPECT_FALSE(obj.isReal());
}

// ===================== Constructor and type tests =====================

TEST_F(ObjectTest_73, DefaultConstructorCreatesNoneObject_73) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_73, BoolConstructorCreatesBoolObject_73) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_73, IntConstructorCreatesIntObject_73) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_73, DoubleConstructorCreatesRealObject_73) {
    Object obj(2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_73, Int64ConstructorCreatesInt64Object_73) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_73, NullFactoryCreatesNullObject_73) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_73, ErrorFactoryCreatesErrorObject_73) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

TEST_F(ObjectTest_73, EofFactoryCreatesEOFObject_73) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// ===================== Value getters =====================

TEST_F(ObjectTest_73, GetBoolReturnsCorrectValue_73) {
    Object objTrue(true);
    Object objFalse(false);
    EXPECT_TRUE(objTrue.getBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectTest_73, GetIntReturnsCorrectValue_73) {
    Object obj(42);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_73, GetIntNegativeValue_73) {
    Object obj(-100);
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_73, GetIntZeroValue_73) {
    Object obj(0);
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_73, GetRealReturnsCorrectValue_73) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_73, GetRealZeroValue_73) {
    Object obj(0.0);
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_73, GetRealNegativeValue_73) {
    Object obj(-2.5);
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_73, GetNumForIntReturnsIntAsDouble_73) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNum(), 10.0);
}

TEST_F(ObjectTest_73, GetNumForRealReturnsReal_73) {
    Object obj(1.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 1.5);
}

TEST_F(ObjectTest_73, GetInt64ReturnsCorrectValue_73) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getInt64(), 9876543210LL);
}

TEST_F(ObjectTest_73, GetIntOrInt64ForIntReturnsValue_73) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_73, GetIntOrInt64ForInt64ReturnsValue_73) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getIntOrInt64(), 9876543210LL);
}

// ===================== isNum tests =====================

TEST_F(ObjectTest_73, IsNumTrueForInt_73) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_73, IsNumTrueForReal_73) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_73, IsNumFalseForBool_73) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_73, IsNumFalseForNull_73) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// ===================== isIntOrInt64 tests =====================

TEST_F(ObjectTest_73, IsIntOrInt64TrueForInt_73) {
    Object obj(5);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_73, IsIntOrInt64TrueForInt64_73) {
    Object obj(static_cast<long long>(5LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_73, IsIntOrInt64FalseForReal_73) {
    Object obj(5.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ===================== Type check exclusivity =====================

TEST_F(ObjectTest_73, TypeChecksMutuallyExclusive_73) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
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

// ===================== Move semantics =====================

TEST_F(ObjectTest_73, MoveConstructorTransfersType_73) {
    Object obj1(3.14);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

TEST_F(ObjectTest_73, MoveAssignmentTransfersType_73) {
    Object obj1(3.14);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 3.14);
}

// ===================== setToNull =====================

TEST_F(ObjectTest_73, SetToNullChangesTypeToNull_73) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
}

// ===================== copy =====================

TEST_F(ObjectTest_73, CopyPreservesRealValue_73) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_73, CopyPreservesIntValue_73) {
    Object obj(99);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 99);
}

TEST_F(ObjectTest_73, CopyPreservesBoolValue_73) {
    Object obj(false);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_FALSE(copied.getBool());
}

// ===================== Name object tests =====================

TEST_F(ObjectTest_73, NameObjectStoresName_73) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_73, IsNameWithMatchingString_73) {
    Object obj(objName, "Foo");
    EXPECT_TRUE(obj.isName("Foo"));
    EXPECT_FALSE(obj.isName("Bar"));
}

// ===================== Cmd object tests =====================

TEST_F(ObjectTest_73, CmdObjectStoresCmd_73) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_73, IsCmdWithMatchingString_73) {
    Object obj(objCmd, "Q");
    EXPECT_TRUE(obj.isCmd("Q"));
    EXPECT_FALSE(obj.isCmd("q"));
}

// ===================== String object tests =====================

TEST_F(ObjectTest_73, StringObjectIsString_73) {
    Object obj(std::string("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isReal());
}

// ===================== HexString object tests =====================

TEST_F(ObjectTest_73, HexStringObjectIsHexString_73) {
    Object obj(objHexString, "ABCDEF");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
}

// ===================== getNumWithDefaultValue =====================

TEST_F(ObjectTest_73, GetNumWithDefaultValueForReal_73) {
    Object obj(5.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 5.5);
}

TEST_F(ObjectTest_73, GetNumWithDefaultValueForInt_73) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 10.0);
}

TEST_F(ObjectTest_73, GetNumWithDefaultValueForNonNum_73) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

// ===================== getBoolWithDefaultValue =====================

TEST_F(ObjectTest_73, GetBoolWithDefaultValueForBool_73) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_73, GetBoolWithDefaultValueForNonBool_73) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ===================== getTypeName =====================

TEST_F(ObjectTest_73, GetTypeNameForReal_73) {
    Object obj(1.0);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_73, GetTypeNameForInt_73) {
    Object obj(1);
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST_F(ObjectTest_73, GetTypeNameForNull_73) {
    Object obj = Object::null();
    const char *name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// ===================== Boundary: very large/small doubles =====================

TEST_F(ObjectTest_73, IsRealWithVeryLargeDouble_73) {
    Object obj(1.0e308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e308);
}

TEST_F(ObjectTest_73, IsRealWithVerySmallDouble_73) {
    Object obj(1.0e-308);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e-308);
}

TEST_F(ObjectTest_73, IsRealWithNegativeDouble_73) {
    Object obj(-1.0e100);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.0e100);
}

// ===================== deepCopy =====================

TEST_F(ObjectTest_73, DeepCopyPreservesRealValue_73) {
    Object obj(7.77);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isReal());
    EXPECT_DOUBLE_EQ(deep.getReal(), 7.77);
}

// ===================== getNum with ok parameter =====================

TEST_F(ObjectTest_73, GetNumWithOkForReal_73) {
    Object obj(4.4);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 4.4);
}

TEST_F(ObjectTest_73, GetNumWithOkForInt_73) {
    Object obj(7);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 7.0);
}

TEST_F(ObjectTest_73, GetNumWithOkForNonNumeric_73) {
    Object obj = Object::null();
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_FALSE(ok);
}
