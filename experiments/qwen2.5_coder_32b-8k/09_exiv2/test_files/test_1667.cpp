#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEncoderTest : public ::testing::Test {

protected:

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_ = nullptr;

    bool isNewImage_ = false;

    PrimaryGroups pPrimaryGroups_;

    const TiffHeaderBase* pHeader_ = nullptr;

    FindEncoderFct findEncoderFct_ = nullptr;



    ExifData exifData_;



    void SetUp() override {

        // Initialize any necessary objects or variables here

        pRoot_ = new TiffComponent();

        pHeader_ = new TiffHeaderBase(ByteOrder::big);

    }



    void TearDown() override {

        delete pRoot_;

        delete pHeader_;

    }

};



TEST_F(TiffEncoderTest, DirtyInitialValueFalse_1667) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    EXPECT_FALSE(encoder.dirty());

}



TEST_F(TiffEncoderTest, SetDirtyTrueAndGetTrue_1667) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    encoder.setDirty(true);

    EXPECT_TRUE(encoder.dirty());

}



TEST_F(TiffEncoderTest, SetDirtyFalseAndGetFalse_1667) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    encoder.setDirty(false);

    EXPECT_FALSE(encoder.dirty());

}



TEST_F(TiffEncoderTest, ExifDataNonEmptyMakesDirtyTrue_1667) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData_.add(key, value);

    EXPECT_TRUE(encoder.dirty());

}



TEST_F(TiffEncoderTest, ExifDataEmptyAndDirtyFlagFalseMakesDirtyFalse_1667) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    EXPECT_FALSE(encoder.dirty());

}
