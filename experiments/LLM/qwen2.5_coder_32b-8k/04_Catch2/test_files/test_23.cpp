#include <gtest/gtest.h>

#include "catch2/internal/catch_unique_ptr.hpp"



using Catch::Detail::unique_ptr;



class UniquePtrTest_23 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(UniquePtrTest_23, DefaultConstructorInitializesToNullptr_23) {

    unique_ptr<int> ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_23, PointerConstructorSetsPointer_23) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(ptr.get(), rawPtr);

}



TEST_F(UniquePtrTest_23, MoveConstructorTransfersOwnership_23) {

    unique_ptr<int> original(new int(42));

    unique_ptr<int> moved(std::move(original));

    EXPECT_NE(moved.get(), nullptr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_23, DeletedCopyConstructor_23) {

    unique_ptr<int> ptr1(new int(42));

    // This should not compile: unique_ptr<int> ptr2 = ptr1;

    SUCCEED(); // If the above line is commented out, this test succeeds

}



TEST_F(UniquePtrTest_23, MoveAssignmentTransfersOwnership_23) {

    unique_ptr<int> original(new int(42));

    unique_ptr<int> moved(nullptr);

    moved = std::move(original);

    EXPECT_NE(moved.get(), nullptr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_23, DeletedCopyAssignment_23) {

    unique_ptr<int> ptr1(new int(42));

    unique_ptr<int> ptr2(new int(0));

    // This should not compile: ptr2 = ptr1;

    SUCCEED(); // If the above line is commented out, this test succeeds

}



TEST_F(UniquePtrTest_23, DestructorFreesMemory_23) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

} // Memory should be freed here



TEST_F(UniquePtrTest_23, DereferenceOperatorWorks_23) {

    unique_ptr<int> ptr(new int(42));

    EXPECT_EQ(*ptr, 42);

}



TEST_F(UniquePtrTest_23, ArrowOperatorWorks_23) {

    struct TestStruct { int value; };

    unique_ptr<TestStruct> ptr(new TestStruct{42});

    EXPECT_EQ(ptr->value, 42);

}



TEST_F(UniquePtrTest_23, GetReturnsRawPointer_23) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(ptr.get(), rawPtr);

}



TEST_F(UniquePtrTest_23, ResetReleasesAndSetsNewPointer_23) {

    unique_ptr<int> ptr(new int(42));

    int* newRawPtr = new int(0);

    ptr.reset(newRawPtr);

    EXPECT_EQ(ptr.get(), newRawPtr);

}



TEST_F(UniquePtrTest_23, ReleaseTransfersOwnershipAndReturnsPointer_23) {

    unique_ptr<int> ptr(new int(42));

    int* rawPtr = ptr.release();

    EXPECT_NE(rawPtr, nullptr);

    EXPECT_EQ(ptr.get(), nullptr);

    delete rawPtr; // Manually delete the released pointer

}



TEST_F(UniquePtrTest_23, BoolConversionOperatorWorks_23) {

    unique_ptr<int> emptyPtr;

    unique_ptr<int> nonEmptyPtr(new int(42));

    EXPECT_FALSE(emptyPtr);

    EXPECT_TRUE(nonEmptyPtr);

}
