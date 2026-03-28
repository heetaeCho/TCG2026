// File: tests/testspec_matchesbyfilter_1009_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the public Catch2 interfaces referenced by the function-under-test.
#include "Catch2/src/catch2/catch_test_spec.hpp"
#include "Catch2/src/catch2/catch_test_case_info.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::NiceMock;

namespace {

// Minimal mock for IConfig. We do not rely on any method being called when there
// are no filters, but a concrete instance is required by the signature.
class MockConfig : public Catch::IConfig {
public:
    // Provide virtual dtor to match interface
    ~MockConfig() override = default;

    // Stub out all pure-virtuals/virtuals to safe defaults. We only override what
    // might be required to instantiate; none are expected to be called in these tests.
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { static const char n[] = "mock"; return Catch::StringRef(n); }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    const Catch::TestSpec& testSpec() const override { return dummy_; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { return empty_; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() const override { return empty_; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(0); }

private:
    Catch::TestSpec dummy_{};
    std::vector<std::string> empty_{};
};

// Helper to build a vector of N placeholder TestCaseHandle objects.
// We pass nullptrs; with an empty TestSpec (no filters), matchesByFilter will
// not dereference these.
static std::vector<Catch::TestCaseHandle> makeDummyTestCases(std::size_t n) {
    std::vector<Catch::TestCaseHandle> out;
    out.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        // The provided signature allows constructing from pointers.
        // Using nullptrs is safe as long as nothing dereferences them, which
        // is guaranteed here because there are no filters.
        out.emplace_back(nullptr, nullptr);
    }
    return out;
}

} // namespace

// ------------------------ TESTS ------------------------

TEST(TestSpec_MatchesByFilter_1009, EmptySpecAndEmptyCases_ReturnsNoMatches_1009) {
    Catch::TestSpec spec;               // default-constructed: no filters (observable via interface only by behavior)
    NiceMock<MockConfig> config;        // config instance (methods not expected to be called)
    std::vector<Catch::TestCaseHandle> testCases; // empty

    auto result = spec.matchesByFilter(testCases, config);

    // With no filters, there should be no per-filter entries in Matches.
    EXPECT_TRUE(result.empty());
}

TEST(TestSpec_MatchesByFilter_1009, EmptySpecWithNonEmptyCases_ReturnsNoMatches_1009) {
    Catch::TestSpec spec;
    NiceMock<MockConfig> config;

    // Create some placeholder test cases. They should be ignored because there are no filters.
    auto testCases = makeDummyTestCases(3);

    auto result = spec.matchesByFilter(testCases, config);

    EXPECT_TRUE(result.empty()) << "No filters => no filter groups in Matches";
    // Input container should remain unchanged (size).
    EXPECT_EQ(testCases.size(), 3u);
}

TEST(TestSpec_MatchesByFilter_1009, HandlesLargeInputWithNoFilters_1009) {
    Catch::TestSpec spec;
    NiceMock<MockConfig> config;

    // Large input to check basic robustness/perf characteristics w.r.t. empty filters.
    auto testCases = makeDummyTestCases(1000);

    auto result = spec.matchesByFilter(testCases, config);

    EXPECT_TRUE(result.empty());
    EXPECT_EQ(testCases.size(), 1000u);
}

TEST(TestSpec_MatchesByFilter_1009, NullHandlesAreSafeWhenNoFilters_1009) {
    Catch::TestSpec spec;
    NiceMock<MockConfig> config;

    // Explicitly use nullptr-based handles. With no filters they aren't touched.
    std::vector<Catch::TestCaseHandle> testCases;
    testCases.emplace_back(nullptr, nullptr);
    testCases.emplace_back(nullptr, nullptr);

    auto result = spec.matchesByFilter(testCases, config);

    EXPECT_TRUE(result.empty());
    EXPECT_EQ(testCases.size(), 2u);
}
