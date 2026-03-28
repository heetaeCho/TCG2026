#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_unique_ptr.hpp"



namespace Catch { namespace Detail {



class UniquePtrTest : public ::testing::Test {

protected:

    struct Base {};

    struct Derived : Base {};



    unique_ptr<Base> basePtr;

    unique_ptr<Derived> derivedPtr;



    void SetUp() override {

        basePtr.reset(new Base());

        derivedPtr.reset(new Derived());

    }

};



TEST_F(UniquePtrTest_21, DefaultConstructorSetsNullptr_21) {

    unique_ptr<Base> ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



TEST_F(UniquePtrTest_21, PointerConstructorInitializesPointer_21) {

    Base* rawBase = new Base();

    unique_ptr<Base> ptr(rawBase);

    EXPECT_EQ(ptr.get(), rawBase);

}



TEST_F(UniquePtrTest_21, MoveConstructorTransfersOwnership_21) {

    Derived* rawDerived = derivedPtr.release();

    unique_ptr<Base> movedPtr(std::move(derivedPtr));

    EXPECT_EQ(movedPtr.get(), rawDerived);

    EXPECT_EQ(derivedPtr.get(), nullptr);

}



TEST_F(UniquePtrTest_21, MoveAssignmentTransfersOwnership_21) {

    Base* rawBase = basePtr.release();

    unique_ptr<Base> movedPtr;

    movedPtr = std::move(basePtr);

    EXPECT_EQ(movedPtr.get(), rawBase);

    EXPECT_EQ(basePtr.get(), nullptr);

}



TEST_F(UniquePtrTest_21, MoveAssignmentFromDerivedTransfersOwnership_21) {

    Derived* rawDerived = derivedPtr.release();

    unique_ptr<Base> movedPtr;

    movedPtr = std::move(derivedPtr);

    EXPECT_EQ(movedPtr.get(), rawDerived);

    EXPECT_EQ(derivedPtr.get(), nullptr);

}



TEST_F(UniquePtrTest_21, ResetReleasesOldPointerAndSetsNew_21) {

    Base* oldBase = basePtr.release();

    Base* newBase = new Base();

    basePtr.reset(newBase);

    EXPECT_NE(basePtr.get(), oldBase);

    EXPECT_EQ(basePtr.get(), newBase);

}



TEST_F(UniquePtrTest_21, ReleaseReturnsPointerAndSetsNullptr_21) {

    Base* rawBase = basePtr.release();

    EXPECT_EQ(basePtr.get(), nullptr);

    delete rawBase; // Clean up manually since release does not delete

}



TEST_F(UniquePtrTest_21, DereferenceOperatorsWorkCorrectly_21) {

    Derived* rawDerived = new Derived();

    unique_ptr<Derived> ptr(rawDerived);

    EXPECT_EQ(&(*ptr), rawDerived);

    EXPECT_EQ(ptr.operator->(), rawDerived);

}



TEST_F(UniquePtrTest_21, BoolConversionReflectsNullStatus_21) {

    unique_ptr<Base> nullPtr;

    EXPECT_FALSE(nullPtr);



    unique_ptr<Base> nonNullPtr(new Base());

    EXPECT_TRUE(nonNullPtr);

}



}} // namespace Catch::Detail
