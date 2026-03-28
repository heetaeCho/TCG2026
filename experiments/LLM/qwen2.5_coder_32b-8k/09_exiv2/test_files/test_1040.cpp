#include <gtest/gtest.h>

#include "exiv2/bmpimage.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class BmpImageTest_1040 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = BasicIo::createMemIo();

    std::unique_ptr<BmpImage> bmpImage;



    void SetUp() override {

        bmpImage = std::make_unique<BmpImage>(std::move(io));

    }

};



TEST_F(BmpImageTest_1040, WriteMetadataThrowsWritingImageFormatUnsupported_1040) {

    EXPECT_THROW(bmpImage->writeMetadata(), Error);

    try {

        bmpImage->writeMetadata();

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);

    }

}



TEST_F(BmpImageTest_1040, ReadMetadataDoesNotThrow_1040) {

    EXPECT_NO_THROW(bmpImage->readMetadata());

}



TEST_F(BmpImageTest_1040, SetExifDataDoesNotThrow_1040) {

    ExifData exifData;

    EXPECT_NO_THROW(bmpImage->setExifData(exifData));

}



TEST_F(BmpImageTest_1040, SetIptcDataDoesNotThrow_1040) {

    IptcData iptcData;

    EXPECT_NO_THROW(bmpImage->setIptcData(iptcData));

}



TEST_F(BmpImageTest_1040, SetCommentDoesNotThrow_1040) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(bmpImage->setComment(comment));

}



TEST_F(BmpImageTest_1040, MimeTypeReturnsCorrectType_1040) {

    EXPECT_EQ(bmpImage->mimeType(), "image/bmp");

}
