#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest_404 : public ::testing::Test {

protected:

    using TestType = int;

    Optional<TestType> opt;

};



TEST_F(OptionalTest_404, DefaultConstructor_SetsNone_404) {

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_404, ValueConstructor_SetsValue_404) {

    TestType value = 42;

    Optional<TestType> optWithVal(value);

    EXPECT_TRUE(optWithVal.some());

    EXPECT_EQ(*optWithVal, value);

}



TEST_F(OptionalTest_404, CopyConstructor_CopiesValue_404) {

    TestType value = 84;

    Optional<TestType> original(value);

    Optional<TestType> copy(original);

    EXPECT_TRUE(copy.some());

    EXPECT_EQ(*copy, *original);

}



TEST_F(OptionalTest_404, MoveConstructor_TransfersOwnership_404) {

    TestType value = 168;

    Optional<TestType> original(value);

    Optional<TestType> moved(std::move(original));

    EXPECT_TRUE(moved.some());

    EXPECT_EQ(*moved, value);

    EXPECT_FALSE(original.some());

}



TEST_F(OptionalTest_404, AssignmentOperator_ValueSetsValue_404) {

    TestType value = 336;

    opt = value;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, value);

}



TEST_F(OptionalTest_404, AssignmentOperator_CopyAssignsValue_404) {

    TestType value = 672;

    Optional<TestType> other(value);

    opt = other;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, *other);

}



TEST_F(OptionalTest_404, AssignmentOperator_MoveTransfersOwnership_404) {

    TestType value = 1344;

    Optional<TestType> other(value);

    opt = std::move(other);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, value);

    EXPECT_FALSE(other.some());

}



TEST_F(OptionalTest_404, Reset_ClearsValue_404) {

    TestType value = 2688;

    opt = value;

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_404, ValueOr_ReturnsDefaultValueWhenNone_404) {

    TestType defaultValue = 5376;

    EXPECT_EQ(opt.valueOr(defaultValue), defaultValue);

}



TEST_F(OptionalTest_404, BoolConversion_ReturnsTrueWhenSome_404) {

    opt = 10752;

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_404, BoolConversion_ReturnsFalseWhenNone_404) {

    EXPECT_FALSE(static_cast<bool>(opt));

}
