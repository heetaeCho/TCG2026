// File: tests/EqualsMatcher_describe_969_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the provided interface (amalgamated header)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

template <typename T>
using MatcherEqualsVec = Catch::Matchers::EqualsMatcher<
    T,
    std::allocator<T>,
    std::allocator<T>
>;

template <typename Vec>
static std::string ExpectedDesc(const Vec& v) {
    // Observable behavior: describe() == "Equals: " + stringify(m_comparator)
    return std::string("Equals: ") + ::Catch::Detail::stringify(v);
}

} // namespace

// -----------------------------
// Normal operation
// -----------------------------

TEST(EqualsMatcherDescribeTest_969, EmptyVector_HasCorrectDescription_969) {
    std::vector<int> comparator{};
    MatcherEqualsVec<int> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}

TEST(EqualsMatcherDescribeTest_969, SingleElementVector_HasCorrectDescription_969) {
    std::vector<int> comparator{42};
    MatcherEqualsVec<int> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}

TEST(EqualsMatcherDescribeTest_969, MultipleElementsVector_HasCorrectDescription_969) {
    std::vector<int> comparator{1, -2, 3000};
    MatcherEqualsVec<int> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}

// -----------------------------
// Boundary-ish / formatting-sensitive values
// -----------------------------

TEST(EqualsMatcherDescribeTest_969, StringVector_WithSpacesAndQuotes_DescriptionMatchesStringify_969) {
    std::vector<std::string> comparator{
        "alpha", " with space ", R"(quote "inside")", ",comma,"
    };
    MatcherEqualsVec<std::string> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}

TEST(EqualsMatcherDescribeTest_969, LargeVector_DescriptionMatchesStringify_969) {
    // Not relying on any internal truncation rules — we only check equality to stringify.
    std::vector<int> comparator;
    for (int i = 0; i < 50; ++i) comparator.push_back(i);
    MatcherEqualsVec<int> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}

// -----------------------------
// Additional type coverage
// -----------------------------

TEST(EqualsMatcherDescribeTest_969, VectorOfChars_DescriptionMatchesStringify_969) {
    std::vector<char> comparator{ 'a', '\n', 'Z' };
    MatcherEqualsVec<char> matcher(comparator);

    const std::string expected = ExpectedDesc(comparator);
    EXPECT_EQ(matcher.describe(), expected);
}
