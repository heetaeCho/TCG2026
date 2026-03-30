#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::Eq;

using ::testing::IsNull;



class PopplerDocumentTest : public ::testing::Test {

protected:

    PopplerDocument* document;



    virtual void SetUp() {

        document = static_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        // Assuming some basic initialization is done here, which might be necessary for the function to work

    }



    virtual void TearDown() {

        g_free(document);

    }

};



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsNullForDefaultSubtype_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypeNone);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, IsNull());

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsCorrectValueForPDFA_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypePDFA);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, Eq("1.7")); // Assuming "1.7" is the correct version for testing purposes

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsCorrectValueForPDFE_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypePDFE);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, Eq("1.4")); // Assuming "1.4" is the correct version for testing purposes

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsCorrectValueForPDFUA_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypePDFUA);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, Eq("1.4")); // Assuming "1.4" is the correct version for testing purposes

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsCorrectValueForPDFVT_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypePDFVT);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, Eq("1.4")); // Assuming "1.4" is the correct version for testing purposes

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsCorrectValueForPDFX_2202) {

    document->doc = new PDFDoc();

    document->doc->setPDFSubtype(subtypePDFX);



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, Eq("1.3")); // Assuming "1.3" is the correct version for testing purposes

    g_free(result);

}



TEST_F(PopplerDocumentTest_2202, GetPdfSubtypeString_ReturnsNullForInvalidDocument_2202) {

    document = nullptr;



    gchar* result = poppler_document_get_pdf_subtype_string(document);

    EXPECT_THAT(result, IsNull());

    g_free(result);

}
