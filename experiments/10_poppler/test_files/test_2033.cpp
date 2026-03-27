#include <gtest/gtest.h>

#include "poppler-media.h"

#include "Object.h"



class PopplerMediaTest_2033 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_media = static_cast<PopplerMedia*>(g_malloc0(sizeof(PopplerMedia)));

    }



    void TearDown() override {

        g_free(poppler_media);

    }



    PopplerMedia* poppler_media;

};



TEST_F(PopplerMediaTest_2033, StreamIsStream_ReturnsTrue_2033) {

    // Arrange

    Object streamObject(true);  // Assuming true represents a valid stream for testing

    poppler_media->stream = streamObject;



    // Act & Assert

    EXPECT_TRUE(poppler_media_is_embedded(poppler_media));

}



TEST_F(PopplerMediaTest_2033, StreamIsNotStream_ReturnsFalse_2033) {

    // Arrange

    Object nonStreamObject(false);  // Assuming false represents a non-stream for testing

    poppler_media->stream = nonStreamObject;



    // Act & Assert

    EXPECT_FALSE(poppler_media_is_embedded(poppler_media));

}



TEST_F(PopplerMediaTest_2033, NullPopplerMedia_ReturnsFalse_2033) {

    // Arrange

    PopplerMedia* nullPopplerMedia = nullptr;



    // Act & Assert

    EXPECT_FALSE(poppler_media_is_embedded(nullPopplerMedia));

}



TEST_F(PopplerMediaTest_2033, StreamIsStreamAndMediaType_ReturnsTrue_2033) {

    // Arrange

    Object streamObject(true);  // Assuming true represents a valid stream for testing

    poppler_media->stream = streamObject;



    // Act & Assert

    EXPECT_TRUE(poppler_media_is_embedded(poppler_media));

}



TEST_F(PopplerMediaTest_2033, StreamIsNotStreamAndMediaType_ReturnsFalse_2033) {

    // Arrange

    Object nonStreamObject(false);  // Assuming false represents a non-stream for testing

    poppler_media->stream = nonStreamObject;



    // Act & Assert

    EXPECT_FALSE(poppler_media_is_embedded(poppler_media));

}
