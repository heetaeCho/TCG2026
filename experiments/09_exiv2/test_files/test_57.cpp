#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = std::make_unique<BasicIo>();

    Image image{ImageType::jpeg, 0x1F, std::move(io)};

};



TEST_F(ImageTest_57, ImageType_ReturnsCorrectType_57) {

    EXPECT_EQ(image.imageType(), ImageType::jpeg);

}



TEST_F(ImageTest_57, PixelWidth_DefaultValueIsZero_57) {

    EXPECT_EQ(image.pixelWidth(), 0U);

}



TEST_F(ImageTest_57, PixelHeight_DefaultValueIsZero_57) {

    EXPECT_EQ(image.pixelHeight(), 0U);

}



TEST_F(ImageTest_57, Comment_DefaultValueIsEmptyString_57) {

    EXPECT_TRUE(image.comment().empty());

}



TEST_F(ImageTest_57, WriteXmpFromPacket_DefaultValueIsFalse_57) {

    EXPECT_FALSE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_57, SupportsMetadata_ReturnsTrueForSupportedMetadata_57) {

    EXPECT_TRUE(image.supportsMetadata(MetadataId::exif));

}



TEST_F(ImageTest_57, SupportsMetadata_ReturnsFalseForUnsupportedMetadata_57) {

    EXPECT_FALSE(image.supportsMetadata(MetadataId::xmp));

}



TEST_F(ImageTest_57, SetComment_ChangesCommentValue_57) {

    image.setComment("Sample Comment");

    EXPECT_EQ(image.comment(), "Sample Comment");

}



TEST_F(ImageTest_57, ClearComment_ResetsCommentValueToEmpty_57) {

    image.setComment("Sample Comment");

    image.clearComment();

    EXPECT_TRUE(image.comment().empty());

}



TEST_F(ImageTest_57, SetWriteXmpFromPacket_ChangesFlagValue_57) {

    image.writeXmpFromPacket(true);

    EXPECT_TRUE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_57, ClearExifData_DoesNotThrowException_57) {

    EXPECT_NO_THROW(image.clearExifData());

}



TEST_F(ImageTest_57, ClearIptcData_DoesNotThrowException_57) {

    EXPECT_NO_THROW(image.clearIptcData());

}



TEST_F(ImageTest_57, ClearXmpPacket_DoesNotThrowException_57) {

    EXPECT_NO_THROW(image.clearXmpPacket());

}



TEST_F(ImageTest_57, ClearXmpData_DoesNotThrowException_57) {

    EXPECT_NO_THROW(image.clearXmpData());

}



TEST_F(ImageTest_57, ClearIccProfile_DoesNotThrowException_57) {

    EXPECT_NO_THROW(image.clearIccProfile());

}
