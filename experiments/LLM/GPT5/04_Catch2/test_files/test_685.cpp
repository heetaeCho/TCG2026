// File: tests/stringref_plus_equal_685.cpp

#include <gtest/gtest.h>
#include <string>
#include <cstring>

#include "catch2/internal/catch_stringref.hpp"  // adjust include path if needed

using Catch::StringRef;

class StringRefPlusEqualTest_685 : public ::testing::Test {};

// Normal operation: append non-empty StringRef to non-empty std::string
TEST_F(StringRefPlusEqualTest_685, AppendNonEmptyToNonEmpty_685) {
    std::string lhs = "Hello";
    StringRef rhs(" World");

    std::string& ret = (lhs += rhs);

    EXPECT_EQ(lhs, "Hello World");
    EXPECT_EQ(&ret, &lhs) << "operator+= should return reference to lhs";
}

// Append to empty lhs
TEST_F(StringRefPlusEqualTest_685, AppendToEmptyLhs_685) {
    std::string lhs;
    StringRef rhs("abc");

    lhs += rhs;

    EXPECT_EQ(lhs, "abc");
    EXPECT_EQ(lhs.size(), 3u);
}

// Append empty rhs (no-op)
TEST_F(StringRefPlusEqualTest_685, AppendEmptyRhsNoChange_685) {
    std::string lhs = "abc";
    StringRef rhs("");  // empty

    lhs += rhs;

    EXPECT_EQ(lhs, "abc");
    EXPECT_EQ(lhs.size(), 3u);
}

// Append StringRef constructed with (char*, size), including embedded nulls
TEST_F(StringRefPlusEqualTest_685, AppendEmbeddedNullBytes_685) {
    std::string lhs = "X";

    const char buf[] = { 'a', '\0', 'b' };
    StringRef rhs(buf, sizeof(buf));  // size=3, includes the null byte

    lhs += rhs;

    std::string expected;
    expected.push_back('X');
    expected.append(buf, sizeof(buf));  // "Xa\0b" (4 bytes)

    EXPECT_EQ(lhs.size(), expected.size());
    EXPECT_EQ(lhs, expected);
    // Spot-check positions around the null
    EXPECT_EQ(lhs[0], 'X');
    EXPECT_EQ(lhs[1], 'a');
    EXPECT_EQ(lhs[2], '\0');
    EXPECT_EQ(lhs[3], 'b');
}

// Chaining: ensure operator returns lhs reference and supports repeated appends
TEST_F(StringRefPlusEqualTest_685, ChainedAppendReturnsLhsRef_685) {
    std::string lhs = "start";
    StringRef r1("_one");
    StringRef r2("_two");

    std::string& ref1 = (lhs += r1);
    EXPECT_EQ(&ref1, &lhs);

    (lhs += r2) += r1;  // chain further

    EXPECT_EQ(lhs, "start_one_two_one");
}

// UTF-8 bytes are handled transparently (treat as raw bytes)
TEST_F(StringRefPlusEqualTest_685, AppendUtf8Bytes_685) {
    std::string lhs = "ok ";
    const char* utf8 = u8"테스트";  // multibyte UTF-8 sequence
    StringRef rhs(utf8);

    lhs += rhs;

    std::string expected = std::string("ok ") + utf8;
    EXPECT_EQ(lhs, expected);
    EXPECT_EQ(lhs.size(), expected.size());
}

// Construct from std::string and append
TEST_F(StringRefPlusEqualTest_685, AppendFromStdStringCtor_685) {
    std::string lhs = "pre-";
    std::string src = "source";
    StringRef rhs(src);  // ctor from std::string

    lhs += rhs;

    EXPECT_EQ(lhs, "pre-source");
}
