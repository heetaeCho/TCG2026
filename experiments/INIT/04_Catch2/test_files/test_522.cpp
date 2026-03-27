// File: tests/seed_rng_tests_522.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <vector>
#include <string>

// Use the provided interface header (treated as authoritative API surface)
#include "Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

// Forward-declare the function under test (definition is in the .cpp)
namespace Catch {
    void seedRng(IConfig const& config);
}

using ::testing::Return;
using ::testing::Exactly;

namespace {

// A strict mock for Catch::IConfig.
// We only care about rngSeed(), but we mock all virtuals to avoid abstract type issues.
// Methods we do not care about will never be called; if they are, the test will fail
// (thanks to Strict behavior).
class MockIConfig : public Catch::IConfig {
public:
    // Google Mock requires a virtual destructor in base; the interface already has one.
    // We do not need to mock the destructor explicitly.

    // The interface in the prompt shows many virtuals. We mock them all.
    // Return types drop top-level const (C++ ignores const on return-by-value).
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

    // The method under direct observation:
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

// A lightweight test fixture (kept for naming consistency/extension).
class SeedRngTest_522 : public ::testing::Test {
protected:
    MockIConfig config_;
};

} // namespace

// ---------- Test cases ----------

// Normal operation: seedRng should query rngSeed() exactly once.
TEST_F(SeedRngTest_522, CallsRngSeedOnce_522) {
    EXPECT_CALL(config_, rngSeed())
        .Times(Exactly(1))
        .WillOnce(Return(123u));

    // Call function under test; we only verify observable interaction with IConfig.
    // We *do not* inspect internal RNG state.
    EXPECT_NO_THROW(Catch::seedRng(config_));
}

// Boundary condition: rngSeed() returns 0 (often a special seed value).
// We verify that seedRng still queries rngSeed() and does not throw.
TEST_F(SeedRngTest_522, AcceptsZeroSeed_522) {
    EXPECT_CALL(config_, rngSeed())
        .Times(Exactly(1))
        .WillOnce(Return(0u));

    EXPECT_NO_THROW(Catch::seedRng(config_));
}

// Boundary condition: rngSeed() returns the maximum 32-bit value.
// Again, we only assert that rngSeed() is consulted and the call succeeds.
TEST_F(SeedRngTest_522, AcceptsMaxUint32Seed_522) {
    EXPECT_CALL(config_, rngSeed())
        .Times(Exactly(1))
        .WillOnce(Return(std::numeric_limits<uint32_t>::max()));

    EXPECT_NO_THROW(Catch::seedRng(config_));
}
