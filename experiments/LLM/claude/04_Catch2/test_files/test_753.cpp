#include <catch2/reporters/catch_reporter_junit.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_reusable_string_stream.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_test_spec.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>

namespace {

// Helper to create a minimal ReporterConfig
class JunitReporterTestFixture_753 : public ::testing::Test {
protected:
    std::stringstream stream_;
    
    // We need to build the infrastructure to create a JunitReporter
    // This is complex due to Catch2's internal dependencies
    
    std::unique_ptr<Catch::IConfig const> makeConfig() {
        // Create a minimal config - we'll use default values
        // This requires building Catch2's config
        char const* argv[] = {"test"};
        Catch::ConfigData configData;
        configData.name = "test";
        return std::make_unique<Catch::Config>(configData);
    }
    
    Catch::ReporterConfig makeReporterConfig(Catch::IConfig const* config) {
        return Catch::ReporterConfig(config, stream_);
    }
    
    Catch::TestCaseInfo makeTestCaseInfo(std::string const& name) {
        Catch::SourceLineInfo lineInfo("test.cpp", 1);
        return Catch::TestCaseInfo(
            "", 
            {name, "[tag]"}, 
            lineInfo
        );
    }
};

TEST_F(JunitReporterTestFixture_753, GetDescription_753) {
    std::string desc = Catch::JunitReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedAccumulatesStdOut_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("TestCase1");
    reporter.testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
    reporter.sectionStarting(sectionInfo);
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::Totals sectionTotals;
    sectionTotals.assertions = counts;
    Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
    reporter.sectionEnded(sectionStats);
    
    Catch::Totals totals;
    totals.assertions.passed = 1;
    Catch::TestCaseStats stats(tcInfo, totals, std::string("Hello stdout"), std::string("Hello stderr"), false);
    reporter.testCaseEnded(stats);
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter.testRunEnded(runStats);
    
    std::string output = stream_.str();
    // The accumulated stdout should appear in the XML output
    EXPECT_NE(output.find("Hello stdout"), std::string::npos);
    EXPECT_NE(output.find("Hello stderr"), std::string::npos);
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedAccumulatesMultipleStdOut_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    // First test case
    {
        auto tcInfo = makeTestCaseInfo("TestCase1");
        reporter.testCaseStarting(tcInfo);
        
        Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
        reporter.sectionStarting(sectionInfo);
        
        Catch::Counts counts;
        counts.passed = 1;
        Catch::Totals sectionTotals;
        sectionTotals.assertions = counts;
        Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
        reporter.sectionEnded(sectionStats);
        
        Catch::Totals totals;
        totals.assertions.passed = 1;
        Catch::TestCaseStats stats(tcInfo, totals, std::string("output1"), std::string("error1"), false);
        reporter.testCaseEnded(stats);
    }
    
    // Second test case
    {
        auto tcInfo = makeTestCaseInfo("TestCase2");
        reporter.testCaseStarting(tcInfo);
        
        Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 2), "root");
        reporter.sectionStarting(sectionInfo);
        
        Catch::Counts counts;
        counts.passed = 1;
        Catch::Totals sectionTotals;
        sectionTotals.assertions = counts;
        Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
        reporter.sectionEnded(sectionStats);
        
        Catch::Totals totals;
        totals.assertions.passed = 1;
        Catch::TestCaseStats stats(tcInfo, totals, std::string("output2"), std::string("error2"), false);
        reporter.testCaseEnded(stats);
    }
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 2;
    runTotals.testCases.passed = 2;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter.testRunEnded(runStats);
    
    std::string output = stream_.str();
    // Both outputs should be accumulated
    EXPECT_NE(output.find("output1"), std::string::npos);
    EXPECT_NE(output.find("output2"), std::string::npos);
    EXPECT_NE(output.find("error1"), std::string::npos);
    EXPECT_NE(output.find("error2"), std::string::npos);
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedWithEmptyStdOutAndStdErr_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("TestCaseEmpty");
    reporter.testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
    reporter.sectionStarting(sectionInfo);
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::Totals sectionTotals;
    sectionTotals.assertions = counts;
    Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
    reporter.sectionEnded(sectionStats);
    
    Catch::Totals totals;
    totals.assertions.passed = 1;
    Catch::TestCaseStats stats(tcInfo, totals, std::string(""), std::string(""), false);
    reporter.testCaseEnded(stats);
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter.testRunEnded(runStats);
    
    // Should not crash and should produce valid XML
    std::string output = stream_.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedWithAbortingFlag_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("TestCaseAborting");
    reporter.testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
    reporter.sectionStarting(sectionInfo);
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::Totals sectionTotals;
    sectionTotals.assertions = counts;
    Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
    reporter.sectionEnded(sectionStats);
    
    Catch::Totals totals;
    totals.assertions.passed = 1;
    Catch::TestCaseStats stats(tcInfo, totals, std::string("aborting_out"), std::string("aborting_err"), true);
    reporter.testCaseEnded(stats);
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, true);
    reporter.testRunEnded(runStats);
    
    std::string output = stream_.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("aborting_out"), std::string::npos);
    EXPECT_NE(output.find("aborting_err"), std::string::npos);
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedWithLargeOutput_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("TestCaseLargeOutput");
    reporter.testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
    reporter.sectionStarting(sectionInfo);
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::Totals sectionTotals;
    sectionTotals.assertions = counts;
    Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
    reporter.sectionEnded(sectionStats);
    
    std::string largeOut(10000, 'A');
    std::string largeErr(10000, 'B');
    Catch::Totals totals;
    totals.assertions.passed = 1;
    Catch::TestCaseStats stats(tcInfo, totals, std::string(largeOut), std::string(largeErr), false);
    reporter.testCaseEnded(stats);
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter.testRunEnded(runStats);
    
    std::string output = stream_.str();
    EXPECT_FALSE(output.empty());
    // The large output should be present in the XML
    EXPECT_NE(output.find(largeOut), std::string::npos);
    EXPECT_NE(output.find(largeErr), std::string::npos);
}

TEST_F(JunitReporterTestFixture_753, TestCaseEndedWithSpecialCharactersInOutput_753) {
    auto config = makeConfig();
    auto reporterConfig = makeReporterConfig(config.get());
    Catch::JunitReporter reporter(CATCH_MOVE(reporterConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("TestCaseSpecialChars");
    reporter.testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("test.cpp", 1), "root");
    reporter.sectionStarting(sectionInfo);
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::Totals sectionTotals;
    sectionTotals.assertions = counts;
    Catch::SectionStats sectionStats(sectionInfo, sectionTotals, 0.1, false);
    reporter.sectionEnded(sectionStats);
    
    Catch::Totals totals;
    totals.assertions.passed = 1;
    // XML special characters
    Catch::TestCaseStats stats(tcInfo, totals, std::string("<xml>&\"special'"), std::string("error<>&"), false);
    reporter.testCaseEnded(stats);
    
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter.testRunEnded(runStats);
    
    std::string output = stream_.str();
    // Should produce valid XML (special chars should be escaped)
    EXPECT_FALSE(output.empty());
    // The raw special chars should be escaped, so raw '<xml>' shouldn't appear unescaped
    // But the content should still be present in some form
}

} // namespace
