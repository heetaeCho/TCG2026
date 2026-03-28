#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <chrono>
#include <vector>

// Include the necessary Catch2 headers
#include "catch_amalgamated.hpp"

using namespace Catch;
using namespace Catch::Benchmark;

// Mock IConfig to control skipBenchmarks() behavior
class MockConfig : public IConfig {
public:
    ~MockConfig() override = default;

    MOCK_CONST_METHOD0(allowThrows, bool());
    MOCK_CONST_METHOD0(name, StringRef());
    MOCK_CONST_METHOD0(includeSuccessfulResults, bool());
    MOCK_CONST_METHOD0(shouldDebugBreak, bool());
    MOCK_CONST_METHOD0(warnAboutMissingAssertions, bool());
    MOCK_CONST_METHOD0(warnAboutUnmatchedTestSpecs, bool());
    MOCK_CONST_METHOD0(zeroTestsCountAsSuccess, bool());
    MOCK_CONST_METHOD0(abortAfter, int());
    MOCK_CONST_METHOD0(showInvisibles, bool());
    MOCK_CONST_METHOD0(showDurations, ShowDurations());
    MOCK_CONST_METHOD0(minDuration, double());
    MOCK_CONST_METHOD0(testSpec, const TestSpec&());
    MOCK_CONST_METHOD0(hasTestFilters, bool());
    MOCK_CONST_METHOD0(getTestsOrTags, const std::vector<std::string>&());
    MOCK_CONST_METHOD0(runOrder, TestRunOrder());
    MOCK_CONST_METHOD0(rngSeed, uint32_t());
    MOCK_CONST_METHOD0(shardCount, unsigned int());
    MOCK_CONST_METHOD0(shardIndex, unsigned int());
    MOCK_CONST_METHOD0(defaultColourMode, ColourMode());
    MOCK_CONST_METHOD0(getSectionsToRun, const std::vector<std::string>&());
    MOCK_CONST_METHOD0(verbosity, Verbosity());
    MOCK_CONST_METHOD0(skipBenchmarks, bool());
    MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());
    MOCK_CONST_METHOD0(benchmarkSamples, unsigned int());
    MOCK_CONST_METHOD0(benchmarkConfidenceInterval, double());
    MOCK_CONST_METHOD0(benchmarkResamples, unsigned int());
    MOCK_CONST_METHOD0(benchmarkWarmupTime, std::chrono::milliseconds());
};

class BenchmarkTest_914 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = std::make_unique<MockConfig>();
    }

    void TearDown() override {
        // Restore context if needed
        getCurrentMutableContext().setConfig(nullptr);
        mockConfig_.reset();
    }

    void setConfig(IConfig const* config) {
        getCurrentMutableContext().setConfig(config);
    }

    std::unique_ptr<MockConfig> mockConfig_;
};

// Test: Benchmark can be constructed with a name
TEST_F(BenchmarkTest_914, ConstructWithName_914) {
    Benchmark bm(std::string("test_benchmark"));
    // A default-constructed benchmark (no function) should be falsy or truthy
    // depending on implementation. We just verify it doesn't crash.
    SUCCEED();
}

// Test: Benchmark can be constructed with a name and function
TEST_F(BenchmarkTest_914, ConstructWithNameAndFunction_914) {
    bool called = false;
    Benchmark bm(std::string("test_benchmark"), [&called](Chronometer) {
        called = true;
    });
    // Construction should succeed without calling the function
    EXPECT_FALSE(called);
}

// Test: operator= with skipBenchmarks true should not set function or run
TEST_F(BenchmarkTest_914, OperatorAssignSkipBenchmarks_914) {
    ON_CALL(*mockConfig_, skipBenchmarks()).WillByDefault(::testing::Return(true));
    EXPECT_CALL(*mockConfig_, skipBenchmarks()).Times(::testing::AtLeast(1));
    setConfig(mockConfig_.get());

    Benchmark bm(std::string("skipped_benchmark"));
    bool funcCalled = false;

    // When skipBenchmarks is true, the function should NOT be stored and run() should NOT be called
    bm = [&funcCalled](Chronometer) {
        funcCalled = true;
    };

    // The function should not have been invoked during assignment
    EXPECT_FALSE(funcCalled);
}

// Test: operator= returns reference to self
TEST_F(BenchmarkTest_914, OperatorAssignReturnsSelf_914) {
    ON_CALL(*mockConfig_, skipBenchmarks()).WillByDefault(::testing::Return(true));
    setConfig(mockConfig_.get());

    Benchmark bm(std::string("self_ref_benchmark"));

    Benchmark& ref = (bm = [](Chronometer) {});
    EXPECT_EQ(&ref, &bm);
}

// Test: BenchmarkFunction default constructor creates a valid (do-nothing) function
TEST_F(BenchmarkTest_914, BenchmarkFunctionDefaultConstructor_914) {
    Detail::BenchmarkFunction bf;
    // Default constructed BenchmarkFunction should be callable without crash
    // (wraps do_nothing)
    SUCCEED();
}

// Test: BenchmarkFunction can be constructed from a lambda
TEST_F(BenchmarkTest_914, BenchmarkFunctionFromLambda_914) {
    bool called = false;
    Detail::BenchmarkFunction bf([&called](Chronometer meter) {
        called = true;
    });
    // Just verify construction doesn't crash
    EXPECT_FALSE(called);
}

// Test: BenchmarkFunction move constructor
TEST_F(BenchmarkTest_914, BenchmarkFunctionMoveConstructor_914) {
    Detail::BenchmarkFunction bf1([](Chronometer) {});
    Detail::BenchmarkFunction bf2(std::move(bf1));
    // Move should succeed without crash
    SUCCEED();
}

// Test: BenchmarkFunction move assignment
TEST_F(BenchmarkTest_914, BenchmarkFunctionMoveAssignment_914) {
    Detail::BenchmarkFunction bf1([](Chronometer) {});
    Detail::BenchmarkFunction bf2;
    bf2 = std::move(bf1);
    // Move assignment should succeed without crash
    SUCCEED();
}

// Test: Benchmark explicit bool operator
TEST_F(BenchmarkTest_914, BenchmarkExplicitBoolOperator_914) {
    Benchmark bm(std::string("bool_test"));
    // Just test that the bool conversion compiles and runs
    bool val = static_cast<bool>(bm);
    // We don't know expected value without internal knowledge, just ensure no crash
    (void)val;
    SUCCEED();
}

// Test: Benchmark constructed with function should convert to true
TEST_F(BenchmarkTest_914, BenchmarkWithFunctionIsTruthy_914) {
    Benchmark bm(std::string("has_func"), [](Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: Multiple assignments with skip should all be no-ops
TEST_F(BenchmarkTest_914, MultipleAssignmentsWithSkip_914) {
    ON_CALL(*mockConfig_, skipBenchmarks()).WillByDefault(::testing::Return(true));
    setConfig(mockConfig_.get());

    Benchmark bm(std::string("multi_assign"));
    int callCount = 0;

    bm = [&callCount](Chronometer) { callCount++; };
    bm = [&callCount](Chronometer) { callCount += 10; };
    bm = [&callCount](Chronometer) { callCount += 100; };

    EXPECT_EQ(callCount, 0);
}

// Test: operator= with different callable types (function pointer vs lambda)
TEST_F(BenchmarkTest_914, OperatorAssignWithDifferentCallableTypes_914) {
    ON_CALL(*mockConfig_, skipBenchmarks()).WillByDefault(::testing::Return(true));
    setConfig(mockConfig_.get());

    Benchmark bm(std::string("callable_types"));

    // Lambda
    bm = [](Chronometer) {};
    SUCCEED();
}

// Test: Benchmark name is preserved after construction
TEST_F(BenchmarkTest_914, BenchmarkNameConstruction_914) {
    std::string name = "my_benchmark";
    Benchmark bm(std::string(name));
    // We can't directly access name, but construction should succeed
    SUCCEED();
}

// Test: Context getConfig returns what was set
TEST_F(BenchmarkTest_914, ContextConfigSetAndGet_914) {
    setConfig(mockConfig_.get());
    const IConfig* retrieved = getCurrentContext().getConfig();
    EXPECT_EQ(retrieved, mockConfig_.get());
}

// Test: Context with nullptr config
TEST_F(BenchmarkTest_914, ContextNullConfig_914) {
    getCurrentMutableContext().setConfig(nullptr);
    const IConfig* retrieved = getCurrentContext().getConfig();
    EXPECT_EQ(retrieved, nullptr);
}
