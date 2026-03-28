// File: tests/approx_scale_tests_703.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the header under test
#include "catch2/catch_approx.hpp"

namespace {

using Catch::Approx;

// Helper trait: does `Approx&.scale(const U&)` form a valid expression?
template <typename U, typename = void>
struct has_scale_with : std::false_type {};

template <typename U>
struct has_scale_with<U, std::void_t<
    decltype(std::declval<Approx&>().scale(std::declval<const U&>()))
>> : std::true_type {};

struct ConvertibleToDouble {
    // Explicit conversion to double should satisfy std::is_constructible<double, T>
    explicit operator double() const { return 42.0; }
};

// A simple fixture if we ever need shared setup later
class ApproxScaleTest_703 : public ::testing::Test {};

} // namespace

// ---- Compile-time acceptance/rejection (SFINAE) -----------------------------

TEST_F(ApproxScaleTest_703, ScaleAcceptsArithmeticTypes_703) {
    // These lines must compile and return Approx& (fluency)
    Approx a{0.0};
    Approx& r1 = a.scale(1);           // int
    Approx& r2 = a.scale(1.5f);        // float
    Approx& r3 = a.scale(2.25);        // double
    long double ld = 3.0L;
    Approx& r4 = a.scale(ld);          // long double

    // All returns should alias the same object (fluent interface)
    EXPECT_EQ(&r1, &a);
    EXPECT_EQ(&r2, &a);
    EXPECT_EQ(&r3, &a);
    EXPECT_EQ(&r4, &a);
}

TEST_F(ApproxScaleTest_703, ScaleAcceptsUserDefinedTypeConvertibleToDouble_703) {
    // Should be well-formed due to conversion to double
    static_assert(std::is_constructible<double, ConvertibleToDouble>::value,
                  "ConvertibleToDouble must be constructible to double");

    Approx a{0.0};
    Approx& r = a.scale(ConvertibleToDouble{});
    EXPECT_EQ(&r, &a); // still returns self
}

TEST_F(ApproxScaleTest_703, ScaleRejectsNonConvertibleTypesAtCompileTime_703) {
    // Using detection idiom against the actual member template
    static_assert(!has_scale_with<std::string>::value,
                  "scale(std::string) must be disabled (not convertible to double)");
    struct NotConvertible {};
    static_assert(!has_scale_with<NotConvertible>::value,
                  "scale(NotConvertible) must be disabled (not convertible to double)");
}

// ---- Runtime, observable interface behavior (no peeking into internals) -----

TEST_F(ApproxScaleTest_703, ScaleIsFluentAndChainableWithOtherModifiers_703) {
    // We only verify chainability and that each step returns the same object.
    Approx a{123.0};

    // Chain scale with other public modifiers mentioned in the interface.
    // We do NOT assert any internal numeric effects.
    Approx& r1 = a.scale(2.0);
    Approx& r2 = r1.epsilon(0.001);
    Approx& r3 = r2.margin(0.5);

    EXPECT_EQ(&r1, &a);
    EXPECT_EQ(&r2, &a);
    EXPECT_EQ(&r3, &a);
}

TEST_F(ApproxScaleTest_703, ScaleCanBeInvokedMultipleTimesSafely_703) {
    // Repeated calls should remain well-formed and keep returning self.
    Approx a{0.0};
    Approx& r1 = a.scale(1.0);
    Approx& r2 = a.scale(10);    // different type
    Approx& r3 = a.scale(0.001f);

    EXPECT_EQ(&r1, &a);
    EXPECT_EQ(&r2, &a);
    EXPECT_EQ(&r3, &a);
}

// ---- Boundary-ish inputs (still via public interface only) ------------------

TEST_F(ApproxScaleTest_703, ScaleHandlesExtremeFiniteValues_703) {
    Approx a{0.0};
    // Large and small finite doubles should be acceptable as they are convertible.
    const double large = std::numeric_limits<double>::max();
    const double small = std::numeric_limits<double>::min(); // smallest positive normal

    EXPECT_EQ(&a.scale(large), &a);
    EXPECT_EQ(&a.scale(small), &a);
}

// Note: We intentionally do NOT assert specific comparison outcomes or internal
// state changes (e.g., effects on equality tolerances), because those would
// require knowledge of private implementation details. The tests stick to
// verifying the public surface: template constraints, call validity, and
// fluent/chainable behavior returning the same object reference.

