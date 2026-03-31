#include <gtest/gtest.h>
#include <cstddef>

// We need to test the noop_cb function which is static in the .cc file.
// Since it's static, we cannot directly access it from outside the translation unit.
// However, we can include the .cc file to gain access to the static function for testing purposes.
// This is a common testing pattern for static functions.

// Forward declare or include the function
// Since noop_cb is static in CurlCachedFile.cc, we include the source to access it
// We need to be careful about other dependencies in that file.

// Alternative: declare the function signature and test via a wrapper
// But per constraints, we include the source file to access the static function.

// If direct inclusion causes issues due to dependencies, we replicate the exact function
// signature for testing. Since we must treat it as a black box and only test the interface,
// we test the observable behavior: return value = size * nmemb.

// Include the source file to access the static function
// This may require the poppler headers to be available
#include "CurlCachedFile.cc"

class NoopCbTest_1980 : public ::testing::Test {
protected:
    // The noop_cb function signature:
    // static size_t noop_cb(char *ptr, size_t size, size_t nmemb, void *ptr2)
};

// Test normal operation: typical size and nmemb values
TEST_F(NoopCbTest_1980, ReturnsProductOfSizeAndNmemb_1980)
{
    size_t result = noop_cb(nullptr, 1, 100, nullptr);
    EXPECT_EQ(result, 100u);
}

// Test with size > 1
TEST_F(NoopCbTest_1980, ReturnsProductWithLargerSize_1980)
{
    size_t result = noop_cb(nullptr, 4, 25, nullptr);
    EXPECT_EQ(result, 100u);
}

// Test boundary: size = 0
TEST_F(NoopCbTest_1980, ReturnsZeroWhenSizeIsZero_1980)
{
    size_t result = noop_cb(nullptr, 0, 100, nullptr);
    EXPECT_EQ(result, 0u);
}

// Test boundary: nmemb = 0
TEST_F(NoopCbTest_1980, ReturnsZeroWhenNmembIsZero_1980)
{
    size_t result = noop_cb(nullptr, 100, 0, nullptr);
    EXPECT_EQ(result, 0u);
}

// Test boundary: both size and nmemb = 0
TEST_F(NoopCbTest_1980, ReturnsZeroWhenBothAreZero_1980)
{
    size_t result = noop_cb(nullptr, 0, 0, nullptr);
    EXPECT_EQ(result, 0u);
}

// Test with size = 1 and nmemb = 1
TEST_F(NoopCbTest_1980, ReturnsOneForUnitValues_1980)
{
    size_t result = noop_cb(nullptr, 1, 1, nullptr);
    EXPECT_EQ(result, 1u);
}

// Test with large values
TEST_F(NoopCbTest_1980, HandlesLargeValues_1980)
{
    size_t result = noop_cb(nullptr, 1024, 1024, nullptr);
    EXPECT_EQ(result, 1024u * 1024u);
}

// Test that non-null pointers don't affect the result (they are unused)
TEST_F(NoopCbTest_1980, IgnoresPointerArguments_1980)
{
    char buffer[10] = "test";
    int userData = 42;
    size_t result = noop_cb(buffer, 5, 10, &userData);
    EXPECT_EQ(result, 50u);
}

// Test with size = 1 (common curl callback pattern where size is always 1)
TEST_F(NoopCbTest_1980, CommonCurlPatternSizeOne_1980)
{
    size_t result = noop_cb(nullptr, 1, 4096, nullptr);
    EXPECT_EQ(result, 4096u);
}

// Test commutativity of multiplication
TEST_F(NoopCbTest_1980, MultiplicationIsCommutative_1980)
{
    size_t result1 = noop_cb(nullptr, 3, 7, nullptr);
    size_t result2 = noop_cb(nullptr, 7, 3, nullptr);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 21u);
}
