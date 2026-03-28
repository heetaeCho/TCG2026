#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest : public ::testing::Test {

protected:

    MemPoolT<sizeof(int)> memPool;

};



TEST_F(MemPoolTTest_18, ClearResetsCounters_18) {

    void* ptr = memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_18, AllocIncreasesCurrentAllocs_18) {

    size_t initialCount = memPool.CurrentAllocs();

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount + 1);

}



TEST_F(MemPoolTTest_18, FreeDecreasesCurrentAllocs_18) {

    void* ptr = memPool.Alloc();

    size_t initialCount = memPool.CurrentAllocs();

    memPool.Free(ptr);

    EXPECT_EQ(memPool.CurrentAllocs(), initialCount - 1);

}



TEST_F(MemPoolTTest_18, ClearReleasesAllBlocks_18) {

    for (int i = 0; i < 20; ++i) { // Assuming more than one block is needed

        memPool.Alloc();

    }

    size_t initialBlockCount = memPool._blockPtrs.Size(); // Accessing public member for testing purposes only

    memPool.Clear();

    EXPECT_EQ(memPool._blockPtrs.Size(), 0); // Accessing public member for testing purposes only

}



TEST_F(MemPoolTTest_18, AllocReturnsNonNullPointer_18) {

    void* ptr = memPool.Alloc();

    EXPECT_NE(ptr, nullptr);

}



TEST_F(MemPoolTTest_18, FreeWithNullDoesNotCrash_18) {

    EXPECT_NO_THROW(memPool.Free(nullptr));

}
