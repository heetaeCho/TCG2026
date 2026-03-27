#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "matroskavideo.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using namespace testing;



class MatroskaVideoTest : public Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<StrictMock<BasicIoMock>>();

        matroskaVideo = new MatroskaVideo(std::move(ioMock));

    }



    void TearDown() override {

        delete matroskaVideo;

    }



    StrictMock<BasicIoMock>* ioMock;

    MatroskaVideo* matroskaVideo;

};



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_NormalOperation_XmpAudioSampleRate_103) {

    const uint64_t tagId = Xmp_audio_SampleRate;

    const std::string tagLabel = "Xmp.audio.SampleRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x40, 0x49, 0x0F, 0xDB, 0x21, 0x09, 0x4E, 0xC0}; // Represents 44100.0 in big-endian float



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.audio.SampleRate"].toFloat(), 44100.0);

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_NormalOperation_XmpAudioOutputSampleRate_103) {

    const uint64_t tagId = Xmp_audio_OutputSampleRate;

    const std::string tagLabel = "Xmp.audio.OutputSampleRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x40, 0x49, 0x0F, 0xDB, 0x21, 0x09, 0x4E, 0xC0}; // Represents 44100.0 in big-endian float



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.audio.OutputSampleRate"].toFloat(), 44100.0);

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_NormalOperation_VideoFrameRateDefaultDuration_Stream1_103) {

    matroskaVideo->stream_ = 1;

    const uint64_t tagId = VideoFrameRate_DefaultDuration;

    const std::string tagLabel = "Xmp.video.FrameRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x00, 0x00, 0x27, 0x10}; // Represents 10000 in big-endian uint64_t



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FrameRate"].toFloat(), 37.0);

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_NormalOperation_VideoFrameRateDefaultDuration_Stream2_103) {

    matroskaVideo->stream_ = 2;

    const uint64_t tagId = VideoFrameRate_DefaultDuration;

    const std::string tagLabel = "Xmp.video.FrameRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x00, 0x00, 0x27, 0x10}; // Represents 10000 in big-endian uint64_t



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FrameRate"].toFloat(), 10.0);

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_BoundaryCondition_StreamZero_103) {

    matroskaVideo->stream_ = 0;

    const uint64_t tagId = VideoFrameRate_DefaultDuration;

    const std::string tagLabel = "Xmp.video.FrameRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x00, 0x00, 0x27, 0x10}; // Represents 10000 in big-endian uint64_t



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FrameRate"].toString(), "Variable Bit Rate");

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_ExceptionalCase_ZeroKey_103) {

    matroskaVideo->stream_ = 1;

    const uint64_t tagId = VideoFrameRate_DefaultDuration;

    const std::string tagLabel = "Xmp.video.FrameRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x00, 0x00, 0x00, 0x00}; // Represents 0 in big-endian uint64_t



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_.find(tagLabel), matroskaVideo->xmpData_.end());

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_ExceptionalCase_UnmatchedKey_103) {

    matroskaVideo->stream_ = 1;

    const uint64_t tagId = VideoFrameRate_DefaultDuration;

    const std::string tagLabel = "Xmp.video.FrameRate";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x00, 0x00, 0x9C, 0x40}; // Represents 39999 in big-endian uint64_t



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FrameRate"].toString(), "Variable Bit Rate");

}



TEST_F(MatroskaVideoTest_103, DecodeFloatTags_DefaultCase_103) {

    const uint64_t tagId = 999; // Some unknown tag ID

    const std::string tagLabel = "UnknownTag";

    Internal::MatroskaTag tag(tagId, tagLabel);

    byte buffer[8] = {0x40, 0x49, 0x0F, 0xDB, 0x21, 0x09, 0x4E, 0xC0}; // Represents 44100.0 in big-endian float



    matroskaVideo->decodeFloatTags(&tag, buffer);



    EXPECT_EQ(matroskaVideo->xmpData_["UnknownTag"].toFloat(), 44100.0);

}
