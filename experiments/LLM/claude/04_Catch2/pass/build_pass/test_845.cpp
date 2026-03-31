#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;
using namespace Catch::Benchmark;

namespace {

// Helper to create BenchmarkStats with specified values
BenchmarkStats<> makeBenchmarkStats(
    double meanVal, double meanLB, double meanUB, double meanCI,
    double sdVal, double sdLB, double sdUB, double sdCI,
    int lowMild, int lowSevere, int highMild, int highSevere,
    double outlierVar)
{
    BenchmarkStats<> stats;
    stats.info.name = "test_benchmark";
    stats.info.iterations = 1;
    stats.info.estimatedDuration = 1.0;

    stats.mean.point = FDuration(meanVal);
    stats.mean.lower_bound = FDuration(meanLB);
    stats.mean.upper_bound = FDuration(meanUB);
    stats.mean.confidence_interval = meanCI;

    stats.standardDeviation.point = FDuration(sdVal);
    stats.standardDeviation.lower_bound = FDuration(sdLB);
    stats.standardDeviation.upper_bound = FDuration(sdUB);
    stats.standardDeviation.confidence_interval = sdCI;

    stats.outliers.low_mild = lowMild;
    stats.outliers.low_severe = lowSevere;
    stats.outliers.high_mild = highMild;
    stats.outliers.high_severe = highSevere;

    stats.outlierVariance = outlierVar;

    return stats;
}

} // anonymous namespace

// Test that XmlWriter produces expected XML for mean element pattern
TEST(XmlWriterBenchmarkTest_845, MeanElementWrittenCorrectly_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        // Simulate what benchmarkEnded does for "mean"
        xml.startElement("BenchmarkResults");
        xml.scopedElement("mean")
            .writeAttribute("value"_sr, 100.0)
            .writeAttribute("lowerBound"_sr, 90.0)
            .writeAttribute("upperBound"_sr, 110.0)
            .writeAttribute("ci"_sr, 0.95);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
    EXPECT_NE(output.find("lowerBound"), std::string::npos);
    EXPECT_NE(output.find("upperBound"), std::string::npos);
    EXPECT_NE(output.find("ci"), std::string::npos);
}

// Test that XmlWriter produces expected XML for standardDeviation element pattern
TEST(XmlWriterBenchmarkTest_845, StandardDeviationElementWrittenCorrectly_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, 5.0)
            .writeAttribute("lowerBound"_sr, 3.0)
            .writeAttribute("upperBound"_sr, 7.0)
            .writeAttribute("ci"_sr, 0.95);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("standardDeviation"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
    EXPECT_NE(output.find("lowerBound"), std::string::npos);
    EXPECT_NE(output.find("upperBound"), std::string::npos);
}

// Test that XmlWriter produces expected XML for outliers element pattern
TEST(XmlWriterBenchmarkTest_845, OutliersElementWrittenCorrectly_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, 0.5)
            .writeAttribute("lowMild"_sr, 1)
            .writeAttribute("lowSevere"_sr, 2)
            .writeAttribute("highMild"_sr, 3)
            .writeAttribute("highSevere"_sr, 4);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("outliers"), std::string::npos);
    EXPECT_NE(output.find("variance"), std::string::npos);
    EXPECT_NE(output.find("lowMild"), std::string::npos);
    EXPECT_NE(output.find("lowSevere"), std::string::npos);
    EXPECT_NE(output.find("highMild"), std::string::npos);
    EXPECT_NE(output.find("highSevere"), std::string::npos);
}

// Test full benchmarkEnded simulation pattern with all three elements
TEST(XmlWriterBenchmarkTest_845, FullBenchmarkEndedPattern_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");

        // Simulate benchmarkEnded
        BenchmarkStats<> stats = makeBenchmarkStats(
            100.0, 90.0, 110.0, 0.95,
            5.0, 3.0, 7.0, 0.95,
            1, 2, 3, 4,
            0.25);

        xml.scopedElement("mean")
            .writeAttribute("value"_sr, stats.mean.point.count())
            .writeAttribute("lowerBound"_sr, stats.mean.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.mean.upper_bound.count())
            .writeAttribute("ci"_sr, stats.mean.confidence_interval);
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, stats.standardDeviation.point.count())
            .writeAttribute("lowerBound"_sr, stats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.standardDeviation.upper_bound.count())
            .writeAttribute("ci"_sr, stats.standardDeviation.confidence_interval);
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, stats.outlierVariance)
            .writeAttribute("lowMild"_sr, stats.outliers.low_mild)
            .writeAttribute("lowSevere"_sr, stats.outliers.low_severe)
            .writeAttribute("highMild"_sr, stats.outliers.high_mild)
            .writeAttribute("highSevere"_sr, stats.outliers.high_severe);
        xml.endElement();
    }
    std::string output = oss.str();

    // Verify all three sections are present
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("standardDeviation"), std::string::npos);
    EXPECT_NE(output.find("outliers"), std::string::npos);

    // Verify order: mean before standardDeviation before outliers
    auto meanPos = output.find("mean");
    auto sdPos = output.find("standardDeviation");
    auto outliersPos = output.find("outliers");
    EXPECT_LT(meanPos, sdPos);
    EXPECT_LT(sdPos, outliersPos);
}

// Test with zero values
TEST(XmlWriterBenchmarkTest_845, ZeroValuesBenchmarkStats_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");

        BenchmarkStats<> stats = makeBenchmarkStats(
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0, 0, 0, 0,
            0.0);

        xml.scopedElement("mean")
            .writeAttribute("value"_sr, stats.mean.point.count())
            .writeAttribute("lowerBound"_sr, stats.mean.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.mean.upper_bound.count())
            .writeAttribute("ci"_sr, stats.mean.confidence_interval);
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, stats.standardDeviation.point.count())
            .writeAttribute("lowerBound"_sr, stats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.standardDeviation.upper_bound.count())
            .writeAttribute("ci"_sr, stats.standardDeviation.confidence_interval);
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, stats.outlierVariance)
            .writeAttribute("lowMild"_sr, stats.outliers.low_mild)
            .writeAttribute("lowSevere"_sr, stats.outliers.low_severe)
            .writeAttribute("highMild"_sr, stats.outliers.high_mild)
            .writeAttribute("highSevere"_sr, stats.outliers.high_severe);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("standardDeviation"), std::string::npos);
    EXPECT_NE(output.find("outliers"), std::string::npos);
}

// Test with negative values (edge case)
TEST(XmlWriterBenchmarkTest_845, NegativeValuesBenchmarkStats_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");

        BenchmarkStats<> stats = makeBenchmarkStats(
            -100.0, -110.0, -90.0, 0.95,
            -5.0, -7.0, -3.0, 0.95,
            0, 0, 0, 0,
            -0.5);

        xml.scopedElement("mean")
            .writeAttribute("value"_sr, stats.mean.point.count())
            .writeAttribute("lowerBound"_sr, stats.mean.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.mean.upper_bound.count())
            .writeAttribute("ci"_sr, stats.mean.confidence_interval);
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, stats.standardDeviation.point.count())
            .writeAttribute("lowerBound"_sr, stats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.standardDeviation.upper_bound.count())
            .writeAttribute("ci"_sr, stats.standardDeviation.confidence_interval);
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, stats.outlierVariance)
            .writeAttribute("lowMild"_sr, stats.outliers.low_mild)
            .writeAttribute("lowSevere"_sr, stats.outliers.low_severe)
            .writeAttribute("highMild"_sr, stats.outliers.high_mild)
            .writeAttribute("highSevere"_sr, stats.outliers.high_severe);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("standardDeviation"), std::string::npos);
    EXPECT_NE(output.find("outliers"), std::string::npos);
}

// Test with large outlier values
TEST(XmlWriterBenchmarkTest_845, LargeOutlierValues_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");

        BenchmarkStats<> stats = makeBenchmarkStats(
            1e9, 1e8, 1e10, 0.99,
            1e6, 1e5, 1e7, 0.99,
            1000, 500, 2000, 100,
            0.99);

        xml.scopedElement("mean")
            .writeAttribute("value"_sr, stats.mean.point.count())
            .writeAttribute("lowerBound"_sr, stats.mean.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.mean.upper_bound.count())
            .writeAttribute("ci"_sr, stats.mean.confidence_interval);
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, stats.standardDeviation.point.count())
            .writeAttribute("lowerBound"_sr, stats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.standardDeviation.upper_bound.count())
            .writeAttribute("ci"_sr, stats.standardDeviation.confidence_interval);
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, stats.outlierVariance)
            .writeAttribute("lowMild"_sr, stats.outliers.low_mild)
            .writeAttribute("lowSevere"_sr, stats.outliers.low_severe)
            .writeAttribute("highMild"_sr, stats.outliers.high_mild)
            .writeAttribute("highSevere"_sr, stats.outliers.high_severe);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("outliers"), std::string::npos);
    // Check that the BenchmarkResults element is closed
    EXPECT_NE(output.find("</BenchmarkResults>"), std::string::npos);
}

// Test BenchmarkStats structure initialization
TEST(BenchmarkStatsTest_845, DefaultConstruction_845)
{
    BenchmarkStats<> stats;
    stats.mean.point = FDuration(42.0);
    stats.mean.lower_bound = FDuration(40.0);
    stats.mean.upper_bound = FDuration(44.0);
    stats.mean.confidence_interval = 0.95;

    EXPECT_DOUBLE_EQ(stats.mean.point.count(), 42.0);
    EXPECT_DOUBLE_EQ(stats.mean.lower_bound.count(), 40.0);
    EXPECT_DOUBLE_EQ(stats.mean.upper_bound.count(), 44.0);
    EXPECT_DOUBLE_EQ(stats.mean.confidence_interval, 0.95);
}

// Test OutlierClassification
TEST(OutlierClassificationTest_845, TotalReturnsSum_845)
{
    OutlierClassification oc;
    oc.low_mild = 1;
    oc.low_severe = 2;
    oc.high_mild = 3;
    oc.high_severe = 4;
    EXPECT_EQ(oc.total(), 10);
}

// Test OutlierClassification with zeros
TEST(OutlierClassificationTest_845, TotalWithZeros_845)
{
    OutlierClassification oc;
    oc.low_mild = 0;
    oc.low_severe = 0;
    oc.high_mild = 0;
    oc.high_severe = 0;
    EXPECT_EQ(oc.total(), 0);
}

// Test Estimate structure
TEST(EstimateTest_845, FDurationEstimate_845)
{
    Estimate<FDuration> est;
    est.point = FDuration(1.0);
    est.lower_bound = FDuration(0.5);
    est.upper_bound = FDuration(1.5);
    est.confidence_interval = 0.95;

    EXPECT_DOUBLE_EQ(est.point.count(), 1.0);
    EXPECT_DOUBLE_EQ(est.lower_bound.count(), 0.5);
    EXPECT_DOUBLE_EQ(est.upper_bound.count(), 1.5);
    EXPECT_DOUBLE_EQ(est.confidence_interval, 0.95);
}

// Test XmlWriter scoped element auto-closes
TEST(XmlWriterBenchmarkTest_845, ScopedElementAutoCloses_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("parent");
        {
            auto elem = xml.scopedElement("child");
            elem.writeAttribute("attr"_sr, "value"_sr);
        }
        // After scoped element destructor, child should be closed
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("child"), std::string::npos);
    EXPECT_NE(output.find("attr"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test confidence interval boundary values
TEST(XmlWriterBenchmarkTest_845, ConfidenceIntervalBoundary_845)
{
    std::ostringstream oss;
    {
        XmlWriter xml(oss);
        xml.startElement("BenchmarkResults");

        // CI of exactly 1.0 and 0.0
        BenchmarkStats<> stats = makeBenchmarkStats(
            50.0, 50.0, 50.0, 1.0,
            0.0, 0.0, 0.0, 0.0,
            0, 0, 0, 0,
            0.0);

        xml.scopedElement("mean")
            .writeAttribute("value"_sr, stats.mean.point.count())
            .writeAttribute("lowerBound"_sr, stats.mean.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.mean.upper_bound.count())
            .writeAttribute("ci"_sr, stats.mean.confidence_interval);
        xml.scopedElement("standardDeviation")
            .writeAttribute("value"_sr, stats.standardDeviation.point.count())
            .writeAttribute("lowerBound"_sr, stats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound"_sr, stats.standardDeviation.upper_bound.count())
            .writeAttribute("ci"_sr, stats.standardDeviation.confidence_interval);
        xml.scopedElement("outliers")
            .writeAttribute("variance"_sr, stats.outlierVariance)
            .writeAttribute("lowMild"_sr, stats.outliers.low_mild)
            .writeAttribute("lowSevere"_sr, stats.outliers.low_severe)
            .writeAttribute("highMild"_sr, stats.outliers.high_mild)
            .writeAttribute("highSevere"_sr, stats.outliers.high_severe);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("mean"), std::string::npos);
    EXPECT_NE(output.find("</BenchmarkResults>"), std::string::npos);
}
