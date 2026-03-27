#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"

#include "exiv2/xmp_exiv2.hpp"



namespace Exiv2 {

    namespace Internal {

        struct MatroskaTag;

    }

}



using ::testing::Test;



class MatroskaVideoTest_99 : public Test {

protected:

    std::unique_ptr<Exiv2::BasicIo> io = nullptr; // Assuming BasicIo is a mock or a dummy implementation

    Exiv2::MatroskaVideo* matroskaVideo = nullptr;



    void SetUp() override {

        io.reset(new Exiv2::FileIo());

        matroskaVideo = new Exiv2::MatroskaVideo(std::move(io));

    }



    void TearDown() override {

        delete matroskaVideo;

    }

};



TEST_F(MatroskaVideoTest_99, DecodeStringTags_TrackNumber_IncreasesTrackCount_99) {

    Exiv2::Internal::MatroskaTag tag(Exiv2::Internal::TrackNumber, "track_label");

    const byte* buf = nullptr; // Not used in this case



    matroskaVideo->decodeStringTags(&tag, buf);

    EXPECT_EQ(matroskaVideo->xmpData()["track_label"].toString(), "1");

}



TEST_F(MatroskaVideoTest_99, DecodeStringTags_NonTrackNumber_DoesNotIncreaseTrackCount_99) {

    Exiv2::Internal::MatroskaTag tag(Exiv2::Internal::Xmp_video_Width_1, "width_label");

    const byte* buf = reinterpret_cast<const byte*>("640");



    matroskaVideo->decodeStringTags(&tag, buf);

    EXPECT_EQ(matroskaVideo->xmpData()["width_label"].toString(), "640");

}



TEST_F(MatroskaVideoTest_99, DecodeStringTags_EmptyBuffer_NonTrackNumber_SetsEmptyValue_99) {

    Exiv2::Internal::MatroskaTag tag(Exiv2::Internal::Xmp_video_Width_1, "width_label");

    const byte* buf = nullptr;



    matroskaVideo->decodeStringTags(&tag, buf);

    EXPECT_EQ(matroskaVideo->xmpData()["width_label"].toString(), "");

}



TEST_F(MatroskaVideoTest_99, DecodeStringTags_MultipleTrackNumbers_IncreasesTrackCountCorrectly_99) {

    Exiv2::Internal::MatroskaTag tag1(Exiv2::Internal::TrackNumber, "track_label1");

    const byte* buf = nullptr;



    matroskaVideo->decodeStringTags(&tag1, buf);

    EXPECT_EQ(matroskaVideo->xmpData()["track_label1"].toString(), "1");



    Exiv2::Internal::MatroskaTag tag2(Exiv2::Internal::TrackNumber, "track_label2");

    matroskaVideo->decodeStringTags(&tag2, buf);

    EXPECT_EQ(matroskaVideo->xmpData()["track_label2"].toString(), "2");

}
