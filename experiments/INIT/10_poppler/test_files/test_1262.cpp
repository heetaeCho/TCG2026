#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdarg>

namespace Poppler {
    static int poppler_vasprintf(char **buf_ptr, const char *format, va_list ap) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        const size_t size = vsnprintf(nullptr, 0, format, ap_copy) + 1;
        va_end(ap_copy);
        *buf_ptr = new char[size];
        return qvsnprintf(*buf_ptr, size, format, ap);
    }
}

class PopplerVasprintfTest_1262 : public ::testing::Test {};

// Test: Normal operation with simple string formatting
TEST_F(PopplerVasprintfTest_1262, FormatString_Success_1262) {
    char *result = nullptr;
    const char *format = "Hello, %s!";
    const char *name = "World";
    va_list ap;
    va_start(ap, name);
    int ret = Poppler::poppler_vasprintf(&result, format, ap);
    va_end(ap);

    EXPECT_EQ(ret, 13);  // Length of "Hello, World!"
    EXPECT_STREQ(result, "Hello, World!");

    delete[] result;
}

// Test: Boundary condition with no formatting (empty string)
TEST_F(PopplerVasprintfTest_1262, FormatEmptyString_Success_1262) {
    char *result = nullptr;
    const char *format = "";
    va_list ap;
    va_start(ap, format);
    int ret = Poppler::poppler_vasprintf(&result, format, ap);
    va_end(ap);

    EXPECT_EQ(ret, 1);  // Length of empty string + 1 for null terminator
    EXPECT_STREQ(result, "");

    delete[] result;
}

// Test: Boundary condition with a large buffer (to test handling of large strings)
TEST_F(PopplerVasprintfTest_1262, FormatLargeString_Success_1262) {
    char *result = nullptr;
    const char *format = "This is a very large string: %s";
    const char *large_string = "A".repeat(1000);  // Simulate a large string
    va_list ap;
    va_start(ap, large_string);
    int ret = Poppler::poppler_vasprintf(&result, format, ap);
    va_end(ap);

    EXPECT_GT(ret, 1000);  // Ensure that the formatted string is large enough
    EXPECT_NE(result, nullptr);

    delete[] result;
}

// Test: Exceptional case with invalid format string
TEST_F(PopplerVasprintfTest_1262, InvalidFormatString_Error_1262) {
    char *result = nullptr;
    const char *format = "Invalid format: %";
    va_list ap;
    va_start(ap, format);
    int ret = Poppler::poppler_vasprintf(&result, format, ap);
    va_end(ap);

    EXPECT_LT(ret, 0);  // Expect an error code (negative return value)
    EXPECT_EQ(result, nullptr);  // No result should be allocated

    delete[] result;
}

// Test: Exceptional case with a NULL pointer as the format string
TEST_F(PopplerVasprintfTest_1262, NullFormatString_Error_1262) {
    char *result = nullptr;
    const char *format = nullptr;
    va_list ap;
    va_start(ap, format);
    int ret = Poppler::poppler_vasprintf(&result, format, ap);
    va_end(ap);

    EXPECT_LT(ret, 0);  // Expect an error code (negative return value)
    EXPECT_EQ(result, nullptr);  // No result should be allocated

    delete[] result;
}