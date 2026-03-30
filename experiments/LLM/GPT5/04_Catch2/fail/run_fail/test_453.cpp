// File: session_run_waitforkeypress_tests_453.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>

// Headers under test
#include "catch2/catch_session.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using Catch::Session;
using Catch::ConfigData;
using Catch::WaitForKeypress;

// ------- Helpers to safely redirect std::cout and std::cin (stdin) -------
class CoutRedirect {
public:
    CoutRedirect() : oldBuf_(std::cout.rdbuf(oss_.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(oldBuf_); }
    std::string str() const { return oss_.str(); }
private:
    std::ostringstream oss_;
    std::streambuf* oldBuf_;
};

class StdinRedirect {
public:
    // Provide a buffer (e.g., "\n\n") that getchar() can read without blocking.
    explicit StdinRedirect(const std::string& data) {
        // Use a temporary file to back stdin
        tmpName_ = std::tmpnam(nullptr);
        std::ofstream ofs(tmpName_, std::ios::binary);
        ofs << data;
        ofs.close();
        oldFile_ = std::freopen(tmpName_.c_str(), "rb", stdin);
    }
    ~StdinRedirect() {
        if (oldFile_) {
            // Restore stdin to its original stream (usually /dev/tty not easily recoverable in tests).
            // Instead, reopen an empty /dev/null-like stream to avoid affecting other tests.
#if defined(_WIN32)
            std::freopen("NUL", "r", stdin);
#else
            std::freopen("/dev/null", "r", stdin);
#endif
        }
        if (!tmpName_.empty()) {
            std::remove(tmpName_.c_str());
        }
    }
private:
    std::string tmpName_;
    FILE* oldFile_{nullptr};
};

// A small fixture for convenience (not strictly required here)
class SessionRunTest_453 : public ::testing::Test {
protected:
    Session session_;
};

// ------------------------------------------------------------------------
// Tests
// ------------------------------------------------------------------------

TEST_F(SessionRunTest_453, Run_NoWait_PrintsNothing_453) {
    ConfigData cfg;
    cfg.waitForKeypress = WaitForKeypress::Never;

    session_.useConfigData(cfg);

    // Even though no wait is expected, provide input to avoid any accidental block.
    StdinRedirect stdinGuard("\n");
    CoutRedirect coutGuard;

    // We do not assert on the return code (black box),
    // only on the absence of "waiting" messages.
    (void)session_.run();

    std::string out = coutGuard.str();
    EXPECT_EQ(out.find("...waiting for enter/ return before starting"), std::string::npos);
    EXPECT_EQ(out.find("...waiting for enter/ return before exiting"), std::string::npos);
}

TEST_F(SessionRunTest_453, Run_WaitBeforeStart_PrintsPrompt_453) {
    ConfigData cfg;
    cfg.waitForKeypress = WaitForKeypress::BeforeStart;

    session_.useConfigData(cfg);

    // Provide one newline so getchar() at start does not block.
    StdinRedirect stdinGuard("\n");
    CoutRedirect coutGuard;

    (void)session_.run();

    std::string out = coutGuard.str();
    // Verify the exact, observable prefix from the implementation.
    EXPECT_NE(out.find("...waiting for enter/ return before starting"), std::string::npos);
    // No exit prompt expected.
    EXPECT_EQ(out.find("...waiting for enter/ return before exiting"), std::string::npos);
}

TEST_F(SessionRunTest_453, Run_WaitBeforeExit_PrintsExitPromptWithCode_453) {
    ConfigData cfg;
    cfg.waitForKeypress = WaitForKeypress::BeforeExit;

    session_.useConfigData(cfg);

    // Provide one newline so getchar() at exit does not block.
    StdinRedirect stdinGuard("\n");
    CoutRedirect coutGuard;

    (void)session_.run();

    std::string out = coutGuard.str();
    // Should not print the "before starting" prompt.
    EXPECT_EQ(out.find("...waiting for enter/ return before starting"), std::string::npos);

    // Should print the exit prompt that includes "with code: <int>"
    auto pos = out.find("...waiting for enter/ return before exiting, with code: ");
    EXPECT_NE(pos, std::string::npos);

    // We cannot assert the exact code (black box), but ensure something follows.
    if (pos != std::string::npos) {
        std::string tail = out.substr(pos);
        // There should be at least one digit or a minus sign before newline.
        bool hasDigitOrMinus = false;
        for (char c : tail) {
            if (c == '\n') break;
            if ((c >= '0' && c <= '9') || c == '-') { hasDigitOrMinus = true; break; }
        }
        EXPECT_TRUE(hasDigitOrMinus);
    }
}

TEST_F(SessionRunTest_453, Run_WaitBeforeStartAndExit_PrintsBothInOrder_453) {
    ConfigData cfg;
    cfg.waitForKeypress = WaitForKeypress::BeforeStartAndExit;

    session_.useConfigData(cfg);

    // Provide two newlines for the two getchar() calls.
    StdinRedirect stdinGuard("\n\n");
    CoutRedirect coutGuard;

    (void)session_.run();

    std::string out = coutGuard.str();

    auto startPos = out.find("...waiting for enter/ return before starting");
    auto exitPos  = out.find("...waiting for enter/ return before exiting, with code: ");

    EXPECT_NE(startPos, std::string::npos);
    EXPECT_NE(exitPos,  std::string::npos);
    // Start prompt should appear before exit prompt
    if (startPos != std::string::npos && exitPos != std::string::npos) {
        EXPECT_LT(startPos, exitPos);
    }
}
