// File: tests/XmlReporter_testCaseStarting_837.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 public headers we rely on (names based on provided partials)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"   // ReporterConfig
#include "catch2/catch_test_case_info.hpp"               // TestCaseInfo, NameAndTags
#include "catch2/internal/catch_source_line_info.hpp"    // SourceLineInfo
#include "catch2/interfaces/catch_interfaces_config.hpp" // IConfig
#include "catch2/catch_user_config.hpp"

using namespace Catch;
using ::testing::Return;

// --- Minimal mock to control observable config behavior ---
class MockConfig_837 : public IConfig {
public:
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));

    // The rest are not used by the SUT in these tests; provide safe dummies
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD((const TestSpec&), testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// --- Test fixture ---
class XmlReporterTest_837 : public ::testing::Test {
protected:
    std::ostringstream out;
    std::unique_ptr<MockConfig_837> cfg;

    std::unique_ptr<XmlReporter> makeReporter() {
        // ReporterConfig takes: stream, config, &verbosity (optional in some versions)
        ReporterConfig rcfg{ out, cfg.get() };
        return std::make_unique<XmlReporter>(std::move(rcfg));
    }

    // Helper to build a minimal TestCaseInfo with name/tags/file/line
    static TestCaseInfo makeTestInfo(const std::string& name,
                                     const std::string& tags,
                                     const std::string& file,
                                     std::size_t line) {
        NameAndTags nt;
        nt.name = name;
        nt.tags = tags; // e.g., "[fast][core]"
        SourceLineInfo sli{ file.c_str(), static_cast<unsigned int>(line) };
        return TestCaseInfo{ StringRef{}, nt, sli };
    }
};

// --- Tests ---

// Normal operation: Writes a <TestCase ...> start element with name (trimmed) & tags,
// writes source info, then closes the opening tag (observable via '>' in output).
TEST_F(XmlReporterTest_837, TestCaseStarting_WritesStartElementAndAttributes_837) {
    cfg = std::make_unique<MockConfig_837>();
    EXPECT_CALL(*cfg, showDurations())
        .WillOnce(Return(ShowDurations::DefaultForReporter));

    auto reporter = makeReporter();

    // Name includes leading/trailing spaces to verify trimming behavior is observable
    const std::string rawName = "   example case   ";
    const std::string trimmedName = "example case";
    const std::string tags = "[fast][math]";

    auto info = makeTestInfo(rawName, tags, "sample_file.cpp", 42);

    reporter->testCaseStarting(info);

    const std::string xml = out.str();

    // Observable assertions on the output text:
    //  - has <TestCase start
    //  - has name attribute with *trimmed* value
    //  - has tags attribute reflecting testInfo.tagsAsString()
    //  - the opening tag has been closed (ensureTagClosed)
    EXPECT_THAT(xml, ::testing::HasSubstr("<TestCase"));
    EXPECT_THAT(xml, ::testing::HasSubstr("name=\""+ trimmedName + "\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("tags=\"" + tags + "\""));
    // We only assert that at least one '>' appears after the start of the element,
    // which is the observable effect of ensureTagClosed().
    auto posStart = xml.find("<TestCase");
    ASSERT_NE(posStart, std::string::npos);
    auto posClose = xml.find('>', posStart);
    EXPECT_NE(posClose, std::string::npos);
}

// Boundary condition: No tags provided — still must emit a tags attribute (value may be empty)
// and a valid start element with a closed opening tag.
TEST_F(XmlReporterTest_837, TestCaseStarting_EmitsTagsAttributeWhenEmpty_837) {
    cfg = std::make_unique<MockConfig_837>();
    EXPECT_CALL(*cfg, showDurations())
        .WillOnce(Return(ShowDurations::DefaultForReporter));

    auto reporter = makeReporter();

    const std::string name = "BoundaryCase";
    const std::string tags; // empty
    auto info = makeTestInfo(name, tags, "no_tags.cpp", 7);

    reporter->testCaseStarting(info);

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<TestCase"));
    EXPECT_THAT(xml, ::testing::HasSubstr("name=\"BoundaryCase\""));
    // We don't assert the exact empty formatting produced by tagsAsString(),
    // but we do require that a tags attribute exists in the output.
    EXPECT_THAT(xml, ::testing::HasSubstr("tags=\""));
    auto posStart = xml.find("<TestCase");
    ASSERT_NE(posStart, std::string::npos);
    auto posClose = xml.find('>', posStart);
    EXPECT_NE(posClose, std::string::npos);
}

// Observable effect of writeSourceInfo: filename should appear in the output
// somewhere as part of the source info written right after the attributes.
TEST_F(XmlReporterTest_837, TestCaseStarting_WritesSourceFilename_837) {
    cfg = std::make_unique<MockConfig_837>();
    EXPECT_CALL(*cfg, showDurations())
        .WillOnce(Return(ShowDurations::DefaultForReporter));

    auto reporter = makeReporter();

    auto info = makeTestInfo("SourceInfoCheck", "[tag]", "very_specific_file_name.cpp", 12345);

    reporter->testCaseStarting(info);

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("very_specific_file_name.cpp"));
    // We do not assert line formatting, as this is reporter-specific formatting detail.
}

// Exceptional/option-path case: When durations are ALWAYS shown, the timer is started,
// which is internal; we only verify that observable output is still a valid opening element.
TEST_F(XmlReporterTest_837, TestCaseStarting_ShowDurationsAlways_ProducesValidStart_837) {
    cfg = std::make_unique<MockConfig_837>();
    EXPECT_CALL(*cfg, showDurations())
        .WillOnce(Return(ShowDurations::Always));

    auto reporter = makeReporter();

    auto info = makeTestInfo("TimingCase", "[timed]", "timed.cpp", 1);

    reporter->testCaseStarting(info);

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<TestCase"));
    EXPECT_THAT(xml, ::testing::HasSubstr("name=\"TimingCase\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("tags=\"[timed]\""));
    auto posStart = xml.find("<TestCase");
    ASSERT_NE(posStart, std::string::npos);
    auto posClose = xml.find('>', posStart);
    EXPECT_NE(posClose, std::string::npos);
}
