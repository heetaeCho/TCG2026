#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_20 : public ::testing::Test {

protected:

    MemPoolT<16> memPool;

};



TEST_F(MemPoolTTest_20, InitialCurrentAllocsIsZero_20) {

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_20, AllocIncreasesCurrentAllocs_20) {

    void* allocated = memPool.Alloc();

    EXPECT_NE(allocated, nullptr);

    EXPECT_EQ(memPool.CurrentAllocs(), 1);

}



TEST_F(MemPoolTTest_20, FreeDecreasesCurrentAllocs_20) {

    void* allocated = memPool.Alloc();

    memPool.Free(allocated);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_20, MultipleAllocIncreasesCurrentAllocs_20) {

    for (int i = 0; i < 5; ++i) {

        memPool.Alloc();

    }

    EXPECT_EQ(memPool.CurrentAllocs(), 5);

}



TEST_F(MemPoolTTest_20, MultipleFreeDecreasesCurrentAllocs_20) {

    void* ptr1 = memPool.Alloc();

    void* ptr2 = memPool.Alloc();

    memPool.Free(ptr1);

    memPool.Free(ptr2);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_20, ClearResetsCurrentAllocs_20) {

    for (int i = 0; i < 5; ++i) {

        memPool.Alloc();

    }

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_20, AllocReturnsDifferentPointers_20) {

    void* ptr1 = memPool.Alloc();

    void* ptr2 = memPool.Alloc();

    EXPECT_NE(ptr1, ptr2);

}



TEST_F(MemPoolTTest_20, FreeNullPointerDoesNotCrash_20) {

    memPool.Free(nullptr); // Should not cause a crash

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}
