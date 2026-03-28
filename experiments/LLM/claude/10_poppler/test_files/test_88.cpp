#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::isIntOrInt64
class ObjectIsIntOrInt64Test_88 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an Object constructed with int returns true for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, IntObjectReturnsTrue_88) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that an Object constructed with long long (int64) returns true for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, Int64ObjectReturnsTrue_88) {
    Object obj(static_cast<long long>(123456789012345LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that a boolean Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, BoolObjectReturnsFalse_88) {
    Object obj(true);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a real (double) Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, RealObjectReturnsFalse_88) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a string Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, StringObjectReturnsFalse_88) {
    Object obj(std::string("hello"));
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a null Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, NullObjectReturnsFalse_88) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that an error Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, ErrorObjectReturnsFalse_88) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that an EOF Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, EOFObjectReturnsFalse_88) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a default-constructed (none) Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, NoneObjectReturnsFalse_88) {
    Object obj;
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a name Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, NameObjectReturnsFalse_88) {
    Object obj(objName, "someName");
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that a cmd Object returns false for isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, CmdObjectReturnsFalse_88) {
    Object obj(objCmd, "someCmd");
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test consistency: isInt and isInt64 individual checks agree with isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, IntObjectIsIntTrueIsInt64False_88) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectIsIntOrInt64Test_88, Int64ObjectIsIntFalseIsInt64True_88) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_FALSE(obj.isInt());
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Boundary: int with value 0
TEST_F(ObjectIsIntOrInt64Test_88, IntZeroReturnsTrue_88) {
    Object obj(0);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Boundary: int with negative value
TEST_F(ObjectIsIntOrInt64Test_88, IntNegativeReturnsTrue_88) {
    Object obj(-1);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Boundary: int64 with value 0
TEST_F(ObjectIsIntOrInt64Test_88, Int64ZeroReturnsTrue_88) {
    Object obj(static_cast<long long>(0LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Boundary: int64 with negative value
TEST_F(ObjectIsIntOrInt64Test_88, Int64NegativeReturnsTrue_88) {
    Object obj(static_cast<long long>(-9876543210LL));
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that a real Object with integer-like value still returns false
TEST_F(ObjectIsIntOrInt64Test_88, RealIntegerValueReturnsFalse_88) {
    Object obj(42.0);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that after move, the moved-from object is not int or int64 (it becomes some default/dead state)
TEST_F(ObjectIsIntOrInt64Test_88, MovedFromIntObjectBehavior_88) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    Object obj2(std::move(obj));
    EXPECT_TRUE(obj2.isIntOrInt64());
}

// Test that after setToNull, an int object is no longer isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, SetToNullClearsIntOrInt64_88) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    obj.setToNull();
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test getIntOrInt64 returns correct value for int object
TEST_F(ObjectIsIntOrInt64Test_88, GetIntOrInt64ForIntObject_88) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// Test getIntOrInt64 returns correct value for int64 object
TEST_F(ObjectIsIntOrInt64Test_88, GetIntOrInt64ForInt64Object_88) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 9876543210LL);
}

// Test move assignment preserves isIntOrInt64
TEST_F(ObjectIsIntOrInt64Test_88, MoveAssignmentPreservesIntOrInt64_88) {
    Object obj(100);
    Object obj2;
    obj2 = std::move(obj);
    EXPECT_TRUE(obj2.isIntOrInt64());
}

// Test that getType returns objInt for int and objInt64 for int64
TEST_F(ObjectIsIntOrInt64Test_88, GetTypeForIntObject_88) {
    Object obj(42);
    EXPECT_EQ(obj.getType(), objInt);
}

TEST_F(ObjectIsIntOrInt64Test_88, GetTypeForInt64Object_88) {
    Object obj(static_cast<long long>(9876543210LL));
    EXPECT_EQ(obj.getType(), objInt64);
}

// Verify that a hexString object returns false
TEST_F(ObjectIsIntOrInt64Test_88, HexStringObjectReturnsFalse_88) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_FALSE(obj.isIntOrInt64());
}
