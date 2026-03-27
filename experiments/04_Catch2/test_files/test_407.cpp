#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;

using ::testing::Eq;



TEST(OptionalTest_407, DefaultConstructor_SetsNone_407) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST(OptionalTest_407, ValueConstructor_Some_ReturnsTrue_407) {

    Optional<int> opt(5);

    EXPECT_TRUE(opt.some());

    EXPECT_FALSE(opt.none());

}



TEST(OptionalTest_407, ValueConstructor_ValueOr_ReturnsValue_407) {

    Optional<int> opt(10);

    EXPECT_EQ(10, opt.valueOr(-1));

}



TEST(OptionalTest_407, MoveConstructor_Some_ReturnsTrue_407) {

    Optional<int> original(5);

    Optional<int> moved(std::move(original));

    EXPECT_TRUE(moved.some());

    EXPECT_FALSE(moved.none());

}



TEST(OptionalTest_407, CopyConstructor_Some_ReturnsTrue_407) {

    Optional<int> original(5);

    Optional<int> copy = original;

    EXPECT_TRUE(copy.some());

    EXPECT_FALSE(copy.none());

}



TEST(OptionalTest_407, CopyAssignmentOperator_Some_ReturnsTrue_407) {

    Optional<int> original(5);

    Optional<int> target;

    target = original;

    EXPECT_TRUE(target.some());

    EXPECT_FALSE(target.none());

}



TEST(OptionalTest_407, MoveAssignmentOperator_Some_ReturnsTrue_407) {

    Optional<int> original(5);

    Optional<int> target;

    target = std::move(original);

    EXPECT_TRUE(target.some());

    EXPECT_FALSE(target.none());

}



TEST(OptionalTest_407, ValueAssignmentOperator_ValueOr_ReturnsValue_407) {

    Optional<int> opt;

    opt = 10;

    EXPECT_EQ(10, opt.valueOr(-1));

}



TEST(OptionalTest_407, Reset_SetsNone_407) {

    Optional<int> opt(5);

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST(OptionalTest_407, ValueOr_DefaultValue_ReturnsDefaultValue_407) {

    Optional<int> opt;

    EXPECT_EQ(-1, opt.valueOr(-1));

}



TEST(OptionalTest_407, BoolOperator_Some_ReturnsTrue_407) {

    Optional<int> opt(5);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST(OptionalTest_407, NotOperator_None_ReturnsTrue_407) {

    Optional<int> opt;

    EXPECT_TRUE(!opt);

}
