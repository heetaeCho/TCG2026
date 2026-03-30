#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class ImageTest_1080 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock = nullptr;

    Image image{ImageType::jpeg, 0x04, std::move(ioMock)};



    XmpData createSampleXmpData() {

        XmpData xmpData;

        xmpData.add(XmpKey("Xmp.dc.title"), new StringValue("Sample Title"));

        return xmpData;

    }

};



TEST_F(ImageTest_1080, SetXmpData_NormalOperation_1080) {

    XmpData sampleXmpData = createSampleXmpData();

    image.setXmpData(sampleXmpData);

    // Assuming there is a way to verify the xmpData_ member after setting, but here we check if count increases

    EXPECT_EQ(image.xmpData().count(), 1);

}



TEST_F(ImageTest_1080, SetXmpData_EmptyData_1080) {

    XmpData emptyXmpData;

    image.setXmpData(emptyXmpData);

    EXPECT_TRUE(image.xmpData().empty());

}



TEST_F(ImageTest_1080, SetXmpData_MultipleEntries_1080) {

    XmpData sampleXmpData = createSampleXmpData();

    sampleXmpData.add(XmpKey("Xmp.dc.creator"), new StringValue("Creator Name"));

    image.setXmpData(sampleXmpData);

    EXPECT_EQ(image.xmpData().count(), 2);

}



TEST_F(ImageTest_1080, SetXmpData_LargePacket_1080) {

    XmpData sampleXmpData = createSampleXmpData();

    std::string largePacket(65535, 'a'); // Large packet size

    sampleXmpData.setPacket(largePacket);

    image.setXmpData(sampleXmpData);

    EXPECT_EQ(image.xmpData().xmpPacket(), largePacket);

}



TEST_F(ImageTest_1080, SetXmpData_WriteFromPacketFlag_1080) {

    XmpData sampleXmpData = createSampleXmpData();

    image.setXmpData(sampleXmpData);

    EXPECT_FALSE(image.writeXmpFromPacket());

}
