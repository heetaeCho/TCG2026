#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_21 : public ::testing::Test {

protected:

    MemPoolT<16> memPool;

};



TEST_F(MemPoolTTest_21, Alloc_ReturnsNonNullPointer_21) {

    void* ptr = memPool.Alloc();

    EXPECT_NE(ptr, nullptr);

}



TEST_F(MemPoolTTest_21, MultipleAlloc_ReturnsDistinctPointers_21) {

    void* ptr1 = memPool.Alloc();

    void* ptr2 = memPool.Alloc();

    EXPECT_NE(ptr1, ptr2);

}



TEST_F(MemPoolTTest_21, Clear_ResetsAllocationCount_21) {

    memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0u);

}



TEST_F(MemPoolTTest_21, Alloc_IncreasesCurrentAllocs_21) {

    size_t initialCount = memPool.CurrentAllocs();

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount + 1u);

}



TEST_F(MemPoolTTest_21, Untracked_ReturnsCorrectCountAfterAlloc_21) {

    memPool.Alloc();

    EXPECT_EQ(memPool.Untracked(), 1u);

}



TEST_F(MemPoolTTest_21, Clear_ResetsUntrackedCount_21) {

    memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.Untracked(), 0u);

}
