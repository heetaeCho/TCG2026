#include <gtest/gtest.h>

#include "UTF.h"



class UTFTest_1281 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(UTFTest_1281, IsUtf8WithBom_ReturnsFalse_ForEmptyString_1281) {

    std::string_view str = "";

    EXPECT_FALSE(isUtf8WithBom(str));

}



TEST_F(UTFTest_1281, IsUtf8WithBom_ReturnsFalse_ForShortStrings_1281) {

    std::string_view str1 = "a";

    std::string_view str2 = "ab";

    std::string_view str3 = "abc";



    EXPECT_FALSE(isUtf8WithBom(str1));

    EXPECT_FALSE(isUtf8WithBom(str2));

    EXPECT_FALSE(isUtf8WithBom(str3));

}



TEST_F(UTFTest_1281, IsUtf8WithBom_ReturnsTrue_ForValidUtf8Bom_1281) {

    std::string_view str = "\xef\xbb\xbf";

    EXPECT_TRUE(isUtf8WithBom(str));

}



TEST_F(UTFTest_1281, IsUtf8WithBom_ReturnsFalse_ForInvalidUtf8Bom_1281) {

    std::string_view str1 = "\xef\xbb\xbe"; // Incorrect third byte

    std::string_view str2 = "\xef\xb0\xbf"; // Incorrect second byte

    std::string_view str3 = "\xe0\xbb\xbf"; // Incorrect first byte



    EXPECT_FALSE(isUtf8WithBom(str1));

    EXPECT_FALSE(isUtf8WithBom(str2));

    EXPECT_FALSE(isUtf8WithBom(str3));

}



TEST_F(UTFTest_1281, IsUtf8WithBom_ReturnsFalse_ForStringsWithExtraCharacters_1281) {

    std::string_view str = "\xef\xbb\xbfextra";

    EXPECT_TRUE(isUtf8WithBom(str));

}
