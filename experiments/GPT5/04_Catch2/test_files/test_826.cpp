// File: tests/reporter_sonarqube_testRunStarting_826.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// Public headers we rely on (interfaces only)
#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

// If your project exposes ReporterConfig in a helper header, include it.
// Otherwise include the header that defines ReporterConfig in your tree.
#include "catch2/reporters/catch_reporter_helpers.hpp" // typical location in Catch2 v3
// ^ If the above path differs in your tree, adjust include accordingly.

// -----------------------------
// Minimal IConfig stub
// -----------------------------
// We need a valid IConfig instance because SonarQubeReporter::testRunStarting()
// calls createMetadataString(*m_config) which dereferences it. We do not care
// about the concrete metadata content, so a stub with harmless defaults is fine.
//
// NOTE: IConfig has many pure virtual members. This stub implements a set that
// is commonly required by Catch2. If your local IConfig differs, extend the
// stub with the remaining pure virtuals (returning benign defaults). This keeps
// the test independent of implementation details of SonarQubeReporter.
//
namespace {
class StubConfig final : public Catch::IConfig {
public:
    // --- Minimal surface returning benign defaults ---
    // The exact set of pure virtuals can vary slightly across Catch2 versions.
    // Implement/extend as needed in your tree.

    // Run name (used in some reporters' metadata)
    std::string name() const override { return "stub-run"; }

    // RNG seed
    uint32_t rngSeed() const override { return 0u; }

    // Listing & filtering
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listReporters() const override { return false; }
    bool listListeners() const override { return false; }

    // Rerun / order
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }

    // Colour / output
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    bool showDurations() const override { return false; }
    Catch::ShowDurations::OrNot::type showDurationsType() const override { return Catch::ShowDurations::OrNot::DefaultForReporter; }
    double minDuration() const override { return 0.0; }

    // Sharding / other (safe defaults)
    bool shardTests() const override { return false; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }

    // Several other members exist depending on Catch2 version (e.g., benchmarks,
    // assertions, test order, repeat count, etc.). Provide conservative defaults:
    bool allowThrows() const override { return true; }
    bool allowIncompleteAssertions() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool includeSuccessfulResults() const override { return true; }
    bool cleanUp() const override { return true; }
    bool useActiveDbgsym() const override { return false; }
    int abortAfter() const override { return 0; }
    bool benchmarkNoAnalysis() const override { return true; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    int benchmarkResamples() const override { return 100; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    Catch::TestSpec const& testSpec() const override {
        static Catch::TestSpec s;
        return s;
    }
    bool hasTestFilters() const override { return false; }
    bool skipBenchmarks() const override { return true; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    Catch::CaseSensitivity nameMatchingCaseSensitivity() const override { return Catch::CaseSensitivity::CaseSensitive; }
    bool filenamesAsTags() const override { return false; }
    bool hasTestAtLine() const override { return false; }
    std::pair<std::string, std::size_t> testAtLine() const override { return {"", 0}; }
    unsigned int rngFixedSeed() const override { return 0; }
    bool useExactTestNamesOnly() const override { return false; }
    bool debugOnFailure() const override { return false; }
    bool printTestNamesOnly() const override { return false; }
};
} // namespace

// -----------------------------
// Fixture
// -----------------------------
class SonarQubeReporterTest_826 : public ::testing::Test {
protected:
    std::ostringstream out;
    StubConfig cfg;

    // ReporterConfig is move-constructed; build it with our stream & config.
    Catch::ReporterConfig makeConfig() {
        // Typical ctor: ReporterConfig(const IConfig*, std::ostream&, ColourMode)
        // If your version differs, adjust accordingly.
        return Catch::ReporterConfig(&cfg, out, Catch::ColourMode::None);
    }
};

// -----------------------------
// Tests
// -----------------------------

TEST_F(SonarQubeReporterTest_826, WritesCommentAndRootElement_826) {
    Catch::SonarQubeReporter reporter{ makeConfig() };

    // Act
    Catch::TestRunInfo tri{ Catch::StringRef("run-826") };
    ASSERT_NO_THROW(reporter.testRunStarting(tri));

    const std::string s = out.str();

    // Assert: an XML comment was written (metadata)
    // We do not depend on exact metadata text, only that a comment opener exists.
    EXPECT_THAT(s, ::testing::HasSubstr("<!--"));

    // Assert: root element "testExecutions" appears
    EXPECT_THAT(s, ::testing::HasSubstr("testExecutions"));

    // Assert: version attribute with value '1' is present
    // We keep this loose on whitespace/quoting style.
    EXPECT_THAT(s, ::testing::HasSubstr("version"));
    EXPECT_THAT(s, ::testing::HasSubstr("1"));
}

TEST_F(SonarQubeReporterTest_826, IsIdempotentForMultipleStarts_826) {
    Catch::SonarQubeReporter reporter{ makeConfig() };

    Catch::TestRunInfo tri{ Catch::StringRef("run-826") };

    // Call twice; we do not assert on internal counters,
    // only that resulting output contains 2 occurrences of the root marker.
    reporter.testRunStarting(tri);
    reporter.testRunStarting(tri);

    const std::string s = out.str();

    // We expect at least two appearances of "testExecutions"
    // (loose check; does not assert on strict XML well-formedness).
    size_t first = s.find("testExecutions");
    ASSERT_NE(first, std::string::npos);
    size_t second = s.find("testExecutions", first + 1);
    EXPECT_NE(second, std::string::npos);

    // And at least two comment markers (metadata per start).
    size_t c1 = s.find("<!--");
    ASSERT_NE(c1, std::string::npos);
    size_t c2 = s.find("<!--", c1 + 1);
    EXPECT_NE(c2, std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, AcceptsArbitraryRunName_826) {
    Catch::SonarQubeReporter reporter{ makeConfig() };

    // Different run name should still produce the same structural output.
    Catch::TestRunInfo tri{ Catch::StringRef("anything-goes-🐙") };
    reporter.testRunStarting(tri);

    const std::string s = out.str();
    EXPECT_THAT(s, ::testing::HasSubstr("testExecutions"));
    EXPECT_THAT(s, ::testing::HasSubstr("version"));
    EXPECT_THAT(s, ::testing::HasSubstr("<!--"));
}

// (Optional) Boundary-ish check: very long run name should not break structure.
// We do not assert on exact placement, only presence of structural bits.
TEST_F(SonarQubeReporterTest_826, LongRunNameDoesNotAffectStructure_826) {
    Catch::SonarQubeReporter reporter{ makeConfig() };

    std::string longName(4096, 'X');
    Catch::TestRunInfo tri{ Catch::StringRef(longName) };
    reporter.testRunStarting(tri);

    const std::string s = out.str();
    EXPECT_THAT(s, ::testing::HasSubstr("testExecutions"));
    EXPECT_THAT(s, ::testing::HasSubstr("version"));
    EXPECT_THAT(s, ::testing::HasSubstr("<!--"));
}
