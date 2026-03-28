#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/python/_re2.cc"

#include "./TestProjects/re2/re2/re2.h"



using namespace re2;

using namespace re2_python;

using ::testing::ElementsAre;

using ::testing::Pair;



class RE2NamedCapturingGroupsShimTest_55 : public ::testing::Test {

protected:

    RE2NamedCapturingGroupsShimTest_55() {}

};



TEST_F(RE2NamedCapturingGroupsShimTest_55, NoCapturingGroups_55) {

    RE2 re("(?:abc)");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_TRUE(result.empty());

}



TEST_F(RE2NamedCapturingGroupsShimTest_55, SingleNamedGroup_55) {

    RE2 re("(?<name>abc)");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_THAT(result, ElementsAre(Pair("name", 1)));

}



TEST_F(RE2NamedCapturingGroupsShimTest_55, MultipleNamedGroups_55) {

    RE2 re("(?<first>a)(?<second>b)(?<third>c)");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_THAT(result, ElementsAre(Pair("first", 1), Pair("second", 2), Pair("third", 3)));

}



TEST_F(RE2NamedCapturingGroupsShimTest_55, DuplicateNamedGroups_55) {

    RE2 re("(?<name>a)(b)(?<name>c)");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_THAT(result, ElementsAre(Pair("name", 1))); // Last occurrence of the name is used

}



TEST_F(RE2NamedCapturingGroupsShimTest_55, InvalidPattern_55) {

    RE2 re("(?<namea)");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_TRUE(result.empty());

}



TEST_F(RE2NamedCapturingGroupsShimTest_55, ComplexPatternWithNamedGroups_55) {

    RE2 re("abc(?<x>def)ghi(?<y>jkl)mno");

    auto result = RE2NamedCapturingGroupsShim(re);

    EXPECT_THAT(result, ElementsAre(Pair("x", 1), Pair("y", 2)));

}
