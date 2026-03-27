#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::NiceMock;

using ::testing::_;



class MockTiffBinaryArray : public TiffBinaryArray {

public:

    MockTiffBinaryArray(uint16_t tag, IfdId group, const ArrayCfg& arrayCfg, const ArrayDef* arrayDef, size_t defSize)

        : TiffBinaryArray(tag, group, arrayCfg, arrayDef, defSize) {}

};



class MockExifdatum : public Exiv2::Exifdatum {

public:

    MockExifdatum(const Exiv2::ExifKey& key, const Exiv2::Value* pValue)

        : Exiv2::Exifdatum(key, pValue) {}

};



class TiffEncoderTest_1680 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects

        arrayCfg = ArrayCfg();

        arrayDef = ArrayDef();

        exifKey = Exiv2::ExifKey("SampleTag", 1, 1);

        value = std::make_unique<Exiv2::Value>();

        datum = new MockExifdatum(exifKey, value.get());

        binaryArray = new MockTiffBinaryArray(1, IfdId::rootIFD, arrayCfg, &arrayDef, 0);

    }



    void TearDown() override {

        // Clean up after tests

        delete datum;

        delete binaryArray;

    }



    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    Exiv2::ExifKey exifKey;

    std::unique_ptr<Exiv2::Value> value;

    MockExifdatum* datum;

    MockTiffBinaryArray* binaryArray;

};



TEST_F(TiffEncoderTest_1680, EncodeBinaryArrayCallsEncodeOffsetEntry_1680) {

    TiffEncoder encoder(Exiv2::ExifData(), Exiv2::IptcData(), Exiv2::XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    

    EXPECT_CALL(*binaryArray, doEncode(_, _)).WillOnce([this](TiffEncoder& encoder, const Exifdatum* datum) {

        encoder.encodeOffsetEntry(binaryArray, datum);

    });



    encoder.encodeBinaryArray(binaryArray, datum);

}



TEST_F(TiffEncoderTest_1680, EncodeBinaryArrayWithNullDatum_1680) {

    TiffEncoder encoder(Exiv2::ExifData(), Exiv2::IptcData(), Exiv2::XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    

    EXPECT_NO_THROW(encoder.encodeBinaryArray(binaryArray, nullptr));

}



TEST_F(TiffEncoderTest_1680, EncodeBinaryArrayWithNullObject_1680) {

    TiffEncoder encoder(Exiv2::ExifData(), Exiv2::IptcData(), Exiv2::XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    

    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, datum));

}
