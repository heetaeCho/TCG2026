// File: tests/XmlReporter_testRunEnded_842.cpp

#include <gtest/gtest.h>
#include <regex>
#include <sstream>

// Headers from the codebase under test (paths follow your partials)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"

using namespace Catch;

namespace {

// Small helpers to keep tests readable (no internal logic reimplementation).
TestRunStats makeStats(uint64_t a_pass, uint64_t a_fail, uint64_t a_failOk, uint64_t a_skip,
                       uint64_t c_pass, uint64_t c_fail, uint64_t c_failOk, uint64_t c_skip) {
    Totals totals;
    totals.assertions.passed      = a_pass;
    totals.assertions.failed      = a_fail;
    totals.assertions.failedButOk = a_failOk;
    totals.assertions.skipped     = a_skip;

    totals.testCases.passed       = c_pass;
    totals.testCases.failed       = c_fail;
    totals.testCases.failedButOk  = c_failOk;
    totals.testCases.skipped      = c_skip;

    TestRunInfo info{ "dummy-run"_sr };
    return TestRunStats{ info, totals, false };
}

// Build a reporter with a bound stream.
// Assumes ReporterConfig is constructible with (IConfig*, std::ostream&, ColourImpl*)
// which matches Catch2 v3 public interface.
std::unique_ptr<XmlReporter> makeReporter(std::ostream& os) {
    ReporterConfig cfg{ /*IConfig*/ nullptr, os, /*ColourImpl*/ nullptr };
    return std::unique_ptr<XmlReporter>(new XmlReporter(std::move(cfg)));
}

// Helpers to assert that the XML contains the expected attributes.
// We intentionally look for substrings/regex rather than exact XML layout
// to avoid assuming formatting/newlines from XmlWriter/StreamingReporterBase.
void expectOverallResults(const std::string& xml,
                          uint64_t succ, uint64_t fail, uint64_t expFail, uint64_t skips) {
    // Example target:
    // <OverallResults successes="X" failures="Y" expectedFailures="Z" skips="W">
    auto attr = [&](const char* name, uint64_t val) {
        std::regex r(name + std::string(R"_(\s*=\s*")_") + std::to_string(val) + R"_(")");
        EXPECT_TRUE(std::regex_search(xml, r)) << "Missing/incorrect attribute " << name
                                               << "=\"" << val << "\" in <OverallResults>";
    };

    // Ensure the element is present
    EXPECT_NE(xml.find("<OverallResults"), std::string::npos)
        << "Missing <OverallResults> element";
    attr("successes",        succ);
    attr("failures",         fail);
    attr("expectedFailures", expFail);
    attr("skips",            skips);
}

void expectOverallResultsCases(const std::string& xml,
                               uint64_t succ, uint64_t fail, uint64_t expFail, uint64_t skips) {
    // Example target:
    // <OverallResultsCases successes="X" failures="Y" expectedFailures="Z" skips="W">
    auto attr = [&](const char* name, uint64_t val) {
        std::regex r(name + std::string(R"_(\s*=\s*")_") + std::to_string(val) + R"_(")");
        EXPECT_TRUE(std::regex_search(xml, r)) << "Missing/incorrect attribute " << name
                                               << "=\"" << val << "\" in <OverallResultsCases>";
    };

    EXPECT_NE(xml.find("<OverallResultsCases"), std::string::npos)
        << "Missing <OverallResultsCases> element";
    attr("successes",        succ);
    attr("failures",         fail);
    attr("expectedFailures", expFail);
    attr("skips",            skips);
}

} // namespace

// ---------- Tests ----------

TEST(XmlReporter_testRunEnded_842, WritesOverallResultsForAssertions_Normal_842) {
    std::stringstream ss;
    auto reporter = makeReporter(ss);

    auto stats = makeStats(/*assertions*/ 5, 2, 1, 3,
                           /*cases*/       2, 1, 0, 1);

    reporter->testRunEnded(stats);

    const std::string out = ss.str();
    expectOverallResults(out,       /*succ*/5, /*fail*/2, /*expFail*/1, /*skips*/3);
    expectOverallResultsCases(out,  /*succ*/2, /*fail*/1, /*expFail*/0, /*skips*/1);
}

TEST(XmlReporter_testRunEnded_842, WritesZerosForEmptyTotals_Boundary_842) {
    std::stringstream ss;
    auto reporter = makeReporter(ss);

    auto stats = makeStats(/*assertions*/ 0, 0, 0, 0,
                           /*cases*/       0, 0, 0, 0);

    reporter->testRunEnded(stats);

    const std::string out = ss.str();
    expectOverallResults(out,       0, 0, 0, 0);
    expectOverallResultsCases(out,  0, 0, 0, 0);
}

TEST(XmlReporter_testRunEnded_842, HandlesLargeCounts_Uint64Boundary_842) {
    std::stringstream ss;
    auto reporter = makeReporter(ss);

    const uint64_t big = std::numeric_limits<uint64_t>::max();

    auto stats = makeStats(/*assertions*/ big, big - 1, big - 2, big - 3,
                           /*cases*/       big - 4, big - 5, big - 6, big - 7);

    reporter->testRunEnded(stats);

    const std::string out = ss.str();
    expectOverallResults(out,       big, big - 1, big - 2, big - 3);
    expectOverallResultsCases(out,  big - 4, big - 5, big - 6, big - 7);
}

// Optional: sanity that some outer closing happens (black-box check without asserting exact structure).
TEST(XmlReporter_testRunEnded_842, EmitsSomeClosingTag_StructureSmoke_842) {
    std::stringstream ss;
    auto reporter = makeReporter(ss);

    auto stats = makeStats(/*assertions*/ 1, 0, 0, 0,
                           /*cases*/       1, 0, 0, 0);

    reporter->testRunEnded(stats);

    const std::string out = ss.str();
    // We don't rely on private tag stack, just check that an end tag exists
    // after our elements (StreamingReporterBase may write other content).
    EXPECT_NE(out.find("</"), std::string::npos)
        << "Expected at least one closing tag in the output";
}
