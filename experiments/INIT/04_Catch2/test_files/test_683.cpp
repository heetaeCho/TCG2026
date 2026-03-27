// File: tests/stringref_ostream_tests_683.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the public interface only
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

class StringRefOstream_683 : public ::testing::Test {};

TEST_F(StringRefOstream_683, WritesPlainAscii_683) {
    // Normal operation: streaming a typical string
    StringRef sr("hello");
    std::ostringstream os;

    os << sr;

    EXPECT_EQ(os.str(), std::string("hello"));
    EXPECT_EQ(os.str().size(), static_cast<size_t>(5));
}

TEST_F(StringRefOstream_683, WritesEmptyString_683) {
    // Boundary: empty string should not change the stream
    StringRef empty("");  // empty via C-string constructor
    std::ostringstream os;
    os << empty;

    EXPECT_TRUE(os.str().empty());
    EXPECT_EQ(os.str().size(), static_cast<size_t>(0));
}

TEST_F(StringRefOstream_683, WritesEmbeddedNulls_683) {
    // Boundary/behavioral: embedded '\0' must be preserved (no implicit strlen)
    const char data[] = { 'A', '\0', 'B' };
    StringRef sr(data, 3);  // use (ptr, size) ctor to include the null byte
    std::ostringstream os;

    os << sr;

    const std::string expected("A\0B", 3);
    ASSERT_EQ(os.str().size(), expected.size());
    EXPECT_EQ(os.str(), expected);  // std::string compares size+bytes, including '\0'
}

TEST_F(StringRefOstream_683, ReturnsOriginalStreamForChaining_683) {
    // API/interaction: operator<< should return the same ostream& for chaining
    StringRef a("foo");
    StringRef b("bar");
    std::ostringstream os;

    std::ostream& ret = (os << a);
    // Returned reference must be the same stream object (by address)
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));

    // And chaining should work as usual
    os << b;
    EXPECT_EQ(os.str(), std::string("foobar"));
}

TEST_F(StringRefOstream_683, MultipleWritesAccumulate_683) {
    // Normal + idempotent accumulation across multiple insertions
    std::ostringstream os;
    os << StringRef("x") << StringRef("y") << StringRef("z");

    EXPECT_EQ(os.str(), std::string("xyz"));
}

TEST_F(StringRefOstream_683, LargeWrite_NoExtraCharacters_683) {
    // Stress-ish boundary: ensure exact number of bytes written (no extra terminators)
    const size_t N = 10000;
    std::string big(N, 'q');         // N 'q's
    StringRef sr(big.c_str(), big.size());
    std::ostringstream os;

    os << sr;

    EXPECT_EQ(os.str().size(), N);
    EXPECT_EQ(os.str(), big);
}
