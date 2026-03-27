#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <pybind11/buffer_info.h>

#include "_re2.cc"



namespace py = pybind11;

using namespace re2_python;



class SetTest_61 : public ::testing::Test {

protected:

    RE2::Options options_;

    Set set_;



    SetTest_61() : set_(RE2::UNANCHORED, options_) {}



    py::buffer_info CreateBufferInfo(const std::string& data) {

        return py::bytes(data).request();

    }

};



TEST_F(SetTest_61, AddReturnsValidIndex_61) {

    py::buffer_info buffer = CreateBufferInfo("test_pattern");

    int index = set_.Add(py::buffer(buffer));

    EXPECT_GE(index, 0);

}



TEST_F(SetTest_61, AddMultiplePatterns_61) {

    py::buffer_info buffer1 = CreateBufferInfo("pattern1");

    py::buffer_info buffer2 = CreateBufferInfo("pattern2");



    int index1 = set_.Add(py::buffer(buffer1));

    int index2 = set_.Add(py::buffer(buffer2));



    EXPECT_GE(index1, 0);

    EXPECT_GE(index2, 0);

    EXPECT_NE(index1, index2);

}



TEST_F(SetTest_61, AddInvalidBuffer_61) {

    py::buffer_info invalid_buffer = CreateBufferInfo("");

    int index = set_.Add(py::buffer(invalid_buffer));

    EXPECT_EQ(index, -1);

}



TEST_F(SetTest_61, CompileAfterAdd_61) {

    py::buffer_info buffer = CreateBufferInfo("test_pattern");

    set_.Add(py::buffer(buffer));



    bool result = set_.Compile();

    EXPECT_TRUE(result);

}



TEST_F(SetTest_61, MatchWithoutCompile_61) {

    py::buffer_info buffer = CreateBufferInfo("test_pattern");

    set_.Add(py::buffer(buffer));



    py::buffer_info match_buffer = CreateBufferInfo("test_string");

    std::vector<int> matches = set_.Match(py::buffer(match_buffer));



    EXPECT_TRUE(matches.empty());

}



TEST_F(SetTest_61, MatchAfterCompile_61) {

    py::buffer_info buffer = CreateBufferInfo("test_pattern");

    set_.Add(py::buffer(buffer));

    set_.Compile();



    py::buffer_info match_buffer = CreateBufferInfo("test_string");

    std::vector<int> matches = set_.Match(py::buffer(match_buffer));



    EXPECT_EQ(matches.size(), 0); // Assuming no match

}



TEST_F(SetTest_61, MatchWithMultiplePatterns_61) {

    py::buffer_info buffer1 = CreateBufferInfo("pattern1");

    py::buffer_info buffer2 = CreateBufferInfo("pattern2");



    set_.Add(py::buffer(buffer1));

    set_.Add(py::buffer(buffer2));

    set_.Compile();



    py::buffer_info match_buffer = CreateBufferInfo("string_with_pattern1_and_pattern2");

    std::vector<int> matches = set_.Match(py::buffer(match_buffer));



    EXPECT_EQ(matches.size(), 2);

}



TEST_F(SetTest_61, MatchWithNoPatterns_61) {

    py::buffer_info match_buffer = CreateBufferInfo("test_string");

    std::vector<int> matches = set_.Match(py::buffer(match_buffer));



    EXPECT_TRUE(matches.empty());

}
