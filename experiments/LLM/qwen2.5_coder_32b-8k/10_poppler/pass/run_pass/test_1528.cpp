#include <gtest/gtest.h>

#include "UTF.cc"



TEST(decodeUtf16Test_1528, NormalSingleCodeUnit_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t codeUnit = 0x41; // 'A'



    EXPECT_EQ(decodeUtf16(&state, &codePoint, codeUnit), UTF16_ACCEPT);

    EXPECT_EQ(codePoint, 0x41);

}



TEST(decodeUtf16Test_1528, NormalHighSurrogateFollowedByLowSurrogate_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t highSurrogate = 0xd834; // High surrogate for musical symbol G clef

    uint16_t lowSurrogate = 0xdd1e;  // Low surrogate for musical symbol G clef



    EXPECT_EQ(decodeUtf16(&state, &codePoint, highSurrogate), highSurrogate);

    EXPECT_EQ(decodeUtf16(&state, &codePoint, lowSurrogate), UTF16_ACCEPT);

    EXPECT_EQ(codePoint, 0x1d11e); // Code point for musical symbol G clef

}



TEST(decodeUtf16Test_1528, InvalidLowSurrogateWithoutHighSurrogate_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t lowSurrogate = 0xdc00;



    EXPECT_EQ(decodeUtf16(&state, &codePoint, lowSurrogate), UTF16_REJECT);

}



TEST(decodeUtf16Test_1528, InvalidHighSurrogateFollowedByNonLowSurrogate_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t highSurrogate = 0xd834; // High surrogate for musical symbol G clef

    uint16_t nonLowSurrogate = 0x42;  // 'B'



    EXPECT_EQ(decodeUtf16(&state, &codePoint, highSurrogate), highSurrogate);

    EXPECT_EQ(decodeUtf16(&state, &codePoint, nonLowSurrogate), UTF16_REJECT);

}



TEST(decodeUtf16Test_1528, BoundaryHighSurrogateRangeStart_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t highSurrogate = 0xd800;



    EXPECT_EQ(decodeUtf16(&state, &codePoint, highSurrogate), highSurrogate);

}



TEST(decodeUtf16Test_1528, BoundaryHighSurrogateRangeEnd_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t highSurrogate = 0xdbff;



    EXPECT_EQ(decodeUtf16(&state, &codePoint, highSurrogate), highSurrogate);

}



TEST(decodeUtf16Test_1528, BoundaryLowSurrogateRangeStart_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t lowSurrogate = 0xdc00;



    EXPECT_EQ(decodeUtf16(&state, &codePoint, lowSurrogate), UTF16_REJECT);

}



TEST(decodeUtf16Test_1528, BoundaryLowSurrogateRangeEnd_1528) {

    uint32_t state = 0;

    uint32_t codePoint;

    uint16_t lowSurrogate = 0xdfff;



    EXPECT_EQ(decodeUtf16(&state, &codePoint, lowSurrogate), UTF16_REJECT);

}
