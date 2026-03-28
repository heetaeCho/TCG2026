#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/xmpsidecar.cpp" // Include the header or source file where matchi is defined



namespace {



class MatchITest : public ::testing::Test {

protected:

    // No additional setup needed for this test

};



TEST_F(MatchITest_1717, ExactMatch_1717) {

    EXPECT_TRUE(Exiv2::matchi("example", "example"));

}



TEST_F(MatchITest_1717, CaseInsensitiveMatch_1717) {

    EXPECT_TRUE(Exiv2::matchi("Example", "example"));

    EXPECT_TRUE(Exiv2::matchi("EXAMPLE", "example"));

}



TEST_F(MatchITest_1717, PartialMatch_1717) {

    EXPECT_TRUE(Exiv2::matchi("this is an example", "example"));

    EXPECT_TRUE(Exiv2::matchi("This Is An Example", "example"));

}



TEST_F(MatchITest_1717, NoMatch_1717) {

    EXPECT_FALSE(Exiv2::matchi("no match here", "example"));

}



TEST_F(MatchITest_1717, EmptyKey_1717) {

    EXPECT_FALSE(Exiv2::matchi("", "example"));

}



TEST_F(MatchITest_1717, EmptySubstring_1717) {

    EXPECT_TRUE(Exiv2::matchi("example", ""));

}



TEST_F(MatchITest_1717, SpecialCharactersMatch_1717) {

    EXPECT_TRUE(Exiv2::matchi("!@#example$%^", "example"));

    EXPECT_TRUE(Exiv2::matchi("!@#Example$%^", "example"));

}



} // namespace
