// File: run_context_aborting_tests_514.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <climits>
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

// Minimal mock for IConfig. We only mock what RunContext::RunContext and
// RunContext::aborting use (name() and abortAfter()).
class MockConfig_514 : public Catch::IConfig {
public:
    // Signatures follow Catch2 v3 style (value return, const-qualified methods).
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));

    // The rest of IConfig's virtuals are not needed for these tests and are
    // provided by the actual library (or are non-pure virtual). If your local
    // headers mark them pure-virtual, you can stub them out trivially.
};

class RunContextAbortingTest_514 : public ::testing::Test {
protected:
    NiceMock<MockConfig_514> config_;

    // Helper to construct a RunContext with a given abortAfter value.
    Catch::RunContext makeContextWithAbortAfter_514(int abort_after) {
        // name() is used by RunContext ctor
        ON_CALL(config_, name()).WillByDefault(Return(Catch::StringRef("MockRun_514")));
        ON_CALL(config_, abortAfter()).WillByDefault(Return(abort_after));
        // Pass a null event listener; aborting() does not rely on reporter.
        return Catch::RunContext(&config_, Catch::IEventListenerPtr{});
    }
};

} // namespace

// Normal operation: with abortAfter == 1 and no recorded failures,
// aborting() should be false.
TEST_F(RunContextAbortingTest_514, AbortingFalseWhenThresholdNotReached_514) {
    auto ctx = makeContextWithAbortAfter_514(1);
    EXPECT_FALSE(ctx.aborting());
}

// Boundary: abortAfter == 0 should trigger immediate aborting (common Catch2 behavior).
TEST_F(RunContextAbortingTest_514, AbortingTrueWhenAbortAfterIsZero_514) {
    auto ctx = makeContextWithAbortAfter_514(0);
    EXPECT_TRUE(ctx.aborting());
}

// Boundary: very large threshold should not abort when no failures have occurred.
TEST_F(RunContextAbortingTest_514, AbortingFalseWhenAbortAfterIsHuge_514) {
    auto ctx = makeContextWithAbortAfter_514(INT_MAX);
    EXPECT_FALSE(ctx.aborting());
}

// Defensive/edge behavior: negative abortAfter (if ever provided) is cast to size_t,
// making the threshold effectively huge; result should be false when there are no failures.
TEST_F(RunContextAbortingTest_514, AbortingFalseWhenAbortAfterIsNegative_514) {
    auto ctx = makeContextWithAbortAfter_514(-1);
    EXPECT_FALSE(ctx.aborting());
}
