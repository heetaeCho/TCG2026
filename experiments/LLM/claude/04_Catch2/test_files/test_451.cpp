#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_context.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

class SessionTest_451 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create argc/argv from a vector of strings
    struct ArgsHelper {
        std::vector<std::string> strings;
        std::vector<const char*> ptrs;

        ArgsHelper(std::initializer_list<std::string> args) : strings(args) {
            for (auto& s : strings) {
                ptrs.push_back(s.c_str());
            }
        }

        int argc() const { return static_cast<int>(ptrs.size()); }
        const char* const* argv() const { return ptrs.data(); }
    };
};

// Test that applying a valid command line with just the program name returns 0
TEST_F(SessionTest_451, ApplyCommandLine_NoArgs_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with --help flag returns 0 (help is shown but not an error)
TEST_F(SessionTest_451, ApplyCommandLine_HelpFlag_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--help"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with -? flag returns 0
TEST_F(SessionTest_451, ApplyCommandLine_QuestionMarkFlag_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "-?"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying an invalid command line argument returns an error code
TEST_F(SessionTest_451, ApplyCommandLine_InvalidArg_ReturnsError_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--completely-invalid-nonexistent-option-xyz"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_NE(result, 0);
}

// Test that applying command line with --libidentify flag returns 0
TEST_F(SessionTest_451, ApplyCommandLine_LibIdentify_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--libidentify"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with valid test spec returns 0
TEST_F(SessionTest_451, ApplyCommandLine_WithTestSpec_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "some_test_name"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with verbosity option returns 0
TEST_F(SessionTest_451, ApplyCommandLine_VerbosityHigh_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--verbosity", "high"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with --list-tests returns 0
TEST_F(SessionTest_451, ApplyCommandLine_ListTests_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--list-tests"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with --list-tags returns 0
TEST_F(SessionTest_451, ApplyCommandLine_ListTags_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--list-tags"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test applying command line twice resets config properly
TEST_F(SessionTest_451, ApplyCommandLine_CalledTwice_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args1{"test_program", "--list-tests"};
    int result1 = session.applyCommandLine(args1.argc(), args1.argv());
    EXPECT_EQ(result1, 0);

    ArgsHelper args2{"test_program"};
    int result2 = session.applyCommandLine(args2.argc(), args2.argv());
    EXPECT_EQ(result2, 0);
}

// Test that applying command line with --nothrow returns 0
TEST_F(SessionTest_451, ApplyCommandLine_NoThrow_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--nothrow"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with --abort returns 0
TEST_F(SessionTest_451, ApplyCommandLine_Abort_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--abort"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test that applying command line with invalid verbosity returns error
TEST_F(SessionTest_451, ApplyCommandLine_InvalidVerbosity_ReturnsError_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--verbosity", "invalid_level"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_NE(result, 0);
}

// Test that cli() returns a valid parser reference
TEST_F(SessionTest_451, Cli_ReturnsValidParser_451) {
    Catch::Session session;
    const Catch::Clara::Parser& parser = session.cli();
    // Just verify we can access it without crashing
    SUCCEED();
}

// Test that configData() returns a reference that can be inspected
TEST_F(SessionTest_451, ConfigData_DefaultValues_451) {
    Catch::Session session;
    Catch::ConfigData& data = session.configData();
    // Default values checks
    EXPECT_FALSE(data.showHelp);
    EXPECT_FALSE(data.listTests);
    EXPECT_FALSE(data.listTags);
    EXPECT_FALSE(data.noThrow);
    EXPECT_FALSE(data.libIdentify);
}

// Test that configData reflects command line parsing
TEST_F(SessionTest_451, ConfigData_AfterApplyCommandLine_ReflectsArgs_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--nothrow"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().noThrow);
}

// Test that useConfigData can be called
TEST_F(SessionTest_451, UseConfigData_SetsData_451) {
    Catch::Session session;
    Catch::ConfigData data;
    data.noThrow = true;
    data.showSuccessfulTests = true;
    session.useConfigData(data);
    EXPECT_TRUE(session.configData().noThrow);
    EXPECT_TRUE(session.configData().showSuccessfulTests);
}

// Test config() returns a valid config after applyCommandLine
TEST_F(SessionTest_451, Config_AfterApplyCommandLine_ReturnsValidConfig_451) {
    Catch::Session session;
    ArgsHelper args{"test_program"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
    // Accessing config should not crash
    Catch::Config& cfg = session.config();
    (void)cfg;
    SUCCEED();
}

// Test that setting a new CLI parser works
TEST_F(SessionTest_451, SetCli_NewParser_451) {
    Catch::Session session;
    Catch::Clara::Parser originalParser = session.cli();
    session.cli(originalParser);
    // Should still work after re-setting
    ArgsHelper args{"test_program"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
}

// Test multiple valid arguments at once
TEST_F(SessionTest_451, ApplyCommandLine_MultipleValidArgs_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "--nothrow", "--abort"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().noThrow);
}

// Test that applying command line with -s (show successful) works
TEST_F(SessionTest_451, ApplyCommandLine_ShowSuccess_ReturnsZero_451) {
    Catch::Session session;
    ArgsHelper args{"test_program", "-s"};
    int result = session.applyCommandLine(args.argc(), args.argv());
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(session.configData().showSuccessfulTests);
}

// Test the error exit code constant
TEST_F(SessionTest_451, UnspecifiedErrorExitCode_IsOne_451) {
    EXPECT_EQ(Catch::UnspecifiedErrorExitCode, 1);
}
