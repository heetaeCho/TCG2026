// tests/binaryexpr_smoketest_120.cpp
#include <type_traits>
#include "catch2/internal/catch_decomposer.hpp"
#include <gtest/gtest.h>

namespace {
using Catch::BinaryExpr;
}

// Ensures the public type is available and includable.
// Does NOT instantiate operator== (which would fail at compile time).
TEST(BinaryExprTest_120, TypeIsUsableAsAClass_120) {
  // Black-box: we only validate that BinaryExpr is a class type that can be named.
  EXPECT_TRUE(std::is_class<BinaryExpr>::value);
}

// Intentionally avoid anything that would form/instantiate operator==,
// because the interface guarantees it hard-fails via static_assert.
