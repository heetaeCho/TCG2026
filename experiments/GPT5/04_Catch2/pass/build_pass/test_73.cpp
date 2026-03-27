// File: catch_strnlen_test_73.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/catch_tostring.hpp"

using Catch::Detail::catch_strnlen;

namespace {

TEST(CatchStrnlenTest_73, ReturnsActualLengthWhenNullWithinN_73) {
    const char* s = "hello";
    std::size_t n = 10;
    EXPECT_EQ(catch_strnlen(s, n), static_cast<std::size_t>(5));
}

TEST(CatchStrnlenTest_73, ReturnsNWhenNoNullWithinRange_73) {
    // Deliberately no null terminator in the first n chars
    const char buf[3] = {'a', 'b', 'c'};
    EXPECT_EQ(catch_strnlen(buf, 3), static_cast<std::size_t>(3));
}

TEST(CatchStrnlenTest_73, ZeroNReturnsZero_73) {
    const char* s = "anything";
    EXPECT_EQ(catch_strnlen(s, 0), static_cast<std::size_t>(0));
}

TEST(CatchStrnlenTest_73, EmptyStringReturnsZero_73) {
    const char* s = "";
    EXPECT_EQ(catch_strnlen(s, 5), static_cast<std::size_t>(0));
}

TEST(CatchStrnlenTest_73, EmbeddedNullBeforeN_73) {
    const char buf[3] = {'x', '\0', 'y'};
    EXPECT_EQ(catch_strnlen(buf, 3), static_cast<std::size_t>(1));
}

TEST(CatchStrnlenTest_73, Boundary_NEqualsActualLength_73) {
    const char* s = "world"; // length 5, '\0' at index 5 (outside first 5 chars)
    EXPECT_EQ(catch_strnlen(s, 5), static_cast<std::size_t>(5));
}

TEST(CatchStrnlenTest_73, Boundary_NLessThanActualLength_73) {
    const char* s = "abcdef"; // length 6
    EXPECT_EQ(catch_strnlen(s, 3), static_cast<std::size_t>(3));
}

TEST(CatchStrnlenTest_73, LargeNGreaterThanLength_73) {
    const char* s = "hi"; // length 2
    EXPECT_EQ(catch_strnlen(s, 1000), static_cast<std::size_t>(2));
}

} // namespace
