#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerDocumentTest_2178 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(malloc(sizeof(PopplerDocument)));

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2178, GetKeywords_ReturnsNull_WhenDocumentIsNull_2178) {

    EXPECT_EQ(poppler_document_get_keywords(nullptr), static_cast<gchar*>(nullptr));

}



TEST_F(PopplerDocumentTest_2178, GetKeywords_ReturnsNull_WhenDocInfoKeywordsAreEmpty_2178) {

    document->doc->getDocInfoKeywords = []() -> std::unique_ptr<GooString> { return nullptr; };

    EXPECT_EQ(poppler_document_get_keywords(document), static_cast<gchar*>(nullptr));

}



TEST_F(PopplerDocumentTest_2178, GetKeywords_ReturnsUtf8String_WhenDocInfoKeywordsAreNotEmpty_2178) {

    const char* expectedKeywords = "test keywords";

    document->doc->getDocInfoKeywords = [expectedKeywords]() -> std::unique_ptr<GooString> { 

        return std::make_unique<GooString>(expectedKeywords);

    };

    gchar* result = poppler_document_get_keywords(document);

    EXPECT_STREQ(result, expectedKeywords);

    g_free(result);

}



TEST_F(PopplerDocumentTest_2178, GetKeywords_ReturnsUtf8String_CorrectlyHandlesSpecialCharacters_2178) {

    const char* expectedKeywords = "test, special characters!@#";

    document->doc->getDocInfoKeywords = [expectedKeywords]() -> std::unique_ptr<GooString> { 

        return std::make_unique<GooString>(expectedKeywords);

    };

    gchar* result = poppler_document_get_keywords(document);

    EXPECT_STREQ(result, expectedKeywords);

    g_free(result);

}



TEST_F(PopplerDocumentTest_2178, GetKeywords_ReturnsUtf8String_CorrectlyHandlesUnicode_2178) {

    const char* expectedKeywords = u8"test, unicode characters: ñ, é, ü";

    document->doc->getDocInfoKeywords = [expectedKeywords]() -> std::unique_ptr<GooString> { 

        return std::make_unique<GooString>(expectedKeywords);

    };

    gchar* result = poppler_document_get_keywords(document);

    EXPECT_STREQ(result, expectedKeywords);

    g_free(result);

}
