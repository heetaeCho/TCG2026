// File: tests/match_all_of_operator_and_and_test.cpp

#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

namespace {

using namespace Catch::Matchers::Detail;

// A tiny external matcher type used as a collaborator in tests.
// It exposes the same public interface used by MatchAllOfGeneric:
//   - template<typename Arg> bool match(Arg&&) const;
//   - std::string describe() const;
// This is NOT simulating internal behavior of MatchAllOfGeneric;
// it’s just a dependency that returns predetermined results.
struct NamedBoolMatcher {
    std::string name;
    bool result; // predetermined result for match()

    explicit NamedBoolMatcher(std::string n, bool r) : name(std::move(n)), result(r) {}

    template <typename Arg>
    bool match(Arg&&) const {
        return result;
    }

    std::string describe() const { return name; }
};

// Helper to check that substrings appear in order inside a string.
// We avoid asserting exact formatting of `describe()` and only
// verify presence + relative order of components.
static void ExpectSubstringsInOrder(const std::string& haystack,
                                    std::initializer_list<std::string> needles) {
    size_t pos = 0;
    for (const auto& needle : needles) {
        size_t found = haystack.find(needle, pos);
        ASSERT_NE(found, std::string::npos) << "Missing substring: " << needle
                                            << " in: " << haystack;
        pos = found + needle.size();
    }
}

} // namespace

// ===============================================================
// TESTS
// ===============================================================

// Normal operation: All matchers return true -> combined match() is true.
TEST(MatchAllOfOperatorAndAnd_160, AllTrueMatches_160) {
    NamedBoolMatcher a{"A", true};
    NamedBoolMatcher b{"B", true};
    NamedBoolMatcher c{"C", true};

    // rhs contains (b && c). Then we do a && rhs.
    MatchAllOfGeneric<NamedBoolMatcher, NamedBoolMatcher> rhs{b, c};
    auto combined = (a && std::move(rhs));

    // Observable behavior: match() result is true if all are true.
    EXPECT_TRUE(combined.match(123));     // arbitrary argument type/value
    EXPECT_TRUE(combined.match(std::string{"foo"}));

    // Observable behavior: description mentions all components.
    const std::string desc = combined.describe();
    ExpectSubstringsInOrder(desc, {"A", "B", "C"}); // verify order (lhs prepended)
}

// Error/exception-like path via observable state: one false -> overall false.
TEST(MatchAllOfOperatorAndAnd_160, AnyFalseFails_160) {
    NamedBoolMatcher a{"A", true};
    NamedBoolMatcher b{"B", false}; // one failing matcher
    NamedBoolMatcher c{"C", true};

    MatchAllOfGeneric<NamedBoolMatcher, NamedBoolMatcher> rhs{b, c};
    auto combined = (a && std::move(rhs));

    EXPECT_FALSE(combined.match(42));
    EXPECT_FALSE(combined.match(std::string{"anything"}));

    // Description still lists components; format is not asserted, only presence.
    const std::string desc = combined.describe();
    ExpectSubstringsInOrder(desc, {"A", "B", "C"});
}

// Boundary condition: Empty rhs (no matchers) should behave like `lhs` alone.
TEST(MatchAllOfOperatorAndAnd_160, EmptyRhsBehavesLikeLhs_160) {
    NamedBoolMatcher lhs{"LHS", true};

    // Create an empty MatchAllOfGeneric<> and combine.
    MatchAllOfGeneric<> empty_rhs{}; // relies on variadic-ctor with zero args
    auto combined = (lhs && std::move(empty_rhs));

    // Should behave like lhs alone (true here).
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match("x"));

    // Description should at least contain the lhs description.
    const std::string desc = combined.describe();
    EXPECT_NE(desc.find("LHS"), std::string::npos);
}

// Mixed results: multiple falses -> still false; verify order in describe() is lhs first.
TEST(MatchAllOfOperatorAndAnd_160, MultipleFalseStillFalseAndOrder_160) {
    NamedBoolMatcher a{"A", false};
    NamedBoolMatcher b{"B", false};
    NamedBoolMatcher c{"C", true};

    MatchAllOfGeneric<NamedBoolMatcher, NamedBoolMatcher> rhs{b, c};
    auto combined = (a && std::move(rhs));

    EXPECT_FALSE(combined.match(999));

    const std::string desc = combined.describe();
    // Check the relative order is A then B then C (lhs gets prepended by operator&&)
    ExpectSubstringsInOrder(desc, {"A", "B", "C"});
}

// Composability: Chain via existing MatchAllOfGeneric and ensure all members are included.
TEST(MatchAllOfOperatorAndAnd_160, ChainedCompositionIncludesAll_160) {
    NamedBoolMatcher a{"A", true};
    NamedBoolMatcher b{"B", true};
    NamedBoolMatcher c{"C", true};
    NamedBoolMatcher d{"D", true};

    // Start with (c && d), then do (b && (c && d)), then (a && ...).
    auto rhs1 = MatchAllOfGeneric<NamedBoolMatcher, NamedBoolMatcher>{c, d};
    auto rhs2 = (b && std::move(rhs1)); // operator&& under test
    auto combined = (a && std::move(rhs2)); // operator&& under test again

    EXPECT_TRUE(combined.match(-1));

    const std::string desc = combined.describe();
    ExpectSubstringsInOrder(desc, {"A", "B", "C", "D"});
}
