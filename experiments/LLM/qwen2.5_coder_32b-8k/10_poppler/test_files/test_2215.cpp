#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "UnicodeMap.h"



using namespace testing;



class UnicodeMapMock : public UnicodeMap {

public:

    MOCK_METHOD3(mapUnicode, int(Unicode u, char * buf, int bufSize));

};



TEST(UnicodeToCharTest_2215, NormalOperation_2215) {

    Unicode unicode[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"

    char expected[] = "Hello";

    

    UnicodeMapMock uMapMock;

    EXPECT_CALL(uMapMock, mapUnicode(0x48, _, 8)).WillOnce(DoAll(SetArrayArgument<1>("H", "H" + 1), Return(1)));

    EXPECT_CALL(uMapMock, mapUnicode(0x65, _, 8)).WillOnce(DoAll(SetArrayArgument<1>("e", "e" + 1), Return(1)));

    EXPECT_CALL(uMapMock, mapUnicode(0x6C, _, 8)).WillOnce(DoAll(SetArrayArgument<1>("l", "l" + 1), Return(1)))

                                                 .WillOnce(DoAll(SetArrayArgument<1>("l", "l" + 1), Return(1)));

    EXPECT_CALL(uMapMock, mapUnicode(0x6F, _, 8)).WillOnce(DoAll(SetArrayArgument<1>("o", "o" + 1), Return(1)));



    globalParams->getUtf8Map = [&]() { return &uMapMock; };



    gchar *result = unicode_to_char(unicode, 5);

    EXPECT_STREQ(result, expected);

    g_free(result);

}



TEST(UnicodeToCharTest_2215, EmptyInput_2215) {

    Unicode unicode[] = {};

    char expected[] = "";



    UnicodeMapMock uMapMock;

    globalParams->getUtf8Map = [&]() { return &uMapMock; };



    gchar *result = unicode_to_char(unicode, 0);

    EXPECT_STREQ(result, expected);

    g_free(result);

}



TEST(UnicodeToCharTest_2215, SingleCharacter_2215) {

    Unicode unicode[] = {0x41}; // "A"

    char expected[] = "A";



    UnicodeMapMock uMapMock;

    EXPECT_CALL(uMapMock, mapUnicode(0x41, _, 8)).WillOnce(DoAll(SetArrayArgument<1>("A", "A" + 1), Return(1)));



    globalParams->getUtf8Map = [&]() { return &uMapMock; };



    gchar *result = unicode_to_char(unicode, 1);

    EXPECT_STREQ(result, expected);

    g_free(result);

}



TEST(UnicodeToCharTest_2215, BufferBoundary_2215) {

    Unicode unicode[] = {0x1F600}; // Smiling Face with Grinning Eyes

    char expected[] = "\xF0\x9F\x98\x80"; // UTF-8 encoding for U+1F600



    UnicodeMapMock uMapMock;

    EXPECT_CALL(uMapMock, mapUnicode(0x1F600, _, 8)).WillOnce(DoAll(SetArrayArgument<1>(expected, expected + 4), Return(4)));



    globalParams->getUtf8Map = [&]() { return &uMapMock; };



    gchar *result = unicode_to_char(unicode, 1);

    EXPECT_STREQ(result, expected);

    g_free(result);

}



TEST(UnicodeToCharTest_2215, IncompleteMapping_2215) {

    Unicode unicode[] = {0x48}; // "H"

    char partial_expected[] = "H";



    UnicodeMapMock uMapMock;

    EXPECT_CALL(uMapMock, mapUnicode(0x48, _, 8)).WillOnce(Return(1));



    globalParams->getUtf8Map = [&]() { return &uMapMock; };



    gchar *result = unicode_to_char(unicode, 1);

    EXPECT_STREQ(result, partial_expected);

    g_free(result);

}
