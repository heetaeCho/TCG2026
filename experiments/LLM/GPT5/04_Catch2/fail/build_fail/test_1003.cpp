// File: tests/name_pattern_matches_1003.cpp

#include <gtest/gtest.h>

// Catch2 headers (public interfaces used by the tests)
#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>

using namespace Catch;

namespace {

// Helper: create a minimal TestCaseInfo with a given display name.
// This uses only public constructors/fields that are part of the interface.
static TestCaseInfo makeTestCaseWithName(const std::string& displayName) {
    // NameAndTags: public interface object used by TestCaseInfo's ctor
    NameAndTags nameAndTags{ displayName, "" };

    // SourceLineInfo: any valid line info is fine; contents are not inspected by matches()
    SourceLineInfo sli{ __FILE__, __LINE__ };

    // className is not used by NamePattern::matches
    StringRef cls{ "" };

    return TestCaseInfo{ cls, nameAndTags, sli };
}

} // namespace

// ========== Normal operation ==========

// Exact name match should return true
TEST(NamePatternMatches_1003, ExactMatch_1003) {
    // Pattern uses the provided "name" argument; filter string is metadata
    TestSpec::NamePattern pattern("MyTestCase", "filter:exact");

    auto tci = makeTestCaseWithName("MyTestCase");
    EXPECT_TRUE(pattern.matches(tci));
}

// Simple '*' wildcard should match suffix variations (e.g., "Foo*" vs "Foobar")
TEST(NamePatternMatches_1003, StarWildcardSuffix_1003) {
    TestSpec::NamePattern pattern("Foo*", "filter:wildcard-star");

    auto t1 = makeTestCaseWithName("Foo");
    auto t2 = makeTestCaseWithName("Foobar");
    auto t3 = makeTestCaseWithName("Foo_bar_baz");

    EXPECT_TRUE(pattern.matches(t1));
    EXPECT_TRUE(pattern.matches(t2));
    EXPECT_TRUE(pattern.matches(t3));
}

// '?' wildcard should match exactly one character difference (e.g., "te?t" vs "test")
TEST(NamePatternMatches_1003, QuestionMarkWildcardSingleChar_1003) {
    TestSpec::NamePattern pattern("te?t", "filter:wildcard-qmark");

    auto t_ok1 = makeTestCaseWithName("test");
    auto t_ok2 = makeTestCaseWithName("text");
    auto t_ng  = makeTestCaseWithName("teest"); // two chars, should not match

    EXPECT_TRUE(pattern.matches(t_ok1));
    EXPECT_TRUE(pattern.matches(t_ok2));
    EXPECT_FALSE(pattern.matches(t_ng));
}

// ========== Case-insensitivity (boundary/important observable) ==========

// NamePattern is constructed to use case-insensitive matching via WildcardPattern;
// verify observable behavior without relying on internals.
TEST(NamePatternMatches_1003, CaseInsensitiveMatch_1003) {
    TestSpec::NamePattern pattern("foo*bar", "filter:ci");

    auto t1 = makeTestCaseWithName("FoObAr");
    auto t2 = makeTestCaseWithName("fOOxxBAR");
    auto t3 = makeTestCaseWithName("fooBARbaz"); // trailing junk => should fail

    EXPECT_TRUE(pattern.matches(t1));
    EXPECT_TRUE(pattern.matches(t2));
    EXPECT_FALSE(pattern.matches(t3));
}

// ========== Non-match / Negative path ==========

// Unrelated names must not match
TEST(NamePatternMatches_1003, NoMatch_1003) {
    TestSpec::NamePattern pattern("alpha*", "filter:negative");

    auto t1 = makeTestCaseWithName("beta");
    auto t2 = makeTestCaseWithName("gamma");
    auto t3 = makeTestCaseWithName("alp"); // prefix too short without wildcard coverage

    EXPECT_FALSE(pattern.matches(t1));
    EXPECT_FALSE(pattern.matches(t2));
    EXPECT_FALSE(pattern.matches(t3));
}

// ========== Edge-ish behavior visible through the interface ==========

// Wildcard covering empty middle piece should still match ("ab*cd" vs "abcd")
TEST(NamePatternMatches_1003, StarWildcardCanMatchEmptySpan_1003) {
    TestSpec::NamePattern pattern("ab*cd", "filter:star-empty");

    auto t1 = makeTestCaseWithName("abcd");      // empty middle
    auto t2 = makeTestCaseWithName("abXYZcd");   // non-empty middle
    auto t3 = makeTestCaseWithName("abXcdY");    // trailing extra => should fail

    EXPECT_TRUE(pattern.matches(t1));
    EXPECT_TRUE(pattern.matches(t2));
    EXPECT_FALSE(pattern.matches(t3));
}
