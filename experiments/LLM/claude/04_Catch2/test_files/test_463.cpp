#include <gtest/gtest.h>
#include <fstream>
#include <string>

// Forward declare the function under test
namespace Catch {
    bool isDebuggerActive();
}

// Test that isDebuggerActive returns a boolean value (normal operation)
TEST(CatchDebuggerTest_463, IsDebuggerActiveReturnsBool_463) {
    bool result = Catch::isDebuggerActive();
    // The function should return either true or false
    EXPECT_TRUE(result == true || result == false);
}

// Test that isDebuggerActive can be called multiple times consistently
TEST(CatchDebuggerTest_463, IsDebuggerActiveConsistentAcrossCalls_463) {
    bool result1 = Catch::isDebuggerActive();
    bool result2 = Catch::isDebuggerActive();
    // Calling the function multiple times in succession should yield the same result
    // (assuming debugger state doesn't change between calls)
    EXPECT_EQ(result1, result2);
}

// Test that isDebuggerActive does not corrupt errno (ErrnoGuard behavior)
TEST(CatchDebuggerTest_463, IsDebuggerActivePreservesErrno_463) {
    errno = 42;
    Catch::isDebuggerActive();
    EXPECT_EQ(errno, 42);
}

// Test that isDebuggerActive does not corrupt errno when errno is zero
TEST(CatchDebuggerTest_463, IsDebuggerActivePreservesZeroErrno_463) {
    errno = 0;
    Catch::isDebuggerActive();
    EXPECT_EQ(errno, 0);
}

// Test that when not being debugged (typical CI/test environment), the function returns false
// This test may need adjustment if run under a debugger
TEST(CatchDebuggerTest_463, IsDebuggerActiveReturnsFalseWhenNotDebugged_463) {
    // In a typical test/CI environment, no debugger is attached
    // We verify by reading /proc/self/status ourselves
    bool expectedResult = false;
    std::ifstream in("/proc/self/status");
    if (in.is_open()) {
        for (std::string line; std::getline(in, line);) {
            if (line.compare(0, 11, "TracerPid:\t") == 0) {
                if (line.length() > 11 && line[11] != '0') {
                    expectedResult = true;
                }
                break;
            }
        }
    }
    
    bool result = Catch::isDebuggerActive();
    EXPECT_EQ(result, expectedResult);
}

// Test that isDebuggerActive preserves errno even with a non-standard errno value
TEST(CatchDebuggerTest_463, IsDebuggerActivePreservesLargeErrno_463) {
    errno = 9999;
    Catch::isDebuggerActive();
    EXPECT_EQ(errno, 9999);
}

// Test rapid successive calls don't cause issues (stress / boundary)
TEST(CatchDebuggerTest_463, IsDebuggerActiveRapidCalls_463) {
    bool firstResult = Catch::isDebuggerActive();
    for (int i = 0; i < 100; ++i) {
        bool result = Catch::isDebuggerActive();
        EXPECT_EQ(result, firstResult);
    }
}
