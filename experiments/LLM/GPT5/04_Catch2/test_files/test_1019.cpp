// File: test/test_getAllTestsSorted_1019.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_test_case_registry_impl.hpp>

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Exactly;
using ::testing::InSequence;

namespace Catch {

// Minimal mock for IConfig that only needs to participate in runOrder().
// We provide trivial concrete implementations for other pure virtuals so the
// type is instantiable, but we never call them in these tests.
class MockConfig_1019 : public IConfig {
public:
    // The method exercised by getAllTestsSorted
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));

    // --- Trivial implementations for the rest of IConfig's pure virtuals ---
    // The exact return values are irrelevant to these tests.
    const StringRef name() const override { static StringRef n{""}; return n; }
    bool allowThrows() const override { return true; }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporters; }
    double minDuration() const override { return 0.0; }
    TestSpec const& testSpec() const override { static TestSpec ts; return ts; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> v; return v;
    }
    uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    ColourMode defaultColourMode() const override { return ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> v; return v;
    }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
};

} // namespace Catch

// ------------------------ Test Fixture ------------------------

class GetAllTestsSorted_1019 : public ::testing::Test {
protected:
    Catch::TestRegistry registry_; // SUT
};

// ------------------------ Tests ------------------------

// 1) Boundary/normal: Empty registry should return an empty vector.
TEST_F(GetAllTestsSorted_1019, ReturnsEmptyOnEmptyRegistry_1019) {
    NiceMock<Catch::MockConfig_1019> cfg;

    // Choose any order; real value doesn't matter when there are no tests.
    ON_CALL(cfg, runOrder()).WillByDefault(Return(Catch::TestRunOrder::Declared));

    // Expect at least 1 call; on first build path it will be 2 calls (see test below),
    // but we keep this one focused on emptiness.
    auto const& out = registry_.getAllTestsSorted(cfg);
    EXPECT_TRUE(out.empty());
}

// 2) External interaction: First call invokes runOrder() twice (condition + assignment).
TEST_F(GetAllTestsSorted_1019, CallsRunOrderTwiceOnFirstBuild_1019) {
    NiceMock<Catch::MockConfig_1019> cfg;

    // Run order chosen arbitrarily.
    EXPECT_CALL(cfg, runOrder())
        .Times(Exactly(2))
        .WillRepeatedly(Return(Catch::TestRunOrder::Declared));

    auto const& out = registry_.getAllTestsSorted(cfg);
    (void)out; // silence unused warning
}

// 3) Cache behavior: With warm cache and same order, only one runOrder() call (condition only).
TEST_F(GetAllTestsSorted_1019, CallsRunOrderOnceWhenCacheHot_1019) {
    NiceMock<Catch::MockConfig_1019> cfg;

    {
        // First call builds the cache: expect 2 calls.
        EXPECT_CALL(cfg, runOrder())
            .Times(Exactly(2))
            .WillRepeatedly(Return(Catch::TestRunOrder::Declared));
        auto const& first = registry_.getAllTestsSorted(cfg);
        (void)first;
        ::testing::Mock::VerifyAndClearExpectations(&cfg);
    }

    {
        // Second call with SAME order: expect exactly 1 call (the condition check).
        EXPECT_CALL(cfg, runOrder())
            .Times(Exactly(1))
            .WillRepeatedly(Return(Catch::TestRunOrder::Declared));
        auto const& second = registry_.getAllTestsSorted(cfg);
        (void)second;
    }
}

// 4) Cache refresh when order changes: expect 2 calls again on that call.
TEST_F(GetAllTestsSorted_1019, RebuildsWhenRunOrderChanges_1019) {
    NiceMock<Catch::MockConfig_1019> cfg;

    {
        // Build initial cache with Declared
        EXPECT_CALL(cfg, runOrder())
            .Times(Exactly(2))
            .WillRepeatedly(Return(Catch::TestRunOrder::Declared));
        auto const& first = registry_.getAllTestsSorted(cfg);
        (void)first;
        ::testing::Mock::VerifyAndClearExpectations(&cfg);
    }

    {
        // Change to LexicographicallySorted (or any different value)
        EXPECT_CALL(cfg, runOrder())
            .Times(Exactly(2))
            .WillRepeatedly(Return(Catch::TestRunOrder::LexicographicallySorted));
        auto const& second = registry_.getAllTestsSorted(cfg);
        (void)second;
    }
}

// 5) Returned reference stability: subsequent calls return the same underlying container.
TEST_F(GetAllTestsSorted_1019, ReturnsStableReferenceAcrossCalls_1019) {
    NiceMock<Catch::MockConfig_1019> cfg;

    // First build (2 calls expected)
    EXPECT_CALL(cfg, runOrder())
        .Times(Exactly(2))
        .WillRepeatedly(Return(Catch::TestRunOrder::Declared));
    auto const* first_ptr = &registry_.getAllTestsSorted(cfg);
    ::testing::Mock::VerifyAndClearExpectations(&cfg);

    // Warm cache path (1 call expected)
    EXPECT_CALL(cfg, runOrder())
        .Times(Exactly(1))
        .WillRepeatedly(Return(Catch::TestRunOrder::Declared));
    auto const* second_ptr = &registry_.getAllTestsSorted(cfg);

    // The address of the referenced vector should be stable (same member returned).
    EXPECT_EQ(first_ptr, second_ptr);
}
