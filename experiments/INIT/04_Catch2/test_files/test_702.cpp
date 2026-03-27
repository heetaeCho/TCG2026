// File: tests/approx_margin_702_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <limits>

// Include the public header under test
#include "Catch2/src/catch2/catch_approx.hpp"

namespace {

// ---------- SFINAE detector: is margin(T) well-formed? ----------
template <typename U>
using margin_expr_t = decltype(std::declval<Catch::Approx&>().margin(std::declval<U const&>()));

template <typename U, typename = void>
struct has_margin : std::false_type {};

template <typename U>
struct has_margin<U, std::void_t<margin_expr_t<U>>> : std::true_type {};

// Types for invocability checks
struct ConvertibleToDouble {
    // NOLINTNEXTLINE(google-explicit-constructor)
    operator double() const { return 0.5; }
};

struct NotConvertibleToDouble {
    // no conversion operators
};

class ApproxMarginTest_702 : public ::testing::Test {
protected:
    Catch::Approx makeApprox(double v = 1.23) { return Catch::Approx(v); }
};

} // namespace

// --- Normal operation: returns self reference and is chainable ---
TEST_F(ApproxMarginTest_702, ReturnsSelfReference_702) {
    auto a = makeApprox(42.0);
    auto& r = a.margin(0.1);
    EXPECT_EQ(&r, &a);
}

TEST_F(ApproxMarginTest_702, FluentChainingReturnsSelf_702) {
    auto a = makeApprox();
    auto& r = a.margin(0.1).margin(0.2).margin(0.3);
    EXPECT_EQ(&r, &a);
}

// --- Type acceptance (interface-level): arithmetic & convertible types ---
TEST_F(ApproxMarginTest_702, AcceptsArithmeticTypes_702) {
    auto a = makeApprox();
    // If any of these are ill-formed, the test won't compile.
    auto& r1 = a.margin(1);                       // int
    auto& r2 = a.margin(1u);                      // unsigned
    auto& r3 = a.margin(1.0f);                    // float
    auto& r4 = a.margin(1.0);                     // double
    long double ld = 1.0L;
    auto& r5 = a.margin(ld);                      // long double

    EXPECT_EQ(&r1, &a);
    EXPECT_EQ(&r2, &a);
    EXPECT_EQ(&r3, &a);
    EXPECT_EQ(&r4, &a);
    EXPECT_EQ(&r5, &a);
}

TEST_F(ApproxMarginTest_702, AcceptsCustomTypeConvertibleToDouble_702) {
    auto a = makeApprox();
    ConvertibleToDouble c{};
    auto& r = a.margin(c);
    EXPECT_EQ(&r, &a);
}

// --- Compile-time invocability (boundary on template constraints) ---
TEST_F(ApproxMarginTest_702, InvocabilityMatchesIsConstructibleToDouble_702) {
    // Positive cases
    static_assert(has_margin<int>::value, "margin(int) should be invocable");
    static_assert(has_margin<double>::value, "margin(double) should be invocable");
    static_assert(has_margin<long double>::value, "margin(long double) should be invocable");
    static_assert(has_margin<ConvertibleToDouble>::value, "margin(ConvertibleToDouble) should be invocable");

    // Negative case
    static_assert(!has_margin<NotConvertibleToDouble>::value,
                  "margin(NotConvertibleToDouble) should NOT be invocable");
    SUCCEED(); // run-time success marker so the test isn't empty
}

// --- Boundary/exceptional values: zero, huge, infinities, NaN ---
// Note: We only assert that the call succeeds and returns self (observable behavior).
TEST_F(ApproxMarginTest_702, HandlesZeroMargin_702) {
    auto a = makeApprox();
    EXPECT_NO_THROW({
        auto& r = a.margin(0.0);
        EXPECT_EQ(&r, &a);
    });
}

TEST_F(ApproxMarginTest_702, HandlesLargeMargin_702) {
    auto a = makeApprox();
    const double big = std::numeric_limits<double>::max();
    EXPECT_NO_THROW({
        auto& r = a.margin(big);
        EXPECT_EQ(&r, &a);
    });
}

TEST_F(ApproxMarginTest_702, HandlesInfinityMargin_702) {
    auto a = makeApprox();
    const double inf = std::numeric_limits<double>::infinity();
    EXPECT_NO_THROW({
        auto& r1 = a.margin(inf);
        EXPECT_EQ(&r1, &a);
        auto& r2 = a.margin(-inf);
        EXPECT_EQ(&r2, &a);
    });
}

TEST_F(ApproxMarginTest_702, HandlesNaNMargin_702) {
    auto a = makeApprox();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_NO_THROW({
        auto& r = a.margin(nan);
        EXPECT_EQ(&r, &a);
    });
}

