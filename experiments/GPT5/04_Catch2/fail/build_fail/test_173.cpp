// File: matchers_operator_and_generic_test_173.cpp

#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_templated.hpp>
#include <type_traits>
#include <functional>
#include <string>

//
// Test-only helper matchers that use ONLY public Catch2 matcher interfaces.
// - LHS: a typed matcher deriving from MatcherBase<int>
// - RHS: a *generic* matcher deriving from Detail::MatcherGenericBase
//
namespace Catch { namespace Matchers {

struct CountingIntMatcher : MatcherBase<int> {
    explicit CountingIntMatcher(std::function<bool(int)> predicate,
                                int* counter = nullptr,
                                std::string desc = "counting-int")
        : predicate_(std::move(predicate)), counter_(counter), desc_(std::move(desc)) {}

    bool match(int const& v) const override {
        if (counter_) ++*counter_;
        return predicate_(v);
    }
    std::string describe() const override { return desc_; }

private:
    std::function<bool(int)> predicate_;
    int* counter_;
    std::string desc_;
};

// A minimal *generic* matcher: derives from Detail::MatcherGenericBase and
// provides a match(int) + describe(). This satisfies the "generic" constraint
// used by is_generic_matcher_v in the operator&& SFINAE.
struct GenericIntPredicate : Detail::MatcherGenericBase {
    explicit GenericIntPredicate(std::function<bool(int)> predicate,
                                 int* counter = nullptr,
                                 std::string desc = "generic-int")
        : predicate_(std::move(predicate)), counter_(counter), desc_(std::move(desc)) {}

    bool match(int const& v) const {
        if (counter_) ++*counter_;
        return predicate_(v);
    }
    std::string describe() const override { return desc_; }

private:
    std::function<bool(int)> predicate_;
    int* counter_;
    std::string desc_;
};

}} // namespace Catch::Matchers

// Detection idiom to check whether `lhs && rhs` is a well-formed expression.
// This lets us verify SFINAE enablement without relying on compilation errors.
template <typename L, typename R, typename = void>
struct is_and_well_formed : std::false_type {};

template <typename L, typename R>
struct is_and_well_formed<L, R, std::void_t<
    decltype(std::declval<L const&>() && std::declval<R const&>())
>> : std::true_type {};

using Catch::Matchers::CountingIntMatcher;
using Catch::Matchers::GenericIntPredicate;

//
// Tests
//

// Return type check against the function signature's declared return type.
TEST(MatchersAndOperatorGeneric_173, ReturnTypeIsMatchAllOfGeneric_173) {
    using L = CountingIntMatcher;
    using R = GenericIntPredicate;

    using Ret = decltype(std::declval<L const&>() && std::declval<R const&>());
    using Expected = Catch::Matchers::Detail::MatchAllOfGeneric<
        Catch::Matchers::MatcherBase<int>,
        R
    >;

    // The operator's signature explicitly returns the following type:
    // std::enable_if_t<is_generic_matcher_v<R>, MatchAllOfGeneric<MatcherBase<int>, R>>
    EXPECT_TRUE((std::is_same<Ret, Expected>::value));
}

// Enablement: only enabled when RHS is a *generic* matcher.
TEST(MatchersAndOperatorGeneric_173, EnabledOnlyForGenericRhs_173) {
    using L = CountingIntMatcher;

    // Positive: RHS is generic
    EXPECT_TRUE((is_and_well_formed<L, GenericIntPredicate>::value));

    // Negative: RHS is *not* a generic matcher (int is a stand-in non-matcher)
    EXPECT_FALSE((is_and_well_formed<L, int>::value));
}

// Normal behavior: both sides match -> combined match succeeds
TEST(MatchersAndOperatorGeneric_173, MatchesTrueWhenBothMatch_173) {
    CountingIntMatcher lhs([](int v){ return v % 2 == 0; }); // even
    GenericIntPredicate rhs([](int v){ return v > 0; });     // positive

    auto combined = lhs && rhs;
    EXPECT_TRUE(combined.match(8));   // even and positive
}

// Mixed behavior: LHS false, RHS true -> combined match fails (logical AND semantics)
TEST(MatchersAndOperatorGeneric_173, MatchesFalseWhenLhsFalse_173) {
    CountingIntMatcher lhs([](int v){ return v % 2 == 0; }); // even
    GenericIntPredicate rhs([](int v){ return v > 0; });     // positive

    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(3));  // odd (lhs false), positive (rhs true)
}

// Mixed behavior: LHS true, RHS false -> combined match fails
TEST(MatchersAndOperatorGeneric_173, MatchesFalseWhenRhsFalse_173) {
    CountingIntMatcher lhs([](int v){ return v % 2 == 0; });  // even
    GenericIntPredicate rhs([](int v){ return v < 0; });      // negative

    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(12)); // even (lhs true), not negative (rhs false)
}

// Chaining: (lhs && rhs1) && rhs2 -> all must match to succeed
TEST(MatchersAndOperatorGeneric_173, ChainedAnd_AllMustMatch_173) {
    CountingIntMatcher lhs([](int v){ return v % 2 == 0; });     // even
    GenericIntPredicate rhs1([](int v){ return v > 0; });        // positive
    GenericIntPredicate rhs2([](int v){ return v < 10; });       // < 10

    auto combined = (lhs && rhs1) && rhs2;
    EXPECT_TRUE(combined.match(8));   // even, positive, <10
    EXPECT_FALSE(combined.match(12)); // even, positive, but not <10
}

// Lifetime/temporaries: combining temporaries should be safe and usable.
TEST(MatchersAndOperatorGeneric_173, WorksWithTemporaries_173) {
    auto combined =
        CountingIntMatcher([](int v){ return v % 2 == 0; }) &&
        GenericIntPredicate([](int v){ return v != 6; });

    EXPECT_TRUE(combined.match(4));
    EXPECT_FALSE(combined.match(6));
}
