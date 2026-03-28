#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "exif.hpp"

#include "value.hpp"

#include "types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffDecoderTest_1661 : public ::testing::Test {

protected:

    void SetUp() override {

        exifData_.clear();

        iptcData_.clear();

        xmpData_.clear();



        mockObject = std::make_unique<TiffEntryBase>(0x2600, ifdCanon, unsignedShort);

        decoder_ = std::make_unique<TiffDecoder>(exifData_, iptcData_, xmpData_, nullptr, nullptr);

    }



    void setMockObjectValue(const std::vector<int16_t>& intValues, const std::vector<uint16_t>& uintValues) {

        auto intValuePtr = Value::create(signedShort);

        for (auto val : intValues) {

            *intValuePtr << val;

        }

        mockObject->setValue(std::move(intValuePtr));



        auto uintValuePtr = Value::create(unsignedShort);

        for (auto val : uintValues) {

            *uintValuePtr << val;

        }

        mockObject->updateValue(std::move(uintValuePtr), bigEndian);

    }



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    std::unique_ptr<TiffDecoder> decoder_;

    std::unique_ptr<TiffEntryBase> mockObject;

};



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_NormalOperation_1661) {

    setMockObjectValue({ 8, 2, 3, 4, 5, 6, 7, 8 }, { 1, 2, 3, 4, 5, 6, 7, 8 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 10U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_InsufficientDataCount_1661) {

    setMockObjectValue({ 2 }, { 1 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 0U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_WrongTypeId_1661) {

    mockObject->setData(nullptr, 2, nullptr); // Set type to something other than unsignedShort

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 0U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_WrongCountInInts_1661) {

    setMockObjectValue({ 4, 2, 3, 4, 5, 6, 7, 8 }, { 1, 2, 3, 4, 5, 6, 7, 8 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 0U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_BoundaryCondition_NPointsZero_1661) {

    setMockObjectValue({ 4, 2, 3, 4, 5, 0 }, { 1, 2, 3, 4, 5 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 7U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_BoundaryCondition_NPointsOne_1661) {

    setMockObjectValue({ 4, 2, 3, 4, 5, 1 }, { 1, 2, 3, 4, 5 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 9U);

}



TEST_F(TiffDecoderTest_1661, DecodeCanonAFInfo_ErrorCase_RecordCountMismatch_1661) {

    setMockObjectValue({ 4, 2, 3, 4, 5, 7 }, { 1, 2, 3, 4, 5, 6, 7 });

    decoder_->decodeCanonAFInfo(mockObject.get());



    EXPECT_EQ(exifData_.count(), 0U);

}
