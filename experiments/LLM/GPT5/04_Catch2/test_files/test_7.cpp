// stringref_empty_test.cpp
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include <utility>

// Adjust include as needed for your project layout.
// If your include root is the "Catch2/src" folder, use the following:
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// Compile-time check that the signature promises nothrow (part of the interface).
static_assert(noexcept(std::declval<const StringRef&>().empty()),
              "StringRef::empty() must be noexcept per interface");

class StringRefEmptyTest_7 : public ::testing::Test {};

// --- Normal operation ---

TEST(StringRefEmptyTest_7, DefaultConstructedIsEmpty_7) {
    StringRef s;
    EXPECT_TRUE(s.empty());
}

TEST(StringRefEmptyTest_7, CStrNonEmptyIsNotEmpty_7) {
    StringRef s("x");
    EXPECT_FALSE(s.empty());
}

TEST(StringRefEmptyTest_7, StdStringNonEmptyIsNotEmpty_7) {
    std::string v = "hello";
    StringRef s(v);
    EXPECT_FALSE(s.empty());
}

// --- Boundary conditions ---

TEST(StringRefEmptyTest_7, CStrEmptyIsEmpty_7) {
    StringRef s("");
    EXPECT_TRUE(s.empty());
}

TEST(StringRefEmptyTest_7, PointerAndSizeZeroIsEmpty_7) {
    const char* p = "abc";
    StringRef s(p, 0);
    EXPECT_TRUE(s.empty());
}

TEST(StringRefEmptyTest_7, SubstrZeroLengthIsEmpty_7) {
    StringRef base("abc");
    auto sub = base.substr(1, 0);
    EXPECT_TRUE(sub.empty());
}

// --- Consistency checks using only public API ---

TEST(StringRefEmptyTest_7, EmptyMatchesSizeEqualsZero_ForDefault_7) {
    StringRef s;
    EXPECT_EQ(s.size() == 0, s.empty());
}

TEST(StringRefEmptyTest_7, EmptyMatchesSizeEqualsZero_ForNonEmpty_7) {
    StringRef s("data");
    EXPECT_EQ(s.size() == 0, s.empty());
}

TEST(StringRefEmptyTest_7, EmptyMatchesSizeEqualsZero_ForExplicitZero_7) {
    StringRef s("data", 0);
    EXPECT_EQ(s.size() == 0, s.empty());
}
