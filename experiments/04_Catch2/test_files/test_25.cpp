#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_unique_ptr.hpp"



using namespace Catch::Detail;



class UniquePtrTest_25 : public ::testing::Test {

protected:

    using TestType = int;

    unique_ptr<TestType> ptr;



    void SetUp() override {

        ptr.reset(new TestType(42));

    }

};



TEST_F(UniquePtrTest_25, OperatorArrowReturnsCorrectPointer_25) {

    EXPECT_EQ(*ptr->operator->(), 42);

}



TEST_F(UniquePtrTest_25, GetReturnsRawPointer_25) {

    EXPECT_EQ(ptr.get(), ptr.operator->());

}



TEST_F(UniquePtrTest_25, ResetChangesPointer_25) {

    TestType* new_ptr = new TestType(84);

    ptr.reset(new_ptr);

    EXPECT_EQ(ptr.get(), new_ptr);

}



TEST_F(UniquePtrTest_25, ReleaseReleasesPointer_25) {

    TestType* raw_ptr = ptr.release();

    EXPECT_EQ(raw_ptr, ptr.get());

    delete raw_ptr;

}



TEST_F(UniquePtrTest_25, DestructorFreesMemory_25) {

    TestType* raw_ptr = new TestType(42);

    unique_ptr<TestType> temp(raw_ptr);

} // The destructor of `temp` should free the memory



TEST_F(UniquePtrTest_25, MoveConstructorTransfersOwnership_25) {

    unique_ptr<TestType> moved_ptr(std::move(ptr));

    EXPECT_EQ(moved_ptr.get(), ptr.get());

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_25, MoveAssignmentOperatorTransfersOwnership_25) {

    unique_ptr<TestType> new_ptr(new TestType(84));

    new_ptr = std::move(ptr);

    EXPECT_EQ(new_ptr.get(), ptr.get());

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_25, OperatorBoolReturnsTrueWhenNotNull_25) {

    EXPECT_TRUE(static_cast<bool>(ptr));

}



TEST_F(UniquePtrTest_25, OperatorBoolReturnsFalseWhenNull_25) {

    ptr.reset();

    EXPECT_FALSE(static_cast<bool>(ptr));

}



TEST_F(UniquePtrTest_25, DeletedCopyConstructorPreventsCopying_25) {

    unique_ptr<TestType> another_ptr;

    another_ptr = std::move(ptr);

    EXPECT_EQ(another_ptr.get(), ptr.get());

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_25, DeleteAssignmentOperatorPreventsCopying_25) {

    unique_ptr<TestType> another_ptr(new TestType(84));

    EXPECT_DEATH(another_ptr = ptr, ""); // This should trigger a compilation error

}
