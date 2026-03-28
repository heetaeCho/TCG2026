// File: has_size_matcher_describe_tests_237.cpp

#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::HasSizeMatcher;

namespace {

// Normal operation: typical positive size
TEST(HasSizeMatcher_237, Describe_ReturnsExpectedForTypicalSize_237) {
    HasSizeMatcher m(3);
    EXPECT_EQ(std::string("has size == 3"), m.describe());
}

// Boundary: zero size
TEST(HasSizeMatcher_237, Describe_ReturnsExpectedForZeroSize_237) {
    HasSizeMatcher m(0);
    EXPECT_EQ(std::string("has size == 0"), m.describe());
}

// Boundary: large size (stress a bigger value without assuming limits)
TEST(HasSizeMatcher_237, Describe_ReturnsExpectedForLargeSize_237) {
    const std::size_t large = static_cast<std::size_t>(1ULL << 31); // representative large value
    HasSizeMatcher m(large);
    EXPECT_EQ(std::string("has size == ") + std::to_string(large), m.describe());
}

// Stability/idempotence: repeated calls should be consistent and not mutate state
TEST(HasSizeMatcher_237, Describe_IsStableAcrossMultipleCalls_237) {
    HasSizeMatcher m(42);
    const std::string first = m.describe();
    const std::string second = m.describe();
    EXPECT_EQ(std::string("has size == 42"), first);
    EXPECT_EQ(first, second);
}

} // namespace
