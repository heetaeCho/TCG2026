#include <gtest/gtest.h>
#include "Object.h"

// Test that getInt64() returns the correct value for an Object constructed with a long long
TEST(ObjectGetInt64Test_108, ReturnsCorrectPositiveValue_108) {
    long long val = 1234567890123LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectGetInt64Test_108, ReturnsCorrectNegativeValue_108) {
    long long val = -9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectGetInt64Test_108, ReturnsZero_108) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectGetInt64Test_108, ReturnsMaxLongLong_108) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectGetInt64Test_108, ReturnsMinLongLong_108) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST(ObjectGetInt64Test_108, TypeIsInt64_108) {
    Object obj(42LL);
    EXPECT_EQ(obj.getType(), objInt64);
}

TEST(ObjectGetInt64Test_108, IsInt64ReturnsTrue_108) {
    Object obj(100LL);
    EXPECT_TRUE(obj.isInt64());
}

TEST(ObjectGetInt64Test_108, IsIntOrInt64ReturnsTrue_108) {
    Object obj(100LL);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that an int Object is not int64
TEST(ObjectGetInt64Test_108, IntObjectIsNotInt64_108) {
    Object obj(42);
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isInt());
}

// Test getIntOrInt64 for int64 object
TEST(ObjectGetInt64Test_108, GetIntOrInt64ReturnsCorrectValueForInt64_108) {
    long long val = 5000000000LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// Test getIntOrInt64 for int object
TEST(ObjectGetInt64Test_108, GetIntOrInt64ReturnsCorrectValueForInt_108) {
    int val = 42;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), static_cast<long long>(val));
}

// Test move construction preserves int64 value
TEST(ObjectGetInt64Test_108, MoveConstructorPreservesInt64_108) {
    long long val = 999999999999LL;
    Object obj1(val);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), val);
}

// Test move assignment preserves int64 value
TEST(ObjectGetInt64Test_108, MoveAssignmentPreservesInt64_108) {
    long long val = 888888888888LL;
    Object obj1(val);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), val);
}

// Test copy() preserves int64 value
TEST(ObjectGetInt64Test_108, CopyPreservesInt64_108) {
    long long val = 777777777777LL;
    Object obj1(val);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isInt64());
    EXPECT_EQ(obj2.getInt64(), val);
}

// Test that bool object is not int64
TEST(ObjectGetInt64Test_108, BoolObjectIsNotInt64_108) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isBool());
}

// Test that real object is not int64
TEST(ObjectGetInt64Test_108, RealObjectIsNotInt64_108) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isReal());
}

// Test that null object is not int64
TEST(ObjectGetInt64Test_108, NullObjectIsNotInt64_108) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isNull());
}

// Test that default constructed object is not int64
TEST(ObjectGetInt64Test_108, DefaultObjectIsNotInt64_108) {
    Object obj;
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isNone());
}

// Test value just beyond int range stored as int64
TEST(ObjectGetInt64Test_108, ValueBeyondIntRange_108) {
    long long val = static_cast<long long>(std::numeric_limits<int>::max()) + 1;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test negative value just beyond int range stored as int64
TEST(ObjectGetInt64Test_108, NegativeValueBeyondIntRange_108) {
    long long val = static_cast<long long>(std::numeric_limits<int>::min()) - 1;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

// Test getTypeName for int64 object
TEST(ObjectGetInt64Test_108, GetTypeNameForInt64_108) {
    Object obj(42LL);
    const char* name = obj.getTypeName();
    EXPECT_NE(name, nullptr);
}

// Test isNum returns true for int64
TEST(ObjectGetInt64Test_108, IsNumReturnsTrueForInt64_108) {
    Object obj(42LL);
    EXPECT_TRUE(obj.isNum());
}

// Test getNum returns correct value for int64
TEST(ObjectGetInt64Test_108, GetNumReturnsCorrectValueForInt64_108) {
    long long val = 12345LL;
    Object obj(val);
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(val));
}
