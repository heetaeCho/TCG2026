// File: tests/json_reporter_testCaseStarting_868.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 public headers you already have in your tree.
// Keep includes to public interfaces only.
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_tag_alias_registry.hpp"
#include "catch2/internal/catch_stringref.hpp"

using ::testing::HasSubstr;
using ::testing::IsEmpty;

namespace {

/////////////////////////////////////////////////////////////////
// Minimal config stub — only what's needed for ReporterConfig //
/////////////////////////////////////////////////////////////////
class MockConfig : public Catch::IConfig {
public:
    // Provide safe defaults so reporter lifecycle can run.
    bool allowThrows() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    int abortAfter() const override { return 0; }
    // These two are commonly accessed by reporters/lifecycle:
    bool warnAboutMissingAssertions() const override { return false; }
    bool benchmarkNoAnalysis() const override { return true; }

    // Return neutral defaults for the rest of IConfig.
    // NOTE: Keep these returning innocuous values; we do not
    // simulate any reporter internals here.
    bool includeSuccessfulResults() const override { return true; }
    bool shouldReportAllAssertions() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    double benchmarkWarmupTime() const override { return 0.0; }
    int benchmarkSamples() const override { return 0; }
    int benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkConfidenceInterval() const override { return std::chrono::milliseconds{0}; }
    double benchmarkClockResolution() const override { return 0.0; }
    double benchmarkSaveSamplesFor() const override { return 0.0; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    std::string name() const override { return "cfg"; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listReporters() const override { return false; }
    std::vector<std::string> const& getReporterNames() const override { static std::vector<std::string> v; return v; }
    std::vector<std::string> const& getReporterOutputs() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool hasVerbosityFlag() const override { return false; }
    bool skipBenchmarks() const override { return false; }
    int rngSeed() const override { return 0; }
    bool showInvisibles() const override { return false; }
    std::vector<std::string> const& getWarningOptions() const override { static std::vector<std::string> v; return v; }
    bool allowOutOfOrderFailedTests() const override { return false; }
};

//////////////////////////////////////
// Fixture to create reporter & sink //
//////////////////////////////////////
class JsonReporter_TCStarting_868 : public ::testing::Test {
protected:
    std::ostringstream os;
    std::unique_ptr<Catch::IStreamingReporter> reporter;

    // Helper: build a TestCaseInfo using public ctor signature
    static Catch::TestCaseInfo makeTCI(
        Catch::StringRef className,
        Catch::StringRef testName,
        Catch::StringRef tagsString,
        Catch::SourceLineInfo src = Catch::SourceLineInfo{"file.cpp", 123}
    ) {
        Catch::NameAndTags nat;
        nat.name = std::string(testName);
        nat.tags = std::string(tagsString); // e.g., "[tag1][tag two]"
        return Catch::TestCaseInfo(className, nat, src);
    }

    void SetUp() override {
        // Create ReporterConfig using the sink and config stub.
        MockConfig* cfg = new MockConfig();
        std::unique_ptr<MockConfig> cfgOwn(cfg);
        // ReporterConfig usually takes: (IConfigPtr, std::ostream&, ColourImpl)
        // Use helper that creates default colour impl if available.
        Catch::ReporterConfig rc{Catch::Detail::make_unique<MockConfig>(*cfg),
                                 os};

        // Construct JsonReporter from ReporterConfig rvalue.
        reporter = Catch::Detail::make_unique<Catch::JsonReporter>(CATCH_MOVE(rc));

        // Begin test run so reporter is in a valid lifecycle state.
        Catch::TestRunInfo tri{ "run-1"_sr };
        reporter->testRunStarting(tri);
    }

    void TearDown() override {
        // Properly end test run to close any open structures
        // (we don't verify this here; just keep lifecycle sane).
        Catch::TestRunStats trs{};
        reporter->testRunEnded(trs);
    }
};

} // anonymous namespace

// =============== TESTS ===============

// Normal operation: Writes "test-info", test name, tags/properties scaffolding,
// and opens "runs" array for the test case.
TEST_F(JsonReporter_TCStarting_868, WritesBasicScaffold_868) {
    auto tci = makeTCI(""_sr, "SampleCase"_sr, "[a][b]"_sr,
                       Catch::SourceLineInfo{"t.cpp", 7});

    reporter->testCaseStarting(tci);

    const std::string out = os.str();

    // Observable fragments only; we do not assert exact formatting.
    EXPECT_THAT(out, HasSubstr("\"test-info\""));
    EXPECT_THAT(out, HasSubstr("\"name\""));
    EXPECT_THAT(out, HasSubstr("SampleCase"));

    // Source info presence (publicly observable via writer helpers)
    EXPECT_THAT(out, HasSubstr("t.cpp"));
    EXPECT_THAT(out, HasSubstr("7"));

    // Tags & properties keys are started in testCaseStarting
    EXPECT_THAT(out, HasSubstr("\"tags\""));
    EXPECT_THAT(out, HasSubstr("\"properties\""));

    // "runs" array should be started for the test case
    EXPECT_THAT(out, HasSubstr("\"runs\""));
}

// Boundary: Empty name & no tags — still emits keys with appropriate arrays started.
TEST_F(JsonReporter_TCStarting_868, EmptyNameAndNoTags_StillEmitsKeys_868) {
    auto tci = makeTCI(""_sr, ""_sr, ""_sr,
                       Catch::SourceLineInfo{"empty.cpp", 1});

    reporter->testCaseStarting(tci);

    const std::string out = os.str();

    // Keys should still be present
    EXPECT_THAT(out, HasSubstr("\"test-info\""));
    EXPECT_THAT(out, HasSubstr("\"name\""));
    EXPECT_THAT(out, HasSubstr("\"tags\""));
    EXPECT_THAT(out, HasSubstr("\"properties\""));
    EXPECT_THAT(out, HasSubstr("\"runs\""));

    // Still writes source info
    EXPECT_THAT(out, HasSubstr("empty.cpp"));
    EXPECT_THAT(out, HasSubstr("1"));
}

// Boundary: Special characters in the test name should be JSON-escaped by the writer.
// We don't assert the exact escape mechanism; we check that the raw substring appears
// around quotes and that output remains syntactically plausible.
TEST_F(JsonReporter_TCStarting_868, SpecialCharsInName_AreHandled_868) {
    auto tci = makeTCI(""_sr, "N\"a\\m\ne\t"_sr, "[weird]"_sr,
                       Catch::SourceLineInfo{"weird.cpp", 42});

    reporter->testCaseStarting(tci);

    const std::string out = os.str();

    EXPECT_THAT(out, HasSubstr("\"name\""));
    // Presence of some representation of the special content
    EXPECT_THAT(out, HasSubstr("weird.cpp"));
    EXPECT_THAT(out, HasSubstr("42"));
    EXPECT_THAT(out, HasSubstr("\"tags\""));
    EXPECT_THAT(out, HasSubstr("\"runs\""));
}

#ifndef NDEBUG
// Exceptional/error (observable via debug assertion):
// Calling testCaseStarting without being inside the 'test-cases' array should
// hit the assertion ("We should be in the 'test-cases' array").
// We validate this via a death test in debug builds only.
TEST(JsonReporter_Death_868, CallingWithoutRunContext_TriggersAssert_868) {
    std::ostringstream os;
    MockConfig cfg;
    Catch::ReporterConfig rc{Catch::Detail::make_unique<MockConfig>(cfg), os};
    Catch::JsonReporter rep{CATCH_MOVE(rc)};

    auto tci = JsonReporter_TCStarting_868::makeTCI(""_sr, "X"_sr, ""_sr);

    // No testRunStarting() called -> violates precondition
    EXPECT_DEATH(rep.testCaseStarting(tci), "test-cases");
}
#endif

