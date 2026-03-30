#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1052 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = nullptr;

    Image* image = nullptr;



    void SetUp() override {

        io = BasicIo::createMemIo();

        image = new Image(imageTypeJpeg, 0x7fff, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1052, Is2ByteType_ValidShortType_1052) {

    EXPECT_TRUE(image->is2ByteType(typeShort));

}



TEST_F(ImageTest_1052, Is2ByteType_InValidShortType_1052) {

    EXPECT_FALSE(image->is2ByteType(typeLong));

}



TEST_F(ImageTest_1052, Is2ByteType_BoundaryCondition_1052) {

    EXPECT_TRUE(image->is2ByteType(3));  // Assuming typeShort is 3

    EXPECT_FALSE(image->is2ByteType(4)); // Assuming typeLong is not 3

}



TEST_F(ImageTest_1052, Is2ByteType_InvalidType_1052) {

    EXPECT_FALSE(image->is2ByteType(9999)); // Some arbitrary invalid type

}
