#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image* image;



    void SetUp() override {

        image = new Image(imageJpeg, mdExif | mdIptc | mdXmp, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1088, SetByteOrder_NormalOperation_1088) {

    image->setByteOrder(bigEndian);

    EXPECT_EQ(image->byteOrder(), bigEndian);



    image->setByteOrder(littleEndian);

    EXPECT_EQ(image->byteOrder(), littleEndian);

}



TEST_F(ImageTest_1088, SetByteOrder_BoundaryConditions_1088) {

    image->setByteOrder(invalidByteOrder);

    EXPECT_EQ(image->byteOrder(), invalidByteOrder);

}



// Assuming ByteOrder is an enum with possible values: bigEndian, littleEndian, invalidByteOrder

// No exceptional cases are observable through the interface for setByteOrder based on provided information.

```


