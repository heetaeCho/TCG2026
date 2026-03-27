#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_25 : public ::testing::Test {

protected:

    MemPoolT<16> memPool;

};



TEST_F(MemPoolTTest_25, UntrackedInitiallyZero_25) {

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_25, AllocAndFreeDoesNotAffectUntracked_25) {

    void* item = memPool.Alloc();

    memPool.Free(item);

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_25, SetTrackedIncreasesUntrackedCount_25) {

    void* item = memPool.Alloc();

    memPool.SetTracked();

    EXPECT_EQ(memPool.Untracked(), 1);

    memPool.Free(item);

}



TEST_F(MemPoolTTest_25, ClearResetsAllCounts_25) {

    memPool.Alloc();

    memPool.SetTracked();

    memPool.Clear();

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_25, AllocIncreasesCurrentAllocsCount_25) {

    size_t initialCount = memPool.CurrentAllocs();

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount + 1);

}



TEST_F(MemPoolTTest_25, FreeDecreasesCurrentAllocsCount_25) {

    void* item = memPool.Alloc();

    size_t initialCount = memPool.CurrentAllocs();

    memPool.Free(item);

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount - 1);

}



TEST_F(MemPoolTTest_25, AllocateAndFreeMultipleItems_25) {

    void* item1 = memPool.Alloc();

    void* item2 = memPool.Alloc();

    size_t initialCount = memPool.CurrentAllocs();



    memPool.Free(item1);

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount - 1);



    memPool.Free(item2);

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount - 2);

}



TEST_F(MemPoolTTest_25, AllocReturnsNonNullPointer_25) {

    void* item = memPool.Alloc();

    EXPECT_NE(item, nullptr);

    memPool.Free(item);

}
