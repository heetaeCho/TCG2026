#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"

#include <vector>



using namespace Catch::Matchers;

using ::testing::ElementsAre;



TEST(AllTrueMatcherTest_182, AllElementsTrue_182) {

    std::vector<bool> values = {true, true, true};

    AllTrueMatcher matcher;

    EXPECT_TRUE(matcher.match(values));

}



TEST(AllTrueMatcherTest_182, MixedElements_182) {

    std::vector<bool> values = {true, false, true};

    AllTrueMatcher matcher;

    EXPECT_FALSE(matcher.match(values));

}



TEST(AllTrueMatcherTest_182, AllElementsFalse_182) {

    std::vector<bool> values = {false, false, false};

    AllTrueMatcher matcher;

    EXPECT_FALSE(matcher.match(values));

}



TEST(AllTrueMatcherTest_182, EmptyRange_182) {

    std::vector<bool> values = {};

    AllTrueMatcher matcher;

    EXPECT_TRUE(matcher.match(values));

}



TEST(AllTrueMatcherTest_182, SingleElementTrue_182) {

    std::vector<bool> values = {true};

    AllTrueMatcher matcher;

    EXPECT_TRUE(matcher.match(values));

}



TEST(AllTrueMatcherTest_182, SingleElementFalse_182) {

    std::vector<bool> values = {false};

    AllTrueMatcher matcher;

    EXPECT_FALSE(matcher.match(values));

}
