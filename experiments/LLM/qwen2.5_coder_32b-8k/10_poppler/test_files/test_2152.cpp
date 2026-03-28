#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mocking any external collaborators if needed (none in this case)



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a mock or real PopplerDocument object

        document = poppler_document_new_from_data(nullptr, 0);

    }



    void TearDown() override {

        // Clean up the PopplerDocument object

        g_object_unref(document);

    }



    PopplerDocument *document;

};



TEST_F(PopplerDocumentTest_2152, GetPageValidIndex_2152) {

    int pageCount = poppler_document_get_n_pages(document);

    if (pageCount > 0) {

        PopplerPage* page = poppler_document_get_page(document, 0);

        EXPECT_NE(page, nullptr);

        g_object_unref(page);

    }

}



TEST_F(PopplerDocumentTest_2152, GetPageInvalidIndexBelowBound_2152) {

    PopplerPage* page = poppler_document_get_page(document, -1);

    EXPECT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2152, GetPageInvalidIndexAboveBound_2152) {

    int pageCount = poppler_document_get_n_pages(document);

    PopplerPage* page = poppler_document_get_page(document, pageCount);

    EXPECT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2152, GetPageNullDocument_2152) {

    PopplerPage* page = poppler_document_get_page(nullptr, 0);

    EXPECT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2152, GetPageEmptyDocument_2152) {

    // Assuming an empty document returns 0 pages

    int pageCount = poppler_document_get_n_pages(document);

    if (pageCount == 0) {

        PopplerPage* page = poppler_document_get_page(document, 0);

        EXPECT_EQ(page, nullptr);

    }

}



TEST_F(PopplerDocumentTest_2152, GetPageLastValidIndex_2152) {

    int pageCount = poppler_document_get_n_pages(document);

    if (pageCount > 0) {

        PopplerPage* page = poppler_document_get_page(document, pageCount - 1);

        EXPECT_NE(page, nullptr);

        g_object_unref(page);

    }

}
