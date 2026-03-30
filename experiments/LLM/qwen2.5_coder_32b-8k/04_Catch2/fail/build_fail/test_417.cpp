#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;

using namespace testing;



class OptionalTest_417 : public Test {

protected:

    Optional<int> emptyOptional;

    Optional<int> filledOptional;



    void SetUp() override {

        filledOptional = Optional<int>(42);

    }

};



TEST_F(OptionalTest_417, DefaultConstructorCreatesEmptyOptional_417) {

    EXPECT_TRUE(emptyOptional.none());

}



TEST_F(OptionalTest_417, ValueConstructorCreatesFilledOptional_417) {

    EXPECT_FALSE(filledOptional.none());

    EXPECT_EQ(*filledOptional, 42);

}



TEST_F(OptionalTest_417, CopyConstructorCopiesValue_417) {

    Optional<int> copiedOptional = filledOptional;

    EXPECT_FALSE(copiedOptional.none());

    EXPECT_EQ(*copiedOptional, *filledOptional);

}



TEST_F(OptionalTest_417, MoveConstructorMovesValue_417) {

    Optional<int> movedOptional = std::move(filledOptional);

    EXPECT_FALSE(movedOptional.none());

    EXPECT_EQ(*movedOptional, 42);

}



TEST_F(OptionalTest_417, CopyAssignmentAssignsValue_417) {

    emptyOptional = filledOptional;

    EXPECT_FALSE(emptyOptional.none());

    EXPECT_EQ(*emptyOptional, *filledOptional);

}



TEST_F(OptionalTest_417, MoveAssignmentMovesValue_417) {

    Optional<int> newFilledOptional(99);

    newFilledOptional = std::move(filledOptional);

    EXPECT_FALSE(newFilledOptional.none());

    EXPECT_EQ(*newFilledOptional, 42);

}



TEST_F(OptionalTest_417, ResetClearsValue_417) {

    filledOptional.reset();

    EXPECT_TRUE(filledOptional.none());

}



TEST_F(OptionalTest_417, DereferenceOperatorReturnsValue_417) {

    EXPECT_EQ(*filledOptional, 42);

}



TEST_F(OptionalTest_417, ArrowOperatorPointsToValue_417) {

    EXPECT_EQ(*(filledOptional.operator->()), 42);

}



TEST_F(OptionalTest_417, ValueOrReturnsStoredValueWhenPresent_417) {

    EXPECT_EQ(filledOptional.valueOr(0), 42);

}



TEST_F(OptionalTest_417, ValueOrDefaultReturnsDefaultValueWhenEmpty_417) {

    EXPECT_EQ(emptyOptional.valueOr(0), 0);

}



TEST_F(OptionalTest_417, SomeReturnsTrueForFilledOptional_417) {

    EXPECT_TRUE(filledOptional.some());

}



TEST_F(OptionalTest_417, NoneReturnsFalseForFilledOptional_417) {

    EXPECT_FALSE(filledOptional.none());

}



TEST_F(OptionalTest_417, NotOperatorReturnsFalseForFilledOptional_417) {

    EXPECT_FALSE(!filledOptional);

}



TEST_F(OptionalTest_417, BoolCastReturnsTrueForFilledOptional_417) {

    EXPECT_TRUE(static_cast<bool>(filledOptional));

}
