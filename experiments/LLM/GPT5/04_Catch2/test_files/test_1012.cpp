// File: tests/sort_tests_1012.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

// Public Catch2 interfaces used by sortTests (as per the provided partial code)
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_test_case_info.hpp"   // for TestCaseHandle declaration
#include "catch_amalgamated.hpp"             // for TestCaseInfoHasher declaration
// Note: sortTests is defined in the amalgamated .cpp, but we only *call* it.
//       No internal logic is reimplemented here.

using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::AnyNumber;

namespace Catch {

// Minimal GMock for IConfig to drive runOrder and rngSeed interactions.
// We only mock what we need; the rest of the virtuals are ignored.
class MockConfig : public IConfig {
public:
    // Only the methods needed for this unit under test:
    MOCK_METHOD(TestRunOrder, runOrder, (), (override));
    MOCK_METHOD(uint32_t, rngSeed, (), (override));

    // Provide safe defaults for other IConfig methods to avoid accidental calls.
    // We DO NOT assert on them, but make them callable if sortTests ever touches them
    // (it shouldn't, per the given code). Keeping them as non-mock simple stubs
    // avoids relying on internal behaviors.
    bool allowThrows() override { return true; }
    StringRef name() override { return StringRef(""); }
    bool includeSuccessfulResults() override { return false; }
    bool shouldDebugBreak() override { return false; }
    bool warnAboutMissingAssertions() override { return false; }
    bool warnAboutUnmatchedTestSpecs() override { return false; }
    bool zeroTestsCountAsSuccess() override { return false; }
    int abortAfter() override { return 0; }
    bool showInvisibles() override { return false; }
    ShowDurations showDurations() override { return ShowDurations::DefaultForReporter; }
    double minDuration() override { return 0.0; }
    TestSpec const& testSpec() override {
        static TestSpec spec; return spec;
    }
    bool hasTestFilters() override { return false; }
    std::vector<std::string> const& getTestsOrTags() override {
        static std::vector<std::string> v; return v;
    }
    unsigned int shardCount() override { return 1u; }
    unsigned int shardIndex() override { return 0u; }
    ColourMode defaultColourMode() override { return ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() override {
        static std::vector<std::string> v; return v;
    }
    Verbosity verbosity() override { return Verbosity::Normal; }
    bool skipBenchmarks() override { return false; }
    bool benchmarkNoAnalysis() override { return false; }
    unsigned int benchmarkSamples() override { return 0u; }
    double benchmarkConfidenceInterval() override { return 0.95; }
    unsigned int benchmarkResamples() override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() override { return std::chrono::milliseconds(0); }
    // Note: runOrder() and rngSeed() are mocked above.
};

// Forward declaration of the function under test (provided in the partial code).
// We only declare it so we can call it; we do not define/reimplement it.
std::vector<TestCaseHandle>
sortTests(IConfig const& config, std::vector<TestCaseHandle> const& unsortedTestCases);

} // namespace Catch

// ------------------------- Tests -------------------------

// Declared order: with empty input, result must be empty and there should be no
// other interactions with config beyond runOrder().
TEST(SortTests_1012, Declared_EmptyInput_ReturnsEmpty_1012) {
    Catch::MockConfig cfg;

    EXPECT_CALL(cfg, runOrder())
        .WillOnce(Return(Catch::TestRunOrder::Declared));
    // rngSeed must NOT be called for Declared
    EXPECT_CALL(cfg, rngSeed()).Times(0);

    const std::vector<Catch::TestCaseHandle> emptyInput;
    auto out = Catch::sortTests(cfg, emptyInput);

    EXPECT_TRUE(out.empty());
}

// LexicographicallySorted order: with empty input, result must be empty and
// rngSeed() is not used.
TEST(SortTests_1012, LexicographicallySorted_EmptyInput_ReturnsEmpty_1012) {
    Catch::MockConfig cfg;

    EXPECT_CALL(cfg, runOrder())
        .WillOnce(Return(Catch::TestRunOrder::LexicographicallySorted));
    // rngSeed must NOT be called for LexicographicallySorted
    EXPECT_CALL(cfg, rngSeed()).Times(0);

    const std::vector<Catch::TestCaseHandle> emptyInput;
    auto out = Catch::sortTests(cfg, emptyInput);

    EXPECT_TRUE(out.empty());
}

// Randomized order: even with empty input, implementation constructs the hasher
// with cfg.rngSeed(), so rngSeed() must be called exactly once.
TEST(SortTests_1012, Randomized_EmptyInput_UsesRngSeed_AndReturnsEmpty_1012) {
    Catch::MockConfig cfg;

    {
        InSequence seq;
        EXPECT_CALL(cfg, runOrder())
            .WillOnce(Return(Catch::TestRunOrder::Randomized));
        EXPECT_CALL(cfg, rngSeed())
            .WillOnce(Return(123u)); // any deterministic seed OK
    }

    const std::vector<Catch::TestCaseHandle> emptyInput;
    auto out = Catch::sortTests(cfg, emptyInput);

    EXPECT_TRUE(out.empty());
}

// Defensive case: If config.runOrder() returns an unknown enum value,
// sortTests triggers the internal error path. We only assert that *some*
// exception is thrown without relying on its type or message (black-box).
TEST(SortTests_1012, UnknownRunOrder_TriggersInternalError_1012) {
    Catch::MockConfig cfg;

    // Force an invalid enum value via static_cast.
    EXPECT_CALL(cfg, runOrder())
        .WillOnce(Return(static_cast<Catch::TestRunOrder>(999)));
    // rngSeed should not be touched in this path (early failure).
    EXPECT_CALL(cfg, rngSeed()).Times(0);

    const std::vector<Catch::TestCaseHandle> emptyInput;

#if GTEST_HAS_DEATH_TEST
    // Depending on how CATCH_INTERNAL_ERROR is configured, it may abort or throw.
    // Prefer a broad EXPECT_ANY_THROW first; if your build aborts instead,
    // you can switch to death test below.
    EXPECT_ANY_THROW({
        (void)Catch::sortTests(cfg, emptyInput);
    });
#else
    EXPECT_ANY_THROW({
        (void)Catch::sortTests(cfg, emptyInput);
    });
#endif
}
