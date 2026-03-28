#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tgaimage.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class TgaImageTest_1232 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = std::make_unique<MemIo>();

    TgaImage tgaImage{std::move(io)};

};



TEST_F(TgaImageTest_1232, WriteMetadataThrowsWritingImageFormatUnsupportedError_1232) {

    EXPECT_THROW(tgaImage.writeMetadata(), Error);

    try {

        tgaImage.writeMetadata();

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);

        EXPECT_STREQ(e.what(), "TGA");

    }

}



TEST_F(TgaImageTest_1232, ReadMetadataDoesNotThrowError_1232) {

    EXPECT_NO_THROW(tgaImage.readMetadata());

}



TEST_F(TgaImageTest_1232, SetExifDataDoesNotThrowError_1232) {

    ExifData exifData;

    EXPECT_NO_THROW(tgaImage.setExifData(exifData));

}



TEST_F(TgaImageTest_1232, SetIptcDataDoesNotThrowError_1232) {

    IptcData iptcData;

    EXPECT_NO_THROW(tgaImage.setIptcData(iptcData));

}



TEST_F(TgaImageTest_1232, SetCommentDoesNotThrowError_1232) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(tgaImage.setComment(comment));

}



TEST_F(TgaImageTest_1232, MimeTypeReturnsExpectedValue_1232) {

    EXPECT_EQ(tgaImage.mimeType(), "image/targa");

}
