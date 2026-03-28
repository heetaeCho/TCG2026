// File: tests/approx_friend_eq_694.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

// ---------- Detection utilities (compile-time; no internal access) ----------
namespace {
    // is_eq_wellformed<L, R> -> true if the expression (std::declval<L>() == std::declval<R>()) is well-formed
    template <typename, typename, typename = void>
    struct is_eq_wellformed : std::false_type {};

    template <typename L, typename R>
    struct is_eq_wellformed<L, R, std::void_t<decltype(std::declval<L>() == std::declval<R>())>>
        : std::true_type {};

    struct NotConvertible {}; // not constructible to double
} // namespace

// ----------------------- Compile-time/SFINAE checks -------------------------
static_assert(!std::is_constructible_v<double, NotConvertible>,
              "Sanity: NotConvertible should not be constructible to double");

// The friend operator== (Approx, T) and its counterpart (T, Approx) should
// not be viable when T is not constructible to double.
static_assert(!is_eq_wellformed<Approx, NotConvertible>::value,
              "operator==(Approx, NotConvertible) should be disabled by SFINAE");
static_assert(!is_eq_wellformed<NotConvertible, Approx>::value,
              "operator==(NotConvertible, Approx) should be disabled by SFINAE");

// ------------------------------ Test fixture -------------------------------
class ApproxEqTests_694 : public ::testing::Test {};

// 1) Normal operation: exact same numeric value, both directions
TEST_F(ApproxEqTests_694, IntEqualsApprox_BothDirections_694) {
    Approx a = Approx(42.0);
    int rhs = 42;

    // These exercise the friend operator==(Approx, T) and the opposite direction.
    EXPECT_TRUE(a == rhs);
    EXPECT_TRUE(rhs == a);
}

// 2) Normal operation: within an absolute margin, both directions
TEST_F(ApproxEqTests_694, WithinMargin_BothDirections_694) {
    Approx a = Approx(1.0).margin(0.5);  // public API only
    double rhs = 1.4;

    EXPECT_TRUE(a == rhs);
    EXPECT_TRUE(rhs == a);
}

// 3) Boundary/negative case: clearly outside any reasonable tolerance -> false
//    (We pick a very distant value to avoid relying on internal epsilon/scale details.)
TEST_F(ApproxEqTests_694, FarOutsideTolerance_BothDirections_694) {
    Approx a = Approx(1.0);    // default tolerances
    double rhs = 100.0;        // very far away

    EXPECT_FALSE(a == rhs);
    EXPECT_FALSE(rhs == a);
}

// 4) Type coverage: other types constructible to double should work in both directions
TEST_F(ApproxEqTests_694, OtherArithmeticTypesConstructibleToDouble_694) {
    long double ld = 2.0L;
    float f = 3.0f;
    long long ll = 7;

    EXPECT_TRUE(Approx(2.0) == ld);
    EXPECT_TRUE(ld == Approx(2.0));

    EXPECT_TRUE(Approx(3.0) == f);
    EXPECT_TRUE(f == Approx(3.0));

    EXPECT_TRUE(Approx(7.0) == ll);
    EXPECT_TRUE(ll == Approx(7.0));
}

// 5) Public API chaining sanity: carry configuration through operator() and compare both ways
TEST_F(ApproxEqTests_694, ConfigurationChainingWithCallOperator_694) {
    // Start from a custom-configured Approx and switch the target value via operator()
    auto cfg = Approx::custom().epsilon(0.01).margin(0.1);  // use only public APIs
    Approx a = cfg(10.0);                                   // call-operator produces a configured Approx for value 10

    double near = 10.05; // within 0.1 margin
    EXPECT_TRUE(a == near);
    EXPECT_TRUE(near == a);
}
