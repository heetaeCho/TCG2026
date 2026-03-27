#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    Optional<int> emptyOptional;

    Optional<int> nonEmptyOptional{42};

};



TEST_F(OptionalTest_412, DefaultConstructorCreatesEmpty_412) {

    EXPECT_FALSE(emptyOptional.some());

}



TEST_F(OptionalTest_412, ValueConstructorCreatesNonEmpty_412) {

    EXPECT_TRUE(nonEmptyOptional.some());

}



TEST_F(OptionalTest_412, ResetSetsToEmpty_412) {

    nonEmptyOptional.reset();

    EXPECT_FALSE(nonEmptyOptional.some());

}



TEST_F(OptionalTest_412, ValueOrReturnsDefaultForEmpty_412) {

    int defaultValue = 0;

    EXPECT_EQ(emptyOptional.valueOr(defaultValue), defaultValue);

}



TEST_F(OptionalTest_412, ValueOrReturnsStoredValueForNonEmpty_412) {

    EXPECT_EQ(nonEmptyOptional.valueOr(0), 42);

}



TEST_F(OptionalTest_412, DereferenceOperatorsWorkForNonEmpty_412) {

    EXPECT_EQ(*nonEmptyOptional, 42);

    EXPECT_EQ(nonEmptyOptional.operator->(), &*nonEmptyOptional);

}



TEST_F(OptionalTest_412, BoolConversionWorksForEmpty_412) {

    EXPECT_FALSE(static_cast<bool>(emptyOptional));

}



TEST_F(OptionalTest_412, BoolConversionWorksForNonEmpty_412) {

    EXPECT_TRUE(static_cast<bool>(nonEmptyOptional));

}



TEST_F(OptionalTest_412, LogicalNotOperatorWorksForEmpty_412) {

    EXPECT_TRUE(!emptyOptional);

}



TEST_F(OptionalTest_412, LogicalNotOperatorWorksForNonEmpty_412) {

    EXPECT_FALSE(!nonEmptyOptional);

}



TEST_F(OptionalTest_412, CopyConstructorCopiesValue_412) {

    Optional<int> copied(nonEmptyOptional);

    EXPECT_TRUE(copied.some());

    EXPECT_EQ(*copied, 42);

}



TEST_F(OptionalTest_412, MoveConstructorMovesValue_412) {

    Optional<int> moved(std::move(nonEmptyOptional));

    EXPECT_TRUE(moved.some());

    EXPECT_EQ(*moved, 42);

}



TEST_F(OptionalTest_412, CopyAssignmentCopiesValue_412) {

    Optional<int> another;

    another = nonEmptyOptional;

    EXPECT_TRUE(another.some());

    EXPECT_EQ(*another, 42);

}



TEST_F(OptionalTest_412, MoveAssignmentMovesValue_412) {

    Optional<int> another;

    another = std::move(nonEmptyOptional);

    EXPECT_TRUE(another.some());

    EXPECT_EQ(*another, 42);

}
