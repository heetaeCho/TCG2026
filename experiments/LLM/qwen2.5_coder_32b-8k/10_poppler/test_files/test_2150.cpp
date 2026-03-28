#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the header file for poppler-document.h is included here

extern "C" {

#include "./TestProjects/poppler/glib/poppler-document.h"

}



class PopplerDocumentFixture_2150 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a mock document or use a real one if available

        document = reinterpret_cast<PopplerDocument*>(malloc(sizeof(PopplerDocument)));

        memset(document, 0, sizeof(PopplerDocument));

    }



    void TearDown() override {

        // Clean up the document if necessary

        free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentFixture_2150, GetIdWithBothIdsNullptr_2150) {

    gchar *permanent_id = nullptr;

    gchar *update_id = nullptr;

    gboolean result = poppler_document_get_id(document, &permanent_id, &update_id);

    EXPECT_FALSE(result);

    EXPECT_EQ(permanent_id, nullptr);

    EXPECT_EQ(update_id, nullptr);

}



TEST_F(PopplerDocumentFixture_2150, GetIdWithPermanentIdOnly_2150) {

    gchar *permanent_id = nullptr;

    gboolean result = poppler_document_get_id(document, &permanent_id, nullptr);

    if (result) {

        EXPECT_NE(permanent_id, nullptr);

        g_free(permanent_id);

    }

}



TEST_F(PopplerDocumentFixture_2150, GetIdWithUpdateIdOnly_2150) {

    gchar *update_id = nullptr;

    gboolean result = poppler_document_get_id(document, nullptr, &update_id);

    if (result) {

        EXPECT_NE(update_id, nullptr);

        g_free(update_id);

    }

}



TEST_F(PopplerDocumentFixture_2150, GetIdWithBothIdsNotNullptr_2150) {

    gchar *permanent_id = nullptr;

    gchar *update_id = nullptr;

    gboolean result = poppler_document_get_id(document, &permanent_id, &update_id);

    if (result) {

        EXPECT_NE(permanent_id, nullptr);

        g_free(permanent_id);

        EXPECT_NE(update_id, nullptr);

        g_free(update_id);

    }

}



TEST_F(PopplerDocumentFixture_2150, GetIdWithInvalidDocument_2150) {

    PopplerDocument* invalid_document = nullptr;

    gchar *permanent_id = nullptr;

    gchar *update_id = nullptr;

    gboolean result = poppler_document_get_id(invalid_document, &permanent_id, &update_id);

    EXPECT_FALSE(result);

    EXPECT_EQ(permanent_id, nullptr);

    EXPECT_EQ(update_id, nullptr);

}



TEST_F(PopplerDocumentFixture_2150, GetIdWithDocumentWithoutID_2150) {

    // Assuming there's a way to set up the document without ID

    gchar *permanent_id = nullptr;

    gchar *update_id = nullptr;

    gboolean result = poppler_document_get_id(document, &permanent_id, &update_id);

    EXPECT_FALSE(result);

    EXPECT_EQ(permanent_id, nullptr);

    EXPECT_EQ(update_id, nullptr);

}
