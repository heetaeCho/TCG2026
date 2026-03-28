// File: tests/contains_matcher_matcher_desc_952.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

// Minimal stand-in collaborator types used only to provide a public `describe()`
// — we are not simulating internal behavior of the class under test.

struct StaticDescMatcher {
    std::string text;
    explicit StaticDescMatcher(std::string s) : text(std::move(s)) {}
    std::string describe() const { return text; }
};

struct MoveOnlyMatcher {
    std::string text;
    explicit MoveOnlyMatcher(std::string s) : text(std::move(s)) {}
    MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher(MoveOnlyMatcher&&) = default;
    MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) = default;
    std::string describe() const { return text; }
};

//------------------------------------------------------------------------------
// Normal operation: description concatenates the standard prefix with the
// inner matcher's description.
//------------------------------------------------------------------------------
TEST(ContainsMatcherMatcher_952, Describe_ConcatenatesPrefixAndInner_952) {
    using Catch::Matchers::ContainsMatcherMatcher;

    StaticDescMatcher inner{"abc == 123"};
    ContainsMatcherMatcher<StaticDescMatcher> wrapper(inner);

    // Observable behavior only: returned string content.
    EXPECT_EQ(wrapper.describe(), "contains element matching abc == 123");
}

//------------------------------------------------------------------------------
// Boundary: inner matcher returns an empty description string.
// Ensures prefix and spacing remain correct.
//------------------------------------------------------------------------------
TEST(ContainsMatcherMatcher_952, Describe_EmptyInnerDescription_952) {
    using Catch::Matchers::ContainsMatcherMatcher;

    StaticDescMatcher inner{""};
    ContainsMatcherMatcher<StaticDescMatcher> wrapper(inner);

    EXPECT_EQ(wrapper.describe(), "contains element matching ");
}

//------------------------------------------------------------------------------
// Boundary: special characters / unicode in the inner description should be
// passed through verbatim.
//------------------------------------------------------------------------------
TEST(ContainsMatcherMatcher_952, Describe_SpecialCharactersPassthrough_952) {
    using Catch::Matchers::ContainsMatcherMatcher;

    StaticDescMatcher inner{R"(.*\w+\s"Ω-ß" <&> 😊)"};
    ContainsMatcherMatcher<StaticDescMatcher> wrapper(inner);

    EXPECT_EQ(wrapper.describe(), R"(contains element matching .*\w+\s"Ω-ß" <&> 😊)");
}

//------------------------------------------------------------------------------
// Construction with move-only collaborator: verifies the template accepts a
// move-only matcher (constructor is observable through successful compilation
// and that describe() still works).
//------------------------------------------------------------------------------
TEST(ContainsMatcherMatcher_952, Describe_WithMoveOnlyMatcher_952) {
    using Catch::Matchers::ContainsMatcherMatcher;

    MoveOnlyMatcher inner{"X<Y"};
    ContainsMatcherMatcher<MoveOnlyMatcher> wrapper(std::move(inner));

    EXPECT_EQ(wrapper.describe(), "contains element matching X<Y");
}

//------------------------------------------------------------------------------
// Const-correctness: describe() must be callable on a const wrapper.
//------------------------------------------------------------------------------
TEST(ContainsMatcherMatcher_952, Describe_IsConstCallable_952) {
    using Catch::Matchers::ContainsMatcherMatcher;

    StaticDescMatcher inner{"const-ok"};
    const ContainsMatcherMatcher<StaticDescMatcher> wrapper(inner);

    EXPECT_EQ(wrapper.describe(), "contains element matching const-ok");
}
