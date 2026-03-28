#include <gtest/gtest.h>
#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"

class SessionTest_456 : public ::testing::Test {
protected:
    Catch::Session session;
};

// Test that a default-constructed Session can be created without throwing
TEST_F(SessionTest_456, DefaultConstruction_456) {
    // If we get here, the Session was constructed successfully
    SUCCEED();
}

// Test that configData() returns a reference to ConfigData
TEST_F(SessionTest_456, ConfigDataReturnsReference_456) {
    Catch::ConfigData& data = session.configData();
    // Verify we can obtain a reference without crashing
    (void)data;
    SUCCEED();
}

// Test that configData() returns the same object on repeated calls
TEST_F(SessionTest_456, ConfigDataReturnsSameReference_456) {
    Catch::ConfigData& data1 = session.configData();
    Catch::ConfigData& data2 = session.configData();
    EXPECT_EQ(&data1, &data2);
}

// Test that config() returns a reference to Config
TEST_F(SessionTest_456, ConfigReturnsReference_456) {
    // Need to ensure config is initialized; applyCommandLine with no args should work
    const char* argv[] = {"test"};
    session.applyCommandLine(1, argv);
    Catch::Config& cfg = session.config();
    (void)cfg;
    SUCCEED();
}

// Test that cli() const returns a parser reference
TEST_F(SessionTest_456, CliReturnsParser_456) {
    const Catch::Session& constSession = session;
    const Clara::Parser& parser = constSession.cli();
    (void)parser;
    SUCCEED();
}

// Test that cli(newParser) sets a new parser
TEST_F(SessionTest_456, CliSetNewParser_456) {
    Clara::Parser newParser;
    session.cli(newParser);
    // Should not crash, and cli should still be accessible
    const Clara::Parser& parser = session.cli();
    (void)parser;
    SUCCEED();
}

// Test applyCommandLine with minimal arguments
TEST_F(SessionTest_456, ApplyCommandLineMinimalArgs_456) {
    const char* argv[] = {"test_program"};
    int result = session.applyCommandLine(1, argv);
    EXPECT_EQ(result, 0);
}

// Test applyCommandLine with help flag
TEST_F(SessionTest_456, ApplyCommandLineWithHelp_456) {
    const char* argv[] = {"test_program", "--help"};
    int result = session.applyCommandLine(2, argv);
    // Help typically returns 0 (success) but sets internal state
    EXPECT_GE(result, 0);
}

// Test applyCommandLine with invalid argument
TEST_F(SessionTest_456, ApplyCommandLineInvalidArg_456) {
    const char* argv[] = {"test_program", "--this-is-not-a-valid-catch2-option"};
    int result = session.applyCommandLine(2, argv);
    // Invalid options should result in a non-zero return
    EXPECT_NE(result, 0);
}

// Test useConfigData with default ConfigData
TEST_F(SessionTest_456, UseConfigDataDefault_456) {
    Catch::ConfigData configData;
    session.useConfigData(configData);
    // Should not crash
    SUCCEED();
}

// Test useConfigData modifies the session's config data
TEST_F(SessionTest_456, UseConfigDataModifiesSession_456) {
    Catch::ConfigData configData;
    configData.showSuccessfulTests = true;
    session.useConfigData(configData);
    EXPECT_TRUE(session.configData().showSuccessfulTests);
}

// Test that configData can be modified through the returned reference
TEST_F(SessionTest_456, ConfigDataModifiableThroughReference_456) {
    Catch::ConfigData& data = session.configData();
    data.showSuccessfulTests = true;
    EXPECT_TRUE(session.configData().showSuccessfulTests);
}

// Test that configData can be set to show no tests
TEST_F(SessionTest_456, ConfigDataShowSuccessfulTestsDefaultFalse_456) {
    Catch::ConfigData& data = session.configData();
    // Default should typically be false
    EXPECT_FALSE(data.showSuccessfulTests);
}

// Test applyCommandLine with verbosity flag
TEST_F(SessionTest_456, ApplyCommandLineVerbosity_456) {
    const char* argv[] = {"test_program", "-v", "high"};
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
}

// Test applyCommandLine with list-tests flag
TEST_F(SessionTest_456, ApplyCommandLineListTests_456) {
    const char* argv[] = {"test_program", "--list-tests"};
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
}

// Test that showHelp does not crash
TEST_F(SessionTest_456, ShowHelpDoesNotCrash_456) {
    EXPECT_NO_THROW(session.showHelp());
}

// Test that libIdentify does not crash
TEST_F(SessionTest_456, LibIdentifyDoesNotCrash_456) {
    EXPECT_NO_THROW(session.libIdentify());
}

// Test creating multiple Session objects (each in its own scope)
TEST(SessionMultipleTest_456, CanCreateSessionAfterDestruction_456) {
    {
        Catch::Session session1;
        const char* argv[] = {"test"};
        session1.applyCommandLine(1, argv);
    }
    // After the first session is destroyed, we should be able to create another
    // Note: Catch2 may have singleton-like behavior, so this tests that
    {
        Catch::Session session2;
        const char* argv[] = {"test"};
        int result = session2.applyCommandLine(1, argv);
        EXPECT_EQ(result, 0);
    }
}

// Test applyCommandLine with test spec filter
TEST_F(SessionTest_456, ApplyCommandLineWithTestFilter_456) {
    const char* argv[] = {"test_program", "SomeTestName"};
    int result = session.applyCommandLine(2, argv);
    EXPECT_EQ(result, 0);
}

// Test applyCommandLine with multiple test spec filters
TEST_F(SessionTest_456, ApplyCommandLineWithMultipleFilters_456) {
    const char* argv[] = {"test_program", "Test1", "Test2"};
    int result = session.applyCommandLine(3, argv);
    EXPECT_EQ(result, 0);
}

// Test that useConfigData with testsOrTags updates configData
TEST_F(SessionTest_456, UseConfigDataWithTestsOrTags_456) {
    Catch::ConfigData configData;
    configData.testsOrTags.push_back("SomeTest");
    session.useConfigData(configData);
    EXPECT_EQ(session.configData().testsOrTags.size(), 1u);
    EXPECT_EQ(session.configData().testsOrTags[0], "SomeTest");
}
