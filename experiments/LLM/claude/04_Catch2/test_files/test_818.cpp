#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"

namespace Catch {

class MockIConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class ShouldShowDurationTest_818 : public ::testing::Test {
protected:
    MockIConfig config;
};

// When showDurations is Always, should always return true regardless of duration
TEST_F(ShouldShowDurationTest_818, AlwaysReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::Always));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.0));

    EXPECT_TRUE(shouldShowDuration(config, 0.0));
    EXPECT_TRUE(shouldShowDuration(config, 1.0));
    EXPECT_TRUE(shouldShowDuration(config, -1.0));
    EXPECT_TRUE(shouldShowDuration(config, 100.0));
}

// When showDurations is Never, should always return false regardless of duration
TEST_F(ShouldShowDurationTest_818, NeverReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::Never));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.0));

    EXPECT_FALSE(shouldShowDuration(config, 0.0));
    EXPECT_FALSE(shouldShowDuration(config, 1.0));
    EXPECT_FALSE(shouldShowDuration(config, -1.0));
    EXPECT_FALSE(shouldShowDuration(config, 100.0));
}

// When showDurations is DefaultForReporter and duration >= minDuration (non-negative), return true
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_DurationAboveMin_ReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.5));

    EXPECT_TRUE(shouldShowDuration(config, 1.0));
    EXPECT_TRUE(shouldShowDuration(config, 0.5));  // exactly at min
    EXPECT_TRUE(shouldShowDuration(config, 100.0));
}

// When showDurations is DefaultForReporter and duration < minDuration, return false
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_DurationBelowMin_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.5));

    EXPECT_FALSE(shouldShowDuration(config, 0.0));
    EXPECT_FALSE(shouldShowDuration(config, 0.4));
    EXPECT_FALSE(shouldShowDuration(config, 0.499));
}

// When showDurations is DefaultForReporter and minDuration is negative, return false
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_NegativeMinDuration_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(-1.0));

    EXPECT_FALSE(shouldShowDuration(config, 0.0));
    EXPECT_FALSE(shouldShowDuration(config, 1.0));
    EXPECT_FALSE(shouldShowDuration(config, 100.0));
}

// When showDurations is DefaultForReporter and minDuration is 0, duration >= 0 returns true
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_ZeroMinDuration_ZeroDuration_ReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.0));

    EXPECT_TRUE(shouldShowDuration(config, 0.0));
    EXPECT_TRUE(shouldShowDuration(config, 0.001));
    EXPECT_TRUE(shouldShowDuration(config, 5.0));
}

// When showDurations is DefaultForReporter, minDuration is 0, and duration is negative
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_ZeroMinDuration_NegativeDuration_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.0));

    EXPECT_FALSE(shouldShowDuration(config, -0.001));
    EXPECT_FALSE(shouldShowDuration(config, -1.0));
}

// Boundary: duration exactly equals minDuration
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_DurationExactlyEqualsMin_ReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(1.5));

    EXPECT_TRUE(shouldShowDuration(config, 1.5));
}

// Boundary: duration just below minDuration
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_DurationJustBelowMin_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(1.5));

    EXPECT_FALSE(shouldShowDuration(config, 1.4999999));
}

// Always mode with zero duration
TEST_F(ShouldShowDurationTest_818, Always_ZeroDuration_ReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::Always));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(10.0));

    EXPECT_TRUE(shouldShowDuration(config, 0.0));
}

// Never mode with large duration
TEST_F(ShouldShowDurationTest_818, Never_LargeDuration_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::Never));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(0.0));

    EXPECT_FALSE(shouldShowDuration(config, 999999.0));
}

// DefaultForReporter with very large minDuration and moderate duration
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_LargeMinDuration_SmallDuration_ReturnsFalse_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(1000000.0));

    EXPECT_FALSE(shouldShowDuration(config, 999999.9));
}

// DefaultForReporter with very large minDuration and large enough duration
TEST_F(ShouldShowDurationTest_818, DefaultForReporter_LargeMinDuration_LargeDuration_ReturnsTrue_818) {
    ON_CALL(config, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
    ON_CALL(config, minDuration()).WillByDefault(::testing::Return(1000000.0));

    EXPECT_TRUE(shouldShowDuration(config, 1000000.0));
    EXPECT_TRUE(shouldShowDuration(config, 1000001.0));
}

}  // namespace Catch
