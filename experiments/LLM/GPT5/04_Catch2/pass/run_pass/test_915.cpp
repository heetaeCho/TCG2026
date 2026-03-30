// File: tests/benchmark_bool_op_915.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the provided amalgamated header (black-box under test)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
  // Bring the class under test into a short alias for clarity.
  using BenchmarkT = ::Catch::Benchmark::Benchmark;
}

// ---------- Compile-time properties (no behavior reimplementation) ----------

// Ensure the boolean conversion is explicit (no implicit conversion to bool).
// This uses type traits only; it does not rely on any private state.
static_assert(!std::is_convertible<BenchmarkT, bool>::value,
              "Benchmark should not be implicitly convertible to bool (explicit operator expected)");

// (Optional) Explicit conversions are allowed via static_cast, which we will
// validate at runtime below. We do not assert std::is_constructible<bool, BenchmarkT>
// because it also checks implicit paths — explicit conversion is validated with static_cast.

// ------------------------------- Runtime tests -------------------------------

TEST(BenchmarkBoolOpTest_915, BoolOp_ReturnsTrue_WithNameOnly_915) {
  // Arrange: construct via the name-only constructor (no assumptions about internals)
  BenchmarkT bm(std::string{"noop"});

  // Act + Assert: explicit cast to bool is allowed and should be true (observable behavior)
  EXPECT_TRUE(static_cast<bool>(bm));
}

TEST(BenchmarkBoolOpTest_915, BoolOp_ReturnsTrue_WithNameAndCallable_915) {
  // Arrange: construct via the name + callable constructor
  auto callable = []() { /* no-op; behavior is black-box */ };
  BenchmarkT bm(std::string{"with-fun"}, callable);

  // Act + Assert
  EXPECT_TRUE(static_cast<bool>(bm));
}

TEST(BenchmarkBoolOpTest_915, BoolOp_ReturnsTrue_WithEmptyName_Boundary_915) {
  // Arrange: boundary case — empty benchmark name
  BenchmarkT bm(std::string{""});

  // Act + Assert
  EXPECT_TRUE(static_cast<bool>(bm));
}
