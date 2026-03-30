// File: tests/is_empty_matcher_test_238.cpp

#include <gtest/gtest.h>
#include <array>
#include <forward_list>
#include <string>
#include <vector>

// Catch2 matcher under test
#include <catch2/matchers/catch_matchers_container_properties.hpp>

using Catch::Matchers::IsEmpty;
using Catch::Matchers::IsEmptyMatcher;

class IsEmptyMatcherTest_238 : public ::testing::Test {};

// Ensures the factory returns a default-constructed matcher usable via its public API.
TEST_F(IsEmptyMatcherTest_238, DefaultConstructibleAndCallable_238) {
    // Construction should be possible without any parameters.
    IsEmptyMatcher m = IsEmpty();

    // Empty vector should match.
    std::vector<int> v;
    EXPECT_TRUE(m.match(v));
}

// Verifies normal operation on std::vector.
TEST_F(IsEmptyMatcherTest_238, MatchesEmptyVector_238) {
    IsEmptyMatcher m = IsEmpty();

    std::vector<int> empty_vec;
    EXPECT_TRUE(m.match(empty_vec));
}

TEST_F(IsEmptyMatcherTest_238, RejectsNonEmptyVector_238) {
    IsEmptyMatcher m = IsEmpty();

    std::vector<int> vec = {1};
    EXPECT_FALSE(m.match(vec));
}

// Verifies normal operation on std::string.
TEST_F(IsEmptyMatcherTest_238, MatchesEmptyString_238) {
    IsEmptyMatcher m = IsEmpty();

    std::string s;
    EXPECT_TRUE(m.match(s));
}

TEST_F(IsEmptyMatcherTest_238, RejectsNonEmptyString_238) {
    IsEmptyMatcher m = IsEmpty();

    std::string s = "x";
    EXPECT_FALSE(m.match(s));
}

// Boundary case: containers that are compile-time empty (std::array<T,0>).
TEST_F(IsEmptyMatcherTest_238, MatchesZeroSizedStdArray_238) {
    IsEmptyMatcher m = IsEmpty();

    std::array<int, 0> a{};
    EXPECT_TRUE(m.match(a));
}

// Compatibility with single-link containers (no size()) like std::forward_list.
TEST_F(IsEmptyMatcherTest_238, WorksWithForwardList_238) {
    IsEmptyMatcher m = IsEmpty();

    std::forward_list<int> fl_empty;
    EXPECT_TRUE(m.match(fl_empty));

    std::forward_list<int> fl_non_empty = {42};
    EXPECT_FALSE(m.match(fl_non_empty));
}
