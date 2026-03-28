// File: tests/xml_reporter_benchmark_preparing_843_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 headers (adjust paths if needed)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_tostring.hpp"      // if your config/mock needs it
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

// If your tree exposes ReporterConfig directly here; otherwise include its header.
#include "catch2/reporters/catch_reporter_helpers.hpp"

using ::testing::HasSubstr;

namespace {

/// Minimal NiceMock-like stub of IConfig to satisfy ReporterConfig construction.
/// Implement only what your particular ReporterConfig constructor or base
/// reporter will touch during these tests. If your repo already has a ready-made
/// test stub for IConfig, replace this with that.
class DummyConfig : public Catch::IConfig {
public:
    // Implement pure virtuals with benign defaults. Adjust if your build requires more.
    bool allowThrows() const override { return true; }
    std::string name() const override { return "dummy-config"; }

    // The rest can return harmless defaults. Add/adjust methods if your build complains.
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 1000; }
    std::chrono::milliseconds shardTestFiles() const override { return std::chrono::milliseconds{0}; }
    std::string shardSeed() const override { return {}; }
    std::size_t shardCount() const override { return 1; }
    std::size_t shardIndex() const override { return 0; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> getTestsOrTags() const override { return {}; }
    std::vector<std::string> getSectionsToRun() const override { return {}; }
    bool listReporters() const override { return false; }
    bool listListeners() const override { return false; }
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listTestNamesOnly() const override { return false; }
    std::vector<std::string> getReporterNames() const override { return {}; }
    std::vector<std::string> getListenerNames() const override { return {}; }
    std::string getProcessName() const override { return "proc"; }
    std::string getReporterOutputPath() const override { return {}; }
    bool showSuccessfulTests() const override { return true; }
    bool showDurations() const override { return false; }
    double minDuration() const override { return 0.0; }
    bool shouldShowDurationForTest() const override { return false; }
    bool showTestCaseOutput() const override { return true; }
    bool showAmbiguousTestNameWarnings() const override { return false; }
    bool allowZeroTests() const override { return true; }
    int abortAfter() const override { return 0; }
    bool inWhatMode() const override { return false; }
    bool writeToDisk() const override { return false; }
    bool loadTestNamesFromFile() const override { return false; }
    std::string getFilename() const override { return {}; }
    bool hasTestFiltersChanged() const override { return false; }
    bool shouldEnforceNoAssertions() const override { return false; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool warningsAsErrors() const override { return false; }
    bool useColour() const override { return true; }
    bool misuseColours() const override { return false; }
    bool includeIthRunInfo() const override { return false; }
    bool showInvisibles() const override { return false; }
    bool showInfoMessages() const override { return false; }
    bool showInternalMessages() const override { return false; }
    bool showUnicodeEscapeSequences() const override { return false; }
    bool defaultToConfigTags() const override { return false; }
    bool hasSharding() const override { return false; }
};

/// A simple IStream that forwards to an std::ostream we own, so ReporterConfig
/// can hand it to the reporter. In Catch2 v3, ReporterConfig typically takes
/// an IStream reference.
class OStringIStream : public Catch::IStream {
public:
    explicit OStringIStream(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

/// Helper to construct XmlReporter bound to our ostringstream.
/// Adjust construction to match your Catch2 version if needed.
static std::unique_ptr<Catch::XmlReporter> makeXmlReporter(std::ostringstream& oss) {
    static DummyConfig dummyConfig;
    OStringIStream istream(oss);

    // Colour mode is irrelevant for XML output; pass None when available.
    Catch::ReporterConfig rc(&dummyConfig, istream, Catch::ColourMode::None);
    return std::unique_ptr<Catch::XmlReporter>(
        new Catch::XmlReporter(CATCH_MOVE(rc))
    );
}

} // namespace

// ========== TESTS ==========

TEST(XmlReporter_BenchmarkPreparing_843, WritesOpeningBenchmarkResultsTagWithNameAttribute_Normal_843) {
    std::ostringstream oss;
    auto reporter = makeXmlReporter(oss);

    reporter->benchmarkPreparing(Catch::StringRef("MatrixMultiply"));

    const std::string out = oss.str();
    // We do NOT assert exact formatting; just the observable presence of element name & attribute key/value.
    EXPECT_THAT(out, HasSubstr("BenchmarkResults"));
    EXPECT_THAT(out, HasSubstr("name"));
    EXPECT_THAT(out, HasSubstr("MatrixMultiply"));
}

TEST(XmlReporter_BenchmarkPreparing_843, HandlesEmptyNameAndStillWritesNameAttribute_843) {
    std::ostringstream oss;
    auto reporter = makeXmlReporter(oss);

    reporter->benchmarkPreparing(Catch::StringRef(""));

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("BenchmarkResults"));
    EXPECT_THAT(out, HasSubstr("name"));
    // We do not force exact `name=""` formatting; presence of the key suffices as observable behavior.
}

TEST(XmlReporter_BenchmarkPreparing_843, AcceptsLongAndSpecialCharNamesWithoutThrowing_843) {
    std::ostringstream oss;
    auto reporter = makeXmlReporter(oss);

    // Boundary-ish: long + characters that typically require XML escaping.
    std::string longWeirdName(1024, 'A');
    longWeirdName.replace(100, 5, "<&\"'>"); // inject special chars somewhere in the middle

    ASSERT_NO_THROW({
        reporter->benchmarkPreparing(Catch::StringRef(longWeirdName));
    });

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("BenchmarkResults"));
    EXPECT_THAT(out, HasSubstr("name"));
    // We do NOT assert exact escaping; just that some representation of the provided name contributed to output length.
    EXPECT_GT(out.size(), 0u);
}

