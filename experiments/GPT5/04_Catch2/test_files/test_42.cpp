// File: ansi_skipping_string_iterator_neq_tests_42.cpp
#include <gtest/gtest.h>
#include <string>

// Include the provided interface header
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

// Test fixture holding a shared backing string so iterators point to the same string object.
class AnsiSkippingStringConstIteratorTest_42 : public ::testing::Test {
protected:
    std::string text_ = "Hello \x1b[31mred\x1b[0m world"; // content is irrelevant to != logic
};

// Verifies that != is the logical negation of == for two iterators at the same position.
TEST_F(AnsiSkippingStringConstIteratorTest_42, NotEqualIsFalseForEqualIterators_42) {
    AnsiSkippingString::const_iterator it1(text_);
    AnsiSkippingString::const_iterator it2(text_);
    EXPECT_TRUE(it1 == it2) << "Iterators constructed on the same string should start equal";
    EXPECT_FALSE(it1 != it2) << "operator!= must be the negation of operator== for equal iterators";
}

// Verifies that advancing one iterator changes inequality state.
TEST_F(AnsiSkippingStringConstIteratorTest_42, NotEqualIsTrueAfterAdvance_42) {
    AnsiSkippingString::const_iterator it1(text_);
    AnsiSkippingString::const_iterator it2(text_);
    ++it1; // move only one iterator forward
    EXPECT_TRUE(it1 != it2) << "Iterators at different positions must be not equal";
    EXPECT_EQ(it1 != it2, it2 != it1) << "Inequality should be symmetric";
}

// Verifies that moving back to the original position restores equality and thus != becomes false.
TEST_F(AnsiSkippingStringConstIteratorTest_42, NotEqualBecomesFalseAfterReturningToSamePosition_42) {
    AnsiSkippingString::const_iterator it1(text_);
    AnsiSkippingString::const_iterator it2(text_);

    ++it1;                            // diverge
    ASSERT_TRUE(it1 != it2);          // confirm divergence is observable via !=
    --it1;                            // return to the original position
    EXPECT_TRUE(it1 == it2);          // equality restored
    EXPECT_FALSE(it1 != it2);         // and so inequality must be false
}

// Sanity: an iterator must never be != to itself.
TEST_F(AnsiSkippingStringConstIteratorTest_42, NotEqualToSelfIsAlwaysFalse_42) {
    AnsiSkippingString::const_iterator it(text_);
    EXPECT_FALSE(it != it) << "Self-inequality must be false (reflexivity)";
}
