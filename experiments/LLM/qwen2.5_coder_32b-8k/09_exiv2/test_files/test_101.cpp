#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;



class MatroskaVideoTest_101 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = std::make_unique<MemIo>();

    MatroskaVideo video{std::move(io)};

    const byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 1}; // Represents the value '1' in big-endian

};



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackType_Video_101) {

    const Internal::MatroskaTag tag{TrackType, "TrackType"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.stream_, 1u); // Video

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackType_Audio_101) {

    const Internal::MatroskaTag tag{TrackType, "TrackType"};

    video.decodeBooleanTags(&tag, &buf[7]); // Represents the value '1' in little-endian

    EXPECT_EQ(video.stream_, 2u); // Audio

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackUsed_DefaultOn_101) {

    const Internal::MatroskaTag tag{TrackUsed, "TrackUsed"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.Enabled"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackDefault_DefaultOn_101) {

    const Internal::MatroskaTag tag{TrackDefault, "TrackDefault"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.DefaultOn"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackForced_DefaultOn_101) {

    const Internal::MatroskaTag tag{TrackForced, "TrackForced"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.TrackForced"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_TrackLacing_DefaultOn_101) {

    const Internal::MatroskaTag tag{TrackLacing, "TrackLacing"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.TrackLacing"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_CodecDecodeAll_DefaultOn_101) {

    const Internal::MatroskaTag tag{CodecDecodeAll, "CodecDecodeAll"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.CodecDecodeAll"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_CodecSettings_DefaultOn_101) {

    const Internal::MatroskaTag tag{CodecSettings, "CodecSettings"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp.video.CodecSettings"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_Xmp_video_TagDefault_DefaultOn_101) {

    const Internal::MatroskaTag tag{Xmp_video_TagDefault, "Xmp_video_TagDefault"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_["Xmp_video.TagDefault"], "Yes");

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_ZeroKey_NoEffect_101) {

    const Internal::MatroskaTag tag{TrackUsed, "TrackUsed"};

    video.decodeBooleanTags(&tag, &buf[7]); // Represents the value '0' in little-endian

    EXPECT_EQ(video.xmpData_.count(), 0);

}



TEST_F(MatroskaVideoTest_101, DecodeBooleanTags_UnrecognizedTag_NoEffect_101) {

    const Internal::MatroskaTag tag{5546, "UnrecognizedTag"};

    video.decodeBooleanTags(&tag, buf);

    EXPECT_EQ(video.xmpData_.count(), 0);

}
