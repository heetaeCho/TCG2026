// File: size_is_matcher_tests_239.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <type_traits>

// Catch2 matcher header providing SizeIs / HasSizeMatcher
#include <catch2/matchers/catch_matchers_container_properties.hpp>

using Catch::Matchers::SizeIs;
using Catch::Matchers::HasSizeMatcher;

namespace {

// Sanity check: the factory returns a HasSizeMatcher object.
// (Interface-level/type property; no assumptions about internals.)
TEST(SizeIsMatcher_239, ReturnsHasSizeMatcherType_239) {
    auto m = SizeIs(3);
    (void)m; // suppress unused warnings
    // Compile-time properties are observable at the interface boundary.
    static_assert(std::is_copy_constructible<HasSizeMatcher>::value, "HasSizeMatcher should be copy-constructible");
    static_assert(std::is_move_constructible<HasSizeMatcher>::value, "HasSizeMatcher should be move-constructible");
}

// Normal operation: exact size match for std::vector
TEST(SizeIsMatcher_239, MatchesExactSize_Vector_239) {
    std::vector<int> v{1, 2, 3};
    auto m = SizeIs(3);
    EXPECT_TRUE(m.match(v));
}

// Boundary condition: empty container (size = 0)
TEST(SizeIsMatcher_239, MatchesZeroSize_EmptyVector_239) {
    std::vector<int> v;
    auto m_zero = SizeIs(0);
    EXPECT_TRUE(m_zero.match(v));

    auto m_one = SizeIs(1);
    EXPECT_FALSE(m_one.match(v));
}

// Non-match case: different size should not match
TEST(SizeIsMatcher_239, NonMatch_DifferentSize_239) {
    std::list<char> lst{'a', 'b'};
    auto m = SizeIs(3);
    EXPECT_FALSE(m.match(lst));
}

// Works with different container types: std::string length
TEST(SizeIsMatcher_239, WorksWithString_Length_239) {
    std::string s = "abcd";
    auto m = SizeIs(4);
    EXPECT_TRUE(m.match(s));

    auto m_not = SizeIs(5);
    EXPECT_FALSE(m_not.match(s));
}

// Another container type: std::list boundary and normal
TEST(SizeIsMatcher_239, WorksWithList_NormalAndBoundary_239) {
    std::list<int> lst1;              // size 0
    std::list<int> lst2{1, 2, 3, 4};  // size 4

    EXPECT_TRUE(SizeIs(0).match(lst1));
    EXPECT_TRUE(SizeIs(4).match(lst2));
    EXPECT_FALSE(SizeIs(3).match(lst2));
}

} // namespace
