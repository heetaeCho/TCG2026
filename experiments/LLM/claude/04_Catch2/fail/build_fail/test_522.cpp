#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

// Include necessary headers
#include "catch2/internal/catch_run_context.cpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_random_number_generator.hpp"

// We need access to sharedRng() - it's declared in Catch namespace
namespace Catch {
    SimplePcg32& sharedRng();
}

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
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
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

class SeedRngTest_522 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that seedRng calls rngSeed() on the config and seeds the shared RNG
TEST_F(SeedRngTest_522, SeedRngCallsRngSeedOnConfig_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .Times(1)
        .WillOnce(::testing::Return(42u));

    Catch::seedRng(config);

    // Verify that the shared RNG was seeded with 42 by comparing output
    // with a freshly seeded SimplePcg32
    Catch::SimplePcg32 expected(42u);
    Catch::SimplePcg32& rng = Catch::sharedRng();
    EXPECT_EQ(rng(), expected());
}

// Test seeding with zero
TEST_F(SeedRngTest_522, SeedRngWithZero_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(0u));

    Catch::seedRng(config);

    Catch::SimplePcg32 expected(0u);
    Catch::SimplePcg32& rng = Catch::sharedRng();
    EXPECT_EQ(rng(), expected());
}

// Test seeding with max uint32_t value
TEST_F(SeedRngTest_522, SeedRngWithMaxValue_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(UINT32_MAX));

    Catch::seedRng(config);

    Catch::SimplePcg32 expected(UINT32_MAX);
    Catch::SimplePcg32& rng = Catch::sharedRng();
    EXPECT_EQ(rng(), expected());
}

// Test seeding with value 1
TEST_F(SeedRngTest_522, SeedRngWithOne_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(1u));

    Catch::seedRng(config);

    Catch::SimplePcg32 expected(1u);
    Catch::SimplePcg32& rng = Catch::sharedRng();
    EXPECT_EQ(rng(), expected());
}

// Test that calling seedRng twice resets the RNG state
TEST_F(SeedRngTest_522, SeedRngCalledTwiceResetsState_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(100u))
        .WillOnce(::testing::Return(100u));

    Catch::seedRng(config);
    // Consume some values from the RNG
    Catch::sharedRng()();
    Catch::sharedRng()();

    // Seed again with the same seed
    Catch::seedRng(config);

    Catch::SimplePcg32 expected(100u);
    EXPECT_EQ(Catch::sharedRng()(), expected());
}

// Test that different seeds produce different sequences
TEST_F(SeedRngTest_522, DifferentSeedsProduceDifferentSequences_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(42u))
        .WillOnce(::testing::Return(43u));

    Catch::seedRng(config);
    auto val1 = Catch::sharedRng()();

    Catch::seedRng(config);
    auto val2 = Catch::sharedRng()();

    EXPECT_NE(val1, val2);
}

// Test that the same seed produces the same first output
TEST_F(SeedRngTest_522, SameSeedProducesSameOutput_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(12345u))
        .WillOnce(::testing::Return(12345u));

    Catch::seedRng(config);
    auto val1 = Catch::sharedRng()();

    Catch::seedRng(config);
    auto val2 = Catch::sharedRng()();

    EXPECT_EQ(val1, val2);
}

// Test with a specific known seed value (boundary: default PCG seed)
TEST_F(SeedRngTest_522, SeedRngWithDefaultPcgSeed_522) {
    MockConfig config;
    EXPECT_CALL(config, rngSeed())
        .WillOnce(::testing::Return(0xed743cc4U));

    Catch::seedRng(config);

    Catch::SimplePcg32 expected(0xed743cc4U);
    EXPECT_EQ(Catch::sharedRng()(), expected());
}
