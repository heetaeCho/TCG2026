#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "Object.h"

// Test constructing Object from std::string rvalue
TEST(ObjectStringConstructorTest_2747, ConstructFromString_2747) {
    std::string testStr = "Hello, World!";
    Object obj(std::move(testStr));
    
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
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

TEST(ObjectStringConstructorTest_2747, StringContentIsCorrect_2747) {
    std::string testStr = "Test String Content";
    Object obj(std::move(testStr));
    
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "Test String Content");
}

TEST(ObjectStringConstructorTest_2747, EmptyString_2747) {
    std::string testStr = "";
    Object obj(std::move(testStr));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "");
}

TEST(ObjectStringConstructorTest_2747, LongString_2747) {
    std::string testStr(10000, 'A');
    Object obj(std::move(testStr));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->getLength(), 10000);
}

TEST(ObjectStringConstructorTest_2747, StringWithSpecialCharacters_2747) {
    std::string testStr = "Hello\0World";
    // Note: std::string constructed from literal stops at \0, but let's test with embedded null
    std::string testStr2("Hello\0World", 11);
    Object obj(std::move(testStr2));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->getLength(), 11);
}

TEST(ObjectStringConstructorTest_2747, StringWithNewlines_2747) {
    std::string testStr = "Line1\nLine2\nLine3";
    Object obj(std::move(testStr));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "Line1\nLine2\nLine3");
}

// Test default constructor
TEST(ObjectDefaultConstructorTest_2747, DefaultIsNone_2747) {
    Object obj;
    
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// Test bool constructor
TEST(ObjectBoolConstructorTest_2747, TrueValue_2747) {
    Object obj(true);
    
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST(ObjectBoolConstructorTest_2747, FalseValue_2747) {
    Object obj(false);
    
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test int constructor
TEST(ObjectIntConstructorTest_2747, PositiveInt_2747) {
    Object obj(42);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST(ObjectIntConstructorTest_2747, ZeroInt_2747) {
    Object obj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST(ObjectIntConstructorTest_2747, NegativeInt_2747) {
    Object obj(-100);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST(ObjectIntConstructorTest_2747, IsNumForInt_2747) {
    Object obj(42);
    
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

// Test double constructor
TEST(ObjectRealConstructorTest_2747, PositiveReal_2747) {
    Object obj(3.14);
    
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST(ObjectRealConstructorTest_2747, ZeroReal_2747) {
    Object obj(0.0);
    
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST(ObjectRealConstructorTest_2747, NegativeReal_2747) {
    Object obj(-2.718);
    
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST(ObjectRealConstructorTest_2747, IsNumForReal_2747) {
    Object obj(3.14);
    
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// Test int64 constructor
TEST(ObjectInt64ConstructorTest_2747, Int64Value_2747) {
    long long val = 9223372036854775807LL;
    Object obj(val);
    
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectInt64ConstructorTest_2747, Int64IsIntOrInt64_2747) {
    long long val = 123456789LL;
    Object obj(val);
    
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test static factory methods
TEST(ObjectStaticFactoryTest_2747, NullObject_2747) {
    Object obj = Object::null();
    
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST(ObjectStaticFactoryTest_2747, EofObject_2747) {
    Object obj = Object::eof();
    
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST(ObjectStaticFactoryTest_2747, ErrorObject_2747) {
    Object obj = Object::error();
    
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// Test move constructor
TEST(ObjectMoveTest_2747, MoveConstructor_2747) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST(ObjectMoveTest_2747, MoveAssignment_2747) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST(ObjectMoveTest_2747, MoveStringObject_2747) {
    std::string testStr = "Move me";
    Object obj1(std::move(testStr));
    Object obj2(std::move(obj1));
    
    EXPECT_TRUE(obj2.isString());
    ASSERT_NE(obj2.getString(), nullptr);
    EXPECT_EQ(obj2.getString()->toStr(), "Move me");
}

// Test setToNull
TEST(ObjectSetToNullTest_2747, SetIntToNull_2747) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST(ObjectSetToNullTest_2747, SetStringToNull_2747) {
    std::string testStr = "will be null";
    Object obj(std::move(testStr));
    EXPECT_TRUE(obj.isString());
    
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// Test copy
TEST(ObjectCopyTest_2747, CopyIntObject_2747) {
    Object obj(42);
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST(ObjectCopyTest_2747, CopyBoolObject_2747) {
    Object obj(true);
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST(ObjectCopyTest_2747, CopyRealObject_2747) {
    Object obj(3.14);
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST(ObjectCopyTest_2747, CopyStringObject_2747) {
    std::string testStr = "copy me";
    Object obj(std::move(testStr));
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isString());
    ASSERT_NE(copied.getString(), nullptr);
    EXPECT_EQ(copied.getString()->toStr(), "copy me");
}

TEST(ObjectCopyTest_2747, CopyNullObject_2747) {
    Object obj = Object::null();
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isNull());
}

// Test getTypeName
TEST(ObjectGetTypeNameTest_2747, IntTypeName_2747) {
    Object obj(42);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST(ObjectGetTypeNameTest_2747, StringTypeName_2747) {
    std::string testStr = "test";
    Object obj(std::move(testStr));
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

TEST(ObjectGetTypeNameTest_2747, NullTypeName_2747) {
    Object obj = Object::null();
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test getNumWithDefaultValue
TEST(ObjectGetNumDefaultTest_2747, IntReturnsNum_2747) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST(ObjectGetNumDefaultTest_2747, RealReturnsNum_2747) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST(ObjectGetNumDefaultTest_2747, NonNumReturnsDefault_2747) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.9), 99.9);
}

TEST(ObjectGetNumDefaultTest_2747, StringReturnsDefault_2747) {
    std::string testStr = "not a number";
    Object obj(std::move(testStr));
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(7.0), 7.0);
}

// Test getBoolWithDefaultValue
TEST(ObjectGetBoolDefaultTest_2747, BoolReturnsValue_2747) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST(ObjectGetBoolDefaultTest_2747, NonBoolReturnsDefault_2747) {
    Object obj(42);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// Test ObjType constructor with string_view for Name type
TEST(ObjectNameConstructorTest_2747, NameFromObjType_2747) {
    Object obj(objName, "TestName");
    
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST(ObjectNameConstructorTest_2747, IsNameWithMatch_2747) {
    Object obj(objName, "TestName");
    
    EXPECT_TRUE(obj.isName("TestName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}

// Test Cmd type
TEST(ObjectCmdConstructorTest_2747, CmdFromObjType_2747) {
    Object obj(objCmd, "BT");
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST(ObjectCmdConstructorTest_2747, IsCmdWithMatch_2747) {
    Object obj(objCmd, "BT");
    
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// Test takeString
TEST(ObjectTakeStringTest_2747, TakeStringReturnsString_2747) {
    std::string testStr = "take me";
    Object obj(std::move(testStr));
    
    std::unique_ptr<GooString> taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_EQ(taken->toStr(), "take me");
}

// Test HexString via ObjType constructor
TEST(ObjectHexStringConstructorTest_2747, HexStringType_2747) {
    Object obj(objHexString, "48656C6C6F");
    
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
}

// Test getNameString
TEST(ObjectNameStringTest_2747, GetNameString_2747) {
    Object obj(objName, "SomeName");
    
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// Test unique_ptr<GooString> constructor
TEST(ObjectGooStringConstructorTest_2747, FromUniquePtr_2747) {
    auto gs = std::make_unique<GooString>("GooString test");
    Object obj(std::move(gs));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "GooString test");
}

// Test string with unicode-like content
TEST(ObjectStringConstructorTest_2747, StringWithUTF8Content_2747) {
    std::string testStr = u8"Héllo Wörld";
    Object obj(std::move(testStr));
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
}

// Test boundary: max int
TEST(ObjectIntBoundaryTest_2747, MaxInt_2747) {
    Object obj(std::numeric_limits<int>::max());
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST(ObjectIntBoundaryTest_2747, MinInt_2747) {
    Object obj(std::numeric_limits<int>::min());
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

// Test move assignment from different types
TEST(ObjectMoveAssignmentTest_2747, OverwriteIntWithString_2747) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    
    std::string testStr = "now a string";
    Object strObj(std::move(testStr));
    obj = std::move(strObj);
    
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "now a string");
}

TEST(ObjectMoveAssignmentTest_2747, OverwriteStringWithInt_2747) {
    std::string testStr = "will become int";
    Object obj(std::move(testStr));
    EXPECT_TRUE(obj.isString());
    
    Object intObj(99);
    obj = std::move(intObj);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 99);
}

// Test getNum with ok parameter
TEST(ObjectGetNumOkTest_2747, IntWithOk_2747) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST(ObjectGetNumOkTest_2747, RealWithOk_2747) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}
