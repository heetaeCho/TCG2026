#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::isNum tests
class ObjectIsNumTest_74 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an Object constructed with int is considered a number
TEST_F(ObjectIsNumTest_74, IntObjectIsNum_74) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

// Test that an Object constructed with double (real) is considered a number
TEST_F(ObjectIsNumTest_74, RealObjectIsNum_74) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

// Test that an Object constructed with long long (int64) is considered a number
TEST_F(ObjectIsNumTest_74, Int64ObjectIsNum_74) {
    Object obj(static_cast<long long>(1234567890123LL));
    EXPECT_TRUE(obj.isNum());
}

// Test that a bool Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, BoolObjectIsNotNum_74) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

// Test that a string Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, StringObjectIsNotNum_74) {
    Object obj(std::string("hello"));
    EXPECT_FALSE(obj.isNum());
}

// Test that a name Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, NameObjectIsNotNum_74) {
    Object obj(objName, "someName");
    EXPECT_FALSE(obj.isNum());
}

// Test that a null Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, NullObjectIsNotNum_74) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

// Test that an error Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, ErrorObjectIsNotNum_74) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isNum());
}

// Test that an EOF Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, EOFObjectIsNotNum_74) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isNum());
}

// Test that a default-constructed (none) Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, NoneObjectIsNotNum_74) {
    Object obj;
    EXPECT_FALSE(obj.isNum());
}

// Test that a cmd Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, CmdObjectIsNotNum_74) {
    Object obj(objCmd, "someCmd");
    EXPECT_FALSE(obj.isNum());
}

// Test that int Object with value 0 is still a number
TEST_F(ObjectIsNumTest_74, IntZeroIsNum_74) {
    Object obj(0);
    EXPECT_TRUE(obj.isNum());
}

// Test that int Object with negative value is a number
TEST_F(ObjectIsNumTest_74, NegativeIntIsNum_74) {
    Object obj(-100);
    EXPECT_TRUE(obj.isNum());
}

// Test that real Object with value 0.0 is a number
TEST_F(ObjectIsNumTest_74, RealZeroIsNum_74) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isNum());
}

// Test that real Object with negative value is a number
TEST_F(ObjectIsNumTest_74, NegativeRealIsNum_74) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isNum());
}

// Test that int64 Object with value 0 is a number
TEST_F(ObjectIsNumTest_74, Int64ZeroIsNum_74) {
    Object obj(static_cast<long long>(0));
    EXPECT_TRUE(obj.isNum());
}

// Test that int64 Object with negative value is a number
TEST_F(ObjectIsNumTest_74, NegativeInt64IsNum_74) {
    Object obj(static_cast<long long>(-999999999999LL));
    EXPECT_TRUE(obj.isNum());
}

// Test consistency: isNum should agree with isInt for int objects
TEST_F(ObjectIsNumTest_74, IntObjectIsIntAndNum_74) {
    Object obj(7);
    EXPECT_TRUE(obj.isInt());
    EXPECT_TRUE(obj.isNum());
}

// Test consistency: isNum should agree with isReal for real objects
TEST_F(ObjectIsNumTest_74, RealObjectIsRealAndNum_74) {
    Object obj(1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
}

// Test consistency: isNum should agree with isInt64 for int64 objects
TEST_F(ObjectIsNumTest_74, Int64ObjectIsInt64AndNum_74) {
    Object obj(static_cast<long long>(42));
    EXPECT_TRUE(obj.isInt64());
    EXPECT_TRUE(obj.isNum());
}

// Test that getNum returns the correct value for int objects
TEST_F(ObjectIsNumTest_74, GetNumForInt_74) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

// Test that getNum returns the correct value for real objects
TEST_F(ObjectIsNumTest_74, GetNumForReal_74) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// Test that getNum returns the correct value for int64 objects
TEST_F(ObjectIsNumTest_74, GetNumForInt64_74) {
    Object obj(static_cast<long long>(100));
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 100.0);
}

// Test hex string Object is NOT considered a number
TEST_F(ObjectIsNumTest_74, HexStringObjectIsNotNum_74) {
    Object obj(objHexString, "DEADBEEF");
    EXPECT_FALSE(obj.isNum());
}

// Test that after setToNull, object is no longer a number
TEST_F(ObjectIsNumTest_74, SetToNullMakesNotNum_74) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    obj.setToNull();
    EXPECT_FALSE(obj.isNum());
}

// Test that moved-from int object: the new object is a number
TEST_F(ObjectIsNumTest_74, MovedIntObjectIsNum_74) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isNum());
}

// Test that moved-from real object: the new object is a number
TEST_F(ObjectIsNumTest_74, MovedRealObjectIsNum_74) {
    Object obj1(2.5);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isNum());
}

// Test getType for int object
TEST_F(ObjectIsNumTest_74, IntObjectTypeIsObjInt_74) {
    Object obj(10);
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_TRUE(obj.isNum());
}

// Test getType for real object
TEST_F(ObjectIsNumTest_74, RealObjectTypeIsObjReal_74) {
    Object obj(1.0);
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isNum());
}

// Test getType for int64 object
TEST_F(ObjectIsNumTest_74, Int64ObjectTypeIsObjInt64_74) {
    Object obj(static_cast<long long>(1));
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: INT_MAX
TEST_F(ObjectIsNumTest_74, IntMaxIsNum_74) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: INT_MIN
TEST_F(ObjectIsNumTest_74, IntMinIsNum_74) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: very large double
TEST_F(ObjectIsNumTest_74, LargeDoubleIsNum_74) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: very small (near zero) positive double
TEST_F(ObjectIsNumTest_74, SmallPositiveDoubleIsNum_74) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: LLONG_MAX for int64
TEST_F(ObjectIsNumTest_74, Int64MaxIsNum_74) {
    Object obj(std::numeric_limits<long long>::max());
    EXPECT_TRUE(obj.isNum());
}

// Test boundary: LLONG_MIN for int64
TEST_F(ObjectIsNumTest_74, Int64MinIsNum_74) {
    Object obj(std::numeric_limits<long long>::min());
    EXPECT_TRUE(obj.isNum());
}
