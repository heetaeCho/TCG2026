#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_reporter_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig for constructing the reporter
class TeamCityReporterTest_573 : public ::testing::Test {
protected:
    void SetUp() override {
        stream = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<TeamCityReporter> makeReporter() {
        auto config = Catch::makeTestConfig();
        // We need a valid ReporterConfig. The exact construction depends on Catch2 internals.
        // Using a minimal approach:
        auto catchConfig = Catch::ConfigData{};
        auto cfg = std::make_shared<Catch::Config>(catchConfig);
        auto reporterConfig = ReporterConfig(cfg, Detail::make_unique<Catch::TextStream>(*stream));
        return std::make_unique<TeamCityReporter>(CATCH_MOVE(reporterConfig));
    }

    std::unique_ptr<std::ostringstream> stream;
};

} // anonymous namespace

// Test that sectionStarting can be called without crashing with a valid SectionInfo
TEST_F(TeamCityReporterTest_573, SectionStartingDoesNotCrash_573) {
    auto reporter = makeReporter();

    // Need to set up test run and test case context first
    TestRunInfo runInfo("test run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"test case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "test section");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
}

// Test that sectionStarting works with empty section name
TEST_F(TeamCityReporterTest_573, SectionStartingWithEmptyName_573) {
    auto reporter = makeReporter();

    TestRunInfo runInfo("test run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"test case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
}

// Test that multiple nested sections can be started
TEST_F(TeamCityReporterTest_573, MultipleSectionStarting_573) {
    auto reporter = makeReporter();

    TestRunInfo runInfo("test run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"test case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo section1(SourceLineInfo("file.cpp", 10), "section 1");
    SectionInfo section2(SourceLineInfo("file.cpp", 20), "section 2");

    EXPECT_NO_THROW(reporter->sectionStarting(section1));
    EXPECT_NO_THROW(reporter->sectionStarting(section2));
}

// Test that sectionStarting with special characters in name doesn't crash
TEST_F(TeamCityReporterTest_573, SectionStartingWithSpecialCharacters_573) {
    auto reporter = makeReporter();

    TestRunInfo runInfo("test run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"test case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10),
                            "section with |special| 'chars' \n and [brackets]");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
}

// Test getDescription returns non-empty string
TEST_F(TeamCityReporterTest_573, GetDescriptionReturnsNonEmpty_573) {
    std::string desc = TeamCityReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}
