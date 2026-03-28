#include <gtest/gtest.h>

#include "UTF.cc"



namespace {



TEST(DecodeUtf8Test_1523, SingleByteAsciiCharacter_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = 'A'; // ASCII value for 'A' is 65

    EXPECT_EQ(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

    EXPECT_EQ(codep, 65U);

}



TEST(DecodeUtf8Test_1523, SingleByteNonAsciiCharacter_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xc3'; // Non-ASCII character

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, TwoByteCharacterStart_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xc3'; // Start of a two-byte character

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, TwoByteCharacterContinuation_1523) {

    uint32_t state = 0x6; // State after processing the start of a two-byte character

    uint32_t codep = 0;

    char byte = '\xa9'; // Continuation byte for copyright symbol (©)

    EXPECT_EQ(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

    EXPECT_EQ(codep, 169U); // Unicode code point for ©

}



TEST(DecodeUtf8Test_1523, ThreeByteCharacterStart_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xe2'; // Start of a three-byte character

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, ThreeByteCharacterContinuation_1523) {

    uint32_t state = 0x6; // State after processing the start of a three-byte character

    uint32_t codep = 0;

    char byte = '\x9c'; // Continuation byte for Euro symbol (€)

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, ThreeByteCharacterFinalContinuation_1523) {

    uint32_t state = 0x7; // State after processing the second byte of a three-byte character

    uint32_t codep = 0x9c0;

    char byte = '\x9d'; // Final continuation byte for Euro symbol (€)

    EXPECT_EQ(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

    EXPECT_EQ(codep, 8364U); // Unicode code point for €

}



TEST(DecodeUtf8Test_1523, FourByteCharacterStart_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xf0'; // Start of a four-byte character

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, FourByteCharacterContinuation_1523) {

    uint32_t state = 0x6; // State after processing the start of a four-byte character

    uint32_t codep = 0;

    char byte = '\x9f'; // Continuation byte for U+1F600 (grinning face emoji)

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, FourByteCharacterSecondContinuation_1523) {

    uint32_t state = 0x7; // State after processing the second byte of a four-byte character

    uint32_t codep = 0x9f0;

    char byte = '\x98'; // Second continuation byte for U+1F600 (grinning face emoji)

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, FourByteCharacterFinalContinuation_1523) {

    uint32_t state = 0x7; // State after processing the third byte of a four-byte character

    uint32_t codep = 0x9f980;

    char byte = '\x80'; // Final continuation byte for U+1F600 (grinning face emoji)

    EXPECT_EQ(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

    EXPECT_EQ(codep, 128512U); // Unicode code point for grinning face emoji

}



TEST(DecodeUtf8Test_1523, InvalidStartByte_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xff'; // Invalid start byte

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, InvalidContinuationByte_1523) {

    uint32_t state = 0x6; // State after processing the start of a two-byte character

    uint32_t codep = 0;

    char byte = '\xc3'; // Invalid continuation byte

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, OverlongEncoding_1523) {

    uint32_t state = UTF8_ACCEPT;

    uint32_t codep = 0;

    char byte = '\xc0'; // Start of an overlong encoding

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, OverlongContinuationByte_1523) {

    uint32_t state = 0x6; // State after processing the start of an overlong encoding

    uint32_t codep = 0;

    char byte = '\xa0'; // Continuation byte for overlong encoding

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



TEST(DecodeUtf8Test_1523, OutOfRangeCharacter_1523) {

    uint32_t state = 0x6; // State after processing the start of a four-byte character

    uint32_t codep = 0;

    char byte = '\xf4'; // Start byte for an out-of-range character (U+110000 and above)

    EXPECT_NE(decodeUtf8(&state, &codep, byte), UTF8_ACCEPT);

}



} // namespace
