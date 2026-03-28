#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Detail;



class SentinelDistanceTest : public ::testing::Test {

protected:

    using ForwardIter = std::vector<int>::iterator;

    using Sentinel = std::vector<int>::iterator;

};



TEST_F(SentinelDistanceTest_945, NormalOperation_945) {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    ForwardIter iter = vec.begin();

    Sentinel sentinel = vec.end();

    EXPECT_EQ(sentinel_distance(iter, sentinel), 5);

}



TEST_F(SentinelDistanceTest_945, EmptyContainer_945) {

    std::vector<int> vec;

    ForwardIter iter = vec.begin();

    Sentinel sentinel = vec.end();

    EXPECT_EQ(sentinel_distance(iter, sentinel), 0);

}



TEST_F(SentinelDistanceTest_945, SingleElement_945) {

    std::vector<int> vec = {1};

    ForwardIter iter = vec.begin();

    Sentinel sentinel = vec.end();

    EXPECT_EQ(sentinel_distance(iter, sentinel), 1);

}



TEST_F(SentinelDistanceTest_945, IterEqualsSentinel_945) {

    std::vector<int> vec = {1, 2, 3};

    ForwardIter iter = vec.begin() + 3;

    Sentinel sentinel = vec.end();

    EXPECT_EQ(sentinel_distance(iter, sentinel), 0);

}



TEST_F(SentinelDistanceTest_945, IterBeforeSentinel_945) {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    ForwardIter iter = vec.begin() + 2;

    Sentinel sentinel = vec.end();

    EXPECT_EQ(sentinel_distance(iter, sentinel), 3);

}
