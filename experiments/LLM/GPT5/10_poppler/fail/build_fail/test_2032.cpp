#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-media.h"

class PopplerMediaTest_2032 : public testing::Test {
protected:
    void SetUp() override {
        // Setup test environment here if needed
    }

    void TearDown() override {
        // Clean up after tests if needed
    }
};

// Test normal operation where filename is valid
TEST_F(PopplerMediaTest_2032, GetFilename_ValidPopplerMedia_2032) {
    PopplerMedia media;
    const char* expected_filename = "sample.pdf";
    media.filename = (int*)expected_filename;

    EXPECT_EQ(poppler_media_get_filename(&media), expected_filename);
}

// Test normal operation where poppler_media is not a stream
TEST_F(PopplerMediaTest_2032, GetFilename_NotStream_2032) {
    PopplerMedia media;
    media.filename = (int*)"valid_file.pdf";
    // Mimicking a non-stream scenario, here `isStream()` should return false
    EXPECT_EQ(poppler_media_get_filename(&media), "valid_file.pdf");
}

// Test boundary condition: Null pointer for PopplerMedia
TEST_F(PopplerMediaTest_2032, GetFilename_NullPopplerMedia_2032) {
    PopplerMedia* media = nullptr;

    EXPECT_EQ(poppler_media_get_filename(media), nullptr);
}

// Test boundary condition: Null filename
TEST_F(PopplerMediaTest_2032, GetFilename_NullFilename_2032) {
    PopplerMedia media;
    media.filename = nullptr;

    EXPECT_EQ(poppler_media_get_filename(&media), nullptr);
}

// Test boundary condition: Invalid PopplerMedia object (e.g., stream is set)
TEST_F(PopplerMediaTest_2032, GetFilename_Stream_2032) {
    PopplerMedia media;
    media.filename = (int*)"filename.pdf";
    // Mimicking a stream object that causes the function to return NULL
    EXPECT_EQ(poppler_media_get_filename(&media), nullptr);
}

// Test exceptional case: Invalid PopplerMedia object (not a valid media)
TEST_F(PopplerMediaTest_2032, GetFilename_InvalidPopplerMedia_2032) {
    PopplerMedia media;
    // Set the media object to a state that makes it invalid
    media.filename = nullptr;
    // Mimicking a failure in the poppler_media_get_filename function
    EXPECT_EQ(poppler_media_get_filename(&media), nullptr);
}