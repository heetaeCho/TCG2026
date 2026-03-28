#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1073 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image* image_;



    void SetUp() override {

        io_ = BasicIo::createMemIo();

        image_ = new Image(imageTypeJpeg, supportedExifMetadata, std::move(io_));

    }



    void TearDown() override {

        delete image_;

    }

};



TEST_F(ImageTest_1073, ClearExifData_NormallyClearsExifData_1073) {

    // Assuming the exifData_ is not empty initially

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("ArtistName");

    image_->exifData().add(key, value);

    delete value;



    EXPECT_FALSE(image_->exifData().empty());



    image_->clearExifData();



    EXPECT_TRUE(image_->exifData().empty());

}



TEST_F(ImageTest_1073, ClearExifData_IdempotentOperation_1073) {

    // Clearing exif data when it's already empty

    image_->clearExifData();



    EXPECT_NO_THROW(image_->clearExifData());

    EXPECT_TRUE(image_->exifData().empty());

}



TEST_F(ImageTest_1073, ClearExifData_DoesNotAffectOtherMetadata_1073) {

    // Assuming the iptcData_ and xmpData_ are not affected by clearExifData

    std::string comment = "Sample Comment";

    image_->setComment(comment);



    EXPECT_EQ(image_->comment(), comment);



    image_->clearExifData();



    EXPECT_EQ(image_->comment(), comment);

}



TEST_F(ImageTest_1073, ClearExifData_NoThrowOnEmptyData_1073) {

    // Ensure no exception is thrown when clearing already empty exif data

    EXPECT_NO_THROW(image_->clearExifData());

}
