#include <gtest/gtest.h>

#include "exiv2/bmffimage.hpp"

#include <memory>

#include <sstream>



using namespace Exiv2;



class BmffImageTest_1193 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    size_t max_box_depth = 10;



    void SetUp() override {

        io = BasicIo::create("");

    }



    BmffImage createBmffImageWithTag(uint32_t fileType) {

        auto image = BmffImage(std::move(io), false, max_box_depth);

        image.fileType_ = fileType; // Accessing private member for test setup only

        return image;

    }

};



TEST_F(BmffImageTest_1193, MimeTypeAvci_1193) {

    BmffImage image = createBmffImageWithTag(TAG::avci);

    EXPECT_EQ(image.mimeType(), "image/avci");

}



TEST_F(BmffImageTest_1193, MimeTypeAvcs_1193) {

    BmffImage image = createBmffImageWithTag(TAG::avcs);

    EXPECT_EQ(image.mimeType(), "image/avcs");

}



TEST_F(BmffImageTest_1193, MimeTypeAvif_1193) {

    BmffImage image = createBmffImageWithTag(TAG::avif);

    EXPECT_EQ(image.mimeType(), "image/avif");

}



TEST_F(BmffImageTest_1193, MimeTypeAvio_1193) {

    BmffImage image = createBmffImageWithTag(TAG::avio);

    EXPECT_EQ(image.mimeType(), "image/avif");

}



TEST_F(BmffImageTest_1193, MimeTypeAvis_1193) {

    BmffImage image = createBmffImageWithTag(TAG::avis);

    EXPECT_EQ(image.mimeType(), "image/avif");

}



TEST_F(BmffImageTest_1193, MimeTypeHeic_1193) {

    BmffImage image = createBmffImageWithTag(TAG::heic);

    EXPECT_EQ(image.mimeType(), "image/heic");

}



TEST_F(BmffImageTest_1193, MimeTypeHeim_1193) {

    BmffImage image = createBmffImageWithTag(TAG::heim);

    EXPECT_EQ(image.mimeType(), "image/heic");

}



TEST_F(BmffImageTest_1193, MimeTypeHeis_1193) {

    BmffImage image = createBmffImageWithTag(TAG::heis);

    EXPECT_EQ(image.mimeType(), "image/heic");

}



TEST_F(BmffImageTest_1193, MimeTypeHeix_1193) {

    BmffImage image = createBmffImageWithTag(TAG::heix);

    EXPECT_EQ(image.mimeType(), "image/heic");

}



TEST_F(BmffImageTest_1193, MimeTypeHeif_1193) {

    BmffImage image = createBmffImageWithTag(TAG::heif);

    EXPECT_EQ(image.mimeType(), "image/heif");

}



TEST_F(BmffImageTest_1193, MimeTypeMif1_1193) {

    BmffImage image = createBmffImageWithTag(TAG::mif1);

    EXPECT_EQ(image.mimeType(), "image/heif");

}



TEST_F(BmffImageTest_1193, MimeTypeJ2is_1193) {

    BmffImage image = createBmffImageWithTag(TAG::j2is);

    EXPECT_EQ(image.mimeType(), "image/j2is");

}



TEST_F(BmffImageTest_1193, MimeTypeJ2ki_1193) {

    BmffImage image = createBmffImageWithTag(TAG::j2ki);

    EXPECT_EQ(image.mimeType(), "image/hej2k");

}



TEST_F(BmffImageTest_1193, MimeTypeCrx_1193) {

    BmffImage image = createBmffImageWithTag(TAG::crx);

    EXPECT_EQ(image.mimeType(), "image/x-canon-cr3");

}



TEST_F(BmffImageTest_1193, MimeTypeJxl_1193) {

    BmffImage image = createBmffImageWithTag(TAG::jxl);

    EXPECT_EQ(image.mimeType(), "image/jxl");

}



TEST_F(BmffImageTest_1193, MimeTypeDefault_1193) {

    BmffImage image = createBmffImageWithTag(0); // Assuming 0 is an invalid tag

    EXPECT_EQ(image.mimeType(), "image/generic");

}
