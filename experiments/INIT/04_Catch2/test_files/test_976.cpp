// File: tests/UnorderedEqualsMatcher_describe_976.tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::HasSubstr;
using ::testing::StartsWith;

namespace {

using IntAlloc = std::allocator<int>;
using MatcherT = Catch::Matchers::UnorderedEqualsMatcher<int, IntAlloc, IntAlloc>;

// NOTE: We only assert on observable strings from describe().
// We avoid assuming the exact vector formatting beyond the documented prefix
// and the presence of the elements as substrings.

TEST(UnorderedEqualsMatcherDescribeTest_976, DescribeHasPrefixAndListsElements_976) {
    const std::vector<int, IntAlloc> target{3, 1, 2};
    MatcherT m{target};

    const std::string desc = m.describe();

    // Required prefix from the provided interface.
    EXPECT_THAT(desc, StartsWith("UnorderedEquals: "));

    // Elements of the target should appear in the description (order-agnostic test).
    EXPECT_THAT(desc, HasSubstr("1"));
    EXPECT_THAT(desc, HasSubstr("2"));
    EXPECT_THAT(desc, HasSubstr("3"));
}

TEST(UnorderedEqualsMatcherDescribeTest_976, DescribeForEmptyTargetIndicatesEmpty_976) {
    const std::vector<int, IntAlloc> target{};
    MatcherT m{target};

    const std::string desc = m.describe();

    EXPECT_THAT(desc, StartsWith("UnorderedEquals: "));
    // We do not rely on the exact spacing of Catch2's vector stringify,
    // only that it indicates an empty container with braces.
    EXPECT_THAT(desc, HasSubstr("{"));
    EXPECT_THAT(desc, HasSubstr("}"));
}

TEST(UnorderedEqualsMatcherDescribeTest_976, DescribeIncludesDuplicateValues_976) {
    const std::vector<int, IntAlloc> target{42, 42};
    MatcherT m{target};

    const std::string desc = m.describe();

    EXPECT_THAT(desc, StartsWith("UnorderedEquals: "));
    // At minimum, the duplicated value should appear in the description.
    // (We avoid asserting exact counts to not couple to stringify details.)
    EXPECT_THAT(desc, HasSubstr("42"));
}

} // namespace
