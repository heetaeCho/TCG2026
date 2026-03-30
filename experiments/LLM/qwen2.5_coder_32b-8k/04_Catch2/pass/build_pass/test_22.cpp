#include <gtest/gtest.h>

#include "catch_unique_ptr.hpp"



namespace Catch {

namespace Detail {



class UniquePtrTest_22 : public ::testing::Test {

protected:

    unique_ptr<int> ptr;

};



TEST_F(UniquePtrTest_22, DefaultConstructorInitializesNullptr_22) {

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_22, PointerConstructorSetsPointer_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(*ptr, 42);

    EXPECT_EQ(ptr.release(), rawPtr);

    delete rawPtr;

}



TEST_F(UniquePtrTest_22, MoveConstructorTransfersOwnership_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr1(rawPtr);

    unique_ptr<int> ptr2(std::move(ptr1));

    EXPECT_EQ(*ptr2, 42);

    EXPECT_EQ(ptr1.get(), nullptr);

    delete rawPtr;

}



TEST_F(UniquePtrTest_22, MoveAssignmentOperatorTransfersOwnership_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr1(rawPtr);

    unique_ptr<int> ptr2;

    ptr2 = std::move(ptr1);

    EXPECT_EQ(*ptr2, 42);

    EXPECT_EQ(ptr1.get(), nullptr);

    delete rawPtr;

}



TEST_F(UniquePtrTest_22, DeleteCopyConstructorAndAssignment_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr1(rawPtr);

    // The following lines should not compile

    // unique_ptr<int> ptr2(ptr1);  // Copy constructor deleted

    // ptr2 = ptr1;                // Copy assignment operator deleted

    delete rawPtr;

}



TEST_F(UniquePtrTest_22, ResetReleasesOldPointerAndSetsNew_22) {

    int* rawPtr1 = new int(42);

    int* rawPtr2 = new int(84);

    unique_ptr<int> ptr(rawPtr1);

    ptr.reset(rawPtr2);

    EXPECT_EQ(ptr.get(), rawPtr2);

    delete rawPtr2;

}



TEST_F(UniquePtrTest_22, ResetWithNullptrReleasesPointer_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    ptr.reset();

    EXPECT_EQ(ptr.get(), nullptr);

    // No need to delete as reset() should have deleted it

}



TEST_F(UniquePtrTest_22, ReleaseReturnsPointerAndNullifiesIt_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(ptr.release(), rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);

    delete rawPtr;

}



TEST_F(UniquePtrTest_22, BoolConversionReflectsNullState_22) {

    unique_ptr<int> ptr1;

    unique_ptr<int> ptr2(new int(42));

    EXPECT_FALSE(static_cast<bool>(ptr1));

    EXPECT_TRUE(static_cast<bool>(ptr2));

    delete ptr2.release();

}



TEST_F(UniquePtrTest_22, DereferenceOperatorsWork_22) {

    int* rawPtr = new int(42);

    unique_ptr<int> ptr(rawPtr);

    EXPECT_EQ(*ptr, 42);

    EXPECT_EQ(ptr.get(), rawPtr);

    delete rawPtr;

}



} // namespace Detail

} // namespace Catch
