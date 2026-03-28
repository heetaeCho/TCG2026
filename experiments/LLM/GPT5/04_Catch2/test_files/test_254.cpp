// File: context_set_result_capture_tests_254.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers from the prompt (paths preserved)
#include "Catch2/src/catch2/internal/catch_context.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"

namespace {

using Catch::Context;
using Catch::IResultCapture;

// Minimal concrete type to obtain an IResultCapture* for tests.
// We never call any of its virtual methods.
struct DummyResultCapture final : IResultCapture {};

// Test suite focuses strictly on observable behavior via public API:
// - getResultCapture()
// - setResultCapture(IResultCapture*)

TEST(ContextTest_254, DefaultResultCaptureIsNull_254) {
    Context ctx;
    // Initially, result capture should be null (observable via the getter).
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST(ContextTest_254, SetResultCaptureStoresPointer_254) {
    Context ctx;
    auto* rc = new DummyResultCapture();  // intentionally not deleted (avoid dtor linkage)
    ctx.setResultCapture(rc);

    // Getter should expose the same pointer we set.
    EXPECT_EQ(ctx.getResultCapture(), rc);
}

TEST(ContextTest_254, OverwritingResultCaptureUpdatesPointer_254) {
    Context ctx;
    auto* first = new DummyResultCapture();   // leak on purpose for safety in isolated test
    auto* second = new DummyResultCapture();  // leak on purpose for safety in isolated test

    ctx.setResultCapture(first);
    ASSERT_EQ(ctx.getResultCapture(), first);  // sanity check of prior state

    ctx.setResultCapture(second);
    EXPECT_EQ(ctx.getResultCapture(), second); // pointer should now be updated
}

TEST(ContextTest_254, SettingNullClearsResultCapture_254) {
    Context ctx;
    auto* rc = new DummyResultCapture();  // leak on purpose for safety in isolated test
    ctx.setResultCapture(rc);
    ASSERT_NE(ctx.getResultCapture(), nullptr);  // ensure precondition

    // Boundary case: setting nullptr should be observable via getter.
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

} // namespace
