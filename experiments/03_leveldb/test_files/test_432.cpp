#include <gtest/gtest.h>

#include "util/arena.h"



using namespace leveldb;



class ArenaTest_432 : public ::testing::Test {

protected:

    Arena arena;

};



TEST_F(ArenaTest_432, AllocateAligned_ReturnsNonZeroPointerForPositiveSize_432) {

    size_t bytes = 16;

    char* result = arena.AllocateAligned(bytes);

    EXPECT_NE(result, nullptr);

}



TEST_F(ArenaTest_432, AllocateAligned_ReturnsProperlyAlignedPointer_432) {

    size_t bytes = 1;

    char* result = arena.AllocateAligned(bytes);

    const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;

    EXPECT_EQ(reinterpret_cast<uintptr_t>(result) % align, 0);

}



TEST_F(ArenaTest_432, AllocateAligned_ReturnsDifferentPointersForSubsequentAllocations_432) {

    size_t bytes = 16;

    char* result1 = arena.AllocateAligned(bytes);

    char* result2 = arena.AllocateAligned(bytes);

    EXPECT_NE(result1, result2);

}



TEST_F(ArenaTest_432, AllocateAligned_ZeroSize_ReturnsNullPointer_432) {

    size_t bytes = 0;

    char* result = arena.AllocateAligned(bytes);

    EXPECT_EQ(result, nullptr);

}



TEST_F(ArenaTest_432, AllocateAligned_LargeSize_AllocatesSuccessfully_432) {

    size_t bytes = 1024 * 1024; // Large allocation

    char* result = arena.AllocateAligned(bytes);

    EXPECT_NE(result, nullptr);

}



TEST_F(ArenaTest_432, AllocateAligned_MemoryUsageIncreasesAfterAllocation_432) {

    size_t initial_memory_usage = arena.MemoryUsage();

    size_t bytes = 16;

    arena.AllocateAligned(bytes);

    size_t final_memory_usage = arena.MemoryUsage();

    EXPECT_GT(final_memory_usage, initial_memory_usage);

}



TEST_F(ArenaTest_432, AllocateAligned_MemoryUsageReflectsAllocatedSize_432) {

    size_t bytes = 16;

    arena.AllocateAligned(bytes);

    EXPECT_GE(arena.MemoryUsage(), bytes);

}
