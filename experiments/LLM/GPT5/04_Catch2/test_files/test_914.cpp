// File: tests/benchmark_operator_assign_tests_914.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the amalgamated Catch2 header so we use the real public interface
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::Return;

namespace {

class MockConfig914 : public Catch::IConfig {
public:
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));

    // The rest of IConfig’s virtuals are not used in these tests.
    // Provide safe defaults to avoid accidental calls.
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

struct CountingFunctor914 {
    int* counter;
    // Accept whatever argument type Catch passes (e.g., Chronometer),
    // without depending on its definition.
    template <typename Any>
    void operator()(Any&&) const {
        ++(*counter);
    }
};

class BenchmarkAssignTest_914 : public ::testing::Test {
protected:
    const Catch::IConfig* prevConfig_ = nullptr;
    MockConfig914 cfg_;

    void SetUp() override {
        // Save current config (if any) and install our mock.
        prevConfig_ = Catch::getCurrentContext().getConfig();
        // Provide safe defaults for unused methods to prevent surprises.
        ON_CALL(cfg_, allowThrows).WillByDefault(Return(true));
        ON_CALL(cfg_, includeSuccessfulResults).WillByDefault(Return(true));
        ON_CALL(cfg_, shouldDebugBreak).WillByDefault(Return(false));
        ON_CALL(cfg_, warnAboutMissingAssertions).WillByDefault(Return(false));
        ON_CALL(cfg_, warnAboutUnmatchedTestSpecs).WillByDefault(Return(false));
        ON_CALL(cfg_, zeroTestsCountAsSuccess).WillByDefault(Return(false));
        ON_CALL(cfg_, abortAfter).WillByDefault(Return(0));
        ON_CALL(cfg_, showInvisibles).WillByDefault(Return(false));
        ON_CALL(cfg_, benchmarkNoAnalysis).WillByDefault(Return(false));
        ON_CALL(cfg_, benchmarkSamples).WillByDefault(Return(1u));
        ON_CALL(cfg_, benchmarkConfidenceInterval).WillByDefault(Return(0.95));
        ON_CALL(cfg_, benchmarkResamples).WillByDefault(Return(1u));
        ON_CALL(cfg_, benchmarkWarmupTime)
            .WillByDefault(Return(std::chrono::milliseconds{0}));

        Catch::getCurrentMutableContext().setConfig(&cfg_);
    }

    void TearDown() override {
        // Restore previous config
        Catch::getCurrentMutableContext().setConfig(prevConfig_);
    }
};

} // namespace

// --- Tests ---

// Normal operation: when skipBenchmarks() == false, operator= should trigger a run,
// which we observe by our callable being invoked at least once.
TEST_F(BenchmarkAssignTest_914, AssignRunsCallableWhenNotSkipped_914) {
    using Catch::Benchmark::Benchmark;

    int count = 0;
    CountingFunctor914 fn{&count};

    // Start with a named Benchmark instance; the initial functor is irrelevant here.
    Benchmark bench{std::string{"assign-run-914"}};

    EXPECT_CALL(cfg_, skipBenchmarks()).WillOnce(Return(false));

    // Assignment should trigger an internal run, which should call our functor.
    bench = fn;

    // We do not assume how many invocations happen — only that it ran at least once.
    EXPECT_GT(count, 0) << "Expected callable to be invoked when benchmarks are not skipped.";
}

// Boundary/exceptional path: when skipBenchmarks() == true, operator= should not run,
// so our callable must not be invoked.
TEST_F(BenchmarkAssignTest_914, AssignDoesNotRunWhenSkipped_914) {
    using Catch::Benchmark::Benchmark;

    int count = 0;
    CountingFunctor914 fn{&count};

    Benchmark bench{std::string{"assign-skip-914"}};

    EXPECT_CALL(cfg_, skipBenchmarks()).WillOnce(Return(true));

    bench = fn;

    EXPECT_EQ(count, 0) << "Callable must not be invoked when benchmarks are skipped.";
}

// API property: operator= returns *this. We verify it returns a reference to the same object.
TEST_F(BenchmarkAssignTest_914, AssignReturnsSelfReference_914) {
    using Catch::Benchmark::Benchmark;

    int count = 0;
    CountingFunctor914 fn{&count};

    Benchmark bench{std::string{"assign-self-914"}};

    // Whether it runs or not is irrelevant to this property; just return false here.
    EXPECT_CALL(cfg_, skipBenchmarks()).WillOnce(Return(false));

    Benchmark& ret = (bench = fn);
    EXPECT_EQ(&ret, &bench) << "operator= should return a reference to *this.";
}
