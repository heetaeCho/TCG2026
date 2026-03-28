#include <gtest/gtest.h>
#include "exiv2/slice.hpp"
#include <stdexcept>

using namespace Exiv2::Internal;

// Test normal construction with valid begin and end
TEST(SliceBaseTest_2146, ConstructWithValidRange_2146) {
    EXPECT_NO_THROW(SliceBase sb(0, 1));
}

TEST(SliceBaseTest_2146, ConstructWithLargerRange_2146) {
    EXPECT_NO_THROW(SliceBase sb(0, 100));
}

TEST(SliceBaseTest_2146, ConstructWithNonZeroBegin_2146) {
    EXPECT_NO_THROW(SliceBase sb(5, 10));
}

TEST(SliceBaseTest_2146, ConstructWithAdjacentValues_2146) {
    EXPECT_NO_THROW(SliceBase sb(99, 100));
}

// Test that begin >= end throws std::out_of_range
TEST(SliceBaseTest_2146, ConstructWithBeginEqualToEndThrows_2146) {
    EXPECT_THROW(SliceBase sb(5, 5), std::out_of_range);
}

TEST(SliceBaseTest_2146, ConstructWithBeginGreaterThanEndThrows_2146) {
    EXPECT_THROW(SliceBase sb(10, 5), std::out_of_range);
}

TEST(SliceBaseTest_2146, ConstructWithZeroBeginAndZeroEndThrows_2146) {
    EXPECT_THROW(SliceBase sb(0, 0), std::out_of_range);
}

TEST(SliceBaseTest_2146, ConstructWithLargeBeginGreaterThanEndThrows_2146) {
    EXPECT_THROW(SliceBase sb(1000, 999), std::out_of_range);
}

// Test size() returns correct value
TEST(SliceBaseTest_2146, SizeReturnsCorrectValue_2146) {
    SliceBase sb(0, 10);
    EXPECT_EQ(sb.size(), 10u);
}

TEST(SliceBaseTest_2146, SizeReturnsOneForAdjacentValues_2146) {
    SliceBase sb(5, 6);
    EXPECT_EQ(sb.size(), 1u);
}

TEST(SliceBaseTest_2146, SizeWithNonZeroBegin_2146) {
    SliceBase sb(3, 8);
    EXPECT_EQ(sb.size(), 5u);
}

TEST(SliceBaseTest_2146, SizeWithLargeRange_2146) {
    SliceBase sb(0, 100000);
    EXPECT_EQ(sb.size(), 100000u);
}

TEST(SliceBaseTest_2146, SizeWithOffsetRange_2146) {
    SliceBase sb(50, 150);
    EXPECT_EQ(sb.size(), 100u);
}

// Boundary: maximum size_t values
TEST(SliceBaseTest_2146, ConstructWithLargeValidValues_2146) {
    size_t large = static_cast<size_t>(-1); // max size_t
    size_t almostLarge = large - 1;
    EXPECT_NO_THROW(SliceBase sb(almostLarge, large));
}

TEST(SliceBaseTest_2146, ConstructWithMaxBeginEqualMaxEndThrows_2146) {
    size_t large = static_cast<size_t>(-1);
    EXPECT_THROW(SliceBase sb(large, large), std::out_of_range);
}

// Test exception message content
TEST(SliceBaseTest_2146, ExceptionMessageIsCorrect_2146) {
    try {
        SliceBase sb(5, 5);
        FAIL() << "Expected std::out_of_range";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "Begin must be smaller than end");
    }
}

TEST(SliceBaseTest_2146, ExceptionMessageWhenBeginGreater_2146) {
    try {
        SliceBase sb(10, 5);
        FAIL() << "Expected std::out_of_range";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "Begin must be smaller than end");
    }
}
