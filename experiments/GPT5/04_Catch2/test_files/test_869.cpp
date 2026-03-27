// File: tests/JsonReporter_testCaseEnded_869.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <regex>

// Catch2 reporter headers under test
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"

// Interfaces used to drive the reporter through its public API
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"

using ::testing::HasSubstr;
using ::testing::Not;

// Utility: normalize JSON-ish output for substring/regex checks
static std::string normalize(std::string s) {
    // Make matching robust to whitespace/indentation differences
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c){
        return c == '\n' || c == '\r' || c == '\t' || c == ' ';
    }), s.end());
    return s;
}

class JsonReporter_TestCaseEnded_869 : public ::testing::Test {
protected:
    std::ostringstream out;

    // Builds a JsonReporter wired to write into `out`.
    std::unique_ptr<Catch::JsonReporter> makeReporter() {
        // TODO(869): Replace with your project’s ReporterConfig builder.
        // Many codebases do something like:
        //
        // Catch::IConfigPtr cfg = makeConfigForTesting(); // Optional
        // Catch::ReporterConfig rc{ out, cfg };
        //
        // The partial headers only show the type; they don’t show ctor args.
        // If your ReporterConfig requires more, adapt here accordingly.
        Catch::ReporterConfig rc{ out, Catch::IConfigPtr{} };
        return std::make_unique<Catch::JsonReporter>(std::move(rc));
    }

    // Minimal helpers to drive the reporter through a valid lifecycle.
    void startRunAndCase(Catch::JsonReporter& r,
                         const Catch::TestRunInfo& tri,
                         const Catch::TestCaseInfo& tci) {
        r.testRunStarting(tri);
        r.testCaseStarting(tci);
    }

    // Factory shims — plug into your existing test builders
    Catch::TestRunInfo makeRunInfo(const char* name = "run-869") {
        // TODO(869): Construct per your codebase; many define
        // Catch::TestRunInfo{ StringRef(name) }
        return Catch::TestRunInfo{ name };
    }

    Catch::TestCaseInfo makeTestCaseInfo(const char* name = "tc-869") {
        // TODO(869): Construct with what your project expects.
        // E.g., a minimal TestCaseInfo with just a name often works.
        return Catch::TestCaseInfo{ name, {}, {}, {} };
    }

    Catch::Totals makeTotalsAssertions(int passed, int failed, int failedButOk = 0) {
        // TODO(869): Build the Totals with a concrete Counts value.
        // Many codebases have:
        //   Counts c; c.passed = passed; c.failed = failed; c.failedButOk = failedButOk;
        //   Totals t; t.assertions = c; return t;
        Catch::Totals t;
        t.assertions.passed = passed;
        t.assertions.failed = failed;
        t.assertions.failedButOk = failedButOk;
        return t;
    }

    Catch::TestCaseStats makeStats(const Catch::TestCaseInfo& tci,
                                   const Catch::Totals& totals,
                                   std::string outStr = {},
                                   std::string errStr = {},
                                   bool aborting = false) {
        // Public ctor per partial header takes (info, totals, stdOut&&, stdErr&&, aborting)
        return Catch::TestCaseStats{ tci, totals, std::move(outStr), std::move(errStr), aborting };
    }
};

// Normal case: after a typical start->testCaseStarting->testCaseEnded sequence,
// the output should include "totals" and nested "assertions", and close array/object.
TEST_F(JsonReporter_TestCaseEnded_869,
       WritesTotalsAndAssertionsKeys_869) {
    auto reporter = makeReporter();

    const auto runInfo = makeRunInfo("run-869");
    const auto tcInfo  = makeTestCaseInfo("tc-869");
    startRunAndCase(*reporter, runInfo, tcInfo);

    const auto totals  = makeTotalsAssertions(/*passed*/3, /*failed*/1);
    const auto stats   = makeStats(tcInfo, totals);

    // Act
    reporter->testCaseEnded(stats);

    const auto s = normalize(out.str());
    // Structural/observable: presence of keys written by testCaseEnded path.
    EXPECT_THAT(s, HasSubstr("\"totals\""));
    EXPECT_THAT(s, HasSubstr("\"assertions\""));

    // Heuristic structural close: should eventually close an object after the call.
    // Being robust to where in the stream this appears, just ensure '}' exists.
    EXPECT_NE(std::string::npos, out.str().find('}'));
}

// Boundary: zero totals should still emit the same keys (we do NOT assert on numbers,
// just that the structure is present — black-box, output-observable).
TEST_F(JsonReporter_TestCaseEnded_869,
       ZeroTotals_StillEmitsTotalsAndAssertions_869) {
    auto reporter = makeReporter();

    const auto runInfo = makeRunInfo("run-869-zero");
    const auto tcInfo  = makeTestCaseInfo("tc-869-zero");
    startRunAndCase(*reporter, runInfo, tcInfo);

    const auto totals  = makeTotalsAssertions(/*passed*/0, /*failed*/0, /*failedButOk*/0);
    const auto stats   = makeStats(tcInfo, totals);

    // Act
    reporter->testCaseEnded(stats);

    const auto s = normalize(out.str());
    EXPECT_THAT(s, HasSubstr("\"totals\""));
    EXPECT_THAT(s, HasSubstr("\"assertions\""));
}

// Robustness wrt large stdOut/stdErr: the function doesn’t use them directly,
// but they travel through TestCaseStats — we only check that it doesn’t crash
// and output is still structurally valid (i.e., array/object closures exist).
TEST_F(JsonReporter_TestCaseEnded_869,
       LargeStdOutStdErr_DoesNotCorruptStructure_869) {
    auto reporter = makeReporter();

    const auto runInfo = makeRunInfo("run-869-large");
    const auto tcInfo  = makeTestCaseInfo("tc-869-large");
    startRunAndCase(*reporter, runInfo, tcInfo);

    std::string big(50'000, 'x');
    const auto totals = makeTotalsAssertions(/*passed*/1, /*failed*/0);
    const auto stats  = makeStats(tcInfo, totals, big, big, /*aborting*/false);

    // Act
    reporter->testCaseEnded(stats);

    // Observable checks only
    const auto s = normalize(out.str());
    EXPECT_THAT(s, HasSubstr("\"totals\""));
    EXPECT_THAT(s, HasSubstr("\"assertions\""));

    // Should contain both ']' and '}' eventually (endArray + endObject invoked).
    EXPECT_NE(std::string::npos, out.str().find(']'));
    EXPECT_NE(std::string::npos, out.str().find('}'));
}

// Sequencing sanity: call testRunStarting + testCaseStarting, then multiple testCaseEnded
// (simulating parameterized/fragmented cases where your harness calls partials or
// multiple test cases back-to-back). We only assert that each call appends structure
// (without asserting exact formatting).
TEST_F(JsonReporter_TestCaseEnded_869,
       MultipleTestCases_EmitsStructurePerCase_869) {
    auto reporter = makeReporter();

    const auto runInfo = makeRunInfo("run-869-multi");
    reporter->testRunStarting(runInfo);

    // Case 1
    const auto tcInfo1 = makeTestCaseInfo("tc-869-1");
    reporter->testCaseStarting(tcInfo1);
    const auto stats1 = makeStats(tcInfo1, makeTotalsAssertions(2, 0));
    reporter->testCaseEnded(stats1);

    // Case 2
    const auto tcInfo2 = makeTestCaseInfo("tc-869-2");
    reporter->testCaseStarting(tcInfo2);
    const auto stats2 = makeStats(tcInfo2, makeTotalsAssertions(0, 1));
    reporter->testCaseEnded(stats2);

    const auto s = normalize(out.str());
    // Expect at least two occurrences of "totals" / "assertions"
    // We won’t rely on exact counts — just verify repetition is visible.
    auto firstTotals = s.find("\"totals\"");
    ASSERT_NE(std::string::npos, firstTotals);
    auto secondTotals = s.find("\"totals\"", firstTotals + 1);
    EXPECT_NE(std::string::npos, secondTotals);

    auto firstAsr = s.find("\"assertions\"");
    ASSERT_NE(std::string::npos, firstAsr);
    auto secondAsr = s.find("\"assertions\"", firstAsr + 1);
    EXPECT_NE(std::string::npos, secondAsr);
}
