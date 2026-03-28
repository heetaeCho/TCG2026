// File: catch_convert_signed_char_ptr_test_82.cpp
#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"  // Path from the prompt

// Shorthand to the function under test
using ::Catch::convert;

class CatchConvertSignedCharPtrTest_82 : public ::testing::Test {};

// [Normal] Basic ASCII should be copied verbatim
TEST_F(CatchConvertSignedCharPtrTest_82, BasicAscii_82) {
    const char* src = "hello, world";
    const signed char* s = reinterpret_cast<const signed char*>(src);

    std::string out = convert(s);

    EXPECT_EQ(out, "hello, world");
}

// [Boundary] Empty string should yield empty std::string
TEST_F(CatchConvertSignedCharPtrTest_82, EmptyString_82) {
    const char* src = "";
    const signed char* s = reinterpret_cast<const signed char*>(src);

    std::string out = convert(s);

    EXPECT_TRUE(out.empty());
    EXPECT_EQ(out.size(), 0u);
}

// [Boundary] Embedded NUL terminator — conversion should stop at first '\0'
TEST_F(CatchConvertSignedCharPtrTest_82, StopsAtFirstNull_82) {
    // signed char buffer with embedded '\0'
    const signed char buf[] = { 'A', 'B', '\0', 'C', 'D', '\0' };

    std::string out = convert(buf);

    EXPECT_EQ(out, "AB");
    EXPECT_EQ(out.size(), 2u);
}

// [Normal] Non-ASCII bytes preserved (e.g., UTF-8 sequence)
// Here we pass bytes C3 A9 which is "é" in UTF-8. We compare raw bytes.
TEST_F(CatchConvertSignedCharPtrTest_82, NonAsciiUtf8BytesPreserved_82) {
    const signed char buf[] = { static_cast<signed char>(0xC3),
                                static_cast<signed char>(0xA9),
                                0x00 }; // NUL

    std::string out = convert(buf);

    // Expected raw 2-byte sequence "\xC3\xA9"
    const std::string expected("\xC3\xA9", 2);
    EXPECT_EQ(out, expected);
    EXPECT_EQ(out.size(), expected.size());
}

// [Normal] Reasonably sized longer string (well below any typical internal cap)
TEST_F(CatchConvertSignedCharPtrTest_82, LongerString_82) {
    std::string thirtyTwo(32, 'x'); // 32 'x' characters
    // Build a signed char buffer with trailing NUL
    std::string withNull = thirtyTwo + '\0';
    const signed char* s =
        reinterpret_cast<const signed char*>(withNull.c_str());

    std::string out = convert(s);

    EXPECT_EQ(out, thirtyTwo);
    EXPECT_EQ(out.size(), thirtyTwo.size());
}
