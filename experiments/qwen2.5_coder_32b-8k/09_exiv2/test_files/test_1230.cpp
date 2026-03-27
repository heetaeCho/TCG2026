#include <gtest/gtest.h>

#include "exiv2/tgaimage.hpp"

#include "mock_basicio.hpp"  // Assuming a mock class for BasicIo exists



using namespace Exiv2;

using ::testing::NiceMock;



class TgaImageTest_1230 : public ::testing::Test {

protected:

    std::unique_ptr<NiceMock<MockBasicIo>> io_;

    TgaImage* tga_image_;



    void SetUp() override {

        io_ = std::make_unique<NiceMock<MockBasicIo>>();

        tga_image_ = new TgaImage(std::move(io_));

    }



    void TearDown() override {

        delete tga_image_;

    }

};



TEST_F(TgaImageTest_1230, MimeTypeReturnsCorrectType_1230) {

    EXPECT_EQ(tga_image_->mimeType(), "image/targa");

}



TEST_F(TgaImageTest_1230, SetExifDataDoesNotThrow_1230) {

    ExifData exifData;

    EXPECT_NO_THROW(tga_image_->setExifData(exifData));

}



TEST_F(TgaImageTest_1230, SetIptcDataDoesNotThrow_1230) {

    IptcData iptcData;

    EXPECT_NO_THROW(tga_image_->setIptcData(iptcData));

}



TEST_F(TgaImageTest_1230, SetCommentDoesNotThrow_1230) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(tga_image_->setComment(comment));

}



TEST_F(TgaImageTest_1230, ReadMetadataDoesNotThrow_1230) {

    EXPECT_NO_THROW(tga_image_->readMetadata());

}



TEST_F(TgaImageTest_1230, WriteMetadataDoesNotThrow_1230) {

    EXPECT_NO_THROW(tga_image_->writeMetadata());

}
