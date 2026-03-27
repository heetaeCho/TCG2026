// File: tests/vector_contains_element_matcher_describe_965.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Use the path you provided in the prompt.
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

using Catch::Matchers::VectorContainsElementMatcher;

// Simple helper to check prefix without depending on std::string::starts_with (C++20)
static bool HasPrefix(const std::string& s, const std::string& prefix) {
    return s.size() >= prefix.size() && std::equal(prefix.begin(), prefix.end(), s.begin());
}

// ---- Test suite ----
// Naming convention with TEST_ID = 965 embedded in every test name.
class VectorContainsElementMatcherDescribeTest_965 : public ::testing::Test {};

TEST_F(VectorContainsElementMatcherDescribeTest_965, IntComparator_ShowsPrefixAndValue_965) {
    const int comparator = 42;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(comparator);

    const std::string desc = matcher.describe();

    EXPECT_TRUE(HasPrefix(desc, "Contains: ")) << "Description should start with \"Contains: \".";
    // We don't assume Catch2's exact formatting rules beyond including the value.
    EXPECT_NE(desc.find("42"), std::string::npos) << "Description should contain the comparator value.";
}

TEST_F(VectorContainsElementMatcherDescribeTest_965, NegativeAndZero_IntComparator_965) {
    {
        const int neg = -7;
        VectorContainsElementMatcher<int, std::allocator<int>> m(neg);
        const std::string d = m.describe();
        EXPECT_TRUE(HasPrefix(d, "Contains: "));
        EXPECT_NE(d.find("-7"), std::string::npos);
    }
    {
        const int zero = 0;
        VectorContainsElementMatcher<int, std::allocator<int>> m(zero);
        const std::string d = m.describe();
        EXPECT_TRUE(HasPrefix(d, "Contains: "));
        EXPECT_NE(d.find("0"), std::string::npos);
    }
}

TEST_F(VectorContainsElementMatcherDescribeTest_965, StringComparator_ContainsRawSubstring_965) {
    // We avoid asserting exact quoting/escaping; we only require that the raw content appears.
    const std::string needle = "hello";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(needle);

    const std::string desc = matcher.describe();

    EXPECT_TRUE(HasPrefix(desc, "Contains: "));
    EXPECT_NE(desc.find("hello"), std::string::npos)
        << "Description should contain the comparator's textual content (quoting/escaping not asserted).";
}

TEST_F(VectorContainsElementMatcherDescribeTest_965, EmptyStringComparator_OnlyChecksPrefixAndLength_965) {
    const std::string empty = "";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(empty);

    const std::string desc = matcher.describe();

    // We only assert the mandated prefix and that describe() produced *some* output.
    EXPECT_TRUE(HasPrefix(desc, "Contains: "));
    // Avoid assuming whether Catch2 prints "" for empty strings; just assert non-empty overall.
    EXPECT_FALSE(desc.empty());
}

} // namespace
