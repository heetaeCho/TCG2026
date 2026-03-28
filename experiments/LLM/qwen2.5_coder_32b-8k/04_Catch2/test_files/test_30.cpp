#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_unique_ptr.hpp"



using namespace Catch::Detail;



class UniquePtrTest_30 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any, can go here.

    }



    void TearDown() override {

        // Teardown code, if any, can go here.

    }

};



TEST_F(UniquePtrTest_30, DefaultConstructorInitializesNullptr_30) {

    unique_ptr<int> ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_30, PointerConstructorInitializesPointer_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(ptr.get(), rawPtr);

}



TEST_F(UniquePtrTest_30, MoveConstructorTransfersOwnership_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> original(rawPtr);

    unique_ptr<int> moved(std::move(original));

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_30, MoveAssignmentOperatorTransfersOwnership_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> original(rawPtr);

    unique_ptr<int> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_30, ResetReleasesOldPointerAndTakesNewOne_30) {

    int* rawPtr1 = new int(42);

    unique_ptr<int> ptr(rawPtr1);

    int* rawPtr2 = new int(84);

    ptr.reset(rawPtr2);

    EXPECT_EQ(ptr.get(), rawPtr2);

}



TEST_F(UniquePtrTest_30, ResetWithNullReleasesPointer_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    ptr.reset();

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_30, ReleaseReturnsRawPointerAndResets_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    int* releasedPtr = ptr.release();

    EXPECT_EQ(releasedPtr, rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_30, DereferenceOperatorReturnsReferenceToData_30) {

    int value = 42;

    unique_ptr<int> ptr(&value);

    EXPECT_EQ(*ptr, value);

}



TEST_F(UniquePtrTest_30, ArrowOperatorReturnsPointerToData_30) {

    struct TestStruct { int data; };

    TestStruct* rawPtr = new TestStruct{42};

    unique_ptr<TestStruct> ptr(rawPtr);

    EXPECT_EQ(ptr->data, 42);

}



TEST_F(UniquePtrTest_30, BoolConversionOperatorReturnsTrueIfNotNull_30) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_TRUE(static_cast<bool>(ptr));

}



TEST_F(UniquePtrTest_30, BoolConversionOperatorReturnsFalseIfNull_30) {

    unique_ptr<int> ptr;

    EXPECT_FALSE(static_cast<bool>(ptr));

}
