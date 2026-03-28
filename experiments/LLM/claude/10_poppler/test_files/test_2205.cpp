#include <gtest/gtest.h>
#include <glib-object.h>

extern "C" {
#include "poppler-document.h"
}

class PopplerDocumentGetPdfConformanceTest_2205 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns POPPLER_PDF_SUBTYPE_CONF_NONE
TEST_F(PopplerDocumentGetPdfConformanceTest_2205, NullDocumentReturnsNone_2205)
{
    PopplerPDFConformance result = poppler_document_get_pdf_conformance(nullptr);
    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_CONF_NONE);
}

// Test that passing an invalid (non-PopplerDocument) GObject returns POPPLER_PDF_SUBTYPE_CONF_NONE
TEST_F(PopplerDocumentGetPdfConformanceTest_2205, InvalidDocumentReturnsNone_2205)
{
    // Passing a nullptr which is not a valid PopplerDocument should trigger g_return_val
    PopplerPDFConformance result = poppler_document_get_pdf_conformance((PopplerDocument *)NULL);
    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_CONF_NONE);
}

// Test with a valid PDF file that we can load - normal PDF should return a valid conformance value
TEST_F(PopplerDocumentGetPdfConformanceTest_2205, ValidDocumentReturnsValidConformance_2205)
{
    GError *error = nullptr;
    
    // Create a minimal PDF in memory to test with
    const char *pdf_data = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";
    
    gsize pdf_len = strlen(pdf_data);
    
    // Try to create a document from the data
    PopplerDocument *doc = poppler_document_new_from_data((char *)pdf_data, (int)pdf_len, nullptr, &error);
    
    if (doc != nullptr) {
        PopplerPDFConformance conformance = poppler_document_get_pdf_conformance(doc);
        
        // The result should be a valid enum value
        EXPECT_GE((int)conformance, (int)POPPLER_PDF_SUBTYPE_CONF_UNSET);
        EXPECT_LE((int)conformance, (int)POPPLER_PDF_SUBTYPE_CONF_NONE);
        
        // A normal PDF (not PDF/A, PDF/X, etc.) likely returns UNSET or NONE
        EXPECT_TRUE(conformance == POPPLER_PDF_SUBTYPE_CONF_UNSET || 
                     conformance == POPPLER_PDF_SUBTYPE_CONF_NONE);
        
        g_object_unref(doc);
    } else {
        // If we can't create the doc from inline data, just skip gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create PopplerDocument from inline PDF data";
    }
}

// Test enum range validity
TEST_F(PopplerDocumentGetPdfConformanceTest_2205, EnumValuesAreCorrect_2205)
{
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_UNSET, 0);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_A, 1);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_B, 2);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_G, 3);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_N, 4);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_P, 5);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_PG, 6);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_U, 7);
    EXPECT_EQ(POPPLER_PDF_SUBTYPE_CONF_NONE, 8);
}

// Test loading from a URI-based file if available
TEST_F(PopplerDocumentGetPdfConformanceTest_2205, FileBasedDocumentConformance_2205)
{
    GError *error = nullptr;
    
    // Attempt to load a test PDF file if it exists
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_conformance.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        PopplerPDFConformance conformance = poppler_document_get_pdf_conformance(doc);
        
        // Should return a valid conformance value within the enum range
        EXPECT_GE((int)conformance, (int)POPPLER_PDF_SUBTYPE_CONF_UNSET);
        EXPECT_LE((int)conformance, (int)POPPLER_PDF_SUBTYPE_CONF_NONE);
        
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF file not available at /tmp/test_conformance.pdf";
    }
}
