#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object tests
class ObjectTest_84 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Tests for isError() =====

TEST_F(ObjectTest_84, IsError_ReturnsTrueForErrorObject_84) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForNullObject_84) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForEOFObject_84) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForBoolObject_84) {
    Object obj(true);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForIntObject_84) {
    Object obj(42);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForRealObject_84) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForInt64Object_84) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_84, IsError_ReturnsFalseForDefaultConstructedObject_84) {
    Object obj;
    EXPECT_FALSE(obj.isError());
}

// ===== Tests for other type-checking methods =====

TEST_F(ObjectTest_84, IsBool_ReturnsTrueForBoolObject_84) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectTest_84, IsBool_ReturnsFalseForIntObject_84) {
    Object obj(10);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_84, IsInt_ReturnsTrueForIntObject_84) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
}

TEST_F(ObjectTest_84, IsInt_ReturnsFalseForRealObject_84) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_84, IsReal_ReturnsTrueForRealObject_84) {
    Object obj(2.718);
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectTest_84, IsReal_ReturnsFalseForIntObject_84) {
    Object obj(10);
    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_84, IsNum_ReturnsTrueForIntObject_84) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_84, IsNum_ReturnsTrueForRealObject_84) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_84, IsNum_ReturnsFalseForBoolObject_84) {
    Object obj(false);
    EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectTest_84, IsNull_ReturnsTrueForNullObject_84) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_84, IsNull_ReturnsFalseForErrorObject_84) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isNull());
}

TEST_F(ObjectTest_84, IsEOF_ReturnsTrueForEOFObject_84) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_84, IsEOF_ReturnsFalseForNullObject_84) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_84, IsNone_ReturnsTrueForDefaultObject_84) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_84, IsNone_ReturnsFalseForIntObject_84) {
    Object obj(1);
    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_84, IsInt64_ReturnsTrueForInt64Object_84) {
    Object obj(static_cast<long long>(100LL));
    EXPECT_TRUE(obj.isInt64());
}

TEST_F(ObjectTest_84, IsInt64_ReturnsFalseForIntObject_84) {
    Object obj(100);
    EXPECT_FALSE(obj.isInt64());
}

TEST_F(ObjectTest_84, IsIntOrInt64_ReturnsTrueForIntObject_84) {
    Object obj(100);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_84, IsIntOrInt64_ReturnsTrueForInt64Object_84) {
    Object obj(static_cast<long long>(100LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_84, IsIntOrInt64_ReturnsFalseForRealObject_84) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ===== Tests for getType() =====

TEST_F(ObjectTest_84, GetType_ReturnsObjErrorForErrorObject_84) {
    Object obj = Object::error();
    EXPECT_EQ(obj.getType(), objError);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjNullForNullObject_84) {
    Object obj = Object::null();
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjEOFForEOFObject_84) {
    Object obj = Object::eof();
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjBoolForBoolObject_84) {
    Object obj(true);
    EXPECT_EQ(obj.getType(), objBool);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjIntForIntObject_84) {
    Object obj(42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjRealForRealObject_84) {
    Object obj(3.14);
    EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjInt64ForInt64Object_84) {
    Object obj(static_cast<long long>(999LL));
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST_F(ObjectTest_84, GetType_ReturnsObjNoneForDefaultConstructed_84) {
    Object obj;
    EXPECT_EQ(obj.getType(), objNone);
}

// ===== Tests for value getters =====

TEST_F(ObjectTest_84, GetBool_ReturnsTrueForTrueBoolObject_84) {
    Object obj(true);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_84, GetBool_ReturnsFalseForFalseBoolObject_84) {
    Object obj(false);
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_84, GetInt_ReturnsCorrectValue_84) {
    Object obj(42);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_84, GetInt_ReturnsZero_84) {
    Object obj(0);
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_84, GetInt_ReturnsNegativeValue_84) {
    Object obj(-100);
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_84, GetReal_ReturnsCorrectValue_84) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_84, GetReal_ReturnsZero_84) {
    Object obj(0.0);
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_84, GetReal_ReturnsNegativeValue_84) {
    Object obj(-2.5);
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_84, GetNum_ReturnsValueForInt_84) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_84, GetNum_ReturnsValueForReal_84) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

TEST_F(ObjectTest_84, GetInt64_ReturnsCorrectValue_84) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getInt64(), 9876543210LL);
}

TEST_F(ObjectTest_84, GetIntOrInt64_ReturnsIntValue_84) {
    Object obj(55);
    EXPECT_EQ(obj.getIntOrInt64(), 55LL);
}

TEST_F(ObjectTest_84, GetIntOrInt64_ReturnsInt64Value_84) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getIntOrInt64(), 9876543210LL);
}

// ===== Tests for setToNull() =====

TEST_F(ObjectTest_84, SetToNull_ChangesTypeToNull_84) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_84, SetToNull_ErrorBecomesNull_84) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isError());
}

// ===== Tests for move semantics =====

TEST_F(ObjectTest_84, MoveConstructor_TransfersType_84) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_84, MoveAssignment_TransfersType_84) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// ===== Tests for static factory methods =====

TEST_F(ObjectTest_84, NullFactory_CreatesNullObject_84) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_84, EofFactory_CreatesEOFObject_84) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_84, ErrorFactory_CreatesErrorObject_84) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ===== Tests for string/name/cmd objects =====

TEST_F(ObjectTest_84, IsString_ReturnsTrueForStringObject_84) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_84, IsString_ReturnsFalseForIntObject_84) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_84, IsName_WithStringArg_MatchesName_84) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_TRUE(obj.isName("TestName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}

TEST_F(ObjectTest_84, IsCmd_WithStringArg_MatchesCmd_84) {
    Object obj(objCmd, "TestCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_TRUE(obj.isCmd("TestCmd"));
    EXPECT_FALSE(obj.isCmd("OtherCmd"));
}

TEST_F(ObjectTest_84, GetName_ReturnsCorrectName_84) {
    Object obj(objName, "MyName");
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_84, GetCmd_ReturnsCorrectCmd_84) {
    Object obj(objCmd, "MyCmd");
    EXPECT_STREQ(obj.getCmd(), "MyCmd");
}

// ===== Tests for getNumWithDefaultValue =====

TEST_F(ObjectTest_84, GetNumWithDefaultValue_ReturnsNumForIntObj_84) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 10.0);
}

TEST_F(ObjectTest_84, GetNumWithDefaultValue_ReturnsNumForRealObj_84) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 2.5);
}

TEST_F(ObjectTest_84, GetNumWithDefaultValue_ReturnsDefaultForNonNumObj_84) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_84, GetNumWithDefaultValue_ReturnsDefaultForErrorObj_84) {
    Object obj = Object::error();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// ===== Tests for getBoolWithDefaultValue =====

TEST_F(ObjectTest_84, GetBoolWithDefaultValue_ReturnsBoolForBoolObj_84) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_84, GetBoolWithDefaultValue_ReturnsDefaultForNonBoolObj_84) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_84, GetBoolWithDefaultValue_ReturnsDefaultForNullObj_84) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ===== Tests for copy =====

TEST_F(ObjectTest_84, Copy_PreservesIntType_84) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_84, Copy_PreservesBoolType_84) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_84, Copy_PreservesRealType_84) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_84, Copy_PreservesErrorType_84) {
    Object obj = Object::error();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isError());
}

TEST_F(ObjectTest_84, Copy_PreservesNullType_84) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// ===== Tests for getTypeName =====

TEST_F(ObjectTest_84, GetTypeName_ReturnsNonNullForAllTypes_84) {
    Object boolObj(true);
    EXPECT_NE(boolObj.getTypeName(), nullptr);

    Object intObj(42);
    EXPECT_NE(intObj.getTypeName(), nullptr);

    Object realObj(3.14);
    EXPECT_NE(realObj.getTypeName(), nullptr);

    Object nullObj = Object::null();
    EXPECT_NE(nullObj.getTypeName(), nullptr);

    Object errorObj = Object::error();
    EXPECT_NE(errorObj.getTypeName(), nullptr);

    Object eofObj = Object::eof();
    EXPECT_NE(eofObj.getTypeName(), nullptr);
}

// ===== Boundary tests =====

TEST_F(ObjectTest_84, IntBoundary_MaxInt_84) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_84, IntBoundary_MinInt_84) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_84, Int64Boundary_LargeValue_84) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_84, RealBoundary_VerySmallPositive_84) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

TEST_F(ObjectTest_84, RealBoundary_VeryLargePositive_84) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());
}

// ===== Tests for string with std::string =====

TEST_F(ObjectTest_84, StringObject_FromStdString_84) {
    std::string s = "test string";
    Object obj(std::make_unique<GooString>(s));
    EXPECT_TRUE(obj.isString());
    EXPECT_NE(obj.getString(), nullptr);
}

// ===== Tests for name construction with ObjType =====

TEST_F(ObjectTest_84, NameObject_Construction_84) {
    Object obj(objName, "SomeName");
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_84, CmdObject_Construction_84) {
    Object obj(objCmd, "SomeCmd");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isString());
}

// ===== Cross-type checks: error object should not be other types =====

TEST_F(ObjectTest_84, ErrorObject_IsNotOtherTypes_84) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
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
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isIntOrInt64());
}

// ===== Null object should not be other types =====

TEST_F(ObjectTest_84, NullObject_IsNotOtherTypes_84) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ===== Tests for getNum with ok parameter =====

TEST_F(ObjectTest_84, GetNumWithOk_IntObject_84) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_84, GetNumWithOk_RealObject_84) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// ===== HexString type check =====

TEST_F(ObjectTest_84, HexStringObject_Construction_84) {
    Object obj(objHexString, "48656C6C6F");
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
    EXPECT_NE(obj.getHexString(), nullptr);
}
