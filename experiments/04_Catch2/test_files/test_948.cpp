#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Detail;

using namespace ::testing;



TEST(IsPermutationTest_948, IdenticalRanges_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {1, 2, 3};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_TRUE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, DifferentElements_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {4, 5, 6};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_FALSE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, PermutationOfElements_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {3, 1, 2};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_TRUE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, DifferentLengths_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {1, 2};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_FALSE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, EmptyRanges_948) {

    std::vector<int> vec1 = {};

    std::vector<int> vec2 = {};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_TRUE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, FirstRangeEmpty_948) {

    std::vector<int> vec1 = {};

    std::vector<int> vec2 = {1, 2, 3};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_FALSE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, SecondRangeEmpty_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {};

    auto cmp = [](int a, int b) { return a == b; };

    EXPECT_FALSE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, ComparatorAlwaysTrue_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {4, 5, 6};

    auto cmp = [](int a, int b) { return true; };

    EXPECT_TRUE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}



TEST(IsPermutationTest_948, ComparatorAlwaysFalse_948) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {1, 2, 3};

    auto cmp = [](int a, int b) { return false; };

    EXPECT_FALSE(is_permutation(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), cmp));

}
