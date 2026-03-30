#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/goo/gmem.h"

#include <cstdlib>



// Mocking gfree and grealloc functions to control their behavior in tests

extern "C" {

    void gfree(void* p) { std::free(p); }

    void* grealloc(void* p, size_t newSize, bool checkoverflow = false) {

        return std::realloc(p, newSize);

    }



    // Mocking gfree and grealloc to track their calls

    MOCK_METHOD1(mock_gfree, void(void*));

    MOCK_METHOD3(mock_grealloc, void*(void*, size_t, bool));



    void* (*original_gfree)(void*) = nullptr;

    void* (*original_grealloc)(void*, size_t, bool) = nullptr;



    void setupMocks() {

        original_gfree = gfree;

        gfree = [](void* p) { mock_gfree(p); };



        original_grealloc = grealloc;

        grealloc = [](void* p, size_t newSize, bool checkoverflow) { return mock_grealloc(p, newSize, checkoverflow); };

    }



    void teardownMocks() {

        gfree = original_gfree;

        grealloc = original_grealloc;

    }

}



using ::testing::_;

using ::testing::Return;



class GreallocnTest : public ::testing::Test {

protected:

    void SetUp() override {

        setupMocks();

    }



    void TearDown() override {

        teardownMocks();

    }

};



TEST_F(GreallocnTest_15, NormalOperation_ReallocatesMemory_15) {

    int* ptr = static_cast<int*>(std::malloc(10 * sizeof(int)));

    ASSERT_NE(ptr, nullptr);



    EXPECT_CALL(mock_gfree, _).Times(0);

    EXPECT_CALL(mock_grealloc, _(ptr, 20 * sizeof(int), false)).WillOnce(Return(static_cast<void*>(std::realloc(ptr, 20 * sizeof(int)))));



    void* result = greallocn(ptr, 20, sizeof(int));

    ASSERT_NE(result, nullptr);



    std::free(result);

}



TEST_F(GreallocnTest_15, CountZero_FreesMemory_ReturnsNullptr_15) {

    int* ptr = static_cast<int*>(std::malloc(10 * sizeof(int)));

    ASSERT_NE(ptr, nullptr);



    EXPECT_CALL(mock_gfree, _(ptr)).Times(1);

    EXPECT_CALL(mock_grealloc, _, _).Times(0);



    void* result = greallocn(ptr, 0, sizeof(int));

    EXPECT_EQ(result, nullptr);

}



TEST_F(GreallocnTest_15, NegativeCount_Aborts_15) {

    int* ptr = static_cast<int*>(std::malloc(10 * sizeof(int)));

    ASSERT_NE(ptr, nullptr);



    EXPECT_CALL(mock_gfree, _).Times(0);

    EXPECT_CALL(mock_grealloc, _, _).Times(0);



    EXPECT_DEATH(greallocn(ptr, -1, sizeof(int)), "Bogus memory allocation size");

}



TEST_F(GreallocnTest_15, SizeZero_Aborts_15) {

    int* ptr = static_cast<int*>(std::malloc(10 * sizeof(int)));

    ASSERT_NE(ptr, nullptr);



    EXPECT_CALL(mock_gfree, _).Times(0);

    EXPECT_CALL(mock_grealloc, _, _).Times(0);



    EXPECT_DEATH(greallocn(ptr, 10, 0), "Bogus memory allocation size");

}



TEST_F(GreallocnTest_15, OverflowCheck_ReturnsNullptr_15) {

    int* ptr = static_cast<int*>(std::malloc(10 * sizeof(int)));

    ASSERT_NE(ptr, nullptr);



    EXPECT_CALL(mock_gfree, _(ptr)).Times(1);

    EXPECT_CALL(mock_grealloc, _, _).Times(0);



    void* result = greallocn(ptr, INT_MAX, 2, true); // This should cause an overflow

    EXPECT_EQ(result, nullptr);

}
