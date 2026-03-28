#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <algorithm>
#include <numeric>

// Include the header under test
#include "catch2/internal/catch_sharding.hpp"

// Test fixture
class CreateShardTest_447 : public ::testing::Test {
protected:
    std::vector<int> makeRange(int n) {
        std::vector<int> v(n);
        std::iota(v.begin(), v.end(), 0);
        return v;
    }
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(CreateShardTest_447, SingleShardReturnsEntireContainer_447) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    auto result = Catch::createShard(input, 1, 0);
    EXPECT_EQ(result, input);
}

TEST_F(CreateShardTest_447, TwoShardsEvenSplit_447) {
    std::vector<int> input = {0, 1, 2, 3};
    auto shard0 = Catch::createShard(input, 2, 0);
    auto shard1 = Catch::createShard(input, 2, 1);
    
    EXPECT_EQ(shard0, (std::vector<int>{0, 1}));
    EXPECT_EQ(shard1, (std::vector<int>{2, 3}));
}

TEST_F(CreateShardTest_447, TwoShardsOddSplit_447) {
    std::vector<int> input = {0, 1, 2, 3, 4};
    auto shard0 = Catch::createShard(input, 2, 0);
    auto shard1 = Catch::createShard(input, 2, 1);
    
    // 5 elements, shardSize=2, leftover=1
    // shard0: start=0, end=3 -> {0,1,2}
    // shard1: start=3, end=5 -> {3,4}
    EXPECT_EQ(shard0, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(shard1, (std::vector<int>{3, 4}));
}

TEST_F(CreateShardTest_447, ThreeShardsEvenSplit_447) {
    std::vector<int> input = {0, 1, 2, 3, 4, 5};
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    EXPECT_EQ(shard0, (std::vector<int>{0, 1}));
    EXPECT_EQ(shard1, (std::vector<int>{2, 3}));
    EXPECT_EQ(shard2, (std::vector<int>{4, 5}));
}

TEST_F(CreateShardTest_447, ThreeShardsWithLeftover_447) {
    std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7};
    // 8 elements, 3 shards: shardSize=2, leftover=2
    // shard0: start=0, end=3 -> {0,1,2}
    // shard1: start=3, end=6 -> {3,4,5}
    // shard2: start=6, end=8 -> {6,7}
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    EXPECT_EQ(shard0, (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(shard1, (std::vector<int>{3, 4, 5}));
    EXPECT_EQ(shard2, (std::vector<int>{6, 7}));
}

TEST_F(CreateShardTest_447, AllShardsCombineToOriginal_447) {
    std::vector<int> input = makeRange(17);
    std::size_t shardCount = 5;
    
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    
    EXPECT_EQ(combined, input);
}

TEST_F(CreateShardTest_447, AllShardsCombineToOriginalEvenDivision_447) {
    std::vector<int> input = makeRange(20);
    std::size_t shardCount = 4;
    
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    
    EXPECT_EQ(combined, input);
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(CreateShardTest_447, EmptyContainer_447) {
    std::vector<int> input;
    auto result = Catch::createShard(input, 1, 0);
    EXPECT_TRUE(result.empty());
}

TEST_F(CreateShardTest_447, EmptyContainerMultipleShards_447) {
    std::vector<int> input;
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    EXPECT_TRUE(shard0.empty());
    EXPECT_TRUE(shard1.empty());
    EXPECT_TRUE(shard2.empty());
}

TEST_F(CreateShardTest_447, SingleElementSingleShard_447) {
    std::vector<int> input = {42};
    auto result = Catch::createShard(input, 1, 0);
    EXPECT_EQ(result, (std::vector<int>{42}));
}

TEST_F(CreateShardTest_447, SingleElementTwoShards_447) {
    std::vector<int> input = {42};
    auto shard0 = Catch::createShard(input, 2, 0);
    auto shard1 = Catch::createShard(input, 2, 1);
    
    // 1 element, 2 shards: shardSize=0, leftover=1
    // shard0: start=0, end=1 -> {42}
    // shard1: start=1, end=1 -> {}
    EXPECT_EQ(shard0, (std::vector<int>{42}));
    EXPECT_TRUE(shard1.empty());
}

TEST_F(CreateShardTest_447, MoreShardsThanElements_447) {
    std::vector<int> input = {0, 1, 2};
    std::size_t shardCount = 5;
    
    // 3 elements, 5 shards: shardSize=0, leftover=3
    // shard0: [0,1), shard1: [1,2), shard2: [2,3), shard3: [3,3), shard4: [3,3)
    auto shard0 = Catch::createShard(input, shardCount, 0);
    auto shard1 = Catch::createShard(input, shardCount, 1);
    auto shard2 = Catch::createShard(input, shardCount, 2);
    auto shard3 = Catch::createShard(input, shardCount, 3);
    auto shard4 = Catch::createShard(input, shardCount, 4);
    
    EXPECT_EQ(shard0.size(), 1u);
    EXPECT_EQ(shard1.size(), 1u);
    EXPECT_EQ(shard2.size(), 1u);
    EXPECT_TRUE(shard3.empty());
    EXPECT_TRUE(shard4.empty());
    
    // Check they combine correctly
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    EXPECT_EQ(combined, input);
}

TEST_F(CreateShardTest_447, ShardCountEqualsElementCount_447) {
    std::vector<int> input = {10, 20, 30, 40, 50};
    std::size_t shardCount = 5;
    
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        ASSERT_EQ(shard.size(), 1u) << "Shard " << i << " should have exactly 1 element";
        EXPECT_EQ(shard[0], input[i]);
    }
}

// ============================================================
// Different container types
// ============================================================

TEST_F(CreateShardTest_447, WorksWithList_447) {
    std::list<int> input = {0, 1, 2, 3, 4, 5, 6};
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    // 7 elements, 3 shards: shardSize=2, leftover=1
    // shard0: [0,3) -> {0,1,2}
    // shard1: [3,5) -> {3,4}
    // shard2: [5,7) -> {5,6}
    EXPECT_EQ(shard0, (std::list<int>{0, 1, 2}));
    EXPECT_EQ(shard1, (std::list<int>{3, 4}));
    EXPECT_EQ(shard2, (std::list<int>{5, 6}));
}

TEST_F(CreateShardTest_447, WorksWithStringVector_447) {
    std::vector<std::string> input = {"a", "b", "c", "d", "e"};
    auto shard0 = Catch::createShard(input, 2, 0);
    auto shard1 = Catch::createShard(input, 2, 1);
    
    // 5 elements, 2 shards: shardSize=2, leftover=1
    // shard0: [0,3) -> {"a","b","c"}
    // shard1: [3,5) -> {"d","e"}
    EXPECT_EQ(shard0, (std::vector<std::string>{"a", "b", "c"}));
    EXPECT_EQ(shard1, (std::vector<std::string>{"d", "e"}));
}

// ============================================================
// Verify leftover distribution
// ============================================================

TEST_F(CreateShardTest_447, LeftoverElementsDistributedToEarlyShards_447) {
    // 10 elements, 3 shards: shardSize=3, leftover=1
    // shard0 gets 4 elements, shard1 gets 3, shard2 gets 3
    std::vector<int> input = makeRange(10);
    
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    EXPECT_EQ(shard0.size(), 4u);
    EXPECT_EQ(shard1.size(), 3u);
    EXPECT_EQ(shard2.size(), 3u);
}

TEST_F(CreateShardTest_447, LeftoverTwoElements_447) {
    // 11 elements, 3 shards: shardSize=3, leftover=2
    // shard0 gets 4, shard1 gets 4, shard2 gets 3
    std::vector<int> input = makeRange(11);
    
    auto shard0 = Catch::createShard(input, 3, 0);
    auto shard1 = Catch::createShard(input, 3, 1);
    auto shard2 = Catch::createShard(input, 3, 2);
    
    EXPECT_EQ(shard0.size(), 4u);
    EXPECT_EQ(shard1.size(), 4u);
    EXPECT_EQ(shard2.size(), 3u);
}

// ============================================================
// Large input test
// ============================================================

TEST_F(CreateShardTest_447, LargeInputAllShardsCombine_447) {
    std::vector<int> input = makeRange(1000);
    std::size_t shardCount = 7;
    
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    
    EXPECT_EQ(combined, input);
}

TEST_F(CreateShardTest_447, LargeInputShardSizesAreBalanced_447) {
    std::vector<int> input = makeRange(1000);
    std::size_t shardCount = 7;
    // 1000 / 7 = 142, leftover = 6
    // First 6 shards get 143, last shard gets 142
    
    for (std::size_t i = 0; i < 6; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        EXPECT_EQ(shard.size(), 143u) << "Shard " << i;
    }
    auto lastShard = Catch::createShard(input, shardCount, 6);
    EXPECT_EQ(lastShard.size(), 142u);
}

// ============================================================
// Verify no overlap and order preservation
// ============================================================

TEST_F(CreateShardTest_447, ShardsPreserveOrder_447) {
    std::vector<int> input = makeRange(15);
    std::size_t shardCount = 4;
    
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        // Each shard's elements should be in ascending order
        for (std::size_t j = 1; j < shard.size(); ++j) {
            EXPECT_LT(shard[j-1], shard[j]);
        }
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    // Combined should equal original
    EXPECT_EQ(combined, input);
}

TEST_F(CreateShardTest_447, ShardsDoNotOverlap_447) {
    std::vector<int> input = makeRange(13);
    std::size_t shardCount = 4;
    
    std::vector<int> combined;
    for (std::size_t i = 0; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        combined.insert(combined.end(), shard.begin(), shard.end());
    }
    
    // No duplicates
    std::sort(combined.begin(), combined.end());
    auto it = std::unique(combined.begin(), combined.end());
    EXPECT_EQ(it, combined.end());
    EXPECT_EQ(combined.size(), input.size());
}

// ============================================================
// Edge: shard count equals container size + extra empty shards
// ============================================================

TEST_F(CreateShardTest_447, TwoElementsTenShards_447) {
    std::vector<int> input = {100, 200};
    std::size_t shardCount = 10;
    
    // 2 elements, 10 shards: shardSize=0, leftover=2
    // shard0 and shard1 get 1 element each, rest are empty
    auto shard0 = Catch::createShard(input, shardCount, 0);
    auto shard1 = Catch::createShard(input, shardCount, 1);
    
    EXPECT_EQ(shard0.size(), 1u);
    EXPECT_EQ(shard0[0], 100);
    EXPECT_EQ(shard1.size(), 1u);
    EXPECT_EQ(shard1[0], 200);
    
    for (std::size_t i = 2; i < shardCount; ++i) {
        auto shard = Catch::createShard(input, shardCount, i);
        EXPECT_TRUE(shard.empty()) << "Shard " << i << " should be empty";
    }
}
