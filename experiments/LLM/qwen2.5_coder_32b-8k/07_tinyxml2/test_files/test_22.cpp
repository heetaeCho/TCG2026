#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_22 : public ::testing::Test {

protected:

    MemPoolT<16> memPool; // Using a template parameter of 16 for testing purposes

};



TEST_F(MemPoolTTest_22, AllocReturnsNonNullPointer_22) {

    void* allocatedMemory = memPool.Alloc();

    EXPECT_NE(allocatedMemory, nullptr);

}



TEST_F(MemPoolTTest_22, FreeDecreasesCurrentAllocs_22) {

    void* allocatedMemory = memPool.Alloc();

    size_t initialAllocs = memPool.CurrentAllocs();

    memPool.Free(allocatedMemory);

    size_t finalAllocs = memPool.CurrentAllocs();

    EXPECT_EQ(finalAllocs, initialAllocs - 1);

}



TEST_F(MemPoolTTest_22, FreeNullPointerDoesNothing_22) {

    size_t initialAllocs = memPool.CurrentAllocs();

    memPool.Free(nullptr);

    size_t finalAllocs = memPool.CurrentAllocs();

    EXPECT_EQ(finalAllocs, initialAllocs);

}



TEST_F(MemPoolTTest_22, CurrentAllocsReflectsAllocations_22) {

    void* allocatedMemory1 = memPool.Alloc();

    void* allocatedMemory2 = memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), 2u);



    memPool.Free(allocatedMemory1);

    EXPECT_EQ(memPool.CurrentAllocs(), 1u);



    memPool.Free(allocatedMemory2);

    EXPECT_EQ(memPool.CurrentAllocs(), 0u);

}



TEST_F(MemPoolTTest_22, ClearResetsCurrentAllocsToZero_22) {

    memPool.Alloc();

    memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0u);

}
