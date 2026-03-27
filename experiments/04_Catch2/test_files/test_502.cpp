#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo &info), (override));

};



class RunContextTest_502 : public ::testing::Test {

protected:

    NiceMock<MockIEventListener> mockReporter;

    IEventListenerPtr reporter = std::make_unique<NiceMock<MockIEventListener>>();

    const IConfig* config = nullptr; // Assuming a valid config is provided in actual usage

    RunContext runContext{config, CATCH_MOVE(reporter)};

};



TEST_F(RunContextTest_502, BenchmarkStarting_CallsReporterBenchmarkStarting_502) {

    BenchmarkInfo info;

    EXPECT_CALL(mockReporter, benchmarkStarting(_)).Times(1);

    runContext.benchmarkStarting(info);

}



TEST_F(RunContextTest_502, BenchmarkStarting_PassesCorrectInfoToReporter_502) {

    BenchmarkInfo expectedInfo{1.0, 100, 5, 3, 0.01, 0.001};

    EXPECT_CALL(mockReporter, benchmarkStarting(expectedInfo)).Times(1);

    runContext.benchmarkStarting(expectedInfo);

}



TEST_F(RunContextTest_502, BenchmarkStarting_NoObservableSideEffectsExceptReporterCall_502) {

    BenchmarkInfo info;

    EXPECT_CALL(mockReporter, benchmarkStarting(_)).Times(1);

    runContext.benchmarkStarting(info);

    // No other observable side effects to verify

}
