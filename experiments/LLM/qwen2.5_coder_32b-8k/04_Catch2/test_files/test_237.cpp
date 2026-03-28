#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;



class HasSizeMatcherTest_237 : public ::testing::Test {

protected:

    std::size_t target_size = 5;

    HasSizeMatcher matcher{target_size};

};



TEST_F(HasSizeMatcherTest_237, DescribeReturnsCorrectString_237) {

    EXPECT_EQ(matcher.describe(), "has size == 5");

}



TEST_F(HasSizeMatcherTest_237, MatchWithExactSizeContainer_ReturnsTrue_237) {

    std::vector<int> container(target_size, 0);

    EXPECT_TRUE(matcher.match(container));

}



TEST_F(HasSizeMatcherTest_237, MatchWithLargerSizeContainer_ReturnsFalse_237) {

    std::vector<int> container(target_size + 1, 0);

    EXPECT_FALSE(matcher.match(container));

}



TEST_F(HasSizeMatcherTest_237, MatchWithSmallerSizeContainer_ReturnsFalse_237) {

    std::vector<int> container(target_size - 1, 0);

    EXPECT_FALSE(matcher.match(container));

}



TEST_F(HasSizeMatcherTest_237, MatchWithEmptyContainer_ReturnsFalse_237) {

    std::vector<int> container;

    EXPECT_FALSE(matcher.match(container));

}
