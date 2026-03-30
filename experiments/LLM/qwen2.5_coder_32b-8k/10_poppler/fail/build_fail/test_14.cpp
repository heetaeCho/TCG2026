#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/goo/gmem.h"



class GMemTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(GMemTest_14, NormalAllocation_14) {

    int width = 10;

    int height = 5;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, size);

    ASSERT_NE(ptr, nullptr);

    free(ptr); // Clean up allocated memory

}



TEST_F(GMemTest_14, ZeroWidth_ReturnsNullptr_14) {

    int width = 0;

    int height = 5;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_14, ZeroHeight_ReturnsNullptr_14) {

    int width = 10;

    int height = 0;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_14, NegativeWidth_ReturnsNullptrAndFputs_14) {

    int width = -10;

    int height = 5;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_14, NegativeHeight_ReturnsNullptrAndFputs_14) {

    int width = 10;

    int height = -5;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_14, NonPositiveSize_ReturnsNullptrAndFputs_14) {

    int width = 10;

    int height = 5;

    int size = 0; // Invalid size

    void* ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);



    size = -8; // Negative size

    ptr = gmallocn3(width, height, size);

    ASSERT_EQ(ptr, nullptr);

}



TEST_F(GMemTest_14, OverflowCheck_ReturnsNullptr_14) {

    int width = 0x7FFFFFFF;

    int height = 2;

    int size = 8; // sizeof(double)

    void* ptr = gmallocn3(width, height, true); // Enable overflow check

    ASSERT_EQ(ptr, nullptr);

}
