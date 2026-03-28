#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

// Include necessary Catch2 headers
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// We need to declare rngSeed() since it's in catch_run_context.cpp
namespace Catch {
    unsigned int rngSeed();
}

// Mock IConfig to control what rngSeed() returns
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

class RngSeedTest_523 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
    }

    void TearDown() override {
        // Reset the config in the context
        Catch::getCurrentMutableContext().setConfig(nullptr);
        delete mockConfig_;
        mockConfig_ = nullptr;
    }

    MockConfig* mockConfig_ = nullptr;
};

// Test that rngSeed() returns the value from the config's rngSeed()
TEST_F(RngSeedTest_523, ReturnsConfigRngSeed_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(42u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    unsigned int result = Catch::rngSeed();
    EXPECT_EQ(result, 42u);
}

// Test with zero seed value
TEST_F(RngSeedTest_523, ReturnsZeroSeed_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(0u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    unsigned int result = Catch::rngSeed();
    EXPECT_EQ(result, 0u);
}

// Test with maximum uint32 seed value
TEST_F(RngSeedTest_523, ReturnsMaxSeed_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(UINT32_MAX));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    unsigned int result = Catch::rngSeed();
    EXPECT_EQ(result, static_cast<unsigned int>(UINT32_MAX));
}

// Test with a typical seed value
TEST_F(RngSeedTest_523, ReturnsTypicalSeed_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(12345u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    unsigned int result = Catch::rngSeed();
    EXPECT_EQ(result, 12345u);
}

// Test that rngSeed delegates to config each time (not cached)
TEST_F(RngSeedTest_523, DelegatesToConfigEachCall_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(100u))
        .WillOnce(::testing::Return(200u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    EXPECT_EQ(Catch::rngSeed(), 100u);
    EXPECT_EQ(Catch::rngSeed(), 200u);
}

// Test with value 1 (boundary: smallest non-zero)
TEST_F(RngSeedTest_523, ReturnsOneSeed_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .WillOnce(::testing::Return(1u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    unsigned int result = Catch::rngSeed();
    EXPECT_EQ(result, 1u);
}

// Test that config's rngSeed is called exactly once per rngSeed() call
TEST_F(RngSeedTest_523, CallsConfigRngSeedExactlyOnce_523) {
    EXPECT_CALL(*mockConfig_, rngSeed())
        .Times(1)
        .WillOnce(::testing::Return(999u));

    Catch::getCurrentMutableContext().setConfig(mockConfig_);

    Catch::rngSeed();
}
