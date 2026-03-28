// File: tests/json_reporter_assertionEnded_871.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 headers (use the real interfaces only)
#include <catch2/reporters/catch_reporter_json.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>
#include <catch2/catch_user_config.hpp>
#include <catch2/catch_version.hpp>
#include <catch2/catch_tostring.hpp>
#include <catch2/catch_test_macros.hpp> // for ResultWas etc., if needed
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_totals.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

using ::testing::HasSubstr;

// Minimal mock for IConfig so we can construct ReporterConfig.
// Only the methods needed by ReporterConfig/JsonReporter at runtime should be
// specified; the rest can return benign defaults.
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(std::ostream&, stream, (), (const, override));
    MOCK_METHOD(std::string, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warningsAsErrors, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations::OrNot, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(bool, noThrow, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, colourMode, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(bool, listReporters, (), (const, override));
    MOCK_METHOD(bool, listTests, (), (const, override));
    MOCK_METHOD(bool, listTags, (), (const, override));
    MOCK_METHOD(bool, listListeners, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, testsOrTags, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutNoTests, (), (const, override));
    MOCK_METHOD(bool, allowZeroTests, (), (const, override));
    MOCK_METHOD(int, shardCount, (), (const, override));
    MOCK_METHOD(int, shardIndex, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, hasExpandedTestSelection, (), (const, override));
};

struct JsonReporterAssertionEndedTest : public ::testing::Test {
    std::ostringstream oss;
    testing::NiceMock<MockConfig> cfg;

    // Helper: construct a reporter bound to our stringstream
    std::unique_ptr<Catch::JsonReporter> makeReporter() {
        // Configure mock with safe defaults used by ReporterConfig
        ON_CALL(cfg, stream()).WillByDefault(::testing::ReturnRef(oss));
        ON_CALL(cfg, name()).WillByDefault(::testing::Return(std::string("run")));
        ON_CALL(cfg, colourMode()).WillByDefault(::testing::Return(Catch::ColourMode::None));
        ON_CALL(cfg, showDurations()).WillByDefault(::testing::Return(Catch::ShowDurations::DefaultForReporter));
        ON_CALL(cfg, minDuration()).WillByDefault(::testing::Return(0.0));
        ON_CALL(cfg, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(cfg, includeSuccessfulResults()).WillByDefault(::testing::Return(true));
        ON_CALL(cfg, verbosity()).WillByDefault(::testing::Return(Catch::Verbosity::Normal));
        ON_CALL(cfg, allowZeroTests()).WillByDefault(::testing::Return(true));
        static std::vector<std::string> empty;
        ON_CALL(cfg, testsOrTags()).WillByDefault(::testing::ReturnRef(empty));

        Catch::ReporterConfig rc{ cfg };
        return std::make_unique<Catch::JsonReporter>(CATCH_MOVE(rc));
    }

    // Drive the reporter through a minimal public lifecycle so that we are
    // "inside" appropriate JSON structures before calling assertionEnded.
    void startRunCaseSection(Catch::JsonReporter& rep) {
        Catch::TestRunInfo runInfo{ Catch::StringRef("run") };
        rep.testRunStarting(runInfo);

        Catch::TestCaseInfo tcInfo{
            "DummyTestCase",
            Catch::SourceLineInfo{ "dummy_test.cpp", 1 },
            {}, {}, {}, {}
        };
        rep.testCaseStarting(tcInfo);

        Catch::SectionInfo sectionInfo{
            Catch::SourceLineInfo{ "dummy_section.cpp", 10 },
            "root",
            ""
        };
        rep.sectionStarting(sectionInfo);
    }

    void endSectionCaseRun(Catch::JsonReporter& rep) {
        Catch::SectionStats secStats{
            { Catch::SourceLineInfo{ "dummy_section.cpp", 10 }, "root", "" },
            Catch::Counts{}, 0.0, false
        };
        rep.sectionEnded(secStats);

        Catch::TestCaseStats tcStats{
            { "DummyTestCase",
              Catch::SourceLineInfo{ "dummy_test.cpp", 1 }, {}, {}, {}, {} },
            Catch::Totals{},
            "", "", {}
        };
        rep.testCaseEnded(tcStats);

        Catch::TestRunStats runStats{
            { Catch::StringRef("run") },
            Catch::Totals{},
            false
        };
        rep.testRunEnded(runStats);
    }

    // Make an AssertionResult with desired result type and source
    Catch::AssertionResult makeResult(Catch::ResultWas::OfType type,
                                      const char* file, std::size_t line,
                                      const char* macro = "REQUIRE",
                                      const char* expr = "1 == 1") {
        Catch::AssertionInfo info{
            Catch::StringRef(macro),
            Catch::SourceLineInfo{ file, static_cast<std::size_t>(line) },
            Catch::StringRef(expr),
            Catch::ResultDisposition::Normal
        };
        Catch::AssertionResultData data{ type };
        return Catch::AssertionResult(info, CATCH_MOVE(data));
    }
};

// TEST 1: Success case writes kind and status=true
TEST_F(JsonReporterAssertionEndedTest, AssertionSuccess_WritesKindAndTrueStatus_871) {
    auto rep = makeReporter();
    startRunCaseSection(*rep);

    auto result = makeResult(Catch::ResultWas::Ok, "my_file.cpp", 123);
    Catch::AssertionStats stats{ result, {}, Catch::Totals{} };

    rep->assertionEnded(stats);
    endSectionCaseRun(*rep);

    const std::string out = oss.str();

    // Observable behavior from assertionEnded:
    // - emits an object with "kind": "assertion"
    // - emits "status": true for OK results
    // - includes source info (we check our file name and line are present)
    EXPECT_THAT(out, HasSubstr("\"kind\""));
    EXPECT_THAT(out, HasSubstr("assertion"));
    EXPECT_THAT(out, HasSubstr("\"status\""));
    EXPECT_THAT(out, HasSubstr("true"));
    EXPECT_THAT(out, HasSubstr("my_file.cpp"));
    EXPECT_THAT(out, HasSubstr("123"));
}

// TEST 2: Failure case writes kind and status=false
TEST_F(JsonReporterAssertionEndedTest, AssertionFailure_WritesKindAndFalseStatus_871) {
    auto rep = makeReporter();
    startRunCaseSection(*rep);

    auto result = makeResult(Catch::ResultWas::ExpressionFailed, "fail.cpp", 77, "REQUIRE", "1 == 2");
    Catch::AssertionStats stats{ result, {}, Catch::Totals{} };

    rep->assertionEnded(stats);
    endSectionCaseRun(*rep);

    const std::string out = oss.str();

    EXPECT_THAT(out, HasSubstr("\"kind\""));
    EXPECT_THAT(out, HasSubstr("assertion"));
    EXPECT_THAT(out, HasSubstr("\"status\""));
    EXPECT_THAT(out, HasSubstr("false"));
    EXPECT_THAT(out, HasSubstr("fail.cpp"));
    EXPECT_THAT(out, HasSubstr("77"));
}
