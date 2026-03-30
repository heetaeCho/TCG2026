#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_run_context.hpp"

#include "./TestProjects/Catch2/src/catch2/benchmark/detail/catch_benchmark_stats.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Mock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> &stats), (override));

};



class RunContextTest_503 : public ::testing::Test {

protected:

    MockIEventListener mockReporter;

    IConfig mockConfig;

    RunContext runContext{&mockConfig, std::make_unique<MockIEventListener>(mockReporter)};

};



TEST_F(RunContextTest_503, BenchmarkEnded_DelegatesToReporter_503) {

    BenchmarkStats<> stats;

    EXPECT_CALL(mockReporter, benchmarkEnded(stats)).Times(1);

    runContext.benchmarkEnded(stats);

}



TEST_F(RunContextTest_503, BenchmarkEnded_HandlesEmptySamplesVector_503) {

    BenchmarkStats<> stats;

    stats.samples = {};

    EXPECT_CALL(mockReporter, benchmarkEnded(stats)).Times(1);

    runContext.benchmarkEnded(stats);

}



TEST_F(RunContextTest_503, BenchmarkEnded_HandlesNonEmptySamplesVector_503) {

    BenchmarkStats<> stats;

    stats.samples = {Benchmark::FDuration{1.0}};

    EXPECT_CALL(mockReporter, benchmarkEnded(stats)).Times(1);

    runContext.benchmarkEnded(stats);

}



TEST_F(RunContextTest_503, BenchmarkEnded_HandlesMeanAndStandardDeviation_503) {

    BenchmarkStats<> stats;

    stats.mean = {Benchmark::FDuration{2.0}, Benchmark::FDuration{1.5}};

    stats.standardDeviation = {Benchmark::FDuration{0.5}, Benchmark::FDuration{0.4}};

    EXPECT_CALL(mockReporter, benchmarkEnded(stats)).Times(1);

    runContext.benchmarkEnded(stats);

}



TEST_F(RunContextTest_503, BenchmarkEnded_HandlesOutliers_503) {

    BenchmarkStats<> stats;

    stats.outliers = Benchmark::OutlierClassification{};

    stats.outlierVariance = 0.2;

    EXPECT_CALL(mockReporter, benchmarkEnded(stats)).Times(1);

    runContext.benchmarkEnded(stats);

}
