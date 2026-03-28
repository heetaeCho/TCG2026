#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include "./TestProjects/Catch2/src/catch2/benchmark/detail/catch_benchmark_stats.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_context.hpp"



using namespace Catch;

using namespace Catch::Benchmark;

using ::testing::_;

using ::testing::MockFunction;



class MockIConfig : public IConfig {

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

    MOCK_CONST_METHOD0(testSpec, const TestSpec &());

    MOCK_CONST_METHOD0(hasTestFilters, bool());

    MOCK_CONST_METHOD0(getTestsOrTags, const std::vector<std::string> &());

    MOCK_CONST_METHOD0(runOrder, TestRunOrder());

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

    MOCK_CONST_METHOD0(shardCount, unsigned int());

    MOCK_CONST_METHOD0(shardIndex, unsigned int());

    MOCK_CONST_METHOD0(defaultColourMode, ColourMode());

    MOCK_CONST_METHOD0(getSectionsToRun, const std::vector<std::string> &());

    MOCK_CONST_METHOD0(verbosity, Verbosity());

    MOCK_CONST_METHOD0(skipBenchmarks, bool());

    MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());

    MOCK_CONST_METHOD0(benchmarkSamples, unsigned int());

    MOCK_CONST_METHOD0(benchmarkConfidenceInterval, double());

    MOCK_CONST_METHOD0(benchmarkResamples, unsigned int());

    MOCK_CONST_METHOD0(benchmarkWarmupTime, std::chrono::milliseconds());

};



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD1(notifyAssertionStarted, void(const AssertionInfo & info));

    MOCK_METHOD3(sectionStarted, bool(StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions));

    MOCK_METHOD1(sectionEnded, void(SectionEndInfo && endInfo));

    MOCK_METHOD1(sectionEndedEarly, void(SectionEndInfo && endInfo));

    MOCK_METHOD2(acquireGeneratorTracker, IGeneratorTracker *(StringRef generatorName, const SourceLineInfo & lineInfo));

    MOCK_METHOD3(createGeneratorTracker, IGeneratorTracker *(StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator));

    MOCK_METHOD1(benchmarkPreparing, void(StringRef name));

    MOCK_METHOD1(benchmarkStarting, void(const BenchmarkInfo & info));

    MOCK_METHOD1(benchmarkEnded, void(const BenchmarkStats<> & stats));

    MOCK_METHOD1(benchmarkFailed, void(StringRef error));

    MOCK_METHOD1(pushScopedMessage, void(const MessageInfo & message));

    MOCK_METHOD1(popScopedMessage, void(const MessageInfo & message));

    MOCK_METHOD1(emplaceUnscopedMessage, void(MessageBuilder && builder));

    MOCK_METHOD1(handleFatalErrorCondition, void(StringRef message));

    MOCK_METHOD4(handleExpr, void(const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction));

    MOCK_METHOD5(handleMessage, void(const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction));

    MOCK_METHOD2(handleUnexpectedExceptionNotThrown, void(const AssertionInfo & info, AssertionReaction & reaction));

    MOCK_METHOD3(handleUnexpectedInflightException, void(const AssertionInfo & info, std::string && message, AssertionReaction & reaction));

    MOCK_METHOD1(handleIncomplete, void(const AssertionInfo & info));

    MOCK_METHOD4(handleNonExpr, void(const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction));

    MOCK_METHOD0(lastAssertionPassed, bool());

    MOCK_METHOD0(assertionPassed, void());

    MOCK_METHOD0(getCurrentTestName, const std::string());

    MOCK_METHOD0(getLastResult, const AssertionResult *());

    MOCK_METHOD0(exceptionEarlyReported, void());

};



class BenchmarkTest_913 : public ::testing::Test {

protected:

    MockIConfig mockConfig;

    MockIResultCapture mockResultCapture;



    virtual void SetUp() override {

        Context::getCurrentMutableContext().setConfig(&mockConfig);

        Context::getCurrentMutableContext().setResultCapture(&mockResultCapture);

    }



    virtual void TearDown() override {

        Context::cleanUpContext();

    }

};



TEST_F(BenchmarkTest_913, BenchmarkPreparingIsCalled_913) {

    EXPECT_CALL(mockResultCapture, benchmarkPreparing(_)).Times(1);



    Benchmark bench("testBenchmark");

    bench.run<std::chrono::steady_clock>();

}



TEST_F(BenchmarkTest_913, BenchmarkStartingAndEndedAreCalled_913) {

    EXPECT_CALL(mockConfig, benchmarkSamples()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockResultCapture, benchmarkStarting(_)).Times(1);

    EXPECT_CALL(mockResultCapture, benchmarkEnded(_)).Times(1);



    Benchmark bench("testBenchmark");

    bench.run<std::chrono::steady_clock>();

}



TEST_F(BenchmarkTest_913, BenchmarkFailedIsCalledWhenAssertionFails_913) {

    MockFunction<void(const AssertionInfo & info)> mockAssert;

    EXPECT_CALL(mockResultCapture, handleExpr(_, _, _)).WillOnce([this, &mockAssert](const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction) {

        mockAssert.Call(info);

        throw TestFailureException("test failure");

    });

    EXPECT_CALL(mockResultCapture, benchmarkFailed(_)).Times(1);



    Benchmark bench("testBenchmark", [&]() { mockAssert.AsStdFunction(); ASSERT_TRUE(false); });

    try {

        bench.run<std::chrono::steady_clock>();

    } catch (...) {}

}



TEST_F(BenchmarkTest_913, BenchmarkRunsZeroSamples_913) {

    EXPECT_CALL(mockConfig, benchmarkSamples()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockResultCapture, benchmarkStarting(_)).Times(0);

    EXPECT_CALL(mockResultCapture, benchmarkEnded(_)).Times(0);



    Benchmark bench("testBenchmark");

    bench.run<std::chrono::steady_clock>();

}
