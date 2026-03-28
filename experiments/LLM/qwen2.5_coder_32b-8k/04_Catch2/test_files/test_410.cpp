#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;

using ::testing::Eq;



class OptionalTest_410 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(OptionalTest_410, DefaultConstructorSetsNone_410) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_410, ValueConstructorSetsSome_410) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

    EXPECT_FALSE(opt.none());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_410, CopyConstructorCreatesIndependentCopy_410) {

    Optional<int> original(42);

    Optional<int> copy(original);

    EXPECT_TRUE(copy.some());

    EXPECT_EQ(*copy, 42);

    copy.reset();

    EXPECT_FALSE(copy.some());

    EXPECT_TRUE(original.some());

}



TEST_F(OptionalTest_410, MoveConstructorTransfersOwnership_410) {

    Optional<int> original(42);

    Optional<int> moved(std::move(original));

    EXPECT_TRUE(moved.some());

    EXPECT_EQ(*moved, 42);

    EXPECT_FALSE(original.some());

}



TEST_F(OptionalTest_410, CopyAssignmentPreservesValue_410) {

    Optional<int> opt;

    Optional<int> other(42);

    opt = other;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_410, MoveAssignmentTransfersValue_410) {

    Optional<int> opt;

    Optional<int> other(42);

    opt = std::move(other);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

    EXPECT_FALSE(other.some());

}



TEST_F(OptionalTest_410, ResetClearsValue_410) {

    Optional<int> opt(42);

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_410, DereferenceOperatorReturnsStoredValue_410) {

    Optional<int> opt(42);

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_410, ArrowOperatorAccessesMemberFunctions_410) {

    struct Point { int x; int y; };

    Optional<Point> opt(Point{1, 2});

    EXPECT_EQ(opt->x, 1);

    EXPECT_EQ(opt->y, 2);

}



TEST_F(OptionalTest_410, ValueOrReturnsDefaultValueWhenNone_410) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(42), 42);

}



TEST_F(OptionalTest_410, ValueOrReturnsStoredValueWhenSome_410) {

    Optional<int> opt(42);

    EXPECT_EQ(opt.valueOr(99), 42);

}



TEST_F(OptionalTest_410, BoolConversionReflectsState_410) {

    Optional<int> empty;

    Optional<int> filled(42);

    EXPECT_FALSE(empty);

    EXPECT_TRUE(filled);

}



TEST_F(OptionalTest_410, NotOperatorReflectsState_410) {

    Optional<int> empty;

    Optional<int> filled(42);

    EXPECT_TRUE(!empty);

    EXPECT_FALSE(!filled);

}
