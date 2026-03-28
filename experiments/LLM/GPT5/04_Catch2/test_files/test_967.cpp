// File: tests/ContainsMatcherDescribe_967.tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::stringify;
using Catch::Matchers::ContainsMatcher;

namespace {

// Helper alias to keep test code concise.
// We stick to std::allocator to avoid relying on any non-essential behavior.
template <typename T>
using CMatcher = ContainsMatcher<T, std::allocator<T>, std::allocator<T>>;

} // namespace

// [Normal] Non-empty comparator of ints
TEST(ContainsMatcherDescribe_967, ReturnsExactPrefixPlusStringifiedComparator_967) {
    const std::vector<int> comparator{1, 2, 3};
    CMatcher<int> m(comparator);

    const std::string expected = std::string("Contains: ") + stringify(comparator);
    EXPECT_EQ(m.describe(), expected);
}

// [Boundary] Empty comparator vector should still be prefixed correctly
TEST(ContainsMatcherDescribe_967, EmptyComparatorStillHasCorrectPrefix_967) {
    const std::vector<int> comparator; // empty
    CMatcher<int> m(comparator);

    const std::string expected = std::string("Contains: ") + stringify(comparator);
    EXPECT_EQ(m.describe(), expected);
}

// [Normal / Special characters] String elements with spaces/punctuation
TEST(ContainsMatcherDescribe_967, StringElementsAreStringifiedAndPrefixed_967) {
    const std::vector<std::string> comparator{"hello", "a, b", " spaced "};
    CMatcher<std::string> m(comparator);

    const std::string expected = std::string("Contains: ") + stringify(comparator);
    EXPECT_EQ(m.describe(), expected);
}

// [Stability] Multiple calls should be consistent (no hidden mutation)
TEST(ContainsMatcherDescribe_967, DescribeIsIdempotentAcrossCalls_967) {
    const std::vector<int> comparator{42, 7};
    CMatcher<int> m(comparator);

    const std::string expected = std::string("Contains: ") + stringify(comparator);
    EXPECT_EQ(m.describe(), expected);
    EXPECT_EQ(m.describe(), expected);  // second call yields same observable result
}
