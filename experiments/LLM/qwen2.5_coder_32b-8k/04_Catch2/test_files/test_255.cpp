#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_context.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using namespace testing;



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



class ContextTest_255 : public ::testing::Test {

protected:

    Context context;

    NiceMock<MockIConfig> mockConfig;



    void SetUp() override {

        context.setConfig(&mockConfig);

    }

};



TEST_F(ContextTest_255, SetAndGetConfig_255) {

    EXPECT_EQ(context.getConfig(), &mockConfig);

}



TEST_F(ContextTest_255, GetResultCaptureInitiallyNull_255) {

    EXPECT_EQ(context.getResultCapture(), nullptr);

}



TEST_F(ContextTest_255, SetAndGetResultCapture_255) {

    IResultCapture* mockResultCapture = reinterpret_cast<IResultCapture*>(0x1234);

    context.setResultCapture(mockResultCapture);

    EXPECT_EQ(context.getResultCapture(), mockResultCapture);

}
