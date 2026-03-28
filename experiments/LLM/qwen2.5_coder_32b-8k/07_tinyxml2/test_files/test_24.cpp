#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MemPoolTTest_24 : public ::testing::Test {

protected:

    MemPoolT<16> memPool;  // Using a template size of 16 for testing purposes

};



TEST_F(MemPoolTTest_24, ItemSizeReturnsCorrectValue_24) {

    EXPECT_EQ(memPool.ItemSize(), 16);

}



TEST_F(MemPoolTTest_24, CurrentAllocsInitiallyZero_24) {

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_24, UntrackedInitiallyZero_24) {

    EXPECT_EQ(memPool.Untracked(), 0);

}



TEST_F(MemPoolTTest_24, AllocIncreasesCurrentAllocs_24) {

    memPool.Alloc();

    EXPECT_EQ(memPool.CurrentAllocs(), 1);

}



TEST_F(MemPoolTTest_24, FreeDecreasesCurrentAllocs_24) {

    void* item = memPool.Alloc();

    memPool.Free(item);

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

}



TEST_F(MemPoolTTest_24, SetTrackedDecreasesUntrackedCount_24) {

    void* item = memPool.Alloc();

    memPool.SetTracked();

    EXPECT_EQ(memPool.Untracked(), 1);

    memPool.Free(item);

}



TEST_F(MemPoolTTest_24, ClearResetsCurrentAllocsAndMaxAllocs_24) {

    memPool.Alloc();

    memPool.Clear();

    EXPECT_EQ(memPool.CurrentAllocs(), 0);

    // Assuming MaxAllocs is reset as well

    // If not, this test should be adjusted accordingly

}



TEST_F(MemPoolTTest_24, FreeNullPointerDoesNotThrow_24) {

    EXPECT_NO_THROW(memPool.Free(nullptr));

}



// Additional tests for boundary conditions and error cases can be added if more details are available about expected behavior.
