#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest_415 : public ::testing::Test {

protected:

    Optional<int> emptyOpt;

    Optional<int> valueOpt;

    Optional<std::string> stringOpt;



    void SetUp() override {

        valueOpt = 42;

        stringOpt = "Hello";

    }

};



TEST_F(OptionalTest_415, DefaultConstructorCreatesEmptyOptional_415) {

    EXPECT_FALSE(static_cast<bool>(emptyOpt));

}



TEST_F(OptionalTest_415, ValueConstructorCreatesNonEmptyOptional_415) {

    EXPECT_TRUE(static_cast<bool>(valueOpt));

}



TEST_F(OptionalTest_415, CopyConstructorCopiesValue_415) {

    Optional<int> copy(valueOpt);

    EXPECT_TRUE(static_cast<bool>(copy));

    EXPECT_EQ(*copy, 42);

}



TEST_F(OptionalTest_415, MoveConstructorMovesValue_415) {

    Optional<int> moved(std::move(valueOpt));

    EXPECT_TRUE(static_cast<bool>(moved));

    EXPECT_EQ(*moved, 42);

    EXPECT_FALSE(static_cast<bool>(valueOpt)); // Original should be empty

}



TEST_F(OptionalTest_415, CopyAssignmentCopiesValue_415) {

    Optional<int> another;

    another = valueOpt;

    EXPECT_TRUE(static_cast<bool>(another));

    EXPECT_EQ(*another, 42);

}



TEST_F(OptionalTest_415, MoveAssignmentMovesValue_415) {

    Optional<int> another;

    another = std::move(valueOpt);

    EXPECT_TRUE(static_cast<bool>(another));

    EXPECT_EQ(*another, 42);

    EXPECT_FALSE(static_cast<bool>(valueOpt)); // Original should be empty

}



TEST_F(OptionalTest_415, ResetClearsOptional_415) {

    valueOpt.reset();

    EXPECT_FALSE(static_cast<bool>(valueOpt));

}



TEST_F(OptionalTest_415, DereferenceOperatorReturnsValue_415) {

    EXPECT_EQ(*valueOpt, 42);

}



TEST_F(OptionalTest_415, ArrowOperatorAccessesMembers_415) {

    EXPECT_EQ(stringOpt->length(), std::string("Hello").length());

}



TEST_F(OptionalTest_415, ValueOrReturnsDefaultValueWhenEmpty_415) {

    int defaultValue = 10;

    EXPECT_EQ(emptyOpt.valueOr(defaultValue), defaultValue);

}



TEST_F(OptionalTest_415, ValueOrReturnsStoredValueWhenNotEmpty_415) {

    int defaultValue = 10;

    EXPECT_EQ(valueOpt.valueOr(defaultValue), 42);

}



TEST_F(OptionalTest_415, SomeReturnsTrueForNonEmptyOptional_415) {

    EXPECT_TRUE(valueOpt.some());

}



TEST_F(OptionalTest_415, SomeReturnsFalseForEmptyOptional_415) {

    EXPECT_FALSE(emptyOpt.some());

}



TEST_F(OptionalTest_415, NoneReturnsTrueForEmptyOptional_415) {

    EXPECT_TRUE(emptyOpt.none());

}



TEST_F(OptionalTest_415, NoneReturnsFalseForNonEmptyOptional_415) {

    EXPECT_FALSE(valueOpt.none());

}



TEST_F(OptionalTest_415, NegationOperatorReturnsFalseForNonEmptyOptional_415) {

    EXPECT_FALSE(!valueOpt);

}



TEST_F(OptionalTest_415, NegationOperatorReturnsTrueForEmptyOptional_415) {

    EXPECT_TRUE(!emptyOpt);

}
