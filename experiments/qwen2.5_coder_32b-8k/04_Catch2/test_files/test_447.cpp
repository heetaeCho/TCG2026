#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/internal/catch_sharding.hpp>

#include <vector>



using namespace Catch;



TEST_F(CatchShardingTest_447, NormalOperation_SingleShard_447) {

    std::vector<int> container = {1, 2, 3, 4, 5};

    std::size_t shardCount = 1;

    std::size_t shardIndex = 0;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, container);

}



TEST_F(CatchShardingTest_447, NormalOperation_TwoShards_EqualSplit_447) {

    std::vector<int> container = {1, 2, 3, 4};

    std::size_t shardCount = 2;

    std::size_t shardIndex = 0;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({1, 2}));

}



TEST_F(CatchShardingTest_447, NormalOperation_TwoShards_UnequalSplit_447) {

    std::vector<int> container = {1, 2, 3, 4, 5};

    std::size_t shardCount = 2;

    std::size_t shardIndex = 0;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));

}



TEST_F(CatchShardingTest_447, NormalOperation_MultipleShards_EqualSplit_447) {

    std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8};

    std::size_t shardCount = 4;

    std::size_t shardIndex = 2;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({5, 6}));

}



TEST_F(CatchShardingTest_447, NormalOperation_MultipleShards_UnequalSplit_447) {

    std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::size_t shardCount = 4;

    std::size_t shardIndex = 2;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({5, 6, 7}));

}



TEST_F(CatchShardingTest_447, BoundaryCondition_EmptyContainer_447) {

    std::vector<int> container;

    std::size_t shardCount = 2;

    std::size_t shardIndex = 0;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_TRUE(result.empty());

}



TEST_F(CatchShardingTest_447, BoundaryCondition_SingleElementContainer_447) {

    std::vector<int> container = {1};

    std::size_t shardCount = 2;

    std::size_t shardIndex = 0;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({1}));

}



TEST_F(CatchShardingTest_447, BoundaryCondition_LastShard_447) {

    std::vector<int> container = {1, 2, 3, 4, 5};

    std::size_t shardCount = 3;

    std::size_t shardIndex = 2;

    auto result = createShard(container, shardCount, shardIndex);

    EXPECT_EQ(result, std::vector<int>({5}));

}



TEST_F(CatchShardingTest_447, ExceptionalCase_ZeroShards_447) {

    std::vector<int> container = {1, 2, 3, 4, 5};

    std::size_t shardCount = 0;

    std::size_t shardIndex = 0;

    EXPECT_DEATH(createShard(container, shardCount, shardIndex), "");

}



TEST_F(CatchShardingTest_447, ExceptionalCase_IndexGreaterThanCount_447) {

    std::vector<int> container = {1, 2, 3, 4, 5};

    std::size_t shardCount = 2;

    std::size_t shardIndex = 2;

    EXPECT_DEATH(createShard(container, shardCount, shardIndex), "");

}
