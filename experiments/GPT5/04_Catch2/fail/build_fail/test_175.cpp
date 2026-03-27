// File: catch_matchers_templated_or_generic_tests_175.cpp

#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Catch2 matcher bases + the operator under test
#include <catch2/matchers/catch_matchers_generic.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>

using Catch::Matchers::MatcherBase;
using Catch::Matchers::MatcherGenericBase;
namespace CatchDetail = Catch::Matchers::Detail;

// Make sure the templated operator|| is visible (it lives in Catch::Matchers)
using Catch::Matchers::operator||;

// ---------- Test helpers (external collaborators), kept minimal ----------

// Typed matcher for ints: matches a specific value.
struct EqualsNTyped : MatcherBase<int> {
    explicit EqualsNTyped(int n) : n_(n) {}

    bool match(int const& v) const override { return v == n_; }
    std::string describe() const override { return "equals " + std::to_string(n_); }

private:
    int n_;
};

// Generic matcher: true for even integral values; false for other types.
struct IsEvenGeneric : MatcherGenericBase {
    std::string describe() const override { return "is even (generic)"; }

    template <typename T>
    bool match(T const& v) const {
        if constexpr (std::is_integral_v<std::decay_t<T>>) {
            return (v % 2) == 0;
        } else {
            return false;
        }
    }
};

// Generic matcher: true when the argument is std::string of length 3; false otherwise.
struct LengthIs3Generic : MatcherGenericBase {
    std::string describe() const override { return "string length == 3 (generic)"; }

    template <typename T>
    bool match(T const& v) const {
        if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
            return v.size() == 3;
        } else {
            return false;
        }
    }
};

// ------------------------------ Tests ------------------------------

class MatchersTemplatedOrGenericTest_175 : public ::testing::Test {};

// Verifies: (1) returned object is a *generic matcher* type, and
// (2) OR-combination behaves correctly for int inputs where both sides are applicable.
TEST_F(MatchersTemplatedOrGenericTest_175, OrWithGeneric_MatchesIntValues_175) {
    EqualsNTyped lhs{42};     // typed matcher for int
    IsEvenGeneric rhs;        // generic matcher for "even"

    auto combined = lhs || rhs;

    // Compile-time: result is recognized as a generic matcher (no reliance on internals beyond public trait)
    static_assert(CatchDetail::is_generic_matcher_v<decltype(combined)>,
                  "operator|| must return a generic matcher");

    // Observable behavior (black-box): OR semantics over int
    EXPECT_TRUE(combined.match(42)); // both: lhs(true), rhs(true)
    EXPECT_TRUE(combined.match(40)); // lhs(false), rhs(true)
    EXPECT_FALSE(combined.match(41)); // lhs(false), rhs(false)
}

// Verifies: combined matcher produced by (typed || generic) is itself generic,
// and thus can be used with types *different* from the typed LHS' ArgLHS.
TEST_F(MatchersTemplatedOrGenericTest_175, OrWithGeneric_AcceptsNonLhsArgTypes_175) {
    EqualsNTyped lhs{3};      // typed for int
    LengthIs3Generic rhs;     // generic for string length == 3

    auto combined = lhs || rhs;

    // Using a non-int type: only the generic part should determine the result.
    EXPECT_TRUE(combined.match(std::string{"abc"}));   // rhs(true)
    EXPECT_FALSE(combined.match(std::string{"abcd"})); // rhs(false)

    // And it still works for the original typed ArgLHS
    EXPECT_TRUE(combined.match(3));   // lhs(true), rhs(false for int)
    EXPECT_FALSE(combined.match(5));  // lhs(false), rhs(false for int)
}

// Verifies: RHS can be a temporary generic matcher object (lifetime managed by the returned matcher).
TEST_F(MatchersTemplatedOrGenericTest_175, OrWithGeneric_AllowsTemporaryRHS_175) {
    EqualsNTyped lhs{9};

    // Pass a temporary generic matcher
    auto combined = lhs || LengthIs3Generic{};

    EXPECT_TRUE(combined.match(std::string{"hey"}));   // length 3 -> true
    EXPECT_FALSE(combined.match(std::string{"heyy"})); // length 4 -> false
}
