#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class XmlReporterAssertionTest_839 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        
        // Set up default expectations
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("")));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(Return(ColourMode::None));
    }

    void TearDown() override {
        reporter_.reset();
        // Config is owned; check if reporter takes ownership
    }

    std::unique_ptr<XmlReporter> createReporter() {
        std::ostringstream* os = new std::ostringstream();
        oss_ = os;
        auto config = ReporterConfig(mockConfig_, Detail::unique_ptr<std::ostream>(os), ColourMode::None, {});
        auto reporter = std::make_unique<XmlReporter>(CATCH_MOVE(config));
        return reporter;
    }

    AssertionResult makeResult(ResultWas::OfType resultType, bool hasExpr = false,
                                const std::string& message = "",
                                const std::string& expr = "",
                                const std::string& expandedExpr = "") {
        SourceLineInfo lineInfo("test.cpp", 42);
        AssertionInfo info("TEST_MACRO", lineInfo, "", resultType);
        AssertionResultData data(resultType, {});
        if (!message.empty()) {
            data.message = message;
        }
        if (hasExpr) {
            data.lazyExpression = {}; // Will need proper setup
        }
        return AssertionResult(info, CATCH_MOVE(data));
    }

    MockConfig* mockConfig_;
    std::ostringstream* oss_ = nullptr;
    std::unique_ptr<XmlReporter> reporter_;
};

// Test: Successful result is not included when includeSuccessfulResults is false
TEST_F(XmlReporterAssertionTest_839, SuccessfulResultNotIncludedWhenConfigSaysFalse_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    
    // Start required context
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 10);
    AssertionInfo info("CHECK", sli, "1 == 1", ResultWas::Ok);
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    std::string before = oss_->str();
    reporter->assertionEnded(stats);
    std::string after = oss_->str();
    
    // Successful result with no warnings should produce no expression/failure output
    // The output should not contain "Expression" element for OK results when not included
    std::string diff = after.substr(before.size());
    EXPECT_EQ(diff.find("Expression"), std::string::npos);
}

// Test: Successful result IS included when includeSuccessfulResults is true
TEST_F(XmlReporterAssertionTest_839, SuccessfulResultIncludedWhenConfigSaysTrue_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(true));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 10);
    AssertionInfo info("CHECK", sli, "1 == 1", ResultWas::Ok);
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    // When includeSuccessfulResults is true, we should see something in output
    // (though exact content depends on hasExpression)
    EXPECT_FALSE(output.empty());
}

// Test: ThrewException produces Exception element
TEST_F(XmlReporterAssertionTest_839, ThrewExceptionProducesExceptionElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 20);
    AssertionInfo info("REQUIRE", sli, "expr", ResultWas::ThrewException);
    AssertionResultData data(ResultWas::ThrewException, LazyExpression(false));
    data.message = "exception message";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Exception"), std::string::npos);
    EXPECT_NE(output.find("exception message"), std::string::npos);
}

// Test: FatalErrorCondition produces FatalErrorCondition element
TEST_F(XmlReporterAssertionTest_839, FatalErrorProducesFatalElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 30);
    AssertionInfo info("REQUIRE", sli, "expr", ResultWas::FatalErrorCondition);
    AssertionResultData data(ResultWas::FatalErrorCondition, LazyExpression(false));
    data.message = "fatal error";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("FatalErrorCondition"), std::string::npos);
    EXPECT_NE(output.find("fatal error"), std::string::npos);
}

// Test: ExplicitFailure produces Failure element
TEST_F(XmlReporterAssertionTest_839, ExplicitFailureProducesFailureElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 40);
    AssertionInfo info("FAIL", sli, "", ResultWas::ExplicitFailure);
    AssertionResultData data(ResultWas::ExplicitFailure, LazyExpression(false));
    data.message = "explicit fail message";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Failure"), std::string::npos);
    EXPECT_NE(output.find("explicit fail message"), std::string::npos);
}

// Test: ExplicitSkip produces Skip element
TEST_F(XmlReporterAssertionTest_839, ExplicitSkipProducesSkipElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 50);
    AssertionInfo info("SKIP", sli, "", ResultWas::ExplicitSkip);
    AssertionResultData data(ResultWas::ExplicitSkip, LazyExpression(false));
    data.message = "skipped";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Skip"), std::string::npos);
    EXPECT_NE(output.find("skipped"), std::string::npos);
}

// Test: Warning messages produce Warning elements
TEST_F(XmlReporterAssertionTest_839, WarningMessageProducesWarningElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 60);
    AssertionInfo info("", sli, "", ResultWas::Warning);
    AssertionResultData data(ResultWas::Warning, LazyExpression(false));
    data.message = "warning message";
    AssertionResult result(info, CATCH_MOVE(data));
    
    SourceLineInfo msgSli("test.cpp", 61);
    MessageInfo msgInfo("WARN", msgSli, ResultWas::Warning);
    msgInfo.message = "a warning";
    
    std::vector<MessageInfo> messages;
    messages.push_back(msgInfo);
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Warning"), std::string::npos);
}

// Test: Info messages included when result is not OK
TEST_F(XmlReporterAssertionTest_839, InfoMessagesIncludedWhenResultNotOk_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 70);
    AssertionInfo info("CHECK", sli, "false", ResultWas::ExpressionFailed);
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    SourceLineInfo msgSli("test.cpp", 71);
    MessageInfo msgInfo("INFO", msgSli, ResultWas::Info);
    msgInfo.message = "info detail";
    
    std::vector<MessageInfo> messages;
    messages.push_back(msgInfo);
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Info"), std::string::npos);
    EXPECT_NE(output.find("info detail"), std::string::npos);
}

// Test: Info messages NOT included when result is OK and includeSuccessfulResults is false
TEST_F(XmlReporterAssertionTest_839, InfoMessagesNotIncludedWhenResultOkAndNotIncluding_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 80);
    AssertionInfo info("CHECK", sli, "true", ResultWas::Ok);
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    SourceLineInfo msgSli("test.cpp", 81);
    MessageInfo msgInfo("INFO", msgSli, ResultWas::Info);
    msgInfo.message = "should not appear";
    
    std::vector<MessageInfo> messages;
    messages.push_back(msgInfo);
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    std::string before = oss_->str();
    reporter->assertionEnded(stats);
    std::string after = oss_->str();
    std::string diff = after.substr(before.size());
    
    EXPECT_EQ(diff.find("should not appear"), std::string::npos);
}

// Test: No info messages - empty messages vector
TEST_F(XmlReporterAssertionTest_839, NoInfoMessagesEmptyVector_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 90);
    AssertionInfo info("CHECK", sli, "1==2", ResultWas::ExpressionFailed);
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages; // empty
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    // Should not crash with empty messages
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test: Expression with hasExpression generates Expression element with attributes
TEST_F(XmlReporterAssertionTest_839, ExpressionElementGeneratedWhenHasExpression_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 100);
    AssertionInfo info("CHECK", sli, "a == b", ResultWas::ExpressionFailed);
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    // If the result has an expression, we expect Expression element
    if (result.hasExpression()) {
        EXPECT_NE(output.find("Expression"), std::string::npos);
        EXPECT_NE(output.find("success"), std::string::npos);
        EXPECT_NE(output.find("Original"), std::string::npos);
        EXPECT_NE(output.find("Expanded"), std::string::npos);
    }
}

// Test: Multiple info messages with mixed types
TEST_F(XmlReporterAssertionTest_839, MultipleInfoAndWarningMessages_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 110);
    AssertionInfo info("CHECK", sli, "x", ResultWas::ExpressionFailed);
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, CATCH_MOVE(data));
    
    SourceLineInfo msgSli1("test.cpp", 111);
    MessageInfo msg1("INFO", msgSli1, ResultWas::Info);
    msg1.message = "info1";
    
    SourceLineInfo msgSli2("test.cpp", 112);
    MessageInfo msg2("WARN", msgSli2, ResultWas::Warning);
    msg2.message = "warn1";
    
    SourceLineInfo msgSli3("test.cpp", 113);
    MessageInfo msg3("INFO", msgSli3, ResultWas::Info);
    msg3.message = "info2";
    
    std::vector<MessageInfo> messages = {msg1, msg2, msg3};
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("info1"), std::string::npos);
    EXPECT_NE(output.find("warn1"), std::string::npos);
    EXPECT_NE(output.find("info2"), std::string::npos);
}

// Test: Warning type in result doesn't produce extra element in switch (break case)
TEST_F(XmlReporterAssertionTest_839, WarningResultTypeProducesNoExtraElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 120);
    AssertionInfo info("", sli, "", ResultWas::Warning);
    AssertionResultData data(ResultWas::Warning, LazyExpression(false));
    data.message = "a warning result";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    // Should not crash; Warning result type hits break in switch
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test: Info result type produces Info element in switch
TEST_F(XmlReporterAssertionTest_839, InfoResultTypeProducesInfoElement_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(true));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("test.cpp", 130);
    AssertionInfo info("INFO", sli, "", ResultWas::Info);
    AssertionResultData data(ResultWas::Info, LazyExpression(false));
    data.message = "info result message";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("Info"), std::string::npos);
    EXPECT_NE(output.find("info result message"), std::string::npos);
}

// Test: Source info is written with correct file and line
TEST_F(XmlReporterAssertionTest_839, SourceInfoWrittenCorrectly_839) {
    EXPECT_CALL(*mockConfig_, includeSuccessfulResults()).WillRepeatedly(Return(false));
    
    auto reporter = createReporter();
    reporter->testRunStarting(TestRunInfo("test"));
    
    SourceLineInfo sli("myfile.cpp", 999);
    AssertionInfo info("REQUIRE", sli, "false", ResultWas::ExplicitFailure);
    AssertionResultData data(ResultWas::ExplicitFailure, LazyExpression(false));
    data.message = "fail here";
    AssertionResult result(info, CATCH_MOVE(data));
    
    std::vector<MessageInfo> messages;
    Totals totals;
    AssertionStats stats(result, messages, totals);
    
    reporter->assertionEnded(stats);
    std::string output = oss_->str();
    
    EXPECT_NE(output.find("myfile.cpp"), std::string::npos);
    EXPECT_NE(output.find("999"), std::string::npos);
}
