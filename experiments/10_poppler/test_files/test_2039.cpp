#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-media.h>

#include <glib.h>



using namespace testing;



class PopplerMediaTest_2039 : public ::testing::Test {

protected:

    PopplerMedia* poppler_media;

    GError* error;



    void SetUp() override {

        poppler_media = static_cast<PopplerMedia*>(g_malloc0(sizeof(PopplerMedia)));

        error = nullptr;

    }



    void TearDown() override {

        g_clear_error(&error);

        g_free(poppler_media);

    }

};



TEST_F(PopplerMediaTest_2039, SaveWithNullFilename_2039) {

    EXPECT_EQ(poppler_media_save(poppler_media, nullptr, &error), FALSE);

    ASSERT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_FAILED), TRUE);

}



TEST_F(PopplerMediaTest_2039, SaveWithInvalidFilename_2039) {

    const char* invalid_filename = "/nonexistent/path/file";

    EXPECT_EQ(poppler_media_save(poppler_media, invalid_filename, &error), FALSE);

    ASSERT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_NOENT), TRUE);

}



TEST_F(PopplerMediaTest_2039, SaveWithNullPopplerMedia_2039) {

    EXPECT_EQ(poppler_media_save(nullptr, "testfile", &error), FALSE);

    ASSERT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_FAILED), TRUE);

}



TEST_F(PopplerMediaTest_2039, SaveWithInvalidStream_2039) {

    poppler_media->stream = Object();

    EXPECT_EQ(poppler_media_save(poppler_media, "testfile", &error), FALSE);

    ASSERT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_FAILED), TRUE);

}



TEST_F(PopplerMediaTest_2039, SaveWithValidParameters_2039) {

    poppler_media->stream = Object(/* assume valid stream */);

    EXPECT_CALL(*reinterpret_cast<FILE**>(fopen("testfile", "wb")), fclose())

        .WillOnce(Return(0));

    EXPECT_EQ(poppler_media_save(poppler_media, "testfile", &error), TRUE);

    ASSERT_EQ(error, nullptr);

}



TEST_F(PopplerMediaTest_2039, SaveWithFileCloseFailure_2039) {

    poppler_media->stream = Object(/* assume valid stream */);

    EXPECT_CALL(*reinterpret_cast<FILE**>(fopen("testfile", "wb")), fclose())

        .WillOnce(Return(-1));

    EXPECT_EQ(poppler_media_save(poppler_media, "testfile", &error), FALSE);

    ASSERT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_FAILED), TRUE);

}
