#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GooString.h"

#include "TextOutputDev.h"



using namespace testing;



class MockTextWord : public TextWord {

public:

    MOCK_CONST_METHOD1(getFontName, const GooString*(int idx));

};



TEST_F(MockTextWordTest_2476, GetFontNameIsNull_2476) {

    MockTextWord mockWord;

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(nullptr));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Default");

    g_free(result);

}



TEST_F(MockTextWordTest_2476, GetFontNameIsEmpty_2476) {

    MockTextWord mockWord;

    GooString emptyFontName;

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(&emptyFontName));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Default");

    g_free(result);

}



TEST_F(MockTextWordTest_2476, GetFontNameNoSubset_2476) {

    MockTextWord mockWord;

    GooString fontName("Helvetica");

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(&fontName));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Helvetica");

    g_free(result);

}



TEST_F(MockTextWordTest_2476, GetFontNameWithSubset_2476) {

    MockTextWord mockWord;

    GooString fontName("AAAA+Helvetica");

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(&fontName));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Helvetica");

    g_free(result);

}



TEST_F(MockTextWordTest_2476, GetFontNameOnlySubsetPrefix_2476) {

    MockTextWord mockWord;

    GooString fontName("AAAA+");

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(&fontName));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Default");

    g_free(result);

}



TEST_F(MockTextWordTest_2476, GetFontNameMixedCaseSubset_2476) {

    MockTextWord mockWord;

    GooString fontName("AAAA+Helvetica-BoldOblique");

    EXPECT_CALL(mockWord, getFontName(0)).WillOnce(Return(&fontName));



    gchar* result = get_font_name_from_word(&mockWord, 0);

    ASSERT_STREQ(result, "Helvetica-BoldOblique");

    g_free(result);

}
