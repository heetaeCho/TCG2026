#include <gtest/gtest.h>

#include "util/arena.h"



using namespace leveldb;



class ArenaTest_84 : public ::testing::Test {

protected:

    Arena arena;

};



TEST_F(ArenaTest_84, AllocateIncreasesMemoryUsage_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(10);

    EXPECT_GT(arena.MemoryUsage(), initial_usage);

}



TEST_F(ArenaTest_84, AllocateAlignedIncreasesMemoryUsage_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(16);

    EXPECT_GT(arena.MemoryUsage(), initial_usage);

}



TEST_F(ArenaTest_84, MemoryUsageReturnsConsistentValue_84) {

    size_t usage_before = arena.MemoryUsage();

    arena.Allocate(5);

    size_t usage_after = arena.MemoryUsage();

    EXPECT_GE(usage_after, usage_before + 5);

}



TEST_F(ArenaTest_84, AllocateZeroBytesDoesNotChangeMemoryUsage_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(0);

    EXPECT_EQ(arena.MemoryUsage(), initial_usage);

}



TEST_F(ArenaTest_84, AllocateAlignedZeroBytesDoesNotChangeMemoryUsage_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(0);

    EXPECT_EQ(arena.MemoryUsage(), initial_usage);

}



TEST_F(ArenaTest_84, AllocateLargeBlockIncreasesMemoryUsageSignificantly_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(1024 * 1024); // 1MB

    EXPECT_GT(arena.MemoryUsage(), initial_usage + (1024 * 1024));

}



TEST_F(ArenaTest_84, AllocateAlignedLargeBlockIncreasesMemoryUsageSignificantly_84) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(1024 * 1024); // 1MB

    EXPECT_GT(arena.MemoryUsage(), initial_usage + (1024 * 1024));

}
