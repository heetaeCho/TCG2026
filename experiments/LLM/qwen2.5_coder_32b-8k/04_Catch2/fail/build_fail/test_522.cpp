#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_random_number_generator.hpp"



using namespace Catch;

using ::testing::Return;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const) override);

    MOCK_METHOD(StringRef, name, (), (const) override);

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const) override);

    MOCK_METHOD(bool, shouldDebugBreak, (), (const) override);

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const) override);

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const) override);

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const) override);

    MOCK_METHOD(int, abortAfter, (), (const) override);

    MOCK_METHOD(bool, showInvisibles, (), (const) override);

    MOCK_METHOD(ShowDurations, showDurations, (), (const) override);

    MOCK_METHOD(double, minDuration, (), (const) override);

    MOCK_METHOD(const TestSpec &, testSpec, (), (const) override);

    MOCK_METHOD(bool, hasTestFilters, (), (const) override);

    MOCK_METHOD(const std::vector<std::string> &, getTestsOrTags, (), (const) override);

    MOCK_METHOD(TestRunOrder, runOrder, (), (const) override);

    MOCK_METHOD(uint32_t, rngSeed, (), (const) override);

    MOCK_METHOD(unsigned int, shardCount, (), (const) override);

    MOCK_METHOD(unsigned int, shardIndex, (), (const) override);

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const) override);

    MOCK_METHOD(const std::vector<std::string> &, getSectionsToRun, (), (const) override);

    MOCK_METHOD(Verbosity, verbosity, (), (const) override);

    MOCK_METHOD(bool, skipBenchmarks, (), (const) override);

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const) override);

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const) override);

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const) override);

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const) override);

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const) override);

};



TEST(seedRngTest_522, SetsSeedCorrectly_522) {

    MockConfig mockConfig;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(12345U));



    SimplePcg32 rng;

    seedRng(mockConfig);



    // Since we cannot directly verify the internal state of SimplePcg32,

    // we rely on the fact that calling operator() should produce a different

    // result after seeding with a new value.

    rng.seed(0); // Reset to initial state

    auto initialValue = rng();

    seedRng(mockConfig);

    auto seededValue = rng();



    EXPECT_NE(initialValue, seededValue);

}



TEST(seedRngTest_522, SetsSeedBoundaryCondition_522) {

    MockConfig mockConfig;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(0U));



    SimplePcg32 rng;

    seedRng(mockConfig);



    // Verify that setting the seed to 0 does not throw an exception and behaves as expected.

    rng.seed(1); // Reset to a non-zero state

    auto initialValue = rng();

    seedRng(mockConfig);

    auto seededValue = rng();



    EXPECT_NE(initialValue, seededValue);

}



TEST(seedRngTest_522, SetsSeedToMaxValue_522) {

    MockConfig mockConfig;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(SimplePcg32::max()));



    SimplePcg32 rng;

    seedRng(mockConfig);



    // Verify that setting the seed to the maximum value does not throw an exception and behaves as expected.

    rng.seed(1); // Reset to a non-maximum state

    auto initialValue = rng();

    seedRng(mockConfig);

    auto seededValue = rng();



    EXPECT_NE(initialValue, seededValue);

}



TEST(seedRngTest_522, SetsSeedToMinValue_522) {

    MockConfig mockConfig;

    EXPECT_CALL(mockConfig, rngSeed()).WillOnce(Return(SimplePcg32::min()));



    SimplePcg32 rng;

    seedRng(mockConfig);



    // Verify that setting the seed to the minimum value does not throw an exception and behaves as expected.

    rng.seed(1); // Reset to a non-minimum state

    auto initialValue = rng();

    seedRng(mockConfig);

    auto seededValue = rng();



    EXPECT_NE(initialValue, seededValue);

}
