// File: tests/run_context_handle_unexpected_inflight_exception_518.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_result_type.hpp>

// These two headers provide a concrete IConfig implementation (Config) and a
// convenient no-op base listener (EventListenerBase) we can derive from to
// observe assertion events without touching RunContext internals.
#include <catch2/catch_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>

using ::testing::_;
using ::testing::Eq;

namespace {

class CapturingListener final : public Catch::EventListenerBase {
public:
    using Catch::EventListenerBase::EventListenerBase;

    // Store AssertionResults that RunContext reports via assertionEnded.
    std::vector<Catch::AssertionResult> seen;

    void assertionEnded(Catch::AssertionStats const& stats) override {
        seen.push_back(stats.assertionResult);
    }
};

struct RunContextFixture_518 : ::testing::Test {
    std::unique_ptr<Catch::Config>            config_;
    std::unique_ptr<Catch::RunContext>        ctx_;
    CapturingListener*                         listenerRaw_ = nullptr; // Owned by ctx_

    static Catch::AssertionInfo makeInfo(Catch::StringRef macro = "REQUIRE",
                                         Catch::StringRef expr  = "x == y",
                                         Catch::ResultDisposition::Flags disp = Catch::ResultDisposition::Normal) {
        Catch::AssertionInfo info;
        info.macroName = macro;
        info.capturedExpression = expr;
        info.resultDisposition = disp;
        return info;
    }

    void SetUp() override {
        // Minimal config with a recognizable run name
        Catch::ConfigData data;
        data.name = "run-518";
        config_ = std::make_unique<Catch::Config>(data);

        // Create our capturing listener and hand ownership to RunContext
        listenerRaw_ = new CapturingListener(*config_);
        Catch::IEventListenerPtr reporter(listenerRaw_);

        ctx_ = std::make_unique<Catch::RunContext>(config_.get(), std::move(reporter));
    }
};

} // namespace

// Verifies that an unexpected in-flight exception is surfaced as the latest
// assertion result with the correct result type and message.
TEST_F(RunContextFixture_518, RecordsThrewExceptionAndMessage_518) {
    Catch::AssertionReaction reaction; // starts with all-false flags
    auto info = makeInfo("REQUIRE", "doRisky()", Catch::ResultDisposition::Normal);

    ctx_->handleUnexpectedInflightException(info, std::string("boom!"), reaction);

    auto last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ThrewException);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_EQ(std::string(last->getMessage()), "boom!");
    // Sanity: macro name is propagated through the public result interface
    EXPECT_EQ(std::string(last->getTestMacroName()), "REQUIRE");
}

// Ensures that the reporter is notified (external interaction) and receives an
// AssertionResult of type ThrewException with the expected message.
TEST_F(RunContextFixture_518, NotifiesReporterWithAssertionResult_518) {
    Catch::AssertionReaction reaction;
    auto info = makeInfo("CHECK", "mightThrow()", Catch::ResultDisposition::Normal);

    ctx_->handleUnexpectedInflightException(info, std::string("unexpected throw"), reaction);

    ASSERT_FALSE(listenerRaw_->seen.empty());
    const auto& reported = listenerRaw_->seen.back();
    EXPECT_EQ(reported.getResultType(), Catch::ResultWas::ThrewException);
    EXPECT_TRUE(reported.hasMessage());
    EXPECT_EQ(std::string(reported.getMessage()), "unexpected throw");
    EXPECT_EQ(std::string(reported.getTestMacroName()), "CHECK");
}

// Empty message is preserved (boundary), result type remains ThrewException,
// and the last assertion did not pass.
TEST_F(RunContextFixture_518, HandlesEmptyMessageAndFlagsLastAssertionFailed_518) {
    Catch::AssertionReaction reaction;
    auto info = makeInfo("REQUIRE", "danger()", Catch::ResultDisposition::Normal);

    ctx_->handleUnexpectedInflightException(info, std::string{}, reaction);

    auto last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ThrewException);
    // Empty message is allowed and observable via public API
    EXPECT_TRUE(std::string(last->getMessage()).empty());

    // Observable pass/fail surface: exception should mark last assertion as not passed
    EXPECT_FALSE(ctx_->lastAssertionPassed());
}

// Calling the handler multiple times should update the last result accordingly
// (no reliance on internal state beyond what the public accessors expose).
TEST_F(RunContextFixture_518, SubsequentCallsUpdateLastResult_518) {
    Catch::AssertionReaction reaction;
    auto info1 = makeInfo("REQUIRE", "first()", Catch::ResultDisposition::Normal);
    auto info2 = makeInfo("REQUIRE", "second()", Catch::ResultDisposition::Normal);

    ctx_->handleUnexpectedInflightException(info1, std::string("first boom"), reaction);
    ctx_->handleUnexpectedInflightException(info2, std::string("second boom"), reaction);

    auto last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ThrewException);
    EXPECT_EQ(std::string(last->getMessage()), "second boom");
    EXPECT_EQ(std::string(last->getTestMacroName()), "REQUIRE");

    ASSERT_GE(listenerRaw_->seen.size(), 2u);
    EXPECT_EQ(std::string(listenerRaw_->seen.back().getMessage()), "second boom");
}
