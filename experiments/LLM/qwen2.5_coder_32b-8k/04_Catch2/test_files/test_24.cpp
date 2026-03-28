#include <gtest/gtest.h>

#include "catch2/internal/catch_unique_ptr.hpp"



class UniquePtrTest_24 : public ::testing::Test {

protected:

    using PtrType = Catch::Detail::unique_ptr<int>;

};



TEST_F(UniquePtrTest_24, DefaultConstructorCreatesNullptr_24) {

    PtrType ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_24, PointerConstructorSetsCorrectPointer_24) {

    int* rawPtr = new int(42);

    PtrType ptr(rawPtr);

    EXPECT_EQ(ptr.get(), rawPtr);

    delete rawPtr;  // Avoid memory leak

}



TEST_F(UniquePtrTest_24, MoveConstructorTransfersOwnership_24) {

    int* rawPtr = new int(42);

    PtrType original(rawPtr);

    PtrType moved(std::move(original));

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_24, DeletedCopyConstructorPreventsCopying_24) {

    int* rawPtr = new int(42);

    PtrType original(rawPtr);

    PtrType copied(original);  // This should cause a compile-time error if uncommented

    delete rawPtr;  // Avoid memory leak

}



TEST_F(UniquePtrTest_24, MoveAssignmentTransfersOwnership_24) {

    int* rawPtr = new int(42);

    PtrType original(rawPtr);

    PtrType moved;

    moved = std::move(original);

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_24, DeletedCopyAssignmentPreventsCopying_24) {

    int* rawPtr = new int(42);

    PtrType original(rawPtr);

    PtrType copied;

    copied = original;  // This should cause a compile-time error if uncommented

    delete rawPtr;  // Avoid memory leak

}



TEST_F(UniquePtrTest_24, DestructorDeletesPointer_24) {

    bool isDeleted = false;

    struct Deletable {

        bool* flag;

        ~Deletable() { *flag = true; }

    };

    

    Deletable* rawPtr = new Deletable{&isDeleted};

    PtrType ptr(rawPtr);

    ptr.reset();

    EXPECT_TRUE(isDeleted);

}



TEST_F(UniquePtrTest_24, ResetReleasesOldPointerAndSetsNewOne_24) {

    int* oldPtr = new int(42);

    int* newPtr = new int(84);

    PtrType ptr(oldPtr);

    ptr.reset(newPtr);

    EXPECT_EQ(ptr.get(), newPtr);

    delete newPtr;  // Avoid memory leak

}



TEST_F(UniquePtrTest_24, ReleaseReturnsPointerAndResetsItself_24) {

    int* rawPtr = new int(42);

    PtrType ptr(rawPtr);

    int* releasedPtr = ptr.release();

    EXPECT_EQ(releasedPtr, rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);

    delete releasedPtr;  // Avoid memory leak

}



TEST_F(UniquePtrTest_24, BoolOperatorChecksForNullptr_24) {

    PtrType nullPtr;

    PtrType validPtr(new int(42));

    

    EXPECT_FALSE(static_cast<bool>(nullPtr));

    EXPECT_TRUE(static_cast<bool>(validPtr));

}
