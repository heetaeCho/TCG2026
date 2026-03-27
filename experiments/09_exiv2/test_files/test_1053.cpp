#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1053 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::autoPtr();

    Image image{ImageType::jpeg, 0x7FFF, std::move(io)};

};



TEST_F(ImageTest_1053, Is4ByteType_LongType_1053) {

    EXPECT_TRUE(image.is4ByteType(unsignedLong));

}



TEST_F(ImageTest_1053, Is4ByteType_FloatType_1053) {

    EXPECT_TRUE(image.is4ByteType(tiffFloat));

}



TEST_F(ImageTest_1053, Is4ByteType_IfdType_1053) {

    EXPECT_TRUE(image.is4ByteType(tiffIfd));

}



TEST_F(ImageTest_1053, Is4ByteType_ShortType_1053) {

    EXPECT_FALSE(image.is4ByteType(unsignedShort));

}



TEST_F(ImageTest_1053, Is4ByteType_RationalType_1053) {

    EXPECT_FALSE(image.is4ByteType(unsignedRational));

}



TEST_F(ImageTest_1053, Is4ByteType_StringType_1053) {

    EXPECT_FALSE(image.is4ByteType(asciiString));

}



TEST_F(ImageTest_1053, Is4ByteType_DoubleType_1053) {

    EXPECT_FALSE(image.is4ByteType(tiffDouble));

}



TEST_F(ImageTest_1053, Is4ByteType_LongLongType_1053) {

    EXPECT_FALSE(image.is4ByteType(unsignedLongLong));

}



TEST_F(ImageTest_1053, Is4ByteType_CustomDefinedBoundary_1053) {

    EXPECT_FALSE(image.is4ByteType(static_cast<uint16_t>(lastTypeId)));

}



TEST_F(ImageTest_1053, Is4ByteType_InvalidType_1053) {

    EXPECT_FALSE(image.is4ByteType(invalidTypeId));

}
