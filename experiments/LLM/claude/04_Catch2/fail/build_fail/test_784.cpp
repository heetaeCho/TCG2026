#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"

using namespace Catch;

namespace {

// Helper to create a StringStream-backed ReporterConfig
class TeamCityReporterTest_784 : public ::testing::Test {
protected:
    std::stringstream captured_stream;
    
    struct TestStream : public Catch::IStream {
        std::ostream& m_os;
        TestStream(std::ostream& os) : m_os(os) {}
        std::ostream& stream() override { return m_os; }
    };

    std::unique_ptr<TeamCityReporter> createReporter() {
        // We need to create a ReporterConfig with our custom stream
        // This depends on Catch2 internals; we try to use the available API
        auto stream = Catch::Detail::make_unique<TestStream>(captured_stream);
        
        // Create a minimal config
        int argc = 1;
        const char* argv[] = {"test"};
        Catch::Session session;
        session.applyCommandLine(argc, argv);
        
        auto config = session.config();
        Catch::ReporterConfig reporterConfig(
            config.get(),
            CATCH_MOVE(stream),
            Catch::ColourMode::None,
            {}
        );
        
        return std::make_unique<TeamCityReporter>(CATCH_MOVE(reporterConfig));
    }
    
    TestCaseInfo makeTestCaseInfo(const std::string& name) {
        return TestCaseInfo(
            "TestClass"_sr,
            NameAndTags(name, ""),
            SourceLineInfo("file.cpp", 1)
        );
    }
};

TEST_F(TeamCityReporterTest_784, TestCaseStartingOutputsTeamCityMessage_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info = makeTestCaseInfo("MyTestCase");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("##teamcity[testStarted name='MyTestCase']"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingOutputContainsNewline_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info = makeTestCaseInfo("SomeTest");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("]\n"), std::string::npos)
        << "Output should end with newline. Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingEscapesSpecialCharacters_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    // TeamCity escaping should handle special chars like |, ', [, ]
    auto info = makeTestCaseInfo("Test|with'special[chars]");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    // The name should be escaped, so raw special chars should not appear unescaped
    EXPECT_TRUE(output.find("##teamcity[testStarted name='") != std::string::npos)
        << "Output was: " << output;
    // The original unescaped name should NOT appear as-is
    EXPECT_EQ(output.find("Test|with'special[chars]"), std::string::npos)
        << "Special characters should be escaped. Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingWithEmptyNameUsesDefault_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    // Empty name should use a default name from TestCaseInfo
    auto info = makeTestCaseInfo("");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("##teamcity[testStarted name='"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingWithSimpleName_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info = makeTestCaseInfo("simple_test");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("##teamcity[testStarted name='simple_test']"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingMultipleTimesProducesMultipleMessages_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info1 = makeTestCaseInfo("test1");
    auto info2 = makeTestCaseInfo("test2");
    
    reporter->testCaseStarting(info1);
    reporter->testCaseStarting(info2);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("##teamcity[testStarted name='test1']"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("##teamcity[testStarted name='test2']"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingWithNewlineInName_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info = makeTestCaseInfo("test\nwith\nnewlines");
    
    reporter->testCaseStarting(info);
    
    std::string output = captured_stream.str();
    EXPECT_NE(output.find("##teamcity[testStarted name='"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(TeamCityReporterTest_784, TestCaseStartingStreamIsFlushed_784) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    auto info = makeTestCaseInfo("flush_test");
    
    reporter->testCaseStarting(info);
    
    // After testCaseStarting, the stream should be flushed
    // We verify by checking the output is immediately available
    std::string output = captured_stream.str();
    EXPECT_FALSE(output.empty()) << "Stream should be flushed and output available";
}

TEST_F(TeamCityReporterTest_784, GetDescriptionReturnsNonEmpty_784) {
    std::string desc = TeamCityReporter::getDescription();
    EXPECT_FALSE(desc.empty()) << "Description should not be empty";
}

} // anonymous namespace
