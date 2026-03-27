#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using namespace testing;



class PopplerDocumentTest_2174 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the document for each test

        document = static_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        // Clean up after each test

        delete document->doc;

        g_free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2174, GetAuthor_ReturnsNull_WhenDocumentIsNull_2174) {

    gchar *author = poppler_document_get_author(nullptr);

    EXPECT_EQ(author, nullptr);

}



TEST_F(PopplerDocumentTest_2174, GetAuthor_ReturnsNull_WhenDocInfoAuthorIsNull_2174) {

    document->doc->getDocInfoAuthor = []() -> const std::unique_ptr<GooString> { return nullptr; };

    gchar *author = poppler_document_get_author(document);

    EXPECT_EQ(author, nullptr);

}



TEST_F(PopplerDocumentTest_2174, GetAuthor_ReturnsValidUTF8String_WhenDocInfoAuthorIsSet_2174) {

    document->doc->getDocInfoAuthor = []() -> const std::unique_ptr<GooString> { return std::make_unique<GooString>("Test Author"); };

    gchar *author = poppler_document_get_author(document);

    EXPECT_STREQ(author, "Test Author");

    g_free(author);

}
