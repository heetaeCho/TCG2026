#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>



using namespace Catch::Matchers;



TEST(ContainsMatcherTest_966, Match_EmptyVectors_ShouldReturnTrue_966) {

    std::vector<int> comparator;

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v;

    EXPECT_TRUE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_EmptyComparator_ShouldReturnTrue_966) {

    std::vector<int> comparator;

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {1, 2, 3};

    EXPECT_TRUE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_EmptyVector_ShouldReturnFalse_966) {

    std::vector<int> comparator = {1, 2, 3};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v;

    EXPECT_FALSE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_SmallVectorWithAllElements_ShouldReturnTrue_966) {

    std::vector<int> comparator = {1, 2, 3};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {1, 2, 3};

    EXPECT_TRUE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_LargerVectorWithAllElements_ShouldReturnTrue_966) {

    std::vector<int> comparator = {1, 2};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {1, 2, 3, 4, 5};

    EXPECT_TRUE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_VectorWithMissingElement_ShouldReturnFalse_966) {

    std::vector<int> comparator = {1, 2, 3};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {1, 3};

    EXPECT_FALSE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_VectorWithExtraElement_ShouldReturnTrue_966) {

    std::vector<int> comparator = {1, 2, 3};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {1, 2, 3, 4};

    EXPECT_TRUE(matcher.match(v));

}



TEST(ContainsMatcherTest_966, Match_VectorWithDifferentOrder_ShouldReturnFalse_966) {

    std::vector<int> comparator = {1, 2, 3};

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> v = {3, 2, 1};

    EXPECT_FALSE(matcher.match(v));

}
