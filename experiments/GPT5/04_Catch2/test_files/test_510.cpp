// File: run_context_exceptionEarlyReported_test_510.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the public interface only; we do not rely on private state.
#include "catch2/internal/catch_run_context.hpp"

namespace {

using Catch::RunContext;

// Helper: detect default-constructibility without instantiating tests that would fail to compile
template <typename T>
constexpr bool IsDefaultConstructibleV = std::is_default_constructible<T>::value;

// 1) API surface is present & addressable.
TEST(RunContextTest_510, ExceptionEarlyReported_IsPresent_510) {
    // Taking the address verifies the member exists with the expected signature.
    auto memfn = &RunContext::exceptionEarlyReported;
    (void)memfn;
    SUCCEED();
}

// 2) Calling it should not throw (normal operation).
TEST(RunContextTest_510, ExceptionEarlyReported_NoThrow_510) {
    if constexpr (IsDefaultConstructibleV<RunContext>) {
        RunContext ctx;
        EXPECT_NO_THROW(ctx.exceptionEarlyReported());
    } else {
        GTEST_SKIP() << "RunContext is not default-constructible in this build.";
    }
}

// 3) Calling it multiple times should be safe (idempotent behavior w.r.t. observable effects).
TEST(RunContextTest_510, ExceptionEarlyReported_MultipleCalls_NoThrow_510) {
    if constexpr (IsDefaultConstructibleV<RunContext>) {
        RunContext ctx;
        EXPECT_NO_THROW(ctx.exceptionEarlyReported());
        EXPECT_NO_THROW(ctx.exceptionEarlyReported());
        EXPECT_NO_THROW(ctx.exceptionEarlyReported());
    } else {
        GTEST_SKIP() << "RunContext is not default-constructible in this build.";
    }
}

// 4) Indirect call via pointer-to-member should also work (verifies visibility/signature).
TEST(RunContextTest_510, ExceptionEarlyReported_CallViaMemberPointer_510) {
    if constexpr (IsDefaultConstructibleV<RunContext>) {
        RunContext ctx;
        void (RunContext::*pmf)() = &RunContext::exceptionEarlyReported;
        EXPECT_NO_THROW((ctx.*pmf)());
        EXPECT_NO_THROW((ctx.*pmf)());
    } else {
        GTEST_SKIP() << "RunContext is not default-constructible in this build.";
    }
}

}  // namespace
