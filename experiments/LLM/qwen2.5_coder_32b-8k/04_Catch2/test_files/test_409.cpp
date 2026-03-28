#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;

using namespace testing;



TEST(OptionalTest_409, DefaultConstructor_CreatesEmptyOptional_409) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST(OptionalTest_409, ValueConstructor_CreatesNonEmptyOptional_409) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

}



TEST(OptionalTest_409, CopyConstructor_CopyValueCorrectly_409) {

    Optional<int> opt1(42);

    Optional<int> opt2(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

}



TEST(OptionalTest_409, MoveConstructor_MoveValueCorrectly_409) {

    Optional<int> opt1(42);

    Optional<int> opt2(std::move(opt1));

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

}



TEST(OptionalTest_409, AssignmentOperator_AssignsValueCorrectly_409) {

    Optional<int> opt;

    opt = 42;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

}



TEST(OptionalTest_409, MoveAssignmentOperator_MovesValueCorrectly_409) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    opt2 = std::move(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

}



TEST(OptionalTest_409, Reset_ClearsOptionalValue_409) {

    Optional<int> opt(42);

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST(OptionalTest_409, ValueOr_ReturnsStoredValueWhenPresent_409) {

    Optional<int> opt(42);

    EXPECT_EQ(opt.valueOr(10), 42);

}



TEST(OptionalTest_409, ValueOr_ReturnsDefaultValueWhenNotPresent_409) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(10), 10);

}



TEST(OptionalTest_409, BoolConversionOperator_ReturnsTrueWhenValuePresent_409) {

    Optional<int> opt(42);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST(OptionalTest_409, BoolConversionOperator_ReturnsFalseWhenNoValue_409) {

    Optional<int> opt;

    EXPECT_FALSE(static_cast<bool>(opt));

}



TEST(OptionalTest_409, LogicalNotOperator_ReturnsFalseWhenValuePresent_409) {

    Optional<int> opt(42);

    EXPECT_FALSE(!opt);

}



TEST(OptionalTest_409, LogicalNotOperator_ReturnsTrueWhenNoValue_409) {

    Optional<int> opt;

    EXPECT_TRUE(!opt);

}
