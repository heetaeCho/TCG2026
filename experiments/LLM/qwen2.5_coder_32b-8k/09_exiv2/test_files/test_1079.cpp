#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::autoPtr();

    Image* image = new Image(ImageType::jpeg, 0x1, std::move(io));



    ~ImageTest() override {

        delete image;

    }

};



TEST_F(ImageTest_1079, ClearXmpData_RemovesAllXmpData_1079) {

    // Arrange

    XmpData& xmpData = image->xmpData();

    xmpData.add(XmpKey("Xmp.dc.title"), new Value("Sample Title"));



    // Act

    image->clearXmpData();



    // Assert

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(ImageTest_1079, ClearXmpData_DoesNotThrowOnEmptyData_1079) {

    // Arrange

    XmpData& xmpData = image->xmpData();

    ASSERT_TRUE(xmpData.empty());



    // Act & Assert

    EXPECT_NO_THROW(image->clearXmpData());

}



TEST_F(ImageTest_1079, ClearXmpData_DoesNotAffectOtherMetadata_1079) {

    // Arrange

    IptcData& iptcData = image->iptcData();

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new Value("Sample Caption"));



    // Act

    image->clearXmpData();



    // Assert

    EXPECT_FALSE(iptcData.empty());

}



TEST_F(ImageTest_1079, ClearXmpData_CallsWriteXmpFromPacketWithFalse_1079) {

    // Arrange

    bool writeXmpFromPacketCalled = false;

    image->writeXmpFromPacket_ = [&writeXmpFromPacketCalled](bool flag) {

        EXPECT_FALSE(flag);

        writeXmpFromPacketCalled = true;

    };



    // Act

    image->clearXmpData();



    // Assert

    EXPECT_TRUE(writeXmpFromPacketCalled);

}



TEST_F(ImageTest_1079, ClearXmpData_DoesNotChangeByteOrder_1079) {

    // Arrange

    ByteOrder originalByteOrder = image->byteOrder();

    XmpData& xmpData = image->xmpData();

    xmpData.add(XmpKey("Xmp.dc.title"), new Value("Sample Title"));



    // Act

    image->clearXmpData();



    // Assert

    EXPECT_EQ(originalByteOrder, image->byteOrder());

}



TEST_F(ImageTest_1079, ClearXmpData_DoesNotChangeMetadataSupport_1079) {

    // Arrange

    uint16_t originalSupportedMetadata = image->supportedMetadata_;

    XmpData& xmpData = image->xmpData();

    xmpData.add(XmpKey("Xmp.dc.title"), new Value("Sample Title"));



    // Act

    image->clearXmpData();



    // Assert

    EXPECT_EQ(originalSupportedMetadata, image->supportedMetadata_);

}
