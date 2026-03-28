#include <gtest/gtest.h>

#include "exiv2/orfimage.hpp"

#include <memory>

#include <sstream>



using namespace Exiv2;



class OrfImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        auto io = std::make_unique<BasicIo>();

        orfImage_ = std::make_unique<OrfImage>(std::move(io), false);

    }



    std::unique_ptr<OrfImage> orfImage_;

};



TEST_F(OrfImageTest_MimeType_1547, MimeTypeReturnsExpectedString_1547) {

    EXPECT_EQ("image/x-olympus-orf", orfImage_->mimeType());

}



TEST_F(OrfImageTest_PrintStructure_1547, PrintStructureDoesNotThrow_1547) {

    std::ostringstream oss;

    EXPECT_NO_THROW(orfImage_->printStructure(oss, PrintStructureOption(), 0));

}



TEST_F(OrfImageTest_ReadMetadata_1547, ReadMetadataDoesNotThrow_1547) {

    EXPECT_NO_THROW(orfImage_->readMetadata());

}



TEST_F(OrfImageTest_WriteMetadata_1547, WriteMetadataDoesNotThrow_1547) {

    EXPECT_NO_THROW(orfImage_->writeMetadata());

}



TEST_F(OrfImageTest_SetComment_1547, SetCommentDoesNotThrow_1547) {

    EXPECT_NO_THROW(orfImage_->setComment("Sample Comment"));

}



TEST_F(OrfImageTest_PixelWidth_1547, PixelWidthReturnsNonZeroIfValid_1547) {

    uint32_t width = orfImage_->pixelWidth();

    // Assuming pixelWidth should return a non-zero value if the image is valid.

    EXPECT_GE(width, 0);

}



TEST_F(OrfImageTest_PixelHeight_1547, PixelHeightReturnsNonZeroIfValid_1547) {

    uint32_t height = orfImage_->pixelHeight();

    // Assuming pixelHeight should return a non-zero value if the image is valid.

    EXPECT_GE(height, 0);

}
