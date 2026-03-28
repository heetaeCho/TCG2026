// File: tests/ContainsMatcherMatcher_954.tests.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

namespace {

// A small helper alias to make type assertions readable
template <typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

} // namespace

// ----------------------------------------------------------------------------
// Type property: returns a ContainsMatcherMatcher<Matcher> when given a matcher
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, ReturnsCorrectType_954) {
    // Use a well-known, real Catch2 matcher (string StartsWith)
    auto inner = StartsWith(std::string("ab"));
    // The return type should be ContainsMatcherMatcher<decltype(inner)>
    using Returned = decltype(Contains(inner));
    using Expected = ContainsMatcherMatcher<decltype(inner)>;

    // Compile-time + runtime check of the type
    static_assert(is_same_v<Returned, Expected>, "Return type must be ContainsMatcherMatcher<Matcher>");
    EXPECT_TRUE((is_same_v<Returned, Expected>));
}

// ----------------------------------------------------------------------------
// Normal operation: matches when any element in the range satisfies inner matcher
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, MatchesWhenAnyElementSatisfies_954) {
    auto inner = StartsWith(std::string("ab"));
    auto combined = Contains(inner);

    std::vector<std::string> data = {"zz", "abacus", "yy"};
    EXPECT_TRUE(combined.match(data));
}

// ----------------------------------------------------------------------------
// Normal operation: does not match when no element satisfies inner matcher
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, DoesNotMatchWhenNoneSatisfy_954) {
    auto inner = Equals(std::string("needle"));
    auto combined = Contains(inner);

    std::vector<std::string> data = {"hay", "stack", "pile"};
    EXPECT_FALSE(combined.match(data));
}

// ----------------------------------------------------------------------------
// Boundary: empty range should never match
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, EmptyRange_954) {
    auto inner = Contains(std::string("x")); // string-contains matcher as inner
    auto combined = Contains(inner);

    std::vector<std::string> empty;
    EXPECT_FALSE(combined.match(empty));
}

// ----------------------------------------------------------------------------
// Boundary: single-element range
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, SingleElementRange_954) {
    auto inner = Equals(std::string("only"));
    auto combined = Contains(inner);

    std::vector<std::string> oneOk = {"only"};
    std::vector<std::string> oneBad = {"other"};

    EXPECT_TRUE(combined.match(oneOk));
    EXPECT_FALSE(combined.match(oneBad));
}

// ----------------------------------------------------------------------------
// Constraint check: SFINAE/requires — non-matcher arguments should be ill-formed
// (We assert this at compile time without invoking UB.)
// ----------------------------------------------------------------------------
TEST(ContainsMatcherMatcherTest_954, RejectsNonMatcherArgumentsAtCompileTime_954) {
#if defined(__cpp_requires) || __cplusplus >= 202002L
    // C++20 requires-expression: 'Contains(123)' should NOT be a valid expression
    auto accepts_int =
        []() constexpr {
            if constexpr (requires { Contains(123); }) { return true; }
            else { return false; }
        }();
    EXPECT_FALSE(accepts_int);
#else
    // Fallback (pre-C++20): use std::is_invocable to approximate
    // We wrap in a functor to avoid immediate hard error in older modes.
    struct TryInvoke {
        template <typename T>
        auto operator()(T&& t) const -> decltype(Contains(std::forward<T>(t)), std::true_type{}) { return {}; }
        auto operator()(...) const -> std::false_type { return {}; }
    };
    auto result = TryInvoke{}(123);
    EXPECT_FALSE(decltype(result)::value);
#endif
}
