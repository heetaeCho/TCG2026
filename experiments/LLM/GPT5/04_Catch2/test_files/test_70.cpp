// File: stream_end_stop_tests_70.cpp
#include <gtest/gtest.h>

// SUT header (as provided)
#include "catch2/internal/catch_stream_end_stop.hpp"

// These tests intentionally avoid asserting anything about StringRef's internals
// (size/contents/equality), because that behavior is not part of the provided interface.

namespace {

using Catch::StreamEndStop;

// ---- Compile-time (interface) checks ----

// The expression type of +StreamEndStop{} must be Catch::StringRef.
static_assert(std::is_same_v<decltype(+StreamEndStop{}), Catch::StringRef>,
              "Unary + on StreamEndStop must return Catch::StringRef");

// The operator+ is declared constexpr; ensure the expression is usable in a constexpr context.
constexpr auto kConstexprProbe_70 = +StreamEndStop{};  // fails to compile if not constexpr

// ---- Runtime tests (observable interface only) ----

TEST(StreamEndStopTest_70, UnaryPlus_ReturnsStringRefType_70) {
  // Mirror the static_assert in a runtime assertion so failure shows in test output too.
  EXPECT_TRUE((std::is_same_v<decltype(+StreamEndStop{}), Catch::StringRef>));
}

TEST(StreamEndStopTest_70, UnaryPlus_IsUsableInConstexpr_70) {
  // If this compiles, the constexpr guarantee from the interface is honored.
  constexpr auto sr = +StreamEndStop{};
  (void)sr;  // suppress unused warning
  SUCCEED(); // Explicitly mark that reaching here is success.
}

TEST(StreamEndStopTest_70, UnaryPlus_DoesNotThrowAtRuntime_70) {
  // We don't assume noexcept in the signature, but we can at least verify no exception is thrown.
  EXPECT_NO_THROW({
    auto sr = +StreamEndStop{};
    (void)sr;
  });
}

} // namespace
