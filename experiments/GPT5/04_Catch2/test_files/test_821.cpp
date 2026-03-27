// File: tests/reporter_helpers_defaultListReporters_821_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// Headers from the codebase under test
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_list.hpp"

using namespace Catch;

namespace {

struct DefaultListReportersTest_821 : ::testing::Test {
    // Helper to build a few reporter descriptions quickly
    static std::vector<ReporterDescription> makeDescs(
        std::initializer_list<std::pair<std::string, std::string>> pairs) {

        std::vector<ReporterDescription> out;
        out.reserve(pairs.size());
        for (const auto& p : pairs) {
            ReporterDescription d;
            // We only rely on public fields used by the function under test.
            // (Catch2's ReporterDescription has `name` and `description`.)
            d.name = p.first;
            d.description = p.second;
            out.push_back(d);
        }
        return out;
    }
};

} // namespace

// [Boundary] Empty input: should print header line and an extra blank line.
TEST_F(DefaultListReportersTest_821, EmptyList_PrintsHeaderAndBlankLine_821) {
    std::ostringstream os;
    const std::vector<ReporterDescription> empty;

    defaultListReporters(os, empty, Verbosity::Normal);

    const std::string out = os.str();
    // Starts with the header
    EXPECT_NE(out.find("Available reporters:\n"), std::string::npos);
    // With no items, there should be 2 consecutive newlines at the end:
    // one from the header line and one final extra newline.
    // Simple check: the output should be exactly the header + blank line.
    EXPECT_EQ(out, std::string("Available reporters:\n\n"));
}

// [Normal operation] Quiet verbosity: prints only names (no colons/descriptions)
TEST_F(DefaultListReportersTest_821, Quiet_PrintsOnlyNames_NoColons_821) {
    std::ostringstream os;
    auto descs = DefaultListReportersTest_821::makeDescs({
        {"console", "Human-friendly console output"},
        {"junit",   "JUnit XML export"},
        {"longer-name", "Something verbose"}
    });

    defaultListReporters(os, descs, Verbosity::Quiet);

    const std::string out = os.str();
    // Header present
    ASSERT_NE(out.find("Available reporters:\n"), std::string::npos);

    // Names appear
    EXPECT_NE(out.find("console"), std::string::npos);
    EXPECT_NE(out.find("junit"), std::string::npos);
    EXPECT_NE(out.find("longer-name"), std::string::npos);

    // Quiet mode should NOT add a colon after the names (no "name:")
    EXPECT_EQ(out.find("console:"), std::string::npos);
    EXPECT_EQ(out.find("junit:"), std::string::npos);
    EXPECT_EQ(out.find("longer-name:"), std::string::npos);

    // We do not assert exact spacing/wrapping — that is handled by TextFlow::Column
    // and considered internal. We only assert observable presence/absence.
}

// [Normal operation] Normal verbosity: prints "name:" and description somewhere after.
TEST_F(DefaultListReportersTest_821, Normal_PrintsNameWithColonAndDescription_821) {
    std::ostringstream os;
    auto descs = DefaultListReportersTest_821::makeDescs({
        {"console", "Human-friendly console output"},
        {"junit",   "JUnit XML export"}
    });

    defaultListReporters(os, descs, Verbosity::Normal);

    const std::string out = os.str();
    // Header present
    ASSERT_NE(out.find("Available reporters:\n"), std::string::npos);

    // Names followed by colon should appear
    EXPECT_NE(out.find("console:"), std::string::npos);
    EXPECT_NE(out.find("junit:"), std::string::npos);

    // Descriptions should appear somewhere (wrapping/spacing unspecified)
    EXPECT_NE(out.find("Human-friendly console output"), std::string::npos);
    EXPECT_NE(out.find("JUnit XML export"), std::string::npos);
}

// [Boundary-ish] High verbosity behaves like Normal (non-Quiet branch)
TEST_F(DefaultListReportersTest_821, HighVerbosity_BehavesLikeNormal_821) {
    std::ostringstream os;
    auto descs = DefaultListReportersTest_821::makeDescs({
        {"spec", "Specification-style output"}
    });

    defaultListReporters(os, descs, Verbosity::High);

    const std::string out = os.str();
    // Should look like the non-Quiet formatting (i.e., include "name:")
    EXPECT_NE(out.find("spec:"), std::string::npos);
    EXPECT_NE(out.find("Specification-style output"), std::string::npos);
}

// [Stress/robustness] Long names and descriptions are included without us
// asserting internal wrapping/padding behavior.
TEST_F(DefaultListReportersTest_821, VeryLongNameAndDescription_Included_821) {
    std::ostringstream os;

    const std::string longName(60, 'N'); // 60 'N's
    const std::string longDesc =
        "This is a very long description that is expected to exceed the console "
        "width and be wrapped by TextFlow::Column. We do not assert the wrapping "
        "details, only that the text is present in the output.";

    auto descs = DefaultListReportersTest_821::makeDescs({
        {longName, longDesc}
    });

    defaultListReporters(os, descs, Verbosity::Normal);

    const std::string out = os.str();
    // Name (with colon in non-Quiet mode) appears
    EXPECT_NE(out.find(longName + ":"), std::string::npos);
    // Description text appears (possibly wrapped across multiple lines)
    EXPECT_NE(out.find("very long description"), std::string::npos);
    EXPECT_NE(out.find("expected to exceed the console"), std::string::npos);
}
