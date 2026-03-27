#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"

#include <vector>



using namespace Catch::Matchers;

using ::testing::ElementsAre;



class NoneTrueMatcherTest : public ::testing::Test {

protected:

    NoneTrueMatcher matcher;

};



TEST_F(NoneTrueMatcherTest_183, AllFalse_ReturnsTrue_183) {

    std::vector<bool> range = {false, false, false};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(NoneTrueMatcherTest_183, SomeTrue_ReturnsFalse_183) {

    std::vector<bool> range = {false, true, false};

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(NoneTrueMatcherTest_183, AllTrue_ReturnsFalse_183) {

    std::vector<bool> range = {true, true, true};

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(NoneTrueMatcherTest_183, EmptyRange_ReturnsTrue_183) {

    std::vector<bool> range = {};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(NoneTrueMatcherTest_183, SingleFalse_ReturnsTrue_183) {

    std::vector<bool> range = {false};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(NoneTrueMatcherTest_183, SingleTrue_ReturnsFalse_183) {

    std::vector<bool> range = {true};

    EXPECT_FALSE(matcher.match(range));

}
