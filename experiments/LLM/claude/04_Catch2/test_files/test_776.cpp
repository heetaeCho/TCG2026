#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/reporters/catch_reporter_automake.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_totals.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a custom stream
class AutomakeReporterTest_776 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid config for the reporter
        // Using Catch2's infrastructure to build it
    }

    std::unique_ptr<AutomakeReporter> createReporter(std::ostream& os) {
        // Create a minimal Catch2 config
        char const* argv[] = {"test"};
        Catch::Session session;
        session.applyCommandLine(1, argv);

        auto config = session.config();

        auto streamWrapper = Catch::Detail::make_unique<Catch::StringStreams::OutputStringStream>(os);
        
        Catch::ReporterConfig repConfig(config, CATCH_MOVE(streamWrapper), Catch::ColourMode::None, {});
        return std::make_unique<AutomakeReporter>(CATCH_MOVE(repConfig));
    }
};

// Since the construction of AutomakeReporter requires significant Catch2 infrastructure,
// let's test via a simpler approach by examining the known output format.

class AutomakeReporterOutputTest_776 : public ::testing::Test {
protected:
    std::stringstream m_oss;
    std::unique_ptr<AutomakeReporter> m_reporter;

    void SetUp() override {
        // Build the Catch2 session/config
        static const char* argv[] = {"test_exe"};
        m_session = std::make_unique<Catch::Session>();
        m_session->applyCommandLine(1, argv);
        
        auto cfg = m_session->config();

        // Create a stream wrapper around our stringstream
        auto wrapper = Catch::Detail::make_unique<Catch::Detail::StreamFromOStream>(m_oss);
        
        Catch::ReporterConfig repConfig(cfg, CATCH_MOVE(wrapper), Catch::ColourMode::None, {});
        m_reporter = std::make_unique<AutomakeReporter>(CATCH_MOVE(repConfig));
    }

    std::unique_ptr<Catch::Session> m_session;
};

} // anonymous namespace

TEST_F(AutomakeReporterOutputTest_776, SkipTestOutputsCorrectFormat_776) {
    // Create a TestCaseInfo for a test named "MyTestCase"
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("MyTestCase", "");
    Catch::TestCaseInfo testInfo("TestClass", nameAndTags, lineInfo);

    m_reporter->skipTest(testInfo);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: SKIP MyTestCase"), std::string::npos)
        << "Expected ':test-result: SKIP MyTestCase' in output, got: " << output;
}

TEST_F(AutomakeReporterOutputTest_776, SkipTestWithEmptyName_776) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    Catch::NameAndTags nameAndTags("", "");
    Catch::TestCaseInfo testInfo("", nameAndTags, lineInfo);

    m_reporter->skipTest(testInfo);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: SKIP"), std::string::npos)
        << "Expected ':test-result: SKIP' in output, got: " << output;
}

TEST_F(AutomakeReporterOutputTest_776, SkipTestWithSpecialCharactersInName_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 10);
    Catch::NameAndTags nameAndTags("Test with spaces & symbols!", "");
    Catch::TestCaseInfo testInfo("SomeClass", nameAndTags, lineInfo);

    m_reporter->skipTest(testInfo);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: SKIP Test with spaces & symbols!"), std::string::npos)
        << "Output was: " << output;
}

TEST_F(AutomakeReporterOutputTest_776, SkipTestEndsWithNewline_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 5);
    Catch::NameAndTags nameAndTags("SomeTest", "");
    Catch::TestCaseInfo testInfo("Class", nameAndTags, lineInfo);

    m_reporter->skipTest(testInfo);

    std::string output = m_oss.str();
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n') << "Expected output to end with newline";
}

TEST_F(AutomakeReporterOutputTest_776, TestCaseEndedWithPassingTest_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 100);
    Catch::NameAndTags nameAndTags("PassingTest", "");
    Catch::TestCaseInfo testInfo("TestClass", nameAndTags, lineInfo);

    // Create passing stats
    Catch::Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.failed = 0;

    Catch::TestCaseStats stats(testInfo, totals, "", "", false);

    m_reporter->testCaseEnded(stats);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: PASS"), std::string::npos)
        << "Expected PASS result in output, got: " << output;
    EXPECT_NE(output.find("PassingTest"), std::string::npos)
        << "Expected test name in output, got: " << output;
}

TEST_F(AutomakeReporterOutputTest_776, TestCaseEndedWithFailingTest_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 200);
    Catch::NameAndTags nameAndTags("FailingTest", "");
    Catch::TestCaseInfo testInfo("TestClass", nameAndTags, lineInfo);

    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 1;

    Catch::TestCaseStats stats(testInfo, totals, "", "", false);

    m_reporter->testCaseEnded(stats);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: FAIL"), std::string::npos)
        << "Expected FAIL result in output, got: " << output;
    EXPECT_NE(output.find("FailingTest"), std::string::npos)
        << "Expected test name in output, got: " << output;
}

TEST_F(AutomakeReporterOutputTest_776, MultipleSkipTestCalls_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 1);
    
    Catch::NameAndTags nameAndTags1("Test1", "");
    Catch::TestCaseInfo testInfo1("Class", nameAndTags1, lineInfo);
    
    Catch::NameAndTags nameAndTags2("Test2", "");
    Catch::TestCaseInfo testInfo2("Class", nameAndTags2, lineInfo);

    m_reporter->skipTest(testInfo1);
    m_reporter->skipTest(testInfo2);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: SKIP Test1"), std::string::npos);
    EXPECT_NE(output.find(":test-result: SKIP Test2"), std::string::npos);
}

TEST_F(AutomakeReporterOutputTest_776, GetDescriptionReturnsNonEmpty_776) {
    std::string desc = AutomakeReporter::getDescription();
    EXPECT_FALSE(desc.empty()) << "getDescription should return a non-empty string";
}

TEST_F(AutomakeReporterOutputTest_776, SkipTestWithLongName_776) {
    Catch::SourceLineInfo lineInfo("file.cpp", 1);
    std::string longName(1000, 'A');
    Catch::NameAndTags nameAndTags(longName, "");
    Catch::TestCaseInfo testInfo("Class", nameAndTags, lineInfo);

    m_reporter->skipTest(testInfo);

    std::string output = m_oss.str();
    EXPECT_NE(output.find(":test-result: SKIP"), std::string::npos);
    EXPECT_NE(output.find(longName), std::string::npos)
        << "Expected the long test name in the output";
}
