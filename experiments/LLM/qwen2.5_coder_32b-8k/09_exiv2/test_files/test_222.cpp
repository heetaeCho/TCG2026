#include <gtest/gtest.h>

#include "exiv2/rafimage.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {



class RafImageTest_222 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    RafImage* rafImage;



    void SetUp() override {

        io = BasicIo::autoPtr(new FileIo());

        rafImage = new RafImage(std::move(io), false);

    }



    void TearDown() override {

        delete rafImage;

    }

};



TEST_F(RafImageTest_222, WriteMetadataThrowsWritingUnsupportedError_222) {

    EXPECT_THROW(rafImage->writeMetadata(), Error);

}



TEST_F(RafImageTest_222, WriteMetadataThrowsCorrectErrorCode_222) {

    try {

        rafImage->writeMetadata();

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);

    }

}



TEST_F(RafImageTest_222, SetExifDataDoesNotThrow_222) {

    ExifData exifData;

    EXPECT_NO_THROW(rafImage->setExifData(exifData));

}



TEST_F(RafImageTest_222, SetIptcDataDoesNotThrow_222) {

    IptcData iptcData;

    EXPECT_NO_THROW(rafImage->setIptcData(iptcData));

}



TEST_F(RafImageTest_222, SetCommentDoesNotThrow_222) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(rafImage->setComment(comment));

}



TEST_F(RafImageTest_222, MimeTypeReturnsExpectedValue_222) {

    EXPECT_EQ(rafImage->mimeType(), "image/x-fujifilm-raf");

}



TEST_F(RafImageTest_222, PixelWidthDoesNotThrow_222) {

    EXPECT_NO_THROW(rafImage->pixelWidth());

}



TEST_F(RafImageTest_222, PixelHeightDoesNotThrow_222) {

    EXPECT_NO_THROW(rafImage->pixelHeight());

}



TEST_F(RafImageTest_222, PrintStructureDoesNotThrow_222) {

    std::ostringstream out;

    EXPECT_NO_THROW(rafImage->printStructure(out, 0, 0));

}



TEST_F(RafImageTest_222, ReadMetadataDoesNotThrow_222) {

    EXPECT_NO_THROW(rafImage->readMetadata());

}



} // namespace Exiv2
