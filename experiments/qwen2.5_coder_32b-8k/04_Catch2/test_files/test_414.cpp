#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



TEST_F(OptionalTest_414, DefaultConstructor_SetsToNone_414) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_414, ValueConstructor_SetsValue_414) {

    Optional<int> opt(42);

    EXPECT_FALSE(opt.none());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_414, CopyConstructor_CopiesValue_414) {

    Optional<int> original(42);

    Optional<int> copy(original);

    EXPECT_FALSE(copy.none());

    EXPECT_EQ(*copy, 42);

}



TEST_F(OptionalTest_414, MoveConstructor_MovesValue_414) {

    Optional<int> original(42);

    Optional<int> moved(std::move(original));

    EXPECT_FALSE(moved.none());

    EXPECT_EQ(*moved, 42);

    EXPECT_TRUE(original.none()); // Original should be none after move

}



TEST_F(OptionalTest_414, CopyAssignment_AssignsValue_414) {

    Optional<int> opt;

    opt = Optional<int>(42);

    EXPECT_FALSE(opt.none());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_414, MoveAssignment_MovesValue_414) {

    Optional<int> original(42);

    Optional<int> moved;

    moved = std::move(original);

    EXPECT_FALSE(moved.none());

    EXPECT_EQ(*moved, 42);

    EXPECT_TRUE(original.none()); // Original should be none after move

}



TEST_F(OptionalTest_414, Reset_ClearsValue_414) {

    Optional<int> opt(42);

    opt.reset();

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_414, DereferenceOperator_ReturnsCorrectValue_414) {

    Optional<int> opt(42);

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_414, ArrowOperator_ReturnsCorrectPointer_414) {

    Optional<int> opt(42);

    EXPECT_EQ(opt->operator int(), 42);

}



TEST_F(OptionalTest_414, ValueOr_ReturnsValueWhenSome_414) {

    Optional<int> opt(42);

    EXPECT_EQ(opt.valueOr(0), 42);

}



TEST_F(OptionalTest_414, ValueOr_ReturnsDefaultValueWhenNone_414) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(42), 42);

}



TEST_F(OptionalTest_414, Some_ReturnsTrueWhenValueSet_414) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

}



TEST_F(OptionalTest_414, Some_ReturnsFalseWhenNoValue_414) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

}



TEST_F(OptionalTest_414, None_ReturnsTrueWhenNoValue_414) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_414, None_ReturnsFalseWhenValueSet_414) {

    Optional<int> opt(42);

    EXPECT_FALSE(opt.none());

}



TEST_F(OptionalTest_414, BoolOperator_ReturnsTrueWhenValueSet_414) {

    Optional<int> opt(42);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_414, BoolOperator_ReturnsFalseWhenNoValue_414) {

    Optional<int> opt;

    EXPECT_FALSE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_414, LogicalNotOperator_ReturnsTrueWhenNoValue_414) {

    Optional<int> opt;

    EXPECT_TRUE(!opt);

}



TEST_F(OptionalTest_414, LogicalNotOperator_ReturnsFalseWhenValueSet_414) {

    Optional<int> opt(42);

    EXPECT_FALSE(!opt);

}
