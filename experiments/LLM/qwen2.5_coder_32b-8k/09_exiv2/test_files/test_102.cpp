#include <gtest/gtest.h>

#include "matroskavideo.hpp"

#include "image.hpp"



namespace Exiv2 {

namespace {



class MatroskaVideoTest_102 : public ::testing::Test {

protected:

    MatroskaVideoTest_102() : matroskaVideo(nullptr) {}



    void SetUp() override {

        auto io = std::make_unique<BasicIo>();

        matroskaVideo = new MatroskaVideo(std::move(io));

    }



    void TearDown() override {

        delete matroskaVideo;

    }



    MatroskaVideo* matroskaVideo;

};



TEST_F(MatroskaVideoTest_102, DecodeDateTags_Xmp_video_Duration_SmallSize_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::Xmp_video_Duration, "Duration");

    byte buf[] = {0x40, 0x49, 0x0f, 0xdb}; // IEEE754 representation of 1.0 in little-endian

    size_t size = sizeof(buf);



    matroskaVideo->decodeDateTags(&tag, buf, size);

    EXPECT_EQ(matroskaVideo->xmpData_["Duration"].toInt64(), 1000); // 1 second in milliseconds

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_Xmp_video_Duration_LargeSize_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::Xmp_video_Duration, "Duration");

    byte buf[] = {0x3f, 0xf1, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9a}; // IEEE754 representation of 1.0 in little-endian

    size_t size = sizeof(buf);



    matroskaVideo->decodeDateTags(&tag, buf, size);

    EXPECT_EQ(matroskaVideo->xmpData_["Duration"].toInt64(), 1000); // 1 second in milliseconds

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_Xmp_video_DateUTC_Valid_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::Xmp_video_DateUTC, "DateUTC");

    uint64_t value = 978307200000000000; // UTC time in nanoseconds for January 1, 2001

    byte buf[sizeof(value)];

    std::memcpy(buf, &value, sizeof(value));



    matroskaVideo->decodeDateTags(&tag, buf, sizeof(buf));

    EXPECT_EQ(matroskaVideo->xmpData_["DateUTC"].toInt64(), 978307200); // UTC time in seconds

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_TimecodeScale_Valid_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::TimecodeScale, "TimecodeScale");

    uint64_t value = 1000000;

    byte buf[sizeof(value)];

    std::memcpy(buf, &value, sizeof(value));



    matroskaVideo->decodeDateTags(&tag, buf, sizeof(buf));

    EXPECT_EQ(matroskaVideo->xmpData_["TimecodeScale"].toFloat(), 0.001);

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_Xmp_video_Duration_ZeroSize_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::Xmp_video_Duration, "Duration");

    byte buf[] = {};

    size_t size = sizeof(buf);



    matroskaVideo->decodeDateTags(&tag, buf, size);

    EXPECT_EQ(matroskaVideo->xmpData_.find("Duration"), matroskaVideo->xmpData_.end());

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_Xmp_video_DateUTC_ZeroValue_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::Xmp_video_DateUTC, "DateUTC");

    uint64_t value = 0;

    byte buf[sizeof(value)];

    std::memcpy(buf, &value, sizeof(value));



    matroskaVideo->decodeDateTags(&tag, buf, sizeof(buf));

    EXPECT_EQ(matroskaVideo->xmpData_.find("DateUTC"), matroskaVideo->xmpData_.end());

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_TimecodeScale_ZeroValue_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::TimecodeScale, "TimecodeScale");

    uint64_t value = 0;

    byte buf[sizeof(value)];

    std::memcpy(buf, &value, sizeof(value));



    matroskaVideo->decodeDateTags(&tag, buf, sizeof(buf));

    EXPECT_EQ(matroskaVideo->xmpData_["TimecodeScale"].toFloat(), 1.0);

}



TEST_F(MatroskaVideoTest_102, DecodeDateTags_DefaultCase_102) {

    Internal::MatroskaTag tag(Exiv2::Internal::matroskaEnum::ChapterDisplay, "Display");

    byte buf[] = {0x40, 0x49, 0x0f, 0xdb}; // Arbitrary data

    size_t size = sizeof(buf);



    matroskaVideo->decodeDateTags(&tag, buf, size);

    EXPECT_EQ(matroskaVideo->xmpData_.find("Display"), matroskaVideo->xmpData_.end());

}



} // namespace

} // namespace Exiv2
