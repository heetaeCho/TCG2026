// File: tests/coverage_helper_exec_cmd_tests_885.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

// Forward-declare the symbol under test.
// In your build, make sure Catch2/tools/misc/coverage-helper.cpp is compiled & linked.
int exec_cmd(std::string const& cmd, int log_num, std::string const& path);

// --------- Test doubles for external collaborators ---------
// We only mock external deps, not internal logic of exec_cmd.

extern "C" {

// Global knobs/state for the fakes
static FILE*        g_fake_pipe_885        = nullptr;
static std::string  g_popen_last_cmd_885;
static int          g_pclose_return_885    = 0;
static bool         g_force_popen_fail_885 = false;
static std::string  g_pipe_payload_885; // what fgets/feof read from

// Helper: (re)build the fake pipe with current payload
static void rebuild_fake_pipe_885() {
    if (g_fake_pipe_885) { fclose(g_fake_pipe_885); g_fake_pipe_885 = nullptr; }
    g_fake_pipe_885 = tmpfile();
    if (g_fake_pipe_885 && !g_pipe_payload_885.empty()) {
        fputs(g_pipe_payload_885.c_str(), g_fake_pipe_885);
        rewind(g_fake_pipe_885);
    }
}

// Fake _popen: record command and hand back a FILE* with our payload.
FILE* _popen(const char* cmd, const char* /*mode*/) {
    if (g_force_popen_fail_885) {
        return nullptr;
    }
    g_popen_last_cmd_885 = cmd ? std::string(cmd) : std::string();
    if (!g_fake_pipe_885) {
        rebuild_fake_pipe_885();
    } else {
        rewind(g_fake_pipe_885);
    }
    return g_fake_pipe_885;
}

// Fake _pclose: return configured code; also close our FILE*.
int _pclose(FILE* fp) {
    if (fp && fp == g_fake_pipe_885) {
        fclose(g_fake_pipe_885);
        g_fake_pipe_885 = nullptr;
    }
    return g_pclose_return_885;
}

} // extern "C"

// Mock escape_arg, an external collaborator used by exec_cmd.
// We do NOT reimplement its real behavior; we return a predictable token-wrapped value
// so we can assert the exact command string that exec_cmd constructs.
std::string escape_arg(std::string const& p) {
    return std::string("[ESC]") + p + "[/ESC]";
}

// --------- Test fixture to isolate global fake state ---------
class ExecCmdTest_885 : public ::testing::Test {
protected:
    std::streambuf* old_buf_ = nullptr;
    std::ostringstream capture_;

    void SetUp() override {
        // Reset fake knobs
        g_popen_last_cmd_885.clear();
        g_pclose_return_885    = 0;
        g_force_popen_fail_885 = false;
        g_pipe_payload_885     = "line1\nline2\n";
        rebuild_fake_pipe_885();

        // Capture std::cout for observable behavior checks
        old_buf_ = std::cout.rdbuf(capture_.rdbuf());
    }

    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(old_buf_);
        // Clean up fake pipe
        if (g_fake_pipe_885) {
            fclose(g_fake_pipe_885);
            g_fake_pipe_885 = nullptr;
        }
    }

    // Utility to build the expected real command string printed by exec_cmd
    static std::string ExpectedCmd(const std::string& cmd, int log_num, const std::string& path) {
        // Mirrors only the *string formatting* contract seen in code;
        // we are not inferring internal logic beyond the visible concatenation.
        return "OpenCppCoverage --export_type binary:cov-report" + std::to_string(log_num) +
               ".bin --quiet --sources " + escape_arg(path) + "\\src --cover_children -- " + cmd;
    }
};

// --- Tests ---

// Normal operation: returns child's status, prints marker + child's output, and passes full command to _popen.
TEST_F(ExecCmdTest_885, NormalCommandAndPath_885) {
    using ::testing::HasSubstr;

    const std::string cmd  = "tool.exe --flag";
    const int         logN = 3;
    const std::string path = "C:\\work\\project";

    // Configure the fake child to succeed with return code 123
    g_pclose_return_885 = 123;
    g_pipe_payload_885  = "child out A\nchild out B\n";
    rebuild_fake_pipe_885();

    const std::string expected_cmd = ExpectedCmd(cmd, logN, path);

    int ret = exec_cmd(cmd, logN, path);
    EXPECT_EQ(ret, 123);

    // Verify the constructed command was printed in the marker line
    std::string printed = capture_.str();
    EXPECT_THAT(printed, HasSubstr("=== Marker ===: Cmd: " + expected_cmd + "\n"));

    // Verify child's stdout was streamed to std::cout
    EXPECT_THAT(printed, HasSubstr("child out A\n"));
    EXPECT_THAT(printed, HasSubstr("child out B\n"));

    // Verify interaction: _popen was called with the exact real command
    EXPECT_EQ(g_popen_last_cmd_885, expected_cmd);
}

// Boundary-ish inputs: empty cmd; path with spaces; log index 0.
// Ensures string assembly and printing remain correct and return code is propagated.
TEST_F(ExecCmdTest_885, EmptyCmdAndSpacedPath_885) {
    using ::testing::HasSubstr;

    const std::string cmd  = "";
    const int         logN = 0;
    const std::string path = "C:\\Program Files\\MyProj";

    g_pclose_return_885 = 0;
    g_pipe_payload_885  = "ok\n";
    rebuild_fake_pipe_885();

    const std::string expected_cmd = ExpectedCmd(cmd, logN, path);

    int ret = exec_cmd(cmd, logN, path);
    EXPECT_EQ(ret, 0);

    std::string printed = capture_.str();
    EXPECT_THAT(printed, HasSubstr("=== Marker ===: Cmd: " + expected_cmd + "\n"));
    EXPECT_THAT(printed, HasSubstr("ok\n"));
    EXPECT_EQ(g_popen_last_cmd_885, expected_cmd);
}

// Error path: _popen fails. Must throw with the documented message.
// Note: The marker with the fully constructed command is printed before _popen is attempted.
TEST_F(ExecCmdTest_885, PopenFailureThrows_885) {
    using ::testing::HasSubstr;

    const std::string cmd  = "anything";
    const int         logN = 7;
    const std::string path = "C:\\x";

    g_force_popen_fail_885 = true;

    const std::string expected_cmd = ExpectedCmd(cmd, logN, path);

    try {
        (void)exec_cmd(cmd, logN, path);
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "popen() failed!");
    }

    // Even on failure, marker with full command should be present
    std::string printed = capture_.str();
    EXPECT_THAT(printed, HasSubstr("=== Marker ===: Cmd: " + expected_cmd + "\n"));

    // When failing at popen, our fake does not record a cmd (by design); we only assert observable output & exception.
}

// Error path: _pclose returns -1. Must throw with the documented message,
// after having streamed any available child output.
TEST_F(ExecCmdTest_885, PcloseUnderlyingErrorThrows_885) {
    using ::testing::HasSubstr;

    const std::string cmd  = "runner --do";
    const int         logN = 11;
    const std::string path = "D:\\dev";

    g_pclose_return_885 = -1;
    g_pipe_payload_885  = "partial\noutput\n";
    rebuild_fake_pipe_885();

    const std::string expected_cmd = ExpectedCmd(cmd, logN, path);

    try {
        (void)exec_cmd(cmd, logN, path);
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "underlying error in pclose()");
    }

    std::string printed = capture_.str();
    EXPECT_THAT(printed, HasSubstr("=== Marker ===: Cmd: " + expected_cmd + "\n"));
    EXPECT_THAT(printed, HasSubstr("partial\n"));
    EXPECT_THAT(printed, HasSubstr("output\n"));
    EXPECT_EQ(g_popen_last_cmd_885, expected_cmd);
}
