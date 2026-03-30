#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"



using namespace Catch;

using ::testing::NiceMock;



class MockBenchmarkStats : public BenchmarkStats<> {

public:

    MockBenchmarkStats() {}

};



class CumulativeReporterBaseTest_856 : public ::testing::Test {

protected:

    ReporterConfig config;

    CumulativeReporterBase reporter;



    CumulativeReporterBaseTest_856() : reporter(CATCH_MOVE(config)) {}



    void SetUp() override {

        SectionNode rootSection(SectionStats());

        reporter.m_sectionStack.push_back(&rootSection);

    }

};



TEST_F(CumulativeReporterBaseTest_856, BenchmarkEndedAddsBenchmark_856) {

    MockBenchmarkStats mockBenchmarkStats;

    reporter.benchmarkEnded(mockBenchmarkStats);



    EXPECT_EQ(reporter.m_sectionStack.back()->assertionsAndBenchmarks.size(), 1);

}



TEST_F(CumulativeReporterBaseTest_856, BenchmarkEndedWithEmptyStackDoesNothing_856) {

    reporter.m_sectionStack.clear();

    MockBenchmarkStats mockBenchmarkStats;

    reporter.benchmarkEnded(mockBenchmarkStats);



    // Since m_sectionStack is empty, no benchmark should be added.

}



TEST_F(CumulativeReporterBaseTest_856, BenchmarkEndedMultipleTimesAddsMultipleBenchmarks_856) {

    MockBenchmarkStats mockBenchmarkStats1;

    MockBenchmarkStats mockBenchmarkStats2;



    reporter.benchmarkEnded(mockBenchmarkStats1);

    reporter.benchmarkEnded(mockBenchmarkStats2);



    EXPECT_EQ(reporter.m_sectionStack.back()->assertionsAndBenchmarks.size(), 2);

}
