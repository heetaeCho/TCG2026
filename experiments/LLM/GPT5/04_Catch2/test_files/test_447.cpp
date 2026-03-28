// File: create_shard_tests_447.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <numeric>   // std::iota
#include <iterator>  // std::next

// Include the header under test
#include "Catch2/src/catch2/internal/catch_sharding.hpp"

using Catch::createShard;

namespace {

template <typename Container>
Container makeSequential(std::size_t n) {
    Container c;
    if constexpr (std::is_same_v<Container, std::vector<int>>) {
        c.resize(n);
        std::iota(c.begin(), c.end(), 0);
    } else {
        for (std::size_t i = 0; i < n; ++i) c.push_back(static_cast<int>(i));
    }
    return c;
}

template <typename Container>
std::vector<int> toVec(const Container& c) {
    return std::vector<int>(c.begin(), c.end());
}

} // namespace

// Normal operation: shardCount == 1 returns the full container unchanged.
TEST(CreateShardTest_447, ReturnsFullWhenSingleShard_447) {
    std::vector<int> input = makeSequential<std::vector<int>>(7);
    auto out = createShard(input, /*shardCount=*/1, /*shardIndex=*/0);
    EXPECT_EQ(out, input);
}

// Normal operation: even split across shards.
TEST(CreateShardTest_447, SplitsEvenly_447) {
    std::vector<int> input = makeSequential<std::vector<int>>(8); // [0..7]
    // 4 shards => 2 items each
    auto s0 = createShard(input, 4, 0);
    auto s1 = createShard(input, 4, 1);
    auto s2 = createShard(input, 4, 2);
    auto s3 = createShard(input, 4, 3);

    EXPECT_EQ(s0, (std::vector<int>{0,1}));
    EXPECT_EQ(s1, (std::vector<int>{2,3}));
    EXPECT_EQ(s2, (std::vector<int>{4,5}));
    EXPECT_EQ(s3, (std::vector<int>{6,7}));
}

// Normal operation: leftovers distributed to the first shards.
TEST(CreateShardTest_447, DistributesLeftoversToFirstShards_447) {
    std::vector<int> input = makeSequential<std::vector<int>>(10); // [0..9]
    // 3 shards: base size 3, leftovers = 1 -> sizes [4,3,3]
    auto s0 = createShard(input, 3, 0);
    auto s1 = createShard(input, 3, 1);
    auto s2 = createShard(input, 3, 2);

    EXPECT_EQ(s0, (std::vector<int>{0,1,2,3}));
    EXPECT_EQ(s1, (std::vector<int>{4,5,6}));
    EXPECT_EQ(s2, (std::vector<int>{7,8,9}));
}

// Boundary: empty container returns empty shards for all shard indices.
TEST(CreateShardTest_447, EmptyContainer_447) {
    std::vector<int> empty;
    // Any valid shardCount/shardIndex pair should yield empty
    auto s0 = createShard(empty, 2, 0);
    auto s1 = createShard(empty, 2, 1);
    EXPECT_TRUE(s0.empty());
    EXPECT_TRUE(s1.empty());
}

// Boundary: verify last shard covers the tail correctly.
TEST(CreateShardTest_447, LastShardBoundaries_447) {
    std::vector<int> input = makeSequential<std::vector<int>>(7); // [0..6]
    // 3 shards: base size 2, leftovers 1 -> sizes [3,2,2]
    auto s2 = createShard(input, 3, 2);
    EXPECT_EQ(s2, (std::vector<int>{5,6}));
}

// Template behavior: works with different container types (std::list).
TEST(CreateShardTest_447, WorksWithStdList_447) {
    std::list<int> input = makeSequential<std::list<int>>(5); // [0..4]
    // 2 shards -> base size 2, leftovers 1 -> sizes [3,2]
    auto s0 = createShard(input, 2, 0);
    auto s1 = createShard(input, 2, 1);

    EXPECT_EQ(toVec(s0), (std::vector<int>{0,1,2}));
    EXPECT_EQ(toVec(s1), (std::vector<int>{3,4}));
}

#ifndef NDEBUG
// Error case (debug builds): shardIndex must be < shardCount, expect debug assert death.
TEST(CreateShardTest_447, InvalidShardIndexTriggersAssertInDebug_447) {
#if GTEST_HAS_DEATH_TEST
    std::vector<int> input = makeSequential<std::vector<int>>(3);
    // shardIndex == shardCount -> violates precondition -> assert fires in debug
    EXPECT_DEATH({ auto _ = createShard(input, 2, 2); (void)_; }, "");
#else
    GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}
#endif // !NDEBUG
