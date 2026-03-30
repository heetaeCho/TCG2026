// File: tests/get_seed_710_tests.cpp

#include <gtest/gtest.h>
#include <cstdint>

// Include the real Catch2 interfaces used by getSeed()
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_get_random_seed.cpp"   // or the header that declares getSeed()
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

class StubConfigForSeed final : public Catch::IConfig {
public:
    explicit StubConfigForSeed(uint32_t seed) : seed_(seed) {}

    // --- Only rngSeed() is relevant to these tests, the rest are minimal stubs ---
    // Return simple defaults; no internal behavior is inferred.
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { static Catch::StringRef n; return n; }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    const Catch::TestSpec& testSpec() const override { static Catch::TestSpec ts; return ts; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }

    uint32_t rngSeed() const override { return seed_; }

    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.0; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    ~StubConfigForSeed() override = default;

private:
    uint32_t seed_;
};

class GetSeedTest_710 : public ::testing::Test {
protected:
    void SetUp() override {
        // Save the original config to restore later
        originalConfig_ = Catch::getCurrentContext().getConfig();
    }

    void TearDown() override {
        // Restore the original config to avoid cross-test side effects
        Catch::getCurrentMutableContext().setConfig(originalConfig_);
    }

    const Catch::IConfig* originalConfig_{nullptr};
};

} // namespace

// --- Tests ---

TEST_F(GetSeedTest_710, ReturnsValueProvidedByConfig_710) {
    StubConfigForSeed cfg{123456u};
    Catch::getCurrentMutableContext().setConfig(&cfg);

    const std::uint32_t seed = Catch::getSeed();

    EXPECT_EQ(seed, 123456u);
}

TEST_F(GetSeedTest_710, ReturnsZeroWhenConfigSeedIsZero_Boundary_710) {
    StubConfigForSeed cfg{0u};
    Catch::getCurrentMutableContext().setConfig(&cfg);

    const std::uint32_t seed = Catch::getSeed();

    EXPECT_EQ(seed, 0u);
}

TEST_F(GetSeedTest_710, ReturnsMaxUint32Seed_Boundary_710) {
    StubConfigForSeed cfg{0xFFFFFFFFu};
    Catch::getCurrentMutableContext().setConfig(&cfg);

    const std::uint32_t seed = Catch::getSeed();

    EXPECT_EQ(seed, 0xFFFFFFFFu);
}

TEST_F(GetSeedTest_710, ReflectsChangeWhenConfigIsReplaced_710) {
    StubConfigForSeed cfg1{111u};
    StubConfigForSeed cfg2{222u};

    // First config
    Catch::getCurrentMutableContext().setConfig(&cfg1);
    EXPECT_EQ(Catch::getSeed(), 111u);

    // Replace with a different config
    Catch::getCurrentMutableContext().setConfig(&cfg2);
    EXPECT_EQ(Catch::getSeed(), 222u);
}
