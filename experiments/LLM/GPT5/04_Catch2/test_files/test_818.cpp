// TEST_ID: 818

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// From the provided dependencies
// (If you already include the real header in your build, prefer that include instead)
#include "Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

// Forward declaration of the function under test from the given partial code.
// (We are NOT re-implementing anything; just declaring so we can call it.)
namespace Catch {
    bool shouldShowDuration( IConfig const& config, double duration );
}

// Minimal mock of IConfig that exposes only what the SUT observes.
class MockConfig_818 : public Catch::IConfig {
public:
    ~MockConfig_818() override = default;

    // Only the methods that are used by shouldShowDuration are mocked.
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double,                  minDuration,  (), (const, override));

    // Stub out other virtuals so we don't rely on internal behavior.
    // We provide default dummy implementations to satisfy the vtable.
    // These are not used by the SUT and thus are not part of any assertions.
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return Catch::StringRef(); }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    const Catch::TestSpec& testSpec() const override { static Catch::TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { static std::vector<std::string> s; return s; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() const override { static std::vector<std::string> s; return s; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
};

// ---------- Tests ----------

using ::testing::Return;
using ::testing::Exactly;

// Always -> true; minDuration must not be queried.
TEST(ShouldShowDurationTest_818, ReturnsTrueWhenShowDurationsAlways_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::Always));
    EXPECT_CALL(cfg, minDuration()).Times(0);

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 0.0);
    EXPECT_TRUE(shown);
}

// Never -> false; minDuration must not be queried.
TEST(ShouldShowDurationTest_818, ReturnsFalseWhenShowDurationsNever_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::Never));
    EXPECT_CALL(cfg, minDuration()).Times(0);

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 123.456);
    EXPECT_FALSE(shown);
}

// DefaultForReporter with negative minDuration -> false regardless of duration.
TEST(ShouldShowDurationTest_818, DefaultModeNegativeMinDurationYieldsFalse_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(-1.0));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 10.0);
    EXPECT_FALSE(shown);
}

// DefaultForReporter: duration == minDuration -> true (boundary).
TEST(ShouldShowDurationTest_818, DefaultModeDurationEqualsMinIsShown_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(1.234));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 1.234);
    EXPECT_TRUE(shown);
}

// DefaultForReporter: duration < minDuration -> false.
TEST(ShouldShowDurationTest_818, DefaultModeDurationBelowMinIsNotShown_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(0.5));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 0.4999999);
    EXPECT_FALSE(shown);
}

// DefaultForReporter: duration > minDuration -> true.
TEST(ShouldShowDurationTest_818, DefaultModeDurationAboveMinIsShown_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(2.0));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 10.0);
    EXPECT_TRUE(shown);
}

// DefaultForReporter: minDuration == 0 -> show for duration >= 0; check duration == 0.
TEST(ShouldShowDurationTest_818, DefaultModeZeroMinShowsAtZeroDuration_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(0.0));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ 0.0);
    EXPECT_TRUE(shown);
}

// DefaultForReporter: negative duration with non-negative min -> not shown.
TEST(ShouldShowDurationTest_818, DefaultModeNegativeDurationWithNonNegativeMinIsNotShown_818) {
    MockConfig_818 cfg;
    EXPECT_CALL(cfg, showDurations()).Times(Exactly(1))
        .WillOnce(Return(Catch::ShowDurations::DefaultForReporter));
    EXPECT_CALL(cfg, minDuration()).Times(Exactly(1))
        .WillOnce(Return(0.0));

    const bool shown = Catch::shouldShowDuration(cfg, /*duration*/ -0.001);
    EXPECT_FALSE(shown);
}
