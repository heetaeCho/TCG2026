#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_1075 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = std::make_unique<BasicIo>();

        image = new Image(ImageType::jpeg, 0x7f, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1075, ClearIptcData_NonEmptyIptcData_1075) {

    // Arrange

    IptcData& iptcData = image->iptcData();

    iptcData.add(IptcKey("Iptc.Application2.Keywords"), new Value(std::string("test")));



    // Act

    image->clearIptcData();



    // Assert

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(ImageTest_1075, ClearIptcData_EmptyIptcData_1075) {

    // Arrange

    IptcData& iptcData = image->iptcData();

    EXPECT_TRUE(iptcData.empty());



    // Act

    image->clearIptcData();



    // Assert

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(ImageTest_1075, ClearIptcData_MultipleEntriesInIptcData_1075) {

    // Arrange

    IptcData& iptcData = image->iptcData();

    iptcData.add(IptcKey("Iptc.Application2.Keywords"), new Value(std::string("test1")));

    iptcData.add(IptcKey("Iptc.Application2.CaptionWriter"), new Value(std::string("test2")));



    // Act

    image->clearIptcData();



    // Assert

    EXPECT_TRUE(iptcData.empty());

}
