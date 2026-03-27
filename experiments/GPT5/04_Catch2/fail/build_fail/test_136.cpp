// File: match_all_of_describe_test.cpp
#include <gtest/gtest.h>

// Include the production header exactly as provided
#include "Catch2/src/catch2/matchers/catch_matchers.hpp"

namespace {

using Catch::Matchers::Detail::MatchAllOf;

// [TEST_ID = 136]
// Verifies that a default-constructed object has a stable, well-formed description.
// Based solely on the interface (describe()), without touching internal state.
TEST(MatchAllOfTest_136, DefaultDescribeIsEmptyGroup_136) {
    MatchAllOf allOf;
    // From the visible implementation logic, empty matcher set formats as "(  )"
    // (note the space after '(' and before ')').
    EXPECT_EQ(allOf.describe(), "(  )");
}

// [TEST_ID = 136]
// Calling describe() multiple times should yield identical results (no hidden mutation).
TEST(MatchAllOfTest_136, DescribeIsStableAcrossCalls_136) {
    MatchAllOf allOf;
    const std::string first = allOf.describe();
    const std::string second = allOf.describe();
    EXPECT_EQ(first, second);
}

// [TEST_ID = 136]
// Basic well-formedness check for boundary formatting: starts with "( " and ends with " )".
// This asserts only on the visible output contract of describe().
TEST(MatchAllOfTest_136, DescribeHasExpectedFraming_136) {
    MatchAllOf allOf;
    const std::string d = allOf.describe();

    ASSERT_GE(d.size(), static_cast<size_t>(4)) << "description too short";
    EXPECT_EQ(d.substr(0, 2), "( ");
    EXPECT_EQ(d.substr(d.size() - 2), " )");
}

// [TEST_ID = 136]
// Smoke test: describe() should be noexcept in practice (at least must not throw).
TEST(MatchAllOfTest_136, DescribeDoesNotThrow_136) {
    MatchAllOf allOf;
    EXPECT_NO_THROW({
        auto s = allOf.describe();
        (void)s;
    });
}

} // namespace
