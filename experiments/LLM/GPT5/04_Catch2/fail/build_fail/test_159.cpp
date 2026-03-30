// File: match_all_of_and_operator_test_159.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include "catch2/matchers/catch_matchers_templated.hpp"

// Shorthand for the namespace in the prompt
namespace C = Catch::Matchers::Detail;

// Minimal dummy matchers used as external collaborators.
// They provide only the public surface that MatchAllOfGeneric might use.
struct DummyA {
    template <typename T>
    bool match(const T&) const { return true; }
    std::string describe() const { return "DummyA"; }
};

struct DummyB {
    template <typename T>
    bool match(const T&) const { return false; }
    std::string describe() const { return "DummyB"; }
};

struct DummyC {
    template <typename T>
    bool match(const T&) const { return true; }
    std::string describe() const { return "DummyC"; }
};

struct DummyD {
    template <typename T>
    bool match(const T&) const { return true; }
    std::string describe() const { return "DummyD"; }
};

// ---- Tests ----

// Verifies that `lhs && rhs` produces a new MatchAllOfGeneric with one more
// stored pointer and that the last stored pointer is the address of `rhs`.
// Also checks that the original LHS matchers' addresses are preserved in order.
TEST(MatchAllOfAndOperator_159, AppendsMatcherAndPreservesLHSOrder_159) {
    DummyA a;
    DummyB b;
    DummyC c;

    // Construct LHS with two matchers
    C::MatchAllOfGeneric<DummyA, DummyB> lhs(a, b);

    // Combine via operator&&
    auto combined = std::move(lhs) && c;

    // Size grew by 1
    ASSERT_EQ(combined.m_matchers.size(), 3u);

    // The first two entries should reference the original matchers
    EXPECT_EQ(combined.m_matchers[0], static_cast<void const*>(&a));
    EXPECT_EQ(combined.m_matchers[1], static_cast<void const*>(&b));

    // The last entry should be the address of rhs (c)
    EXPECT_EQ(combined.m_matchers[2], static_cast<void const*>(&c));
}

// Verifies the resulting type from `lhs && rhs` matches
// MatchAllOfGeneric<MatcherTs..., MatcherRHS>.
TEST(MatchAllOfAndOperator_159, ResultTypeExtendsMatcherPack_159) {
    DummyA a;
    DummyB b;
    DummyC c;

    C::MatchAllOfGeneric<DummyA, DummyB> lhs(a, b);
    auto combined = std::move(lhs) && c;

    // Type check
    bool const is_expected_type =
        std::is_same<decltype(combined), C::MatchAllOfGeneric<DummyA, DummyB, DummyC>>::value;
    EXPECT_TRUE(is_expected_type);
}

// Verifies that chaining `&&` works (observable via size and last pointer).
TEST(MatchAllOfAndOperator_159, ChainedAndAccumulatesMatchers_159) {
    DummyA a;
    DummyB b;
    DummyC c;
    DummyD d;

    C::MatchAllOfGeneric<DummyA, DummyB> lhs(a, b);

    auto combined = (std::move(lhs) && c) && d;

    ASSERT_EQ(combined.m_matchers.size(), 4u);
    // Original two preserved
    EXPECT_EQ(combined.m_matchers[0], static_cast<void const*>(&a));
    EXPECT_EQ(combined.m_matchers[1], static_cast<void const*>(&b));
    // Then c, then d
    EXPECT_EQ(combined.m_matchers[2], static_cast<void const*>(&c));
    EXPECT_EQ(combined.m_matchers[3], static_cast<void const*>(&d));
}

// Smoke test to ensure the resulting object exposes the documented interface
// (match() and describe()) without asserting specific internal logic.
TEST(MatchAllOfAndOperator_159, ResultHasUsableInterface_159) {
    DummyA a;
    DummyB b;
    DummyC c;

    C::MatchAllOfGeneric<DummyA, DummyB> lhs(a, b);
    auto combined = std::move(lhs) && c;

    // Call describe(); we don't assert content, only that it is callable and returns a string.
    std::string desc = combined.describe();
    (void)desc; // Avoid unused warning
    SUCCEED() << "describe() is callable on the combined matcher";

    // Call match() on some argument type; we do not assert truthiness (black-box).
    int sample_arg = 42;
    bool res = combined.match(sample_arg);
    (void)res;
    SUCCEED() << "match() is callable on the combined matcher";
}
