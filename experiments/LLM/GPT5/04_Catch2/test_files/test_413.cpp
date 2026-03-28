// optional_none_tests_413.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_optional.hpp"

using Catch::Optional;

class OptionalNoneTest_413 : public ::testing::Test {};

// [Normal] Default-constructed Optional has no value -> none() == true
TEST_F(OptionalNoneTest_413, DefaultConstructedIsNone_413) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
}

// [Normal] Constructing from an lvalue engages the Optional -> none() == false
TEST_F(OptionalNoneTest_413, LValueConstructedIsNotNone_413) {
    int v = 42;
    Optional<int> opt(v);
    EXPECT_FALSE(opt.none());
}

// [Normal] Constructing from an rvalue engages the Optional -> none() == false
TEST_F(OptionalNoneTest_413, RValueConstructedIsNotNone_413) {
    Optional<int> opt(int{7});
    EXPECT_FALSE(opt.none());
}

// [Boundary] Copy-construct from an engaged Optional stays engaged -> none() == false
TEST_F(OptionalNoneTest_413, CopyConstructFromEngagedIsNotNone_413) {
    Optional<int> src(5);
    Optional<int> copy(src);
    EXPECT_FALSE(copy.none());
}

// [Boundary] Copy-construct from a disengaged Optional stays disengaged -> none() == true
TEST_F(OptionalNoneTest_413, CopyConstructFromDisengagedIsNone_413) {
    Optional<int> src;       // default-constructed (disengaged by interface snippet)
    Optional<int> copy(src); // copy-construct
    EXPECT_TRUE(copy.none());
}
