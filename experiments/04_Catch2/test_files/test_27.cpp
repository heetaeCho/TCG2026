#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch::Detail;



class unique_ptrTest : public ::testing::Test {

protected:

    unique_ptr<int> ptr;

};



TEST_F(unique_ptrTest_27, DefaultConstructorInitializesToNullptr_27) {

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(unique_ptrTest_27, PointerConstructorSetsCorrectPointer_27) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(*ptr.get(), 42);

    delete rawPtr; // Ensure no double delete

}



TEST_F(unique_ptrTest_27, MoveConstructorTransfersOwnership_27) {

    int* rawPtr = new int(42);

    unique_ptr<int> original(rawPtr);

    unique_ptr<int> moved(std::move(original));

    EXPECT_EQ(*moved.get(), 42);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(unique_ptrTest_27, MoveAssignmentOperatorTransfersOwnership_27) {

    int* rawPtr = new int(42);

    unique_ptr<int> original(rawPtr);

    ptr = std::move(original);

    EXPECT_EQ(*ptr.get(), 42);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(unique_ptrTest_27, ResetReleasesPointerAndSetsToNullptr_27) {

    int* rawPtr = new int(42);

    ptr.reset(rawPtr);

    ptr.reset();

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(unique_ptrTest_27, ReleaseReturnsPointerAndSetsToNullptr_27) {

    int* rawPtr = new int(42);

    ptr.reset(rawPtr);

    int* releasedPtr = ptr.release();

    EXPECT_EQ(releasedPtr, rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);

    delete releasedPtr; // Clean up

}



TEST_F(unique_ptrTest_27, DereferenceOperatorWorksCorrectly_27) {

    int* rawPtr = new int(42);

    ptr.reset(rawPtr);

    EXPECT_EQ(*ptr, 42);

}



TEST_F(unique_ptrTest_27, ArrowOperatorWorksCorrectly_27) {

    struct TestStruct { int value; };

    TestStruct* rawPtr = new TestStruct{42};

    unique_ptr<TestStruct> ptr(rawPtr);

    EXPECT_EQ(ptr->value, 42);

}



TEST_F(unique_ptrTest_27, BoolConversionOperatorWorksCorrectly_27) {

    EXPECT_FALSE(static_cast<bool>(ptr));

    int* rawPtr = new int(42);

    ptr.reset(rawPtr);

    EXPECT_TRUE(static_cast<bool>(ptr));

}
