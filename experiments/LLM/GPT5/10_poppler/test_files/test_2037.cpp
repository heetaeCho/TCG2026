#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/glib/poppler-media.h"

// Mocking PopplerMedia for testing purposes
class MockPopplerMedia : public PopplerMedia {
public:
    MOCK_METHOD(const gchar*, getMimeType, (), (const));
};

// Test suite for PopplerMedia functions
TEST_F(PopplerMediaTest_2037, poppler_media_get_mime_type_valid) {
    // Create a PopplerMedia object with valid mime_type
    PopplerMedia media;
    media.mime_type = const_cast<char*>("image/jpeg");
    
    // Call the function and validate that mime_type is returned correctly
    EXPECT_STREQ(poppler_media_get_mime_type(&media), "image/jpeg");
}

TEST_F(PopplerMediaTest_2037, poppler_media_get_mime_type_invalid_media) {
    // Create an invalid PopplerMedia object (e.g., nullptr or invalid reference)
    PopplerMedia* invalid_media = nullptr;
    
    // Call the function and expect a NULL return value for invalid media
    EXPECT_EQ(poppler_media_get_mime_type(invalid_media), nullptr);
}

TEST_F(PopplerMediaTest_2037, poppler_media_get_mime_type_null_mime_type) {
    // Create a PopplerMedia object with NULL mime_type
    PopplerMedia media;
    media.mime_type = nullptr;
    
    // Call the function and expect a NULL return value as mime_type is NULL
    EXPECT_EQ(poppler_media_get_mime_type(&media), nullptr);
}

TEST_F(PopplerMediaTest_2037, poppler_media_get_mime_type_mocked) {
    // Mock the PopplerMedia object
    MockPopplerMedia mock_media;
    
    // Expect a call to getMimeType and specify a return value for this call
    EXPECT_CALL(mock_media, getMimeType())
        .WillOnce(testing::Return("audio/mp3"));
    
    // Call the function and verify it returns the expected result
    EXPECT_STREQ(poppler_media_get_mime_type(&mock_media), "audio/mp3");
}