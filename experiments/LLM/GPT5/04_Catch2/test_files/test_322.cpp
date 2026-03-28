// File: table_tests_322.cpp
#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <cstring> // for std::strcmp

// ---------- Test doubles in the same namespace to intercept calls ----------
namespace Catch { namespace Generators {

// Minimal stand-in for the production wrapper to capture what `table` returns.
// This is a *test double*, not a reimplementation of behavior.
template <typename T>
struct GeneratorWrapper {
    using CapturedType = T;
    std::vector<T> captured;

    GeneratorWrapper() = default;

    // Construct from initializer_list to store forwarded tuples
    explicit GeneratorWrapper(std::initializer_list<T> il) : captured(il) {}
};

// Shim for `values<T>(initializer_list<T>)` that `table` calls.
// It simply returns a GeneratorWrapper<T> containing the input items.
template <typename T>
GeneratorWrapper<T> values(std::initializer_list<T> il) {
    return GeneratorWrapper<T>(il);
}

// --------------------- Code under test (given) ---------------------
template <typename... Ts>
GeneratorWrapper<std::tuple<std::decay_t<Ts>...>> table(
    std::initializer_list<std::tuple<std::decay_t<Ts>...>> tuples
) {
    return values<std::tuple<Ts...>>(tuples);
}

}} // namespace Catch::Generators

using Catch::Generators::GeneratorWrapper;
using Catch::Generators::table;

// ------------------------------ Tests ------------------------------

struct TableGeneratorTest_322 : ::testing::Test {};

// Normal operation: returns a wrapper containing the provided tuples
TEST_F(TableGeneratorTest_322, ReturnsWrapperWithProvidedTuples_322) {
    auto gw = table<int, const char*>({ {1, "a"}, {2, "b"} });

    // Type check (compile-time): returned wrapper holds tuples of <int, const char*>
    static_assert(std::is_same_v<decltype(gw), GeneratorWrapper<std::tuple<int, const char*>>>,
                  "Return type must be GeneratorWrapper<std::tuple<int, const char*>>");

    ASSERT_EQ(gw.captured.size(), 2u);

    // Verify the first tuple contents
    EXPECT_EQ(std::get<0>(gw.captured[0]), 1);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[0]), "a"), 0);

    // Verify the second tuple contents
    EXPECT_EQ(std::get<0>(gw.captured[1]), 2);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[1]), "b"), 0);
}

// Boundary condition: empty initializer_list should be handled
TEST_F(TableGeneratorTest_322, HandlesEmptyInitializerList_322) {
    auto gw = table<int, const char*>({}); // empty
    ASSERT_TRUE(gw.captured.empty());
}

// Order preservation: elements are yielded in the same order as provided
TEST_F(TableGeneratorTest_322, PreservesOrderOfTuples_322) {
    auto gw = table<int, const char*>({ {10, "x"}, {20, "y"}, {30, "z"} });
    ASSERT_EQ(gw.captured.size(), 3u);

    EXPECT_EQ(std::get<0>(gw.captured[0]), 10);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[0]), "x"), 0);

    EXPECT_EQ(std::get<0>(gw.captured[1]), 20);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[1]), "y"), 0);

    EXPECT_EQ(std::get<0>(gw.captured[2]), 30);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[2]), "z"), 0);
}

// Type conformance: return type uses std::decay_t<Ts> in the tuple
// (Here Ts are already decayed; we assert exact type to catch mismatches.)
TEST_F(TableGeneratorTest_322, ReturnTypeMatchesDecayedTuple_322) {
    using Ret = decltype(table<int, const char*>({ {3, "c"} }));
    // Ensure the wrapper holds tuple<int, const char*> (decayed)
    static_assert(std::is_same_v<typename Ret::CapturedType, std::tuple<int, const char*>>,
                  "CapturedType must be std::tuple<decay_t<int>, decay_t<const char*>>");
    // Basic sanity on captured content
    Ret gw = table<int, const char*>({ {3, "c"} });
    ASSERT_EQ(gw.captured.size(), 1u);
    EXPECT_EQ(std::get<0>(gw.captured[0]), 3);
    EXPECT_EQ(std::strcmp(std::get<1>(gw.captured[0]), "c"), 0);
}
