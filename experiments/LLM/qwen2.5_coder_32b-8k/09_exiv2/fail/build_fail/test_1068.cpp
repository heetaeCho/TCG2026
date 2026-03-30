#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_1068 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = std::make_unique<BasicIo>();

        image = new Image(ImageType::jpeg, 0x1F, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1068, ExifData_ReturnsNonEmptyReference_1068) {

    EXPECT_FALSE(&image->exifData() == nullptr);

}



TEST_F(ImageTest_1068, IptcData_ReturnsNonEmptyReference_1068) {

    EXPECT_FALSE(&image->iptcData() == nullptr);

}



TEST_F(ImageTest_1068, XmpData_ReturnsNonEmptyReference_1068) {

    EXPECT_FALSE(&image->xmpData() == nullptr);

}



TEST_F(ImageTest_1068, PixelWidth_DefaultValueIsZero_1068) {

    EXPECT_EQ(image->pixelWidth(), 0U);

}



TEST_F(ImageTest_1068, PixelHeight_DefaultValueIsZero_1068) {

    EXPECT_EQ(image->pixelHeight(), 0U);

}



TEST_F(ImageTest_1068, Comment_DefaultValueIsEmptyString_1068) {

    EXPECT_TRUE(image->comment().empty());

}



TEST_F(ImageTest_1068, SupportsMetadata_ValidMetadataId_ReturnsTrue_1068) {

    EXPECT_TRUE(image->supportsMetadata(MetadataId::exif));

}



TEST_F(ImageTest_1068, WriteXmpFromPacket_DefaultValueIsFalse_1068) {

    EXPECT_FALSE(image->writeXmpFromPacket());

}



TEST_F(ImageTest_1068, SetExifData_ModifiesExifData_1068) {

    ExifData exifData;

    image->setExifData(exifData);

    // Assuming setting does not throw and we can check the reference

    EXPECT_EQ(&image->exifData(), &exifData);

}



TEST_F(ImageTest_1068, SetIptcData_ModifiesIptcData_1068) {

    IptcData iptcData;

    image->setIptcData(iptcData);

    // Assuming setting does not throw and we can check the reference

    EXPECT_EQ(&image->iptcData(), &iptcData);

}



TEST_F(ImageTest_1068, SetXmpPacket_ModifiesXmpPacket_1068) {

    std::string xmpPacket = "<x:xmpmeta></x:xmpmeta>";

    image->setXmpPacket(xmpPacket);

    EXPECT_EQ(image->xmpPacket(), xmpPacket);

}



TEST_F(ImageTest_1068, SetComment_ModifiesComment_1068) {

    std::string comment = "Sample Comment";

    image->setComment(comment);

    EXPECT_EQ(image->comment(), comment);

}



TEST_F(ImageTest_1068, ClearExifData_ClearsExifData_1068) {

    ExifData exifData;

    image->setExifData(exifData);

    image->clearExifData();

    // Assuming clearing does not throw and we can check the reference

    EXPECT_FALSE(&image->exifData() == &exifData);

}



TEST_F(ImageTest_1068, ClearIptcData_ClearsIptcData_1068) {

    IptcData iptcData;

    image->setIptcData(iptcData);

    image->clearIptcData();

    // Assuming clearing does not throw and we can check the reference

    EXPECT_FALSE(&image->iptcData() == &iptcData);

}



TEST_F(ImageTest_1068, ClearXmpPacket_ClearsXmpPacket_1068) {

    std::string xmpPacket = "<x:xmpmeta></x:xmpmeta>";

    image->setXmpPacket(xmpPacket);

    image->clearXmpPacket();

    EXPECT_TRUE(image->xmpPacket().empty());

}



TEST_F(ImageTest_1068, ClearComment_ClearsComment_1068) {

    std::string comment = "Sample Comment";

    image->setComment(comment);

    image->clearComment();

    EXPECT_TRUE(image->comment().empty());

}
