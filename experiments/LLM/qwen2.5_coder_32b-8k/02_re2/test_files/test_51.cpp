#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <pybind11/pybind11.h>

#include "_re2.cc"



namespace py = pybind11;



using namespace re2_python;

using ::testing::Test;

using ::testing::Eq;



class CharLenToBytesTest_51 : public Test {

protected:

    py::bytes test_bytes;

    py::buffer_info buffer_info;



    void SetUp() override {

        // Setup a sample byte string for testing

        test_bytes = py::bytes("hello, world");

        buffer_info = test_bytes.request();

    }

};



TEST_F(CharLenToBytesTest_51, NormalOperation_51) {

    ssize_t pos = 0;

    ssize_t len = 2;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 2); // "he" in "hello, world"

}



TEST_F(CharLenToBytesTest_51, BoundaryCondition_StartOfBuffer_51) {

    ssize_t pos = 0;

    ssize_t len = 0;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 0); // No characters to move

}



TEST_F(CharLenToBytesTest_51, BoundaryCondition_EndOfBuffer_51) {

    ssize_t pos = buffer_info.size - 1;

    ssize_t len = 1;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 1); // Last character in "hello, world"

}



TEST_F(CharLenToBytesTest_51, BoundaryCondition_OutOfBounds_51) {

    ssize_t pos = buffer_info.size;

    ssize_t len = 1;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 0); // Position is out of bounds

}



TEST_F(CharLenToBytesTest_51, ExceptionalCase_NegativeLength_51) {

    ssize_t pos = 0;

    ssize_t len = -1;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 0); // Negative length should not move pointer

}



TEST_F(CharLenToBytesTest_51, ExceptionalCase_NegativePosition_51) {

    ssize_t pos = -1;

    ssize_t len = 1;

    ssize_t result = CharLenToBytes(test_bytes, pos, len);

    EXPECT_EQ(result, 0); // Negative position should not move pointer

}
