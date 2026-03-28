#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest : public ::testing::Test {

protected:

    MemPoolT<16> memPool;

};



TEST_F(MemPoolTTest_19, ItemSize_ReturnsCorrectValue_19) {

    EXPECT_EQ(memPool.ItemSize(), 16);

}



TEST_F(MemPoolTTest_19, CurrentAllocs_ReturnsZeroInitially_19) {

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_19, Alloc_IncreasesCurrentAllocs_19) {

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), 1);

}



TEST_F(MemPoolTTest_19, Free_DecreasesCurrentAllocs_19) {

    void* ptr = memPool.Alloc();

    memPool.Free(ptr);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_19, Alloc_MultipleTimesIncreasesCurrentAllocs_19) {

    for (int i = 0; i < 5; ++i) {

        memPool.Alloc();

    }

    EXPECT_EQ(memPool.CurrentAllocs(), 5);

}



TEST_F(MemPoolTTest_19, Free_AllAllocatedDecreasesCurrentAllocsToZero_19) {

    void* ptr1 = memPool.Alloc();

    void* ptr2 = memPool.Alloc();

    memPool.Free(ptr1);

    memPool.Free(ptr2);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_19, Untracked_ReturnsZeroInitially_19) {

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_19, SetTracked_UntrackedReturnsNonZero_19) {

    memPool.SetTracked();

    EXPECT_NE(memPool.Untracked(), 0);

}
