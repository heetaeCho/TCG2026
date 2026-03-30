// File: match_all_of_base_case_test_151.cpp

#include <gtest/gtest.h>
#include <array>
#include <string>
#include <utility>

// Include the header under test (path as provided in the prompt)
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

namespace {

using Catch::Matchers::Detail::match_all_of;

// A simple move-only type to verify perfect-forwarding compatibility.
struct MoveOnly {
    MoveOnly() = default;
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default;
};

// [Normal operation] N = 0 (boundary for the array size) with lvalue argument.
TEST(MatchAllOfBaseCaseTest_151, ReturnsTrueForEmptyIndexSequence_N0_151) {
    std::array<void const*, 0> arr{};
    int x = 42;

    bool result = match_all_of(x, arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// [Normal operation] N > 0 with rvalue argument; heterogeneous, valid object addresses.
TEST(MatchAllOfBaseCaseTest_151, ReturnsTrueForNonZeroNAndRvalueArg_151) {
    int a = 1, b = 2, c = 3;
    std::array<void const*, 3> arr{
        { static_cast<void const*>(&a),
          static_cast<void const*>(&b),
          static_cast<void const*>(&c) }
    };

    std::string s = "value";
    bool result = match_all_of(std::move(s), arr, std::index_sequence<>{});
    EXPECT_TRUE(result);
}

// [Boundary conditions] Works with N = 1; both lvalue and prvalue arguments.
TEST(MatchAllOfBaseCaseTest_151, ReturnsTrueForSingleElementArray_LvalueAndPrvalue_151) {
    int v = 7;
    std::array<void const*, 1> arr{ { static_cast<void const*>(&v) } };

    int x = 10;
    EXPECT_TRUE(match_all_of(x, arr, std::index_sequence<>{}));     // lvalue
    EXPECT_TRUE(match_all_of(99, arr, std::index_sequence<>{}));    // prvalue
}

// [Type coverage] Accepts const char* and const-qualified args; still returns true.
TEST(MatchAllOfBaseCaseTest_151, AcceptsConstQualifiedAndPointerArgs_151) {
    const char* cstr = "hello";
    std::array<void const*, 2> arr{
        { static_cast<void const*>(cstr),
          static_cast<void const*>(&cstr) }
    };

    const std::string cs = "const string";
    EXPECT_TRUE(match_all_of(cs, arr, std::index_sequence<>{}));
    EXPECT_TRUE(match_all_of(cstr, arr, std::index_sequence<>{}));
}

// [Edge-like type] Move-only type works for both lvalue and rvalue; return remains true.
TEST(MatchAllOfBaseCaseTest_151, WorksWithMoveOnlyArg_LvalueAndRvalue_151) {
    std::array<void const*, 1> arr{ { nullptr } };

    MoveOnly m;
    EXPECT_TRUE(match_all_of(m, arr, std::index_sequence<>{}));          // lvalue move-only
    EXPECT_TRUE(match_all_of(MoveOnly{}, arr, std::index_sequence<>{})); // rvalue move-only
}

// [Robustness] Array contents (including nullptr) do not affect the observable result.
TEST(MatchAllOfBaseCaseTest_151, IgnoresArrayContents_ReturnsTrueRegardless_151) {
    int x = 123;
    std::array<void const*, 3> arr_all_null{ { nullptr, nullptr, nullptr } };
    std::array<void const*, 3> arr_mixed{
        { static_cast<void const*>(&x), nullptr, static_cast<void const*>(&arr_all_null) }
    };

    EXPECT_TRUE(match_all_of(x, arr_all_null, std::index_sequence<>{}));
    EXPECT_TRUE(match_all_of(x, arr_mixed, std::index_sequence<>{}));
}

} // namespace
