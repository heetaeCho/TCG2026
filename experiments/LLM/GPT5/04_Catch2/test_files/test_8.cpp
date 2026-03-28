// StringRef_size_tests_8.cpp
#include <gtest/gtest.h>
#include <string>
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

TEST(StringRefSizeTest_8, DefaultConstructedHasZeroSize_8) {
    StringRef sr;
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(0u, actual);
}

TEST(StringRefSizeTest_8, FromCStringComputesSize_8) {
    const char* s = "hello";
    StringRef sr{s};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(5u, actual);
}

TEST(StringRefSizeTest_8, FromEmptyCStringIsZero_8) {
    const char* s = "";
    StringRef sr{s};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(0u, actual);
}

TEST(StringRefSizeTest_8, FromCStringExplicitLengthIsUsed_8) {
    const char* s = "hello";
    StringRef sr{s, 2};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(2u, actual);
}

TEST(StringRefSizeTest_8, FromCStringExplicitZeroLength_8) {
    const char* s = "hello";
    StringRef sr{s, 0};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(0u, actual);
}

TEST(StringRefSizeTest_8, FromStdStringReflectsStdStringSize_8) {
    std::string base = "world";
    StringRef sr{base};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(base.size(), actual);
}

TEST(StringRefSizeTest_8, SubstrMiddleHasRequestedLength_8) {
    StringRef sr{"abcdef"};
    auto sub = sr.substr(1, 3); // "bcd"
    auto actual = static_cast<std::size_t>(sub.size());
    EXPECT_EQ(3u, actual);
}

TEST(StringRefSizeTest_8, SubstrAtEndIsEmpty_8) {
    StringRef sr{"abcdef"};
    auto sub = sr.substr(sr.size(), 10); // start at end
    auto actual = static_cast<std::size_t>(sub.size());
    EXPECT_EQ(0u, actual);
}

TEST(StringRefSizeTest_8, ExplicitLengthCountsEmbeddedNulls_8) {
    const char raw[] = {'a', '\0', 'b', '\0'};
    StringRef sr{raw, 4};
    auto actual = static_cast<std::size_t>(sr.size());
    EXPECT_EQ(4u, actual);
}
