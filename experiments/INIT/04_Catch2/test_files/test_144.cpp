// File: match_not_of_describe_tests_144.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers::Detail;

// ---- Test-only helper: external collaborator we can control ----
template <typename T>
class DummyMatcher : public MatcherBase<T> {
public:
    explicit DummyMatcher(std::string desc) : desc_(std::move(desc)) {}

    bool match(T const&) const override { return false; } // unobserved in these tests
    std::string describe() const override { return desc_; }

private:
    std::string desc_;
};

// ----------------------- Test Fixture ---------------------------
class MatchNotOfDescribeTest_144 : public ::testing::Test {
protected:
    // Helper to build a MatchNotOf around a controllable underlying matcher
    template <typename T>
    MatchNotOf<T> makeNotOf(const std::string& underlyingDesc) {
        underlying_ = std::make_unique<DummyMatcher<T>>(underlyingDesc);
        return MatchNotOf<T>(*underlying_);
    }

    // Keep the underlying alive for the lifetime of each test
    std::unique_ptr<MatcherBase<int>> underlying_;
};

// -------------------------- Tests -------------------------------

// Normal operation: description is prefixed with "not " and mirrors the underlying toString()
TEST_F(MatchNotOfDescribeTest_144, PrefixesUnderlyingDescription_144) {
    auto notOf = makeNotOf<int>("x > 0");
    // Build expected strictly from the underlying's observable toString()
    std::string expected = std::string("not ") + underlying_->toString();

    EXPECT_EQ(notOf.describe(), expected);
}

// Boundary: empty underlying description -> still prefixed with "not "
TEST_F(MatchNotOfDescribeTest_144, HandlesEmptyUnderlyingDescription_144) {
    auto notOf = makeNotOf<int>("");
    std::string expected = std::string("not ") + underlying_->toString(); // "not " + ""

    EXPECT_EQ(notOf.describe(), expected);
    EXPECT_EQ(expected, "not ");
}

// Special characters/whitespace preserved in the resulting description
TEST_F(MatchNotOfDescribeTest_144, PreservesSpecialCharacters_144) {
    std::string weird = "a\n\tb [c]{d}(e) ^$.*+?|\\";
    auto notOf = makeNotOf<int>(weird);

    std::string expected = std::string("not ") + underlying_->toString();
    EXPECT_EQ(notOf.describe(), expected);
}

// Idempotence across calls: multiple calls return the same string
TEST_F(MatchNotOfDescribeTest_144, DescribeIsStableAcrossCalls_144) {
    auto notOf = makeNotOf<int>("some underlying description");

    auto first  = notOf.describe();
    auto second = notOf.describe();
    EXPECT_EQ(first, second);
}

// Underlying already starts with "not " — no de-duplication; observable result is a plain prefix
TEST_F(MatchNotOfDescribeTest_144, DoesNotAlterUnderlyingLeadingNot_144) {
    auto notOf = makeNotOf<int>("not x == 5");

    std::string expected = std::string("not ") + underlying_->toString(); // "not not x == 5"
    EXPECT_EQ(notOf.describe(), expected);
}
