#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-media.h"

#include "TestProjects/poppler/poppler/Rendition.h"

#include "TestProjects/poppler/poppler/Object.h"



using namespace testing;



class MockMediaRendition : public MediaRendition {

public:

    MOCK_CONST_METHOD0(getMHParameters, const MediaParameters*());

    MOCK_CONST_METHOD0(getBEParameters, const MediaParameters*());

    MOCK_CONST_METHOD0(getContentType, const GooString*());

    MOCK_CONST_METHOD0(getFileName, const GooString*());

    MOCK_CONST_METHOD0(getIsEmbedded, bool());

    MOCK_CONST_METHOD0(getEmbbededStreamObject, const Object*());



    MockMediaRendition() : MediaRendition(Dict{}) {}

};



class PopplerMediaTest_2031 : public ::testing::Test {

protected:

    NiceMock<MockMediaRendition> mock_rendition;

};



TEST_F(PopplerMediaTest_2031, NormalOperation_EmbeddedMedia_2031) {

    const GooString expected_mime_type("video/mp4");

    const Object embedded_stream;



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(true));

    EXPECT_CALL(mock_rendition, getEmbbededStreamObject()).WillOnce(Return(&embedded_stream));

    EXPECT_CALL(mock_rendition, getContentType()).WillOnce(Return(&expected_mime_type));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    ASSERT_NE(media->mime_type, nullptr);

    EXPECT_STREQ(media->mime_type, "video/mp4");

    EXPECT_EQ(media->filename, nullptr);

    EXPECT_TRUE(goo_string_equal(reinterpret_cast<GooString*>(media->stream.getString()), embedded_stream.getString()));



    g_free(media->mime_type);

    delete media;

}



TEST_F(PopplerMediaTest_2031, NormalOperation_ExternalMedia_2031) {

    const GooString expected_filename("example.mp4");



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(&expected_filename));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    ASSERT_NE(media->filename, nullptr);

    EXPECT_STREQ(media->filename, "example.mp4");

    EXPECT_EQ(media->mime_type, nullptr);



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_DefaultValues_2031) {

    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_EQ(media->auto_play, false);

    EXPECT_EQ(media->show_controls, false);

    EXPECT_DOUBLE_EQ(media->repeat_count, 1.0);



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_BEValues_2031) {

    const MediaParameters be_params{0, 0, MediaFittingPolicy::FitWidthOrHeight,

                                    true, 2.5, Color(), true, MediaWindowParameters()};



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));

    EXPECT_CALL(mock_rendition, getMHParameters()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_rendition, getBEParameters()).WillOnce(Return(&be_params));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_EQ(media->auto_play, true);

    EXPECT_EQ(media->show_controls, true);

    EXPECT_DOUBLE_EQ(media->repeat_count, 2.5);



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_MHValues_2031) {

    const MediaParameters mh_params{0, 0, MediaFittingPolicy::FitWidthOrHeight,

                                    false, 5.0, Color(), true, MediaWindowParameters()};



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));

    EXPECT_CALL(mock_rendition, getMHParameters()).WillOnce(Return(&mh_params));

    EXPECT_CALL(mock_rendition, getBEParameters()).WillOnce(Return(nullptr));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_EQ(media->auto_play, false);

    EXPECT_EQ(media->show_controls, true);

    EXPECT_DOUBLE_EQ(media->repeat_count, 5.0);



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_DefaultRepeatCount_2031) {

    const MediaParameters mh_params{0, 0, MediaFittingPolicy::FitWidthOrHeight,

                                    false, 0.0, Color(), true, MediaWindowParameters()};



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));

    EXPECT_CALL(mock_rendition, getMHParameters()).WillOnce(Return(&mh_params));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_DOUBLE_EQ(media->repeat_count, 1.0); // Default repeat count should be used



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_DefaultAutoPlay_2031) {

    const MediaParameters mh_params{0, 0, MediaFittingPolicy::FitWidthOrHeight,

                                    false, 0.0, Color(), true, MediaWindowParameters()};



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));

    EXPECT_CALL(mock_rendition, getMHParameters()).WillOnce(Return(&mh_params));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_EQ(media->auto_play, false); // Default auto play should be used



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, MediaParameters_DefaultShowControls_2031) {

    const MediaParameters mh_params{0, 0, MediaFittingPolicy::FitWidthOrHeight,

                                    false, 0.0, Color(), true, MediaWindowParameters()};



    EXPECT_CALL(mock_rendition, getIsEmbedded()).WillOnce(Return(false));

    EXPECT_CALL(mock_rendition, getFileName()).WillOnce(Return(new GooString("example.mp4")));

    EXPECT_CALL(mock_rendition, getMHParameters()).WillOnce(Return(&mh_params));



    PopplerMedia* media = _poppler_media_new(&mock_rendition);



    EXPECT_EQ(media->show_controls, true); // Default show controls should be used



    g_free(media->filename);

    delete media;

}



TEST_F(PopplerMediaTest_2031, NullPointerCheck_2031) {

    EXPECT_DEATH(_poppler_media_new(nullptr), ".*Assertion.*failed");

}
