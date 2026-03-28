#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest_403 : public ::testing::Test {

protected:

    Optional<int> emptyOptional;

    Optional<int> nonEmptyOptional;

    

    void SetUp() override {

        nonEmptyOptional = Optional<int>(42);

    }

};



TEST_F(OptionalTest_403, DefaultConstructorCreatesEmpty_403) {

    EXPECT_FALSE(emptyOptional.some());

    EXPECT_TRUE(emptyOptional.none());

}



TEST_F(OptionalTest_403, ValueConstructorCreatesNonEmpty_403) {

    EXPECT_TRUE(nonEmptyOptional.some());

    EXPECT_FALSE(nonEmptyOptional.none());

}



TEST_F(OptionalTest_403, CopyConstructorCopiesValue_403) {

    Optional<int> copy = nonEmptyOptional;

    EXPECT_EQ(*copy, *nonEmptyOptional);

}



TEST_F(OptionalTest_403, MoveConstructorMovesValue_403) {

    Optional<int> moved = std::move(nonEmptyOptional);

    EXPECT_TRUE(moved.some());

    EXPECT_FALSE(nonEmptyOptional.some()); // Moved from object should be empty

}



TEST_F(OptionalTest_403, CopyAssignmentOperatorCopiesValue_403) {

    Optional<int> copy;

    copy = nonEmptyOptional;

    EXPECT_EQ(*copy, *nonEmptyOptional);

}



TEST_F(OptionalTest_403, MoveAssignmentOperatorMovesValue_403) {

    Optional<int> moved;

    moved = std::move(nonEmptyOptional);

    EXPECT_TRUE(moved.some());

    EXPECT_FALSE(nonEmptyOptional.some()); // Moved from object should be empty

}



TEST_F(OptionalTest_403, ResetSetsToEmpty_403) {

    nonEmptyOptional.reset();

    EXPECT_FALSE(nonEmptyOptional.some());

    EXPECT_TRUE(nonEmptyOptional.none());

}



TEST_F(OptionalTest_403, DereferenceOperatorReturnsCorrectValue_403) {

    EXPECT_EQ(*nonEmptyOptional, 42);

}



TEST_F(OptionalTest_403, ArrowOperatorPointsToCorrectValue_403) {

    EXPECT_EQ(nonEmptyOptional->operator int(), 42);

}



TEST_F(OptionalTest_403, ValueOrReturnsStoredValueWhenSome_403) {

    EXPECT_EQ(nonEmptyOptional.valueOr(99), 42);

}



TEST_F(OptionalTest_403, ValueOrReturnsDefaultValueWhenNone_403) {

    EXPECT_EQ(emptyOptional.valueOr(99), 99);

}



TEST_F(OptionalTest_403, BoolConversionEvaluatesToTrueWhenSome_403) {

    EXPECT_TRUE(static_cast<bool>(nonEmptyOptional));

}



TEST_F(OptionalTest_403, BoolConversionEvaluatesToFalseWhenNone_403) {

    EXPECT_FALSE(static_cast<bool>(emptyOptional));

}



TEST_F(OptionalTest_403, NotOperatorEvaluatesToTrueWhenNone_403) {

    EXPECT_TRUE(!emptyOptional);

}



TEST_F(OptionalTest_403, NotOperatorEvaluatesToFalseWhenSome_403) {

    EXPECT_FALSE(!nonEmptyOptional);

}
