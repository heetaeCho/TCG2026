#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>

// Include necessary headers
#include "catch2/catch_get_random_seed.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_context.hpp"

// Mock class for IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;

    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(std::uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class GetRandomSeedTest_710 : public ::testing::Test {
protected:
    MockConfig mockConfig;

    void SetUp() override {
        // Set up the mock config in the Catch2 context
        Catch::getCurrentMutableContext().setConfig(&mockConfig);
    }

    void TearDown() override {
        // Clean up the config to avoid dangling pointers
        Catch::getCurrentMutableContext().setConfig(nullptr);
    }
};

// Test that getSeed returns the value from the config's rngSeed
TEST_F(GetRandomSeedTest_710, ReturnsConfigRngSeed_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(42u));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, 42u);
}

// Test with seed value of zero
TEST_F(GetRandomSeedTest_710, ReturnsZeroSeed_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(0u));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, 0u);
}

// Test with maximum uint32 seed value
TEST_F(GetRandomSeedTest_710, ReturnsMaxUint32Seed_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(std::numeric_limits<std::uint32_t>::max()));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, std::numeric_limits<std::uint32_t>::max());
}

// Test with a typical seed value
TEST_F(GetRandomSeedTest_710, ReturnsTypicalSeedValue_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(12345u));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, 12345u);
}

// Test that getSeed calls rngSeed exactly once per invocation
TEST_F(GetRandomSeedTest_710, CallsRngSeedOnce_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .Times(1)
        .WillOnce(::testing::Return(99u));

    Catch::getSeed();
}

// Test that multiple calls to getSeed each query the config
TEST_F(GetRandomSeedTest_710, MultipleCallsQueryConfigEachTime_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(100u))
        .WillOnce(::testing::Return(200u))
        .WillOnce(::testing::Return(300u));

    EXPECT_EQ(Catch::getSeed(), 100u);
    EXPECT_EQ(Catch::getSeed(), 200u);
    EXPECT_EQ(Catch::getSeed(), 300u);
}

// Test with value 1 (boundary near zero)
TEST_F(GetRandomSeedTest_710, ReturnsSeedValueOne_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(1u));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, 1u);
}

// Test with a large but not max seed value
TEST_F(GetRandomSeedTest_710, ReturnsLargeSeedValue_710) {
    EXPECT_CALL(mockConfig, rngSeed())
        .WillOnce(::testing::Return(0xDEADBEEFu));

    std::uint32_t seed = Catch::getSeed();
    EXPECT_EQ(seed, 0xDEADBEEFu);
}
