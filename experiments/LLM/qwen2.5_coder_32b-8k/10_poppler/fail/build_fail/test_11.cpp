#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "TestProjects/poppler/goo/gmem.h"

}



class GreallocTest_11 : public ::testing::Test {

protected:

    void *ptr;

    

    void SetUp() override {

        ptr = nullptr;

    }

    

    void TearDown() override {

        if (ptr) {

            gfree(ptr);

            ptr = nullptr;

        }

    }

};



TEST_F(GreallocTest_11, AllocateMemory_11) {

    size_t size = 10;

    ptr = grealloc(nullptr, size);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(GreallocTest_11, ReallocateMemory_11) {

    size_t initial_size = 10;

    size_t new_size = 20;

    ptr = grealloc(nullptr, initial_size);

    void *new_ptr = grealloc(ptr, new_size);

    EXPECT_NE(new_ptr, nullptr);

    ptr = new_ptr; // Update ptr to the new address

}



TEST_F(GreallocTest_11, FreeMemory_11) {

    size_t size = 10;

    ptr = grealloc(nullptr, size);

    void *freed_ptr = grealloc(ptr, 0);

    EXPECT_EQ(freed_ptr, nullptr);

}



TEST_F(GreallocTest_11, AllocateZeroSize_11) {

    size_t size = 0;

    ptr = grealloc(nullptr, size);

    EXPECT_EQ(ptr, nullptr);

}



TEST_F(GreallocTest_11, ReallocateToZeroSize_11) {

    size_t initial_size = 10;

    ptr = grealloc(nullptr, initial_size);

    void *freed_ptr = grealloc(ptr, 0);

    EXPECT_EQ(freed_ptr, nullptr);

}



TEST_F(GreallocTest_11, AllocateLargeMemory_11) {

    size_t large_size = 1024 * 1024; // 1MB

    ptr = grealloc(nullptr, large_size);

    EXPECT_NE(ptr, nullptr);

}
