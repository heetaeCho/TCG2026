// File: tests/ContainsMatcher_953_Test.cpp
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>

// Include the amalgamated Catch2 header that provides the Contains helper
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::Contains;

namespace {

// ---- Normal operation -------------------------------------------------

TEST(ContainsMatcher_953, MatchesPresentInt_953) {
    std::vector<int> v{1, 2, 3, 4};
    auto m = Contains(3);
    EXPECT_TRUE(m.match(v));
}

TEST(ContainsMatcher_953, DoesNotMatchAbsentInt_953) {
    std::vector<int> v{1, 2, 4};
    auto m = Contains(3);
    EXPECT_FALSE(m.match(v));
}

// ---- Boundary conditions ----------------------------------------------

TEST(ContainsMatcher_953, EmptyContainerReturnsFalse_953) {
    std::vector<int> empty;
    auto m = Contains(42);
    EXPECT_FALSE(m.match(empty));
}

TEST(ContainsMatcher_953, MultipleEqualElementsStillMatch_953) {
    std::vector<int> v{2, 2, 2};
    auto m = Contains(2);
    EXPECT_TRUE(m.match(v));
}

TEST(ContainsMatcher_953, WorksWithArrayContainer_953) {
    std::array<int, 5> a{{10, 20, 30, 40, 50}};
    auto m = Contains(40);
    EXPECT_TRUE(m.match(a));
}

// ---- Observable comparator behavior (transparent std::equal_to<>) -----

TEST(ContainsMatcher_953, HeterogeneousCompare_StringLiteralToStdString_953) {
    std::vector<std::string> v{"alpha", "beta"};
    // Pass a const char*; with std::equal_to<> the comparison is transparent
    // and should use std::string == const char*.
    auto m = Contains("alpha");
    EXPECT_TRUE(m.match(v));

    auto m_no = Contains("gamma");
    EXPECT_FALSE(m_no.match(v));
}

TEST(ContainsMatcher_953, HeterogeneousCompare_IntToLong_953) {
    std::list<long> lst{1L, 3L, 5L};
    auto m = Contains(3);      // int compared to long via transparent comparator
    auto m_absent = Contains(2);
    EXPECT_TRUE(m.match(lst));
    EXPECT_FALSE(m_absent.match(lst));
}

} // namespace
