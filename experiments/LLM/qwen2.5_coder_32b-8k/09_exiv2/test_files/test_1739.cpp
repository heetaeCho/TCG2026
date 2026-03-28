#include <gtest/gtest.h>

#include "exiv2/cr2image.hpp"



using namespace Exiv2;



class Cr2ImageTest_1739 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io;

    std::unique_ptr<Cr2Image> cr2Image;



    void SetUp() override {

        io = BasicIo::createMemIo();

        cr2Image = std::make_unique<Cr2Image>(std::move(io), false);

    }

};



TEST_F(Cr2ImageTest_1739, MimeTypeReturnsCorrectValue_1739) {

    EXPECT_EQ(cr2Image->mimeType(), "image/x-canon-cr2");

}



TEST_F(Cr2ImageTest_1739, PixelWidthBoundaryCondition_1739) {

    // Assuming pixelWidth is not observable without reading metadata, we can't directly test its value.

    // However, we can ensure it doesn't throw an exception.

    EXPECT_NO_THROW(cr2Image->pixelWidth());

}



TEST_F(Cr2ImageTest_1739, PixelHeightBoundaryCondition_1739) {

    // Similar to pixelWidth, we can only check for exceptions.

    EXPECT_NO_THROW(cr2Image->pixelHeight());

}



TEST_F(Cr2ImageTest_1739, PrintStructureNoThrowOnValidParameters_1739) {

    std::ostringstream out;

    EXPECT_NO_THROW(cr2Image->printStructure(out, kpsNone, 0));

}



TEST_F(Cr2ImageTest_1739, SetCommentNoThrowOnValidString_1739) {

    EXPECT_NO_THROW(cr2Image->setComment("Sample Comment"));

}



TEST_F(Cr2ImageTest_1739, ReadMetadataNoThrow_1739) {

    EXPECT_NO_THROW(cr2Image->readMetadata());

}



TEST_F(Cr2ImageTest_1739, WriteMetadataNoThrow_1739) {

    EXPECT_NO_THROW(cr2Image->writeMetadata());

}
