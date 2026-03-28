// File: get_result_capture_tests_521.cpp

#include <gtest/gtest.h>

// The partial code places these in namespace Catch.
// We include the minimal declarations we need as externals.
// In your actual project, prefer including the right Catch2 headers instead.
namespace Catch {
    class IResultCapture; // forward decl is enough for calling the function
    IResultCapture& getResultCapture(); // under test
}

// NOTE: We intentionally limit ourselves to calling getResultCapture()
// and asserting the observable outcome (exception) when there is no active
// result capture in the current context. We do not construct or mock
// IResultCapture, because its full interface is not provided here,
// and doing so would risk re-implementing/inventing internals.

// Test fixture kept empty on purpose — no state assumptions made.
class GetResultCaptureTest_521 : public ::testing::Test {};

// [Behavior] When there is no active result-capture in the context,
//            getResultCapture triggers an internal error (observable as an exception).
TEST_F(GetResultCaptureTest_521, ThrowsIfNoResultCapture_521) {
    // We assert that calling getResultCapture() without prior setup
    // leads to an exception. We use EXPECT_ANY_THROW to avoid assuming
    // a specific exception type from internal macros.
    EXPECT_ANY_THROW({
        (void)Catch::getResultCapture();
    });
}

// [Behavior] Repeated calls remain erroring if the context still lacks
//            a result-capture (idempotent failure in the same state).
TEST_F(GetResultCaptureTest_521, RepeatedCallsStillThrowWithoutCapture_521) {
    EXPECT_ANY_THROW({
        (void)Catch::getResultCapture();
    });
    EXPECT_ANY_THROW({
        (void)Catch::getResultCapture();
    });
}
