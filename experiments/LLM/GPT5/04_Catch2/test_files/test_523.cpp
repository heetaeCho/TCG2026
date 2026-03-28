// File: rng_seed_tests_523.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.cpp"      // for Catch::rngSeed()
#include "catch2/internal/catch_context.hpp"           // for Catch::Context APIs
#include "catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Minimal mock for IConfig focusing only on the observable call we care about.
// We do not mock or rely on any internal state/behavior beyond rngSeed().
class MockConfig : public Catch::IConfig {
public:
    // Provide a virtual destructor to match interface
    ~MockConfig() override = default;

    // Only rngSeed is needed/observed in these tests.
    MOCK_METHOD(uint32_t, rngSeed, (), (override));

    // Stub the rest with default bodies to avoid making assumptions or using them.
    // These stubs won't be called; they exist only to satisfy the interface.
    bool allowThrows() override { return true; }
    Catch::StringRef name() override { static Catch::StringRef n; return n; }
    bool includeSuccessfulResults() override { return false; }
    bool shouldDebugBreak() override { return false; }
    bool warnAboutMissingAssertions() override { return false; }
    bool warnAboutUnmatchedTestSpecs() override { return false; }
    bool zeroTestsCountAsSuccess() override { return false; }
    int abortAfter() override { return 0; }
    bool showInvisibles() override { return false; }
    Catch::ShowDurations showDurations() override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() override { return 0.0; }
    const Catch::TestSpec& testSpec() override { static Catch::TestSpec ts; return ts; }
    bool hasTestFilters() override { return false; }
    const std::vector<std::string>& getTestsOrTags() override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() override { return Catch::TestRunOrder::Declared; }
    unsigned int shardCount() override { return 1u; }
    unsigned int shardIndex() override { return 0u; }
    Catch::ColourMode defaultColourMode() override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() override { return false; }
    bool benchmarkNoAnalysis() override { return false; }
    unsigned int benchmarkSamples() override { return 0u; }
    double benchmarkConfidenceInterval() override { return 0.0; }
    unsigned int benchmarkResamples() override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() override { return std::chrono::milliseconds{0}; }
};

// Fixture to safely swap the config pointer in the global Catch context.
class RngSeedTest_523 : public ::testing::Test {
protected:
    const Catch::IConfig* originalConfig_ = nullptr;

    void SetUp() override {
        // Save the original config so we can restore it after each test.
        originalConfig_ = Catch::getCurrentContext().getConfig();
    }
    void TearDown() override {
        // Restore original config to avoid test cross-talk.
        Catch::getCurrentMutableContext().setConfig(originalConfig_);
    }
};

} // namespace

// Normal operation: rngSeed returns the value provided by the current config.
TEST_F(RngSeedTest_523, ReturnsSeedFromConfig_523) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, rngSeed()).Times(1).WillOnce(Return(123u));

    Catch::getCurrentMutableContext().setConfig(&cfg);
    const unsigned int seed = Catch::rngSeed();

    EXPECT_EQ(seed, 123u);
}

// Boundary condition: rngSeed propagates zero from config.
TEST_F(RngSeedTest_523, ReturnsZeroSeed_523) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, rngSeed()).Times(1).WillOnce(Return(0u));

    Catch::getCurrentMutableContext().setConfig(&cfg);
    const unsigned int seed = Catch::rngSeed();

    EXPECT_EQ(seed, 0u);
}

// Boundary condition: rngSeed propagates a large 32-bit value from config.
TEST_F(RngSeedTest_523, ReturnsLargeSeed_523) {
    StrictMock<MockConfig> cfg;
    // A large 32-bit value within uint32_t range; observable via returned unsigned int.
    constexpr uint32_t largeSeed = 3141592653u;
    EXPECT_CALL(cfg, rngSeed()).Times(1).WillOnce(Return(largeSeed));

    Catch::getCurrentMutableContext().setConfig(&cfg);
    const unsigned int seed = Catch::rngSeed();

    EXPECT_EQ(seed, static_cast<unsigned int>(largeSeed));
}
