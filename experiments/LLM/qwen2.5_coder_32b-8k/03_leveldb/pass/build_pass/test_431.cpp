#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/arena.h"



using namespace leveldb;



class ArenaTest_431 : public ::testing::Test {

protected:

    Arena arena;

};



TEST_F(ArenaTest_431, AllocateReturnsNonNullPointer_431) {

    size_t bytes = 10;

    char* ptr = arena.Allocate(bytes);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_431, AllocateAlignedReturnsNonNullPointer_431) {

    size_t bytes = 16;

    char* ptr = arena.AllocateAligned(bytes);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_431, AllocateIncreasesMemoryUsage_431) {

    size_t initial_usage = arena.MemoryUsage();

    size_t bytes = 10;

    arena.Allocate(bytes);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_431, AllocateAlignedIncreasesMemoryUsage_431) {

    size_t initial_usage = arena.MemoryUsage();

    size_t bytes = 16;

    arena.AllocateAligned(bytes);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_431, AllocateZeroBytesReturnsNonNullPointer_431) {

    char* ptr = arena.Allocate(0);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_431, AllocateAlignedZeroBytesReturnsNonNullPointer_431) {

    char* ptr = arena.AllocateAligned(0);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_431, MemoryUsageIsConsistentWithAllocations_431) {

    size_t initial_usage = arena.MemoryUsage();

    for (size_t i = 1; i <= 5; ++i) {

        arena.Allocate(i);

        EXPECT_GE(arena.MemoryUsage(), initial_usage + i);

        initial_usage = arena.MemoryUsage();

    }

}



TEST_F(ArenaTest_431, MemoryUsageIsConsistentWithAlignedAllocations_431) {

    size_t initial_usage = arena.MemoryUsage();

    for (size_t i = 1; i <= 5; ++i) {

        arena.AllocateAligned(i);

        EXPECT_GE(arena.MemoryUsage(), initial_usage + i);

        initial_usage = arena.MemoryUsage();

    }

}
