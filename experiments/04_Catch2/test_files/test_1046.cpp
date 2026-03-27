#include <gtest/gtest.h>

#include "catch2/internal/catch_unique_ptr.hpp"



using Catch::Detail::unique_ptr;



class UniquePtrTest_1046 : public ::testing::Test {

protected:

    using TestType = int;

};



TEST_F(UniquePtrTest_1046, DefaultConstructorSetsNullptr_1046) {

    unique_ptr<TestType> ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_1046, PointerConstructorSetsCorrectPointer_1046) {

    TestType* rawPtr = new TestType();

    unique_ptr<TestType> ptr(rawPtr);

    EXPECT_EQ(ptr.get(), rawPtr);

}



TEST_F(UniquePtrTest_1046, MoveConstructorTransfersOwnership_1046) {

    TestType* rawPtr = new TestType();

    unique_ptr<TestType> original(rawPtr);

    unique_ptr<TestType> moved(std::move(original));

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_1046, DeleteCopyConstructor_1046) {

    unique_ptr<TestType> ptr(new TestType());

    EXPECT_FALSE((std::is_copy_constructible<decltype(ptr)>::value));

}



TEST_F(UniquePtrTest_1046, MoveAssignmentTransfersOwnership_1046) {

    TestType* rawPtr = new TestType();

    unique_ptr<TestType> original(rawPtr);

    unique_ptr<TestType> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.get(), rawPtr);

    EXPECT_EQ(original.get(), nullptr);

}



TEST_F(UniquePtrTest_1046, DeleteCopyAssignment_1046) {

    unique_ptr<TestType> ptr(new TestType());

    EXPECT_FALSE((std::is_copy_assignable<decltype(ptr)>::value));

}



TEST_F(UniquePtrTest_1046, DestructorDeletesPointer_1046) {

    bool deleted = false;

    auto deleter = [&deleted]() { deleted = true; };

    struct Deletable : public TestType {

        std::function<void()> deleter;

        ~Deletable() override { deleter(); }

    };



    unique_ptr<Deletable> ptr(new Deletable{deleter});

    EXPECT_FALSE(deleted);

    ptr.reset();

    EXPECT_TRUE(deleted);

}



TEST_F(UniquePtrTest_1046, ResetReplacesPointerAndDeletesOld_1046) {

    bool deleted = false;

    auto deleter = [&deleted]() { deleted = true; };

    struct Deletable : public TestType {

        std::function<void()> deleter;

        ~Deletable() override { deleter(); }

    };



    unique_ptr<Deletable> ptr(new Deletable{deleter});

    EXPECT_FALSE(deleted);

    ptr.reset(new Deletable{deleter});

    EXPECT_TRUE(deleted);

}



TEST_F(UniquePtrTest_1046, ReleaseReturnsAndClearsPointer_1046) {

    TestType* rawPtr = new TestType();

    unique_ptr<TestType> ptr(rawPtr);

    TestType* releasedPtr = ptr.release();

    EXPECT_EQ(releasedPtr, rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_1046, DereferenceOperatorsWorkCorrectly_1046) {

    int value = 42;

    unique_ptr<int> ptr(&value);

    EXPECT_EQ(*ptr, value);

    EXPECT_EQ(ptr->operator*(), value);

}



TEST_F(UniquePtrTest_1046, BoolConversionReflectsNullState_1046) {

    unique_ptr<TestType> nullPtr;

    unique_ptr<TestType> nonNullPtr(new TestType());

    EXPECT_FALSE(static_cast<bool>(nullPtr));

    EXPECT_TRUE(static_cast<bool>(nonNullPtr));

}
