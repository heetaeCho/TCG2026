#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <fcntl.h>

#include <unistd.h>

#include "poppler-media.h"



class PopplerMediaTest_2040 : public ::testing::Test {

protected:

    GError *error = nullptr;

    int fd;



    void SetUp() override {

        fd = open("/tmp/testfile", O_WRONLY | O_CREAT | O_TRUNC, 0600);

        ASSERT_NE(fd, -1) << "Failed to create test file";

    }



    void TearDown() override {

        close(fd);

        unlink("/tmp/testfile");

        if (error) {

            g_error_free(error);

        }

    }

};



TEST_F(PopplerMediaTest_2040, SaveToValidFD_ReturnsTrue_2040) {

    PopplerMedia poppler_media;

    // Assuming the stream is properly initialized

    bool result = poppler_media_save_to_fd(&poppler_media, fd, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);

}



TEST_F(PopplerMediaTest_2040, SaveToInvalidFD_ReturnsFalse_2040) {

    PopplerMedia poppler_media;

    bool result = poppler_media_save_to_fd(&poppler_media, -1, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerMediaTest_2040, SaveToNonWritableFD_ReturnsFalse_2040) {

    PopplerMedia poppler_media;

    int non_writable_fd = open("/tmp", O_RDONLY);

    bool result = poppler_media_save_to_fd(&poppler_media, non_writable_fd, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    close(non_writable_fd);

    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerMediaTest_2040, SaveToClosedFD_ReturnsFalse_2040) {

    PopplerMedia poppler_media;

    close(fd);

    bool result = poppler_media_save_to_fd(&poppler_media, fd, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerMediaTest_2040, SaveWithNullError_ReturnsTrue_2040) {

    PopplerMedia poppler_media;

    bool result = poppler_media_save_to_fd(&poppler_media, fd, nullptr);

    EXPECT_TRUE(result);

}



TEST_F(PopplerMediaTest_2040, SaveWithInvalidStream_ReturnsFalse_2040) {

    PopplerMedia poppler_media;

    // Assuming the stream is not properly initialized

    poppler_media.stream = Object();

    bool result = poppler_media_save_to_fd(&poppler_media, fd, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

    error = nullptr;

}
