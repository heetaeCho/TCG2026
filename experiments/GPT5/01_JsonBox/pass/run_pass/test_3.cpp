// File: ./TestProjects/JsonBox/tests/Convert_decodeUTF8_test_3.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Assuming headers are available like this:
#include "JsonBox/Convert.h"

using JsonBox::Convert;
using JsonBox::String32;

class ConvertTest_3 : public ::testing::Test {
protected:
    Convert conv;
};

// Empty input -> empty output
TEST_F(ConvertTest_3, Decode_EmptyString_ReturnsEmpty_3) {
    std::string in;
    String32 out = conv.decodeUTF8(in);
    EXPECT_TRUE(out.empty());
}

// ASCII roundtrip for simple characters (single-byte UTF-8)
TEST_F(ConvertTest_3, Decode_ASCII_Simple_3) {
    std::string in = "Hello";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 5u);
    EXPECT_EQ(out[0], 'H');
    EXPECT_EQ(out[1], 'e');
    EXPECT_EQ(out[2], 'l');
    EXPECT_EQ(out[3], 'l');
    EXPECT_EQ(out[4], 'o');
}

// Includes NUL byte inside the string (valid single byte)
TEST_F(ConvertTest_3, Decode_ContainsNullByte_3) {
    std::string in;
    in.push_back('A');
    in.push_back('\0');      // U+0000
    in.push_back('B');
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], 'A');
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 'B');
}

// 2-byte sequence: U+00A9 © -> C2 A9
TEST_F(ConvertTest_3, Decode_2Byte_UTF8_Copyright_3) {
    std::string in = "\xC2\xA9"; // ©
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x00A9);
}

// 3-byte sequence: U+20AC € -> E2 82 AC
TEST_F(ConvertTest_3, Decode_3Byte_UTF8_Euro_3) {
    std::string in = "\xE2\x82\xAC"; // €
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x20AC);
}

// 4-byte sequence: U+1F600 😀 -> F0 9F 98 80
TEST_F(ConvertTest_3, Decode_4Byte_UTF8_GrinningFace_3) {
    std::string in = "\xF0\x9F\x98\x80"; // 😀
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x1F600);
}

// Mixed string with ASCII + 2,3,4-byte sequences: "A©€😀"
TEST_F(ConvertTest_3, Decode_Mixed_ASCII_And_Multibyte_3) {
    std::string in = std::string("A")           // 41
                   + "\xC2\xA9"                 // © U+00A9
                   + "\xE2\x82\xAC"             // € U+20AC
                   + "\xF0\x9F\x98\x80";        // 😀 U+1F600
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 4u);
    EXPECT_EQ(out[0], 0x41);
    EXPECT_EQ(out[1], 0x00A9);
    EXPECT_EQ(out[2], 0x20AC);
    EXPECT_EQ(out[3], 0x1F600);
}

// Boundary of 2-byte range: lowest (U+0080) -> C2 80
TEST_F(ConvertTest_3, Decode_2Byte_LowestBoundary_0080_3) {
    std::string in = "\xC2\x80";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x0080);
}

// Boundary of 2-byte range: highest (U+07FF) -> DF BF
TEST_F(ConvertTest_3, Decode_2Byte_HighestBoundary_07FF_3) {
    std::string in = "\xDF\xBF";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x07FF);
}

// Boundary of 3-byte range: lowest (U+0800) -> E0 A0 80
TEST_F(ConvertTest_3, Decode_3Byte_LowestBoundary_0800_3) {
    std::string in = "\xE0\xA0\x80";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x0800);
}

// Boundary of 3-byte range: highest (U+FFFF) -> EF BF BF
TEST_F(ConvertTest_3, Decode_3Byte_HighestBoundary_FFFF_3) {
    std::string in = "\xEF\xBF\xBF";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0xFFFF);
}

// Non-standard 5-byte pattern the implementation appears to accept: F8 80 80 80 80 -> expect 0
TEST_F(ConvertTest_3, Decode_5Byte_AllZeroPayload_3) {
    std::string in = "\xF8\x80\x80\x80\x80";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x00000000);
}

// Non-standard 6-byte pattern the implementation appears to accept: FC 80 80 80 80 80 -> expect 0
TEST_F(ConvertTest_3, Decode_6Byte_AllZeroPayload_3) {
    std::string in = "\xFC\x80\x80\x80\x80\x80";
    String32 out = conv.decodeUTF8(in);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], 0x00000000);
}
