#include <catch2/reporters/catch_reporter_sonarqube.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_xmlwriter.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/reporters/catch_reporter_cumulative_base.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_session.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

using namespace Catch;

namespace {

// Helper to create a ReporterConfig pointing to a given stream
class SonarQubeReporterTest_828 : public ::testing::Test {
protected:
    std::stringstream ss;
    
    std::unique_ptr<SonarQubeReporter> createReporter() {
        // We need a valid config for the reporter
        // Using Catch2's internal mechanisms to create one
        auto config = std::make_shared<Catch::Config>();
        auto reporterConfig = ReporterConfig(config.get(), ss, Catch::ColourMode::None, {});
        storedConfig = config; // prevent destruction
        return std::make_unique<SonarQubeReporter>(std::move(reporterConfig));
    }
    
    std::shared_ptr<Catch::Config> storedConfig;
};

} // anonymous namespace

// Test that writeTestFile produces a file element with the correct path attribute
TEST_F(SonarQubeReporterTest_828, WriteTestFileProducesFileElement_828) {
    auto reporter = createReporter();
    
    std::vector<TestCaseNode const*> emptyNodes;
    reporter->writeTestFile("test_file.cpp"_sr, emptyNodes);
    
    std::string output = ss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("file"));
    EXPECT_THAT(output, ::testing::HasSubstr("path"));
    EXPECT_THAT(output, ::testing::HasSubstr("test_file.cpp"));
}

// Test that writeTestFile with empty test case nodes produces a file element with no testCase children
TEST_F(SonarQubeReporterTest_828, WriteTestFileWithEmptyNodes_828) {
    auto reporter = createReporter();
    
    std::vector<TestCaseNode const*> emptyNodes;
    reporter->writeTestFile("empty.cpp"_sr, emptyNodes);
    
    std::string output = ss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("empty.cpp"));
    // Should not contain testCase elements since there are no nodes
    EXPECT_THAT(output, ::testing::Not(::testing::HasSubstr("testCase")));
}

// Test that writeTestFile with an empty filename still produces a file element
TEST_F(SonarQubeReporterTest_828, WriteTestFileWithEmptyFilename_828) {
    auto reporter = createReporter();
    
    std::vector<TestCaseNode const*> emptyNodes;
    reporter->writeTestFile(""_sr, emptyNodes);
    
    std::string output = ss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("file"));
    EXPECT_THAT(output, ::testing::HasSubstr("path"));
}

// Test that getDescription returns a non-empty string
TEST_F(SonarQubeReporterTest_828, GetDescriptionReturnsNonEmpty_828) {
    std::string desc = SonarQubeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that testRunStarting can be called without error
TEST_F(SonarQubeReporterTest_828, TestRunStartingDoesNotThrow_828) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
}

// Test that writeTestFile with a path containing special characters
TEST_F(SonarQubeReporterTest_828, WriteTestFileWithSpecialCharsInFilename_828) {
    auto reporter = createReporter();
    
    std::vector<TestCaseNode const*> emptyNodes;
    reporter->writeTestFile("path/to/my<test>&file.cpp"_sr, emptyNodes);
    
    std::string output = ss.str();
    // XML should escape special characters
    EXPECT_THAT(output, ::testing::HasSubstr("file"));
    EXPECT_THAT(output, ::testing::HasSubstr("path"));
}

// Test multiple writeTestFile calls produce multiple file elements
TEST_F(SonarQubeReporterTest_828, MultipleWriteTestFileCalls_828) {
    auto reporter = createReporter();
    
    std::vector<TestCaseNode const*> emptyNodes;
    reporter->writeTestFile("file1.cpp"_sr, emptyNodes);
    reporter->writeTestFile("file2.cpp"_sr, emptyNodes);
    
    std::string output = ss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("file1.cpp"));
    EXPECT_THAT(output, ::testing::HasSubstr("file2.cpp"));
}
