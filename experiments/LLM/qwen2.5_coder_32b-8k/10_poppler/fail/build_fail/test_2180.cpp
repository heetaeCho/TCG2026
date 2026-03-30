#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerDocumentTest_2180 : public ::testing::Test {

protected:

    PopplerDocument *document;



    void SetUp() override {

        document = static_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->doc = new _PrivateDoc();  // Assuming _PrivateDoc is the internal doc structure

    }



    void TearDown() override {

        delete document->doc;

        g_free(document);

    }

};



TEST_F(PopplerDocumentTest_2180, GetCreator_ReturnsNull_WhenDocumentIsNull_2180) {

    EXPECT_EQ(poppler_document_get_creator(nullptr), nullptr);

}



TEST_F(PopplerDocumentTest_2180, GetCreator_ReturnsNull_WhenCreatorInfoIsMissing_2180) {

    document->doc->getDocInfoCreator = []() -> std::unique_ptr<GooString> { return nullptr; };

    EXPECT_EQ(poppler_document_get_creator(document), nullptr);

}



TEST_F(PopplerDocumentTest_2180, GetCreator_ReturnsValidUtf8String_WhenCreatorInfoIsPresent_2180) {

    document->doc->getDocInfoCreator = []() -> std::unique_ptr<GooString> { return std::make_unique<GooString>("CreatorName"); };

    gchar *creator = poppler_document_get_creator(document);

    EXPECT_STREQ(creator, "CreatorName");

    g_free(creator);

}



TEST_F(PopplerDocumentTest_2180, GetCreator_ReturnsEmptyString_WhenCreatorInfoIsEmpty_2180) {

    document->doc->getDocInfoCreator = []() -> std::unique_ptr<GooString> { return std::make_unique<GooString>(""); };

    gchar *creator = poppler_document_get_creator(document);

    EXPECT_STREQ(creator, "");

    g_free(creator);

}



TEST_F(PopplerDocumentTest_2180, GetCreator_ReturnsUtf8StringWithSpecialCharacters_WhenCreatorInfoContainsSpecialChars_2180) {

    document->doc->getDocInfoCreator = []() -> std::unique_ptr<GooString> { return std::make_unique<GooString>("Creator@#Name!"); };

    gchar *creator = poppler_document_get_creator(document);

    EXPECT_STREQ(creator, "Creator@#Name!");

    g_free(creator);

}

```


