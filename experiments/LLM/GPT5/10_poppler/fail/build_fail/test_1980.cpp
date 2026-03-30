#include <gtest/gtest.h>

// Function declaration for the noop_cb from the provided code
static size_t noop_cb(char* /*ptr*/, size_t size, size_t nmemb, void* /*ptr2*/) {
    return size * nmemb;
}

// Test case for normal operation: Ensuring noop_cb returns the correct size calculation.
TEST_F(NoopCallbackTest_1980, ReturnsCorrectSize_1980) {
    // Given
    size_t size = 10;
    size_t nmemb = 5;
    
    // When
    size_t result = noop_cb(nullptr, size, nmemb, nullptr);
    
    // Then
    EXPECT_EQ(result, size * nmemb) << "Expected size * nmemb to be " << size * nmemb;
}

// Test case for boundary condition: Ensuring noop_cb handles edge case of 0 size and 0 nmemb correctly.
TEST_F(NoopCallbackTest_1981, HandlesZeroSizeAndNmemb_1981) {
    // Given
    size_t size = 0;
    size_t nmemb = 0;
    
    // When
    size_t result = noop_cb(nullptr, size, nmemb, nullptr);
    
    // Then
    EXPECT_EQ(result, 0) << "Expected the result to be 0 when size and nmemb are both 0";
}

// Test case for boundary condition: Ensuring noop_cb handles extremely large values of size and nmemb correctly.
TEST_F(NoopCallbackTest_1982, HandlesLargeSizeAndNmemb_1982) {
    // Given
    size_t size = 1000000;
    size_t nmemb = 1000000;
    
    // When
    size_t result = noop_cb(nullptr, size, nmemb, nullptr);
    
    // Then
    EXPECT_EQ(result, size * nmemb) << "Expected size * nmemb to be " << size * nmemb;
}

// Test case for exceptional case: Ensuring noop_cb doesn't cause errors with large values (no error expected).
TEST_F(NoopCallbackTest_1983, NoErrorWithLargeValues_1983) {
    // Given
    size_t size = 1000000;
    size_t nmemb = 1000000;
    
    // When
    size_t result = noop_cb(nullptr, size, nmemb, nullptr);
    
    // Then
    EXPECT_NO_THROW({
        EXPECT_EQ(result, size * nmemb) << "Expected size * nmemb to be " << size * nmemb;
    }) << "Expected no exception to be thrown";
}