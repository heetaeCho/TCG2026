#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig for JsonReporter construction
class JsonReporterTest_871 : public ::testing::Test {
protected:
    std::stringstream m_stream;
    std::unique_ptr<JsonReporter> m_reporter;

    void SetUp() override {
        // We need to build a valid ReporterConfig
        // This requires a Config object and an ostream
    }

    // Helper to create AssertionResult with given status
    static AssertionResult makeAssertionResult(bool ok, const char* file = "test.cpp", std::size_t line = 42) {
        AssertionInfo info;
        info.lineInfo = SourceLineInfo(file, line);
        info.macroName = "REQUIRE"_sr;
        info.capturedExpression = "x == y"_sr;

        AssertionResultData data;
        if (ok) {
            data.resultType = ResultWas::Ok;
        } else {
            data.resultType = ResultWas::ExpressionFailed;
        }

        return AssertionResult(info, CATCH_MOVE(data));
    }

    static AssertionStats makeAssertionStats(bool ok) {
        auto result = makeAssertionResult(ok);
        std::vector<MessageInfo> messages;
        Totals totals;
        return AssertionStats(result, messages, totals);
    }
};

} // anonymous namespace

TEST(JsonReporterDescription_871, GetDescription_871) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Since constructing a full JsonReporter requires a complex setup with
// ReporterConfig, Config, etc., we test what we can through the public interface.

// The following tests verify the lifecycle of JsonReporter through its
// streaming interface. We need a valid ReporterConfig to create the reporter.

class JsonReporterIntegration_871 : public ::testing::Test {
protected:
    std::stringstream m_stream;
    std::unique_ptr<JsonReporter> m_reporter;

    void SetUp() override {
        // Create minimal config for reporter
        auto configData = ConfigData{};
        configData.showDurations = ShowDurations::Never;
        auto config = std::make_shared<Config>(configData);
        
        auto reporterConfig = ReporterConfig(config, m_stream, ColourMode::None, {});
        m_reporter = std::make_unique<JsonReporter>(CATCH_MOVE(reporterConfig));
    }

    void TearDown() override {
        m_reporter.reset();
    }

    AssertionResult makeResult(bool ok, const char* file = "test.cpp", std::size_t line = 10) {
        AssertionInfo info;
        info.lineInfo = SourceLineInfo(file, line);
        info.macroName = "REQUIRE"_sr;
        info.capturedExpression = "a == b"_sr;

        AssertionResultData data;
        if (ok) {
            data.resultType = ResultWas::Ok;
        } else {
            data.resultType = ResultWas::ExpressionFailed;
        }
        return AssertionResult(info, CATCH_MOVE(data));
    }

    AssertionStats makeStats(bool ok) {
        auto result = makeResult(ok);
        return AssertionStats(result, {}, Totals{});
    }

    // Set up the reporter to be in a state where assertionEnded can be called
    void setupForAssertion() {
        TestRunInfo runInfo("test_run");
        m_reporter->testRunStarting(runInfo);

        auto tags = std::vector<Tag>{};
        auto props = TestCaseProperties::None;
        auto tcInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
        m_reporter->testCaseStarting(*tcInfo);
        m_reporter->testCasePartialStarting(*tcInfo, 0);

        SectionInfo sectionInfo(SourceLineInfo("file.cpp", 1), "section");
        m_reporter->sectionStarting(sectionInfo);
    }

    void teardownFromAssertion() {
        SectionStats sectionStats(SectionInfo(SourceLineInfo("file.cpp", 1), "section"), Counts{}, 0.0, false);
        m_reporter->sectionEnded(sectionStats);

        auto tcInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
        
        TestCaseStats tcStats(*tcInfo, Totals{}, "", "", false);
        m_reporter->testCasePartialEnded(tcStats, 0);
        m_reporter->testCaseEnded(tcStats);

        TestRunStats runStats(Totals{}, false);
        m_reporter->testRunEnded(runStats);
    }

    std::unique_ptr<TestCaseInfo> makeTestCaseInfo(
        const std::string& className,
        std::initializer_list<StringRef> strings,
        SourceLineInfo lineInfo) {
        return std::make_unique<TestCaseInfo>(
            ""_sr, className, strings, lineInfo);
    }
};

TEST_F(JsonReporterIntegration_871, AssertionEndedOk_871) {
    setupForAssertion();

    auto stats = makeStats(true);
    m_reporter->assertionEnded(stats);

    teardownFromAssertion();

    std::string output = m_stream.str();
    // The output should contain "assertion" as the kind
    EXPECT_NE(output.find("assertion"), std::string::npos);
    // The status should reflect isOk() == true
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(JsonReporterIntegration_871, AssertionEndedFailed_871) {
    setupForAssertion();

    auto stats = makeStats(false);
    m_reporter->assertionEnded(stats);

    teardownFromAssertion();

    std::string output = m_stream.str();
    EXPECT_NE(output.find("assertion"), std::string::npos);
    // Failed assertion: isOk() returns false
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(JsonReporterIntegration_871, AssertionEndedContainsKind_871) {
    setupForAssertion();

    auto stats = makeStats(true);
    m_reporter->assertionEnded(stats);

    teardownFromAssertion();

    std::string output = m_stream.str();
    EXPECT_NE(output.find("\"kind\""), std::string::npos);
    EXPECT_NE(output.find("\"assertion\""), std::string::npos);
}

TEST_F(JsonReporterIntegration_871, AssertionEndedContainsStatus_871) {
    setupForAssertion();

    auto stats = makeStats(true);
    m_reporter->assertionEnded(stats);

    teardownFromAssertion();

    std::string output = m_stream.str();
    EXPECT_NE(output.find("\"status\""), std::string::npos);
}

TEST_F(JsonReporterIntegration_871, MultipleAssertions_871) {
    setupForAssertion();

    auto stats1 = makeStats(true);
    m_reporter->assertionEnded(stats1);

    auto stats2 = makeStats(false);
    m_reporter->assertionEnded(stats2);

    teardownFromAssertion();

    std::string output = m_stream.str();
    // Both assertions should appear
    // Count occurrences of "assertion"
    size_t count = 0;
    size_t pos = 0;
    while ((pos = output.find("\"assertion\"", pos)) != std::string::npos) {
        ++count;
        pos += 11;
    }
    EXPECT_GE(count, 2u);
}

TEST_F(JsonReporterIntegration_871, AssertionStartingDoesNotCrash_871) {
    setupForAssertion();

    AssertionInfo info;
    info.lineInfo = SourceLineInfo("file.cpp", 1);
    info.macroName = "REQUIRE"_sr;
    info.capturedExpression = "x"_sr;
    
    // assertionStarting should be a no-op essentially
    EXPECT_NO_THROW(m_reporter->assertionStarting(info));

    auto stats = makeStats(true);
    m_reporter->assertionEnded(stats);

    teardownFromAssertion();
}

TEST_F(JsonReporterIntegration_871, TestRunLifecycleProducesValidJson_871) {
    TestRunInfo runInfo("full_lifecycle_test");
    m_reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("", {"lifecycle_test", "[unit]"}, SourceLineInfo("lifecycle.cpp", 5));
    m_reporter->testCaseStarting(*tcInfo);
    m_reporter->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo(SourceLineInfo("lifecycle.cpp", 5), "main_section");
    m_reporter->sectionStarting(sectionInfo);

    auto stats = makeStats(true);
    m_reporter->assertionEnded(stats);

    SectionStats sectionStats(SectionInfo(SourceLineInfo("lifecycle.cpp", 5), "main_section"), Counts{}, 0.0, false);
    m_reporter->sectionEnded(sectionStats);

    TestCaseStats tcStats(*tcInfo, Totals{}, "", "", false);
    m_reporter->testCasePartialEnded(tcStats, 0);
    m_reporter->testCaseEnded(tcStats);

    TestRunStats runStats(Totals{}, false);
    m_reporter->testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_FALSE(output.empty());
    // Should have opening brace for JSON object
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(JsonReporterIntegration_871, SourceInfoWritten_871) {
    setupForAssertion();

    AssertionInfo info;
    info.lineInfo = SourceLineInfo("myfile.cpp", 99);
    info.macroName = "CHECK"_sr;
    info.capturedExpression = "val"_sr;

    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(info, CATCH_MOVE(data));
    AssertionStats stats(result, {}, Totals{});

    m_reporter->assertionEnded(stats);

    teardownFromAssertion();

    std::string output = m_stream.str();
    // Source info should contain the filename
    EXPECT_NE(output.find("myfile.cpp"), std::string::npos);
}
