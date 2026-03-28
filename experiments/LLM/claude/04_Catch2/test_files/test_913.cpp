#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <chrono>

#include "catch_amalgamated.hpp"

using namespace Catch;
using namespace Catch::Benchmark;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::AtLeast;
using ::testing::NiceMock;

// Mock for IResultCapture
class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef, const SourceLineInfo&, Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&&), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef, const SourceLineInfo&), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo&, const ITransientExpression&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo&, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo&, ResultWas::OfType, AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class BenchmarkTest_913 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test: Benchmark construction with name only
TEST_F(BenchmarkTest_913, ConstructWithNameOnly_913) {
    Catch::Benchmark::Benchmark bm(std::string("TestBenchmark"));
    // A benchmark constructed with only a name should not be "truthy"
    // since no function has been assigned
    EXPECT_FALSE(static_cast<bool>(bm));
}

// Test: Benchmark construction with name and function
TEST_F(BenchmarkTest_913, ConstructWithNameAndFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("TestBenchmark"), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: Benchmark operator= assigns a function
TEST_F(BenchmarkTest_913, OperatorAssignFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("TestBenchmark"));
    EXPECT_FALSE(static_cast<bool>(bm));
    
    bm = [](Catch::Benchmark::Chronometer) {};
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: Benchmark with empty name
TEST_F(BenchmarkTest_913, ConstructWithEmptyName_913) {
    Catch::Benchmark::Benchmark bm(std::string(""));
    EXPECT_FALSE(static_cast<bool>(bm));
}

// Test: Benchmark move construction preserves name and function
TEST_F(BenchmarkTest_913, MoveConstruction_913) {
    Catch::Benchmark::Benchmark bm(std::string("MoveBenchmark"), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
    
    Catch::Benchmark::Benchmark bm2(std::move(bm));
    EXPECT_TRUE(static_cast<bool>(bm2));
}

// Test: Benchmark operator= with lambda that does actual work
TEST_F(BenchmarkTest_913, OperatorAssignWithWorkFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("WorkBenchmark"));
    
    int counter = 0;
    bm = [&counter](Catch::Benchmark::Chronometer meter) {
        meter.measure([&counter] { ++counter; });
    };
    
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: Benchmark explicit bool conversion - no function
TEST_F(BenchmarkTest_913, ExplicitBoolConversionNoFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("NoBool"));
    bool result = static_cast<bool>(bm);
    EXPECT_FALSE(result);
}

// Test: Benchmark explicit bool conversion - with function
TEST_F(BenchmarkTest_913, ExplicitBoolConversionWithFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("WithBool"), [](Catch::Benchmark::Chronometer) {});
    bool result = static_cast<bool>(bm);
    EXPECT_TRUE(result);
}

// Test: Reassigning function via operator=
TEST_F(BenchmarkTest_913, ReassignFunction_913) {
    Catch::Benchmark::Benchmark bm(std::string("Reassign"), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
    
    // Reassign with a different function
    bm = [](Catch::Benchmark::Chronometer meter) {
        meter.measure([] { return 42; });
    };
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: BenchmarkInfo structure values
TEST_F(BenchmarkTest_913, BenchmarkInfoDefaultValues_913) {
    BenchmarkInfo info{
        "test_benchmark",
        100.0,
        10,
        100,
        10000,
        1.0,
        0.5
    };
    
    EXPECT_EQ(info.name, "test_benchmark");
    EXPECT_DOUBLE_EQ(info.estimatedDuration, 100.0);
    EXPECT_EQ(info.iterations, 10);
    EXPECT_EQ(info.samples, 100u);
    EXPECT_EQ(info.resamples, 10000u);
    EXPECT_DOUBLE_EQ(info.clockResolution, 1.0);
    EXPECT_DOUBLE_EQ(info.clockCost, 0.5);
}

// Test: BenchmarkInfo with zero values
TEST_F(BenchmarkTest_913, BenchmarkInfoZeroValues_913) {
    BenchmarkInfo info{
        "",
        0.0,
        0,
        0,
        0,
        0.0,
        0.0
    };
    
    EXPECT_EQ(info.name, "");
    EXPECT_DOUBLE_EQ(info.estimatedDuration, 0.0);
    EXPECT_EQ(info.iterations, 0);
    EXPECT_EQ(info.samples, 0u);
    EXPECT_EQ(info.resamples, 0u);
}

// Test: BenchmarkInfo with large values
TEST_F(BenchmarkTest_913, BenchmarkInfoLargeValues_913) {
    BenchmarkInfo info{
        "large_benchmark",
        1e12,
        1000000,
        10000,
        100000,
        1e-9,
        1e-8
    };
    
    EXPECT_EQ(info.name, "large_benchmark");
    EXPECT_DOUBLE_EQ(info.estimatedDuration, 1e12);
    EXPECT_EQ(info.iterations, 1000000);
    EXPECT_EQ(info.samples, 10000u);
    EXPECT_EQ(info.resamples, 100000u);
}

// Test: Multiple benchmark instances are independent
TEST_F(BenchmarkTest_913, MultipleBenchmarksIndependent_913) {
    Catch::Benchmark::Benchmark bm1(std::string("Bench1"), [](Catch::Benchmark::Chronometer) {});
    Catch::Benchmark::Benchmark bm2(std::string("Bench2"));
    
    EXPECT_TRUE(static_cast<bool>(bm1));
    EXPECT_FALSE(static_cast<bool>(bm2));
}

// Test: Benchmark with long name
TEST_F(BenchmarkTest_913, BenchmarkLongName_913) {
    std::string longName(1000, 'x');
    Catch::Benchmark::Benchmark bm(std::string(longName), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test: Benchmark with special characters in name
TEST_F(BenchmarkTest_913, BenchmarkSpecialCharsInName_913) {
    Catch::Benchmark::Benchmark bm(std::string("bench!@#$%^&*()"), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
}
