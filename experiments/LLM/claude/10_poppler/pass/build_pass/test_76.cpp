#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_76 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isHexString tests ====================

TEST_F(ObjectTest_76, IsHexString_WhenConstructedAsHexString_ReturnsTrue_76) {
    Object obj(objHexString, std::string("48656C6C6F"));
    EXPECT_TRUE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenConstructedAsRegularString_ReturnsFalse_76) {
    Object obj(std::make_unique<GooString>("Hello"));
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenDefaultConstructed_ReturnsFalse_76) {
    Object obj;
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenNull_ReturnsFalse_76) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenBool_ReturnsFalse_76) {
    Object obj(true);
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenReal_ReturnsFalse_76) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenError_ReturnsFalse_76) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenEOF_ReturnsFalse_76) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, IsHexString_WhenInt64_ReturnsFalse_76) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isHexString());
}

// ==================== Type check tests ====================

TEST_F(ObjectTest_76, IsBool_WhenBool_ReturnsTrue_76) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectTest_76, IsBool_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_76, IsInt_WhenInt_ReturnsTrue_76) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
}

TEST_F(ObjectTest_76, IsInt_WhenReal_ReturnsFalse_76) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_76, IsReal_WhenReal_ReturnsTrue_76) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectTest_76, IsReal_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_76, IsNum_WhenInt_ReturnsTrue_76) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_76, IsNum_WhenReal_ReturnsTrue_76) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_76, IsNum_WhenString_ReturnsFalse_76) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_76, IsString_WhenString_ReturnsTrue_76) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_76, IsString_WhenHexString_ReturnsFalse_76) {
    Object obj(objHexString, std::string("48656C6C6F"));
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_76, IsNull_WhenNull_ReturnsTrue_76) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_76, IsNull_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_76, IsError_WhenError_ReturnsTrue_76) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectTest_76, IsError_WhenNull_ReturnsFalse_76) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_76, IsEOF_WhenEOF_ReturnsTrue_76) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_76, IsEOF_WhenNull_ReturnsFalse_76) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_76, IsNone_WhenDefaultConstructed_ReturnsTrue_76) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_76, IsNone_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_76, IsInt64_WhenInt64_ReturnsTrue_76) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_TRUE(obj.isInt64());
}

TEST_F(ObjectTest_76, IsInt64_WhenInt_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_76, IsIntOrInt64_WhenInt_ReturnsTrue_76) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_76, IsIntOrInt64_WhenInt64_ReturnsTrue_76) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_76, IsIntOrInt64_WhenReal_ReturnsFalse_76) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ==================== Value getter tests ====================

TEST_F(ObjectTest_76, GetBool_WhenTrue_ReturnsTrue_76) {
    Object obj(true);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_76, GetBool_WhenFalse_ReturnsFalse_76) {
    Object obj(false);
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_76, GetInt_ReturnsCorrectValue_76) {
    Object obj(42);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_76, GetInt_NegativeValue_76) {
    Object obj(-100);
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_76, GetInt_Zero_76) {
    Object obj(0);
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_76, GetReal_ReturnsCorrectValue_76) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_76, GetNum_WhenInt_ReturnsCorrectValue_76) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_76, GetNum_WhenReal_ReturnsCorrectValue_76) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_76, GetInt64_ReturnsCorrectValue_76) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getInt64(), 9876543210LL);
}

TEST_F(ObjectTest_76, GetIntOrInt64_WhenInt_ReturnsCorrectValue_76) {
    Object obj(42);
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_76, GetIntOrInt64_WhenInt64_ReturnsCorrectValue_76) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getIntOrInt64(), 9876543210LL);
}

TEST_F(ObjectTest_76, GetString_ReturnsNonNull_76) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_NE(obj.getString(), nullptr);
}

TEST_F(ObjectTest_76, GetHexString_WhenHexString_ReturnsNonNull_76) {
    Object obj(objHexString, std::string("ABCD"));
    EXPECT_NE(obj.getHexString(), nullptr);
}

// ==================== getType tests ====================

TEST_F(ObjectTest_76, GetType_WhenBool_ReturnsBoolType_76) {
    Object obj(true);
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_76, GetType_WhenInt_ReturnsIntType_76) {
    Object obj(42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_76, GetType_WhenReal_ReturnsRealType_76) {
    Object obj(3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_76, GetType_WhenString_ReturnsStringType_76) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectTest_76, GetType_WhenHexString_ReturnsHexStringType_76) {
    Object obj(objHexString, std::string("ABCD"));
    EXPECT_EQ(obj.getType(), objHexString);
}

TEST_F(ObjectTest_76, GetType_WhenNull_ReturnsNullType_76) {
    Object obj = Object::null();
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_76, GetType_WhenError_ReturnsErrorType_76) {
    Object obj = Object::error();
    EXPECT_EQ(obj.getType(), objError);
}

TEST_F(ObjectTest_76, GetType_WhenEOF_ReturnsEOFType_76) {
    Object obj = Object::eof();
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_76, GetType_WhenDefault_ReturnsNoneType_76) {
    Object obj;
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_76, GetType_WhenInt64_ReturnsInt64Type_76) {
    Object obj(static_cast<long long>(123LL));
    EXPECT_EQ(obj.getType(), objInt64);
}

// ==================== setToNull tests ====================

TEST_F(ObjectTest_76, SetToNull_ChangesTypeToNull_76) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_76, SetToNull_FromBool_76) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
}

// ==================== Move semantics tests ====================

TEST_F(ObjectTest_76, MoveConstructor_TransfersOwnership_76) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_76, MoveAssignment_TransfersOwnership_76) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ==================== copy tests ====================

TEST_F(ObjectTest_76, Copy_Int_76) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_76, Copy_Bool_76) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_76, Copy_Real_76) {
    Object obj(2.718);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.718);
}

TEST_F(ObjectTest_76, Copy_Null_76) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_76, Copy_HexString_76) {
    Object obj(objHexString, std::string("BEEF"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isHexString());
}

// ==================== getNumWithDefaultValue tests ====================

TEST_F(ObjectTest_76, GetNumWithDefaultValue_WhenInt_ReturnsNum_76) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 42.0);
}

TEST_F(ObjectTest_76, GetNumWithDefaultValue_WhenReal_ReturnsNum_76) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 3.14);
}

TEST_F(ObjectTest_76, GetNumWithDefaultValue_WhenNotNum_ReturnsDefault_76) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ==================== getBoolWithDefaultValue tests ====================

TEST_F(ObjectTest_76, GetBoolWithDefaultValue_WhenBoolTrue_ReturnsTrue_76) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_76, GetBoolWithDefaultValue_WhenBoolFalse_ReturnsFalse_76) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_76, GetBoolWithDefaultValue_WhenNotBool_ReturnsDefault_76) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

// ==================== Static factory method tests ====================

TEST_F(ObjectTest_76, NullFactory_CreatesNullObject_76) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_76, EofFactory_CreatesEOFObject_76) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_76, ErrorFactory_CreatesErrorObject_76) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ==================== getTypeName tests ====================

TEST_F(ObjectTest_76, GetTypeName_WhenBool_ReturnsNonNull_76) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_76, GetTypeName_WhenInt_ReturnsNonNull_76) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_76, GetTypeName_WhenNull_ReturnsNonNull_76) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_76, GetTypeName_WhenHexString_ReturnsNonNull_76) {
    Object obj(objHexString, std::string("ABCD"));
    EXPECT_NE(obj.getTypeName(), nullptr);
}

// ==================== HexString with different string constructors ====================

TEST_F(ObjectTest_76, HexString_ConstructedWithStringView_76) {
    Object obj(objHexString, std::string_view("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_EQ(obj.getType(), objHexString);
}

TEST_F(ObjectTest_76, HexString_ConstructedWithCString_76) {
    Object obj(objHexString, "CAFEBABE");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_76, HexString_EmptyString_76) {
    Object obj(objHexString, std::string(""));
    EXPECT_TRUE(obj.isHexString());
}

// ==================== Name type tests ====================

TEST_F(ObjectTest_76, IsName_WhenName_ReturnsTrue_76) {
    Object obj(objName, std::string("TestName"));
    EXPECT_TRUE(obj.isName());
}

TEST_F(ObjectTest_76, IsName_WhenNotName_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isName());
}

TEST_F(ObjectTest_76, IsNameWithArg_WhenMatching_ReturnsTrue_76) {
    Object obj(objName, std::string("TestName"));
    EXPECT_TRUE(obj.isName("TestName"));
}

TEST_F(ObjectTest_76, IsNameWithArg_WhenNotMatching_ReturnsFalse_76) {
    Object obj(objName, std::string("TestName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}

// ==================== Cmd type tests ====================

TEST_F(ObjectTest_76, IsCmd_WhenCmd_ReturnsTrue_76) {
    Object obj(objCmd, std::string("BT"));
    EXPECT_TRUE(obj.isCmd());
}

TEST_F(ObjectTest_76, IsCmd_WhenNotCmd_ReturnsFalse_76) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_76, IsCmdWithArg_WhenMatching_ReturnsTrue_76) {
    Object obj(objCmd, std::string("BT"));
    EXPECT_TRUE(obj.isCmd("BT"));
}

TEST_F(ObjectTest_76, IsCmdWithArg_WhenNotMatching_ReturnsFalse_76) {
    Object obj(objCmd, std::string("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// ==================== Boundary value tests ====================

TEST_F(ObjectTest_76, Int_MaxValue_76) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_76, Int_MinValue_76) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_76, Real_Zero_76) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_76, Real_NegativeValue_76) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

TEST_F(ObjectTest_76, Int64_LargeValue_76) {
    long long val = 9999999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_76, Int64_NegativeLargeValue_76) {
    long long val = -9999999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// ==================== Multiple type checks on same object ====================

TEST_F(ObjectTest_76, TypeExclusivity_Int_76) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
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

TEST_F(ObjectTest_76, TypeExclusivity_HexString_76) {
    Object obj(objHexString, std::string("FF"));
    EXPECT_TRUE(obj.isHexString());
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
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
}

// ==================== GetNum with ok parameter ====================

TEST_F(ObjectTest_76, GetNumWithOk_WhenInt_SetsOkTrue_76) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_76, GetNumWithOk_WhenReal_SetsOkTrue_76) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(ObjectTest_76, GetNumWithOk_WhenNotNum_SetsOkFalse_76) {
    Object obj = Object::null();
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_FALSE(ok);
}

// ==================== String-based constructor tests ====================

TEST_F(ObjectTest_76, StringConstructor_StdString_76) {
    Object obj(std::string("hello world"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_76, NameConstructor_76) {
    Object obj(objName, std::string("MyName"));
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(std::string(obj.getName()), "MyName");
}

TEST_F(ObjectTest_76, CmdConstructor_76) {
    Object obj(objCmd, std::string("q"));
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(std::string(obj.getCmd()), "q");
}
