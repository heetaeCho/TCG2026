#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"



TEST(WXMPUtils_EncodeToBase64_1950, NormalOperation_1950) {

    XMP_StringPtr rawStr = "HelloWorld";

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);



    ASSERT_NE(encodedStr, nullptr);

    EXPECT_EQ(encodedLen, 16); // Base64 encoded length of "HelloWorld" is 16

    EXPECT_STREQ(encodedStr, "SGVsbG8gV29ybGQ=");

}



TEST(WXMPUtils_EncodeToBase64_1950, EmptyString_1950) {

    XMP_StringPtr rawStr = "";

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);



    ASSERT_NE(encodedStr, nullptr);

    EXPECT_EQ(encodedLen, 0); // Base64 encoded length of "" is 0

    EXPECT_STREQ(encodedStr, "");

}



TEST(WXMPUtils_EncodeToBase64_1950, NullEncodedStrPointer_1950) {

    XMP_StringPtr rawStr = "HelloWorld";

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, nullptr, &encodedLen, &wResult);



    EXPECT_EQ(encodedLen, 0); // encodedLen should not change

}



TEST(WXMPUtils_EncodeToBase64_1950, NullEncodedLenPointer_1950) {

    XMP_StringPtr rawStr = "HelloWorld";

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, nullptr, &wResult);



    ASSERT_NE(encodedStr, nullptr);

}



TEST(WXMPUtils_EncodeToBase64_1950, NullRawStrPointer_1950) {

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(nullptr, 0, &encodedStr, &encodedLen, &wResult);



    ASSERT_NE(encodedStr, nullptr);

    EXPECT_EQ(encodedLen, 0); // Base64 encoded length of null string is 0

    EXPECT_STREQ(encodedStr, "");

}



TEST(WXMPUtils_EncodeToBase64_1950, LargeString_1950) {

    std::string largeStr(1024, 'A'); // Large string of 1024 'A's

    XMP_StringPtr rawStr = largeStr.c_str();

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);



    ASSERT_NE(encodedStr, nullptr);

    EXPECT_EQ(encodedLen, 1367); // Base64 encoded length of 1024 'A's is 1367

}



TEST(WXMPUtils_EncodeToBase64_1950, SpecialCharacters_1950) {

    XMP_StringPtr rawStr = "!@#$%^&*()";

    XMP_StringLen rawLen = strlen(rawStr);

    XMP_StringPtr encodedStr = nullptr;

    XMP_StringLen encodedLen = 0;

    WXMP_Result wResult;



    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);



    ASSERT_NE(encodedStr, nullptr);

    EXPECT_EQ(encodedLen, 12); // Base64 encoded length of "!@#$%^&*()" is 12

    EXPECT_STREQ(encodedStr, "IUAjJCVeJioqKA==");

}
