#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <map>
#include <memory>

// Catch2 public headers used by the interface under test.
// (Paths follow the ones provided in the prompt.)
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_json.hpp"

// -------------------------
// Minimal IStream test sink
// -------------------------
namespace Catch {
struct TestOStringStream : IStream {
    std::ostringstream oss;
    std::ostream& stream() override { return oss; }
};
} // namespace Catch

// ---------------------------------
// Minimal TestSpec holder for config
// ---------------------------------
namespace {
class TestSpecHolder {
public:
    // We keep a real Catch::TestSpec instance. We only rely on hasFilters()
    // being observable via the constructor writing "filters" key when true.
    // For these tests we validate the "no filters" branch.
    const Catch::TestSpec& get() const { return m_spec; }
private:
    Catch::TestSpec m_spec; // default constructed -> hasFilters() should be false
};
} // namespace

// -------------------------
// Stub IConfig (public API)
// -------------------------
// We implement all pure virtuals with neutral defaults, and only three
// are relevant to the constructor: name(), rngSeed(), testSpec().
class StubConfig : public Catch::IConfig {
public:
    explicit StubConfig(std::string name, uint32_t seed, const Catch::TestSpec& ts)
        : m_name(std::move(name)), m_seed(seed), m_testSpec(ts) {}

    // --- Methods the JsonReporter constructor uses:
    Catch::StringRef name() const override { return Catch::StringRef(m_name); }
    uint32_t rngSeed() const override { return m_seed; }
    const Catch::TestSpec& testSpec() const override { return m_testSpec; }

    // --- Everything else: neutral defaults (do not affect constructor)
    bool allowThrows() const override { return true; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

private:
    std::string m_name;
    uint32_t m_seed;
    const Catch::TestSpec& m_testSpec;
};

// ------------------------------
// Fixture: JsonReporterTest_1104
// ------------------------------
class JsonReporterTest_1104 : public ::testing::Test {
protected:
    using UniqueStream = Catch::Detail::unique_ptr<Catch::IStream>;

    // Helper: build a ReporterConfig targeting our ostringstream sink
    Catch::ReporterConfig makeConfig(Catch::IConfig const* cfg) {
        auto sink = UniqueStream(new Catch::TestOStringStream());
        // Keep a raw pointer to read the stream later
        m_sink = static_cast<Catch::TestOStringStream*>(sink.get());
        std::map<std::string, std::string> options;
        return Catch::ReporterConfig(cfg, std::move(sink),
                                     Catch::ColourMode::PlatformDefault, options);
    }

    // Access the underlying captured output
    std::string out() const {
        return m_sink ? m_sink->oss.str() : std::string{};
    }

    Catch::TestOStringStream* m_sink = nullptr;
    TestSpecHolder m_specHolder; // default -> hasFilters() expected false
};

// ----------------------------------------------------
// TEST 1: Preferences flags are set + metadata written
// ----------------------------------------------------
TEST_F(JsonReporterTest_1104, Constructor_WritesHeaderAndMetadata_1104) {
    // Arrange
    StubConfig cfg{"json-run", /*rng*/ 424242u, m_specHolder.get()};
    auto repCfg = makeConfig(&cfg);

    // Act
    Catch::JsonReporter reporter(std::move(repCfg));

    // Assert: preferences
    const auto& prefs = reporter.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut) << "Constructor should enable stdout redirection";
    EXPECT_TRUE(prefs.shouldReportAllAssertions) << "Constructor should enable reporting all assertions";

    // Assert: output envelope & metadata keys present
    const std::string s = out();
    // We do not assert full JSON shape (black box) — only observable keys/values.
    EXPECT_THAT(s, ::testing::HasSubstr("\"version\"")) << "version key should be present";
    EXPECT_THAT(s, ::testing::HasSubstr("1")) << "version value 1 should be present";

    EXPECT_THAT(s, ::testing::HasSubstr("\"metadata\"")) << "metadata object should be present";
    EXPECT_THAT(s, ::testing::HasSubstr("\"name\"")) << "name key should be present";
    EXPECT_THAT(s, ::testing::HasSubstr("json-run")) << "configured run name should be present in output";

    EXPECT_THAT(s, ::testing::HasSubstr("\"rng-seed\"")) << "rng-seed key should be present";
    EXPECT_THAT(s, ::testing::HasSubstr("424242")) << "rng seed value should be present";

    EXPECT_THAT(s, ::testing::HasSubstr("\"catch2-version\""))
        << "catch2-version key should be present (value is provided by the library)";
}

// ---------------------------------------------------------------------
// TEST 2 (boundary): no filters -> constructor must NOT write `filters`
// ---------------------------------------------------------------------
TEST_F(JsonReporterTest_1104, Constructor_DoesNotWriteFiltersWhenNone_1104) {
    // Arrange: default TestSpec -> hasFilters() expected false
    StubConfig cfg{"no-filters", /*rng*/ 0u, m_specHolder.get()};
    auto repCfg = makeConfig(&cfg);

    // Act
    Catch::JsonReporter reporter(std::move(repCfg));

    // Assert: stream should not contain "filters" field
    const std::string s = out();
    EXPECT_THAT(s, ::testing::Not(::testing::HasSubstr("\"filters\"")))
        << "When TestSpec::hasFilters() is false, constructor must not emit filters";
}

// ---------------------------------------------------------------------
// TEST 3 (edge input): empty name + rngSeed=0 still yields stable JSON
// ---------------------------------------------------------------------
TEST_F(JsonReporterTest_1104, Constructor_AllowsEmptyNameAndZeroSeed_1104) {
    // Arrange
    StubConfig cfg{"", /*rng*/ 0u, m_specHolder.get()};
    auto repCfg = makeConfig(&cfg);

    // Act
    Catch::JsonReporter reporter(std::move(repCfg));

    // Assert: keys are present; empty name and zero appear in JSON
    const std::string s = out();
    EXPECT_THAT(s, ::testing::HasSubstr("\"metadata\""));
    EXPECT_THAT(s, ::testing::HasSubstr("\"name\""));
    // Empty string should still serialize a name field; we only check the key exists.
    EXPECT_THAT(s, ::testing::HasSubstr("\"rng-seed\""));
    EXPECT_THAT(s, ::testing::HasSubstr("0"));
}
