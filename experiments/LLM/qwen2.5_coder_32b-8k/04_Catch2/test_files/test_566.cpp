#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_registrars.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(allowThrows, bool());

    MOCK_CONST_METHOD0(name, StringRef());

    MOCK_CONST_METHOD0(includeSuccessfulResults, bool());

    MOCK_CONST_METHOD0(shouldDebugBreak, bool());

    MOCK_CONST_METHOD0(warnAboutMissingAssertions, bool());

    MOCK_CONST_METHOD0(warnAboutUnmatchedTestSpecs, bool());

    MOCK_CONST_METHOD0(zeroTestsCountAsSuccess, bool());

    MOCK_CONST_METHOD0(abortAfter, int());

    MOCK_CONST_METHOD0(showInvisibles, bool());

    MOCK_CONST_METHOD0(showDurations, ShowDurations());

    MOCK_CONST_METHOD0(minDuration, double());

    MOCK_CONST_METHOD0(testSpec, const TestSpec&());

    MOCK_CONST_METHOD0(hasTestFilters, bool());

    MOCK_CONST_METHOD0(getTestsOrTags, const std::vector<std::string>&());

    MOCK_CONST_METHOD0(runOrder, TestRunOrder());

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

    MOCK_CONST_METHOD0(shardCount, unsigned int());

    MOCK_CONST_METHOD0(shardIndex, unsigned int());

    MOCK_CONST_METHOD0(defaultColourMode, ColourMode());

    MOCK_CONST_METHOD0(getSectionsToRun, const std::vector<std::string>&());

    MOCK_CONST_METHOD0(verbosity, Verbosity());

    MOCK_CONST_METHOD0(skipBenchmarks, bool());

    MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());

    MOCK_CONST_METHOD0(benchmarkSamples, unsigned int());

    MOCK_CONST_METHOD0(benchmarkConfidenceInterval, double());

    MOCK_CONST_METHOD0(benchmarkResamples, unsigned int());

    MOCK_CONST_METHOD0(benchmarkWarmupTime, std::chrono::milliseconds());

};



class ListenerRegistrarTest : public ::testing::Test {

protected:

    ListenerRegistrar::TypedListenerFactory factory{"MockListener"};

    NiceMock<MockConfig> mockConfig;

};



TEST_F(ListenerRegistrarTest_Create_ReturnsNonNullPointer_566) {

    IEventListenerPtr listener = factory.create(&mockConfig);

    EXPECT_NE(listener, nullptr);

}



TEST_F(ListenerRegistrarTest_GetName_ReturnsCorrectName_566) {

    EXPECT_EQ(factory.getName(), "MockListener");

}
