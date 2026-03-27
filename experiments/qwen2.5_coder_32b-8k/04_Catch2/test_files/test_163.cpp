#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MatchAnyOfGenericTest_163 : public ::testing::Test {

protected:

    using MatcherType = int; // Assuming a simple type for matchers

    std::array<void const*, 2> matchersArray = {reinterpret_cast<void const*>(42), reinterpret_cast<void const*>(24)};



    MatchAnyOfGeneric<MatcherType> matchAnyOf = MatchAnyOfGeneric<MatcherType>(matchersArray);

};



TEST_F(MatchAnyOfGenericTest_163, MatchReturnsTrueForMatchingValue_163) {

    EXPECT_TRUE(matchAnyOf.match(42));

}



TEST_F(MatchAnyOfGenericTest_163, MatchReturnsFalseForNonMatchingValue_163) {

    EXPECT_FALSE(matchAnyOf.match(0));

}



TEST_F(MatchAnyOfGenericTest_163, MatchReturnsTrueForAnotherMatchingValue_163) {

    EXPECT_TRUE(matchAnyOf.match(24));

}



TEST_F(MatchAnyOfGenericTest_163, DescribeProvidesMeaningfulDescription_163) {

    std::string description = matchAnyOf.describe();

    EXPECT_THAT(description, ::testing::ContainsRegex("matches any of"));

}



// Assuming boundary conditions for the number of matchers

class MatchAnyOfGenericBoundaryTest_163 : public ::testing::Test {

protected:

    using MatcherType = int; // Assuming a simple type for matchers



    std::array<void const*, 0> emptyMatchersArray;

    MatchAnyOfGeneric<MatcherType> emptyMatchAnyOf = MatchAnyOfGeneric<MatcherType>(emptyMatchersArray);



    std::array<void const*, 1> singleMatchersArray = {reinterpret_cast<void const*>(42)};

    MatchAnyOfGeneric<MatcherType> singleMatchAnyOf = MatchAnyOfGeneric<MatcherType>(singleMatchersArray);

};



TEST_F(MatchAnyOfGenericBoundaryTest_163, MatchWithEmptyMatchersAlwaysReturnsFalse_163) {

    EXPECT_FALSE(emptyMatchAnyOf.match(42));

}



TEST_F(MatchAnyOfGenericBoundaryTest_163, MatchWithSingleMatcherMatchesCorrectly_163) {

    EXPECT_TRUE(singleMatchAnyOf.match(42));

    EXPECT_FALSE(singleMatchAnyOf.match(0));

}
