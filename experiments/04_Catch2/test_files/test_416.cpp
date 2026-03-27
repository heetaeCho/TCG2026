#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



TEST_F(OptionalTest_416, DefaultConstructorCreatesEmptyOptional_416) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_416, ValueConstructorInitializesOptionalWithValue_416) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_416, CopyConstructorCreatesCopyOfOptional_416) {

    Optional<int> opt1(42);

    Optional<int> opt2(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

}



TEST_F(OptionalTest_416, MoveConstructorTransfersValueFromOptional_416) {

    Optional<int> opt1(42);

    Optional<int> opt2(std::move(opt1));

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

    EXPECT_FALSE(opt1.some()); // Original should be empty after move

}



TEST_F(OptionalTest_416, AssignmentOperatorAssignsValueToOptional_416) {

    Optional<int> opt;

    opt = 42;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_416, CopyAssignmentOperatorAssignsCopyOfOptional_416) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    opt2 = opt1;

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

}



TEST_F(OptionalTest_416, MoveAssignmentOperatorTransfersValueFromOptional_416) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    opt2 = std::move(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, 42);

    EXPECT_FALSE(opt1.some()); // Original should be empty after move

}



TEST_F(OptionalTest_416, ResetClearsOptionalValue_416) {

    Optional<int> opt(42);

    opt.reset();

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_416, OperatorStarReturnsReferenceToValue_416) {

    Optional<int> opt(42);

    *opt = 84;

    EXPECT_EQ(*opt, 84);

}



TEST_F(OptionalTest_416, OperatorArrowAccessesMembersOfValue_416) {

    struct Point { int x; int y; };

    Optional<Point> opt(Point{3, 4});

    EXPECT_EQ(opt->x, 3);

    EXPECT_EQ(opt->y, 4);

}



TEST_F(OptionalTest_416, ValueOrReturnsStoredValueIfPresent_416) {

    Optional<int> opt(42);

    EXPECT_EQ(opt.valueOr(0), 42);

}



TEST_F(OptionalTest_416, ValueOrDefaultReturnsDefaultValueIfNotPresent_416) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(42), 42);

}



TEST_F(OptionalTest_416, SomeReturnsTrueIfValueIsPresent_416) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

}



TEST_F(OptionalTest_416, SomeReturnsFalseIfNoValueIsPresent_416) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

}



TEST_F(OptionalTest_416, NoneReturnsTrueIfNoValueIsPresent_416) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_416, NoneReturnsFalseIfValueIsPresent_416) {

    Optional<int> opt(42);

    EXPECT_FALSE(opt.none());

}



TEST_F(OptionalTest_416, OperatorBoolConvertsToTrueIfValueIsPresent_416) {

    Optional<int> opt(42);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_416, OperatorBoolConvertsToFalseIfNoValueIsPresent_416) {

    Optional<int> opt;

    EXPECT_FALSE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_416, EqualityOperatorReturnsTrueForTwoEmptyOptionals_416) {

    Optional<int> opt1;

    Optional<int> opt2;

    EXPECT_TRUE(opt1 == opt2);

}



TEST_F(OptionalTest_416, EqualityOperatorReturnsFalseForOneEmptyAndOneNonEmptyOptional_416) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    EXPECT_FALSE(opt1 == opt2);

}



TEST_F(OptionalTest_416, EqualityOperatorReturnsTrueForTwoEquivalentOptionals_416) {

    Optional<int> opt1(42);

    Optional<int> opt2(42);

    EXPECT_TRUE(opt1 == opt2);

}



TEST_F(OptionalTest_416, EqualityOperatorReturnsFalseForTwoNonEquivalentOptionals_416) {

    Optional<int> opt1(42);

    Optional<int> opt2(84);

    EXPECT_FALSE(opt1 == opt2);

}
