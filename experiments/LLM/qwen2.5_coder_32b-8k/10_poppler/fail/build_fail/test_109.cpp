#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_109 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



// Test normal operation with int

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsIntValue_109) {

    Object obj(123);

    EXPECT_EQ(obj.getIntOrInt64(), 123);

}



// Test normal operation with long long

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsLongLongValue_109) {

    Object obj(static_cast<long long>(123456789012));

    EXPECT_EQ(obj.getIntOrInt64(), 123456789012);

}



// Test boundary condition with int min

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsIntMinValue_109) {

    Object obj(std::numeric_limits<int>::min());

    EXPECT_EQ(obj.getIntOrInt64(), std::numeric_limits<int>::min());

}



// Test boundary condition with long long min

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsLongLongMinValue_109) {

    Object obj(std::numeric_limits<long long>::min());

    EXPECT_EQ(obj.getIntOrInt64(), std::numeric_limits<long long>::min());

}



// Test boundary condition with int max

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsIntMaxValue_109) {

    Object obj(std::numeric_limits<int>::max());

    EXPECT_EQ(obj.getIntOrInt64(), std::numeric_limits<int>::max());

}



// Test boundary condition with long long max

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsLongLongMaxValue_109) {

    Object obj(std::numeric_limits<long long>::max());

    EXPECT_EQ(obj.getIntOrInt64(), std::numeric_limits<long long>::max());

}



// Test exceptional case with non-integer type

TEST_F(ObjectTest_109, GetIntOrInt64_ReturnsZeroForNonIntegerType_109) {

    Object obj("string");

    EXPECT_EQ(obj.getIntOrInt64(), 0);

}
