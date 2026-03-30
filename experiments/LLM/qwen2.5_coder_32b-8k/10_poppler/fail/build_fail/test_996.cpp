#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/UnicodeMap.h"



using namespace testing;



TEST(UnicodeMapTest_996, GetEncodingName_ReturnsCorrectValue_996) {

    const char* encodingName = "UTF-8";

    UnicodeMap map(encodingName, true, 1);

    EXPECT_EQ(map.getEncodingName(), encodingName);

}



TEST(UnicodeMapTest_996, Match_ReturnsTrueForMatchingEncodingName_996) {

    const std::string encodingName = "ISO-8859-1";

    UnicodeMap map(encodingName.c_str(), false, 2);

    EXPECT_TRUE(map.match(encodingName));

}



TEST(UnicodeMapTest_996, Match_ReturnsFalseForNonMatchingEncodingName_996) {

    const std::string encodingName = "ISO-8859-1";

    UnicodeMap map(encodingName.c_str(), false, 2);

    EXPECT_FALSE(map.match("UTF-8"));

}



TEST(UnicodeMapTest_996, IsUnicode_ReturnsTrueWhenConstructedWithUnicodeOutTrue_996) {

    UnicodeMap map("ASCII", true, 3);

    EXPECT_TRUE(map.isUnicode());

}



TEST(UnicodeMapTest_996, IsUnicode_ReturnsFalseWhenConstructedWithUnicodeOutFalse_996) {

    UnicodeMap map("ASCII", false, 4);

    EXPECT_FALSE(map.isUnicode());

}



TEST(UnicodeMapTest_996, MapUnicode_ReturnsValidValueForKnownUnicode_996) {

    UnicodeMap map("ASCII", true, 5);

    char buffer[10];

    int result = map.mapUnicode('A', buffer, sizeof(buffer));

    EXPECT_EQ(result, 1); // Assuming 'A' maps to a single character

    EXPECT_STREQ(buffer, "A");

}



TEST(UnicodeMapTest_996, MapUnicode_ReturnsZeroForUnknownUnicode_996) {

    UnicodeMap map("ASCII", true, 6);

    char buffer[10];

    int result = map.mapUnicode(0xFFFF, buffer, sizeof(buffer));

    EXPECT_EQ(result, 0); // Assuming unknown Unicode returns no characters

}



TEST(UnicodeMapTest_996, MapUnicode_RespectsBufferSizeLimit_996) {

    UnicodeMap map("ASCII", true, 7);

    char buffer[1];

    int result = map.mapUnicode('A', buffer, sizeof(buffer));

    EXPECT_EQ(result, 0); // Buffer too small to fit any characters

}



TEST(UnicodeMapTest_996, Parse_ReturnsNonNullPointerForValidEncodingName_996) {

    auto map = UnicodeMap::parse("UTF-8");

    EXPECT_NE(map.get(), nullptr);

}



TEST(UnicodeMapTest_996, Parse_ReturnsNullPointerForInvalidEncodingName_996) {

    auto map = UnicodeMap::parse("INVALID_ENCODING");

    EXPECT_EQ(map.get(), nullptr);

}
