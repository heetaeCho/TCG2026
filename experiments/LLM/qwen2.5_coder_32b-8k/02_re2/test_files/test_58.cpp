#include <gtest/gtest.h>

#include "re2/re2.h"

#include "_re2.cc"



using namespace re2_python;

using namespace re2;



// Test fixture for RE2PossibleMatchRangeShim tests.

class RE2PossibleMatchRangeShimTest_58 : public ::testing::Test {

protected:

    void SetUp() override {

        pattern = "a.*";

        re2.reset(new RE2(pattern));

    }



    std::string pattern;

    std::unique_ptr<RE2> re2;

};



// Test normal operation with a valid regex and maxlen.

TEST_F(RE2PossibleMatchRangeShimTest_58, NormalOperation_58) {

    auto result = RE2PossibleMatchRangeShim(*re2, 10);

    EXPECT_TRUE(std::get<0>(result));

    EXPECT_EQ("a", std::string(py::bytes(std::get<1>(result))));

    EXPECT_EQ("a~~~~~~~~~", std::string(py::bytes(std::get<2>(result))));

}



// Test boundary condition with maxlen = 0.

TEST_F(RE2PossibleMatchRangeShimTest_58, MaxLenZero_58) {

    auto result = RE2PossibleMatchRangeShim(*re2, 0);

    EXPECT_TRUE(std::get<0>(result));

    EXPECT_EQ("a", std::string(py::bytes(std::get<1>(result))));

    EXPECT_EQ("", std::string(py::bytes(std::get<2>(result))));

}



// Test boundary condition with maxlen = 1.

TEST_F(RE2PossibleMatchRangeShimTest_58, MaxLenOne_58) {

    auto result = RE2PossibleMatchRangeShim(*re2, 1);

    EXPECT_TRUE(std::get<0>(result));

    EXPECT_EQ("a", std::string(py::bytes(std::get<1>(result))));

    EXPECT_EQ("a", std::string(py::bytes(std::get<2>(result))));

}



// Test with a pattern that does not match anything.

TEST_F(RE2PossibleMatchRangeShimTest_58, NoMatchPattern_58) {

    RE2 no_match_re2("b");

    auto result = RE2PossibleMatchRangeShim(no_match_re2, 10);

    EXPECT_FALSE(std::get<0>(result));

    EXPECT_EQ("", std::string(py::bytes(std::get<1>(result))));

    EXPECT_EQ("", std::string(py::bytes(std::get<2>(result))));

}



// Test with an invalid regex pattern.

TEST_F(RE2PossibleMatchRangeShimTest_58, InvalidPattern_58) {

    RE2 invalid_re2("a(*");

    auto result = RE2PossibleMatchRangeShim(invalid_re2, 10);

    EXPECT_FALSE(std::get<0>(result));

    EXPECT_EQ("", std::string(py::bytes(std::get<1>(result))));

    EXPECT_EQ("", std::string(py::bytes(std::get<2>(result))));

}
