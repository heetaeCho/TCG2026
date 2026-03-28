// stringref_substr_test_9.cpp
#include <gtest/gtest.h>
#include <string>
#include <limits>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ---- A small compile-time check that substr is constexpr-capable ----
namespace {
constexpr StringRef kSrcConstexpr("abcdef", 6);
constexpr StringRef kSubConstexpr = kSrcConstexpr.substr(1, 3);
static_assert(kSubConstexpr.size() == 3, "substr size should be 3");
static_assert(kSubConstexpr[0] == 'b', "first char should be 'b'");
static_assert(!kSubConstexpr.empty(), "result should not be empty");
} // namespace

// ------------------------- Runtime tests ------------------------------

TEST(StringRefSubstrTest_9, ReturnsMiddlePortion_9) {
    StringRef s("hello world", 11);
    auto sub = s.substr(6, 5); // "world"
    EXPECT_EQ(static_cast<std::string>(sub), "world");
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_FALSE(sub.empty());
    EXPECT_EQ(sub[0], 'w');
}

TEST(StringRefSubstrTest_9, LengthIsClippedWhenTooLong_9) {
    StringRef s("hello", 5);
    auto sub = s.substr(2, 1000); // request past end -> clipped to "llo"
    EXPECT_EQ(static_cast<std::string>(sub), "llo");
    EXPECT_EQ(sub.size(), 3u);
}

TEST(StringRefSubstrTest_9, StartEqualsSizeReturnsEmpty_9) {
    StringRef s("abc", 3);
    auto sub = s.substr(3, 10);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
    EXPECT_EQ(static_cast<std::string>(sub), "");
}

TEST(StringRefSubstrTest_9, StartGreaterThanSizeReturnsEmpty_9) {
    StringRef s("abc", 3);
    auto sub = s.substr(4, 1);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
    EXPECT_EQ(static_cast<std::string>(sub), "");
}

TEST(StringRefSubstrTest_9, ZeroLengthReturnsEmpty_9) {
    StringRef s("abc", 3);
    auto sub = s.substr(1, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
    EXPECT_EQ(static_cast<std::string>(sub), "");
}

TEST(StringRefSubstrTest_9, FullStringWhenLengthEqualsSize_9) {
    StringRef s("abc", 3);
    auto sub = s.substr(0, 3);
    // Use observable equality via operator== on the public interface
    EXPECT_TRUE(sub == s);
    EXPECT_EQ(static_cast<std::string>(sub), "abc");
    EXPECT_EQ(sub.size(), 3u);
}

TEST(StringRefSubstrTest_9, LastCharacterSlice_9) {
    StringRef s("xyz", 3);
    auto sub = s.substr(2, 1);
    EXPECT_EQ(static_cast<std::string>(sub), "z");
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_FALSE(sub.empty());
    EXPECT_EQ(sub[0], 'z');
}

TEST(StringRefSubstrTest_9, WorksWithStdStringConstructor_9) {
    std::string base = "std::string backed";
    StringRef s(base);
    auto sub = s.substr(6, 6); // "string"
    EXPECT_EQ(static_cast<std::string>(sub), "string");
    EXPECT_EQ(sub.size(), 6u);
}

TEST(StringRefSubstrTest_9, VeryLargeRequestedLengthIsSafelyClipped_9) {
    StringRef s("clip", 4);
    auto sub = s.substr(1, std::numeric_limits<std::size_t>::max()); // ask huge length
    EXPECT_EQ(static_cast<std::string>(sub), "lip");
    EXPECT_EQ(sub.size(), 3u);
}
