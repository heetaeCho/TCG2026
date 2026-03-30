#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock the Object class to simulate the stream behavior
class MockObject : public Object {
public:
    MOCK_METHOD(bool, isStream, (), (const, override));
};

// Test fixture class for PopplerMedia
class PopplerMediaTest_2033 : public ::testing::Test {
protected:
    // Setup before each test
    void SetUp() override {
        poppler_media = new PopplerMedia();
    }

    // Cleanup after each test
    void TearDown() override {
        delete poppler_media;
    }

    // PopplerMedia instance for testing
    PopplerMedia *poppler_media;
};

// Test for normal operation (embedded media stream is true)
TEST_F(PopplerMediaTest_2033, IsEmbedded_StreamTrue_2033) {
    // Set up a mock Object that will simulate the stream as true
    MockObject mock_stream;
    EXPECT_CALL(mock_stream, isStream()).WillOnce(testing::Return(true));

    // Set the mock stream to the poppler_media
    poppler_media->stream = mock_stream;

    // Call the function under test
    gboolean result = poppler_media_is_embedded(poppler_media);

    // Verify that the result is TRUE (indicating the media is embedded)
    EXPECT_EQ(result, TRUE);
}

// Test for normal operation (embedded media stream is false)
TEST_F(PopplerMediaTest_2033, IsEmbedded_StreamFalse_2033) {
    // Set up a mock Object that will simulate the stream as false
    MockObject mock_stream;
    EXPECT_CALL(mock_stream, isStream()).WillOnce(testing::Return(false));

    // Set the mock stream to the poppler_media
    poppler_media->stream = mock_stream;

    // Call the function under test
    gboolean result = poppler_media_is_embedded(poppler_media);

    // Verify that the result is FALSE (indicating the media is not embedded)
    EXPECT_EQ(result, FALSE);
}

// Test boundary condition when poppler_media is NULL
TEST_F(PopplerMediaTest_2033, IsEmbedded_NullPopplerMedia_2033) {
    // Set poppler_media to NULL
    poppler_media = nullptr;

    // Call the function under test (this should return FALSE for a NULL poppler_media)
    gboolean result = poppler_media_is_embedded(poppler_media);

    // Verify that the result is FALSE as it cannot be embedded
    EXPECT_EQ(result, FALSE);
}

// Test exceptional/error case when poppler_media is not a valid media
TEST_F(PopplerMediaTest_2033, IsEmbedded_InvalidPopplerMedia_2033) {
    // Set up a mock Object for stream but simulate the Object type being invalid
    MockObject mock_stream;
    EXPECT_CALL(mock_stream, isStream()).WillOnce(testing::Return(true));

    // Set the stream to a mock object but fail the check for the media validity
    poppler_media->stream = mock_stream;

    // Simulate an invalid poppler_media object (in practice, we assume this to be invalid in some way)
    poppler_media->filename = nullptr;

    // Call the function under test
    gboolean result = poppler_media_is_embedded(poppler_media);

    // Verify that the result is FALSE for an invalid media object
    EXPECT_EQ(result, FALSE);
}