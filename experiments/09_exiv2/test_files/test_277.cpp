#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffEncoderTest_277 : public ::testing::Test {

protected:

    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_ = nullptr;

    bool isNewImage_ = false;

    PrimaryGroups pPrimaryGroups_;

    const TiffHeaderBase* pHeader_ = nullptr;

    FindEncoderFct findEncoderFct_;



    TiffEncoderTest_277() {

        // Initialize necessary objects and mocks if needed

    }



    ~TiffEncoderTest_277() override {

        // Clean up if necessary

    }

};



TEST_F(TiffEncoderTest_277, ByteOrder_ReturnsCorrectValue_277) {

    TiffHeaderBase mockHeader(ByteOrder::bigEndian);

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, &mockHeader, findEncoderFct_);

    EXPECT_EQ(encoder.byteOrder(), ByteOrder::bigEndian);



    mockHeader = TiffHeaderBase(ByteOrder::littleEndian);

    TiffEncoder encoder2(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, &mockHeader, findEncoderFct_);

    EXPECT_EQ(encoder2.byteOrder(), ByteOrder::littleEndian);

}



TEST_F(TiffEncoderTest_277, SetDirty_ChangesDirtyFlag_277) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    EXPECT_FALSE(encoder.dirty());



    encoder.setDirty(true);

    EXPECT_TRUE(encoder.dirty());



    encoder.setDirty(false);

    EXPECT_FALSE(encoder.dirty());

}



TEST_F(TiffEncoderTest_277, WriteMethod_ReturnsDefaultWriteMethod_277) {

    TiffEncoder encoder(exifData_, iptcData_, xmpData_, pRoot_, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);

}
