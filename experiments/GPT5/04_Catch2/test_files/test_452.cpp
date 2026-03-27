// File: test_session_useConfigData_452.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// ---- Minimal forward declarations for unrelated dependencies ----
// These are only to satisfy compilation and do not simulate any internal logic.
// We never use them directly in assertions.
namespace Clara { class Parser {}; }
namespace Catch {
    // Forward-declare Config; tests don't use it directly.
    class Config;
}

// ---- Headers under test (as provided) ----
#include "Catch2/src/catch2/catch_config.hpp"
#include "Catch2/src/catch2/catch_session.hpp"

using namespace Catch;

class SessionUseConfigDataTest_452 : public ::testing::Test {
protected:
    Session session; // SUT
};

// Helper to build a non-default ConfigData for clearer assertions
static ConfigData MakeConfigDataVariant() {
    ConfigData cd;
    cd.listTests = true;
    cd.listTags = true;
    cd.listReporters = true;
    cd.listListeners = true;
    cd.showSuccessfulTests = true;
    cd.noThrow = true;
    cd.showHelp = true;
    cd.showInvisibles = true;
    cd.filenamesAsTags = true;
    cd.libIdentify = true;
    cd.allowZeroTests = true;

    cd.abortAfter = 5;
    cd.rngSeed = 123456u;
    cd.shardCount = 3u;
    cd.shardIndex = 1u;

    cd.skipBenchmarks = true;
    cd.benchmarkNoAnalysis = true;
    cd.benchmarkSamples = 7u;
    cd.benchmarkConfidenceInterval = 0.9;
    cd.benchmarkResamples = 77u;
    cd.benchmarkWarmupTime = 250;

    // Enum-like fields — keep defaults or simple variations if enums are opaque here.
    // We only test what we can read back via configData().
    cd.defaultOutputFilename = "results.txt";
    cd.processName = "my_proc";

    cd.reporterSpecifications = { ReporterSpec{"junit"}, ReporterSpec{"console"} };
    cd.testsOrTags = { "[fast]", "ParserSpec" };
    cd.sectionsToRun = { "init", "teardown" };

    return cd;
}

// [Normal operation]
// Verifies that useConfigData copies all (observable) fields into the session.
TEST_F(SessionUseConfigDataTest_452, UseConfigData_CopiesAllFields_452) {
    ConfigData input = MakeConfigDataVariant();

    EXPECT_NO_THROW(session.useConfigData(input));

    const ConfigData& actual = session.configData();

    EXPECT_TRUE(actual.listTests);
    EXPECT_TRUE(actual.listTags);
    EXPECT_TRUE(actual.listReporters);
    EXPECT_TRUE(actual.listListeners);
    EXPECT_TRUE(actual.showSuccessfulTests);
    EXPECT_TRUE(actual.noThrow);
    EXPECT_TRUE(actual.showHelp);
    EXPECT_TRUE(actual.showInvisibles);
    EXPECT_TRUE(actual.filenamesAsTags);
    EXPECT_TRUE(actual.libIdentify);
    EXPECT_TRUE(actual.allowZeroTests);

    EXPECT_EQ(actual.abortAfter, 5);
    EXPECT_EQ(actual.rngSeed, 123456u);
    EXPECT_EQ(actual.shardCount, 3u);
    EXPECT_EQ(actual.shardIndex, 1u);

    EXPECT_TRUE(actual.skipBenchmarks);
    EXPECT_TRUE(actual.benchmarkNoAnalysis);
    EXPECT_EQ(actual.benchmarkSamples, 7u);
    EXPECT_DOUBLE_EQ(actual.benchmarkConfidenceInterval, 0.9);
    EXPECT_EQ(actual.benchmarkResamples, 77u);
    EXPECT_EQ(actual.benchmarkWarmupTime, 250);

    EXPECT_EQ(actual.defaultOutputFilename, "results.txt");
    EXPECT_EQ(actual.processName, "my_proc");

    ASSERT_EQ(actual.reporterSpecifications.size(), 2u);
    EXPECT_EQ(actual.reporterSpecifications[0].name, "junit");
    EXPECT_EQ(actual.reporterSpecifications[1].name, "console");

    ASSERT_EQ(actual.testsOrTags.size(), 2u);
    EXPECT_EQ(actual.testsOrTags[0], "[fast]");
    EXPECT_EQ(actual.testsOrTags[1], "ParserSpec");

    ASSERT_EQ(actual.sectionsToRun.size(), 2u);
    EXPECT_EQ(actual.sectionsToRun[0], "init");
    EXPECT_EQ(actual.sectionsToRun[1], "teardown");
}

// [Boundary conditions]
// Ensure edge-ish/default-y values are preserved verbatim (e.g., negatives/zeros/empties).
TEST_F(SessionUseConfigDataTest_452, UseConfigData_PreservesBoundaryLikeValues_452) {
    ConfigData input; // defaults from header
    // Tweak a couple of boundary-ish fields explicitly:
    input.abortAfter = -1;             // "no abort" sentinel per header default
    input.minDuration = -1;            // default sentinel
    input.shardCount = 1u;             // default minimal valid
    input.shardIndex = 0u;             // lowest index
    input.defaultOutputFilename = "";  // empty string
    input.processName = "";            // empty string
    input.testsOrTags.clear();         // empty vector
    input.sectionsToRun.clear();       // empty vector
    input.reporterSpecifications.clear();

    session.useConfigData(input);

    const ConfigData& actual = session.configData();
    EXPECT_EQ(actual.abortAfter, -1);
    EXPECT_DOUBLE_EQ(actual.minDuration, -1);
    EXPECT_EQ(actual.shardCount, 1u);
    EXPECT_EQ(actual.shardIndex, 0u);
    EXPECT_EQ(actual.defaultOutputFilename, "");
    EXPECT_EQ(actual.processName, "");
    EXPECT_TRUE(actual.testsOrTags.empty());
    EXPECT_TRUE(actual.sectionsToRun.empty());
    EXPECT_TRUE(actual.reporterSpecifications.empty());
}

// [Exceptional/error-ish observable behavior]
// Calling useConfigData multiple times should be safe and should overwrite the stored data.
TEST_F(SessionUseConfigDataTest_452, UseConfigData_SecondCallOverwritesPrevious_452) {
    ConfigData first = MakeConfigDataVariant();
    session.useConfigData(first);

    ConfigData second;
    second.listTests = false;
    second.abortAfter = 42;
    second.processName = "second_proc";
    second.testsOrTags = { "[slow]" };

    // This must not throw and must update observable state
    EXPECT_NO_THROW(session.useConfigData(second));

    const ConfigData& actual = session.configData();
    EXPECT_FALSE(actual.listTests);
    EXPECT_EQ(actual.abortAfter, 42);
    EXPECT_EQ(actual.processName, "second_proc");

    ASSERT_EQ(actual.testsOrTags.size(), 1u);
    EXPECT_EQ(actual.testsOrTags[0], "[slow]");
}

// [Interaction/independence]
// After passing a ConfigData by const reference, later mutations to the original
// argument must not retroactively change the Session's stored config.
TEST_F(SessionUseConfigDataTest_452, UseConfigData_ArgumentLaterMutationsDoNotAffectSession_452) {
    ConfigData input = MakeConfigDataVariant();
    session.useConfigData(input);

    // Mutate the original after the call
    input.listTests = false;
    input.abortAfter = 999;
    input.testsOrTags.push_back("[mutated]");
    input.processName = "mutated_proc";

    const ConfigData& actual = session.configData();
    // Expect values remain as initially stored (copied), not reflecting later mutations.
    EXPECT_TRUE(actual.listTests);               // was true in MakeConfigDataVariant
    EXPECT_EQ(actual.abortAfter, 5);             // original
    ASSERT_EQ(actual.testsOrTags.size(), 2u);    // original size
    EXPECT_EQ(actual.processName, "my_proc");    // original
}
