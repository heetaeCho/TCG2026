#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



// Test normal operation: Create an Object with a double value and check its type and value.

TEST_F(ObjectTest_2745, CreateWithDouble_CheckTypeAndValue_2745) {

    Object obj(3.14);

    EXPECT_EQ(obj.getType(), objReal);

    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);

}



// Test boundary condition: Create an Object with the smallest possible double value.

TEST_F(ObjectTest_2745, CreateWithSmallestDouble_CheckValue_2745) {

    Object obj(std::numeric_limits<double>::lowest());

    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::lowest());

}



// Test boundary condition: Create an Object with the largest possible double value.

TEST_F(ObjectTest_2745, CreateWithLargestDouble_CheckValue_2745) {

    Object obj(std::numeric_limits<double>::max());

    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());

}



// Test boundary condition: Create an Object with a double value of zero.

TEST_F(ObjectTest_2745, CreateWithZeroDouble_CheckValue_2745) {

    Object obj(0.0);

    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);

}



// Test exceptional case: Check behavior when trying to get an integer from a double Object (should not be possible).

TEST_F(ObjectTest_2745, CreateWithDouble_GetInt_ShouldFail_2745) {

    Object obj(3.14);

    EXPECT_THROW(obj.getInt(), std::runtime_error); // Assuming this is the expected behavior

}



// Test exceptional case: Check behavior when trying to get a boolean from a double Object (should not be possible).

TEST_F(ObjectTest_2745, CreateWithDouble_GetBool_ShouldFail_2745) {

    Object obj(3.14);

    EXPECT_THROW(obj.getBool(), std::runtime_error); // Assuming this is the expected behavior

}



// Test exceptional case: Check behavior when trying to get a string from a double Object (should not be possible).

TEST_F(ObjectTest_2745, CreateWithDouble_GetString_ShouldFail_2745) {

    Object obj(3.14);

    EXPECT_THROW(obj.getString(), std::runtime_error); // Assuming this is the expected behavior

}



// Test static method: Check if null() returns an object of type objNone.

TEST_F(ObjectTest_2745, StaticNull_ReturnsTypeObjNone_2745) {

    Object obj = Object::null();

    EXPECT_EQ(obj.getType(), objNone);

}



// Test static method: Check if eof() returns an object of type objEOF.

TEST_F(ObjectTest_2745, StaticEof_ReturnsTypeObjEof_2745) {

    Object obj = Object::eof();

    EXPECT_EQ(obj.getType(), objEOF);

}



// Test static method: Check if error() returns an object of type objError.

TEST_F(ObjectTest_2745, StaticError_ReturnsTypeObjError_2745) {

    Object obj = Object::error();

    EXPECT_EQ(obj.getType(), objError);

}
