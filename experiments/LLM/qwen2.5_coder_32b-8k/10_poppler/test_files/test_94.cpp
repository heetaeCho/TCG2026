#include <gtest/gtest.h>

#include "Object.h"



// Test fixture for Object class tests

class ObjectTest_94 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



// Test normal operation of getNum with integer type

TEST_F(ObjectTest_94, GetNum_IntegerType_94) {

    Object obj(123);

    EXPECT_EQ(obj.getNum(), 123.0);

}



// Test normal operation of getNum with int64_t type

TEST_F(ObjectTest_94, GetNum_Int64Type_94) {

    Object obj(static_cast<long long>(1234567890123));

    EXPECT_EQ(obj.getNum(), 1234567890123.0);

}



// Test normal operation of getNum with real (double) type

TEST_F(ObjectTest_94, GetNum_RealType_94) {

    Object obj(123.456);

    EXPECT_DOUBLE_EQ(obj.getNum(), 123.456);

}



// Test boundary condition of getNum with zero integer value

TEST_F(ObjectTest_94, GetNum_ZeroIntegerValue_94) {

    Object obj(0);

    EXPECT_EQ(obj.getNum(), 0.0);

}



// Test boundary condition of getNum with zero int64_t value

TEST_F(ObjectTest_94, GetNum_ZeroInt64Value_94) {

    Object obj(static_cast<long long>(0));

    EXPECT_EQ(obj.getNum(), 0.0);

}



// Test boundary condition of getNum with zero real (double) value

TEST_F(ObjectTest_94, GetNum_ZeroRealValue_94) {

    Object obj(0.0);

    EXPECT_DOUBLE_EQ(obj.getNum(), 0.0);

}



// Test exceptional case of getNum when type is not a number

TEST_F(ObjectTest_94, GetNum_NonNumberType_94) {

    Object obj("not_a_number");

    EXPECT_THROW(obj.getNum(), std::exception); // Assuming this will throw an exception if type is not a number

}



// Test exceptional case of getNum when type is error

TEST_F(ObjectTest_94, GetNum_ErrorType_94) {

    Object obj = Object::error();

    EXPECT_THROW(obj.getNum(), std::exception); // Assuming this will throw an exception if type is error

}
