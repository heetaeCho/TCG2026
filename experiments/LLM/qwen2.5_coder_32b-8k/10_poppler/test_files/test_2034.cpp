#include <gtest/gtest.h>

#include "poppler-media.h"

#include <glib-object.h>



// Test fixture for PopplerMedia tests

class PopplerMediaTest_2034 : public ::testing::Test {

protected:

    PopplerMedia *media;



    void SetUp() override {

        media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));

    }



    void TearDown() override {

        g_clear_object(&media);

    }

};



// Test normal operation when auto_play is TRUE

TEST_F(PopplerMediaTest_2034, GetAutoPlay_ReturnsTrue_2034) {

    media->auto_play = TRUE;

    EXPECT_TRUE(poppler_media_get_auto_play(media));

}



// Test normal operation when auto_play is FALSE

TEST_F(PopplerMediaTest_2034, GetAutoPlay_ReturnsFalse_2034) {

    media->auto_play = FALSE;

    EXPECT_FALSE(poppler_media_get_auto_play(media));

}



// Test boundary condition where auto_play is set to an unexpected value

TEST_F(PopplerMediaTest_2034, GetAutoPlay_BoundaryCondition_2034) {

    media->auto_play = -1; // Assuming this is an unexpected value

    EXPECT_FALSE(poppler_media_get_auto_play(media));

}



// Test exceptional case where the input pointer is NULL

TEST_F(PopplerMediaTest_2034, GetAutoPlay_NullPointer_2034) {

    EXPECT_FALSE(poppler_media_get_auto_play(nullptr));

}
