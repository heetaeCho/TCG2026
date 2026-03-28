// File: tests/range_function_tests_937.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include "Catch2/extras/catch_amalgamated.hpp"

// Detection idiom to check whether `Catch::Generators::range<T>` is well-formed
// with the signature range(T const&, T const&, T const&), without causing a
// hard compile error for negative cases.
template <typename T, typename = void>
struct is_range_invocable_937 : std::false_type {};

template <typename T>
struct is_range_invocable_937<
    T,
    std::void_t<
        decltype(
            Catch::Generators::range(
                std::declval<T const&>(),
                std::declval<T const&>(),
                std::declval<T const&>()
            )
        )
    >
> : std::true_type {};

template <typename T>
inline constexpr bool is_range_invocable_937_v = is_range_invocable_937<T>::value;

// ---- Tests ----

// Verifies that calling range with an arithmetic (non-bool) type is well-formed
TEST(RangeFunction_937, InvocableWithInt_937) {
    static_assert(std::is_arithmetic<int>::value && !std::is_same<int, bool>::value, "precondition");
    EXPECT_TRUE(is_range_invocable_937_v<int>);
}

TEST(RangeFunction_937, InvocableWithDouble_937) {
    static_assert(std::is_arithmetic<double>::value && !std::is_same<double, bool>::value, "precondition");
    EXPECT_TRUE(is_range_invocable_937_v<double>);
}

// Verifies that calling range with bool is NOT well-formed due to the static_assert in the template
TEST(RangeFunction_937, NotInvocableWithBool_937) {
    // The function template should be excluded when T is bool
    EXPECT_FALSE(is_range_invocable_937_v<bool>);
}

// Verifies that calling range with a non-numeric type is NOT well-formed
TEST(RangeFunction_937, NotInvocableWithString_937) {
    EXPECT_FALSE(is_range_invocable_937_v<std::string>);
}

// Verifies the return type for arithmetic types is GeneratorWrapper<T>
TEST(RangeFunction_937, ReturnsGeneratorWrapperForInt_937) {
    using Catch::Generators::GeneratorWrapper;
    auto wrapper = Catch::Generators::range(0, 10, 2);
    (void)wrapper; // suppress unused warning

    // Check the deduced type explicitly using decltype on an unevaluated expression
    using RetT = decltype(Catch::Generators::range(0, 10, 2));
    EXPECT_TRUE((std::is_same<RetT, GeneratorWrapper<int>>::value));
}

TEST(RangeFunction_937, ReturnsGeneratorWrapperForDouble_937) {
    using Catch::Generators::GeneratorWrapper;
    auto wrapper = Catch::Generators::range(0.0, 1.0, 0.1);
    (void)wrapper;

    using RetT = decltype(Catch::Generators::range(0.0, 1.0, 0.1));
    EXPECT_TRUE((std::is_same<RetT, GeneratorWrapper<double>>::value));
}

// (Boundary at the interface level)
// Confirms that mixed cv-qualifiers/references still match the declared signature T const&
// This does NOT test any iteration logic; it only checks that the function accepts const refs.
TEST(RangeFunction_937, AcceptsConstLvalueRefs_937) {
    const int s = 1, e = 5, step = 2;
    auto wrapper = Catch::Generators::range(s, e, step);
    (void)wrapper;

    using RetT = decltype(Catch::Generators::range(s, e, step));
    using Catch::Generators::GeneratorWrapper;
    EXPECT_TRUE((std::is_same<RetT, GeneratorWrapper<int>>::value));
}
