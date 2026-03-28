#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/catch_session.hpp"

class SessionTest_424 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed Session can be created without throwing
TEST_F(SessionTest_424, DefaultConstruction_424) {
    EXPECT_NO_THROW(Catch::Session session);
}

// Test that run() with no arguments returns a valid return code
TEST_F(SessionTest_424, RunWithNoArgs_424) {
    Catch::Session session;
    int result = session.run();
    // run() should return some integer (0 for success or non-zero for specific conditions)
    // We just verify it doesn't crash and returns something
    EXPECT_GE(result, 0);
}

// Test applyCommandLine with minimal arguments (just program name)
TEST_F(SessionTest_424, ApplyCommandLineMinimalArgs_424) {
    Catch::Session session;
    const char* argv[] = {"test_program"};
    int result = session.applyCommandLine(1, argv);
    EXPECT_EQ(result, 0);
}

// Test the template run with argc/argv (char)
TEST_F(SessionTest_424, TemplateRunWithCharArgs_424) {
    Catch::Session session;
    const char* argv[] = {"test_program"};
    int result = session.run(1, argv);
    // Should succeed with just program name
    EXPECT_GE(result, 0);
}

// Test applyCommandLine with help flag
TEST_F(SessionTest_424, ApplyCommandLineWithHelp_424) {
    Catch::Session session;
    const char* argv[] = {"test_program", "--help"};
    int result = session.applyCommandLine(2, argv);
    // --help typically causes a non-zero return to skip running tests
    // but applyCommandLine might return 0 and set internal state
    // We just check it doesn't crash
    (void)result;
}

// Test that cli() returns a valid parser reference
TEST_F(SessionTest_424, CliReturnsParser_424) {
    Catch::Session session;
    EXPECT_NO_THROW({
        const auto& parser = session.cli();
        (void)parser;
    });
}

// Test that configData() returns a mutable reference
TEST_F(SessionTest_424, ConfigDataReturnsMutableReference_424) {
    Catch::Session session;
    EXPECT_NO_THROW({
        auto& data = session.configData();
        (void)data;
    });
}

// Test that config() returns a reference after applyCommandLine
TEST_F(SessionTest_424, ConfigReturnsReference_424) {
    Catch::Session session;
    const char* argv[] = {"test_program"};
    session.applyCommandLine(1, argv);
    EXPECT_NO_THROW({
        auto& cfg = session.config();
        (void)cfg;
    });
}

// Test setting a new CLI parser
TEST_F(SessionTest_424, SetCliParser_424) {
    Catch::Session session;
    auto originalParser = session.cli();
    EXPECT_NO_THROW(session.cli(originalParser));
}

// Test showHelp doesn't crash
TEST_F(SessionTest_424, ShowHelpDoesNotCrash_424) {
    Catch::Session session;
    EXPECT_NO_THROW(session.showHelp());
}

// Test libIdentify doesn't crash
TEST_F(SessionTest_424, LibIdentifyDoesNotCrash_424) {
    Catch::Session session;
    EXPECT_NO_THROW(session.libIdentify());
}

// Test applyCommandLine with invalid/unknown option
TEST_F(SessionTest_424, ApplyCommandLineWithUnknownOption_424) {
    Catch::Session session;
    const char* argv[] = {"test_program", "--completely-invalid-option-xyz"};
    int result = session.applyCommandLine(2, argv);
    // Unknown options should result in non-zero return code
    EXPECT_NE(result, 0);
}

// Test run(argc, argv) with an invalid option
TEST_F(SessionTest_424, TemplateRunWithInvalidOption_424) {
    Catch::Session session;
    const char* argv[] = {"test_program", "--completely-invalid-option-xyz"};
    int result = session.run(2, argv);
    EXPECT_NE(result, 0);
}

// Test useConfigData
TEST_F(SessionTest_424, UseConfigData_424) {
    Catch::Session session;
    Catch::ConfigData configData;
    EXPECT_NO_THROW(session.useConfigData(configData));
}

// Test that calling applyCommandLine multiple times works
TEST_F(SessionTest_424, MultipleApplyCommandLine_424) {
    Catch::Session session;
    const char* argv1[] = {"test_program"};
    int result1 = session.applyCommandLine(1, argv1);
    EXPECT_EQ(result1, 0);

    const char* argv2[] = {"test_program"};
    int result2 = session.applyCommandLine(1, argv2);
    EXPECT_EQ(result2, 0);
}

// Test run with argc=0 (boundary condition)
TEST_F(SessionTest_424, ApplyCommandLineZeroArgc_424) {
    Catch::Session session;
    const char* argv[] = {nullptr};
    // argc=0 is an edge case
    int result = session.applyCommandLine(0, argv);
    (void)result; // Just verify it doesn't crash
}

// Test that template run works with wchar_t if supported
// Note: This tests the template instantiation path
TEST_F(SessionTest_424, TemplateRunWithArgcOne_424) {
    Catch::Session session;
    const char* argv[] = {"test_program"};
    int result = session.run(1, argv);
    EXPECT_GE(result, 0);
}

// Test applying command line with list-tests flag
TEST_F(SessionTest_424, ApplyCommandLineListTests_424) {
    Catch::Session session;
    const char* argv[] = {"test_program", "--list-tests"};
    int result = session.applyCommandLine(2, argv);
    // list-tests should be a valid option
    EXPECT_EQ(result, 0);
}

// Test that configData can be modified before run
TEST_F(SessionTest_424, ModifyConfigDataBeforeRun_424) {
    Catch::Session session;
    auto& data = session.configData();
    data.showHelp = true;
    // Running with showHelp should not crash
    int result = session.run();
    (void)result;
}
