#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"



using namespace Catch::Detail;



// Test fixture for unique_ptr tests

class UniquePtrTest_31 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple utility function test

};



TEST_F(UniquePtrTest_31, MakeUniqueCreatesValidPointer_31) {

    auto ptr = make_unique<int>(42);

    EXPECT_NE(ptr.get(), nullptr);

    EXPECT_EQ(*ptr, 42);

}



TEST_F(UniquePtrTest_31, MakeUniqueWithMultipleArgsCreatesValidPointer_31) {

    struct TestStruct { int a; double b; };

    auto ptr = make_unique<TestStruct>(42, 3.14);

    EXPECT_NE(ptr.get(), nullptr);

    EXPECT_EQ(ptr->a, 42);

    EXPECT_DOUBLE_EQ(ptr->b, 3.14);

}



TEST_F(UniquePtrTest_31, MakeUniqueWithNoArgsCreatesValidPointer_31) {

    struct DefaultConstructible { int value = 0; };

    auto ptr = make_unique<DefaultConstructible>();

    EXPECT_NE(ptr.get(), nullptr);

    EXPECT_EQ(ptr->value, 0);

}



TEST_F(UniquePtrTest_31, MakeUniqueWithArrayCreatesValidPointer_31) {

    auto arrPtr = Catch::Detail::make_unique<int[]>(5);

    for (int i = 0; i < 5; ++i) {

        arrPtr[i] = i;

        EXPECT_EQ(arrPtr[i], i);

    }

}
