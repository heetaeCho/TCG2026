#include <gtest/gtest.h>

#include "util/arena.h"



namespace {



class ArenaTest_85 : public ::testing::Test {

protected:

    leveldb::Arena arena;

};



TEST_F(ArenaTest_85, AllocateReturnsNonNullPointerForPositiveSize_85) {

    char* ptr = arena.Allocate(1);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_85, AllocateIncreasesMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(10);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_85, AllocateAlignedReturnsNonNullPointerForPositiveSize_85) {

    char* ptr = arena.AllocateAligned(16);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(ArenaTest_85, AllocateAlignedIncreasesMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(16);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_85, AllocateThrowsAssertionForZeroSize_85) {

    EXPECT_DEATH({ arena.Allocate(0); }, "bytes > 0");

}



TEST_F(ArenaTest_85, AllocateAlignedThrowsAssertionForZeroSize_85) {

    EXPECT_DEATH({ arena.AllocateAligned(0); }, "bytes > 0");

}



TEST_F(ArenaTest_85, MultipleAllocatesIncreaseMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(1);

    arena.Allocate(2);

    arena.Allocate(3);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_85, AllocateAlignedWithVariousSizesIncreasesMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(16);

    arena.AllocateAligned(32);

    arena.AllocateAligned(48);

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_85, AllocateWithLargeSizeIncreasesMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.Allocate(1024 * 1024); // 1MB

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



TEST_F(ArenaTest_85, AllocateAlignedWithLargeSizeIncreasesMemoryUsage_85) {

    size_t initial_usage = arena.MemoryUsage();

    arena.AllocateAligned(1024 * 1024); // 1MB

    size_t final_usage = arena.MemoryUsage();

    EXPECT_GT(final_usage, initial_usage);

}



} // namespace
