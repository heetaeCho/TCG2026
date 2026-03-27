// File: tests/run_context_sectionEnded_499_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 headers (interfaces + types used by sectionEnded)
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/internal/catch_section.hpp> // for SectionStats

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;

namespace {

//
// Minimal concrete IConfig that satisfies v3 interface.
// We keep it tiny and return benign defaults. Only name() is used by RunContext
// constructor (to fill TestRunInfo), but we must implement all pure virtuals.
//
class StubConfig final : public Catch::IConfig {
public:
    explicit StubConfig(std::string name = "RunContextSectionEnded_499")
        : name_(std::move(name)) {}

    // --- Required overrides (benign defaults) ---
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return name_; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return true; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int  abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    Catch::TestSpec const& testSpec() const override { return dummySpec_; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { return emptyVec_; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    const std::vector<std::string>& getSectionsToRun() const override { return emptyVec_; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return true; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

private:
    std::string name_;
    std::vector<std::string> emptyVec_;
    // Dummy object to satisfy reference return; never actually used.
    struct DummyTestSpec : Catch::TestSpec { } dummySpec_;
};

//
// Mock reporter to verify external interaction: sectionEnded is called with
// expected SectionStats (name, duration, and computed assertion counts).
//
class MockReporter : public Catch::IEventListener {
public:
    // Pass config into base so anything that queries m_config is safe.
    explicit MockReporter(const Catch::IConfig* cfg) : Catch::IEventListener(cfg) {}

    MOCK_METHOD(void, sectionEnded, (const Catch::SectionStats&), (override));

    // All other virtuals keep default (non-pure) implementations inherited.
};

//
// Test fixture: owns config and prepares a RunContext with a mock reporter.
//
class RunContextSectionEndedTest_499 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reporter is created as a unique_ptr, but we keep a raw pointer for expectations.
        auto reporter = std::make_unique<NiceMock<MockReporter>>(&config_);
        reporter_ = reporter.get();
        runCtx_ = std::make_unique<Catch::RunContext>(&config_, std::move(reporter));
    }

    StubConfig config_;
    NiceMock<MockReporter>* reporter_ = nullptr; // non-owning
    std::unique_ptr<Catch::RunContext> runCtx_;
};

} // namespace

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Normal path: no active sections before calling sectionEnded.
// Verifies the reporter is notified once and receives the SectionStats with
// our SectionInfo name and the provided duration. Since no assertions happened,
// the total in SectionStats::assertions should be 0.
TEST_F(RunContextSectionEndedTest_499, SectionEnded_NotStartedBefore_ReportsZeroAssertions_499) {
    using namespace Catch;

    const char* kSecName = "lonely-section-499";
    const double kDuration = 0.123;

    SectionEndInfo endInfo;
    endInfo.sectionInfo = SectionInfo{ StringRef{kSecName},
                                       SourceLineInfo{ "unit_test.cpp", 4242 } };
    endInfo.prevAssertions = Counts{}; // no prior assertions
    endInfo.durationInSeconds = kDuration;

    EXPECT_CALL(*reporter_, sectionEnded(_))
        .WillOnce(Invoke([&](const SectionStats& stats){
            // name propagated
            EXPECT_STREQ(std::string(stats.sectionInfo.name).c_str(), kSecName);
            // duration propagated
            EXPECT_DOUBLE_EQ(stats.durationInSeconds, kDuration);
            // delta of assertions = 0
            EXPECT_EQ(stats.assertions.total(), 0u);
        }));

    runCtx_->sectionEnded(std::move(endInfo));
}

// Branch coverage: start a section, then end it.
// This ensures the internal "if (!m_activeSections.empty()) { ... }" path is exercised.
// We still verify only the observable effect: reporter gets called with the
// SectionStats matching our section and a zero-assertion delta (because no
// assertions were made between start and end).
TEST_F(RunContextSectionEndedTest_499, SectionEnded_AfterSectionStarted_ReportsZeroDelta_499) {
    using namespace Catch;

    // Start a section to put a tracker on the stack.
    Counts prev{};
    (void)runCtx_->sectionStarted(StringRef{"outer-499"},
                                  SourceLineInfo{"unit_test.cpp", 101}, prev);

    // Prepare matching end info, with prevAssertions taken from sectionStarted output.
    const double kDuration = 0.5;
    SectionEndInfo endInfo;
    endInfo.sectionInfo = SectionInfo{ StringRef{"outer-499"},
                                       SourceLineInfo{ "unit_test.cpp", 101 } };
    endInfo.prevAssertions = prev;       // ensure delta computes to 0
    endInfo.durationInSeconds = kDuration;

    EXPECT_CALL(*reporter_, sectionEnded(_))
        .WillOnce(Invoke([&](const SectionStats& stats){
            EXPECT_STREQ(std::string(stats.sectionInfo.name).c_str(), "outer-499");
            EXPECT_DOUBLE_EQ(stats.durationInSeconds, kDuration);
            EXPECT_EQ(stats.assertions.total(), 0u);
        }));

    runCtx_->sectionEnded(std::move(endInfo));
}

// Boundary-ish behavior: ending a section with a non-zero duration and an
// explicit prevAssertions greater/equal to current totals (still zero here) should
// not crash and must still notify the reporter once. We only validate the call.
TEST_F(RunContextSectionEndedTest_499, SectionEnded_ReporterIsAlwaysNotified_499) {
    using namespace Catch;

    SectionEndInfo endInfo;
    endInfo.sectionInfo = SectionInfo{ StringRef{"notify-always-499"},
                                       SourceLineInfo{ "unit_test.cpp", 7 } };
    // prevAssertions arbitrary; with no actual assertions, delta should not underflow
    endInfo.prevAssertions = Counts{};
    endInfo.durationInSeconds = 42.0;

    EXPECT_CALL(*reporter_, sectionEnded(_)).Times(1);
    runCtx_->sectionEnded(std::move(endInfo));
}
