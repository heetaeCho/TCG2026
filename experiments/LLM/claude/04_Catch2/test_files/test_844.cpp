#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/catch_reporter_config.hpp"
#include "catch2/catch_test_run_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal ReporterConfig for testing
class XmlReporterTest_844 : public ::testing::Test {
protected:
    std::ostringstream oss;

    std::unique_ptr<XmlReporter> createReporter() {
        // Create a ReporterConfig that writes to our ostringstream
        auto config = std::make_shared<Catch::Config>(Catch::ConfigData{});
        ReporterConfig reporterConfig(config, oss, Catch::ColourMode::None, {});
        auto reporter = std::make_unique<XmlReporter>(CATCH_MOVE(reporterConfig));
        return reporter;
    }

    void prepareForBenchmark(XmlReporter& reporter) {
        // We need to set up state so benchmarkStarting can write attributes
        // This typically requires benchmarkPreparing to be called first to open a tag
        reporter.benchmarkPreparing("TestBenchmark"_catch_sr);
    }
};

} // anonymous namespace

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesSamples_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("samples=\"100\""), std::string::npos)
        << "Output should contain samples attribute. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesResamples_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("resamples=\"200\""), std::string::npos)
        << "Output should contain resamples attribute. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesIterations_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("iterations=\"50\""), std::string::npos)
        << "Output should contain iterations attribute. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesClockResolution_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("clockResolution="), std::string::npos)
        << "Output should contain clockResolution attribute. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesEstimatedDuration_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("estimatedDuration="), std::string::npos)
        << "Output should contain estimatedDuration attribute. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesNanoSecondsComment_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 100;
    info.resamples = 200;
    info.iterations = 50;
    info.clockResolution = 1.5;
    info.estimatedDuration = 3000.0;
    info.clockCost = 0.5;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("nano seconds"), std::string::npos)
        << "Output should contain comment about nano seconds. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWithZeroValues_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 0;
    info.resamples = 0;
    info.iterations = 0;
    info.clockResolution = 0.0;
    info.estimatedDuration = 0.0;
    info.clockCost = 0.0;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("samples=\"0\""), std::string::npos)
        << "Output should contain zero samples. Output: " << output;
    EXPECT_NE(output.find("resamples=\"0\""), std::string::npos)
        << "Output should contain zero resamples. Output: " << output;
    EXPECT_NE(output.find("iterations=\"0\""), std::string::npos)
        << "Output should contain zero iterations. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWithLargeValues_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 1000000;
    info.resamples = 2000000;
    info.iterations = 999999;
    info.clockResolution = 1e15;
    info.estimatedDuration = 1e18;
    info.clockCost = 1e10;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("samples=\"1000000\""), std::string::npos)
        << "Output should contain large samples value. Output: " << output;
    EXPECT_NE(output.find("resamples=\"2000000\""), std::string::npos)
        << "Output should contain large resamples value. Output: " << output;
    EXPECT_NE(output.find("iterations=\"999999\""), std::string::npos)
        << "Output should contain large iterations value. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWritesAllAttributesInOrder_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 10;
    info.resamples = 20;
    info.iterations = 5;
    info.clockResolution = 2.5;
    info.estimatedDuration = 500.0;
    info.clockCost = 1.0;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();

    auto samplesPos = output.find("samples=");
    auto resamplesPos = output.find("resamples=");
    auto iterationsPos = output.find("iterations=");
    auto clockResPos = output.find("clockResolution=");
    auto estDurPos = output.find("estimatedDuration=");

    ASSERT_NE(samplesPos, std::string::npos);
    ASSERT_NE(resamplesPos, std::string::npos);
    ASSERT_NE(iterationsPos, std::string::npos);
    ASSERT_NE(clockResPos, std::string::npos);
    ASSERT_NE(estDurPos, std::string::npos);

    // Verify ordering
    EXPECT_LT(samplesPos, resamplesPos);
    EXPECT_LT(resamplesPos, iterationsPos);
    EXPECT_LT(iterationsPos, clockResPos);
    EXPECT_LT(clockResPos, estDurPos);
}

TEST_F(XmlReporterTest_844, BenchmarkStartingWithSingleSample_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 1;
    info.resamples = 1;
    info.iterations = 1;
    info.clockResolution = 0.001;
    info.estimatedDuration = 0.001;
    info.clockCost = 0.001;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    EXPECT_NE(output.find("samples=\"1\""), std::string::npos)
        << "Output should handle single sample. Output: " << output;
    EXPECT_NE(output.find("iterations=\"1\""), std::string::npos)
        << "Output should handle single iteration. Output: " << output;
}

TEST_F(XmlReporterTest_844, BenchmarkStartingOutputContainsXmlComment_844) {
    auto reporter = createReporter();
    prepareForBenchmark(*reporter);

    BenchmarkInfo info;
    info.samples = 42;
    info.resamples = 84;
    info.iterations = 21;
    info.clockResolution = 10.0;
    info.estimatedDuration = 100.0;
    info.clockCost = 5.0;

    reporter->benchmarkStarting(info);

    std::string output = oss.str();
    // XML comments are enclosed in <!-- -->
    EXPECT_NE(output.find("<!--"), std::string::npos)
        << "Output should contain XML comment opening. Output: " << output;
    EXPECT_NE(output.find("-->"), std::string::npos)
        << "Output should contain XML comment closing. Output: " << output;
}
