#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffEncoderTest_278 : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    TiffComponent* pRoot = nullptr; // Assuming this needs to be initialized appropriately

    bool isNewImage = false;

    PrimaryGroups pPrimaryGroups;

    const TiffHeaderBase* pHeader = nullptr; // Assuming this needs to be initialized appropriately

    FindEncoderFct findEncoderFct;



    TiffEncoder encoder{exifData, iptcData, xmpData, pRoot, isNewImage, pPrimaryGroups, pHeader, findEncoderFct};



    virtual void SetUp() {

        // Initialize any necessary objects or variables here

    }



    virtual void TearDown() {

        // Clean up any resources if needed

    }

};



TEST_F(TiffEncoderTest_278, WriteMethodDefault_278) {

    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);

}



TEST_F(TiffEncoderTest_278, SetDirtyAndGetDirty_278) {

    encoder.setDirty(true);

    EXPECT_TRUE(encoder.dirty());



    encoder.setDirty(false);

    EXPECT_FALSE(encoder.dirty());

}
