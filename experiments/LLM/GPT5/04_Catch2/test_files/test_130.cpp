// File: test_decomposer_operator_le_130.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include <utility>

// Adjust include path if your build sets the include root differently.
#include <catch2/internal/catch_decomposer.hpp>

namespace {
template <typename D, typename U, typename = void>
struct is_le_invocable : std::false_type {};

template <typename D, typename U>
struct is_le_invocable<D, U, std::void_t<decltype(std::declval<D>() <= std::declval<U>())>>
    : std::true_type {};
}  // namespace

// 1) Normal operation with a fundamental type: returns ExprLhs<int>
TEST(DecomposerOperatorLE_130, ReturnsExprLhsForInt_130) {
    using namespace Catch;
    using T = int;

    auto result = Decomposer{} <= T{42};
    (void)result;

    static_assert(std::is_same<decltype(result), ExprLhs<T>>::value,
                  "operator<= should return ExprLhs<T> for fundamental types");
    SUCCEED();
}

// 2) Normal operation with a std::string (copyable, value type)
TEST(DecomposerOperatorLE_130, ReturnsExprLhsForStdString_130) {
    using namespace Catch;
    using T = std::string;

    auto result = Decomposer{} <= T{"hello"};
    (void)result;

    static_assert(std::is_same<decltype(result), ExprLhs<T>>::value,
                  "operator<= should return ExprLhs<T> for std::string");
    SUCCEED();
}

// 3) Boundary: top-level const on the value should decay for by-value parameter
TEST(DecomposerOperatorLE_130, DecaysTopLevelConstOnValue_130) {
    using namespace Catch;
    const int ci = 7;

    auto result = Decomposer{} <= ci;
    (void)result;

    static_assert(std::is_same<decltype(result), ExprLhs<int>>::value,
                  "Top-level const should not affect deduced T for by-value param");
    SUCCEED();
}

// 4) Boundary: requires rvalue Decomposer (friend takes Decomposer&&)
TEST(DecomposerOperatorLE_130, InvocableOnlyWithRvalueDecomposer_130) {
    using namespace Catch;
    // Must be invocable with rvalue Decomposer
    static_assert(is_le_invocable<Decomposer&&, int>::value,
                  "operator<= should be invocable with rvalue Decomposer");

    // Should NOT be invocable with lvalue Decomposer (signature requires rvalue)
    static_assert(!is_le_invocable<Decomposer&, int>::value,
                  "operator<= should not be invocable with lvalue Decomposer");
    SUCCEED();
}

// 5) Normal operation with string literal (pointer type after decay)
TEST(DecomposerOperatorLE_130, WorksWithStringLiteral_130) {
    using namespace Catch;

    auto result = Decomposer{} <= "abc"; // argument decays to const char*
    (void)result;

    using Expected = ExprLhs<const char*>;
    static_assert(std::is_same<decltype(result), Expected>::value,
                  "operator<= should deduce T as const char* for string literals");
    SUCCEED();
}
