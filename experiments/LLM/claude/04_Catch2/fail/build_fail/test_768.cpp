#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_reporter_registrars.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_stringref.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

namespace {

// Helper to create a ConsoleReporter with a stringstream for output capture
class ConsoleReporterTest_768 : public ::testing::Test {
protected:
    std::stringstream ss;
    std::unique_ptr<Catch::ConsoleReporter> reporter;

    void SetUp() override {
        // We need to set up the Catch2 infrastructure to create a ConsoleReporter
        // This involves creating a config and reporter config
        const char* argv[] = {"test"};
        Catch::Session session;
        session.applyCommandLine(1, argv);

        auto config = session.configData();
        auto catchConfig = std::make_shared<Catch::Config>(config);

        Catch::ReporterConfig reporterConfig(
            catchConfig.get(),
            ss,
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );

        reporter = std::make_unique<Catch::ConsoleReporter>(std::move(reporterConfig));

        // We need to simulate enough state so that benchmarkPreparing doesn't crash.
        // Start a test run and test case to set up internal state.
        Catch::TestRunInfo runInfo("test_group");
        reporter->testRunStarting(runInfo);

        auto tags = std::vector<Catch::Tag>{};
        Catch::TestCaseInfo testCaseInfo(
            "",
            {"test_class", "test_name", {"[tag]"}},
            Catch::SourceLineInfo("file.cpp", 1)
        );
        reporter->testCaseStarting(testCaseInfo);

        Catch::SectionInfo sectionInfo(
            Catch::SourceLineInfo("file.cpp", 1),
            "section"
        );
        reporter->sectionStarting(sectionInfo);
    }

    void TearDown() override {
        reporter.reset();
    }
};

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingWithShortName_768) {
    // Test that benchmarkPreparing with a short name produces output containing the name
    ss.str("");
    ss.clear();
    reporter->benchmarkPreparing(Catch::StringRef("short"));
    std::string output = ss.str();
    // The name should appear somewhere in the output
    EXPECT_NE(output.find("short"), std::string::npos);
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingWithEmptyName_768) {
    // Test that benchmarkPreparing with an empty name does not crash
    ss.str("");
    ss.clear();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("")));
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingWithLongName_768) {
    // Test that benchmarkPreparing with a very long name handles wrapping
    ss.str("");
    ss.clear();
    std::string longName(200, 'x');
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef(longName)));
    std::string output = ss.str();
    // At least part of the long name should appear
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingWithSpecialCharacters_768) {
    // Test that benchmarkPreparing handles special characters in the name
    ss.str("");
    ss.clear();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("bench<int, float>(\"test\")")));
    std::string output = ss.str();
    EXPECT_NE(output.find("bench"), std::string::npos);
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingCalledMultipleTimes_768) {
    // Test that calling benchmarkPreparing multiple times does not crash
    ss.str("");
    ss.clear();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("first")));
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("second")));
    std::string output = ss.str();
    EXPECT_NE(output.find("first"), std::string::npos);
    EXPECT_NE(output.find("second"), std::string::npos);
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingWithSpacesInName_768) {
    // Test name with spaces - should wrap at word boundaries
    ss.str("");
    ss.clear();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("benchmark with spaces in name")));
    std::string output = ss.str();
    EXPECT_NE(output.find("benchmark"), std::string::npos);
}

TEST_F(ConsoleReporterTest_768, BenchmarkPreparingSingleCharName_768) {
    // Test with single character name
    ss.str("");
    ss.clear();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(Catch::StringRef("A")));
    std::string output = ss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(ConsoleReporterTest_768, GetDescription_768) {
    // Test that getDescription returns a non-empty string
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

} // anonymous namespace
