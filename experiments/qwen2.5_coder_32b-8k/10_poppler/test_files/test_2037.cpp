#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary declarations for PopplerMedia and related functions are included



extern "C" {

    const gchar *poppler_media_get_mime_type(PopplerMedia *poppler_media);

}



class PopplerMediaTest_2037 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the PopplerMedia object for testing

        poppler_media = static_cast<PopplerMedia*>(g_malloc(sizeof(PopplerMedia)));

        poppler_media->mime_type = g_strdup("video/mp4");

    }



    void TearDown() override {

        // Clean up after each test

        if (poppler_media->mime_type) {

            g_free(poppler_media->mime_type);

        }

        g_free(poppler_media);

    }



    PopplerMedia *poppler_media;

};



TEST_F(PopplerMediaTest_2037, GetMimeType_ReturnsCorrectType_2037) {

    // Test normal operation: get mime type

    EXPECT_STREQ("video/mp4", poppler_media_get_mime_type(poppler_media));

}



TEST_F(PopplerMediaTest_2037, GetMimeType_ReturnsNullForInvalidObject_2037) {

    // Test exceptional case: invalid object

    EXPECT_EQ(nullptr, poppler_media_get_mime_type(nullptr));

}



TEST_F(PopplerMediaTest_2037, GetMimeType_ReturnsNullWhenMimeTypeIsNull_2037) {

    // Test boundary condition: mime type is null

    g_free(poppler_media->mime_type);

    poppler_media->mime_type = nullptr;

    EXPECT_EQ(nullptr, poppler_media_get_mime_type(poppler_media));

}
