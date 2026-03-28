#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-document.h"

#include "TestProjects/poppler/glib/poppler-private.h"



class PopplerDocumentTest_2192 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock PopplerDocument instance for testing

        document = static_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->doc = static_cast<_PopplerDocument*>(g_malloc0(sizeof(_PopplerDocument)));

    }



    void TearDown() override {

        // Free the allocated memory for the mock PopplerDocument instance

        g_free(document->doc);

        g_free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2192, IsLinearized_ReturnsFalse_WhenDocumentIsNotLinearized_2192) {

    // Arrange

    document->doc->isLinearized = []() -> gboolean { return FALSE; };



    // Act

    gboolean result = poppler_document_is_linearized(document);



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(PopplerDocumentTest_2192, IsLinearized_ReturnsTrue_WhenDocumentIsLinearized_2192) {

    // Arrange

    document->doc->isLinearized = []() -> gboolean { return TRUE; };



    // Act

    gboolean result = poppler_document_is_linearized(document);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(PopplerDocumentTest_2192, IsLinearized_ReturnsFalse_WhenNullPointerIsPassed_2192) {

    // Arrange & Act

    gboolean result = poppler_document_is_linearized(nullptr);



    // Assert

    EXPECT_FALSE(result);

}
