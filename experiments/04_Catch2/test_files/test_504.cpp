#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

};



class RunContextTest_504 : public ::testing::Test {

protected:

    NiceMock<MockIEventListener> mockReporter;

    IConfig mockConfig;

    RunContext runContext{&mockConfig, IEventListenerPtr{new MockIEventListener(mockReporter)}};

};



TEST_F(RunContextTest_504, BenchmarkFailed_CallsReporterBenchmarkFailedWithErrorMessage_504) {

    StringRef errorMessage = "Benchmark failed due to some reason";

    EXPECT_CALL(mockReporter, benchmarkFailed(errorMessage));

    runContext.benchmarkFailed(errorMessage);

}



TEST_F(RunContextTest_504, BenchmarkFailed_HandlesEmptyErrorMessage_504) {

    StringRef errorMessage = "";

    EXPECT_CALL(mockReporter, benchmarkFailed(errorMessage));

    runContext.benchmarkFailed(errorMessage);

}
