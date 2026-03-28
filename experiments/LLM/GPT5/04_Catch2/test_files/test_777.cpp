// File: tests/reporter_base_listReporters_777_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <map>
#include <vector>

#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_user_config.hpp> // if you have a project-local config; harmless if absent

using ::testing::Return;
using ::testing::Exactly;

namespace {

class MockConfig : public Catch::IConfig {
public:
    // Only mock what we need; other virtuals can keep default-empty impls.
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));

    // Provide safe defaults for other virtuals if g++ complains they’re
    // “pure” in your local headers (some forks mark a few as =0).
    // If your IConfig has them non-pure, you can omit these overrides.
    // Below are minimal, *unused* stubs to satisfy linkage when needed.
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { static const std::string n = "mock"; return Catch::StringRef(n); }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    const Catch::TestSpec& testSpec() const override {
        static Catch::TestSpec s; return s;
    }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override {
        static std::vector<std::string> v; return v;
    }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    const std::vector<std::string>& getSectionsToRun() const override {
        static std::vector<std::string> v; return v;
    }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
};

// Helper to build a ReporterBase with a string-backed stream.
// If your project exposes convenience helpers, feel free to use those instead.
class ReporterBaseHarness {
public:
    ReporterBaseHarness(Catch::IConfig const* cfg, std::ostringstream& sink)
        : m_streamHolder(Catch::Detail::make_unique<Catch::IStream const>(Catch::Detail::makeStream(sink)))
        , m_config(cfg)
    {
        // --- Adjust this block if your ReporterConfig signature differs ---
        // Many Catch2 v3 trees have a ReporterConfig that accepts:
        // (IConfig const* fullConfig,
        //  Catch::Detail::unique_ptr<Catch::IStream> stream,
        //  ColourMode mode,
        //  std::map<std::string, std::string> customOptions = {})
        Catch::ReporterConfig rc(
            m_config,
            Catch::Detail::unique_ptr<Catch::IStream>(const_cast<Catch::IStream*>(m_streamHolder.get())), // take ownership
            Catch::ColourMode::None,
            {}
        );

        // We must not keep m_streamHolder after moving it into rc; to keep
        // this simple, we rebuild it above and then move it here. Alternatively,
        // you can create the unique_ptr directly in-place for rc.
        // Construct the ReporterBase under test
        m_reporter = std::unique_ptr<Catch::ReporterBase>(new Catch::ReporterBase(std::move(rc)));
    }

    Catch::ReporterBase& reporter() { return *m_reporter; }

private:
    // Keep an owning handle to the initially created stream till we hand it over
    Catch::Detail::unique_ptr<Catch::IStream const> m_streamHolder;
    Catch::IConfig const* m_config = nullptr;
    std::unique_ptr<Catch::ReporterBase> m_reporter;
};

} // namespace

// --------------------- Tests ---------------------

// TEST_ID: 777
TEST(ReporterBase_ListReporters_777, CallsVerbosityOnConfig_777) {
    using namespace Catch;

    std::ostringstream sink;
    MockConfig cfg;

    EXPECT_CALL(cfg, verbosity())
        .Times(Exactly(1))
        .WillOnce(Return(Verbosity::Normal));

    ReporterBaseHarness harness(&cfg, sink);

    // Provide a minimal non-empty description list.
    ReporterDescription desc;
    // The fields of ReporterDescription are not asserted in tests; we only
    // need existence to trigger defaultListReporters. If your type requires
    // construction args, fill them appropriately here without asserting on them.
    std::vector<ReporterDescription> descriptions{desc};

    // Act: black-box call
    ASSERT_NO_THROW(harness.reporter().listReporters(descriptions));
}

// TEST_ID: 777
TEST(ReporterBase_ListReporters_777, WritesSomethingWhenDescriptionsPresent_777) {
    using namespace Catch;

    std::ostringstream sink;
    MockConfig cfg;

    // Verbosity value is an input into the behavior; we don't assert on format.
    EXPECT_CALL(cfg, verbosity())
        .Times(Exactly(1))
        .WillOnce(Return(Verbosity::Quiet));

    ReporterBaseHarness harness(&cfg, sink);

    // At least one item to list -> should produce some output.
    ReporterDescription desc;
    std::vector<ReporterDescription> descriptions{desc};

    harness.reporter().listReporters(descriptions);

    // Black-box observable: some output was written to the configured stream.
    // We do NOT check exact formatting.
    const std::string out = sink.str();
    EXPECT_FALSE(out.empty()) << "Expected listReporters to emit some text for non-empty input";
}

// TEST_ID: 777
TEST(ReporterBase_ListReporters_777, HandlesEmptyListGracefully_777) {
    using namespace Catch;

    std::ostringstream sink;
    MockConfig cfg;

    EXPECT_CALL(cfg, verbosity())
        .Times(Exactly(1))
        .WillOnce(Return(Verbosity::Normal));

    ReporterBaseHarness harness(&cfg, sink);

    std::vector<ReporterDescription> descriptions; // empty

    // The method should be safe to call with no reporters; we only verify
    // that it does not throw and keeps stream usable. We do NOT assert on
    // specific text presence/absence.
    EXPECT_NO_THROW(harness.reporter().listReporters(descriptions));
    EXPECT_TRUE(sink.good() || sink.eof()) << "Stream should remain in a good/eof state after call";
}
