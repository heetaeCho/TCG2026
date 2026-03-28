#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

};



class RunContextTest_501 : public ::testing::Test {

protected:

    NiceMock<MockIEventListener> mockReporter;

    RunContext runContext{nullptr, std::make_unique<MockIEventListener>(mockReporter)};

};



TEST_F(RunContextTest_501, BenchmarkPreparing_CallsReporter_501) {

    StringRef benchmarkName("Benchmark1");

    EXPECT_CALL(mockReporter, benchmarkPreparing(benchmarkName));

    runContext.benchmarkPreparing(benchmarkName);

}



TEST_F(RunContextTest_501, BenchmarkPreparing_EmptyString_501) {

    StringRef emptyBenchmarkName("");

    EXPECT_CALL(mockReporter, benchmarkPreparing(emptyBenchmarkName));

    runContext.benchmarkPreparing(emptyBenchmarkName);

}



TEST_F(RunContextTest_501, BenchmarkPreparing_LongString_501) {

    std::string longBenchmarkName(1024, 'a'); // 1KB string

    StringRef longStringRef(longBenchmarkName.c_str());

    EXPECT_CALL(mockReporter, benchmarkPreparing(longStringRef));

    runContext.benchmarkPreparing(longStringRef);

}
