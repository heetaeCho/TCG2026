// File: tests/session_apply_command_line_451_tests.cpp

#include <gtest/gtest.h>

// Include only the public headers/interfaces shown in the prompt
#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Catch;

class SessionApplyCommandLineTest_451 : public ::testing::Test {
protected:
    // Common helper to build a minimal argv
    static void MakeArgv(const char* prog, std::vector<const char*>& out) {
        out.clear();
        out.push_back(prog);
        out.push_back(nullptr); // argv must be null-terminated
    }
};

// [Normal] With no options, parsing should succeed and return 0.
TEST_F(SessionApplyCommandLineTest_451, ReturnsZeroOnSuccessfulParse_451) {
    Session s;

    std::vector<const char*> argv;
    MakeArgv("prog", argv);

    const int rc = s.applyCommandLine(1, argv.data());
    EXPECT_EQ(rc, 0);
}

// [Error path] An unknown/invalid option should cause parse failure and
// applyCommandLine should return UnspecifiedErrorExitCode.
// Additionally, when parse fails, Session is expected to set the active
// Catch context's config to its own Config instance before returning.
// We observe this via getCurrentContext().getConfig().
TEST_F(SessionApplyCommandLineTest_451, ReturnsErrorAndSetsContextConfigOnInvalidArgs_451) {
    Session s;

    // Obtain the Session's Config instance (observable via public API).
    // This must match the context's config when parse fails.
    Config& cfgRef = s.config();
    const IConfig* expectedCfgPtr = &cfgRef;

    // Build argv with a definitely invalid flag to trigger CLI error handling.
    const char* invalid = "--this-flag-should-not-exist";
    std::vector<const char*> argv = {"prog", invalid, nullptr};

    const int rc = s.applyCommandLine(2, argv.data());
    EXPECT_EQ(rc, UnspecifiedErrorExitCode);

    // On error, applyCommandLine should have set the context's config
    // to the Session's config before returning.
    EXPECT_EQ(getCurrentContext().getConfig(), expectedCfgPtr);
}

// [Flag-driven behavior, observable result] If help is requested,
// applyCommandLine should still succeed (return 0). We do NOT assert
// internal calls like showHelp(); we only verify the public outcome.
TEST_F(SessionApplyCommandLineTest_451, HelpFlagPreconfiguredStillReturnsZero_451) {
    Session s;
    ConfigData cd;
    cd.showHelp = true; // preconfigure via public API
    s.useConfigData(cd);

    std::vector<const char*> argv = {"prog", nullptr};
    const int rc = s.applyCommandLine(1, argv.data());
    EXPECT_EQ(rc, 0);
}

// [Flag-driven behavior, observable result] If lib identification is requested,
// applyCommandLine should also succeed (return 0). Again, no assumptions about internals.
TEST_F(SessionApplyCommandLineTest_451, LibIdentifyFlagPreconfiguredStillReturnsZero_451) {
    Session s;
    ConfigData cd;
    cd.libIdentify = true; // preconfigure via public API
    s.useConfigData(cd);

    std::vector<const char*> argv = {"prog", nullptr};
    const int rc = s.applyCommandLine(1, argv.data());
    EXPECT_EQ(rc, 0);
}

// [Boundary] Provide a program name only (no options) with a longer argc
// scenario using an empty string as an extra non-option token. Parser
// should still succeed (return 0). This avoids assumptions about specific
// option names while exercising minimal-but-nontrivial argv.
TEST_F(SessionApplyCommandLineTest_451, ProgramNameOnlyStillReturnsZero_451) {
    Session s;

    // argv: prog, "", nullptr  -> a benign extra token
    std::vector<const char*> argv = {"prog", "", nullptr};
    const int rc = s.applyCommandLine(2, argv.data());
    EXPECT_EQ(rc, 0);
}
