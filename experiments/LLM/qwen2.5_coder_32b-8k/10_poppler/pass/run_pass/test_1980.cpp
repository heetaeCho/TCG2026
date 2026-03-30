#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function noop_cb is part of a class or namespace, we will mock it if needed.

// However, since it's a simple static function and doesn't interact with any external dependencies,

// we can directly test its behavior.



size_t noop_cb(char * /*ptr*/, size_t size, size_t nmemb, void * /*ptr2*/) {

    return size * nmemb;

}



TEST(noop_cb_Test_1980, NormalOperation_1980) {

    // Test with normal values

    size_t size = 5;

    size_t nmemb = 10;

    EXPECT_EQ(noop_cb(nullptr, size, nmemb, nullptr), size * nmemb);

}



TEST(noop_cb_Test_1980, BoundaryCondition_ZeroSize_1980) {

    // Test with size as zero

    size_t size = 0;

    size_t nmemb = 10;

    EXPECT_EQ(noop_cb(nullptr, size, nmemb, nullptr), 0);

}



TEST(noop_cb_Test_1980, BoundaryCondition_ZeroNmemb_1980) {

    // Test with nmemb as zero

    size_t size = 5;

    size_t nmemb = 0;

    EXPECT_EQ(noop_cb(nullptr, size, nmemb, nullptr), 0);

}



TEST(noop_cb_Test_1980, BoundaryCondition_MaxValues_1980) {

    // Test with maximum possible values for size and nmemb

    size_t size = std::numeric_limits<size_t>::max();

    size_t nmemb = 1; // To avoid overflow in multiplication

    EXPECT_EQ(noop_cb(nullptr, size, nmemb, nullptr), size * nmemb);

}



TEST(noop_cb_Test_1980, BoundaryCondition_MaxValuesBoth_1980) {

    // Test with maximum possible values for both size and nmemb

    // This test is expected to overflow, so we check for the expected result of the multiplication overflow

    size_t size = std::numeric_limits<size_t>::max();

    size_t nmemb = 2; // To ensure overflow

    EXPECT_NE(noop_cb(nullptr, size, nmemb, nullptr), size * nmemb);

}



// Since the function is a simple multiplier and doesn't have any side effects or external interactions,

// there are no exceptional cases to test.
