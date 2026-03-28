#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/utils/pdftohtml.cc"

#include "poppler/poppler/Object.h"

#include "poppler/poppler/Dict.h"

#include "poppler/utils/HtmlFonts.h"



using namespace testing;



class DictMock : public Dict {

public:

    MOCK_METHOD2(lookup, Object(const char*, int));

};



TEST(getInfoStringTest_2716, NormalOperationWithAscii_2716) {

    DictMock dictMock;

    const char* key = "Title";

    const char* value = "Example Document";



    EXPECT_CALL(dictMock, lookup(key, _))

        .WillOnce(Return(Object(std::string(value))));



    auto result = getInfoString(&dictMock, key);

    ASSERT_NE(result.get(), nullptr);

    EXPECT_EQ(result->toStr(), value);

}



TEST(getInfoStringTest_2716, NormalOperationWithUnicode_2716) {

    DictMock dictMock;

    const char* key = "Title";

    const char* unicodeValue = "\xFE\xFFE\x00x\x00a\x00m\x00p\x00l\x00e\x00 \x00D\x00o\x00c\x00u\x00m\x00e\x00n\x00t";



    EXPECT_CALL(dictMock, lookup(key, _))

        .WillOnce(Return(Object(std::string(unicodeValue))));



    auto result = getInfoString(&dictMock, key);

    ASSERT_NE(result.get(), nullptr);

    EXPECT_EQ(result->toStr(), "Example Document");

}



TEST(getInfoStringTest_2716, EmptyString_2716) {

    DictMock dictMock;

    const char* key = "Title";

    const char* value = "";



    EXPECT_CALL(dictMock, lookup(key, _))

        .WillOnce(Return(Object(std::string(value))));



    auto result = getInfoString(&dictMock, key);

    ASSERT_EQ(result.get(), nullptr);

}



TEST(getInfoStringTest_2716, NonStringObject_2716) {

    DictMock dictMock;

    const char* key = "Title";

    Object nonStringObj(5);



    EXPECT_CALL(dictMock, lookup(key, _))

        .WillOnce(Return(nonStringObj));



    auto result = getInfoString(&dictMock, key);

    ASSERT_EQ(result.get(), nullptr);

}



TEST(getInfoStringTest_2716, KeyNotFound_2716) {

    DictMock dictMock;

    const char* key = "NonExistentKey";



    EXPECT_CALL(dictMock, lookup(key, _))

        .WillOnce(Return(Object::null()));



    auto result = getInfoString(&dictMock, key);

    ASSERT_EQ(result.get(), nullptr);

}
