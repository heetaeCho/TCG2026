#include <gtest/gtest.h>

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch::Detail;



class UniquePtrTest_29 : public ::testing::Test {

protected:

    unique_ptr<int> ptr;

};



TEST_F(UniquePtrTest_29, DefaultConstructorSetsNullptr_29) {

    unique_ptr<int> defaultConstructedPtr;

    EXPECT_FALSE(static_cast<bool>(defaultConstructedPtr));

}



TEST_F(UniquePtrTest_29, PointerConstructorSetsCorrectPointer_29) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_TRUE(static_cast<bool>(ptr));

    EXPECT_EQ(*ptr, 42);

    delete rawPtr; // To prevent memory leak in case of test failure

}



TEST_F(UniquePtrTest_29, MoveConstructorTransfersOwnership_29) {

    unique_ptr<int> original(new int(10));

    unique_ptr<int> moved(std::move(original));

    EXPECT_TRUE(static_cast<bool>(moved));

    EXPECT_FALSE(static_cast<bool>(original));

    EXPECT_EQ(*moved, 10);

}



TEST_F(UniquePtrTest_29, DeletedCopyConstructorPreventsCopying_29) {

    unique_ptr<int> original(new int(5));

    // This should not compile

    // unique_ptr<int> copy = original;

}



TEST_F(UniquePtrTest_29, MoveAssignmentOperatorTransfersOwnership_29) {

    unique_ptr<int> original(new int(15));

    unique_ptr<int> moved;

    moved = std::move(original);

    EXPECT_TRUE(static_cast<bool>(moved));

    EXPECT_FALSE(static_cast<bool>(original));

    EXPECT_EQ(*moved, 15);

}



TEST_F(UniquePtrTest_29, DeletedCopyAssignmentOperatorPreventsCopying_29) {

    unique_ptr<int> original(new int(7));

    unique_ptr<int> other(new int(8));

    // This should not compile

    // moved = original;

}



TEST_F(UniquePtrTest_29, DestructorReleasesMemory_29) {

    bool isDeleted = false;

    struct Deletable { ~Deletable() { isDeleted = true; } };

    {

        unique_ptr<Deletable> ptr(new Deletable);

    }

    EXPECT_TRUE(isDeleted);

}



TEST_F(UniquePtrTest_29, DereferenceOperatorsWorkCorrectly_29) {

    int value = 42;

    unique_ptr<int> ptr(&value);

    *ptr = 84;

    EXPECT_EQ(*ptr, 84);

    EXPECT_EQ(ptr->operator*(), 84);

}



TEST_F(UniquePtrTest_29, GetReturnsRawPointer_29) {

    int value = 100;

    unique_ptr<int> ptr(&value);

    EXPECT_EQ(ptr.get(), &value);

}



TEST_F(UniquePtrTest_29, ResetSetsNewPointer_29) {

    unique_ptr<int> ptr(new int(20));

    ptr.reset(new int(30));

    EXPECT_TRUE(static_cast<bool>(ptr));

    EXPECT_EQ(*ptr, 30);

}



TEST_F(UniquePtrTest_29, ReleaseTransfersOwnershipAndReturnsRawPointer_29) {

    unique_ptr<int> ptr(new int(50));

    int* rawPtr = ptr.release();

    EXPECT_FALSE(static_cast<bool>(ptr));

    EXPECT_NE(rawPtr, nullptr);

    delete rawPtr;

}



TEST_F(UniquePtrTest_29, BoolConversionReflectsValidity_29) {

    unique_ptr<int> validPtr(new int(10));

    unique_ptr<int> invalidPtr;

    EXPECT_TRUE(static_cast<bool>(validPtr));

    EXPECT_FALSE(static_cast<bool>(invalidPtr));

}
