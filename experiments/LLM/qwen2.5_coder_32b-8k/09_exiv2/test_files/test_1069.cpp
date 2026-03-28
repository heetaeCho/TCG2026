#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1069 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image image_;



    void SetUp() override {

        io_ = BasicIo::createMemIo();

        image_ = Image(ImageType::jpeg, 0x7FFFU, std::move(io_));

    }

};



TEST_F(ImageTest_1069, IptcDataReferenceReturned_1069) {

    IptcData& iptcDataRef = image_.iptcData();

    EXPECT_TRUE(&iptcDataRef == &image_.iptcData());

}



// Additional test cases



TEST_F(ImageTest_1069, SetAndClearIptcData_1069) {

    IptcData initialData;

    initialData.add(Exiv2::IptcKey("Iptc.Application2.Caption", "iptc"), "Initial Caption");

    image_.setIptcData(initialData);



    IptcData& iptcDataRef = image_.iptcData();

    EXPECT_EQ(iptcDataRef.count(), 1);

    EXPECT_EQ(iptcDataRef.findKey(Exiv2::IptcKey("Iptc.Application2.Caption", "iptc"))->value(), "Initial Caption");



    image_.clearIptcData();

    EXPECT_EQ(image_.iptcData().count(), 0);

}



TEST_F(ImageTest_1069, CheckModeForSupportedMetadata_1069) {

    // Assuming ImageType::jpeg supports Exif metadata

    EXPECT_TRUE(image_.supportsMetadata(MetadataId::exif));

    EXPECT_EQ(image_.checkMode(MetadataId::exif), AccessMode::write);



    // Assuming ImageType::jpeg does not support XMP metadata (based on hypothetical setup)

    EXPECT_FALSE(image_.supportsMetadata(MetadataId::xmp));

    EXPECT_EQ(image_.checkMode(MetadataId::xmp), AccessMode::none);

}



TEST_F(ImageTest_1069, GoodMethodReturnsTrueAfterInitialization_1069) {

    EXPECT_TRUE(image_.good());

}
