#include <gtest/gtest.h>

#include "gmem.h"



class GMemTest_9 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(GMemTest_9, AllocateZeroSize_ReturnsNullptr_9) {

    void* ptr = gmalloc(0);

    EXPECT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_9, AllocateNonZeroSize_ReturnsNonNullptr_9) {

    void* ptr = gmalloc(1);

    EXPECT_NE(ptr, nullptr);

    std::free(ptr); // Clean up

}



TEST_F(GMemTest_9, AllocateLargeSize_ReturnsNonNullptr_9) {

    size_t largeSize = 1024 * 1024; // 1 MB

    void* ptr = gmalloc(largeSize);

    EXPECT_NE(ptr, nullptr);

    std::free(ptr); // Clean up

}



TEST_F(GMemTest_9, AllocateWithCheckOverflowZeroSize_ReturnsNullptr_9) {

    void* ptr = gmalloc(0, true);

    EXPECT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_9, AllocateWithCheckOverflowNonZeroSize_ReturnsNonNullptr_9) {

    void* ptr = gmalloc(1, true);

    EXPECT_NE(ptr, nullptr);

    std::free(ptr); // Clean up

}
