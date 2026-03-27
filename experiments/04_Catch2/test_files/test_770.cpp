#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_console.cpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    NiceMock<MockConfig> config;

    Detail::unique_ptr<TablePrinter> table_printer = Detail::make_unique<TablePrinter>(std::cout, []() -> std::vector<ColumnInfo> { return {}; });

    BenchmarkStats<> benchmark_stats;



    ConsoleReporterTest()

        : reporter(ReporterConfig{&config}) {

        benchmark_stats.mean.point.count() = 100;

        benchmark_stats.mean.lower_bound.count() = 95;

        benchmark_stats.mean.upper_bound.count() = 105;

        benchmark_stats.standardDeviation.point.count() = 2;

        benchmark_stats.standardDeviation.lower_bound.count() = 1.8;

        benchmark_stats.standardDeviation.upper_bound.count() = 2.2;

    }



protected:

    ConsoleReporter reporter;

};



TEST_F(ConsoleReporterTest_770, BenchmarkEndedWithAnalysis_770) {

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*table_printer, operator<<(_)).Times(13); // 13 expected << operations for analysis case



    reporter.benchmarkEnded(benchmark_stats);

}



TEST_F(ConsoleReporterTest_770, BenchmarkEndedWithoutAnalysis_770) {

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*table_printer, operator<<(_)).Times(1); // 1 expected << operation for no analysis case



    reporter.benchmarkEnded(benchmark_stats);

}



TEST_F(ConsoleReporterTest_770, BenchmarkEndedBoundaryValues_770) {

    benchmark_stats.mean.point.count() = 0;

    benchmark_stats.mean.lower_bound.count() = 0;

    benchmark_stats.mean.upper_bound.count() = 0;

    benchmark_stats.standardDeviation.point.count() = 0;

    benchmark_stats.standardDeviation.lower_bound.count() = 0;

    benchmark_stats.standardDeviation.upper_bound.count() = 0;



    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*table_printer, operator<<(_)).Times(13); // Ensure boundary values are handled correctly



    reporter.benchmarkEnded(benchmark_stats);

}
