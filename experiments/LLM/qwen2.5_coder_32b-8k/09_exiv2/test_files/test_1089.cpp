#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_1089 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = BasicIo::create("dummy.jpg");

        image = new Image(imageJpeg, 0x7f, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1089, ByteOrderDefault_1089) {

    EXPECT_EQ(image->byteOrder(), invalidByteOrder);

}



TEST_F(ImageTest_1089, SetAndCheckByteOrder_1089) {

    image->setByteOrder(littleEndian);

    EXPECT_EQ(image->byteOrder(), littleEndian);



    image->setByteOrder(bigEndian);

    EXPECT_EQ(image->byteOrder(), bigEndian);

}



TEST_F(ImageTest_1089, ByteOrderBoundaryCondition_1089) {

    image->setByteOrder(static_cast<ByteOrder>(-1));

    EXPECT_NE(image->byteOrder(), littleEndian);

    EXPECT_NE(image->byteOrder(), bigEndian);

}



TEST_F(ImageTest_1089, GoodMethodInitialValue_1089) {

    EXPECT_TRUE(image->good());

}
