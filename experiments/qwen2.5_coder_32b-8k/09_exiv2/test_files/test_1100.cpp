#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {

    struct Registry;

}



using namespace Exiv2;



class ImageFactoryTest : public ::testing::Test {

protected:

    ImageFactory factory;

};



TEST_F(ImageFactoryTest_1100, CheckMode_ExifSupported_Jpeg_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::jpeg, MetadataId::mdExif), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcSupported_Jpeg_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::jpeg, MetadataId::mdIptc), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpSupported_Jpeg_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::jpeg, MetadataId::mdXmp), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentSupported_Jpeg_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::jpeg, MetadataId::mdComment), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifUnsupported_Cr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::cr2, MetadataId::mdExif), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcUnsupported_Cr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::cr2, MetadataId::mdIptc), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpUnsupported_Cr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::cr2, MetadataId::mdXmp), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Cr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::cr2, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifSupported_Tiff_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::tiff, MetadataId::mdExif), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcSupported_Tiff_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::tiff, MetadataId::mdIptc), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpUnsupported_Tiff_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::tiff, MetadataId::mdXmp), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Tiff_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::tiff, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifRead_Mrw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::mrw, MetadataId::mdExif), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcRead_Mrw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::mrw, MetadataId::mdIptc), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpNone_Mrw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::mrw, MetadataId::mdXmp), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Mrw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::mrw, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifRead_Arw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::arw, MetadataId::mdExif), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcRead_Arw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::arw, MetadataId::mdIptc), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpNone_Arw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::arw, MetadataId::mdXmp), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Arw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::arw, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifRead_Rw2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::rw2, MetadataId::mdExif), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcRead_Rw2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::rw2, MetadataId::mdIptc), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpNone_Rw2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::rw2, MetadataId::mdXmp), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Rw2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::rw2, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifRead_Sr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::sr2, MetadataId::mdExif), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcRead_Sr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::sr2, MetadataId::mdIptc), AccessMode::amRead);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpNone_Sr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::sr2, MetadataId::mdXmp), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentNone_Sr2_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::sr2, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifReadWrite_Srw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::srw, MetadataId::mdExif), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcReadWrite_Srw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::srw, MetadataId::mdIptc), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpReadWrite_Srw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::srw, MetadataId::mdXmp), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentReadWrite_Srw_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::srw, MetadataId::mdComment), AccessMode::amReadWrite);

}



TEST_F(ImageFactoryTest_1100, CheckMode_ExifUnsupported_Gif_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::gif, MetadataId::mdExif), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_IptcUnsupported_Gif_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::gif, MetadataId::mdIptc), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_XmpUnsupported_Gif_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::gif, MetadataId::mdXmp), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_CommentUnsupported_Gif_1100) {

    EXPECT_EQ(factory.checkMode(ImageType::gif, MetadataId::mdComment), AccessMode::amNone);

}



TEST_F(ImageFactoryTest_1100, CheckMode_UnsupportedImageType_1100) {

    EXPECT_THROW(factory.checkMode(static_cast<ImageType>(999), MetadataId::mdExif), Exiv2::Error);

}
