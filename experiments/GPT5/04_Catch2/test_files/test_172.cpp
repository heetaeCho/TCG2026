// File: matchers_operator_and_generic_tests_172.cpp
#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

#include <string>
#include <type_traits>

namespace M = Catch::Matchers;

// --- Helpers: simple external matchers used as collaborators ---

// A generic matcher: matches any type and returns a fixed boolean.
// Derives from MatcherGenericBase so it is recognized as a "generic" matcher.
struct GenericBoolMatcher : M::MatcherGenericBase {
    explicit GenericBoolMatcher(bool v) : value(v) {}
    template <typename T>
    bool match(const T&) const { return value; }
    std::string describe() const override { return value ? "generic-true" : "generic-false"; }
    bool value;
};

// A typed int matcher: true iff the value is even.
struct IsEvenMatcher : M::MatcherBase<int> {
    bool match(const int& v) const override { return (v % 2) == 0; }
    std::string describe() const override { return "is even"; }
};

// A typed std::string matcher: true iff the value starts with a prefix.
struct StartsWithMatcher : M::MatcherBase<std::string> {
    explicit StartsWithMatcher(std::string p) : prefix(std::move(p)) {}
    bool match(const std::string& s) const override { return s.rfind(prefix, 0) == 0; }
    std::string describe() const override { return "starts with '" + prefix + "'"; }
    std::string prefix;
};

// --- Tests for operator&&(generic LHS, typed RHS) ---

// Verifies that combining a generic matcher with a typed matcher yields
// a composite that behaves like logical AND for Arg=int.
TEST(MatchersOperatorAndGeneric_172, Int_TrueWhenBothMatch_172) {
    GenericBoolMatcher gtrue{true};
    IsEvenMatcher even;

    auto combined = gtrue && even;  // This calls the target overload.

    EXPECT_TRUE(combined.match(2));
    EXPECT_FALSE(combined.match(3));
}

// When the generic LHS fails, the composite should not match even if RHS would.
TEST(MatchersOperatorAndGeneric_172, Int_FalseWhenGenericFails_172) {
    GenericBoolMatcher gfalse{false};
    IsEvenMatcher even;

    auto combined = gfalse && even;

    EXPECT_FALSE(combined.match(2));
    EXPECT_FALSE(combined.match(3));
}

// Type property: the result of (generic && typed<int>) should itself be
// a matcher for int (i.e., derive from MatcherBase<int>).
TEST(MatchersOperatorAndGeneric_172, ResultDerivesFromMatcherBase_Int_172) {
    using Combined =
        decltype(std::declval<const GenericBoolMatcher&>() && std::declval<const IsEvenMatcher&>());
    static_assert(std::is_base_of<M::MatcherBase<int>, Combined>::value,
                  "Combined type must derive from MatcherBase<int>");
    SUCCEED(); // Reaches runtime only if the static_assert passes.
}

// Works with different RHS types as long as RHS is a typed matcher and LHS is generic.
TEST(MatchersOperatorAndGeneric_172, String_RhsTypeSupported_172) {
    GenericBoolMatcher gtrue{true};
    StartsWithMatcher starts_ab{"ab"};

    auto combined = gtrue && starts_ab;

    EXPECT_TRUE(combined.match(std::string{"abc"}));
    EXPECT_FALSE(combined.match(std::string{"zab"}));
}

// Also supports rvalues and const-lvalues on both sides per the interface (const& params).
TEST(MatchersOperatorAndGeneric_172, AcceptsRvaluesAndConstLvalues_172) {
    const GenericBoolMatcher gtrue{true};
    const StartsWithMatcher starts_hello{"hello"};

    // rvalue generic, lvalue typed
    auto c1 = GenericBoolMatcher{true} && starts_hello;
    EXPECT_TRUE(c1.match(std::string{"hello world"}));

    // lvalue generic, rvalue typed
    auto c2 = gtrue && StartsWithMatcher{"he"};
    EXPECT_TRUE(c2.match(std::string{"hey"}));
}
