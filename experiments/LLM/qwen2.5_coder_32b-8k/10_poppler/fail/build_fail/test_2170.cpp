#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mocking external collaborators if needed (not required in this case)



class PopplerDocumentTest : public ::testing::Test {

protected:

    PopplerDocument *document;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        // Assuming necessary initialization for the document

    }



    void TearDown() override {

        g_free(document);

    }

};



TEST_F(PopplerDocumentTest_2170, GetPdfVersionString_ReturnsCorrectFormat_2170) {

    gchar *version_string = poppler_document_get_pdf_version_string(document);

    EXPECT_THAT(version_string, testing::StartsWith("PDF-"));

    g_free(version_string);

}



TEST_F(PopplerDocumentTest_2170, GetPdfVersionString_ReturnsValidNumber_2170) {

    gchar *version_string = poppler_document_get_pdf_version_string(document);

    // Assuming a valid version number like "1.4" is returned

    EXPECT_TRUE(g_ascii_strtod(version_string + 4, nullptr) > 0.0);

    g_free(version_string);

}



TEST_F(PopplerDocumentTest_2170, GetPdfVersionString_NullPointer_ReturnsNull_2170) {

    gchar *version_string = poppler_document_get_pdf_version_string(nullptr);

    EXPECT_EQ(version_string, nullptr);

}



// Assuming no exceptional cases are observable through the interface for this function

```


