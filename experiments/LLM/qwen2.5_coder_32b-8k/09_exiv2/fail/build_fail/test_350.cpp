#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeBinaryArray, (const TiffBinaryArray* object, const Exifdatum* datum), (override));

};



class TiffBinaryArrayTest_350 : public ::testing::Test {

protected:

    void SetUp() override {

        encoder = std::make_unique<MockTiffEncoder>(Exiv2::ExifData(), Exiv2::IptcData(), Exiv2::XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

        datum = new Exiv2::Exifdatum(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::Value());

    }



    void TearDown() override {

        delete datum;

    }



    std::unique_ptr<MockTiffEncoder> encoder;

    Exiv2::Exifdatum* datum;

};



TEST_F(TiffBinaryArrayTest_350, DoEncode_NormalOperation_350) {

    TiffBinaryArray array(1, IfdId::exifIFD, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*encoder, encodeBinaryArray(&array, datum)).Times(1);

    array.doEncode(*encoder, datum);

}



TEST_F(TiffBinaryArrayTest_350, DoEncode_WithNullDatum_350) {

    TiffBinaryArray array(1, IfdId::exifIFD, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*encoder, encodeBinaryArray(&array, nullptr)).Times(1);

    array.doEncode(*encoder, nullptr);

}



TEST_F(TiffBinaryArrayTest_350, DoEncode_VerifyExternalInteraction_350) {

    TiffBinaryArray array(1, IfdId::exifIFD, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*encoder, encodeBinaryArray(&array, datum)).WillOnce(Return());

    array.doEncode(*encoder, datum);

}
