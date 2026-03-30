// File: run_context_notifyAssertionStarted_tests_495.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_stringref.hpp>

using ::testing::_;
using ::testing::Invoke;

namespace Catch {

// Minimal concrete config to satisfy RunContext construction.
class DummyConfig_495 final : public IConfig {
public:
    DummyConfig_495() = default;
    StringRef name() const override { return StringRef("DummyConfig_495"); }
    // If IConfig has more pure-virtuals in your build, add trivial overrides here.
};

// Mock reporter that observes calls from RunContext.
class MockEventListener_495 : public IEventListener {
public:
    explicit MockEventListener_495(IConfig const* cfg) : IEventListener(cfg) {}
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
};

} // namespace Catch

// Helper to build an AssertionInfo with customizable fields.
static Catch::AssertionInfo MakeInfo_495(
    Catch::StringRef macro = Catch::StringRef("REQUIRE"),
    Catch::StringRef expr  = Catch::StringRef("1==1")) {
    Catch::AssertionInfo info;
    info.macroName = macro;
    info.capturedExpression = expr;
    // Use a default-initialized flag; exact value is immaterial for this test.
    info.resultDisposition = static_cast<Catch::ResultDisposition::Flags>(0);
    return info;
}

// Verifies that notifyAssertionStarted forwards the provided AssertionInfo
// to reporter->assertionStarting exactly once.
TEST(RunContext_NotifyAssertionStarted_495, ForwardsInfoToReporter_495) {
    Catch::DummyConfig_495 cfg;

    auto reporterPtr = Catch::IEventListenerPtr(new Catch::MockEventListener_495(&cfg));
    auto* reporterRaw = static_cast<Catch::MockEventListener_495*>(reporterPtr.get());

    Catch::RunContext ctx(&cfg, std::move(reporterPtr));

    const auto info = MakeInfo_495(Catch::StringRef("REQUIRE"), Catch::StringRef("x == y"));

    EXPECT_CALL(*repor terRaw, assertionStarting(_))
        .Times(1)
        .WillOnce(Invoke([&](const Catch::AssertionInfo& got){
            EXPECT_EQ(got.macroName, info.macroName);
            EXPECT_EQ(got.capturedExpression, info.capturedExpression);
        }));

    ctx.notifyAssertionStarted(info);
}

// Boundary: empty macro/expression strings still must be forwarded to reporter.
TEST(RunContext_NotifyAssertionStarted_495, HandlesEmptyAssertionInfo_495) {
    Catch::DummyConfig_495 cfg;

    auto reporterPtr = Catch::IEventListenerPtr(new Catch::MockEventListener_495(&cfg));
    auto* reporterRaw = static_cast<Catch::MockEventListener_495*>(reporterPtr.get());

    Catch::RunContext ctx(&cfg, std::move(reporterPtr));

    const auto info = MakeInfo_495(Catch::StringRef(), Catch::StringRef());

    EXPECT_CALL(*reporterRaw, assertionStarting(_))
        .Times(1)
        .WillOnce(Invoke([&](const Catch::AssertionInfo& got){
            EXPECT_TRUE(got.macroName.empty());
            EXPECT_TRUE(got.capturedExpression.empty());
        }));

    ctx.notifyAssertionStarted(info);
}

// Regression-style: multiple invocations should notify reporter each time.
TEST(RunContext_NotifyAssertionStarted_495, MultipleCallsNotifyEachTime_495) {
    Catch::DummyConfig_495 cfg;

    auto reporterPtr = Catch::IEventListenerPtr(new Catch::MockEventListener_495(&cfg));
    auto* reporterRaw = static_cast<Catch::MockEventListener_495*>(reporterPtr.get());

    Catch::RunContext ctx(&cfg, std::move(reporterPtr));

    const auto info1 = MakeInfo_495(Catch::StringRef("CHECK"), Catch::StringRef("a < b"));
    const auto info2 = MakeInfo_495(Catch::StringRef("REQUIRE"), Catch::StringRef("c == d"));

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*reporterRaw, assertionStarting(_)).Times(1);
        EXPECT_CALL(*reporterRaw, assertionStarting(_)).Times(1);
    }

    ctx.notifyAssertionStarted(info1);
    ctx.notifyAssertionStarted(info2);
}
