// File: stringref_eq_tests_4.cpp
#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

//
// Tests focus strictly on observable behavior of operator==
// No assumptions about private state or internal logic beyond the public interface.
//

TEST(StringRefTest_4, Equal_WhenSameCStringContent_4) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_4, Equal_WithExplicitLengthSamePrefix_4) {
    // Explicit-length should only compare the first N bytes
    const char* raw = "abcXYZ";
    StringRef a(raw, 3);         // "abc"
    StringRef b("abc");          // "abc"
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);         // symmetry (observable via ==)
}

TEST(StringRefTest_4, NotEqual_WhenDifferentSizes_4) {
    StringRef a("a");
    StringRef b("ab");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(StringRefTest_4, NotEqual_WhenSameSizeDifferentContent_4) {
    StringRef a("abc");
    StringRef b("abx");
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(StringRefTest_4, EmptyEquality_DefaultCtorVsEmptyLiterals_4) {
    StringRef def;               // default-constructed
    StringRef empty1("");
    StringRef empty2("ignored", 0); // explicit zero length
    EXPECT_TRUE(def == empty1);
    EXPECT_TRUE(empty1 == empty2);
    EXPECT_TRUE(def == empty2);
}

TEST(StringRefTest_4, Equal_WithEmbeddedNullBytes_4) {
    const char s1[] = { 'a', '\0', 'b' };
    const char s2[] = { 'a', '\0', 'b' };
    StringRef a(s1, 3);
    StringRef b(s2, 3);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

TEST(StringRefTest_4, NotEqual_WithEmbeddedNullBytesContentDiffers_4) {
    const char s1[] = { 'a', '\0', 'b' };
    const char s2[] = { 'a', '\0', 'c' };
    StringRef a(s1, 3);
    StringRef b(s2, 3);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(StringRefTest_4, SelfEquality_4) {
    std::string src = "self-check";
    StringRef a(src);
    EXPECT_TRUE(a == a);
}

TEST(StringRefTest_4, Equal_AcrossConstructors_CStringVsStdString_4) {
    const char* cstr = "mix-and-match";
    std::string cpp = "mix-and-match";
    StringRef a(cstr);
    StringRef b(cpp);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}
