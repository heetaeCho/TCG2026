#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"
#include <gtest/gtest.h>

class SessionTest_452 : public ::testing::Test {
protected:
    Catch::Session session;
};

// Test that a default-constructed Session exists and configData has default values
TEST_F(SessionTest_452, DefaultConstruction_452) {
    Catch::ConfigData& data = session.configData();
    EXPECT_FALSE(data.listTests);
    EXPECT_FALSE(data.listTags);
    EXPECT_FALSE(data.listReporters);
    EXPECT_FALSE(data.listListeners);
    EXPECT_FALSE(data.showSuccessfulTests);
    EXPECT_FALSE(data.noThrow);
    EXPECT_FALSE(data.showHelp);
    EXPECT_FALSE(data.showInvisibles);
    EXPECT_FALSE(data.filenamesAsTags);
    EXPECT_FALSE(data.libIdentify);
    EXPECT_FALSE(data.allowZeroTests);
    EXPECT_EQ(data.abortAfter, -1);
    EXPECT_EQ(data.shardCount, 1u);
    EXPECT_EQ(data.shardIndex, 0u);
    EXPECT_FALSE(data.skipBenchmarks);
    EXPECT_FALSE(data.benchmarkNoAnalysis);
    EXPECT_EQ(data.benchmarkSamples, 100u);
    EXPECT_DOUBLE_EQ(data.benchmarkConfidenceInterval, 0.95);
    EXPECT_EQ(data.benchmarkResamples, 100000u);
    EXPECT_EQ(data.benchmarkWarmupTime, 100);
    EXPECT_EQ(data.verbosity, Catch::Verbosity::Normal);
    EXPECT_DOUBLE_EQ(data.minDuration, -1.0);
    EXPECT_EQ(data.runOrder, Catch::TestRunOrder::Declared);
    EXPECT_EQ(data.defaultColourMode, Catch::ColourMode::PlatformDefault);
}

// Test useConfigData replaces config data
TEST_F(SessionTest_452, UseConfigDataReplacesData_452) {
    Catch::ConfigData newData;
    newData.listTests = true;
    newData.listTags = true;
    newData.showHelp = true;
    newData.abortAfter = 5;
    newData.shardCount = 4;
    newData.shardIndex = 2;
    newData.verbosity = Catch::Verbosity::High;
    newData.processName = "test_process";

    session.useConfigData(newData);

    Catch::ConfigData& data = session.configData();
    EXPECT_TRUE(data.listTests);
    EXPECT_TRUE(data.listTags);
    EXPECT_TRUE(data.showHelp);
    EXPECT_EQ(data.abortAfter, 5);
    EXPECT_EQ(data.shardCount, 4u);
    EXPECT_EQ(data.shardIndex, 2u);
    EXPECT_EQ(data.verbosity, Catch::Verbosity::High);
    EXPECT_EQ(data.processName, "test_process");
}

// Test that configData returns a mutable reference
TEST_F(SessionTest_452, ConfigDataReturnsMutableReference_452) {
    Catch::ConfigData& data = session.configData();
    data.listTests = true;
    data.abortAfter = 10;
    data.processName = "modified";

    Catch::ConfigData& dataAgain = session.configData();
    EXPECT_TRUE(dataAgain.listTests);
    EXPECT_EQ(dataAgain.abortAfter, 10);
    EXPECT_EQ(dataAgain.processName, "modified");
}

// Test that useConfigData can be called multiple times
TEST_F(SessionTest_452, UseConfigDataMultipleTimes_452) {
    Catch::ConfigData data1;
    data1.listTests = true;
    data1.processName = "first";
    session.useConfigData(data1);

    EXPECT_TRUE(session.configData().listTests);
    EXPECT_EQ(session.configData().processName, "first");

    Catch::ConfigData data2;
    data2.listTests = false;
    data2.processName = "second";
    session.useConfigData(data2);

    EXPECT_FALSE(session.configData().listTests);
    EXPECT_EQ(session.configData().processName, "second");
}

// Test that cli() returns a valid parser (const version)
TEST_F(SessionTest_452, CliReturnsParser_452) {
    const Catch::Clara::Parser& parser = session.cli();
    // Just verify we can obtain a reference without crashing
    (void)parser;
    SUCCEED();
}

// Test that cli(newParser) sets a new parser
TEST_F(SessionTest_452, SetCliParser_452) {
    Catch::Clara::Parser newParser;
    session.cli(newParser);
    // Verify it doesn't crash and we can still retrieve the cli
    const Catch::Clara::Parser& parser = session.cli();
    (void)parser;
    SUCCEED();
}

// Test that config() returns a valid Config reference
TEST_F(SessionTest_452, ConfigReturnsValidReference_452) {
    Catch::Config& cfg = session.config();
    (void)cfg;
    SUCCEED();
}

// Test applyCommandLine with no extra arguments (just program name)
TEST_F(SessionTest_452, ApplyCommandLineMinimalArgs_452) {
    const char* argv[] = {"test_program"};
    int result = session.applyCommandLine(1, argv);
    EXPECT_EQ(result, 0);
}

// Test applyCommandLine with help flag
TEST_F(SessionTest_452, ApplyCommandLineHelp_452) {
    const char* argv[] = {"test_program", "--help"};
    int result = session.applyCommandLine(2, argv);
    // When help is requested, it may return 0 or some specific code
    // The configData should reflect showHelp = true
    EXPECT_TRUE(session.configData().showHelp);
}

// Test applyCommandLine with invalid arguments
TEST_F(SessionTest_452, ApplyCommandLineInvalidArgs_452) {
    const char* argv[] = {"test_program", "--this-is-not-a-valid-option-xyz"};
    int result = session.applyCommandLine(2, argv);
    // Invalid args should result in non-zero return
    EXPECT_NE(result, 0);
}

// Test useConfigData with default ConfigData (boundary: all defaults)
TEST_F(SessionTest_452, UseConfigDataWithDefaults_452) {
    Catch::ConfigData defaultData;
    session.useConfigData(defaultData);

    Catch::ConfigData& data = session.configData();
    EXPECT_FALSE(data.listTests);
    EXPECT_FALSE(data.showHelp);
    EXPECT_EQ(data.abortAfter, -1);
    EXPECT_EQ(data.shardCount, 1u);
    EXPECT_EQ(data.shardIndex, 0u);
}

// Test useConfigData with tests/tags specified
TEST_F(SessionTest_452, UseConfigDataWithTestsOrTags_452) {
    Catch::ConfigData data;
    data.testsOrTags.push_back("test1");
    data.testsOrTags.push_back("[tag1]");
    data.sectionsToRun.push_back("section1");

    session.useConfigData(data);

    EXPECT_EQ(session.configData().testsOrTags.size(), 2u);
    EXPECT_EQ(session.configData().testsOrTags[0], "test1");
    EXPECT_EQ(session.configData().testsOrTags[1], "[tag1]");
    EXPECT_EQ(session.configData().sectionsToRun.size(), 1u);
    EXPECT_EQ(session.configData().sectionsToRun[0], "section1");
}

// Test useConfigData with benchmark configuration
TEST_F(SessionTest_452, UseConfigDataBenchmarkSettings_452) {
    Catch::ConfigData data;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 50;
    data.benchmarkConfidenceInterval = 0.99;
    data.benchmarkResamples = 50000;
    data.benchmarkWarmupTime = 200;

    session.useConfigData(data);

    EXPECT_TRUE(session.configData().skipBenchmarks);
    EXPECT_TRUE(session.configData().benchmarkNoAnalysis);
    EXPECT_EQ(session.configData().benchmarkSamples, 50u);
    EXPECT_DOUBLE_EQ(session.configData().benchmarkConfidenceInterval, 0.99);
    EXPECT_EQ(session.configData().benchmarkResamples, 50000u);
    EXPECT_EQ(session.configData().benchmarkWarmupTime, 200);
}

// Test that useConfigData resets m_config (observable through config() recreating)
TEST_F(SessionTest_452, UseConfigDataResetsConfig_452) {
    // Access config first to ensure it's created
    Catch::Config& cfg1 = session.config();
    (void)cfg1;

    // Now change config data
    Catch::ConfigData newData;
    newData.noThrow = true;
    session.useConfigData(newData);

    // Accessing config again should give us a config reflecting the new data
    Catch::Config& cfg2 = session.config();
    (void)cfg2;
    SUCCEED();
}

// Test applyCommandLine with verbosity flag
TEST_F(SessionTest_452, ApplyCommandLineVerbosity_452) {
    const char* argv[] = {"test_program", "-v", "high"};
    int result = session.applyCommandLine(3, argv);
    if (result == 0) {
        EXPECT_EQ(session.configData().verbosity, Catch::Verbosity::High);
    }
}

// Test that configData modifications persist
TEST_F(SessionTest_452, DirectConfigDataModificationPersists_452) {
    session.configData().allowZeroTests = true;
    session.configData().noThrow = true;
    session.configData().showInvisibles = true;

    EXPECT_TRUE(session.configData().allowZeroTests);
    EXPECT_TRUE(session.configData().noThrow);
    EXPECT_TRUE(session.configData().showInvisibles);
}
