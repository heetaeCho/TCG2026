#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

#include <vector>



using namespace Catch::Matchers;



class SizeMatchesMatcherTest : public ::testing::Test {

protected:

    template<typename Matcher>

    bool matchSize(const Matcher& matcher, const auto& range) {

        return SizeMatchesMatcher<Matcher>(matcher).match(range);

    }

};



TEST_F(SizeMatchesMatcherTest_233, MatchExactSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_TRUE(matchSize(Equals(3), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MismatchExactSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_FALSE(matchSize(Equals(4), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MatchGreaterThanOrEqualToSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_TRUE(matchSize(Ge(3), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MismatchGreaterThanOrEqualToSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_FALSE(matchSize(Ge(4), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MatchLessThanOrEqualToSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_TRUE(matchSize(Le(3), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MismatchLessThanOrEqualToSize_233) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_FALSE(matchSize(Le(2), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MatchEmptyContainer_233) {

    std::vector<int> vec;

    EXPECT_TRUE(matchSize(Equals(0), vec));

}



TEST_F(SizeMatchesMatcherTest_233, MismatchNonEmptyContainerWithZeroSize_233) {

    std::vector<int> vec = {1};

    EXPECT_FALSE(matchSize(Equals(0), vec));

}
