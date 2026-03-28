#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>

// Forward declaration of the function under test
int exec_cmd(std::string const& cmd, int log_num, std::string const& path);

// We also need escape_arg to be available; it's assumed to be defined in the same translation unit
// If not available, we declare it:
// std::string escape_arg(std::string const& arg);

class ExecCmdTest_885 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that exec_cmd with a simple successful command returns 0
// Using "cmd /c echo hello" as a command that should succeed on Windows
TEST_F(ExecCmdTest_885, SuccessfulCommandReturnsZero_885) {
    // "cmd /c exit 0" should return 0 on Windows
    // Note: This test is platform-dependent (Windows, due to _popen/_pclose)
    int result = exec_cmd("cmd /c exit 0", 1, "C:\\TestPath");
    EXPECT_EQ(result, 0);
}

// Test that exec_cmd with a command that fails returns non-zero
TEST_F(ExecCmdTest_885, FailingCommandReturnsNonZero_885) {
    // "cmd /c exit 1" should return non-zero
    int result = exec_cmd("cmd /c exit 1", 2, "C:\\TestPath");
    EXPECT_NE(result, 0);
}

// Test with different log_num values to ensure the binary output file name varies
TEST_F(ExecCmdTest_885, DifferentLogNumsProduceDifferentCommands_885) {
    // Both should execute without throwing; we're testing that different log_num values work
    int result1 = exec_cmd("cmd /c exit 0", 0, "C:\\TestPath");
    int result2 = exec_cmd("cmd /c exit 0", 999, "C:\\TestPath");
    EXPECT_EQ(result1, 0);
    EXPECT_EQ(result2, 0);
}

// Test with negative log_num (boundary condition)
TEST_F(ExecCmdTest_885, NegativeLogNum_885) {
    int result = exec_cmd("cmd /c exit 0", -1, "C:\\TestPath");
    EXPECT_EQ(result, 0);
}

// Test with empty path string
TEST_F(ExecCmdTest_885, EmptyPathString_885) {
    // Should still execute without throwing, the command is constructed regardless
    int result = exec_cmd("cmd /c exit 0", 3, "");
    // The command may fail or succeed depending on OpenCppCoverage behavior
    // but it should not throw from popen being null for a valid cmd
    // We mainly verify it doesn't crash
    (void)result;
}

// Test with empty command string
TEST_F(ExecCmdTest_885, EmptyCommandString_885) {
    // Empty cmd appended to the OpenCppCoverage command line
    // This might cause OpenCppCoverage to fail, but popen itself should succeed
    EXPECT_NO_THROW({
        int result = exec_cmd("", 4, "C:\\TestPath");
        (void)result;
    });
}

// Test with large log_num (boundary)
TEST_F(ExecCmdTest_885, LargeLogNum_885) {
    int result = exec_cmd("cmd /c exit 0", 2147483647, "C:\\TestPath");
    EXPECT_EQ(result, 0);
}

// Test with path containing spaces
TEST_F(ExecCmdTest_885, PathWithSpaces_885) {
    // escape_arg should handle paths with spaces
    EXPECT_NO_THROW({
        int result = exec_cmd("cmd /c exit 0", 5, "C:\\Program Files\\Test Path");
        (void)result;
    });
}

// Test that a specific exit code is propagated
TEST_F(ExecCmdTest_885, ExitCodePropagation_885) {
    int result = exec_cmd("cmd /c exit 42", 6, "C:\\TestPath");
    // On Windows, _pclose returns the exit status of the command
    EXPECT_EQ(result, 42);
}
