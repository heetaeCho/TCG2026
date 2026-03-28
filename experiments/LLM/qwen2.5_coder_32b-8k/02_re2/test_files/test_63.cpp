#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pybind11/buffer_info.h"

#include "re2/re2.h"

#include "_re2.cc"



namespace py = pybind11;

using namespace re2_python;



class FilterTest : public ::testing::Test {

protected:

    Filter filter_;

    RE2::Options options_;

};



TEST_F(FilterTest_63, AddReturnsValidIndex_63) {

    py::buffer buffer("test_pattern");

    int index = filter_.Add(buffer, options_);

    EXPECT_GE(index, 0);

}



TEST_F(FilterTest_63, AddMultiplePatterns_63) {

    py::buffer buffer1("pattern1");

    py::buffer buffer2("pattern2");



    int index1 = filter_.Add(buffer1, options_);

    int index2 = filter_.Add(buffer2, options_);



    EXPECT_GE(index1, 0);

    EXPECT_GE(index2, 0);

    EXPECT_NE(index1, index2);

}



TEST_F(FilterTest_63, CompileReturnsTrueOnSuccess_63) {

    py::buffer buffer("test_pattern");

    filter_.Add(buffer, options_);

    EXPECT_TRUE(filter_.Compile());

}



TEST_F(FilterTest_63, MatchFindsPattern_63) {

    py::buffer pattern_buffer("test_pattern");

    int index = filter_.Add(pattern_buffer, options_);

    filter_.Compile();



    py::buffer match_buffer("this is a test_pattern in the string");

    std::vector<int> matches = filter_.Match(match_buffer, false);



    EXPECT_EQ(matches.size(), 1);

    EXPECT_EQ(matches[0], index);

}



TEST_F(FilterTest_63, MatchNoPatternFound_63) {

    py::buffer pattern_buffer("test_pattern");

    filter_.Add(pattern_buffer, options_);

    filter_.Compile();



    py::buffer match_buffer("no matching pattern here");

    std::vector<int> matches = filter_.Match(match_buffer, false);



    EXPECT_TRUE(matches.empty());

}



TEST_F(FilterTest_63, GetRE2ReturnsCorrectPattern_63) {

    py::buffer buffer("test_pattern");

    int index = filter_.Add(buffer, options_);

    filter_.Compile();



    const RE2& re2_pattern = filter_.GetRE2(index);

    EXPECT_EQ(re2_pattern.pattern(), "test_pattern");

}



TEST_F(FilterTest_63, AddWithEmptyBuffer_ReturnsNegativeIndex_63) {

    py::buffer buffer("");

    int index = filter_.Add(buffer, options_);

    EXPECT_LT(index, 0);

}
