#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class ImageTest_1047 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image* image_;



    void SetUp() override {

        io_ = std::make_unique<BasicIo>();

        image_ = new Image(imageTypeNone, 0, std::move(io_));

    }



    void TearDown() override {

        delete image_;

    }

};



TEST_F(ImageTest_1047, IsStringType_AsciiString_1047) {

    EXPECT_TRUE(image_->isStringType(asciiString));

}



TEST_F(ImageTest_1047, IsStringType_UnsignedByte_1047) {

    EXPECT_TRUE(image_->isStringType(unsignedByte));

}



TEST_F(ImageTest_1047, IsStringType_SignedByte_1047) {

    EXPECT_TRUE(image_->isStringType(signedByte));

}



TEST_F(ImageTest_1047, IsStringType_Undefined_1047) {

    EXPECT_TRUE(image_->isStringType(undefined));

}



TEST_F(ImageTest_1047, IsStringType_UnsignedShort_1047) {

    EXPECT_FALSE(image_->isStringType(unsignedShort));

}



TEST_F(ImageTest_1047, IsStringType_SignedShort_1047) {

    EXPECT_FALSE(image_->isStringType(signedShort));

}



TEST_F(ImageTest_1047, IsStringType_String_1047) {

    EXPECT_TRUE(image_->isStringType(string));

}



TEST_F(ImageTest_1047, IsStringType_Date_1047) {

    EXPECT_FALSE(image_->isStringType(date));

}



TEST_F(ImageTest_1047, IsStringType_Time_1047) {

    EXPECT_FALSE(image_->isStringType(time));

}



TEST_F(ImageTest_1047, IsStringType_Comment_1047) {

    EXPECT_TRUE(image_->isStringType(comment));

}



TEST_F(ImageTest_1047, IsStringType_Directory_1047) {

    EXPECT_FALSE(image_->isStringType(directory));

}



TEST_F(ImageTest_1047, IsStringType_XmpText_1047) {

    EXPECT_TRUE(image_->isStringType(xmpText));

}



TEST_F(ImageTest_1047, IsStringType_XmpAlt_1047) {

    EXPECT_FALSE(image_->isStringType(xmpAlt));

}



TEST_F(ImageTest_1047, IsStringType_XmpBag_1047) {

    EXPECT_FALSE(image_->isStringType(xmpBag));

}



TEST_F(ImageTest_1047, IsStringType_XmpSeq_1047) {

    EXPECT_FALSE(image_->isStringType(xmpSeq));

}



TEST_F(ImageTest_1047, IsStringType_LangAlt_1047) {

    EXPECT_TRUE(image_->isStringType(langAlt));

}



TEST_F(ImageTest_1047, IsStringType_InvalidTypeId_1047) {

    EXPECT_FALSE(image_->isStringType(invalidTypeId));

}
