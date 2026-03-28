// File: is_empty_matcher_tests_236.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Assume the header is available on the include path.
#include "catch2/matchers/catch_matchers_container_properties.hpp"

namespace {

using Catch::Matchers::IsEmptyMatcher;

TEST(IsEmptyMatcherTest_236, DescribeReturnsExpectedLiteral_236) {
    IsEmptyMatcher m;
    const std::string desc = m.describe();
    EXPECT_EQ(desc, "is empty");
}

TEST(IsEmptyMatcherTest_236, DescribeIsStableAcrossCalls_236) {
    IsEmptyMatcher m;
    const std::string first = m.describe();
    const std::string second = m.describe();
    EXPECT_EQ(first, "is empty");
    EXPECT_EQ(second, "is empty");
    EXPECT_EQ(first, second);
}

TEST(IsEmptyMatcherTest_236, DescribeCallableOnConstInstance_236) {
    const IsEmptyMatcher m{};
    EXPECT_EQ(m.describe(), "is empty");
}

TEST(IsEmptyMatcherTest_236, DescribeCallableOnTemporaryRvalue_236) {
    EXPECT_EQ(IsEmptyMatcher{}.describe(), "is empty");
}

TEST(IsEmptyMatcherTest_236, DescribeReturnTypeIsStdString_236) {
    // Verify the function’s observable signature aspect (return type).
    static_assert(std::is_same<decltype(std::declval<IsEmptyMatcher>().describe()), std::string>::value,
                  "IsEmptyMatcher::describe() must return std::string");
    SUCCEED(); // Keep this a valid test body for frameworks requiring a statement.
}

} // namespace
