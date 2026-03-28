#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

class SessionTest_453 : public ::testing::Test {
protected:
    void SetUp() override {
        // Session is non-copyable, so we create fresh instances per test
    }

    void TearDown() override {
    }
};

// Test: Default construction of Session
TEST_F(SessionTest_453, DefaultConstruction_453) {
    Catch::Session session;
    // Session should be constructible without throwing
    SUCCEED();
}

// Test: configData returns a reference and has expected defaults
TEST_F(SessionTest_453, ConfigDataDefaultValues_453) {
    Catch::Session session;
    Catch::ConfigData& data = session.configData();
    
    EXPECT_EQ(data.waitForKeypress, Catch::WaitForKeypress::Never);
    EXPECT_FALSE(data.listTests);
    EXPECT_FALSE(data.listTags);
    EXPECT_FALSE(data.listReporters);
    EXPECT_FALSE(data.listListeners);
    EXPECT_FALSE(data.showHelp);
    EXPECT_FALSE(data.noThrow);
    EXPECT_FALSE(data.libIdentify);
    EXPECT_FALSE(data.allowZeroTests);
    EXPECT_EQ(data.abortAfter, -1);
    EXPECT_EQ(data.shardCount, 1u);
    EXPECT_EQ(data.shardIndex, 0u);
    EXPECT_FALSE(data.skipBenchmarks);
    EXPECT_FALSE(data.benchmarkNoAnalysis);
    EXPECT_EQ(data.benchmarkSamples, 100u);
    EXPECT_EQ(data.benchmarkResamples, 100000u);
    EXPECT_EQ(data.benchmarkWarmupTime, 100);
    EXPECT_EQ(data.verbosity, Catch::Verbosity::Normal);
    EXPECT_EQ(data.showDurations, Catch::ShowDurations::DefaultForReporter);
    EXPECT_DOUBLE_EQ(data.minDuration, -1.0);
    EXPECT_EQ(data.runOrder, Catch::TestRunOrder::Declared);
    EXPECT_EQ(data.defaultColourMode, Catch::ColourMode::PlatformDefault);
}

// Test: configData is modifiable
TEST_F(SessionTest_453, ConfigDataIsModifiable_453) {
    Catch::Session session;
    Catch::ConfigData& data = session.configData();
    
    data.listTests = true;
    EXPECT_TRUE(session.configData().listTests);
    
    data.abortAfter = 5;
    EXPECT_EQ(session.configData().abortAfter, 5);
}

// Test: useConfigData applies the provided config
TEST_F(SessionTest_453, UseConfigDataAppliesConfig_453) {
    Catch::Session session;
    Catch::ConfigData configData;
    configData.listTests = true;
    configData.abortAfter = 3;
    configData.allowZeroTests = true;
    
    session.useConfigData(configData);
    
    EXPECT_TRUE(session.configData().listTests);
    EXPECT_EQ(session.configData().abortAfter, 3);
    EXPECT_TRUE(session.configData().allowZeroTests);
}

// Test: cli() returns a parser (const version)
TEST_F(SessionTest_453, CliReturnsParser_453) {
    Catch::Session session;
    const Clara::Parser& parser = session.cli();
    // Just verify we can obtain the parser reference without issues
    SUCCEED();
}

// Test: cli() can be set with a new parser
TEST_F(SessionTest_453, CliCanBeSet_453) {
    Catch::Session session;
    Clara::Parser newParser;
    session.cli(newParser);
    // Verify it doesn't crash
    const Clara::Parser& parser = session.cli();
    SUCCEED();
}

// Test: applyCommandLine with no arguments (just program name)
TEST_F(SessionTest_453, ApplyCommandLineNoArgs_453) {
    Catch::Session session;
    const char* argv[] = { "test_program" };
    int result = session.applyCommandLine(1, argv);
    EXPECT_EQ(result, 0);
}

// Test: applyCommandLine with help flag
TEST_F(SessionTest_453, ApplyCommandLineWithHelp_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--help" };
    int result = session.applyCommandLine(2, argv);
    // When help is requested, it may return 0 but set showHelp
    EXPECT_TRUE(session.configData().showHelp || result == 0);
}

// Test: applyCommandLine with invalid arguments
TEST_F(SessionTest_453, ApplyCommandLineWithInvalidArgs_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--not-a-real-option-xyz" };
    int result = session.applyCommandLine(2, argv);
    // Invalid options should return non-zero
    EXPECT_NE(result, 0);
}

// Test: applyCommandLine with list-tests
TEST_F(SessionTest_453, ApplyCommandLineListTests_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--list-tests" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().listTests);
}

// Test: applyCommandLine with list-tags
TEST_F(SessionTest_453, ApplyCommandLineListTags_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--list-tags" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().listTags);
}

// Test: applyCommandLine with abort after N
TEST_F(SessionTest_453, ApplyCommandLineAbortAfter_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "-x", "3" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(session.configData().abortAfter, 3);
}

// Test: applyCommandLine with nothrow
TEST_F(SessionTest_453, ApplyCommandLineNoThrow_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--nothrow" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().noThrow);
}

// Test: applyCommandLine with verbosity high
TEST_F(SessionTest_453, ApplyCommandLineVerbosityHigh_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "-v", "high" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(session.configData().verbosity, Catch::Verbosity::High);
}

// Test: run with no test cases and allowZeroTests
TEST_F(SessionTest_453, RunWithNoTestsAllowed_453) {
    Catch::Session session;
    session.configData().allowZeroTests = true;
    session.configData().waitForKeypress = Catch::WaitForKeypress::Never;
    int exitCode = session.run();
    EXPECT_EQ(exitCode, 0);
}

// Test: run with no tests and not allowing zero tests
TEST_F(SessionTest_453, RunWithNoTestsNotAllowed_453) {
    Catch::Session session;
    session.configData().allowZeroTests = false;
    session.configData().waitForKeypress = Catch::WaitForKeypress::Never;
    // With no registered tests and allowZeroTests=false, it may return non-zero
    int exitCode = session.run();
    // The behavior depends on whether there are registered tests
    // We just ensure it completes without crashing
    SUCCEED();
}

// Test: run with argc/argv template version
TEST_F(SessionTest_453, RunWithArgcArgv_453) {
    Catch::Session session;
    const char* argv[] = { "test_program" };
    session.configData().allowZeroTests = true;
    session.configData().waitForKeypress = Catch::WaitForKeypress::Never;
    session.applyCommandLine(1, argv);
    int exitCode = session.run();
    EXPECT_EQ(exitCode, 0);
}

// Test: config() returns a reference
TEST_F(SessionTest_453, ConfigReturnsReference_453) {
    Catch::Session session;
    // Apply command line first to ensure config is initialized
    const char* argv[] = { "test_program" };
    session.applyCommandLine(1, argv);
    Catch::Config& config = session.config();
    SUCCEED();
}

// Test: WaitForKeypress Never does not block
TEST_F(SessionTest_453, WaitForKeypressNeverDoesNotBlock_453) {
    Catch::Session session;
    session.configData().waitForKeypress = Catch::WaitForKeypress::Never;
    session.configData().allowZeroTests = true;
    int exitCode = session.run();
    // Should complete without waiting
    EXPECT_EQ(exitCode, 0);
}

// Test: useConfigData overrides previous settings
TEST_F(SessionTest_453, UseConfigDataOverridesPrevious_453) {
    Catch::Session session;
    session.configData().listTests = true;
    
    Catch::ConfigData newConfig;
    newConfig.listTests = false;
    newConfig.listTags = true;
    session.useConfigData(newConfig);
    
    EXPECT_FALSE(session.configData().listTests);
    EXPECT_TRUE(session.configData().listTags);
}

// Test: applyCommandLine with test spec
TEST_F(SessionTest_453, ApplyCommandLineWithTestSpec_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "SomeTestName" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(session.configData().testsOrTags.empty());
    EXPECT_EQ(session.configData().testsOrTags[0], "SomeTestName");
}

// Test: applyCommandLine with multiple test specs
TEST_F(SessionTest_453, ApplyCommandLineMultipleTestSpecs_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "Test1", "Test2" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_GE(session.configData().testsOrTags.size(), 2u);
}

// Test: applyCommandLine with random seed
TEST_F(SessionTest_453, ApplyCommandLineWithSeed_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--rng-seed", "42" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(session.configData().rngSeed, 42u);
}

// Test: applyCommandLine with order rand
TEST_F(SessionTest_453, ApplyCommandLineWithOrderRand_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--order", "rand" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(session.configData().runOrder, Catch::TestRunOrder::Randomized);
}

// Test: Multiple runs on same session
TEST_F(SessionTest_453, MultipleRuns_453) {
    Catch::Session session;
    session.configData().allowZeroTests = true;
    session.configData().waitForKeypress = Catch::WaitForKeypress::Never;
    
    int exitCode1 = session.run();
    int exitCode2 = session.run();
    
    EXPECT_EQ(exitCode1, exitCode2);
}

// Test: applyCommandLine with libidentify
TEST_F(SessionTest_453, ApplyCommandLineLibIdentify_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--libidentify" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().libIdentify);
}

// Test: Benchmark configuration via command line
TEST_F(SessionTest_453, ApplyCommandLineBenchmarkSamples_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "--benchmark-samples", "200" };
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(session.configData().benchmarkSamples, 200u);
}

// Test: showSuccessfulTests via command line
TEST_F(SessionTest_453, ApplyCommandLineShowSuccessfulTests_453) {
    Catch::Session session;
    const char* argv[] = { "test_program", "-s" };
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().showSuccessfulTests);
}
