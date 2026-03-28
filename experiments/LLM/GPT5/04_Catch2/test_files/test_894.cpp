// File: tests/benchmark_function_move_assign_894.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <vector>

// Include the provided interface (amalgamated header)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
using BF = Catch::Benchmark::Detail::BenchmarkFunction;

// ---- Compile-time interface properties ----
static_assert(std::is_move_constructible<BF>::value,
              "BenchmarkFunction should be move-constructible");
static_assert(std::is_move_assignable<BF>::value,
              "BenchmarkFunction should be move-assignable");
static_assert(std::is_nothrow_move_assignable<BF>::value,
              "BenchmarkFunction move-assignment should be noexcept");

static_assert(!std::is_copy_constructible<BF>::value,
              "BenchmarkFunction should not be copy-constructible");
static_assert(!std::is_copy_assignable<BF>::value,
              "BenchmarkFunction should not be copy-assignable");
} // namespace

// TEST_ID: 894
TEST(BenchmarkFunction_MoveAssign_894, ReturnsSelfReference_894) {
    // Arrange: construct two distinct callables; actual invocation is not required
    // for testing move-assignment return semantics.
    auto f1 = [] (auto /*meter*/) {};
    auto f2 = [] (auto /*meter*/) {};

    BF lhs(f2);
    BF rhs(f1);

    // Act: move-assign and capture the return reference
    BF* lhs_addr = &lhs;
    BF& ret = (lhs = std::move(rhs));

    // Assert: operator= returns *this (self reference)
    EXPECT_EQ(&ret, lhs_addr);
}

// TEST_ID: 894
TEST(BenchmarkFunction_MoveAssign_894, NoThrowOnMoveAssignment_894) {
    auto f1 = [] (auto /*meter*/) {};
    auto f2 = [] (auto /*meter*/) {};

    BF a(f1);
    BF b(f2);

    // Act & Assert: move-assign should be noexcept at runtime as well
    EXPECT_NO_THROW( b = std::move(a) );
}

// TEST_ID: 894
TEST(BenchmarkFunction_MoveAssign_894, SupportsChainedMoveAssignment_894) {
    auto f1 = [] (auto /*meter*/) {};
    auto f2 = [] (auto /*meter*/) {};
    auto f3 = [] (auto /*meter*/) {};

    BF x(f1);
    BF y(f2);
    BF z(f3);

    // Compile-time: ensure operator= returns BF&
#if defined(__cpp_decltype)
    static_assert(std::is_same<decltype((y = std::move(x))), BF&>::value,
                  "operator= should return BF&");
#endif

    // Runtime: chained move-assign should bind to the leftmost object
    BF* z_addr = &z;
    BF& ret = (z = (y = std::move(x)));

    EXPECT_EQ(&ret, z_addr);
}

// TEST_ID: 894
TEST(BenchmarkFunction_MoveAssign_894, WorksInStdVectorAndRemainsValid_894) {
    auto f1 = [] (auto /*meter*/) {};
    auto f2 = [] (auto /*meter*/) {};

    std::vector<BF> vec;
    vec.emplace_back(f1);
    vec.emplace_back(f2);

    ASSERT_EQ(vec.size(), 2u);

    // Move-assign inside a container should be a valid operation and not throw
    EXPECT_NO_THROW( vec[1] = std::move(vec[0]) );

    // Vector shape (size) remains unchanged; we do not assume anything about
    // moved-from object's callable state.
    EXPECT_EQ(vec.size(), 2u);
}
