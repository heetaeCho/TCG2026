// File: tests/ApproxMatcher_scale_974.tests.cpp
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <type_traits>
#include <limits>

// Include the amalgamated header that declares ApproxMatcher
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::ApproxMatcher;

namespace {

// --- SFINAE detection helpers (no reliance on private state) ---
template <typename M, typename Arg, typename = void>
struct is_scale_invocable : std::false_type {};

template <typename M, typename Arg>
struct is_scale_invocable<M, Arg,
    std::void_t<decltype(std::declval<M&>().scale(std::declval<Arg const&>()))>> : std::true_type {};

// Concrete matcher aliases with explicit template parameters
using MatcherDouble =
    ApproxMatcher<double, std::allocator<double>, std::allocator<double>>;
using MatcherInt =
    ApproxMatcher<int, std::allocator<int>, std::allocator<int>>;
using MatcherString =
    ApproxMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>>;

} // namespace

// --- Normal operation: returns reference to *this (fluent API) ---
TEST(ApproxMatcherScale_974, ReturnsSelfReference_974) {
    std::vector<double> comp{1.0, 2.0, 3.0};
    MatcherDouble matcher(comp);

    auto& ret = matcher.scale(1.0);
    EXPECT_EQ(&ret, &matcher); // same object => fluent interface
}

// --- Normal operation + boundary-ish values: chaining and no-throw contract (observable) ---
TEST(ApproxMatcherScale_974, ChainableAndNoThrow_974) {
    std::vector<double> comp{0.0, 0.0};
    MatcherDouble matcher(comp);

    EXPECT_NO_THROW({
        matcher.scale(0.0)
               .scale(1.0)
               .scale(std::numeric_limits<double>::max());
    });

    // We do not assert internal effect; just that public methods remain usable.
    std::vector<double> same{0.0, 0.0};
    (void)matcher.match(same);     // callable; result is an observable bool but not asserted
    (void)matcher.describe();      // callable; returns std::string
    SUCCEED();                     // reached without exceptions
}

// --- Compile-time contract: enabled only when T is constructible as double ---
TEST(ApproxMatcherScale_974, SFINAEEnabledForArithmeticT_974) {
    static_assert(std::is_constructible<double, double>::value, "double -> double must be constructible");
    static_assert(std::is_constructible<double, int>::value, "int -> double must be constructible");

    // scale should be invocable for numeric T
    static_assert(is_scale_invocable<MatcherDouble, double>::value,
                  "scale(double) should be available when T=double");
    static_assert(is_scale_invocable<MatcherInt, int>::value,
                  "scale(int) should be available when T=int");
}

// --- Compile-time contract: disabled when T is NOT constructible as double ---
TEST(ApproxMatcherScale_974, SFINAEDisabledForNonNumericT_974) {
    static_assert(!std::is_constructible<double, std::string>::value,
                  "std::string -> double should NOT be constructible");

    // For T=std::string, the member template should be disabled (no viable overload)
    static_assert(!is_scale_invocable<MatcherString, std::string>::value,
                  "scale(std::string) should NOT be available when T=std::string");
}

// --- Acceptance of different numeric argument kinds via implicit conversion (no UB asserted) ---
TEST(ApproxMatcherScale_974, AcceptsConvertibleNumericValues_974) {
    std::vector<double> comp{42.0};
    MatcherDouble matcher(comp);

    // Parameter type is T const& (double); float/long double are implicitly convertible.
    EXPECT_NO_THROW({
        float f = 1.5f;
        long double ld = 2.75L;
        matcher.scale(f).scale(ld).scale(3); // also an int literal (convertible)
    });
}
