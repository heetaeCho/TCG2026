#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_17 : public ::testing::Test {

protected:

    MemPoolT<sizeof(int)> memPool;

};



TEST_F(MemPoolTTest_17, ItemSize_ReturnsCorrectValue_17) {

    EXPECT_EQ(memPool.ItemSize(), sizeof(int));

}



TEST_F(MemPoolTTest_17, CurrentAllocs_ReturnsZeroInitially_17) {

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_17, Untracked_ReturnsZeroInitially_17) {

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_17, Alloc_IncreasesCurrentAllocs_17) {

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), 1);

}



TEST_F(MemPoolTTest_17, Free_DecreasesCurrentAllocs_17) {

    void* item = memPool.Alloc();

    memPool.Free(item);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_17, Free_NullPointer_NoEffect_17) {

    memPool.Free(nullptr);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_17, Clear_ResetsCurrentAllocs_17) {

    memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_17, Trace_DoesNotThrowException_17) {

    EXPECT_NO_THROW(memPool.Trace("test"));

}



TEST_F(MemPoolTTest_17, SetTracked_DoesNotThrowException_17) {

    EXPECT_NO_THROW(memPool.SetTracked());

}
