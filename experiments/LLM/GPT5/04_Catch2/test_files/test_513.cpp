// File: run_context_assertionPassed_test_513.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

using ::testing::NiceMock;
using ::testing::ReturnRef;

namespace {

// Minimal mock for IConfig based solely on what the RunContext
// constructor observably uses in this exercise: name()
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(const std::string&, name, (), (const, override));
    // NOTE: If your local IConfig has additional pure virtuals,
    // provide trivial overrides here (returning safe defaults).
};

} // namespace

// Test fixture providing a constructed RunContext with a mock config.
// Reporter is left as a null pointer, which is acceptable for these tests
// because assertionPassed() does not interact with the reporter.
class RunContextTest_513 : public ::testing::Test {
protected:
    std::string run_name_ = "rc-assertionPassed-tests";
    NiceMock<MockConfig> config_;
    Catch::IEventListenerPtr reporter_;
    std::unique_ptr<Catch::RunContext> ctx_;

    void SetUp() override {
        ON_CALL(config_, name()).WillByDefault(ReturnRef(run_name_));
        reporter_ = Catch::IEventListenerPtr{}; // nullptr is fine here
        ctx_ = std::make_unique<Catch::RunContext>(&config_, std::move(reporter_));
    }
};

// Verifies initial observable state via the public API.
TEST_F(RunContextTest_513, LastAssertionPassedInitiallyFalse_513) {
    // Expect initial state to report "not passed"
    EXPECT_FALSE(ctx_->lastAssertionPassed());
}

// Normal operation: calling assertionPassed flips the public flag to true.
TEST_F(RunContextTest_513, AssertionPassed_SetsFlagTrue_513) {
    ctx_->assertionPassed();
    EXPECT_TRUE(ctx_->lastAssertionPassed());
}

// Boundary/idempotence: multiple calls keep the observable flag true.
// (We do not inspect internal counters; we only assert interface-visible state.)
TEST_F(RunContextTest_513, AssertionPassed_MultipleCallsKeepTrue_513) {
    ctx_->assertionPassed();
    ctx_->assertionPassed();
    ctx_->assertionPassed();
    EXPECT_TRUE(ctx_->lastAssertionPassed());
}
