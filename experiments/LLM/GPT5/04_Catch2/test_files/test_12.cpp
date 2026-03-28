// StringRef_end_tests_12.cpp
#include <gtest/gtest.h>
#include <string>
#include <iterator> // std::distance
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

TEST(StringRefEndTest_12, EmptyHasBeginEqEnd_12) {
    // Default-constructed: empty range => begin() == end(), distance == 0
    StringRef s;

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);

    EXPECT_EQ(s.begin(), s.end());
    EXPECT_EQ(std::distance(s.begin(), s.end()), 0);

    // For an empty range, end() should equal data() + size() (i.e., data()).
    EXPECT_EQ(s.end(), s.data());
}

TEST(StringRefEndTest_12, DistanceEqualsSizeForCString_12) {
    // Construct from C-string; iterating [begin, end) should yield the characters.
    StringRef s("abc");

    EXPECT_EQ(std::distance(s.begin(), s.end()),
              static_cast<std::ptrdiff_t>(s.size()));

    // Roundtrip via iterator range must match expected contents.
    std::string roundtrip(s.begin(), s.end());
    EXPECT_EQ(roundtrip, "abc");

    // end() should be exactly data() + size()
    EXPECT_EQ(s.end(), s.data() + s.size());
}

TEST(StringRefEndTest_12, WorksWithEmbeddedNulls_12) {
    // Construct from (ptr, size) so embedded '\0' is part of the view.
    const char raw[] = { 'a', '\0', 'b', 'c', 'd' };
    StringRef s(raw, 5);

    EXPECT_EQ(std::distance(s.begin(), s.end()), 5);

    std::string roundtrip(s.begin(), s.end());
    EXPECT_EQ(roundtrip.size(), 5u);
    EXPECT_EQ(roundtrip, std::string("a\0bcd", 5));

    EXPECT_EQ(s.end(), s.data() + s.size());
}

TEST(StringRefEndTest_12, SubstrRespectsEnd_12) {
    // Substring view: iteration limits and end pointer must align with size()
    StringRef s("hello");
    auto sub = s.substr(1, 3); // expected "ell"

    EXPECT_EQ(std::distance(sub.begin(), sub.end()),
              static_cast<std::ptrdiff_t>(sub.size()));

    std::string roundtrip(sub.begin(), sub.end());
    EXPECT_EQ(roundtrip, "ell");

    EXPECT_EQ(sub.end(), sub.data() + sub.size());
}

TEST(StringRefEndTest_12, SubstrAtSizeIsEmpty_12) {
    // Boundary: start at size() should produce an empty view.
    StringRef s("hi");
    auto sub = s.substr(s.size(), 10); // start at end

    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.begin(), sub.end());
    EXPECT_EQ(std::distance(sub.begin(), sub.end()), 0);
    EXPECT_EQ(sub.end(), sub.data()); // data() + size() for empty view
}
