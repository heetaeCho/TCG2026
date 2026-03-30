#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-media.h"

#include "Object.h"



using namespace testing;



class PopplerMediaTest_2032 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_media = reinterpret_cast<PopplerMedia*>(malloc(sizeof(PopplerMedia)));

        memset(poppler_media, 0, sizeof(PopplerMedia));

        poppler_media->filename = strdup("testfile.mp4");

    }



    void TearDown() override {

        free(poppler_media->filename);

        free(poppler_media);

    }



    PopplerMedia *poppler_media;

};



TEST_F(PopplerMediaTest_2032, GetFilename_NormalOperation_2032) {

    const gchar* filename = poppler_media_get_filename(poppler_media);

    EXPECT_STREQ(filename, "testfile.mp4");

}



TEST_F(PopplerMediaTest_2032, GetFilename_StreamIsStream_ReturnsNull_2032) {

    poppler_media->stream.setStream();

    const gchar* filename = poppler_media_get_filename(poppler_media);

    EXPECT_EQ(filename, nullptr);

}



TEST_F(PopplerMediaTest_2032, GetFilename_NullPopplerMedia_ReturnsNull_2032) {

    const gchar* filename = poppler_media_get_filename(nullptr);

    EXPECT_EQ(filename, nullptr);

}
