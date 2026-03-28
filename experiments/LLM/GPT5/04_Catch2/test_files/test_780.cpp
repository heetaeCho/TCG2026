// File: tests/reporterbase_listtags_tests_780.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>

// Catch2 headers (paths may vary depending on your tree layout)
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp" // for ReporterConfig (v3)

// ------------------------------------------------------------
// Test double for the free function defaultListTags.
// This is the ONLY behavior we verify: that ReporterBase::listTags
// forwards to this function with the correct parameters.
// ------------------------------------------------------------
namespace Catch {

static std::ostream* g_lastStream = nullptr;
static bool g_lastHasFilters = false;
static size_t g_callCount = 0;

// Link-time replacement used only in tests.
// Signature must match the production declaration.
void defaultListTags(std::ostream& os,
                     std::vector<TagInfo> const& tags,
                     bool hasTestFilters) {
    (void)tags; // we don't assert on contents; just that it's forwarded
    g_lastStream = &os;
    g_lastHasFilters = hasTestFilters;
    ++g_callCount;

    // Write a small marker so tests can also assert the stream was actually used.
    os << "[defaultListTags-called]";
}

} // namespace Catch

// ------------------------------------------------------------
// GoogleMock for IConfig so we can control hasTestFilters().
// We only override what's needed for this unit.
// ------------------------------------------------------------
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));

    // Provide harmless defaults for the rest of the virtuals so we do not
    // couple tests to their behavior. These return values are not used by the SUT.
    // (Using ON_CALL(...) as needed keeps the interface black-boxed.)
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { static const std::string n = "cfg"; return Catch::StringRef(n); }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec ts; return ts; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return true; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
};

// ------------------------------------------------------------
// Test fixture sets up a ReporterBase instance with a controllable
// IConfig (mock) and a stringstream as the output sink.
// ------------------------------------------------------------
class ReporterBase_ListTags_780 : public ::testing::Test {
protected:
    std::unique_ptr<MockConfig> mockCfg;
    std::ostringstream oss;

    // ReporterBase requires a ReporterConfig. We build one with our
    // mock IConfig, our stringstream sink, and a neutral colour mode.
    std::unique_ptr<Catch::ReporterBase> reporter;

    void SetUp() override {
        using namespace Catch;

        mockCfg = std::make_unique<MockConfig>();

        // ReporterConfig API differs slightly across Catch2 minor versions.
        // This overload uses: (IConfig const*, IStream*, ColourMode, Detail::unique_ptr<IStream> ownership wrapper)
        // Helper creates an owning stream wrapper for our ostringstream.
        auto streamPtr = Catch::Detail::make_unique<Catch::Detail::OStream>(oss);

        Catch::ReporterConfig rc(
            mockCfg.get(),                    // fullConfig
            streamPtr.get(),                  // IStream* (the wrapper, not the std::ostream)
            Catch::ColourMode::None,          // colour choice neutral
            {}                                // custom options (empty)
        );

        // ReporterBase takes ownership of the IStream through ReporterConfig::takeStream(),
        // so we must release it from our local unique_ptr.
        streamPtr.release();

        reporter = std::make_unique<Catch::ReporterBase>(std::move(rc));

        // Reset the spy
        Catch::g_lastStream = nullptr;
        Catch::g_lastHasFilters = false;
        Catch::g_callCount = 0;
    }
};

// ------------------------------------------------------------
// TESTS
// ------------------------------------------------------------

TEST_F(ReporterBase_ListTags_780, ListTags_Forwards_WhenHasFiltersFalse_780) { // TEST_ID = 780
    using ::testing::Return;

    ON_CALL(*mockCfg, hasTestFilters())
        .WillByDefault(Return(false));

    // Empty tags vector is fine; we don't assert on contents.
    std::vector<Catch::TagInfo> tags;

    reporter->listTags(tags);

    // Verify the external collaborator was called exactly once
    EXPECT_EQ(Catch::g_callCount, 1u);

    // The forwarded stream must be the reporter's output stream (our oss)
    ASSERT_NE(Catch::g_lastStream, nullptr);
    EXPECT_EQ(Catch::g_lastStream, &oss);

    // The hasFilters flag must reflect IConfig::hasTestFilters()
    EXPECT_FALSE(Catch::g_lastHasFilters);

    // And we should see the small marker written by our test double.
    EXPECT_NE(oss.str().find("[defaultListTags-called]"), std::string::npos);
}

TEST_F(ReporterBase_ListTags_780, ListTags_Forwards_WhenHasFiltersTrue_780) { // TEST_ID = 780
    using ::testing::Return;

    ON_CALL(*mockCfg, hasTestFilters())
        .WillByDefault(Return(true));

    std::vector<Catch::TagInfo> tags;

    reporter->listTags(tags);

    EXPECT_EQ(Catch::g_callCount, 1u);
    ASSERT_NE(Catch::g_lastStream, nullptr);
    EXPECT_EQ(Catch::g_lastStream, &oss);
    EXPECT_TRUE(Catch::g_lastHasFilters);
    EXPECT_NE(oss.str().find("[defaultListTags-called]"), std::string::npos);
}

// Boundary: even with an empty tag list, the collaborator must be called once.
TEST_F(ReporterBase_ListTags_780, ListTags_CallsCollaborator_WithEmptyTagList_780) { // TEST_ID = 780
    using ::testing::Return;
    ON_CALL(*mockCfg, hasTestFilters()).WillByDefault(Return(false));

    std::vector<Catch::TagInfo> emptyTags;
    reporter->listTags(emptyTags);

    EXPECT_EQ(Catch::g_callCount, 1u);
    EXPECT_NE(oss.str().find("[defaultListTags-called]"), std::string::npos);
}
