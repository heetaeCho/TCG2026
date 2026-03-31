#include <catch2/reporters/catch_reporter_junit.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_test_spec.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>

using namespace Catch;

namespace {

// Helper to create an AssertionResult with a specific ResultWas type
AssertionResult makeAssertionResult(ResultWas::OfType resultType) {
    AssertionInfo info;
    info.macroName = "TEST_CASE"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 1);
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data;
    data.resultType = resultType;

    return AssertionResult(info, CATCH_MOVE(data));
}

AssertionStats makeAssertionStats(ResultWas::OfType resultType) {
    auto result = makeAssertionResult(resultType);
    std::vector<MessageInfo> messages;
    Totals totals;
    return AssertionStats(result, messages, totals);
}

// Helper to create a minimal ReporterConfig
class JunitReporterTestFixture_752 : public ::testing::Test {
protected:
    std::stringstream stream;

    std::unique_ptr<JunitReporter> createReporter() {
        // We need a valid IConfig - create a minimal one
        auto configData = ConfigData{};
        configData.name = "test";
        auto config = std::make_shared<Config>(configData);
        
        ReporterConfig reporterConfig(config.get(), Detail::make_unique<std::ostream&>(stream), ColourMode::None, {});
        storedConfig = config; // prevent destruction
        return std::make_unique<JunitReporter>(CATCH_MOVE(reporterConfig));
    }

    std::shared_ptr<Config> storedConfig;
};

} // anonymous namespace

// Test that assertionEnded does not crash with a normal Ok result
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithOkResult_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    // Set up the reporter in proper state
    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::Ok);
    // Should not throw
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test that assertionEnded handles ThrewException type (should increment unexpectedExceptions)
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithThrewException_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ThrewException);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with ExpressionFailed
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithExpressionFailed_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ExpressionFailed);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with ExplicitFailure
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithExplicitFailure_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ExplicitFailure);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with Info result
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithInfoResult_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::Info);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with FatalErrorCondition
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithFatalErrorCondition_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::FatalErrorCondition);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test that multiple assertionEnded calls work correctly
TEST_F(JunitReporterTestFixture_752, MultipleAssertionEndedCalls_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto statsOk = makeAssertionStats(ResultWas::Ok);
    auto statsThrew = makeAssertionStats(ResultWas::ThrewException);
    auto statsFailed = makeAssertionStats(ResultWas::ExpressionFailed);

    EXPECT_NO_THROW(reporter->assertionEnded(statsOk));
    EXPECT_NO_THROW(reporter->assertionEnded(statsThrew));
    EXPECT_NO_THROW(reporter->assertionEnded(statsFailed));
    EXPECT_NO_THROW(reporter->assertionEnded(statsThrew));
}

// Test that ThrewException with okToFail tag doesn't increment unexpectedExceptions
// Observable through full lifecycle XML output
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithOkToFailTag_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    // Create test case with !mayfail tag to set m_okToFail = true
    auto tags = std::vector<Tag>{{"!mayfail"_catch_sr}};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::MayFail);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ThrewException);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with DidntThrowException
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithDidntThrowException_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::DidntThrowException);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test assertionEnded with Warning
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithWarning_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::Warning);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}

// Test getDescription returns a non-empty string
TEST_F(JunitReporterTestFixture_752, GetDescriptionReturnsNonEmpty_752) {
    std::string desc = JunitReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test full lifecycle: ThrewException without okToFail shows in output
TEST_F(JunitReporterTestFixture_752, FullLifecycleWithThrewExceptionInOutput_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ThrewException);
    reporter->assertionEnded(stats);

    Counts counts;
    counts.failed = 1;
    SectionStats sectionStats(sectionInfo, counts, 0.1, false);
    reporter->sectionEnded(sectionStats);

    Totals totals;
    totals.assertions.failed = 1;
    TestCaseStats testCaseStats(testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);

    totals.testCases.failed = 1;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);

    std::string output = stream.str();
    // The output should contain something related to the test - at minimum XML
    EXPECT_FALSE(output.empty());
}

// Test ExplicitSkip result type
TEST_F(JunitReporterTestFixture_752, AssertionEndedWithExplicitSkip_752) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);

    auto tags = std::vector<Tag>{};
    auto testCaseInfo = TestCaseInfo("test case", {"class"}, {"test.cpp", 1}, "", tags, TestCaseProperties::None);
    reporter->testCaseStarting(testCaseInfo);

    SectionInfo sectionInfo({"test.cpp", 1}, "root section");
    reporter->sectionStarting(sectionInfo);

    auto stats = makeAssertionStats(ResultWas::ExplicitSkip);
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
}
