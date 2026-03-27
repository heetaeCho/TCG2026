#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <pybind11/buffer_info.h>

#include <pybind11/pybuffer.h>

#include "_re2.cc"  // Adjust the include path as necessary



namespace py = pybind11;

using namespace re2_python;



class BytesToCharLenTest_52 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(BytesToCharLenTest_52, NormalOperation_SingleByteChars_52) {

    py::bytes buffer("abc");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, 0, info.size);

    EXPECT_EQ(result, 3);

}



TEST_F(BytesToCharLenTest_52, NormalOperation_MultiByteChars_52) {

    py::bytes buffer("😊😉");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, 0, info.size);

    EXPECT_EQ(result, 2); // Each emoji is a single character

}



TEST_F(BytesToCharLenTest_52, BoundaryCondition_EmptyBuffer_52) {

    py::bytes buffer("");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, 0, info.size);

    EXPECT_EQ(result, 0);

}



TEST_F(BytesToCharLenTest_52, BoundaryCondition_StartAtEnd_52) {

    py::bytes buffer("hello");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, info.size, info.size);

    EXPECT_EQ(result, 0);

}



TEST_F(BytesToCharLenTest_52, BoundaryCondition_OutOfBoundsEndPos_52) {

    py::bytes buffer("hello");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, 0, info.size + 1);

    EXPECT_EQ(result, 5); // Should handle gracefully and count up to the end

}



TEST_F(BytesToCharLenTest_52, BoundaryCondition_StartPastEndPos_52) {

    py::bytes buffer("hello");

    py::buffer_info info = buffer.request();

    ssize_t result = BytesToCharLen(buffer, 10, info.size);

    EXPECT_EQ(result, 0); // No characters to count

}



TEST_F(BytesToCharLenTest_52, ExceptionalCase_NullBufferPtr_52) {

    py::buffer_info fake_buffer(nullptr, 0, PyBUF_SIMPLE, 1, {0}, {0});

    ssize_t result = BytesToCharLen(py::buffer(fake_buffer), 0, 0);

    EXPECT_EQ(result, 0); // Should handle gracefully

}
