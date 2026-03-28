#include "string_piece.h"
#include "string_piece_util.h"
#include <gtest/gtest.h>

class EqualsCaseInsensitiveASCIITest_126 : public ::testing::Test {};

// ------------------------------------------------------------
// Normal Case: Identical strings (same case)
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, IdenticalSameCase_126) {
    StringPiece a("Hello");
    StringPiece b("Hello");
    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Normal Case: Identical strings (different case)
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, IdenticalDifferentCase_126) {
    StringPiece a("Hello");
    StringPiece b("hElLo");
    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Boundary Case: Empty strings
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, BothEmpty_126) {
    StringPiece a("");
    StringPiece b("");
    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Boundary Case: One empty and one non-empty
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, OneEmptyOneNotEmpty_126) {
    StringPiece a("");
    StringPiece b("A");
    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Normal Case: Different length
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, DifferentLength_126) {
    StringPiece a("Hi");
    StringPiece b("Hii");
    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Normal Case: Same length but different characters (case-insensitive mismatch)
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, SameLengthDifferentCharacters_126) {
    StringPiece a("Hello");
    StringPiece b("Helxo");
    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Verify behavior on ASCII punctuation (case-insensitive but unchanged by ToLowerASCII)
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, PunctuationComparison_126) {
    StringPiece a("!?-");
    StringPiece b("!?-");
    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Test with explicitly provided length (non-null terminated)
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, ExplicitLengthStringPiece_126) {
    const char* data = "HelloWorld";
    StringPiece a(data, 5);  // "Hello"
    StringPiece b("hELLo");
    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// ------------------------------------------------------------
// Non-ASCII characters (should be compared byte-wise, not Unicode-case-folded)
// Observable behavior: mismatch for bytes not equal when lowercased ASCII
// ------------------------------------------------------------
TEST_F(EqualsCaseInsensitiveASCIITest_126, NonASCIIBytes_126) {
    const char a_bytes[] = { static_cast<char>(0xC3), static_cast<char>(0xA9), 0 }; // é UTF-8 first bytes
    const char b_bytes[] = { static_cast<char>(0xC3), static_cast<char>(0xA8), 0 }; // è UTF-8 first bytes
    StringPiece a(a_bytes);
    StringPiece b(b_bytes);
    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b)); // As ASCII, bytes differ
}
