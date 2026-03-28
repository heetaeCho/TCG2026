// File: run_context_handle_incomplete_tests_519.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 types under test
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_result_type.hpp"

// Minimal helpers to create a usable RunContext without relying on internal state.
// We only depend on IConfig::name() being callable (constructor uses it), and we
// do not assume anything else about configuration.

namespace Catch {

// A very small stub for IConfig that provides a name; other members (if any)
// are satisfied by defaulted implementations in the real headers.
class StubConfig : public IConfig {
public:
    StringRef name() const override { return StringRef("handleIncomplete-tests"); }

    // ---- The following virtuals are provided as conservative no-ops/defaults.
    // We do not rely on them in the tests, but some Catch2 builds require them.
    // If your local IConfig interface differs, keep these as simple pass-throughs.
    bool allowThrows() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    int abortAfter() const override { return 0; }
    bool includeSuccessfulResults() const override { return false; }
    ShowDurations::OrNot showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    TestSpec const& testSpec() const override { static TestSpec ts; return ts; }
    bool hasTestFilters() const override { return false; }
    WarnAbout::What warnAbout() const override { return WarnAbout::Nothing; }
    enum RunTests::InWhatOrder runOrder() const override { return RunTests::InDeclarationOrder; }
    UseColour::YesOrNo useColour() const override { return UseColour::Auto; }
    bool shouldReportAllAssertions() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds::rep benchmarkWarmupTime() const override { return 0; }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
};

} // namespace Catch

// Test fixture that owns a RunContext instance
class RunContextHandleIncompleteTest_519 : public ::testing::Test {
protected:
    std::unique_ptr<Catch::RunContext> ctx;

    static Catch::AssertionInfo MakeInfo(const char* macro,
                                         const char* captured) {
        Catch::AssertionInfo info;
        info.macroName = Catch::StringRef(macro);
        info.capturedExpression = Catch::StringRef(captured);
        // ResultDisposition flags are not relevant for handleIncomplete path;
        // leave default-initialized (zero).
        return info;
    }

    void SetUp() override {
        auto cfg = std::make_unique<Catch::StubConfig>();
        // Reporter can be null; tests do not assert on reporting side-effects.
        Catch::IEventListenerPtr reporter;
        // RunContext expects a raw IConfig* & an rvalue reporter
        ctx = std::make_unique<Catch::RunContext>(cfg.release(), std::move(reporter));
    }
};

// --- Tests ---

// Normal behavior: handleIncomplete should produce a last result with
// type ResultWas::ThrewException and a fixed explanatory message.
TEST_F(RunContextHandleIncompleteTest_519, ProducesThrewExceptionWithFixedMessage_519) {
    const auto info = MakeInfo("REQUIRE", "foo == bar");

    ctx->handleIncomplete(info);

    auto* last = ctx->getLastResult();
    ASSERT_NE(last, nullptr) << "getLastResult() should return a result after handleIncomplete";

    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ThrewException);
    // The message is defined in the implementation and should be fixed text.
    EXPECT_THAT(std::string(last->getMessage()),
                ::testing::HasSubstr("Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE"));
    // Sanity: result should have a message.
    EXPECT_TRUE(last->hasMessage());
}

// Info propagation: the AssertionInfo passed in should be reflected in the
// resulting AssertionResult's metadata (macro name).
TEST_F(RunContextHandleIncompleteTest_519, PropagatesAssertionInfoMacroName_519) {
    const auto info = MakeInfo("CHECK_THROWS", "danger()");

    ctx->handleIncomplete(info);

    auto* last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(std::string(last->getTestMacroName()), "CHECK_THROWS");
}

// Multiple invocations: the latest call should overwrite the last result,
// keeping the same failure type & message while reflecting the latest info.
TEST_F(RunContextHandleIncompleteTest_519, SubsequentCallsUpdateLastResult_519) {
    const auto first  = MakeInfo("REQUIRE", "a == b");
    const auto second = MakeInfo("CHECK_THROWS", "g()");

    ctx->handleIncomplete(first);
    auto const* firstRes = ctx->getLastResult();
    ASSERT_NE(firstRes, nullptr);
    EXPECT_EQ(firstRes->getResultType(), Catch::ResultWas::ThrewException);

    ctx->handleIncomplete(second);
    auto const* secondRes = ctx->getLastResult();
    ASSERT_NE(secondRes, nullptr);

    // It should now mirror the second call
    EXPECT_EQ(secondRes->getResultType(), Catch::ResultWas::ThrewException);
    EXPECT_EQ(std::string(secondRes->getTestMacroName()), "CHECK_THROWS");
    EXPECT_THAT(std::string(secondRes->getMessage()),
                ::testing::HasSubstr("Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE"));
}

// Boundary-ish input: empty/unknown macro & expression are accepted;
// observable output remains the same fixed failure classification & message.
TEST_F(RunContextHandleIncompleteTest_519, AcceptsEmptyAssertionInfo_519) {
    const auto info = MakeInfo("", "");

    ctx->handleIncomplete(info);

    auto* last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ThrewException);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_THAT(std::string(last->getMessage()),
                ::testing::HasSubstr("CATCH_CONFIG_FAST_COMPILE"));
}
