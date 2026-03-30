// File: any_match_matcher_describe_tests_180.cpp

#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AnyMatchMatcher;

// A simple stub collaborator with a configurable description.
// This is an external dependency passed into AnyMatchMatcher.
struct StubMatcher {
    std::string desc;
    explicit StubMatcher(std::string d) : desc(std::move(d)) {}
    std::string describe() const { return desc; }
};

// A move-only collaborator to verify AnyMatchMatcher can be constructed
// with movable, non-copyable dependencies.
struct MoveOnlyMatcher {
    std::string desc;
    explicit MoveOnlyMatcher(std::string d) : desc(std::move(d)) {}
    MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher(MoveOnlyMatcher&&) noexcept = default;
    MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) noexcept = default;

    std::string describe() const { return desc; }
};

// Normal operation: describe() should prefix inner matcher description.
TEST(AnyMatchMatcherTest_180, DescribePrefixesInnerDescription_180) {
    StubMatcher inner{"is even"};
    AnyMatchMatcher<StubMatcher> any(inner);

    EXPECT_EQ(any.describe(), "any match is even");
}

// Boundary condition: inner description is empty.
TEST(AnyMatchMatcherTest_180, DescribeWithEmptyInnerDescription_180) {
    StubMatcher inner{""};
    AnyMatchMatcher<StubMatcher> any(inner);

    EXPECT_EQ(any.describe(), "any match ");
}

// Construction with move-only collaborator (no copy). Also checks describe().
TEST(AnyMatchMatcherTest_180, ConstructWithMoveOnlyMatcherAndDescribe_180) {
    AnyMatchMatcher<MoveOnlyMatcher> any{MoveOnlyMatcher{"passes"}};

    EXPECT_EQ(any.describe(), "any match passes");
}
