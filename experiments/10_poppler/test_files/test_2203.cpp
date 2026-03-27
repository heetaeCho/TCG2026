#include <gtest/gtest.h>

#include "poppler-document.h"



// Mocking external dependencies if any



class PopplerDocumentTest_2203 : public ::testing::Test {

protected:

    // Setup and teardown functions can be added here if needed

    virtual void SetUp() override {

        document = new PopplerDocument;

    }



    virtual void TearDown() override {

        delete document;

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2203, GetPdfSubtype_ReturnsUnsetForNewDocument_2203) {

    EXPECT_EQ(poppler_document_get_pdf_subtype(document), POPPLER_PDF_SUBTYPE_UNSET);

}



TEST_F(PopplerDocumentTest_2203, GetPdfSubtype_ReturnsNoneForNullPointer_2203) {

    EXPECT_EQ(poppler_document_get_pdf_subtype(nullptr), POPPLER_PDF_SUBTYPE_NONE);

}
