#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader = std::make_unique<MnHeader>();

    TiffIfdMakernote tiff_ifd_makernote{1, IfdId::rootIFD, IfdId::exifIFD, std::move(pHeader), false};

};



TEST_F(TiffIfdMakernoteTest, ConstructorInitializesCorrectly_361) {

    EXPECT_EQ(tiff_ifd_makernote.tag(), 1);

}



TEST_F(TiffIfdMakernoteTest, SetByteOrderChangesByteOrder_361) {

    tiff_ifd_makernote.setByteOrder(bigEndian);

    EXPECT_EQ(tiff_ifd_makernote.byteOrder(), bigEndian);



    tiff_ifd_makernote.setByteOrder(littleEndian);

    EXPECT_EQ(tiff_ifd_makernote.byteOrder(), littleEndian);

}



TEST_F(TiffIfdMakernoteTest, SetImageByteOrderChangesImageByteOrder_361) {

    tiff_ifd_makernote.setImageByteOrder(bigEndian);

    EXPECT_EQ(tiff_ifd_makernote.byteOrder(), bigEndian);



    tiff_ifd_makernote.setImageByteOrder(littleEndian);

    EXPECT_EQ(tiff_ifd_makernote.byteOrder(), littleEndian);

}



TEST_F(TiffIfdMakernoteTest, DoCountReturnsCorrectValue_361) {

    EXPECT_EQ(tiff_ifd_makernote.doCount(), 0u);

}



TEST_F(TiffIfdMakernoteTest, CountReturnsCorrectValue_361) {

    EXPECT_EQ(tiff_ifd_makernote.count(), 0u);

}
