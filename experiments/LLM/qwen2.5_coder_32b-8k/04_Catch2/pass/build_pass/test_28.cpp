#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_unique_ptr.hpp"



using namespace Catch::Detail;



class UniquePtrTest_28 : public ::testing::Test {

protected:

    int* ptr;

    unique_ptr<int> uPtr;



    void SetUp() override {

        ptr = new int(42);

        uPtr.reset(ptr);

    }



    void TearDown() override {

        delete ptr;

    }

};



TEST_F(UniquePtrTest_28, ReleaseReturnsPointer_28) {

    EXPECT_EQ(uPtr.release(), ptr);

    EXPECT_EQ(uPtr.get(), nullptr);

}



TEST_F(UniquePtrTest_28, ResetReleasesAndSetsNewPointer_28) {

    int* newPtr = new int(100);

    uPtr.reset(newPtr);

    EXPECT_NE(uPtr.get(), ptr);

    EXPECT_EQ(*uPtr, 100);

    delete newPtr;

}



TEST_F(UniquePtrTest_28, ResetWithNullReleasesPointer_28) {

    uPtr.reset(nullptr);

    EXPECT_EQ(uPtr.get(), nullptr);

}



TEST_F(UniquePtrTest_28, GetReturnsCurrentPointer_28) {

    EXPECT_EQ(uPtr.get(), ptr);

}



TEST_F(UniquePtrTest_28, OperatorStarDereferencesPointer_28) {

    EXPECT_EQ(*uPtr, 42);

}



TEST_F(UniquePtrTest_28, OperatorArrowAccessesMembers_28) {

    struct TestStruct { int value; };

    unique_ptr<TestStruct> testPtr(new TestStruct{10});

    EXPECT_EQ(testPtr->value, 10);

}



TEST_F(UniquePtrTest_28, BoolConversionEvaluatesCorrectly_28) {

    EXPECT_TRUE(uPtr);

    uPtr.reset(nullptr);

    EXPECT_FALSE(uPtr);

}



TEST_F(UniquePtrTest_28, MoveConstructorTransfersOwnership_28) {

    unique_ptr<int> movedPtr = std::move(uPtr);

    EXPECT_EQ(movedPtr.get(), ptr);

    EXPECT_EQ(uPtr.get(), nullptr);

}



TEST_F(UniquePtrTest_28, MoveAssignmentOperatorTransfersOwnership_28) {

    unique_ptr<int> movedPtr;

    movedPtr = std::move(uPtr);

    EXPECT_EQ(movedPtr.get(), ptr);

    EXPECT_EQ(uPtr.get(), nullptr);

}
