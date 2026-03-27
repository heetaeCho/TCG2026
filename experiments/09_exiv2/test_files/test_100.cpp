#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MatroskaVideoTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    MatroskaVideo* matroska_video_;



    void SetUp() override {

        io_ = BasicIo::createMemIo();

        matroska_video_ = new MatroskaVideo(std::move(io_));

    }



    void TearDown() override {

        delete matroska_video_;

    }

};



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_NormalOperation_Width_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58 };

    MatroskaTag tag(Xmp_video_Width_1, "Xmp.video.Width", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->width_, 600);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_NormalOperation_Height_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58 };

    MatroskaTag tag(Xmp_video_Height_1, "Xmp.video.Height", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->height_, 600);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_BoundaryCondition_ZeroValue_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    MatroskaTag tag(Xmp_video_Width_1, "Xmp.video.Width", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->width_, 0);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_BoundaryCondition_MaxValue_100) {

    byte buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    MatroskaTag tag(Xmp_video_Height_2, "Xmp.video.Height", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->height_, UINT64_MAX);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_UnrecognizedTag_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58 };

    MatroskaTag tag(9999, "Unrecognized.Tag", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->width_, 0);

    EXPECT_EQ(matroska_video_->height_, 0);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_XmpDataUpdate_Width_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58 };

    MatroskaTag tag(Xmp_video_Width_1, "Xmp.video.Width", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->xmpData_["Xmp.video.Width"].toInt64(), 600);

}



TEST_F(MatroskaVideoTest_100, DecodeIntegerTags_XmpDataUpdate_Height_100) {

    byte buffer[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58 };

    MatroskaTag tag(Xmp_video_Height_2, "Xmp.video.Height", UndefinedType, Undefined);



    matroska_video_->decodeIntegerTags(&tag, buffer);

    EXPECT_EQ(matroska_video_->xmpData_["Xmp.video.Height"].toInt64(), 600);

}
