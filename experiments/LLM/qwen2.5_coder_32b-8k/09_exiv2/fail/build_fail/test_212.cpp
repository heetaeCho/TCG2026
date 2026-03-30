#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/gifimage.hpp"

#include "exiv2/error.hpp"

#include <memory>



using namespace Exiv2;

using ::testing::_;

using ::testing::Throw;



class GifImageTest_212 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock = BasicIo::createMemIo();

    std::unique_ptr<GifImage> gifImage;



    void SetUp() override {

        gifImage = std::make_unique<GifImage>(std::move(ioMock));

    }

};



TEST_F(GifImageTest_212, WriteMetadataThrowsWritingImageFormatUnsupportedError_212) {

    EXPECT_THROW(gifImage->writeMetadata(), Error);

    try {

        gifImage->writeMetadata();

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);

        EXPECT_STREQ(e.what(), "GIF");

    }

}



TEST_F(GifImageTest_212, ReadMetadataDoesNotThrowException_212) {

    EXPECT_NO_THROW(gifImage->readMetadata());

}



TEST_F(GifImageTest_212, SetExifDataDoesNotThrowException_212) {

    ExifData exifData;

    EXPECT_NO_THROW(gifImage->setExifData(exifData));

}



TEST_F(GifImageTest_212, SetIptcDataDoesNotThrowException_212) {

    IptcData iptcData;

    EXPECT_NO_THROW(gifImage->setIptcData(iptcData));

}



TEST_F(GifImageTest_212, SetCommentDoesNotThrowException_212) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(gifImage->setComment(comment));

}



TEST_F(GifImageTest_212, MimeTypeReturnsCorrectValue_212) {

    EXPECT_EQ(gifImage->mimeType(), "image/gif");

}
