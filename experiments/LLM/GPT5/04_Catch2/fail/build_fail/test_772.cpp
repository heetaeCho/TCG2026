// File: tests/console_reporter_test_case_ended_772.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Catch2 headers — adjust include paths to your tree if needed.
#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>   // ReporterConfig
#include <catch2/catch_test_case_info.hpp>               // TestCaseInfo, NameAndTags
#include <catch2/catch_totals.hpp>                       // Totals
#include <catch2/catch_test_case_info.hpp>               // NameAndTags
#include <catch2/internal/catch_stringref.hpp>           // StringRef
#include <catch2/internal/catch_source_line_info.hpp>    // SourceLineInfo

using namespace Catch;

namespace {

// Minimal helpers to build inputs strictly via public constructors.
// If your repository uses slightly different constructor signatures,
// adjust the small helper below (kept tiny on purpose).

TestCaseInfo makeDummyTestCaseInfo(const std::string& name = "DummyCase") {
    NameAndTags nat{ StringRef{name}, StringRef{} };
    SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };
    // TestCaseInfo’s public constructor in Catch2 v3 takes (NameAndTags, SourceLineInfo, StringRef className, bool isHidden, bool throws, bool okToFail, int expectedToFail).
    return TestCaseInfo(
        nat,
        sli,
        StringRef{},  /* className */
        false,        /* isHidden */
        false,        /* throws */
        false,        /* okToFail */
        0             /* expectedToFail */
    );
}

TestCaseStats makeStats(const TestCaseInfo& tci,
                        const Totals& totals,
                        std::string out,
                        std::string err,
                        bool aborting) {
    // Uses the public ctor from the prompt:
    // TestCaseStats( const TestCaseInfo&, const Totals&, std::string&&, std::string&&, bool )
    return TestCaseStats(tci, totals, std::move(out), std::move(err), aborting);
}

// Minimal ReporterConfig builder using an ostringstream so we can observe output.
ReporterConfig makeConfig(std::ostream& os) {
    // Defaults: full config uses colour mode / warnings / verbosity; the helper
    // takes stream, config, and a “full config” view for reporters.
    // For tests, we can use default-constructed “ReporterPreferences/ConfigData”
    // through the helper utilities.
    // catch_reporter_helpers.hpp exposes ReporterConfig that takes:
    //   (std::ostream& _stream, IConfig const* _fullConfig)
    // We can pass nullptr for fullConfig when not needed by the reporter path exercised.
    return ReporterConfig(os, /*fullConfig*/ nullptr);
}

struct ConsoleReporterFixture : ::testing::Test {
    std::ostringstream oss;
    std::unique_ptr<ConsoleReporter> reporter;

    void SetUp() override {
        reporter = std::make_unique<ConsoleReporter>(ReporterConfig{ makeConfig(oss) });
    }
};

} // namespace

// ============ TESTS ============

TEST_F(ConsoleReporterFixture, TestCaseEnded_Normal_772) {
    const auto tci = makeDummyTestCaseInfo("NormalCase");
    const Totals totals; // default totals (0s) are fine for black-box call
    auto stats = makeStats(tci, totals, /*stdout*/"hello", /*stderr*/"", /*aborting*/false);

    // Act + Assert: should be callable without throwing; observable surface is “no crash” and stream remains usable.
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));

    // The reporter should remain usable after ending a case — start another small cycle.
    EXPECT_NO_THROW(reporter->testCaseStarting(tci));
    // A small visible side-effect path: starting a section is safe post-end.
    SectionInfo si{ StringRef{"sec"}, SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)} };
    EXPECT_NO_THROW(reporter->sectionStarting(si));
    // End the section to keep lifecycle tidy.
    SectionStats sstats{ si, Counts{}, /*missing assertions*/ false, /*duration*/ 0.0 };
    EXPECT_NO_THROW(reporter->sectionEnded(sstats));
}

TEST_F(ConsoleReporterFixture, TestCaseEnded_BoundaryEmptyIO_772) {
    const auto tci = makeDummyTestCaseInfo("EmptyIO");
    const Totals totals;
    auto stats = makeStats(tci, totals, /*stdout*/"", /*stderr*/"", /*aborting*/false);

    EXPECT_NO_THROW(reporter->testCaseEnded(stats));

    // Starting another test case after end should still work.
    const auto tci2 = makeDummyTestCaseInfo("NextCase");
    EXPECT_NO_THROW(reporter->testCaseStarting(tci2));
}

TEST_F(ConsoleReporterFixture, TestCaseEnded_AbortingTrue_772) {
    const auto tci = makeDummyTestCaseInfo("AbortingCase");
    const Totals totals;
    auto stats = makeStats(tci, totals, /*stdout*/"partial", /*stderr*/"fail", /*aborting*/true);

    // Even with aborting=true, ConsoleReporter::testCaseEnded should be safe to call.
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));

    // Reporter remains usable afterwards — e.g., it can still accept a new test run start.
    TestRunInfo tri{ StringRef{"run"} };
    EXPECT_NO_THROW(reporter->testRunStarting(tri));
}

TEST_F(ConsoleReporterFixture, TestCaseEnded_IdempotentishMultipleCalls_772) {
    const auto tci = makeDummyTestCaseInfo("MultipleEnds");
    const Totals totals;
    auto stats = makeStats(tci, totals, /*stdout*/"", /*stderr*/"", /*aborting*/false);

    // Calling more than once with valid inputs should not crash (closing internal table twice should be safe).
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

