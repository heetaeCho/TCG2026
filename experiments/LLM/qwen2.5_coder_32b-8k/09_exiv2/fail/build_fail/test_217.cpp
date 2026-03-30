#include <gtest/gtest.h>

#include "exiv2/rafimage.hpp"

#include <memory>



using namespace Exiv2;



class RafImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    std::unique_ptr<RafImage> rafImage;



    void SetUp() override {

        rafImage = std::make_unique<RafImage>(std::move(io), false);

    }

};



TEST_F(RafImageTest_217, MimeTypeReturnsCorrectValue_217) {

    EXPECT_EQ(rafImage->mimeType(), "image/x-fuji-raf");

}



TEST_F(RafImageTest_217, PixelWidthBoundaryCondition_217) {

    // Assuming pixelWidth can return 0 if not set or some default value

    EXPECT_GE(rafImage->pixelWidth(), 0);

}



TEST_F(RafImageTest_217, PixelHeightBoundaryCondition_217) {

    // Assuming pixelHeight can return 0 if not set or some default value

    EXPECT_GE(rafImage->pixelHeight(), 0);

}



TEST_F(RafImageTest_217, SetExifDataDoesNotThrow_217) {

    ExifData exifData;

    EXPECT_NO_THROW(rafImage->setExifData(exifData));

}



TEST_F(RafImageTest_217, SetIptcDataDoesNotThrow_217) {

    IptcData iptcData;

    EXPECT_NO_THROW(rafImage->setIptcData(iptcData));

}



TEST_F(RafImageTest_217, SetCommentDoesNotThrow_217) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(rafImage->setComment(comment));

}



TEST_F(RafImageTest_217, PrintStructureDoesNotThrowWithValidOption_217) {

    std::ostringstream out;

    PrintStructureOption option = kpsNone;

    size_t depth = 0;

    EXPECT_NO_THROW(rafImage->printStructure(out, option, depth));

}



TEST_F(RafImageTest_217, ReadMetadataDoesNotThrow_217) {

    EXPECT_NO_THROW(rafImage->readMetadata());

}



TEST_F(RafImageTest_217, WriteMetadataDoesNotThrow_217) {

    EXPECT_NO_THROW(rafImage->writeMetadata());

}
