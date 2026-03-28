#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_session.hpp"

namespace {

// Helper to create a ReporterConfig for testing
class XmlReporterTest_843 : public ::testing::Test {
protected:
    std::ostringstream oss;
    
    std::unique_ptr<Catch::XmlReporter> createReporter() {
        // Create a minimal config for the reporter
        std::vector<const char*> args = {"test"};
        Catch::ConfigData configData;
        configData.showDurations = Catch::ShowDurations::DefaultForReporter;
        auto config = std::make_shared<Catch::Config>(configData);
        
        auto colour = Catch::makeColourImpl(
            Catch::ColourMode::None, &oss);
        
        Catch::ReporterConfig reporterConfig(
            config, CATCH_MOVE(oss), CATCH_MOVE(colour),
            std::map<std::string, std::string>{});
        
        return std::make_unique<Catch::XmlReporter>(CATCH_MOVE(reporterConfig));
    }
    
    std::string getOutput() {
        return oss.str();
    }
};

// Test that benchmarkPreparing writes BenchmarkResults element with name attribute
TEST_F(XmlReporterTest_843, BenchmarkPreparingWritesBenchmarkResultsElement_843) {
    auto reporter = createReporter();
    
    // Need to set up proper context first
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("MyBenchmark"_catch_sr);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
    EXPECT_THAT(output, ::testing::HasSubstr("MyBenchmark"));
}

// Test benchmarkPreparing with empty name
TEST_F(XmlReporterTest_843, BenchmarkPreparingWithEmptyName_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing(Catch::StringRef());
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
    EXPECT_THAT(output, ::testing::HasSubstr("name"));
}

// Test benchmarkPreparing with special characters in name
TEST_F(XmlReporterTest_843, BenchmarkPreparingWithSpecialCharsInName_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("Bench<mark>&\"test"_catch_sr);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
}

// Test that getDescription returns a non-empty string
TEST_F(XmlReporterTest_843, GetDescriptionReturnsNonEmptyString_843) {
    std::string desc = Catch::XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test benchmarkPreparing with long name
TEST_F(XmlReporterTest_843, BenchmarkPreparingWithLongName_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    std::string longName(1000, 'A');
    reporter->benchmarkPreparing(Catch::StringRef(longName));
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
    EXPECT_THAT(output, ::testing::HasSubstr(longName));
}

// Test benchmarkFailed writes error attribute
TEST_F(XmlReporterTest_843, BenchmarkFailedWritesError_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("FailBench"_catch_sr);
    reporter->benchmarkFailed("some error message"_catch_sr);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("some error message"));
}

// Test benchmarkPreparing with name containing only whitespace
TEST_F(XmlReporterTest_843, BenchmarkPreparingWithWhitespaceName_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("   "_catch_sr);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
}

// Test full benchmark lifecycle: preparing -> starting -> ended
TEST_F(XmlReporterTest_843, BenchmarkFullLifecycle_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("LifecycleBench"_catch_sr);
    
    Catch::BenchmarkInfo benchInfo{"LifecycleBench", 1.0, 100, 10, 1000, 10000};
    reporter->benchmarkStarting(benchInfo);
    
    Catch::BenchmarkStats<> stats{
        benchInfo,
        Catch::Benchmark::Estimate<double>{1.0, 0.9, 1.1, 0.95},
        Catch::Benchmark::Estimate<double>{0.1, 0.05, 0.15, 0.95},
        Catch::Benchmark::Estimate<double>{0.01, 0.005, 0.015, 0.95},
        Catch::Benchmark::Estimate<double>{0.5, 0.4, 0.6, 0.95},
        0
    };
    reporter->benchmarkEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("BenchmarkResults"));
    EXPECT_THAT(output, ::testing::HasSubstr("LifecycleBench"));
}

// Test that name attribute is properly set using writeAttribute
TEST_F(XmlReporterTest_843, BenchmarkPreparingNameAttributeFormat_843) {
    auto reporter = createReporter();
    
    Catch::TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Catch::TestCaseInfo testCaseInfo(
        "", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("AttributeTest"_catch_sr);
    
    std::string output = getOutput();
    // The XML should contain name="AttributeTest" as an attribute
    EXPECT_THAT(output, ::testing::HasSubstr("name=\"AttributeTest\""));
}

} // anonymous namespace
