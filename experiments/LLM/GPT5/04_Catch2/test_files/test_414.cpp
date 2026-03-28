// File: tests/optional_not_operator_test.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

// TEST_ID: 414

// Default-constructed Optional has no value => operator! returns true
TEST(OptionalNotOperatorTest_414, DefaultConstructedIsEmpty_414) {
    Optional<int> opt;                 // default constructed
    EXPECT_TRUE(!opt);                 // should report "empty"
}

// Optional constructed with a value is not empty => operator! returns false
TEST(OptionalNotOperatorTest_414, ValueConstructedIsNotEmpty_414) {
    Optional<int> opt{42};             // has a value
    EXPECT_FALSE(!opt);                // should report "not empty"
}

// After reset(), Optional becomes empty => operator! returns true
TEST(OptionalNotOperatorTest_414, ResetMakesItEmpty_414) {
    Optional<int> opt{7};              // start non-empty
    opt.reset();                       // observable mutator
    EXPECT_TRUE(!opt);                 // now empty
}

// operator! is const-qualified and should work on const objects too
TEST(OptionalNotOperatorTest_414, ConstObjectCheck_414) {
    const Optional<int> opt{5};        // const, has a value
    EXPECT_FALSE(!opt);                // still "not empty"
}
