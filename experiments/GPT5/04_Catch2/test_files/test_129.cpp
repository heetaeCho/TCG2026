// Decomposer_operator_le_tests_129.cpp

#include <type_traits>
#include <gtest/gtest.h>

// Include the interface under test (as provided)
#include "Catch2/src/catch2/internal/catch_decomposer.hpp"

// ---------- Small helpers for type inspection (public, non-invasive) ----------

// Extract inner template argument from Catch::ExprLhs<Inner>
template <typename T>
struct ExprLhsInner_129;

template <typename Inner>
struct ExprLhsInner_129<Catch::ExprLhs<Inner>> { using type = Inner; };

// Detection: is the expression (D <= X) well-formed?
template <typename D, typename X, typename = void>
struct is_leq_invocable_129 : std::false_type {};

template <typename D, typename X>
struct is_leq_invocable_129<D, X, std::void_t<decltype(std::declval<D>() <= std::declval<X>())>>
    : std::true_type {};


// ======================= TESTS =======================

TEST(DecomposerOperatorLE_129, LvalueIntReturnsConstRefExprLhs_129) {
    int x = 42;

    using Result = decltype(Catch::Decomposer{} <= x);
    using Inner = typename ExprLhsInner_129<Result>::type;

    // Compile-time guarantees
    static_assert(std::is_reference_v<Inner>, "Inner must be a reference");
    static_assert(std::is_const_v<std::remove_reference_t<Inner>>, "Inner referent must be const");

    // Runtime mirrors (not strictly necessary, but keeps the test green if compiled)
    EXPECT_TRUE((std::is_reference_v<Inner>));
    EXPECT_TRUE((std::is_const_v<std::remove_reference_t<Inner>>));
}

TEST(DecomposerOperatorLE_129, RvalueIntReturnsConstRefExprLhs_129) {
    using Result = decltype(Catch::Decomposer{} <= 7);
    using Inner  = typename ExprLhsInner_129<Result>::type;

    static_assert(std::is_reference_v<Inner>, "Inner must be a reference");
    static_assert(std::is_const_v<std::remove_reference_t<Inner>>, "Inner referent must be const");

    EXPECT_TRUE((std::is_reference_v<Inner>));
    EXPECT_TRUE((std::is_const_v<std::remove_reference_t<Inner>>));
}

TEST(DecomposerOperatorLE_129, ConstLvalueIntReturnsConstRefExprLhs_129) {
    const int cx = 5;

    using Result = decltype(Catch::Decomposer{} <= cx);
    using Inner  = typename ExprLhsInner_129<Result>::type;

    static_assert(std::is_reference_v<Inner>, "Inner must be a reference");
    static_assert(std::is_const_v<std::remove_reference_t<Inner>>, "Inner referent must be const");

    EXPECT_TRUE((std::is_reference_v<Inner>));
    EXPECT_TRUE((std::is_const_v<std::remove_reference_t<Inner>>));
}

TEST(DecomposerOperatorLE_129, LvalueDoubleReturnsConstRefExprLhs_129) {
    double d = 3.14;

    using Result = decltype(Catch::Decomposer{} <= d);
    using Inner  = typename ExprLhsInner_129<Result>::type;

    static_assert(std::is_reference_v<Inner>, "Inner must be a reference");
    static_assert(std::is_const_v<std::remove_reference_t<Inner>>, "Inner referent must be const");

    EXPECT_TRUE((std::is_reference_v<Inner>));
    EXPECT_TRUE((std::is_const_v<std::remove_reference_t<Inner>>));
}

// Verifies the function’s constraint that it accepts an rvalue Decomposer only.
TEST(DecomposerOperatorLE_129, OnlyAcceptsRvalueDecomposer_129) {
    // Expression must be invocable with rvalue Decomposer
    constexpr bool ok_with_rvalue =
        is_leq_invocable_129<Catch::Decomposer&&, int>::value;

    // And NOT invocable with lvalue Decomposer (since parameter is Decomposer&&)
    constexpr bool ok_with_lvalue =
        is_leq_invocable_129<Catch::Decomposer&, int>::value;

    EXPECT_TRUE(ok_with_rvalue);
    EXPECT_FALSE(ok_with_lvalue);
}

// Sanity check with a user-defined type (no assumptions about capture_by_value specifics).
struct Widget_129 { int v{0}; };

TEST(DecomposerOperatorLE_129, UserDefinedTypeReturnsConstRefExprLhs_129) {
    Widget_129 w;

    using Result = decltype(Catch::Decomposer{} <= w);
    using Inner  = typename ExprLhsInner_129<Result>::type;

    static_assert(std::is_reference_v<Inner>, "Inner must be a reference");
    static_assert(std::is_const_v<std::remove_reference_t<Inner>>, "Inner referent must be const");

    EXPECT_TRUE((std::is_reference_v<Inner>));
    EXPECT_TRUE((std::is_const_v<std::remove_reference_t<Inner>>));
}
