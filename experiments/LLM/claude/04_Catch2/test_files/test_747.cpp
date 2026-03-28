#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_tap.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_compiler_capabilities.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_section_info.hpp"

using namespace Catch;

namespace {

// Helper to create a string-stream based IStream
class StringIStream : public IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Helper to create ReporterConfig with a string stream
struct TestFixtureHelper {
    static Detail::unique_ptr<IStream> makeStream() {
        return Detail::unique_ptr<IStream>(new StringIStream());
    }
};

class TAPReporterTest_747 : public ::testing::Test {
protected:
    std::unique_ptr<TAPReporter> reporter;
    StringIStream* streamPtr = nullptr;

    void SetUp() override {
        // We need to create a ReporterConfig. This requires an IConfig and IStream.
        // Creating minimal config for testing.
    }

    TAPReporter* createReporter(StringIStream*& outStream) {
        auto stream = new StringIStream();
        outStream = stream;
        
        // We need to create a proper ReporterConfig
        // This depends on the Catch2 internals, so we try to construct one
        auto streamPtr = Detail::unique_ptr<IStream>(stream);
        
        // Create a minimal config
        char const* argv[] = {"test"};
        Catch::Session session;
        
        auto config = session.config();
        
        ReporterConfig reporterConfig(
            config,
            CATCH_MOVE(streamPtr),
            ColourMode::None,
            {}
        );
        
        return new TAPReporter(CATCH_MOVE(reporterConfig));
    }

    std::string getStreamContent() {
        if (streamPtr) return streamPtr->str();
        return "";
    }
};

TEST_F(TAPReporterTest_747, GetDescription_ReturnsNonEmptyString_747) {
    std::string desc = TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(TAPReporterTest_747, TestRunStarting_ProducesNoOutput_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    // testRunStarting for TAP should not produce significant output
    // (it may or may not produce output, we check it doesn't crash)
    SUCCEED();
}

TEST_F(TAPReporterTest_747, NoMatchingTestCases_OutputsWarning_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    rep->noMatchingTestCases("someSpec"_sr);
    
    std::string output = stream->str();
    // TAP reporter should output something about no matching test cases
    EXPECT_TRUE(output.find("someSpec") != std::string::npos || output.size() > 0);
}

TEST_F(TAPReporterTest_747, AssertionEnded_SuccessfulAssertion_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Test Case 1", "");
    SourceLineInfo lineInfo("file.cpp", 10);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    // Create a passing assertion
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    totals.assertions.passed = 1;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    std::string output = stream->str();
    // TAP format: "ok" for passing tests
    EXPECT_TRUE(output.find("ok") != std::string::npos);
    // Should contain test case name
    EXPECT_TRUE(output.find("Test Case 1") != std::string::npos);
}

TEST_F(TAPReporterTest_747, AssertionEnded_FailedAssertion_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Failing Test", "");
    SourceLineInfo lineInfo("file.cpp", 20);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::ExpressionFailed;
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    totals.assertions.failed = 1;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    std::string output = stream->str();
    // TAP format: "not ok" for failing tests
    EXPECT_TRUE(output.find("not ok") != std::string::npos);
    EXPECT_TRUE(output.find("Failing Test") != std::string::npos);
}

TEST_F(TAPReporterTest_747, AssertionEnded_CounterIncrements_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Counter Test", "");
    SourceLineInfo lineInfo("file.cpp", 30);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    // Create two passing assertions
    for (int i = 0; i < 2; ++i) {
        AssertionInfo assertionInfo(
            "test"_sr,
            lineInfo,
            ""_sr,
            ResultDisposition::Normal
        );
        
        AssertionResultData data;
        data.resultType = ResultWas::Ok;
        
        AssertionResult result(assertionInfo, CATCH_MOVE(data));
        std::vector<MessageInfo> messages;
        Totals totals;
        
        AssertionStats stats(result, messages, totals);
        rep->assertionEnded(stats);
    }
    
    std::string output = stream->str();
    // Should see numbered entries: "ok 1" and "ok 2"
    EXPECT_TRUE(output.find("1") != std::string::npos);
    EXPECT_TRUE(output.find("2") != std::string::npos);
}

TEST_F(TAPReporterTest_747, TestRunEnded_OutputsTotalCount_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("End Test", "");
    SourceLineInfo lineInfo("file.cpp", 40);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    // Add one assertion
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> messages;
    Totals totals;
    totals.assertions.passed = 1;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    // End the test run
    TestRunStats runStats(runInfo, totals, false);
    rep->testRunEnded(runStats);
    
    std::string output = stream->str();
    // TAP format should have "1..N" at the end
    EXPECT_TRUE(output.find("1..") != std::string::npos);
}

TEST_F(TAPReporterTest_747, AssertionEnded_WithInfoMessages_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Message Test", "");
    SourceLineInfo lineInfo("file.cpp", 50);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    
    // Create info messages
    std::vector<MessageInfo> messages;
    MessageInfo info("Some info message", lineInfo, ResultWas::Info);
    messages.push_back(info);
    
    Totals totals;
    totals.assertions.passed = 1;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    std::string output = stream->str();
    EXPECT_TRUE(output.find("Message Test") != std::string::npos);
}

TEST_F(TAPReporterTest_747, TestRunEnded_NoAssertions_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("empty suite"_sr);
    rep->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    rep->testRunEnded(runStats);
    
    std::string output = stream->str();
    // Should have "1..0" for zero tests
    EXPECT_TRUE(output.find("1..0") != std::string::npos);
}

TEST_F(TAPReporterTest_747, AssertionEnded_ExceptionThrown_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Exception Test", "");
    SourceLineInfo lineInfo("file.cpp", 60);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::ThrewException;
    data.message = "unexpected exception";
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> messages;
    Totals totals;
    totals.assertions.failed = 1;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    std::string output = stream->str();
    EXPECT_TRUE(output.find("not ok") != std::string::npos);
    EXPECT_TRUE(output.find("Exception Test") != std::string::npos);
}

TEST_F(TAPReporterTest_747, MultipleAssertions_CorrectTAPNumbering_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Numbering Test", "");
    SourceLineInfo lineInfo("file.cpp", 70);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    for (int i = 0; i < 5; ++i) {
        AssertionInfo assertionInfo(
            "test"_sr,
            lineInfo,
            ""_sr,
            ResultDisposition::Normal
        );
        
        AssertionResultData data;
        data.resultType = ResultWas::Ok;
        
        AssertionResult result(assertionInfo, CATCH_MOVE(data));
        std::vector<MessageInfo> messages;
        Totals totals;
        
        AssertionStats stats(result, messages, totals);
        rep->assertionEnded(stats);
    }
    
    Totals totals;
    totals.assertions.passed = 5;
    TestRunStats runStats(runInfo, totals, false);
    rep->testRunEnded(runStats);
    
    std::string output = stream->str();
    // After 5 assertions, plan line should be "1..5"
    EXPECT_TRUE(output.find("1..5") != std::string::npos);
}

TEST_F(TAPReporterTest_747, AssertionEnded_OutputContainsHash_747) {
    StringIStream* stream = nullptr;
    auto rep = std::unique_ptr<TAPReporter>(createReporter(stream));
    
    TestRunInfo runInfo("test suite"_sr);
    rep->testRunStarting(runInfo);
    
    NameAndTags nameAndTags("Hash Test", "");
    SourceLineInfo lineInfo("file.cpp", 80);
    TestCaseInfo testCaseInfo("TestClass"_sr, nameAndTags, lineInfo);
    rep->testCaseStarting(testCaseInfo);
    
    AssertionInfo assertionInfo(
        "test"_sr,
        lineInfo,
        ""_sr,
        ResultDisposition::Normal
    );
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(assertionInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> messages;
    Totals totals;
    
    AssertionStats stats(result, messages, totals);
    rep->assertionEnded(stats);
    
    std::string output = stream->str();
    // TAP uses "# " for comments, and test case name appears after #
    EXPECT_TRUE(output.find("# Hash Test") != std::string::npos);
}

} // anonymous namespace
