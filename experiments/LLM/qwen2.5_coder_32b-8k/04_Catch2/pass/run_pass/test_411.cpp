#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;

using ::testing::Eq;



TEST(OptionalTest_411, ValueOr_ReturnsValueWhenPresent_411) {

    Optional<int> opt(5);

    EXPECT_EQ(opt.valueOr(0), 5);

}



TEST(OptionalTest_411, ValueOr_ReturnsDefaultValueWhenNotPresent_411) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(10), 10);

}



TEST(OptionalTest_411, Some_ReturnsTrueWhenValuePresent_411) {

    Optional<int> opt(5);

    EXPECT_TRUE(opt.some());

}



TEST(OptionalTest_411, Some_ReturnsFalseWhenValueNotPresent_411) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

}



TEST(OptionalTest_411, None_ReturnsFalseWhenValuePresent_411) {

    Optional<int> opt(5);

    EXPECT_FALSE(opt.none());

}



TEST(OptionalTest_411, None_ReturnsTrueWhenValueNotPresent_411) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST(OptionalTest_411, OperatorBool_ReturnsTrueWhenValuePresent_411) {

    Optional<int> opt(5);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST(OptionalTest_411, OperatorBool_ReturnsFalseWhenValueNotPresent_411) {

    Optional<int> opt;

    EXPECT_FALSE(static_cast<bool>(opt));

}



TEST(OptionalTest_411, OperatorStar_ReturnsReferenceToValue_411) {

    Optional<int> opt(5);

    EXPECT_EQ(*opt, 5);

}



TEST(OptionalTest_411, OperatorArrow_ReturnsPointerToValue_411) {

    Optional<std::string> opt("hello");

    EXPECT_EQ(opt->length(), 5);

}



TEST(OptionalTest_411, Reset_ClearsTheValue_411) {

    Optional<int> opt(5);

    opt.reset();

    EXPECT_FALSE(opt.some());

}



TEST(OptionalTest_411, CopyConstructor_CopiesValue_411) {

    Optional<std::string> opt("hello");

    Optional<std::string> copy = opt;

    EXPECT_TRUE(copy.some() && *copy == "hello");

}



TEST(OptionalTest_411, MoveConstructor_MovesValue_411) {

    Optional<std::string> opt("hello");

    Optional<std::string> moved = std::move(opt);

    EXPECT_TRUE(moved.some() && *moved == "hello" && !opt.some());

}



TEST(OptionalTest_411, CopyAssignment_CopiesValue_411) {

    Optional<int> opt(5);

    Optional<int> other;

    other = opt;

    EXPECT_TRUE(other.some() && *other == 5);

}



TEST(OptionalTest_411, MoveAssignment_MovesValue_411) {

    Optional<std::string> opt("hello");

    Optional<std::string> other;

    other = std::move(opt);

    EXPECT_TRUE(other.some() && *other == "hello" && !opt.some());

}
