#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/yaml-cpp/src/exp.h"



using namespace YAML::Exp;



TEST(ValueFunctionTest_134, ReturnsValidRegExInstance_134) {

    const RegEx& value = Value();

    EXPECT_TRUE(&value != nullptr);

}



TEST(MatchesCharTest_134, MatchesColon_134) {

    const RegEx& value = Value();

    EXPECT_TRUE(value.Matches(':'));

}



TEST(MatchesCharTest_134, DoesNotMatchNonColon_134) {

    const RegEx& value = Value();

    EXPECT_FALSE(value.Matches('a'));

}



TEST(MatchesStringTest_134, MatchesColonOnlyString_134) {

    const RegEx& value = Value();

    EXPECT_TRUE(value.Matches(":"));

}



TEST(MatchesStringTest_134, MatchesColonFollowedByBlank_134) {

    const RegEx& value = Value();

    EXPECT_TRUE(value.Matches(": "));

}



TEST(MatchesStringTest_134, DoesNotMatchEmptyString_134) {

    const RegEx& value = Value();

    EXPECT_FALSE(value.Matches(""));

}



TEST(MatchStringTest_134, MatchColonOnlyStringReturnsOne_134) {

    const RegEx& value = Value();

    EXPECT_EQ(1, value.Match(":"));

}



TEST(MatchStringTest_134, MatchColonFollowedByBlankReturnsTwo_134) {

    const RegEx& value = Value();

    EXPECT_EQ(2, value.Match(": "));

}



TEST(MatchStringTest_134, MatchEmptyStringReturnsZero_134) {

    const RegEx& value = Value();

    EXPECT_EQ(0, value.Match(""));

}
