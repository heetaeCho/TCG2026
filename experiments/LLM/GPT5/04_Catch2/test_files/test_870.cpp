// File: tests/json_reporter_sectionStarting_870_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 headers (paths may differ slightly in your repo)
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/reporters/catch_reporter_json.cpp" // if needed for inline / link
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_test_macros.hpp"

// ---- Minimal external stubs/mocks to construct JsonReporter (BLACK-BOX compliant) ----
// Only mock external collaborators. Do NOT peek into JsonReporter internals.

#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_common.hpp" // ReporterConfig, ReporterPreferences, etc.
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::Detail::unique_ptr<Catch::IStream>, createStream, (Catch::StringRef), (const, override));
    MOCK_METHOD(std::string, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations::OrNot, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(bool, noThrow, (), (const, override));
    MOCK_METHOD(bool, (benchmarkNoAnalysis), (), (const, override));
    MOCK_METHOD(int, (benchmarkSamples), (), (const, override));
    MOCK_METHOD(double, (benchmarkConfidenceInterval), (), (const, override));
    MOCK_METHOD(unsigned int, (benchmarkResamples), (), (const, override));
    MOCK_METHOD(bool, (benchmarkWarmupTime), (), (const, override)); // if signature differs, adjust/remove
    MOCK_METHOD(bool, (skipBenchmarks), (), (const, override));
    MOCK_METHOD(bool, (zeroTestsCountAsSuccess), (), (const, override));
    MOCK_METHOD(Catch::IConfig::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, (warnAboutUnmatchedTestSpecs), (), (const, override));
    MOCK_METHOD(bool, (benchmarkEnabled), (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(Catch::Option<std::size_t> const&, rngSeed, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getProcessesOrTags, (), (const, override));
    MOCK_METHOD(Catch::Detail::unique_ptr<Catch::IStream> const&, reporterOutput, (), (const, override));
    MOCK_METHOD(bool, listReporters, (), (const, override));
    MOCK_METHOD(bool, listListeners, (), (const, override));
    MOCK_METHOD(bool, listTests, (), (const, override));
    MOCK_METHOD(bool, listTags, (), (const, override));
    MOCK_METHOD(bool, listTestNamesOnly, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getListenerSpecs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getWarningSpecs, (), (const, override));
    MOCK_METHOD(bool, allowZeroTests, (), (const, override));
    MOCK_METHOD(bool, hasOptions, (), (const, override));
    MOCK_METHOD(bool, runningUnderCI, (), (const, override));
    MOCK_METHOD(bool, shouldEnforceNoTests, (), (const, override));
};

// Helper to build a ReporterConfig that writes to `os`.
static Catch::ReporterConfig makeReporterConfig(Catch::IConfig& cfg, std::ostream& os) {
    Catch::ReporterPreferences prefs;
    // Only safe, public fields we are allowed to touch:
    prefs.shouldRedirectStdOut = false;
    prefs.verbosity = Catch::IConfig::Verbosity::Normal;

    // ReporterConfig takes (IConfig&, std::ostream&, ReporterPreferences)
    return Catch::ReporterConfig{ cfg, os, prefs };
}

// Light helper to create a SectionInfo
static Catch::SectionInfo makeSectionInfo(const char* file, std::size_t line, std::string name) {
    Catch::SourceLineInfo sli{ file, static_cast<std::size_t>(line) };
    return Catch::SectionInfo{ sli, std::move(name), nullptr };
}

} // namespace

// -------------------- Fixture --------------------
class JsonReporterSectionStartingTest_870 : public ::testing::Test {
protected:
    std::stringstream out;
    NiceMock<MockConfig> mockCfg;

    void SetUp() override {
        // Reasonable defaults for calls reporter might make during construction or usage
        ON_CALL(mockCfg.allowThrows()).WillByDefault(Return(true));
        ON_CALL(mockCfg.includeSuccessfulResults()).WillByDefault(Return(true));
        ON_CALL(mockCfg.shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(mockCfg.abortAfter()).WillByDefault(Return(0));
        ON_CALL(mockCfg.warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(mockCfg.showDurations()).WillByDefault(Return(Catch::ShowDurations::DefaultForReporter));
        ON_CALL(mockCfg.minDuration()).WillByDefault(Return(0.0));
        ON_CALL(mockCfg.noThrow()).WillByDefault(Return(false));
        ON_CALL(mockCfg.verbosity()).WillByDefault(Return(Catch::IConfig::Verbosity::Normal));
        // Many other methods are not touched by the specific path we test.
    }

    Catch::JsonReporter makeReporter() {
        auto rc = makeReporterConfig(mockCfg, out);
        return Catch::JsonReporter{ std::move(rc) };
    }
};

// -------------------- Tests --------------------

// 1) Error/exceptional case: Calling sectionStarting while NOT inside an array
//    should assert (debug builds). This verifies the explicit contract in the code.
TEST_F(JsonReporterSectionStartingTest_870, SectionStartingAssertsOutsideArray_870) {
    auto reporter = makeReporter();
    auto sec = makeSectionInfo("a.cpp", 123, "S1");

#ifndef NDEBUG
    ASSERT_DEATH_IF_SUPPORTED(
        reporter.sectionStarting(sec),
        "Section should always start inside an object"
    );
#else
    // In release builds, assert is compiled out; we just call it to ensure no UB/crash.
    // We don't check output here because behavior without preconditions is unspecified.
    reporter.sectionStarting(sec);
#endif
}

// 2) Boundary: empty section name. Still must satisfy precondition (inside array) to be meaningful.
//    We drive a plausible public sequence to reach a valid state, then call sectionStarting.
//    We only assert on observable fragments that MUST be present by interface (keys/structure),
//    not on exact formatting or private details.
TEST_F(JsonReporterSectionStartingTest_870, SectionStartingWritesKindAndName_EmptyName_870) {
    auto reporter = makeReporter();

    // Drive the reporter into a plausible state using public API:
    // Start a run and a test case – common path that should initialize JSON structures.
    // We construct lightweight public inputs only (no private peeking).
    Catch::TestRunInfo runInfo{ "run" };
    reporter.testRunStarting(runInfo);

    // Minimal TestCaseInfo: Catch2 provides public constructor; if your local signature differs,
    // adjust the arguments accordingly (public-only).
    Catch::NameAndTags nat{ "", {} };
    Catch::TestCaseInfo tcInfo{
        Catch::NameAndTags{ "T", {} },
        Catch::SourceLineInfo{ "t.cpp", 10 },
        "",  // className
        0,   // line
        Catch::TestCaseProperties::None
    };
    reporter.testCaseStarting(tcInfo);

    auto emptySec = makeSectionInfo("s.cpp", 42, "");

    // Now the reporter should be ready to accept a section.
    reporter.sectionStarting(emptySec);

    // Observable behavior: it must write a section object containing "kind":"section"
    // and the "name" field (even if empty), and start an array "path".
    const std::string outStr = out.str();
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"kind\""));
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"section\""));
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"name\""));
    // We don't assert exact placement/commas/indentation, only key presence.
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"path\""));
}

// 3) Normal operation: non-empty name should be reflected in output.
//    Again, we only validate observable fragments, not internal state.
TEST_F(JsonReporterSectionStartingTest_870, SectionStartingWritesProvidedName_870) {
    auto reporter = makeReporter();

    Catch::TestRunInfo runInfo{ "run" };
    reporter.testRunStarting(runInfo);

    Catch::TestCaseInfo tcInfo{
        Catch::NameAndTags{ "T", {} },
        Catch::SourceLineInfo{ "t.cpp", 10 },
        "",  // className
        0,   // line
        Catch::TestCaseProperties::None
    };
    reporter.testCaseStarting(tcInfo);

    auto sec = makeSectionInfo("file.cpp", 77, "InitSection");
    reporter.sectionStarting(sec);

    const std::string outStr = out.str();
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"kind\""));
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"section\""));
    EXPECT_THAT(outStr, ::testing::HasSubstr("\"name\""));
    EXPECT_THAT(outStr, ::testing::HasSubstr("InitSection"));

    // Source info is written through public helper; we do not assume formatting,
    // but it's reasonable to see the file name or line number show up.
    EXPECT_THAT(outStr, ::testing::HasSubstr("file.cpp"));
    // Line number presence is optional depending on formatting; include a soft check:
    // (Do not fail the test if formatting differs.)
    // if (outStr.find("77") == std::string::npos) { SUCCEED(); }
}

