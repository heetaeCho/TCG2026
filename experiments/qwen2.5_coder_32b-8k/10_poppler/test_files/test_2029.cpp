#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-media.cc"

#include "./TestProjects/poppler/poppler/Object.h"



using namespace testing;



// Mocking the necessary dependencies

class MockObject : public Object {

public:

    MOCK_METHOD(void, setToNull, (), (override));

};



// Fixture for PopplerMedia tests

class PopplerMediaTest_2029 : public ::testing::Test {

protected:

    void SetUp() override {

        media = g_object_new(POPPLER_TYPE_MEDIA, nullptr);

    }



    void TearDown() override {

        g_clear_object(&media);

    }



    PopplerMedia* media;

};



// Test to verify the finalize function cleans up filename and mime_type properly

TEST_F(PopplerMediaTest_2029, FinalizeFreesStrings_2029) {

    // Arrange

    char* test_filename = g_strdup("testfile.mp4");

    char* test_mime_type = g_strdup("video/mp4");



    media->filename = test_filename;

    media->mime_type = test_mime_type;



    GObject* object = G_OBJECT(media);



    // Act

    poppler_media_finalize(object);



    // Assert

    EXPECT_EQ(media->filename, nullptr);

    EXPECT_EQ(media->mime_type, nullptr);

}



// Test to verify the finalize function resets stream properly

TEST_F(PopplerMediaTest_2029, FinalizeResetsStream_2029) {

    // Arrange

    MockObject mock_stream;

    media->stream = mock_stream;



    EXPECT_CALL(mock_stream, setToNull());



    GObject* object = G_OBJECT(media);



    // Act

    poppler_media_finalize(object);



    // Assert is handled by the expectation in MOCK_METHOD call

}



// Test to verify finalize function does not crash with null filename and mime_type

TEST_F(PopplerMediaTest_2029, FinalizeWithNullStrings_2029) {

    // Arrange

    media->filename = nullptr;

    media->mime_type = nullptr;



    GObject* object = G_OBJECT(media);



    // Act & Assert (should not crash)

    poppler_media_finalize(object);

}



// Test to verify finalize function does not crash with uninitialized stream

TEST_F(PopplerMediaTest_2029, FinalizeWithUninitializedStream_2029) {

    // Arrange (stream is already uninitialized by default in SetUp)



    GObject* object = G_OBJECT(media);



    // Act & Assert (should not crash)

    poppler_media_finalize(object);

}
