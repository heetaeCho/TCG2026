#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using testing::Throw;



class BmffImageTest_1202 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    BmffImage image{std::move(io), false, 10};

};



TEST_F(BmffImageTest_1202, WriteMetadataThrowsUnsupportedFormatError_1202) {

    EXPECT_THROW(image.writeMetadata(), Error);

}



TEST_F(BmffImageTest_1202, SetExifDataDoesNotThrow_1202) {

    ExifData exifData;

    EXPECT_NO_THROW(image.setExifData(exifData));

}



TEST_F(BmffImageTest_1202, SetIptcDataDoesNotThrow_1202) {

    IptcData iptcData;

    EXPECT_NO_THROW(image.setIptcData(iptcData));

}



TEST_F(BmffImageTest_1202, SetXmpDataDoesNotThrow_1202) {

    XmpData xmpData;

    EXPECT_NO_THROW(image.setXmpData(xmpData));

}



TEST_F(BmffImageTest_1202, SetCommentDoesNotThrow_1202) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(image.setComment(comment));

}



TEST_F(BmffImageTest_1202, MimeTypeReturnsNonEmptyString_1202) {

    EXPECT_FALSE(image.mimeType().empty());

}



TEST_F(BmffImageTest_1202, PixelWidthDoesNotThrow_1202) {

    EXPECT_NO_THROW(image.pixelWidth());

}



TEST_F(BmffImageTest_1202, PixelHeightDoesNotThrow_1202) {

    EXPECT_NO_THROW(image.pixelHeight());

}



TEST_F(BmffImageTest_1202, ParseTiffSingleParamDoesNotThrow_1202) {

    EXPECT_NO_THROW(image.parseTiff(0x49492A00, 8));

}



TEST_F(BmffImageTest_1202, ParseTiffDoubleParamDoesNotThrow_1202) {

    EXPECT_NO_THROW(image.parseTiff(0x49492A00, 8, 0));

}



TEST_F(BmffImageTest_1202, ParseXmpDoesNotThrow_1202) {

    EXPECT_NO_THROW(image.parseXmp(8, 0));

}
