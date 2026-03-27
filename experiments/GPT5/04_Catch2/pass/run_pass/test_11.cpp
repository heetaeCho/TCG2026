// File: stringref_begin_tests_11.cpp
#include <gtest/gtest.h>
#include <string>
#include <cstddef>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

class StringRefBeginTest_11 : public ::testing::Test {};

// Normal: non-empty C-string
TEST_F(StringRefBeginTest_11, BeginEqualsDataOnNonEmpty_11) {
    StringRef sr("hello");
    ASSERT_NE(sr.begin(), sr.end());
    EXPECT_EQ(sr.begin(), sr.data());
    EXPECT_EQ(*sr.begin(), 'h');
}

// Boundary: default-constructed empty
TEST_F(StringRefBeginTest_11, BeginEqualsEndOnEmptyDefault_11) {
    StringRef sr; // default-constructed
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
    EXPECT_EQ(sr.begin(), sr.end());
}

// Normal: constructed from std::string
TEST_F(StringRefBeginTest_11, BeginOnStdStringBacked_11) {
    std::string s = std::string("world");
    StringRef sr(s);
    ASSERT_NE(sr.begin(), sr.end());
    EXPECT_EQ(*sr.begin(), 'w');
    EXPECT_EQ(sr.begin(), sr.data()); // observable pointer equality through the interface
}

// Boundary: explicit size with embedded nulls
TEST_F(StringRefBeginTest_11, BeginWithExplicitSizeKeepsEmbeddedNulls_11) {
    const char buf[] = { 'a', '\0', 'b', 'c' };
    StringRef sr(buf, 4);
    ASSERT_EQ(sr.size(), 4u);
    ASSERT_NE(sr.begin(), sr.end());
    EXPECT_EQ(*sr.begin(), 'a');
    // Pointer distance equals size (observable through begin/end/size)
    EXPECT_EQ(static_cast<std::ptrdiff_t>(sr.end() - sr.begin()),
              static_cast<std::ptrdiff_t>(sr.size()));
    EXPECT_EQ(*(sr.end() - 1), 'c');
}

// Normal: substr produces view whose begin() points inside original
TEST_F(StringRefBeginTest_11, BeginOfSubstrPointsInsideOriginal_11) {
    StringRef sr("abcde");
    auto sub = sr.substr(1, 3); // expected "bcd"
    ASSERT_EQ(sub.size(), 3u);
    ASSERT_NE(sub.begin(), sub.end());
    EXPECT_EQ(*sub.begin(), 'b');
    // Compare via public data() to avoid any internal assumptions
    EXPECT_EQ(sub.begin(), sr.data() + 1);
}

// Boundary: empty substr has begin()==end()
TEST_F(StringRefBeginTest_11, BeginEqualsEndOnEmptySubstr_11) {
    StringRef sr("abc");
    auto emptySub = sr.substr(1, 0);
    EXPECT_TRUE(emptySub.empty());
    EXPECT_EQ(emptySub.size(), 0u);
    EXPECT_EQ(emptySub.begin(), emptySub.end());
}

// Const-correctness: begin() on const instance
TEST_F(StringRefBeginTest_11, BeginWorksOnConstInstance_11) {
    const StringRef sr("xy");
    const auto b = sr.begin();
    const auto e = sr.end();
    ASSERT_NE(b, e);
    EXPECT_EQ(*b, 'x');
}
