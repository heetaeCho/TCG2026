#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-media.h"  // Include the necessary headers
#include "poppler/stream.h"  // Include the Stream class

// Mocks for external dependencies
class MockStream : public Stream {
public:
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
};

// Test Fixture for PopplerMedia
class PopplerMediaTest_2041 : public ::testing::Test {
protected:
    PopplerMedia *poppler_media;
    MockStream *mock_stream;
    GError *error = nullptr;

    void SetUp() override {
        // Initialize PopplerMedia and MockStream
        mock_stream = new MockStream();
        poppler_media = new PopplerMedia();
        poppler_media->stream = Object(std::unique_ptr<Stream>(mock_stream));
    }

    void TearDown() override {
        delete poppler_media;
        delete mock_stream;
    }
};

// Test: Normal operation - the function works as expected
TEST_F(PopplerMediaTest_2041, popplerMediaSaveToCallback_NormalOperation_2041) {
    // Setup the mock behavior for the Stream
    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(true));
    EXPECT_CALL(*mock_stream, getChar()).WillRepeatedly(testing::Return('a'));
    EXPECT_CALL(*mock_stream, close()).Times(1);

    // Mock save function that returns true
    auto save_func = [](const char *buf, int size, gpointer user_data, GError **error) {
        return true;  // Simulate a successful save
    };

    gboolean result = poppler_media_save_to_callback(poppler_media, save_func, nullptr, &error);

    // Validate that the function returned true (success)
    ASSERT_TRUE(result);
}

// Test: Boundary condition - EOF reached in the stream
TEST_F(PopplerMediaTest_2041, popplerMediaSaveToCallback_EOF_2041) {
    // Setup the mock behavior for the Stream
    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(true));
    EXPECT_CALL(*mock_stream, getChar())
        .WillOnce(testing::Return('a'))
        .WillOnce(testing::Return(EOF));  // Simulate EOF after one character
    EXPECT_CALL(*mock_stream, close()).Times(1);

    auto save_func = [](const char *buf, int size, gpointer user_data, GError **error) {
        return true;  // Simulate a successful save
    };

    gboolean result = poppler_media_save_to_callback(poppler_media, save_func, nullptr, &error);

    // Validate that the function returned true (success)
    ASSERT_TRUE(result);
}

// Test: Exceptional case - stream rewind fails
TEST_F(PopplerMediaTest_2041, popplerMediaSaveToCallback_RewindFailure_2041) {
    // Setup the mock behavior for the Stream
    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(false));  // Rewind fails
    EXPECT_CALL(*mock_stream, close()).Times(0);  // close should not be called

    auto save_func = [](const char *buf, int size, gpointer user_data, GError **error) {
        return true;  // Simulate a successful save
    };

    gboolean result = poppler_media_save_to_callback(poppler_media, save_func, nullptr, &error);

    // Validate that the function returned false due to the rewind failure
    ASSERT_FALSE(result);
}

// Test: Exceptional case - save function fails
TEST_F(PopplerMediaTest_2041, popplerMediaSaveToCallback_SaveFailure_2041) {
    // Setup the mock behavior for the Stream
    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(true));
    EXPECT_CALL(*mock_stream, getChar()).WillRepeatedly(testing::Return('a'));
    EXPECT_CALL(*mock_stream, close()).Times(1);

    // Mock save function that returns false
    auto save_func = [](const char *buf, int size, gpointer user_data, GError **error) {
        return false;  // Simulate a save failure
    };

    gboolean result = poppler_media_save_to_callback(poppler_media, save_func, nullptr, &error);

    // Validate that the function returned false due to the save function failure
    ASSERT_FALSE(result);
}