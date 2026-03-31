#include <catch2/reporters/catch_reporter_teamcity.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_istream.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <string>

using namespace Catch;
using ::testing::HasSubstr;
using ::testing::Not;

namespace {

// A custom IStream that wraps a stringstream so we can inspect output
class StringIStream : public Catch::IStream {
public:
    std::ostringstream m_oss;
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Helper to create a minimal IConfig
class FakeConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return 0.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

class TeamCityReporterTest_783 : public ::testing::Test {
protected:
    StringIStream* m_rawStream = nullptr;
    std::unique_ptr<TeamCityReporter> m_reporter;
    std::shared_ptr<FakeConfig> m_config;

    void SetUp() override {
        m_config = std::make_shared<FakeConfig>();
        auto streamPtr = Catch::Detail::make_unique<StringIStream>();
        m_rawStream = streamPtr.get();
        
        ReporterConfig reporterConfig(m_config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
        m_reporter = std::make_unique<TeamCityReporter>(CATCH_MOVE(reporterConfig));
    }

    std::string getOutput() const {
        return m_rawStream->str();
    }

    void clearOutput() {
        m_rawStream->m_oss.str("");
        m_rawStream->m_oss.clear();
    }

    AssertionResult makeResult(ResultWas::OfType resultType, bool hasExpr = false, 
                                std::string expr = "", std::string expandedExpr = "") {
        AssertionInfo info;
        info.macroName = "REQUIRE"_sr;
        info.lineInfo = SourceLineInfo("test.cpp", 42);
        if (hasExpr) {
            info.capturedExpression = "x == y";
        }

        AssertionResultData data;
        data.resultType = resultType;
        if (hasExpr) {
            data.reconstructedExpression = expandedExpr.empty() ? "1 == 2" : expandedExpr;
        }

        return AssertionResult(info, CATCH_MOVE(data));
    }

    AssertionStats makeStats(AssertionResult&& result, 
                              std::vector<MessageInfo> msgs = {}) {
        Totals totals;
        return AssertionStats(result, msgs, totals);
    }

    void setupTestCase(const std::string& testName, TestCaseProperties props = TestCaseProperties::None) {
        NameAndTags nat(testName, "");
        auto tcInfo = std::make_unique<TestCaseInfo>(""_sr, nat, SourceLineInfo("test.cpp", 1));
        tcInfo->properties = props;
        
        // Need to start a test run and test case to set currentTestCaseInfo
        TestRunInfo runInfo("test_group"_sr);
        m_reporter->testRunStarting(runInfo);
        m_reporter->testCaseStarting(*tcInfo);
        
        // Store the test case info for lifetime management
        m_testCaseInfos.push_back(std::move(tcInfo));
        clearOutput(); // Clear the setup output
    }

    std::vector<std::unique_ptr<TestCaseInfo>> m_testCaseInfos;
};

// Test: OK result should not produce testFailed output
TEST_F(TeamCityReporterTest_783, OkResultProducesNoFailureOutput_783) {
    setupTestCase("PassingTest");
    
    auto result = makeResult(ResultWas::Ok);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, Not(HasSubstr("##teamcity[testFailed")));
    EXPECT_THAT(output, Not(HasSubstr("##teamcity[testIgnored")));
}

// Test: ExpressionFailed produces testFailed
TEST_F(TeamCityReporterTest_783, ExpressionFailedProducesTestFailed_783) {
    setupTestCase("FailingTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(output, HasSubstr("expression failed"));
    EXPECT_THAT(output, HasSubstr("name='FailingTest'"));
}

// Test: ThrewException produces testFailed with "unexpected exception"
TEST_F(TeamCityReporterTest_783, ThrewExceptionProducesTestFailed_783) {
    setupTestCase("ThrowingTest");
    
    auto result = makeResult(ResultWas::ThrewException);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(output, HasSubstr("unexpected exception"));
}

// Test: FatalErrorCondition produces testFailed
TEST_F(TeamCityReporterTest_783, FatalErrorConditionProducesTestFailed_783) {
    setupTestCase("FatalTest");
    
    auto result = makeResult(ResultWas::FatalErrorCondition);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(output, HasSubstr("fatal error condition"));
}

// Test: DidntThrowException produces testFailed
TEST_F(TeamCityReporterTest_783, DidntThrowExceptionProducesTestFailed_783) {
    setupTestCase("NoThrowTest");
    
    auto result = makeResult(ResultWas::DidntThrowException);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(output, HasSubstr("no exception was thrown where one was expected"));
}

// Test: ExplicitFailure produces testFailed
TEST_F(TeamCityReporterTest_783, ExplicitFailureProducesTestFailed_783) {
    setupTestCase("ExplicitFailTest");
    
    auto result = makeResult(ResultWas::ExplicitFailure);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(output, HasSubstr("explicit failure"));
}

// Test: ExplicitSkip produces testIgnored
TEST_F(TeamCityReporterTest_783, ExplicitSkipProducesTestIgnored_783) {
    setupTestCase("SkippedTest");
    
    auto result = makeResult(ResultWas::ExplicitSkip);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testIgnored"));
    EXPECT_THAT(output, HasSubstr("explicit skip"));
    EXPECT_THAT(output, Not(HasSubstr("##teamcity[testFailed")));
}

// Test: OkToFail test case produces testIgnored instead of testFailed
TEST_F(TeamCityReporterTest_783, OkToFailProducesTestIgnored_783) {
    setupTestCase("OkToFailTest", TestCaseProperties::MayFail);
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("##teamcity[testIgnored"));
    EXPECT_THAT(output, HasSubstr("ok to fail"));
}

// Test: Single info message includes "with message:"
TEST_F(TeamCityReporterTest_783, SingleInfoMessageIncluded_783) {
    setupTestCase("InfoTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    
    MessageInfo msgInfo("INFO"_sr, SourceLineInfo("test.cpp", 10), ResultWas::Info);
    msgInfo.message = "some info message";
    std::vector<MessageInfo> msgs = {msgInfo};
    
    auto stats = makeStats(std::move(result), msgs);
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("with message:"));
    EXPECT_THAT(output, HasSubstr("some info message"));
}

// Test: Multiple info messages include "with messages:"
TEST_F(TeamCityReporterTest_783, MultipleInfoMessagesIncluded_783) {
    setupTestCase("MultiInfoTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    
    MessageInfo msg1("INFO"_sr, SourceLineInfo("test.cpp", 10), ResultWas::Info);
    msg1.message = "first message";
    MessageInfo msg2("INFO"_sr, SourceLineInfo("test.cpp", 11), ResultWas::Info);
    msg2.message = "second message";
    std::vector<MessageInfo> msgs = {msg1, msg2};
    
    auto stats = makeStats(std::move(result), msgs);
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("with messages:"));
    EXPECT_THAT(output, HasSubstr("first message"));
    EXPECT_THAT(output, HasSubstr("second message"));
}

// Test: Expression with expansion is included in output
TEST_F(TeamCityReporterTest_783, ExpressionAndExpansionIncluded_783) {
    setupTestCase("ExprTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed, true, "x == y", "1 == 2");
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("with expansion:"));
}

// Test: Source info is included in failure message
TEST_F(TeamCityReporterTest_783, SourceInfoIncludedInMessage_783) {
    setupTestCase("SourceInfoTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("test.cpp"));
}

// Test: No info messages means no "with message" text
TEST_F(TeamCityReporterTest_783, NoInfoMessagesNoWithMessage_783) {
    setupTestCase("NoMsgTest");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    std::vector<MessageInfo> emptyMsgs;
    auto stats = makeStats(std::move(result), emptyMsgs);
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, Not(HasSubstr("with message")));
}

// Test: Test name is escaped in output
TEST_F(TeamCityReporterTest_783, TestNameIsEscapedInOutput_783) {
    setupTestCase("Test with 'quotes'");
    
    auto result = makeResult(ResultWas::ExpressionFailed);
    auto stats = makeStats(std::move(result));
    
    m_reporter->assertionEnded(stats);
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("name='"));
    // The name should be escaped - quotes should be replaced
    EXPECT_THAT(output, HasSubstr("##teamcity[testFailed"));
}

} // anonymous namespace
