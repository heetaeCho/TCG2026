// File: ansi_skipping_string_const_iterator_decrement_test_39.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test
// Adjust the include path as needed for your project layout.
#include "catch2/internal/catch_textflow.hpp"

namespace CT = Catch::TextFlow;

class AnsiSkippingStringConstIteratorTest_39 : public ::testing::Test {};

// [TEST_ID: 39]
// Verifies that pre-decrement returns a reference to the same iterator instance.
// This checks the reference-return contract of operator--().
TEST_F(AnsiSkippingStringConstIteratorTest_39, PreDecrementReturnsSelf_39) {
    std::string s = "x";
    CT::AnsiSkippingString::const_iterator it(s);

    // Move forward once to avoid boundary-specific behavior assumptions.
    ++it;

    auto& ret = --it;
    EXPECT_EQ(&ret, &it) << "Pre-decrement must return *this by reference";
}

// [TEST_ID: 39]
// Verifies that (++it followed by --it) restores iterator equality with a baseline copy.
// This asserts only observable equality via operator== without assuming internal layout.
TEST_F(AnsiSkippingStringConstIteratorTest_39, PreDecrementReversesPreviousIncrement_39) {
    std::string s = "abc";
    CT::AnsiSkippingString::const_iterator start(s);
    CT::AnsiSkippingString::const_iterator it = start;

    ++it;          // advance once
    auto& back = --it; // and come back

    // Still the same object by address
    EXPECT_EQ(&back, &it);

    // And equal by observable equality
    EXPECT_TRUE(it == start) << "Increment then pre-decrement should restore equality to the baseline iterator";
}

// [TEST_ID: 39]
// Verifies post-decrement returns a copy (by value) of the prior iterator state.
// This uses only operator== to compare snapshots; it does not assume any internal position.
TEST_F(AnsiSkippingStringConstIteratorTest_39, PostDecrementReturnsPriorStateByValue_39) {
    std::string s = "yz";
    CT::AnsiSkippingString::const_iterator it(s);

    // Ensure we are not at a potential begin boundary before decrementing.
    ++it;

    CT::AnsiSkippingString::const_iterator snapshot = it--; // should capture pre-decrement state (by value)

    // The snapshot should compare equal to the state that existed before decrement.
    // We cannot directly capture "before" without copying; snapshot *is* that copy.
    EXPECT_TRUE(snapshot == ++(CT::AnsiSkippingString::const_iterator(s)))
        << "Snapshot should equal the iterator's state before the decrement (one step past start after a single ++).";

    // Also check the returned object is distinct from the mutated iterator instance.
    EXPECT_NE(&snapshot, &it) << "Post-decrement must return by value (a separate object), not by reference";
}

// [TEST_ID: 39]
// Verifies that chaining pre-decrement expressions yields a reference, ensuring fluent usage.
// We only assert reference identity from the immediate pre-decrement call.
TEST_F(AnsiSkippingStringConstIteratorTest_39, ChainedPreDecrementIsReference_39) {
    std::string s = "hello";
    CT::AnsiSkippingString::const_iterator it(s);

    // Move away from potential boundary.
    ++it; // safe step forward

    auto& r1 = --it;        // first pre-decrement
    EXPECT_EQ(&r1, &it);

    // Move forward again and test another pre-decrement reference-return
    ++it;
    auto& r2 = --it;        // second pre-decrement
    EXPECT_EQ(&r2, &it);
}
