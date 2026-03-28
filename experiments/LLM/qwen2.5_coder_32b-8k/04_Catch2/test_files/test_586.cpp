#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



namespace Catch {

    bool endsWith(std::string const& s, std::string const& suffix);

}



// Test fixture for the endsWith function

class EndsWithTest_586 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(EndsWithTest_586, NormalOperation_MatchesSuffix_586) {

    EXPECT_TRUE(Catch::endsWith("hello world", "world"));

}



TEST_F(EndsWithTest_586, NormalOperation_DoesNotMatchSuffix_586) {

    EXPECT_FALSE(Catch::endsWith("hello world", "hello"));

}



TEST_F(EndsWithTest_586, BoundaryCondition_EmptyStringAndSuffix_586) {

    EXPECT_TRUE(Catch::endsWith("", ""));

}



TEST_F(EndsWithTest_586, BoundaryCondition_NonEmptyStringEmptySuffix_586) {

    EXPECT_TRUE(Catch::endsWith("hello", ""));

}



TEST_F(EndsWithTest_586, BoundaryCondition_EmptyStringNonEmptySuffix_586) {

    EXPECT_FALSE(Catch::endsWith("", "suffix"));

}



TEST_F(EndsWithTest_586, ExceptionalCase_SuffixLongerThanString_586) {

    EXPECT_FALSE(Catch::endsWith("short", "longerthanstring"));

}
