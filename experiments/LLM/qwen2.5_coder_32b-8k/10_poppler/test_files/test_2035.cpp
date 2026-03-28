#include <gtest/gtest.h>

#include "poppler-media.h"



// Mocking external collaborators if needed would go here.

// However, in this case, no additional mocking is necessary.



class PopplerMediaTest_2035 : public ::testing::Test {

protected:

    PopplerMedia *poppler_media;



    void SetUp() override {

        poppler_media = reinterpret_cast<PopplerMedia*>(g_malloc(sizeof(PopplerMedia)));

        // Initialize the structure members as needed for testing

        poppler_media->show_controls = FALSE;

    }



    void TearDown() override {

        g_free(poppler_media);

    }

};



TEST_F(PopplerMediaTest_2035, GetShowControls_ReturnsFalseWhenNotSet_2035) {

    EXPECT_EQ(poppler_media_get_show_controls(poppler_media), FALSE);

}



TEST_F(PopplerMediaTest_2035, GetShowControls_ReturnsTrueWhenSet_2035) {

    poppler_media->show_controls = TRUE;

    EXPECT_EQ(poppler_media_get_show_controls(poppler_media), TRUE);

}



TEST_F(PopplerMediaTest_2035, GetShowControls_InvalidPointer_ReturnsFalse_2035) {

    EXPECT_EQ(poppler_media_get_show_controls(nullptr), FALSE);

}
