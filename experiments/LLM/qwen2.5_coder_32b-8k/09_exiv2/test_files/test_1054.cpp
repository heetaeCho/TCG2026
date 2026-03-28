#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1054 : public ::testing::Test {

protected:

    // Create a mock BasicIo object if needed using Google Mock

    std::unique_ptr<BasicIo> io = nullptr;

    Image image {ImageType::jpeg, 0x1F, std::move(io)};

};



TEST_F(ImageTest_1054, Is8ByteType_RationalType_1054) {

    EXPECT_TRUE(image.is8ByteType(unsignedRational));

}



TEST_F(ImageTest_1054, Is8ByteType_LongLongType_1054) {

    EXPECT_TRUE(image.is8ByteType(unsignedLongLong));

}



TEST_F(ImageTest_1054, Is8ByteType_TiffIfd8Type_1054) {

    EXPECT_TRUE(image.is8ByteType(tiffIfd8));

}



TEST_F(ImageTest_1054, Is8ByteType_TiffDoubleType_1054) {

    EXPECT_TRUE(image.is8ByteType(tiffDouble));

}



TEST_F(ImageTest_1054, Is8ByteType_OtherTypesFalse_1054) {

    EXPECT_FALSE(image.is8ByteType(unsignedByte));

    EXPECT_FALSE(image.is8ByteType(asciiString));

    EXPECT_FALSE(image.is8ByteType(unsignedShort));

    EXPECT_FALSE(image.is8ByteType(unsignedLong));

}



TEST_F(ImageTest_1054, Is8ByteType_BoundaryCondition_1054) {

    EXPECT_FALSE(image.is8ByteType(invalidTypeId - 1));

    EXPECT_FALSE(image.is8ByteType(lastTypeId + 1));

}
