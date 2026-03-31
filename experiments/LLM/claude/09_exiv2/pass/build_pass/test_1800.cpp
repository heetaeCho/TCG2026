#include <gtest/gtest.h>
#include <cstdlib>
#include <stdexcept>
#include <string>

// Include the header that declares getEnv and EnVar
#include "exiv2/futils.hpp"

// Test normal operation: getEnv with envHTTPPOST returns default when env var is not set
TEST(GetEnvTest_1800, DefaultHTTPPOST_WhenEnvNotSet_1800) {
    // Unset the environment variable to ensure we get the default
#ifdef _WIN32
    _putenv_s("EXIV2_HTTP_POST", "");
    // On Windows, _putenv_s with empty string may not fully unset; use _putenv
    _putenv("EXIV2_HTTP_POST=");
#else
    unsetenv("EXIV2_HTTP_POST");
#endif
    std::string result = Exiv2::getEnv(Exiv2::envHTTPPOST);
    EXPECT_EQ(result, "/exiv2.php");
}

// Test normal operation: getEnv with envTIMEOUT returns default when env var is not set
TEST(GetEnvTest_1800, DefaultTIMEOUT_WhenEnvNotSet_1800) {
#ifdef _WIN32
    _putenv("EXIV2_TIMEOUT=");
#else
    unsetenv("EXIV2_TIMEOUT");
#endif
    std::string result = Exiv2::getEnv(Exiv2::envTIMEOUT);
    EXPECT_EQ(result, "40");
}

// Test normal operation: getEnv with envHTTPPOST returns custom value when env var is set
TEST(GetEnvTest_1800, CustomHTTPPOST_WhenEnvSet_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_HTTP_POST", "/custom.php");
#else
    setenv("EXIV2_HTTP_POST", "/custom.php", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envHTTPPOST);
    EXPECT_EQ(result, "/custom.php");

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_HTTP_POST=");
#else
    unsetenv("EXIV2_HTTP_POST");
#endif
}

// Test normal operation: getEnv with envTIMEOUT returns custom value when env var is set
TEST(GetEnvTest_1800, CustomTIMEOUT_WhenEnvSet_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_TIMEOUT", "120");
#else
    setenv("EXIV2_TIMEOUT", "120", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envTIMEOUT);
    EXPECT_EQ(result, "120");

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_TIMEOUT=");
#else
    unsetenv("EXIV2_TIMEOUT");
#endif
}

// Test boundary: getEnv with envHTTPPOST (lower bound = 0)
TEST(GetEnvTest_1800, LowerBoundEnvVar_1800) {
#ifdef _WIN32
    _putenv("EXIV2_HTTP_POST=");
#else
    unsetenv("EXIV2_HTTP_POST");
#endif
    EXPECT_NO_THROW({
        std::string result = Exiv2::getEnv(Exiv2::envHTTPPOST);
        EXPECT_FALSE(result.empty());
    });
}

// Test boundary: getEnv with envTIMEOUT (upper bound = 1)
TEST(GetEnvTest_1800, UpperBoundEnvVar_1800) {
#ifdef _WIN32
    _putenv("EXIV2_TIMEOUT=");
#else
    unsetenv("EXIV2_TIMEOUT");
#endif
    EXPECT_NO_THROW({
        std::string result = Exiv2::getEnv(Exiv2::envTIMEOUT);
        EXPECT_FALSE(result.empty());
    });
}

// Test error case: getEnv with value below envHTTPPOST should throw out_of_range
TEST(GetEnvTest_1800, BelowLowerBound_ThrowsOutOfRange_1800) {
    EXPECT_THROW(Exiv2::getEnv(Exiv2::envHTTPPOST - 1), std::out_of_range);
}

// Test error case: getEnv with value above envTIMEOUT should throw out_of_range
TEST(GetEnvTest_1800, AboveUpperBound_ThrowsOutOfRange_1800) {
    EXPECT_THROW(Exiv2::getEnv(Exiv2::envTIMEOUT + 1), std::out_of_range);
}

// Test error case: getEnv with a large negative value should throw out_of_range
TEST(GetEnvTest_1800, LargeNegativeValue_ThrowsOutOfRange_1800) {
    EXPECT_THROW(Exiv2::getEnv(-100), std::out_of_range);
}

// Test error case: getEnv with a large positive value should throw out_of_range
TEST(GetEnvTest_1800, LargePositiveValue_ThrowsOutOfRange_1800) {
    EXPECT_THROW(Exiv2::getEnv(100), std::out_of_range);
}

// Test that setting env var to empty string behaves correctly for HTTPPOST
TEST(GetEnvTest_1800, EmptyEnvVarHTTPPOST_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_HTTP_POST", "");
#else
    setenv("EXIV2_HTTP_POST", "", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envHTTPPOST);
    // When set to empty, on Unix getenv returns "" which is truthy (non-null pointer)
    // so the result should be empty string, not default
#ifndef _WIN32
    EXPECT_EQ(result, "");
#endif

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_HTTP_POST=");
#else
    unsetenv("EXIV2_HTTP_POST");
#endif
}

// Test that setting env var to empty string behaves correctly for TIMEOUT
TEST(GetEnvTest_1800, EmptyEnvVarTIMEOUT_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_TIMEOUT", "");
#else
    setenv("EXIV2_TIMEOUT", "", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envTIMEOUT);
#ifndef _WIN32
    EXPECT_EQ(result, "");
#endif

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_TIMEOUT=");
#else
    unsetenv("EXIV2_TIMEOUT");
#endif
}

// Test setting HTTPPOST env var with special characters
TEST(GetEnvTest_1800, SpecialCharsHTTPPOST_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_HTTP_POST", "/path/to/script.php?a=1&b=2");
#else
    setenv("EXIV2_HTTP_POST", "/path/to/script.php?a=1&b=2", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envHTTPPOST);
    EXPECT_EQ(result, "/path/to/script.php?a=1&b=2");

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_HTTP_POST=");
#else
    unsetenv("EXIV2_HTTP_POST");
#endif
}

// Test setting TIMEOUT env var with numeric string
TEST(GetEnvTest_1800, NumericTimeoutValue_1800) {
#ifdef _WIN32
    _putenv_s("EXIV2_TIMEOUT", "0");
#else
    setenv("EXIV2_TIMEOUT", "0", 1);
#endif
    std::string result = Exiv2::getEnv(Exiv2::envTIMEOUT);
    EXPECT_EQ(result, "0");

    // Cleanup
#ifdef _WIN32
    _putenv("EXIV2_TIMEOUT=");
#else
    unsetenv("EXIV2_TIMEOUT");
#endif
}
