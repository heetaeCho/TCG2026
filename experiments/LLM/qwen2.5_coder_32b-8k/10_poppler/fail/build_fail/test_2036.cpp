#include <gtest/gtest.h>

#include "poppler-media.h"



class PopplerMediaTest_2036 : public ::testing::Test {

protected:

    PopplerMedia *media;



    void SetUp() override {

        media = g_object_new(POPPLER_TYPE_MEDIA, nullptr);

    }



    void TearDown() override {

        g_object_unref(media);

    }

};



TEST_F(PopplerMediaTest_2036, GetRepeatCount_DefaultValue_2036) {

    EXPECT_EQ(poppler_media_get_repeat_count(media), 0);

}



TEST_F(PopplerMediaTest_2036, GetRepeatCount_SetValue_2036) {

    media->repeat_count = 5;

    EXPECT_EQ(poppler_media_get_repeat_count(media), 5);

}



TEST_F(PopplerMediaTest_2036, GetRepeatCount_NegativeValue_2036) {

    media->repeat_count = -1;

    EXPECT_EQ(poppler_media_get_repeat_count(media), -1);

}



TEST_F(PopplerMediaTest_2036, GetRepeatCount_MaxIntValue_2036) {

    media->repeat_count = INT_MAX;

    EXPECT_EQ(poppler_media_get_repeat_count(media), INT_MAX);

}



TEST_F(PopplerMediaTest_2036, GetRepeatCount_ZeroValue_2036) {

    media->repeat_count = 0;

    EXPECT_EQ(poppler_media_get_repeat_count(media), 0);

}
