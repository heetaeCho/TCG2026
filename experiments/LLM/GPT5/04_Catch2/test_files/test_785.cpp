// File: tests/TeamCityReporter_testCaseEnded_785.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <map>

#include <catch2/reporters/catch_reporter_teamcity.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_totals.hpp>

// ---------- Test-only helpers (external to the class under test) ----------

// A stringbuf that lets us detect flush() (via pubsync/sync) without relying
// on any TeamCityReporter internals.
class FlushTrackingStringBuf : public std::stringbuf {
public:
    int sync() override {
        ++flushCount;
        return std::stringbuf::sync();
    }
    int flushCount = 0;
};

// A minimal IStream wrapper that returns a reference to an ostream we control.
class OStreamWrapper : public Catch::IStream {
public:
    explicit OStreamWrapper(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// A *very* small testing facade to construct ReporterConfig with a custom stream.
// This avoids re-implementing logic and sticks to the public constructor surface.
static Catch::ReporterConfig makeReporterConfigFor(
    std::unique_ptr<Catch::IStream>&& stream,
    const Catch::IConfig* fullCfg = nullptr,
    Catch::ColourMode colour = Catch::ColourMode::None,
    std::map<std::string, std::string> custom = {}
) {
    // ReporterConfig’s ctor is part of Catch2’s public surface for reporters.
    // Passing `fullCfg` as nullptr is okay for these tests because we only
    // exercise output formatting in testCaseEnded (no config-dependent paths).
    return Catch::ReporterConfig(fullCfg, std::move(stream), colour, std::move(custom));
}

// Build a trivial TestCaseInfo with a simple name (no escaping needed).
static Catch::TestCaseInfo makeTCI(const std::string& name) {
    Catch::NameAndTags nt;
    nt.name = name;
    nt.tags = "";
    // className can be empty
    return Catch::TestCaseInfo(
        Catch::StringRef{},             // className
        nt,                             // NameAndTags
        Catch::SourceLineInfo{__FILE__, __LINE__}
    );
}

// Build TestCaseStats with provided stdOut/stdErr; totals/aborting are not used
// by TeamCityReporter::testCaseEnded’s observable output.
static Catch::TestCaseStats makeTCS(
    const Catch::TestCaseInfo& tci,
    std::string stdOut,
    std::string stdErr,
    bool aborting = false
) {
    Catch::Totals totals; // default totals are fine for these tests
    return Catch::TestCaseStats(tci, totals, std::move(stdOut), std::move(stdErr), aborting);
}

// ------------------------------- Fixture -----------------------------------

class TeamCityReporter_testCaseEnded_785 : public ::testing::Test {
protected:
    // Builds a TeamCityReporter that writes into our flush-tracking buffer.
    std::unique_ptr<Catch::TeamCityReporter> makeReporter() {
        // Route reporter output into an ostream backed by our tracking buffer.
        m_os = std::make_unique<std::ostream>(&m_buf);
        auto wrapper = std::make_unique<OStreamWrapper>(*m_os);
        auto cfg = makeReporterConfigFor(std::move(wrapper));

        return std::make_unique<Catch::TeamCityReporter>(std::move(cfg));
    }

    std::string output() const { return m_buf.str(); }
    int flushCount() const { return m_buf.flushCount; }

    // We keep these alive for the life of each test
    std::unique_ptr<std::ostream> m_os;
    mutable FlushTrackingStringBuf m_buf;
};

// ------------------------------- Tests --------------------------------------

// Normal path: both stdOut and stdErr present -> both lines appear (in order)
// and testFinished appears with a numeric duration.
TEST_F(TeamCityReporter_testCaseEnded_785, WritesStdOutStdErrAndFinished_InOrder_785) {
    auto reporter = makeReporter();

    auto tci  = makeTCI("SimpleTest");
    auto tcs  = makeTCS(tci, "hello out", "oops err");

    reporter->testCaseEnded(tcs);

    const std::string out = output();

    // Use regexes tolerant to TeamCity escaping — only assert presence of the
    // original substrings within quoted fields and required tokens.
    using ::testing::MatchesRegex;

    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testStdOut name='[^']*SimpleTest[^']*' out='[^']*hello out[^']*'\\].*"));
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testStdErr name='[^']*SimpleTest[^']*' out='[^']*oops err[^']*'\\].*"));
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testFinished name='[^']*SimpleTest[^']*' duration='[0-9]+'\\].*"));

    // Ordering: StdOut precedes StdErr, which precedes testFinished
    const auto pOut  = out.find("##teamcity[testStdOut");
    const auto pErr  = out.find("##teamcity[testStdErr");
    const auto pFin  = out.find("##teamcity[testFinished");
    ASSERT_NE(pOut, std::string::npos);
    ASSERT_NE(pErr, std::string::npos);
    ASSERT_NE(pFin, std::string::npos);
    EXPECT_LT(pOut, pErr);
    EXPECT_LT(pErr, pFin);
}

// Boundary: only stdOut present -> only testStdOut + testFinished (no testStdErr).
TEST_F(TeamCityReporter_testCaseEnded_785, WritesOnlyStdOutWhenStdErrEmpty_785) {
    auto reporter = makeReporter();

    auto tci = makeTCI("SoloOut");
    auto tcs = makeTCS(tci, "stdout only", /*stdErr*/ "");

    reporter->testCaseEnded(tcs);

    const std::string out = output();
    using ::testing::MatchesRegex;

    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testStdOut name='[^']*SoloOut[^']*' out='[^']*stdout only[^']*'\\].*"));
    EXPECT_EQ(out.find("##teamcity[testStdErr"), std::string::npos)
        << "StdErr block must not be printed when stdErr is empty";
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testFinished name='[^']*SoloOut[^']*' duration='[0-9]+'\\].*"));
}

// Boundary: only stdErr present -> only testStdErr + testFinished (no testStdOut).
TEST_F(TeamCityReporter_testCaseEnded_785, WritesOnlyStdErrWhenStdOutEmpty_785) {
    auto reporter = makeReporter();

    auto tci = makeTCI("SoloErr");
    auto tcs = makeTCS(tci, /*stdOut*/ "", /*stdErr*/ "stderr only");

    reporter->testCaseEnded(tcs);

    const std::string out = output();
    using ::testing::MatchesRegex;

    EXPECT_EQ(out.find("##teamcity[testStdOut"), std::string::npos)
        << "StdOut block must not be printed when stdOut is empty";
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testStdErr name='[^']*SoloErr[^']*' out='[^']*stderr only[^']*'\\].*"));
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testFinished name='[^']*SoloErr[^']*' duration='[0-9]+'\\].*"));
}

// Boundary: both stdOut and stdErr empty -> only testFinished line appears.
TEST_F(TeamCityReporter_testCaseEnded_785, WritesOnlyFinishedWhenStdOutAndStdErrEmpty_785) {
    auto reporter = makeReporter();

    auto tci = makeTCI("NoIO");
    auto tcs = makeTCS(tci, "", "");

    reporter->testCaseEnded(tcs);

    const std::string out = output();
    EXPECT_EQ(out.find("##teamcity[testStdOut"), std::string::npos);
    EXPECT_EQ(out.find("##teamcity[testStdErr"), std::string::npos);
    EXPECT_NE(out.find("##teamcity[testFinished name='"), std::string::npos);
    // Ensure a duration number is present, but do not assert its value.
    using ::testing::MatchesRegex;
    EXPECT_THAT(out, MatchesRegex("(?s).*##teamcity\\[testFinished name='[^']*NoIO[^']*' duration='[0-9]+'\\].*"));
}

// Exceptional/side-effect: stream is flushed at the end (observable via streambuf).
TEST_F(TeamCityReporter_testCaseEnded_785, FlushesStreamAtEnd_785) {
    auto reporter = makeReporter();

    auto tci = makeTCI("FlushCheck");
    auto tcs = makeTCS(tci, "o", "e");

    const int before = flushCount();
    reporter->testCaseEnded(tcs);
    const int after  = flushCount();

    EXPECT_GT(after, before) << "Expected TeamCityReporter to flush the stream at the end";
}
