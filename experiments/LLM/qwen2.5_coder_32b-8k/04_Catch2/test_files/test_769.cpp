#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_console.hpp"

#include "./TestProjects/Catch2/src/catch2/benchmark/detail/catch_benchmark_stats.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockTablePrinter : public TablePrinter {

public:

    MOCK_METHOD1(operator<<, TablePrinter&(std::string const&));

    MOCK_METHOD0(operator<<, TablePrinter&(ColumnBreak const&));

    MOCK_METHOD0(operator<<, TablePrinter&(OutputFlush const&));

};



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    NiceMock<MockTablePrinter> mockTablePrinter;

    NiceMock<MockConfig> mockConfig;

    BenchmarkInfo benchmarkInfo;



    void SetUp() override {

        benchmarkInfo.samples = 100;

        benchmarkInfo.iterations = 500;

        benchmarkInfo.estimatedDuration = 2.5;

        benchmarkInfo.resamples = 10;

        benchmarkInfo.clockResolution = 0.1;

        benchmarkInfo.clockCost = 0.01;



        ConsoleReporter reporter({&mockTablePrinter, &mockConfig});

    }

};



TEST_F(ConsoleReporterTest_769, BenchmarkStarting_NormalOperation_769) {

    EXPECT_CALL(mockTablePrinter, operator<<(std::to_string(benchmarkInfo.samples)))

        .Times(1);

    EXPECT_CALL(mockTablePrinter, operator<<(ColumnBreak()))

        .Times(2);

    EXPECT_CALL(mockTablePrinter, operator<<(Duration(benchmarkInfo.estimatedDuration)))

        .Times(1);

    EXPECT_CALL(mockConfig, benchmarkNoAnalysis())

        .WillOnce(Return(false));

    EXPECT_CALL(mockTablePrinter, operator<<(OutputFlush{}))

        .Times(1);



    ConsoleReporter reporter({&mockTablePrinter, &mockConfig});

    reporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(ConsoleReporterTest_769, BenchmarkStarting_NoAnalysis_769) {

    EXPECT_CALL(mockTablePrinter, operator<<(std::to_string(benchmarkInfo.samples)))

        .Times(1);

    EXPECT_CALL(mockTablePrinter, operator<<(ColumnBreak()))

        .Times(2);

    EXPECT_CALL(mockConfig, benchmarkNoAnalysis())

        .WillOnce(Return(true));

    EXPECT_CALL(mockTablePrinter, operator<<(Duration(benchmarkInfo.estimatedDuration)))

        .Times(0);

    EXPECT_CALL(mockTablePrinter, operator<<(OutputFlush{}))

        .Times(1);



    ConsoleReporter reporter({&mockTablePrinter, &mockConfig});

    reporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(ConsoleReporterTest_769, BenchmarkStarting_BoundaryConditions_769) {

    benchmarkInfo.samples = 0;

    benchmarkInfo.iterations = 0;

    benchmarkInfo.estimatedDuration = 0;



    EXPECT_CALL(mockTablePrinter, operator<<(std::to_string(benchmarkInfo.samples)))

        .Times(1);

    EXPECT_CALL(mockTablePrinter, operator<<(ColumnBreak()))

        .Times(2);

    EXPECT_CALL(mockConfig, benchmarkNoAnalysis())

        .WillOnce(Return(false));

    EXPECT_CALL(mockTablePrinter, operator<<(Duration(benchmarkInfo.estimatedDuration)))

        .Times(1);

    EXPECT_CALL(mockTablePrinter, operator<<(OutputFlush{}))

        .Times(1);



    ConsoleReporter reporter({&mockTablePrinter, &mockConfig});

    reporter.benchmarkStarting(benchmarkInfo);

}
