#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest : public ::testing::Test {

protected:

    MemPoolT<32> memPool;

};



TEST_F(MemPoolTTest_23, TraceOutputsCorrectFormat_23) {

    testing::internal::CaptureStdout();

    memPool.Trace("TestPool");

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, testing::MatchesRegex("Mempool TestPool watermark=\\d+ \\[\\dk\\] current=0 size=32 nAlloc=0 blocks=0\n"));

}



TEST_F(MemPoolTTest_23, CurrentAllocsReturnsZeroInitially_23) {

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_23, AllocIncreasesCurrentAllocs_23) {

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), 1);

}



TEST_F(MemPoolTTest_23, FreeDecreasesCurrentAllocs_23) {

    void* alloc = memPool.Alloc();

    memPool.Free(alloc);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_23, AllocAndFreeMultipleTimes_23) {

    for (int i = 0; i < 10; ++i) {

        void* alloc = memPool.Alloc();

        memPool.Free(alloc);

    }

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_23, ClearResetsCurrentAllocs_23) {

    for (int i = 0; i < 5; ++i) {

        memPool.Alloc();

    }

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_23, ItemSizeReturnsCorrectValue_23) {

    EXPECT_EQ(memPool.ItemSize(), 32);

}
