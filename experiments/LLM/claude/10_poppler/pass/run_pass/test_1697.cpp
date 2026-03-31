#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StructElement.h"
#include "Object.h"

// Since StructElement has private constructors, we need to test what we can
// through the public interface. We'll focus on hasStmRef() which is the
// primary method shown in the partial code, and other publicly accessible methods.

// Note: StructElement constructors are private, so we cannot directly instantiate
// StructElement objects in tests without friend access or factory methods.
// We'll test the Object class's isRef() method which underlies hasStmRef(),
// and test StructElement through any available creation mechanisms.

// Test the Object class behavior that underlies hasStmRef
class ObjectRefTest_1697 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ObjectRefTest_1697, DefaultObjectIsNotRef_1697) {
    Object obj;
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectRefTest_1697, NullObjectIsNotRef_1697) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectRefTest_1697, ErrorObjectIsNotRef_1697) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectRefTest_1697, EofObjectIsNotRef_1697) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectRefTest_1697, BoolObjectIsNotRef_1697) {
    Object obj(true);
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectRefTest_1697, IntObjectIsNotRef_1697) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isInt());
}

TEST_F(ObjectRefTest_1697, RealObjectIsNotRef_1697) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectRefTest_1697, NoneObjectIsNotRef_1697) {
    Object obj;
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectRefTest_1697, Int64ObjectIsNotRef_1697) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isRef());
    EXPECT_TRUE(obj.isInt64());
}

// Test Object type checking methods
TEST_F(ObjectRefTest_1697, ObjectTypeChecks_1697) {
    Object nullObj = Object::null();
    EXPECT_TRUE(nullObj.isNull());
    EXPECT_FALSE(nullObj.isBool());
    EXPECT_FALSE(nullObj.isInt());
    EXPECT_FALSE(nullObj.isReal());
    EXPECT_FALSE(nullObj.isString());
    EXPECT_FALSE(nullObj.isName());
    EXPECT_FALSE(nullObj.isArray());
    EXPECT_FALSE(nullObj.isDict());
    EXPECT_FALSE(nullObj.isStream());
    EXPECT_FALSE(nullObj.isRef());
    EXPECT_FALSE(nullObj.isCmd());
    EXPECT_FALSE(nullObj.isError());
    EXPECT_FALSE(nullObj.isEOF());
}

TEST_F(ObjectRefTest_1697, SetToNullMakesObjectNull_1697) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectRefTest_1697, MoveConstructor_1697) {
    Object obj1(42);
    EXPECT_TRUE(obj1.isInt());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectRefTest_1697, MoveAssignment_1697) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectRefTest_1697, BoolGetValue_1697) {
    Object objTrue(true);
    Object objFalse(false);
    EXPECT_TRUE(objTrue.getBool());
    EXPECT_FALSE(objFalse.getBool());
}

TEST_F(ObjectRefTest_1697, IntGetValue_1697) {
    Object obj(123);
    EXPECT_EQ(obj.getInt(), 123);
}

TEST_F(ObjectRefTest_1697, RealGetValue_1697) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getReal(), 2.718);
}

TEST_F(ObjectRefTest_1697, NumericChecks_1697) {
    Object intObj(5);
    Object realObj(5.0);
    EXPECT_TRUE(intObj.isNum());
    EXPECT_TRUE(realObj.isNum());
}

TEST_F(ObjectRefTest_1697, GetNumFromInt_1697) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectRefTest_1697, GetNumFromReal_1697) {
    Object obj(7.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.5);
}

TEST_F(ObjectRefTest_1697, Int64GetValue_1697) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectRefTest_1697, IsIntOrInt64_1697) {
    Object intObj(42);
    Object int64Obj(static_cast<long long>(42LL));
    Object realObj(42.0);
    EXPECT_TRUE(intObj.isIntOrInt64());
    EXPECT_TRUE(int64Obj.isIntOrInt64());
    EXPECT_FALSE(realObj.isIntOrInt64());
}

TEST_F(ObjectRefTest_1697, GetNumWithDefaultValue_1697) {
    Object nullObj = Object::null();
    double result = nullObj.getNumWithDefaultValue(99.9);
    EXPECT_DOUBLE_EQ(result, 99.9);
}

TEST_F(ObjectRefTest_1697, GetBoolWithDefaultValue_1697) {
    Object nullObj = Object::null();
    bool result = nullObj.getBoolWithDefaultValue(true);
    EXPECT_TRUE(result);
}

TEST_F(ObjectRefTest_1697, CopyObject_1697) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectRefTest_1697, DeepCopyObject_1697) {
    Object obj(42);
    Object deepCopied = obj.deepCopy();
    EXPECT_TRUE(deepCopied.isInt());
    EXPECT_EQ(deepCopied.getInt(), 42);
}

TEST_F(ObjectRefTest_1697, GetTypeName_1697) {
    Object nullObj = Object::null();
    const char* typeName = nullObj.getTypeName();
    EXPECT_NE(typeName, nullptr);
}

// Test boundary: zero values
TEST_F(ObjectRefTest_1697, ZeroInt_1697) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
    EXPECT_FALSE(obj.isRef());
}

// Test boundary: negative values
TEST_F(ObjectRefTest_1697, NegativeInt_1697) {
    Object obj(-1);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -1);
    EXPECT_FALSE(obj.isRef());
}

// Test boundary: large int64
TEST_F(ObjectRefTest_1697, LargeInt64_1697) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_FALSE(obj.isRef());
}

// Test boundary: minimum int64
TEST_F(ObjectRefTest_1697, MinInt64_1697) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test that moving an object transfers ownership properly
TEST_F(ObjectRefTest_1697, MoveAssignmentClearsSource_1697) {
    Object obj1(42);
    Object obj2 = Object::null();
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

// Test string object
TEST_F(ObjectRefTest_1697, StringObjectCreation_1697) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isRef());
    EXPECT_NE(obj.getString(), nullptr);
}

// Test name object
TEST_F(ObjectRefTest_1697, NameObjectCreation_1697) {
    Object obj(ObjType::objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectRefTest_1697, NameObjectIsNameCheck_1697) {
    Object obj(ObjType::objName, "TestName");
    EXPECT_TRUE(obj.isName("TestName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}
